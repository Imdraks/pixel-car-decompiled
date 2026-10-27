#include "game_audio.hpp"
#include "original_audio.hpp"
#include "base_audio.hpp"
#include <algorithm>
#include <fstream>
#include <cmath>
#include <stdexcept>
namespace pcr {
void checkOriginalAudio(const std::filesystem::path& assets,const std::filesystem::path& output){
    if(!std::filesystem::create_directory(output))throw std::runtime_error("Le contrôle audio exige un dossier neuf.");
    std::ofstream report(output/"audio-report.txt");int count=0;
    for(int bank=0;bank<2;bank++)for(int id=0;id<94;id++){
        const auto& source=sourceSound(id,bank);
        auto path=(assets/source.file).u8string();Wave wave=LoadWave(path.c_str());
        bool valid=IsWaveValid(wave)&&wave.frameCount>0&&wave.sampleRate>0;
        if(valid&&std::string(source.name).find("engine")!=std::string::npos){
            float* samples=LoadWaveSamples(wave);bool nonSilent=false;
            if(samples){for(unsigned int i=0;i<wave.frameCount*wave.channels;i++)if(std::abs(samples[i])>.000001f){nonSilent=true;break;}UnloadWaveSamples(samples);}
            valid=nonSilent;
        }
        report<<(valid?"PASS ":"FAIL ")<<(bank==1?"original/":"unbound/")<<source.name<<" frames="<<wave.frameCount<<" sample_rate="<<wave.sampleRate<<'\n';
        if(IsWaveValid(wave))UnloadWave(wave);
        if(!valid)throw std::runtime_error(std::string("Son original illisible : ")+source.name);
        ++count;
    }
    report<<"PASS: "<<count<<" original sounds decoded without opening an audio device. Physical playback is not established.\n";
}
void GameAudio::init(const std::filesystem::path& path){root=path;InitAudioDevice();ready=IsAudioDeviceReady();}
void GameAudio::selectBank(int value){
    value=value==1?1:0;if(value==bank)return;
    for(auto* stream:{&on,&off,&turbo,&blower,&nos,&town})if(stream->id>=0){UnloadMusicStream(stream->music);*stream=Loop{};}
    for(auto& s:shots)UnloadSound(s.second);
    shots.clear();bank=value;reset();
}
void GameAudio::loop(Loop& stream,int id,float volume,float pitch){
    if(stream.id!=id){
        if(stream.id>=0)UnloadMusicStream(stream.music);
        stream.music=LoadMusicStream((root/sourceSound(id,bank).file).u8string().c_str());
        if(!IsMusicValid(stream.music)){stream.id=-1;++failures;return;}
        stream.id=id;stream.music.looping=true;SetMusicVolume(stream.music,std::clamp(volume,0.f,1.f));SetMusicPitch(stream.music,std::clamp(pitch,.25f,3.f));PlayMusicStream(stream.music);
    }
    UpdateMusicStream(stream.music);
    SetMusicVolume(stream.music,std::clamp(volume,0.f,1.f));SetMusicPitch(stream.music,std::clamp(pitch,.25f,3.f));
}
void GameAudio::shot(int id,float volume){
    auto i=shots.find(id);
    if(i==shots.end()){Sound sound=LoadSound((root/sourceSound(id,bank).file).u8string().c_str());if(!IsSoundValid(sound)){++failures;return;}i=shots.emplace(id,sound).first;}
    SetSoundVolume(i->second,volume);PlaySound(i->second);
}
void GameAudio::update(const Profile& profile,const Vehicle& vehicle,const CarState& car,const DriverInput& input,double collision,bool active,bool enabled,bool limiter){
    if(!ready)return;
    selectBank(profile.audioSource);
    if(!enabled)for(auto& sound:shots)StopSound(sound.second);
    auto samples=engineSamples(profile);bool gas=active&&input.throttle&&(!input.brake||car.burningOut||car.neutral||car.handbraking);
    float audible=enabled&&active?1.f:0.f;
    float pitch=float(.45+car.rpm/6500.0),load=gas?1.f:.15f;
    if(car.launching||limiter)load*=std::sin(car.elapsed*62.831853)>0?1.f:.25f;
    loop(on,samples.on,audible*.34f*load,pitch);
    loop(off,samples.off,audible*(gas?.04f:.23f),pitch*.94f);
    loop(turbo,29,audible*float(std::clamp(car.boostPsi/35,0.0,.7))*(vehicle.supercharged?0.f:1.f),float(.65+car.boostPsi/30));
    loop(blower,28,audible*float(std::clamp(car.boostPsi/50,0.0,.6))*(vehicle.supercharged?1.f:0.f),pitch);
    if(car.nitroActive&&!lastNos&&nos.id>=0)SeekMusicStream(nos.music,0);
    loop(nos,76,audible*(car.nitroActive?.35f:0.f),1);
    loop(town,58,enabled?(active?.025f:.12f):0.f,1);
    if(enabled&&active){
        if((car.launching||limiter)&&car.elapsed>=nextLaunchPop){shot(43,.12f);nextLaunchPop=car.elapsed+.13;}
        if(car.gear!=lastGear)shot(44,.30f);
        if(((lastGas&&!gas)||car.gear!=lastGear)&&lastBoost>2&&!vehicle.supercharged){
            static constexpr int valves[]={77,0,17,53};int choice=profile.bov<0?(vehicle.boostPsi>=30?3:0):std::clamp(profile.bov,0,3);shot(valves[choice],.42f);
        }
        if(collision>lastCollision+.5)shot(1+(crashes++%3),.55f);
        if(car.gear!=lastGear&&profile.parts[int(PartSlot::Exhaust)]!=0)shot(43,.25f);
    }
    lastGear=car.gear;lastGas=gas;lastNos=car.nitroActive;lastBoost=car.boostPsi;lastCollision=collision;
}
GameAudio::~GameAudio(){
    if(!ready)return;
    for(auto* stream:{&on,&off,&turbo,&blower,&nos,&town})if(stream->id>=0)UnloadMusicStream(stream->music);
    for(auto& s:shots)UnloadSound(s.second);
    CloseAudioDevice();
}
}
