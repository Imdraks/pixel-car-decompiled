#include "game_audio.hpp"
#include <atomic>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <thread>
using namespace pcr;
static std::atomic<unsigned long long> energy{0},invalid{0},peak{0};
static void capture(void* buffer,unsigned frames){
    auto pcm=static_cast<const float*>(buffer);unsigned long long sum=0;
    for(unsigned i=0;i<frames*2;i++){
        if(!std::isfinite(pcm[i])){++invalid;continue;}
        auto x=static_cast<unsigned long long>(std::abs(pcm[i])*1000000);sum+=x;
        auto previous=peak.load();while(previous<x&&!peak.compare_exchange_weak(previous,x)){}
    }
    energy+=sum;
}
static void require(bool ok,const char* message){if(!ok)throw std::runtime_error(message);}
int main(int argc,char** argv){try{
    require(argc==3,"Supply assets and report");SetTraceLogLevel(LOG_WARNING);std::ofstream report(argv[2]);
    GameAudio audio;audio.init(std::filesystem::u8path(argv[1]));require(audio.ready,"No audio device");
    AttachAudioMixedProcessor(capture);std::this_thread::sleep_for(std::chrono::milliseconds(2200));
    Profile p;CarState state;auto vehicle=buildVehicle(p).vehicle;int cases=0;
    AudioVolumes levels;levels.engine=levels.turbo=levels.effects=levels.ambience=levels.interface=0;
    auto pump=[&](int track,bool enabled,int ticks){for(int i=0;i<ticks;i++){
        audio.update(p,vehicle,state,{},0,false,enabled);audio.updateMusic(p,track,enabled);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }};
    for(int bank=0;bank<2;bank++)for(int track:{46,4}){
        p.audioSource=bank;levels.music=.5;audio.setVolumes(levels);pump(track,true,45);
        auto before=energy.load();pump(track,true,30);
        require(energy.load()>before&&audio.musicStatus.gain>0,"Music category produced no PCM");
        require(audio.musicStatus.track==track&&audio.musicStatus.bank==bank,"Wrong source music");
        auto starts=audio.musicStatus.streamStarts;auto pos=audio.musicStatus.seconds;
        levels.music=0;audio.setVolumes(levels);pump(track,true,30);before=energy.load();pump(track,true,20);
        require(energy.load()==before&&audio.musicStatus.gain==0,"Music mute leaked PCM");
        require(audio.musicStatus.seconds>pos&&audio.musicStatus.streamStarts==starts,"Slider restarted music");
        levels.music=.5;audio.setVolumes(levels);pump(track,true,20);pos=audio.musicStatus.seconds;
        pump(-1,true,30);before=energy.load();pump(-1,true,20);
        require(energy.load()==before&&audio.musicStatus.track==-1,"Music leaked into driving");
        require(std::abs(audio.musicStatus.seconds-pos)<.03,"Driving advanced paused music");
        pump(track,true,30);require(audio.musicStatus.seconds>pos&&audio.musicStatus.streamStarts==starts,"Returning from driving restarted the song");
        pump(track,false,30);before=energy.load();pump(track,false,20);require(energy.load()==before,"Global sound disable leaked music");
        pump(track,true,25);before=energy.load();pump(track,true,20);require(energy.load()>before,"Music failed to resume after sound enable");
        report<<"PASS bank="<<bank<<" track="<<track<<" independent_gain mute preserve_position driving_silence resume global_sound\n";++cases;
    }
    levels.music=0;levels.effects=1;audio.setVolumes(levels);pump(4,true,30);auto before=energy.load();audio.horn(true);pump(4,true,20);
    require(energy.load()>before,"Music mute also muted effects");
    require(cases==4&&invalid==0&&peak<1000000&&audio.failures==0,"Invalid, clipped or missing audio");
    DetachAudioMixedProcessor(capture);report<<"PASS independent effects with music muted\npeak="<<peak.load()/1000000.0<<"\nfinite_pcm=1\nphysical_speaker_listening=0\n";
    std::cout<<"PASS: four real music/bank cases, no music in driving, peak "<<peak.load()/1000000.0<<'\n';return 0;
}catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}}
