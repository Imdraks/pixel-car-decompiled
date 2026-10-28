#include "game_audio.hpp"
#include <atomic>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <thread>
using namespace pcr;
static std::atomic<unsigned long long> frames{0},energy{0},peakMillion{0},invalid{0};
static void capture(void* buffer,unsigned count){
    const float* pcm=static_cast<const float*>(buffer);unsigned long long sum=0,peak=0;
    for(unsigned i=0;i<count*2;i++){
        if(!std::isfinite(pcm[i])){++invalid;continue;}
        auto value=static_cast<unsigned long long>(std::abs(pcm[i])*1000000);sum+=value;peak=std::max(peak,value);
    }
    frames+=count;energy+=sum;auto old=peakMillion.load();while(old<peak&&!peakMillion.compare_exchange_weak(old,peak)){}
}
static void require(bool value,const char* message){if(!value)throw std::runtime_error(message);}
int main(int argc,char** argv){try{
    require(argc==3,"Supply assets and report path");SetTraceLogLevel(LOG_WARNING);
    std::ofstream report(argv[2]);int cases=0;
    {
        GameAudio audio;audio.init(std::filesystem::u8path(argv[1]));require(audio.ready,"No real software audio device");AttachAudioMixedProcessor(capture);
        std::this_thread::sleep_for(std::chrono::milliseconds(2200));
        for(int bank=0;bank<2;bank++)for(const auto& pack:SimulatedPacks){
            Profile p;p.audioSource=bank;equipPart(p,PartSlot::Engine,pack.engineId);
            auto vehicle=buildVehicle(p).vehicle;vehicle.factoryBoostSoundPsi=0;vehicle.boostPsi=0;CarState state;state.rpm=1000;
            auto pump=[&](bool gas,int ticks){for(int tick=0;tick<ticks;tick++){state.elapsed+=.01;audio.update(p,vehicle,state,{gas,false,true},0,true,true);std::this_thread::sleep_for(std::chrono::milliseconds(10));}};
            auto startEvents=audio.simulatedStatus.startupEvents;audio.startEngine(p,true);pump(false,20);
            require(audio.simulatedStatus.engineId==pack.engineId&&audio.simulatedStatus.streams==int(pack.count),"Wrong active simulated bank");
            require(audio.simulatedStatus.startupEvents==startEvents+1,"Missing simulated startup");
            auto starts=audio.simulatedStatus.streamStarts;auto previousEnergy=energy.load();
            for(int tick=0;tick<100;tick++){
                double phase=tick/99.0;state.rpm=1000+(vehicle.redlineRpm+2300-1000)*(phase<.5?phase*2:(1-phase)*2);
                pump(tick<60,1);require(audio.simulatedStatus.gainSum<=.55001,"Crossfade gain exceeds headroom");
            }
            if(energy.load()<=previousEnergy)std::cerr<<"Silent case engine="<<pack.engineId<<" frames="<<frames.load()<<" gain="<<audio.simulatedStatus.gainSum<<" starts="<<audio.simulatedStatus.streamStarts<<'\n';
            require(energy.load()>previousEnergy,"Silent simulated loop mix");require(audio.simulatedStatus.streamStarts==starts,"RPM/load changes restarted music streams");
            // Independent manual overrides: preserve the opposite automatic layers.
            p.soundOn=4;pump(false,12);require(audio.simulatedStatus.engineId==pack.engineId&&audio.simulatedStatus.gainSum>0,"Manual charge discarded automatic coast");
            p.soundOn=-1;p.soundOff=4;pump(true,12);require(audio.simulatedStatus.gainSum>0,"Manual coast discarded automatic charge");
            auto stops=audio.simulatedStatus.shutdownEvents;audio.stopEngine(true);
            require(audio.simulatedStatus.shutdownEvents==stops+1&&audio.simulatedStatus.gainSum==0,"Shutdown did not stop loops and play the generated event");
            audio.update(p,vehicle,state,{},0,false,true);std::this_thread::sleep_for(std::chrono::milliseconds(70));
            audio.update(p,vehicle,state,{},0,false,false);require(audio.simulatedStatus.gainSum==0,"Muted engine leaked loop gain");
            p.soundOn=p.soundOff=4;pump(true,12);require(audio.simulatedStatus.engineId==0,"Full manual sound must bypass the simulated bank");
            report<<"PASS engine="<<pack.engineId<<" source_bank="<<bank<<" streams="<<pack.count<<" no_restarts=1 independent_overrides=1 startup_shutdown=1 mute=1\n";++cases;
        }
        // Switching back to an untouched source engine releases all simulated loops.
        Profile fallback;equipPart(fallback,PartSlot::Engine,1002);auto v=buildVehicle(fallback).vehicle;CarState s;s.rpm=4000;
        audio.update(fallback,v,s,{true,false,true},0,true,true);require(audio.simulatedStatus.engineId==0,"Source engine uses an unrelated simulated pack");
        require(audio.failures==0,"Stream or event load failure");DetachAudioMixedProcessor(capture);
    }
    require(cases==12&&frames>0&&invalid==0&&peakMillion<1000000,"Invalid or saturated real mixed PCM");
    report<<"PASS: 12 real simulated engine/bank cases, fallback, event and manual-priority checks.\nframes="<<frames<<"\npeak="<<peakMillion.load()/1000000.0<<"\nfinite_pcm=1\nphysical_speaker_listening=0\n";
    std::cout<<"PASS: 12 simulated engine/bank cases, peak "<<peakMillion.load()/1000000.0<<'\n';return 0;
}catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
