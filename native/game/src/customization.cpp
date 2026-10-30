#include "model.hpp"
#include "art.hpp"
#include "wheelie_bars.hpp"
#include "original_audio.hpp"
#include "engine_assignments.hpp"
#include <algorithm>
#include <cmath>
#include <string>
#include <unordered_map>

namespace pcr {
int audioEngineId(const Profile& profile){
    int selected=profile.parts[int(PartSlot::Engine)];
    if(auto* factory=vehicleForStockEngine(selected))return factory->audioEngineId?factory->audioEngineId:selected;
    return selected?selected:profile.visualVariant?VehicleCatalog[bodyChoiceIndex(profile)].factoryEngineId:nfsFactoryEngine(profile.car,profile.contentSource);
}
EngineSamples engineSamples(const Profile& profile){
    EngineSamples samples;const Part* engine=findPart(audioEngineId(profile));
    // Recovered engine_hp -> e_s/e_s2 -> sample dispatch, checked in both banks.
    // Stock-car selection remains a native fallback. Explicit PC overrides win.
    if(engine&&pcEngine(engine->id)){
        const auto& e=*pcEngine(engine->id);samples.on=e.soundOn;samples.off=e.soundOff;
    }else if(engine){
        int frame=std::clamp(engine->subimage,0,16);
        samples.on=ReplacementEngineSamples[frame][0];
        samples.off=ReplacementEngineSamples[frame][1];
    }
    if(profile.soundOn>=0&&profile.soundOn<16)samples.on=EngineSoundProfiles[profile.soundOn][0];
    if(profile.soundOff>=0&&profile.soundOff<16)samples.off=EngineSoundProfiles[profile.soundOff][1];
    return samples;
}

const Part* findPart(int id){static const auto index=[](){std::unordered_map<int,const Part*> map;for(const auto& p:PartCatalog)map.emplace(p.id,&p);for(const auto& p:FactoryEngineCatalog)map.emplace(p.id,&p);return map;}();auto it=index.find(id);return it==index.end()?nullptr:it->second;}
const char* slotKey(PartSlot slot){
    static const char* keys[]={"engine","suspension","turbo","supercharger","ecu","nos","intake","intercooler","pistons","exhaust","tires","fuel","brakes","clutch","differential","gearbox","battery_cooling","electrical","motor_components","overcharge"};
    int index=int(slot);return index>=0&&index<PartSlotCount?keys[index]:"invalid";
}
const char* slotLabel(PartSlot slot){
    static const char* labels[]={"MOTEURS","SUSPENSIONS","TURBOS","SUPERCHARGERS","ECU","NOS","INTAKES","INTERCOOLERS","PISTONS","EXHAUSTS","TIRES","CARBURANT","FREINS","EMBRAYAGES","DIFFÉRENTIELS","BOÎTES","REFROIDISSEMENT BATTERIE","SYSTÈME ÉLECTRIQUE","MOTEUR ÉLECTRIQUE","SURCHARGE"};
    int index=int(slot);return index>=0&&index<PartSlotCount?labels[index]:"?";
}
bool partCompatibleWithPowertrain(const Profile& profile,PartSlot slot,int id){
    if(!id||slot==PartSlot::Engine)return true;
    auto e=nfsEngine(profile.parts[int(PartSlot::Engine)]);bool electric=e&&e->electric;
    bool electricPart=int(slot)>=int(PartSlot::BatteryCooling);
    if(electricPart)return electric;
    bool thermal=slot==PartSlot::Turbo||slot==PartSlot::Supercharger||slot==PartSlot::Intake||slot==PartSlot::Intercooler||slot==PartSlot::Pistons||slot==PartSlot::Exhaust||slot==PartSlot::Fuel||slot==PartSlot::Nos;
    return !electric||!thermal;
}
bool equipPart(Profile& profile,PartSlot slot,int id){
    int index=int(slot);if(index<0||index>=PartSlotCount)return false;
    const Part* part=findPart(id);
    if(id!=0&&(!part||part->slot!=slot||!partCompatibleWithPowertrain(profile,slot,id)))return false;
    profile.parts[index]=id;
    if(slot==PartSlot::Engine)for(int n=1;n<PartSlotCount;n++)if(!partCompatibleWithPowertrain(profile,PartSlot(n),profile.parts[n]))profile.parts[n]=0;
    if(part&&slot==PartSlot::Gearbox){
        profile.gearCount=std::clamp(int(part->stat),1,10);profile.gearboxPreset=-1;
        double first=profile.gearCount==1?1:profile.gearCount==2?2.1:3.8;
        double last=profile.gearCount<=3?1:.65;
        for(int n=0;n<10;n++)profile.gearRatios[n]=n<profile.gearCount?first*std::pow(last/first,double(n)/std::max(1,profile.gearCount-1)):profile.gearRatios[n-1]*.92;
    }
    if(id&&slot==PartSlot::Turbo)profile.parts[int(PartSlot::Supercharger)]=0;
    if(id&&slot==PartSlot::Supercharger)profile.parts[int(PartSlot::Turbo)]=0;
    return true;
}
static double rideHeight(const Part& part){
    static constexpr double offsets[]={0,.5,1,1.5,2,2,2.5,3,3.5,2,2.5,3,3.5,4,5,6,3};
    return part.subimage>=0&&part.subimage<17?offsets[part.subimage]:0;
}
double partPerformance(const Part& p){
    return p.slot==PartSlot::Suspension?130-p.weight+rideHeight(p):p.slot==PartSlot::Clutch?-p.stat:p.stat;
}
Rarity partRarity(const Part& part){
    int grade=nfsGrade(part.id);if(grade>=0)return Rarity(grade);
    double low=partPerformance(part),high=low;
    for(const auto& p:PartCatalog)if(p.slot==part.slot&&nfsGrade(p.id)<0){low=std::min(low,partPerformance(p));high=std::max(high,partPerformance(p));}
    if(high<=low||partPerformance(part)>=high-1e-9)return Rarity::Contraband;
    return Rarity(std::clamp(int((partPerformance(part)-low)/(high-low)*5),0,4));
}
const char* rarityLabel(Rarity rarity){
    static const char* names[]={"BASIC","SPORT","PRO","SUPER","ELITE","CONTREBANDE"};
    return names[std::clamp(int(rarity),0,5)];
}
bool weakerPart(const Part& a,const Part& b){
    if(partRarity(a)!=partRarity(b))return int(partRarity(a))<int(partRarity(b));
    double pa=partPerformance(a),pb=partPerformance(b);
    if(pa!=pb)return pa<pb;
    if(a.weight!=b.weight)return a.weight>b.weight;
    return a.id>b.id;
}
void equipBestParts(Profile& profile){
    for(int slot=0;slot<PartSlotCount;slot++){
        if(PartSlot(slot)==PartSlot::Supercharger)continue;
        const Part* best=nullptr;
        for(const auto& p:PartCatalog)if(int(p.slot)==slot&&!(p.slot==PartSlot::Engine&&nfsEngine(p.id)&&nfsEngine(p.id)->electric)&&partCompatibleWithPowertrain(profile,p.slot,p.id)&&(!best||partPerformance(*best)<partPerformance(p)))best=&p;
        if(best)equipPart(profile,PartSlot(slot),best->id);
    }
    // Compare complete engine/induction pairs, including airflow-limited assemblies.
    Profile best=profile;double bestHp=buildVehicle(best).boostedHp;
    for(const auto& engine:PartCatalog)if(engine.slot==PartSlot::Engine)
        for(const auto& induction:PartCatalog)if(induction.slot==PartSlot::Turbo||induction.slot==PartSlot::Supercharger){
            Profile alternate=profile;equipPart(alternate,PartSlot::Engine,engine.id);equipPart(alternate,induction.slot,induction.id);
            double hp=buildVehicle(alternate).boostedHp;if(hp>bestHp){best=alternate;bestHp=hp;}
        }
    profile=best;
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
    if(engine)if(auto* factory=vehicleForStockEngine(engine->id))return factory->stock.redlineRpm;
    if(engine)if(const auto* e=pcEngine(engine->id))return e->redlineRpm;
    return engine&&engine->slot==PartSlot::Engine?replacementEngine(engine->subimage).redlineRpm:vehicleMechanics(profile).redlineRpm;
}
Build buildVehicle(const Profile& profile){
    Build build;auto& v=build.vehicle;const auto& stock=vehicleMechanics(profile);
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
    const auto* enginePart=chosen(PartSlot::Engine);
    const auto* pc=enginePart?pcEngine(enginePart->id):nullptr;
    const auto* nfs=enginePart?nfsEngine(enginePart->id):nullptr;
    v.electric=nfs&&nfs->electric;if(v.electric){v.idleRpm=200;v.engineBrakeTorque=8;}
    if(!enginePart)if(auto* factory=pcEngine(nfsFactoryEngine(profile.car,profile.contentSource))){v.factoryBoostSoundPsi=factory->factoryBoostSoundPsi;v.supercharged=factory->blower;}
    if(pc){
        v.torquePeakRpm=pc->torquePeakRpm*8100/pc->redlineRpm;
        v.torqueWidthRpm=pc->torqueWidthRpm*8100/pc->redlineRpm;
        v.lowTorqueFraction=pc->lowTorqueFraction;v.engineInertia=pc->inertia;
        v.factoryBoostSoundPsi=pc->factoryBoostSoundPsi;v.supercharged=pc->blower;
        stockPowerPerTorque=powerPerTorque(v);
    }
    double targetHp=stock.hp,addedHp=0,massDelta=0;
    if(auto* p=chosen(PartSlot::Engine)){targetHp=p->stat;massDelta+=p->weight-250;}
    double nfsProgress=0;
    for(PartSlot slot:{PartSlot::Intake,PartSlot::Pistons,PartSlot::Exhaust,PartSlot::Fuel}){
        if(auto* p=chosen(slot)){
            if(slot==PartSlot::Exhaust)build.exhaustFrame=p->subimage;
            if(auto* upgrade=nfsUpgrade(p->id);upgrade&&nfs){
                double share=slot==PartSlot::Intake?.15:slot==PartSlot::Exhaust?.15:slot==PartSlot::Fuel?.20:0;
                nfsProgress+=share*upgrade->strength;
            }else addedHp+=slot==PartSlot::Fuel?targetHp*.08*p->stat:p->stat;
            double baseline=slot==PartSlot::Intake?10:slot==PartSlot::Pistons?30:slot==PartSlot::Exhaust?80:0;
            massDelta+=p->weight-baseline;
        }
    }
    if(auto* p=chosen(PartSlot::Intercooler))massDelta+=p->weight;
    if(auto* p=chosen(PartSlot::Ecu)){v.twoStep=std::string(p->name).find("2STEP")!=std::string::npos;v.redlineRpm+=p->stat;v.upshiftRpm+=p->stat;massDelta+=p->weight;}
    if(auto* p=chosen(PartSlot::Ecu))if(auto* u=nfsUpgrade(p->id);u&&nfs)nfsProgress+=.20*u->strength;
    const Part* boost=chosen(PartSlot::Turbo);
    if(auto* p=chosen(PartSlot::Supercharger)){boost=p;v.supercharged=true;}
    if(boost){v.factoryBoostSoundPsi=0;v.supercharged=boost->slot==PartSlot::Supercharger;v.boostPsi=boost->stat;massDelta+=boost->weight;
        // Native charge-temperature calibration: intercooling recovers boost efficiency.
        auto* cooler=chosen(PartSlot::Intercooler);
        v.boostEfficiency=.65+.35*(cooler?std::clamp(cooler->stat/107.0,0.0,1.0):0);
        if(const auto* t=pcTurbo(boost->id)){
            v.turboFlowHp=t->capacityHp;v.turboSpoolStartRpm=t->spoolStartRpm;v.turboFullBoostRpm=t->fullBoostRpm;
            v.turboRiseSeconds=t->riseSeconds;v.turboSecondaryStartRpm=t->secondaryStartRpm;
            v.turboSecondaryFullRpm=t->secondaryFullRpm;v.turboFirstShare=t->firstShare;
            v.turboCount=t->count;v.turboSoundPitch=t->soundPitch;v.turboSoundGain=t->soundGain;
            v.turboAutoValve=t->layout==TurboLayout::Hybrid?1:t->layout==TurboLayout::Electric?2:t->count>=2?3:t->psi>=40?2:0;
            double litres=pc?pc->litres:enginePart?replacementEngine(enginePart->subimage).litres:stock.litres;
            double exhaustScale=std::clamp(std::pow(3.0/std::max(.7,litres),.35),.65,1.35);
            v.turboSpoolStartRpm*=exhaustScale;v.turboFullBoostRpm*=exhaustScale;
            v.turboSecondaryStartRpm*=exhaustScale;v.turboSecondaryFullRpm*=exhaustScale;
            v.turboRiseSeconds*=std::clamp(std::pow(3.0/std::max(.7,litres),.25),.7,1.3);
        }
    }
    bool nfsInduction=boost&&nfsUpgrade(boost->id);
    if(nfsInduction){
        auto* u=nfsUpgrade(boost->id);if(u->variant!=0)nfsProgress+=.30*u->strength;
        v.turboCount=u->variant==2?2:1;
        v.turboRiseSeconds=u->variant==2?.24:u->variant>=3?.10:.42;
        v.turboSpoolStartRpm=u->variant==2?1400:2200;v.turboFullBoostRpm=u->variant==2?3600:4700;
        v.turboSoundGain=.35;v.turboSoundPitch=u->variant==2?1.15:1;
        v.turboAutoValve=u->variant==2?3:0;v.superchargerExponent=u->variant==3?2:u->variant>=4?.25:1;
    }
    if(nfs&&nfs->electric){
        for(auto slot:{PartSlot::BatteryCooling,PartSlot::Electrical,PartSlot::MotorComponents})if(auto* p=chosen(slot))nfsProgress+=nfsUpgrade(p->id)->strength/3;
    }
    if(nfs)addedHp+=(nfs->potentialHp-nfs->hp)*std::clamp(nfsProgress,0.0,1.0);
    v.curveRpmScale=v.redlineRpm/8100.0;
    if(auto* p=chosen(PartSlot::Clutch))v.shiftSeconds=std::min(v.shiftSeconds,p->stat);
    if(auto* p=chosen(PartSlot::Overcharge))v.nitroHp=p->stat;
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
        if(auto* u=nfsUpgrade(p->id)){
            const double variants[]={1,1.08,.72,1.04,.90,.60};v.grip*=variants[std::clamp(u->variant,0,5)];
        }
    }
    for(int id:profile.cosmetics)if(const auto* cosmetic=findCosmetic(id))massDelta+=cosmetic->weight;
    // Body/part weights share the source lb scale; use SI kg for integration.
    v.mass=std::max(350.0,v.mass+massDelta*.45359237);
    v.torque=(targetHp+addedHp)*745.699872/stockPowerPerTorque;
    if(nfs){v.torque=1;v.torque=(targetHp+addedHp)/std::max(.0001,peakPower(v,nfsInduction).hp);}
    Profile chassis=profile;sanitizeSuspension(chassis);
    build.rideOffset-=chassis.rideHeightMm*.001*48/1.25;
    v.centreOfGravityHeight=std::clamp(v.centreOfGravityHeight+chassis.rideHeightMm*.001,.25,.80);
    v.springStiffness=chassis.springStiffness;v.dampingRatio=chassis.dampingRatio;
    if(auto* p=chosen(PartSlot::Suspension))if(auto* u=nfsUpgrade(p->id)){
        v.springStiffness*=u->variant==2?1-.2*u->strength:1+.3*u->strength;
        v.dampingRatio+=.1*u->strength;
    }
    v.frontWeightFraction=std::clamp((v.drive==DriveLayout::Front?.60:.48)+chassis.frontBias,.28,.75);
    v.drivenWeightFraction=v.drive==DriveLayout::Front?v.frontWeightFraction:1-v.frontWeightFraction;
    v.wheelieTune=chassis.wheelieTune;v.allowWheelie=chassis.allowWheelie;v.suspensionDynamics=true;v.tyreDynamics=true;v.brakeDeceleration=13;
    if(auto* p=chosen(PartSlot::Brakes))v.brakeDeceleration=p->stat;
    if(auto* p=chosen(PartSlot::Differential))v.grip*=1+.04*p->stat;
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
