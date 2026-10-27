#pragma once
#include "raylib.h"
#include "model.hpp"
#include "engine_mix.hpp"
#include <filesystem>
#include <map>
#include <algorithm>
namespace pcr {
void checkOriginalAudio(const std::filesystem::path& assets,const std::filesystem::path& output);
class GameAudio {
    struct Loop { Music music{}; int id=-1;std::vector<unsigned char> memory;float gain=0; };
    std::filesystem::path root;
    std::map<int,Sound> shots;
    Loop on,off,turbo,blower,nos,town;
    EngineMix engineMix;double lastUpdate=0,audioDt=1.0/60;
    int bank=0;
    bool lastGas=false,lastNos=false;int lastGear=1,crashes=0;double lastBoost=0,lastCollision=0,nextLaunchPop=0;
    void loop(Loop&,int id,float volume,float pitch);
    void shot(int id,float volume=1);
public:
    bool ready=false;int failures=0;
    void init(const std::filesystem::path&);
    void selectBank(int);
    void update(const Profile&,const Vehicle&,const CarState&,const DriverInput&,double collision,bool active,bool enabled,bool limiter=false);
    void startEngine(const Profile& profile,bool enabled){if(ready&&enabled){selectBank(profile.audioSource);reset();shot(45,.4f);}}
    void stopEngine(){auto start=shots.find(45);if(start!=shots.end())StopSound(start->second);reset();}
    void click(bool enabled){if(ready&&enabled)shot(37,.4f);}
    void install(bool enabled){if(ready&&enabled)shot(40,.5f);}
    void horn(bool enabled){if(ready&&enabled)shot(25,.5f);}
    void valve(int preset,bool enabled){static constexpr int ids[]={77,0,17,53};if(ready&&enabled)shot(ids[std::clamp(preset,0,3)],.4f);}
    void reset(){lastGas=false;lastNos=false;lastGear=1;lastBoost=0;lastCollision=0;nextLaunchPop=0;}
    ~GameAudio();
};
}
