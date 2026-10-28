#include "game_audio.hpp"
#include "garage_engine.hpp"
#include <atomic>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <thread>
#include <chrono>
using namespace pcr;
static std::atomic<unsigned long long> frames{0},energy{0};
static void mixed(void* buffer,unsigned int count){
    const auto* samples=static_cast<const float*>(buffer);unsigned long long value=0;
    for(unsigned int i=0;i<count*2;i++)if(std::isfinite(samples[i]))value+=static_cast<unsigned long long>(std::abs(samples[i])*1000000);
    frames.fetch_add(count);energy.fetch_add(value);
}
int main(int argc,char** argv){
    try{
        if(argc!=3)throw std::runtime_error("Supply assets and an isolated output file");
        SetTraceLogLevel(LOG_WARNING);
        {
            GameAudio audio;std::cerr<<"Initializing software audio device\n";audio.init(std::filesystem::u8path(argv[1]));
            if(!audio.ready)throw std::runtime_error("Software test audio device unavailable");
            std::cerr<<"Audio device initialized\n";AttachAudioMixedProcessor(mixed);
            Profile profile;equipPart(profile,PartSlot::Engine,1002);equipPart(profile,PartSlot::Turbo,3026);equipPart(profile,PartSlot::Nos,5007);equipPart(profile,PartSlot::Exhaust,9048);
            auto setup=buildVehicle(profile);CarState state;state.rpm=5000;state.speed=30;state.gear=3;state.boostPsi=25;
            for(int source=0;source<2;source++){
            profile.audioSource=source;auto previousEnergy=energy.load();
            for(int bank=0;bank<16;bank++){
                std::cerr<<"Mixing original profile "<<bank<<'\n';profile.soundOn=profile.soundOff=bank;
                for(int tick=0;tick<12;tick++){audio.update(profile,setup.vehicle,state,{true,false,true},0,true,true);std::this_thread::sleep_for(std::chrono::milliseconds(10));}
                audio.update(profile,setup.vehicle,state,{false,false,true},0,true,true);
            }
            profile.soundOn=profile.soundOff=-1;
            for(const auto& part:PartCatalog)if(part.slot==PartSlot::Engine){
                equipPart(profile,PartSlot::Engine,part.id);setup=buildVehicle(profile);
                for(bool throttle:{true,false})for(int tick=0;tick<12;tick++){
                    audio.update(profile,setup.vehicle,state,{throttle,false,true},0,true,true);
                    std::this_thread::sleep_for(std::chrono::milliseconds(10));
                }
            }
            Profile garageProfile=profile;equipPart(garageProfile,PartSlot::Engine,1008);auto garageVehicle=buildVehicle(garageProfile).vehicle;
            GarageEngine garage;garage.toggle(garageVehicle);audio.startEngine(garageProfile,true);
            for(int tick=0;tick<240;tick++){
                garage.update(garageVehicle,true,Step);
                audio.update(garageProfile,garageVehicle,garage.state,{true,false,true},0,true,true,garage.limiting);
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
            if(!garage.limiting)throw std::runtime_error("Garage audition failed to reach limiter");
            garage.stop();audio.stopEngine();audio.update(garageProfile,garageVehicle,garage.state,{},0,false,true);
            state.nitroActive=true;
            for(int tick=0;tick<30;tick++){audio.update(profile,setup.vehicle,state,{true,false,true,true},0,true,true);std::this_thread::sleep_for(std::chrono::milliseconds(10));}
            setup.vehicle.supercharged=true;state.gear=4;
            for(int tick=0;tick<30;tick++){audio.update(profile,setup.vehicle,state,{true,false,true},1.2,true,true);std::this_thread::sleep_for(std::chrono::milliseconds(10));}
            audio.click(true);audio.install(true);audio.horn(true);
            for(int tick=0;tick<4;tick++){audio.valve(tick,true);std::this_thread::sleep_for(std::chrono::milliseconds(30));}
            if(energy.load()<=previousEnergy)throw std::runtime_error("Silent audio bank after source switch");
            }
            DetachAudioMixedProcessor(mixed);
            if(audio.failures)throw std::runtime_error("An original music stream or sound event failed to load");
        }
        if(frames.load()==0||energy.load()==0)throw std::runtime_error("Original audio did not produce non-silent mixed PCM");
        std::ofstream out(std::filesystem::u8path(argv[2]));
        out<<"PASS: both banks, 16 engine profile pairs per bank, 31 automatic equipped-engine pairs per bank, turbo, supercharger, NOS, LS garage starter/idle/high-RPM rev limiter/shutdown and event sounds mixed through the real Raylib audio backend.\n"
           <<"stream_decode_failures=0\n"<<"frames="<<frames.load()<<"\nabsolute_pcm_energy_scaled="<<energy.load()<<"\n"
           <<"Software/null audio device only; physical speaker playback and stock-car engine assignment are not established.\n";
        std::cout<<"PASS: non-silent original audio mix, "<<frames.load()<<" frames\n";return 0;
    }catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
