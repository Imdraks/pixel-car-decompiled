#include "game_audio.hpp"
#include "vehicle_garage.hpp"
#include <atomic>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <thread>
#include <stdexcept>
using namespace pcr;
static std::atomic<unsigned long long> energy{0},peak{0},invalid{0};
static void capture(void* buffer,unsigned frames){auto pcm=static_cast<const float*>(buffer);unsigned long long sum=0;
    for(unsigned i=0;i<frames*2;i++){if(!std::isfinite(pcm[i])){++invalid;continue;}auto x=static_cast<unsigned long long>(std::abs(pcm[i])*1000000);sum+=x;auto p=peak.load();while(p<x&&!peak.compare_exchange_weak(p,x)){}}energy+=sum;
}
static void require(bool v,const char* s){if(!v)throw std::runtime_error(s);}
int main(int argc,char** argv){try{
    require(argc==3,"Supply assets and report");SetTraceLogLevel(LOG_WARNING);std::ofstream report(argv[2]);GameAudio audio;audio.init(std::filesystem::u8path(argv[1]));require(audio.ready,"No software audio device");AudioVolumes levels;levels.turbo=levels.effects=levels.ambience=levels.interface=0;audio.setVolumes(levels);AttachAudioMixedProcessor(capture);std::this_thread::sleep_for(std::chrono::milliseconds(2200));int cases=0;
    for(int bank=0;bank<2;bank++)for(size_t i=0;i<std::size(VehicleCatalog);i++){
        const auto& entry=VehicleCatalog[i];if(entry.body!=0&&entry.body!=63&&entry.body!=121&&entry.body!=94)continue;
        Profile p=factoryVehicle(int(i));p.audioSource=bank;auto v=buildVehicle(p).vehicle;CarState state;state.rpm=v.idleRpm;auto pump=[&](int ticks){for(int t=0;t<ticks;t++){state.elapsed+=.01;audio.update(p,v,state,{true,false,true},0,true,true,false,true);std::this_thread::sleep_for(std::chrono::milliseconds(10));}};
        audio.startEngine(p,true);pump(25);audio.stopEngine();pump(10);auto before=energy.load();state.rpm=v.redlineRpm*.8;pump(35);
        require(energy.load()>before&&audio.failures==0,"Silent or missing vehicle engine sound");
        auto samples=engineSamples(p);require(samples.on>=0&&samples.on<94&&samples.off>=0&&samples.off<94,"Invalid factory sound selection");
        report<<"PASS "<<entry.id<<" bank="<<bank<<" installed="<<p.parts[0]<<" audio="<<audioEngineId(p)<<" simulated="<<audio.simulatedStatus.engineId<<'\n';++cases;
        if(entry.body==63&&entry.source==0){equipPart(p,PartSlot::Engine,entry.stockEngineId);v=buildVehicle(p).vehicle;before=energy.load();pump(25);require(energy.load()>before&&audioEngineId(p)==20008,"Recovered provisional Porsche block used the old Golf sound");report<<"PASS recovered Porsche block uses F6 audio in bank "<<bank<<'\n';++cases;}
        audio.stopEngine();audio.update(p,v,state,{},0,false,true);
    }
    require(cases>=14&&invalid==0&&peak<1000000&&audio.failures==0,"Invalid, clipped or incomplete vehicle audio");DetachAudioMixedProcessor(capture);report<<"cases="<<cases<<"\npeak="<<peak.load()/1000000.0<<"\nfinite_pcm=1\nphysical_speaker_listening=0\n";std::cout<<"PASS: "<<cases<<" real factory-vehicle audio cases, peak "<<peak.load()/1000000.0<<'\n';return 0;
}catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}}
