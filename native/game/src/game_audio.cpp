#include "game_audio.hpp"
#include "original_audio.hpp"
#include "base_audio.hpp"
#include <algorithm>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <chrono>
#include <cstdint>
namespace pcr {
void checkOriginalAudio(const std::filesystem::path& assets,const std::filesystem::path& output){
    if(!std::filesystem::create_directory(output))throw std::runtime_error("Le contrôle audio exige un dossier neuf.");
    std::ofstream report(output/"audio-report.txt"),loops(output/"engine-loop-report.json");int count=0,loopCount=0;
    loops<<"{\"loops\":[";
    for(int bank=0;bank<2;bank++)for(int id=0;id<94;id++){
        const auto& source=sourceSound(id,bank);
        auto path=(assets/source.file).u8string();Wave wave=LoadWave(path.c_str());
        bool valid=IsWaveValid(wave)&&wave.frameCount>0&&wave.sampleRate>0;
        if(valid&&std::string(source.name).find("engine")!=std::string::npos){
            float* samples=LoadWaveSamples(wave);bool nonSilent=false;
            if(samples){
                auto conditioned=seamlessEngineLoop(samples,wave.frameCount,wave.channels,wave.sampleRate);
                double before=0,after=0,peakBefore=0,peakAfter=0;
                for(unsigned c=0;c<wave.channels;c++){
                    before=std::max(before,double(std::abs(samples[c]-samples[size_t(wave.frameCount-1)*wave.channels+c])));
                    if(!conditioned.empty())after=std::max(after,double(std::abs(conditioned[c]-conditioned[conditioned.size()-wave.channels+c])));
                }
                for(size_t i=0;i<size_t(wave.frameCount)*wave.channels;i++){nonSilent|=std::abs(samples[i])>.000001f;peakBefore=std::max(peakBefore,double(std::abs(samples[i])));}
                for(float value:conditioned)peakAfter=std::max(peakAfter,double(std::abs(value)));
                if(conditioned.empty()||after>before+.00001||peakAfter>peakBefore+.00001)throw std::runtime_error("Engine loop conditioning increased a seam or peak");
                if(loopCount++)loops<<',';
                loops<<"{\"bank\":"<<bank<<",\"sample\":\""<<source.name<<"\",\"seam_before\":"<<before<<",\"seam_after\":"<<after<<",\"peak_before\":"<<peakBefore<<",\"peak_after\":"<<peakAfter<<"}";
                UnloadWaveSamples(samples);
            }
            valid=nonSilent;
        }
        report<<(valid?"PASS ":"FAIL ")<<(bank==1?"original/":"unbound/")<<source.name<<" frames="<<wave.frameCount<<" sample_rate="<<wave.sampleRate<<'\n';
        if(IsWaveValid(wave))UnloadWave(wave);
        if(!valid)throw std::runtime_error(std::string("Son original illisible : ")+source.name);
        ++count;
    }
    report<<"PASS: "<<count<<" original sounds decoded without opening an audio device. Physical playback is not established.\n";
    loops<<"],\"engine_bank_cases\":"<<loopCount<<",\"source_files_modified\":false}\n";
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
        stream.memory.clear();stream.gain=0;
        const auto& source=sourceSound(id,bank);auto path=(root/source.file).u8string();
        if(std::string(source.name).find("engine")!=std::string::npos){
            Wave wave=LoadWave(path.c_str());
            if(IsWaveValid(wave)){
                float* pcm=LoadWaveSamples(wave);
                auto conditioned=seamlessEngineLoop(pcm,wave.frameCount,wave.channels,wave.sampleRate);
                if(pcm)UnloadWaveSamples(pcm);
                if(!conditioned.empty()){
                    auto& bytes=stream.memory;bytes.resize(44+conditioned.size()*2);
                    auto word=[&](size_t pos,uint32_t value,int count){for(int i=0;i<count;i++)bytes[pos+i]=static_cast<unsigned char>(value>>(i*8));};
                    auto tag=[&](size_t pos,const char* value){for(int i=0;i<4;i++)bytes[pos+i]=static_cast<unsigned char>(value[i]);};
                    tag(0,"RIFF");word(4,uint32_t(bytes.size()-8),4);tag(8,"WAVE");tag(12,"fmt ");word(16,16,4);word(20,1,2);word(22,wave.channels,2);
                    word(24,wave.sampleRate,4);word(28,wave.sampleRate*wave.channels*2,4);word(32,wave.channels*2,2);word(34,16,2);tag(36,"data");word(40,uint32_t(conditioned.size()*2),4);
                    for(size_t i=0;i<conditioned.size();i++)word(44+i*2,uint16_t(int16_t(std::lround(conditioned[i]*32767))),2);
                }
                UnloadWave(wave);
            }
        }
        stream.music=stream.memory.empty()?LoadMusicStream(path.c_str()):LoadMusicStreamFromMemory(".wav",stream.memory.data(),int(stream.memory.size()));
        if(!IsMusicValid(stream.music)){stream.id=-1;++failures;return;}
        stream.id=id;stream.music.looping=true;SetMusicVolume(stream.music,0);SetMusicPitch(stream.music,std::clamp(pitch,.25f,3.f));PlayMusicStream(stream.music);
    }
    UpdateMusicStream(stream.music);
    float target=std::clamp(volume*sourceSound(id,bank).volume,0.f,1.f);
    stream.gain=target==0?0:stream.gain+(target-stream.gain)*float(1-std::exp(-audioDt/.015));
    SetMusicVolume(stream.music,stream.gain);SetMusicPitch(stream.music,std::clamp(pitch,.25f,3.f));
}
void GameAudio::shot(int id,float volume){
    auto i=shots.find(id);
    if(i==shots.end()){Sound sound=LoadSound((root/sourceSound(id,bank).file).u8string().c_str());if(!IsSoundValid(sound)){++failures;return;}i=shots.emplace(id,sound).first;}
    SetSoundVolume(i->second,volume);PlaySound(i->second);
}
void GameAudio::update(const Profile& profile,const Vehicle& vehicle,const CarState& car,const DriverInput& input,double collision,bool active,bool enabled,bool limiter){
    if(!ready)return;
    selectBank(profile.audioSource);
    double now=std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
    audioDt=lastUpdate>0?std::clamp(now-lastUpdate,0.0,.1):1.0/60;lastUpdate=now;
    if(!enabled)for(auto& sound:shots)StopSound(sound.second);
    auto samples=engineSamples(profile);bool gas=active&&input.throttle&&(!input.brake||car.burningOut||car.neutral||car.handbraking);
    float audible=enabled&&active?1.f:0.f;
    engineMix.update(car.rpm,gas,audible>0,audioDt,samples.on);
    float pitch=float(engineMix.pitch),load=float(engineMix.load);
    float cut=limiter?float(.3+.7*(.5+.5*std::sin(car.elapsed*62.831853))):car.launching?(std::sin(car.elapsed*62.831853)>0?1.f:.25f):1.f;
    float onVolume=audible*.40f*load*cut,offVolume=audible*.32f*(1-load);
    // sfx_engine2e is a byte-identical alias of sfx_engine2 in each source bank.
    auto canonical=[](int id){return id==22?21:id;};
    if(canonical(samples.on)==canonical(samples.off)){onVolume+=offVolume;offVolume=0;}
    loop(on,samples.on,onVolume,pitch);
    loop(off,samples.off,offVolume,pitch);
    loop(turbo,29,audible*float(std::clamp(car.boostPsi/35,0.0,.7))*(vehicle.supercharged?0.f:1.f),float(.65+car.boostPsi/30));
    loop(blower,28,audible*float(std::clamp(car.boostPsi/50,0.0,.6))*(vehicle.supercharged?1.f:0.f),pitch);
    if(car.nitroActive&&!lastNos&&nos.id>=0)SeekMusicStream(nos.music,0);
    loop(nos,76,audible*(car.nitroActive?.35f:0.f),1);
    loop(town,58,enabled?(active?.025f:.12f):0.f,1);
    if(enabled&&active){
        if(car.launching&&car.elapsed>=nextLaunchPop){shot(43,.12f);nextLaunchPop=car.elapsed+.13;}
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
