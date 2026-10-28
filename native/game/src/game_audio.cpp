#include "game_audio.hpp"
#include "garage_audio.hpp"
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
    std::ofstream simulation(output/"simulated-audio-report.txt");int simulatedCount=0;
    for(const auto& pack:SimulatedPacks){
        auto folder=(assets/pack.startup).parent_path();
        if(!std::filesystem::is_directory(folder))throw std::runtime_error("Missing simulated engine pack");
        for(const auto& entry:std::filesystem::directory_iterator(folder)){
            auto extension=entry.path().extension();if(extension!=".wav"&&extension!=".ogg")continue;
            Wave wave=LoadWave(entry.path().u8string().c_str());
            bool valid=IsWaveValid(wave)&&wave.sampleRate==44100&&wave.channels==1&&wave.frameCount>44100&&wave.frameCount<44100*4;
            double peak=0,seam=0;bool nonSilent=false;
            if(valid){float* samples=LoadWaveSamples(wave);valid=samples!=nullptr;
                if(samples){for(unsigned i=0;i<wave.frameCount;i++){valid&=std::isfinite(samples[i]);peak=std::max(peak,double(std::abs(samples[i])));nonSilent|=std::abs(samples[i])>.00001f;}
                    seam=std::abs(samples[0]-samples[wave.frameCount-1]);UnloadWaveSamples(samples);}
            }
            valid&=nonSilent&&peak<.99;
            if(entry.path().filename().string().find("_rpm_")!=std::string::npos)valid&=seam<=.04;
            simulation<<(valid?"PASS ":"FAIL ")<<entry.path().filename().string()<<" peak="<<peak<<" seam="<<seam<<'\n';
            if(IsWaveValid(wave))UnloadWave(wave);
            if(!valid)throw std::runtime_error("Invalid simulated engine audio");
            ++simulatedCount;
        }
    }
    if(simulatedCount!=198)throw std::runtime_error("Incomplete simulated engine bank");
    simulation<<"PASS: "<<simulatedCount<<" WAV/OGG simulated files decoded, no saturation, finite samples and bounded loop seams.\n";
}
void GameAudio::clearSimulated(){
    for(auto& stream:simulatedLoops)if(IsMusicValid(stream.music))UnloadMusicStream(stream.music);
    simulatedLoops.clear();
    if(IsSoundValid(simulatedStartup))UnloadSound(simulatedStartup);
    if(IsSoundValid(simulatedShutdown))UnloadSound(simulatedShutdown);
    simulatedStartup={};simulatedShutdown={};simulated=nullptr;starting=false;
    simulatedStatus.engineId=0;simulatedStatus.streams=0;simulatedStatus.gainSum=0;simulatedStatus.audible=false;
}
bool GameAudio::loadSimulated(int engineId){
    if(simulatedRequested==engineId)return simulated!=nullptr;
    clearSimulated();simulatedRequested=engineId;
    const auto* pack=simulatedPack(engineId);if(!pack)return false;
    bool present=std::filesystem::is_regular_file(root/pack->startup)&&std::filesystem::is_regular_file(root/pack->shutdown);
    for(std::size_t i=0;i<pack->count;i++)present&=std::filesystem::is_regular_file(root/pack->clips[i].file);
    if(!present){++failures;return false;}
    for(std::size_t i=0;i<pack->count;i++){
        Music music=LoadMusicStream((root/pack->clips[i].file).u8string().c_str());
        if(!IsMusicValid(music)){++failures;clearSimulated();return false;}
        music.looping=true;SetMusicVolume(music,0);PlayMusicStream(music);
        simulatedLoops.push_back({music,0,1});++simulatedStatus.streamStarts;
    }
    simulatedStartup=LoadSound((root/pack->startup).u8string().c_str());
    simulatedShutdown=LoadSound((root/pack->shutdown).u8string().c_str());
    if(!IsSoundValid(simulatedStartup)||!IsSoundValid(simulatedShutdown)){++failures;clearSimulated();return false;}
    simulated=pack;simulatedStatus.engineId=engineId;simulatedStatus.streams=int(pack->count);return true;
}
void GameAudio::muteSimulated(){
    for(auto& stream:simulatedLoops){stream.gain=0;SetMusicVolume(stream.music,0);}
    simulatedStatus.gainSum=0;simulatedStatus.audible=false;
}
void GameAudio::updateSimulated(double rpm,double load,float audible,float cut,bool autoOn,bool autoOff){
    if(!simulated)return;
    double loopFade=1;
    if(starting){
        startupElapsed+=audioDt;
        loopFade=std::max(load,std::clamp((startupElapsed-simulated->startupSeconds+.3)/.3,0.0,1.0));
        SetSoundVolume(simulatedStartup,float(audible*.45*volumes.engine*(1-loopFade)));
        if(startupElapsed>=simulated->startupSeconds){starting=false;StopSound(simulatedStartup);}
    }
    simulatedStatus.gainSum=0;simulatedStatus.audible=audible>0;
    double smoothing=1-std::exp(-audioDt/.035);
    for(std::size_t i=0;i<simulatedLoops.size();i++){
        auto mix=simulatedClipMix(*simulated,i,rpm,load,autoOn,autoOff);auto& stream=simulatedLoops[i];
        double target=audible*.55*cut*loopFade*mix.gain*volumes.engine;
        stream.gain=audible<=0||volumes.engine<=0?0:float(stream.gain+(target-stream.gain)*smoothing);
        stream.pitch=float(stream.pitch+(mix.pitch-stream.pitch)*smoothing);
        SetMusicVolume(stream.music,stream.gain);SetMusicPitch(stream.music,stream.pitch);UpdateMusicStream(stream.music);
        simulatedStatus.gainSum+=stream.gain;
    }
}
void GameAudio::startEngine(const Profile& profile,bool enabled){
    if(!ready||!enabled)return;
    lastEnabled=enabled;selectBank(profile.audioSource);reset();
    bool autoSound=profile.soundOn<0||profile.soundOff<0;
    if(autoSound&&loadSimulated(profile.parts[int(PartSlot::Engine)])){
        StopSound(simulatedShutdown);StopSound(simulatedStartup);
        SetSoundVolume(simulatedStartup,float(.45*volumes.engine));PlaySound(simulatedStartup);
        starting=true;startupElapsed=0;++simulatedStatus.startupEvents;
    }else shot(45,.4f);
}
void GameAudio::stopEngine(bool shutdown){
    if(!ready)return;
    auto start=shots.find(45);if(start!=shots.end())StopSound(start->second);
    if(simulated){
        StopSound(simulatedStartup);starting=false;muteSimulated();
        if(shutdown&&lastEnabled){SetSoundVolume(simulatedShutdown,float(.45*volumes.engine));PlaySound(simulatedShutdown);++simulatedStatus.shutdownEvents;}
        else StopSound(simulatedShutdown);
    }
    reset();
}
void GameAudio::init(const std::filesystem::path& path){root=path;InitAudioDevice();ready=IsAudioDeviceReady();if(ready)SetMasterVolume(float(volumes.master));}
float GameAudio::shotChannel(int id)const{
    if(id==45||id==27)return float(volumes.engine);
    if(id==77||id==0||id==17||id==53)return float(volumes.turbo);
    if(id==37||id==40||id==41||id==33||id==34||id==55)return float(volumes.interface);
    return float(volumes.effects);
}
void GameAudio::setVolumes(const AudioVolumes& value){
    auto next=validateVolumes(value);if(next==volumes)return;volumes=next;if(!ready)return;
    SetMasterVolume(float(volumes.master));
    for(auto& pair:shots)SetSoundVolume(pair.second,shotBaseVolumes[pair.first]*shotChannel(pair.first));
    if(IsSoundValid(simulatedStartup))SetSoundVolume(simulatedStartup,float(.45*volumes.engine));
    if(IsSoundValid(simulatedShutdown))SetSoundVolume(simulatedShutdown,float(.45*volumes.engine));
}
void GameAudio::selectBank(int value){
    value=value==1?1:0;if(value==bank)return;
    for(auto* stream:{&on,&off,&turbo,&blower,&nos,&town,&music})if(stream->id>=0){UnloadMusicStream(stream->music);*stream=Loop{};}
    for(auto& s:shots)UnloadSound(s.second);
    shots.clear();shotBaseVolumes.clear();bank=value;musicStatus.track=-1;reset();
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
    double group=(&stream==&on||&stream==&off)?volumes.engine:(&stream==&turbo||&stream==&blower)?volumes.turbo:(&stream==&town)?volumes.ambience:(&stream==&music)?volumes.music:volumes.effects;
    float target=std::clamp(float(volume*sourceSound(id,bank).volume*group),0.f,1.f);
    stream.gain=target==0?0:stream.gain+(target-stream.gain)*float(1-std::exp(-audioDt/.015));
    SetMusicVolume(stream.music,stream.gain);SetMusicPitch(stream.music,std::clamp(pitch,.25f,3.f));
}
void GameAudio::updateMusic(const Profile& profile,int track,bool enabled){
    if(!ready)return;
    selectBank(profile.audioSource);
    if(track<0){
        if(music.id>=0){SetMusicVolume(music.music,0);PauseMusicStream(music.music);}
        music.gain=0;musicStatus.track=-1;musicStatus.gain=0;return;
    }
    // Stable source indices: title, workshop, map. Keep muted streams running so
    // sliders/global sound do not restart a song or change engine state.
    if(track!=46&&track!=4&&track!=5)track=46;
    bool changed=music.id!=track;
    if(!changed&&!IsMusicStreamPlaying(music.music))ResumeMusicStream(music.music);
    loop(music,track,enabled?.18f:0.f,1);
    if(changed&&music.id==track)++musicStatus.streamStarts;
    musicStatus.track=music.id;musicStatus.bank=bank;musicStatus.gain=music.gain;
    musicStatus.seconds=music.id>=0?GetMusicTimePlayed(music.music):0;
}
void GameAudio::shot(int id,float volume){
    auto i=shots.find(id);
    if(i==shots.end()){Sound sound=LoadSound((root/sourceSound(id,bank).file).u8string().c_str());if(!IsSoundValid(sound)){++failures;return;}i=shots.emplace(id,sound).first;}
    shotBaseVolumes[id]=volume;SetSoundVolume(i->second,volume*shotChannel(id));PlaySound(i->second);
}
void GameAudio::update(const Profile& profile,const Vehicle& vehicle,const CarState& car,const DriverInput& input,double collision,bool active,bool enabled,bool limiter,bool garageAudition){
    if(!ready)return;
    selectBank(profile.audioSource);
    double now=std::chrono::duration<double>(std::chrono::steady_clock::now().time_since_epoch()).count();
    audioDt=lastUpdate>0?std::clamp(now-lastUpdate,0.0,.1):1.0/60;lastUpdate=now;
    lastEnabled=enabled;
    if(!enabled){
        for(auto& sound:shots)StopSound(sound.second);
        if(IsSoundValid(simulatedStartup))StopSound(simulatedStartup);
        if(IsSoundValid(simulatedShutdown))StopSound(simulatedShutdown);
        starting=false;
    }
    auto samples=engineSamples(profile);bool gas=active&&input.throttle&&(!input.brake||car.burningOut||car.neutral||car.handbraking);
    float audible=enabled&&active?1.f:0.f;
    engineMix.update(car.rpm,gas,audible>0,audioDt,samples.on);
    float pitch=float(engineMix.pitch),load=float(engineMix.load);
    float cut=limiter?float(.3+.7*(.5+.5*std::sin(car.elapsed*62.831853))):car.launching?(std::sin(car.elapsed*62.831853)>0?1.f:.25f):1.f;
    float onVolume=audible*.40f*load*cut,offVolume=audible*.32f*(1-load);
    bool autoOn=profile.soundOn<0,autoOff=profile.soundOff<0;
    int engineId=profile.parts[int(PartSlot::Engine)];
    bool useSimulated=false;
    if(active&&(autoOn||autoOff))useSimulated=loadSimulated(engineId);
    else if(simulatedRequested!=engineId||(!autoOn&&!autoOff)){clearSimulated();simulatedRequested=-1;}
    if(useSimulated){if(autoOn)onVolume=0;if(autoOff)offVolume=0;}
    updateSimulated(car.rpm,load,useSimulated?audible:0,cut,autoOn,autoOff);
    // sfx_engine2e is a byte-identical alias of sfx_engine2 in each source bank.
    auto canonical=[](int id){return id==22?21:id;};
    if(canonical(samples.on)==canonical(samples.off)){onVolume+=offVolume;offVolume=0;}
    loop(on,samples.on,onVolume,pitch);
    loop(off,samples.off,offVolume,pitch);
    double audibleBoost=std::max(car.boostPsi,vehicle.factoryBoostSoundPsi*load*std::clamp(car.rpm/5000.0,0.0,1.0));
    if(garageAudition)audibleBoost=garageInductionAudio(vehicle,car.rpm,load);
    inductionAudioLevel=audible>0?audibleBoost:0;
    float turboVolume=vehicle.turboSoundGain>0?float(vehicle.turboSoundGain*std::clamp(audibleBoost/std::max(1.0,vehicle.boostPsi),0.0,1.0)):float(std::clamp(audibleBoost/35,0.0,.7));
    float turboPitch=vehicle.turboSoundGain>0?float(vehicle.turboSoundPitch*(.7+.6*std::sqrt(std::clamp(audibleBoost/std::max(1.0,vehicle.boostPsi),0.0,1.0)))):float(.65+audibleBoost/30);
    loop(turbo,29,audible*turboVolume*(vehicle.supercharged?0.f:1.f),turboPitch);
    loop(blower,28,audible*float(std::clamp(audibleBoost/50,0.0,.6))*(vehicle.supercharged?1.f:0.f),pitch);
    if(car.nitroActive&&!lastNos&&nos.id>=0)SeekMusicStream(nos.music,0);
    loop(nos,76,audible*(car.nitroActive?.35f:0.f),1);
    loop(town,58,enabled?(active?.025f:.12f):0.f,1);
    if(enabled&&active){
        if(car.launching&&car.elapsed>=nextLaunchPop){shot(43,.12f);nextLaunchPop=car.elapsed+.13;}
        if(car.gear!=lastGear)shot(44,.30f);
        if(((lastGas&&!gas)||car.gear!=lastGear)&&lastBoost>2&&!vehicle.supercharged){
            static constexpr int valves[]={77,0,17,53};int choice=profile.bov<0?(vehicle.turboAutoValve>=0?vehicle.turboAutoValve:vehicle.boostPsi>=30?3:0):std::clamp(profile.bov,0,3);shot(valves[choice],.42f);
        }
        if(collision>lastCollision+.5)shot(1+(crashes++%3),.55f);
        if(car.gear!=lastGear&&profile.parts[int(PartSlot::Exhaust)]!=0)shot(43,.25f);
    }
    lastGear=car.gear;lastGas=gas;lastNos=car.nitroActive;lastBoost=audibleBoost;lastCollision=collision;
}
GameAudio::~GameAudio(){
    if(!ready)return;
    clearSimulated();
    for(auto* stream:{&on,&off,&turbo,&blower,&nos,&town,&music})if(stream->id>=0)UnloadMusicStream(stream->music);
    for(auto& s:shots)UnloadSound(s.second);
    CloseAudioDevice();
}
}
