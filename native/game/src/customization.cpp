#include "model.hpp"
#include "art.hpp"
#include "wheelie_bars.hpp"
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
static double rideHeight(const Part& part){
    static constexpr double offsets[]={0,.5,1,1.5,2,2,2.5,3,3.5,2,2.5,3,3.5,4,5,6,3};
    return part.subimage>=0&&part.subimage<17?offsets[part.subimage]:0;
}
double partPerformance(const Part& p){
    return p.slot==PartSlot::Suspension?130-p.weight+rideHeight(p):p.stat;
}
Rarity partRarity(const Part& part){
    double low=partPerformance(part),high=low;
    for(const auto& p:PartCatalog)if(p.slot==part.slot){low=std::min(low,partPerformance(p));high=std::max(high,partPerformance(p));}
    if(high<=low||partPerformance(part)>=high-1e-9)return Rarity::Contraband;
    return Rarity(std::clamp(int((partPerformance(part)-low)/(high-low)*5),0,4));
}
const char* rarityLabel(Rarity rarity){
    static const char* names[]={"COMMUN","PEU COMMUN","RARE","ÉPIQUE","LÉGENDAIRE","CONTREBANDE"};
    return names[std::clamp(int(rarity),0,5)];
}
bool weakerPart(const Part& a,const Part& b){
    double pa=partPerformance(a),pb=partPerformance(b);
    if(pa!=pb)return pa<pb;
    if(a.weight!=b.weight)return a.weight>b.weight;
    return a.id>b.id;
}
void equipBestParts(Profile& profile){
    for(int slot=0;slot<PartSlotCount;slot++){
        if(PartSlot(slot)==PartSlot::Supercharger)continue;
        const Part* best=nullptr;
        for(const auto& p:PartCatalog)if(int(p.slot)==slot&&(!best||weakerPart(*best,p)))best=&p;
        if(best)equipPart(profile,PartSlot(slot),best->id);
    }
    // Compare the best compressor to the turbo using the actual steady-state power.
    const Part* compressor=nullptr;
    for(const auto& p:PartCatalog)if(p.slot==PartSlot::Supercharger&&(!compressor||weakerPart(*compressor,p)))compressor=&p;
    if(compressor){Profile alternate=profile;equipPart(alternate,PartSlot::Supercharger,compressor->id);
        if(buildVehicle(alternate).boostedHp>buildVehicle(profile).boostedHp)profile=alternate;
    }
}
static double powerPerTorque(const Vehicle& vehicle){return peakPower(vehicle,false).hp*745.699872/vehicle.torque;}
const char* gearboxPresetName(int preset){
    static const char* names[]={"ORIGINE • 6","AUTO 4 • 4L75-E","MANUELLE 5 • TKX","MANUELLE 6 • MAGNUM","DCT 7 • TR-9070","AUTO 8 • 8L90-E","AUTO 6 • 6L80-E","AUTO 10 • 10L90-E"};
    return preset>=0&&preset<8?names[preset]:"PERSONNALISÉE";
}
void applyGearboxPreset(Profile& p,int preset){
    p.gearboxPreset=std::clamp(preset,0,7);p.automatic=true;
    switch(p.gearboxPreset){
    case 1:p.gearCount=4;p.gearRatios={3.06,1.62,1,.70,.63,.56,.49,.42,.35,.30};p.finalDrive=3.73;p.shiftSeconds=.20;break;
    case 2:p.gearCount=5;p.gearRatios={2.87,1.89,1.28,1,.68,.60,.52,.44,.37,.30};p.finalDrive=3.9;p.shiftSeconds=.22;p.automatic=false;break;
    case 3:p.gearCount=6;p.gearRatios={2.66,1.78,1.30,1,.80,.63,.54,.46,.38,.30};p.finalDrive=3.9;p.shiftSeconds=.20;p.automatic=false;break;
    case 4:p.gearCount=7;p.gearRatios={3.14,2.05,1.43,1.10,.86,.68,.56,.46,.38,.30};p.finalDrive=3.73;p.shiftSeconds=.08;break;
    case 5:p.gearCount=8;p.gearRatios={4.56,2.97,2.08,1.69,1.27,1,.85,.65,.54,.43};p.finalDrive=3.15;p.shiftSeconds=.12;break;
    case 6:p.gearCount=6;p.gearRatios={4.02,2.36,1.53,1.15,.85,.67,.56,.47,.38,.30};p.finalDrive=3.73;p.shiftSeconds=.14;break;
    case 7:p.gearCount=10;p.gearRatios={4.70,2.99,2.15,1.80,1.52,1.28,1,.85,.69,.64};p.finalDrive=3.15;p.shiftSeconds=.12;break;
    default:p.gearCount=6;p.gearRatios={3.15,2.10,1.55,1.22,1,.82,.68,.56,.46,.38};p.finalDrive=3.9;p.shiftSeconds=.15;
    }
}
double engineRedline(const Profile& profile){
    const auto* engine=findPart(profile.parts[int(PartSlot::Engine)]);
    return engine&&engine->slot==PartSlot::Engine?replacementEngine(engine->subimage).redlineRpm:stockVehicle(profile.car).redlineRpm;
}
Build buildVehicle(const Profile& profile){
    Build build;auto& v=build.vehicle;const auto& stock=stockVehicle(profile.car);
    v.drive=effectiveDrive(profile);v.mass=stock.weightLb*.45359237;
    v.redlineRpm=engineRedline(profile);v.upshiftRpm=v.redlineRpm-1000;
    v.launchRpm=std::min(2800.0,v.redlineRpm*.4);
    v.curveRpmScale=v.redlineRpm/8100.0;
    // Source grip is a game stat, not a dimensionless SI friction coefficient.
    // Preserve each chassis' relative source grip in the native tyre-force model.
    const double chassisGrip=stock.gripRaw/1200.0;v.grip=1.08*chassisGrip;
    Profile gearbox=profile;sanitizeTransmission(gearbox);v.gearCount=gearbox.gearCount;v.ratios=gearbox.gearRatios;v.finalDrive=gearbox.finalDrive;v.shiftSeconds=gearbox.shiftSeconds;
    v.drivenWeightFraction=v.drive==DriveLayout::Front?.60:.52;
    auto chosen=[&](PartSlot slot){const auto* p=findPart(profile.parts[int(slot)]);return p&&p->slot==slot?p:nullptr;};
    double stockPowerPerTorque=powerPerTorque(v);
    double targetHp=stock.hp,addedHp=0,massDelta=0;
    if(auto* p=chosen(PartSlot::Engine)){targetHp=p->stat;massDelta+=p->weight-250;}
    for(PartSlot slot:{PartSlot::Intake,PartSlot::Pistons,PartSlot::Exhaust}){
        if(auto* p=chosen(slot)){
            if(slot==PartSlot::Exhaust)build.exhaustFrame=p->subimage;
            addedHp+=p->stat;
            double baseline=slot==PartSlot::Intake?10:slot==PartSlot::Pistons?30:slot==PartSlot::Exhaust?80:0;
            massDelta+=p->weight-baseline;
        }
    }
    if(auto* p=chosen(PartSlot::Intercooler))massDelta+=p->weight;
    if(auto* p=chosen(PartSlot::Ecu)){v.twoStep=std::string(p->name).find("2STEP")!=std::string::npos;v.redlineRpm+=p->stat;v.upshiftRpm+=p->stat;massDelta+=p->weight;}
    const Part* boost=chosen(PartSlot::Turbo);
    if(auto* p=chosen(PartSlot::Supercharger)){boost=p;v.supercharged=true;}
    if(boost){v.boostPsi=boost->stat;massDelta+=boost->weight;
        // Native charge-temperature calibration: intercooling recovers boost efficiency.
        auto* cooler=chosen(PartSlot::Intercooler);
        v.boostEfficiency=.65+.35*(cooler?std::clamp(cooler->stat/107.0,0.0,1.0):0);
    }
    v.curveRpmScale=v.redlineRpm/8100.0;
    if(auto* p=chosen(PartSlot::Nos))v.nitroHp=p->stat;
    if(auto* p=chosen(PartSlot::Suspension)){
        build.rideOffset=rideHeight(*p);
        massDelta+=p->weight-130;
        v.centreOfGravityHeight=std::max(.30,v.centreOfGravityHeight-build.rideOffset*.025);
    }
    if(auto* p=chosen(PartSlot::Tires)){
        v.grip=(.8+p->stat*.002)*chassisGrip;
        build.tireFrame=std::clamp(p->subimage,0,int(std::size(art::tires))-1);
        v.wheelRadius*=art::tires[build.tireFrame].w/50.0;
    }
    for(int id:profile.cosmetics)if(const auto* cosmetic=findCosmetic(id))massDelta+=cosmetic->weight;
    // Body/part weights share the source lb scale; use SI kg for integration.
    v.mass=std::max(350.0,v.mass+massDelta*.45359237);
    v.torque=(targetHp+addedHp)*745.699872/stockPowerPerTorque;
    Profile chassis=profile;sanitizeSuspension(chassis);
    build.rideOffset-=chassis.rideHeightMm*.001*48/1.25;
    v.centreOfGravityHeight=std::clamp(v.centreOfGravityHeight+chassis.rideHeightMm*.001,.25,.80);
    v.springStiffness=chassis.springStiffness;v.dampingRatio=chassis.dampingRatio;
    v.frontWeightFraction=std::clamp((v.drive==DriveLayout::Front?.60:.48)+chassis.frontBias,.28,.75);
    v.drivenWeightFraction=v.drive==DriveLayout::Front?v.frontWeightFraction:1-v.frontWeightFraction;
    v.allowWheelie=chassis.allowWheelie;v.suspensionDynamics=true;v.tyreDynamics=true;v.brakeDeceleration=13;
    // The roller belongs to the DRAG PRO rear piece, including the full kit.
    const auto* rear=findCosmetic(profile.cosmetics[6]);const auto* kit=findCosmetic(profile.cosmetics[4]);
    int rearKit=rear?rear->subimage:kit?kit->subimage:0;
    const auto& roller=wheelie_bars::roller(profile.car,profile.contentSource==1);
    if(rearKit==11&&roller.present){
        v.wheelieBar=true;
        // Rear wheel origin is (62,58). Front arch locations are body-specific.
        const auto& wheels=roller;
        double span=std::max(1.0,double(wheels.front-wheels.rear)),ppm=span/v.wheelbase;
        v.wheelieBarArm=(roller.x-wheels.rear)/ppm-v.wheelbase*v.frontWeightFraction;
        v.wheelieBarClearance=std::max(0.0,(wheels.y+wheels.radius-roller.bottom-build.rideOffset)/ppm);
    }
    build.engineHp=targetHp;build.boltOnHp=addedHp;
    build.baseHp=peakPower(v,false).hp;
    auto peak=peakPower(v);build.boostedHp=peak.hp;build.peakRpm=peak.rpm;
    build.nitroHp=build.boostedHp+v.nitroHp;
    return build;
}
}
