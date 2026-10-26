#pragma once
#include "model.hpp"
#include <vector>
namespace pcr {
enum class EffectKind { Smoke, BrakeSmoke, Flame, Nitro, Spark };
struct Particle { EffectKind kind; double x,y,vx,vy,age,life,scale; bool hood=false; };
struct EffectSources { double rearWheel,frontWheel,wheelY,exhaustX,exhaustY; bool hood=false; };
class DrivingEffects {
    unsigned random=0x564658;
    double lastPosition=0;
    double smokeTimer=0,nitroTimer=0,flameTimer=0,lastCollision=0;int lastGear=1;
    double sample();
    void add(EffectKind,double x,double y,bool hood=false);
public:
    std::vector<Particle> particles;
    void update(const CarState&,const Vehicle&,const DriverInput&,const EffectSources&,double collision,double dt,bool exhaustEquipped);
};
}
