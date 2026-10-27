#pragma once
#include "model.hpp"
#include "exhaust.hpp"
#include <vector>
namespace pcr {
using SmokeTint=std::array<unsigned char,3>;
SmokeTint tireSmokeTint(int tireFrame);
enum class EffectKind { Smoke, BrakeSmoke, Flame, Nitro, Spark };
struct Particle { EffectKind kind; double x,y,vx,vy,age,life,scale; int outlet=0; double dx=-1,dy=0; SmokeTint tint{255,255,255}; bool foreground=false; };
struct EffectSources { double rearWheel=0,frontWheel=0,wheelY=0; std::array<Outlet,3> outlets{}; int outletCount=1;double scale=1.25;int tireFrame=0; };
class DrivingEffects {
    unsigned random=0x564658;
    double lastPosition=0;
    double smokeTimer=0,nitroTimer=0,flameTimer=0,lastCollision=0;int lastGear=1;
    double sample();
    void add(EffectKind,double x,double y,SmokeTint tint={255,255,255});
public:
    std::vector<Particle> particles;
    void update(const CarState&,const Vehicle&,const DriverInput&,const EffectSources&,double collision,double dt,bool exhaustEquipped);
};
}
