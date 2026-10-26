#include "model.hpp"
#include "art.hpp"
#include "original_audio.hpp"
#include <algorithm>
#include <cmath>
#include <string>

namespace pcr {
EngineSamples engineSamples(const Profile& profile){
    EngineSamples samples;const Part* engine=findPart(profile.parts[int(PartSlot::Engine)]);
    // Native family-based automatic assignment; original engine-item -> sound-profile
    // assignments are not established. The two original profile indices can override it.
    if(engine){
        static constexpr int familyOn[]={21,21,23,20,23,23,23,24,47,47,71,47,47,47,47,20,21};
        samples.on=familyOn[std::clamp(engine->subimage,0,16)];
        samples.off=samples.on==21?22:samples.on==20?78:samples.on==71?24:samples.on;
    }
    if(profile.soundOn>=0&&profile.soundOn<16)samples.on=EngineSoundProfiles[profile.soundOn][0];
    if(profile.soundOff>=0&&profile.soundOff<16)samples.off=EngineSoundProfiles[profile.soundOff][1];
    return samples;
}

const Part* findPart(int id){for(const auto& p:PartCatalog)if(p.id==id)return &p;return nullptr;}
const char* slotKey(PartSlot slot){
    static const char* keys[]={"engine","suspension","turbo","supercharger","ecu","nos","intake","intercooler","pistons","exhaust","tires"};
    int index=int(slot);return index>=0&&index<PartSlotCount?keys[index]:"invalid";
}
const char* slotLabel(PartSlot slot){
    static const char* labels[]={"MOTEURS","SUSPENSIONS","TURBOS","SUPERCHARGERS","ECU","NOS","INTAKES","INTERCOOLERS","PISTONS","EXHAUSTS","TIRES"};
    int index=int(slot);return index>=0&&index<PartSlotCount?labels[index]:"?";
}
bool equipPart(Profile& profile,PartSlot slot,int id){
    int index=int(slot);if(index<0||index>=PartSlotCount)return false;
    const Part* part=findPart(id);
    if(id!=0&&(!part||part->slot!=slot))return false;
    profile.parts[index]=id;
    if(id&&slot==PartSlot::Turbo)profile.parts[int(PartSlot::Supercharger)]=0;
    if(id&&slot==PartSlot::Supercharger)profile.parts[int(PartSlot::Turbo)]=0;
    return true;
}
static double powerPerTorque(const Vehicle& vehicle){
    double result=0;
    for(double rpm=vehicle.idleRpm;rpm<=vehicle.redlineRpm;rpm+=10){
        double factor=.62+.38*std::exp(-std::pow((rpm-5200)/2700,2));
        result=std::max(result,factor*rpm*6.283185307179586/60);
    }
    return result;
}
Build buildVehicle(const Profile& profile){
    Build build;auto& v=build.vehicle;v.drive=profile.drive;
    v.drivenWeightFraction=profile.drive==DriveLayout::Front?.60:.52;
    auto chosen=[&](PartSlot slot){const auto* p=findPart(profile.parts[int(slot)]);return p&&p->slot==slot?p:nullptr;};
    double targetHp=v.torque*powerPerTorque(v)/745.699872,addedHp=0,massDelta=0;
    bool powerChanged=false;
    if(auto* p=chosen(PartSlot::Engine)){targetHp=p->stat;massDelta+=p->weight-250;powerChanged=true;}
    for(PartSlot slot:{PartSlot::Intake,PartSlot::Intercooler,PartSlot::Pistons,PartSlot::Exhaust}){
        if(auto* p=chosen(slot)){
            addedHp+=p->stat;powerChanged=true;
            double baseline=slot==PartSlot::Intake?10:slot==PartSlot::Pistons?30:slot==PartSlot::Exhaust?80:0;
            massDelta+=p->weight-baseline;
        }
    }
    if(auto* p=chosen(PartSlot::Ecu)){v.twoStep=std::string(p->name).find("2STEP")!=std::string::npos;v.redlineRpm+=p->stat;v.upshiftRpm+=p->stat;massDelta+=p->weight;}
    const Part* boost=chosen(PartSlot::Turbo);
    if(auto* p=chosen(PartSlot::Supercharger)){boost=p;v.supercharged=true;}
    if(boost){v.boostPsi=boost->stat;massDelta+=boost->weight;}
    if(auto* p=chosen(PartSlot::Nos))v.nitroHp=p->stat;
    if(auto* p=chosen(PartSlot::Suspension)){
        // Native ride-height calibration; the original suspension formulas remain unknown.
        static constexpr double offsets[]={0,.5,1,1.5,2,2,2.5,3,3.5,2,2.5,3,3.5,4,5,6,3};
        if(p->subimage>=0&&p->subimage<17)build.rideOffset=offsets[p->subimage];
        massDelta+=p->weight-130;
        v.centreOfGravityHeight=std::max(.30,v.centreOfGravityHeight-build.rideOffset*.025);
    }
    if(auto* p=chosen(PartSlot::Tires)){
        v.grip=.8+p->stat*.002;
        build.tireFrame=std::clamp(p->subimage,0,int(std::size(art::tires))-1);
        v.wheelRadius*=art::tires[build.tireFrame].w/50.0;
    }
    // Provisional mass calibration. Raw source weights have no verified unit.
    v.mass=std::max(600.0,v.mass+massDelta*.45359237);
    if(powerChanged)v.torque=(targetHp+addedHp)*745.699872/powerPerTorque(v);
    build.baseHp=v.torque*powerPerTorque(v)/745.699872;
    return build;
}
}
