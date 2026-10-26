#include "effects.hpp"
#include "road_scene.hpp"
#include <algorithm>
namespace pcr {
double DrivingEffects::sample(){random=1664525u*random+1013904223u;return (random>>8)/16777216.0;}
void DrivingEffects::add(EffectKind kind,double x,double y,bool hood){
    if(particles.size()>=256)return;
    Particle p{kind,x,y,0,0,0,.18,1,hood};
    if(kind==EffectKind::Smoke||kind==EffectKind::BrakeSmoke){p.vx=-20+sample()*40;p.vy=-30-sample()*30;p.life=.6+sample()*.6;p.scale=.5+sample()*.6;}
    if(kind==EffectKind::Spark){p.vx=-80-sample()*180;p.vy=-130+sample()*180;p.life=.15+sample()*.3;}
    if(kind==EffectKind::Nitro)p.life=.10;
    particles.push_back(p);
}
void DrivingEffects::update(const CarState& car,const Vehicle& vehicle,const DriverInput& input,const EffectSources& source,double collision,double dt,bool exhaustEquipped){
    if(dt<=0)return;
    double groundTravel=scene::pixels(car.position-lastPosition);lastPosition=car.position;
    for(auto& p:particles){p.age+=dt;p.x+=p.vx*dt-groundTravel;p.y+=p.vy*dt;if(p.kind==EffectKind::Spark)p.vy+=350*dt;}
    particles.erase(std::remove_if(particles.begin(),particles.end(),[](const Particle& p){return p.age>=p.life||p.x< -120||p.y< -120||p.y>820;}),particles.end());
    smokeTimer-=dt;nitroTimer-=dt;flameTimer-=dt;
    bool slip=input.throttle&&car.wheelSlip>.05;
    bool braking=input.brake&&car.speed>18;
    if((slip||braking)&&smokeTimer<=0){
        if(vehicle.drive!=DriveLayout::Front||braking)add(braking?EffectKind::BrakeSmoke:EffectKind::Smoke,source.rearWheel,source.wheelY);
        if(vehicle.drive!=DriveLayout::Rear||braking)add(braking?EffectKind::BrakeSmoke:EffectKind::Smoke,source.frontWheel,source.wheelY);
        smokeTimer=.045;
    }
    if(car.nitroActive&&nitroTimer<=0){add(EffectKind::Nitro,source.exhaustX,source.exhaustY,source.hood);nitroTimer=.04;}
    if(car.launching&&flameTimer<=0){add(EffectKind::Flame,source.exhaustX,source.exhaustY,source.hood);flameTimer=.10;}
    if(car.gear!=lastGear&&input.throttle&&(exhaustEquipped||car.boostPsi>2))add(EffectKind::Flame,source.exhaustX,source.exhaustY,source.hood);
    if(collision>lastCollision+.5)for(int i=0;i<14;i++)add(EffectKind::Spark,source.frontWheel+35,source.wheelY-10);
    lastCollision=collision;lastGear=car.gear;
}
}
