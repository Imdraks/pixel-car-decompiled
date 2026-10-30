#include "model.hpp"
#include "platform.hpp"
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <map>
#include <sstream>
#include <locale>

namespace pcr {
void applySuspensionPreset(Profile& p,SuspensionPreset preset){
    p.rideHeightMm=0;p.springStiffness=1;p.dampingRatio=.65;p.frontBias=0;p.allowWheelie=false;p.wheelieTune=1;
    if(preset==SuspensionPreset::Drag){
        // Native launch setup: control pitch and retain contact, rather than
        // confusing drag preparation with an extreme wheelie demonstration.
        p.rideHeightMm=-10;p.springStiffness=1.35;p.dampingRatio=.9;
        auto layout=effectiveDrive(p);p.frontBias=layout==DriveLayout::Front?.04:layout==DriveLayout::Rear?-.06:0;
    }else if(preset==SuspensionPreset::Track){p.rideHeightMm=-40;p.springStiffness=2;p.dampingRatio=.9;}
    else if(preset==SuspensionPreset::Wheelie){p.rideHeightMm=120;p.springStiffness=.5;p.dampingRatio=.3;p.frontBias=-.15;p.allowWheelie=true;p.wheelieTune=0;}
}
void equipRim(Profile& p,int id,int axle){
    if(!isRimFrame(id))return;
    if(axle==2){p.rearRim=id;return;}
    if(axle==1&&p.rearRim<0)p.rearRim=p.rim;
    p.rim=id;if(axle==0)p.rearRim=-1;
}
int bodyChoiceIndex(const Profile& p){for(size_t i=0;i<std::size(VehicleCatalog);i++)if(VehicleCatalog[i].body==p.car&&VehicleCatalog[i].source==p.contentSource&&VehicleCatalog[i].visualVariant==p.visualVariant)return int(i);for(size_t i=0;i<std::size(VehicleCatalog);i++)if(VehicleCatalog[i].body==p.car&&VehicleCatalog[i].visualVariant==p.visualVariant&&(VehicleCatalog[i].sourceMask&(p.contentSource==2?16:p.contentSource==1?1:2)))return int(i);for(size_t i=0;i<std::size(VehicleCatalog);i++)if(VehicleCatalog[i].body==p.car&&VehicleCatalog[i].visualVariant==0)return int(i);return 0;}
void cycleBody(Profile& p,int direction){int index=(bodyChoiceIndex(p)+direction+int(std::size(VehicleCatalog)))%int(std::size(VehicleCatalog));p.car=VehicleCatalog[index].body;p.contentSource=VehicleCatalog[index].source;p.visualVariant=VehicleCatalog[index].visualVariant;}

bool operator==(const Settings&a,const Settings&b){return a.mode==b.mode&&a.width==b.width&&a.height==b.height&&a.fps==b.fps&&a.vsync==b.vsync&&a.showFps==b.showFps&&a.sound==b.sound&&a.traffic==b.traffic&&a.abs==b.abs&&a.tractionControl==b.tractionControl&&a.quality==b.quality&&a.volumes==b.volumes;}
const char* modeKey(WindowMode mode){switch(mode){case WindowMode::Fullscreen:return "fullscreen";case WindowMode::Borderless:return "borderless";default:return "windowed";}}
Settings validate(Settings s){
    if(s.mode!=WindowMode::Windowed&&s.mode!=WindowMode::Borderless&&s.mode!=WindowMode::Fullscreen)s.mode=WindowMode::Windowed;
    if(s.width<800||s.width>7680||s.height<450||s.height>4320){s.width=1280;s.height=720;}
    if(s.fps!=0&&s.fps!=30&&s.fps!=60&&s.fps!=120&&s.fps!=144&&s.fps!=165&&s.fps!=240)s.fps=120;
    if(s.quality!=Quality::Low&&s.quality!=Quality::Medium&&s.quality!=Quality::High)s.quality=Quality::High;
    s.volumes=validateVolumes(s.volumes);return s;
}
static std::map<std::string,std::string> readIni(const std::filesystem::path& file){
    std::ifstream in(file);std::map<std::string,std::string> values;std::string line;
    while(std::getline(in,line)){
        if(line.size()>4096)continue;
        auto p=line.find('=');if(p==std::string::npos)continue;
        auto key=line.substr(0,p),value=line.substr(p+1);
        if(!value.empty()&&value.back()=='\r')value.pop_back();
        values[key]=value;
    }return values;
}
static int integer(const std::map<std::string,std::string>& v,const std::string& k,int fallback){
    auto i=v.find(k);if(i==v.end())return fallback;
    try{size_t used=0;int n=std::stoi(i->second,&used);return used==i->second.size()?n:fallback;}catch(...){return fallback;}
}
static double real(const std::map<std::string,std::string>& v,const std::string& key,double fallback){
    auto it=v.find(key);if(it==v.end())return fallback;
    try{size_t used=0;double value=std::stod(it->second,&used);return used==it->second.size()&&std::isfinite(value)?value:fallback;}catch(...){return fallback;}
}
void sanitizeTransmission(Profile& p){
    p.gearCount=std::clamp(p.gearCount,1,10);
    if(p.gearboxPreset< -1||p.gearboxPreset>7)p.gearboxPreset=0;
    if(!std::isfinite(p.finalDrive)||p.finalDrive<2||p.finalDrive>6)p.finalDrive=3.9;
    if(!std::isfinite(p.shiftSeconds)||p.shiftSeconds<.04||p.shiftSeconds>.5)p.shiftSeconds=.15;
    bool valid=true;double previous=7;
    for(double ratio:p.gearRatios){valid&=std::isfinite(ratio)&&ratio>=.3&&ratio<=6&&previous-ratio>=.05-1e-9;previous=ratio;}
    if(!valid)p.gearRatios={3.15,2.10,1.55,1.22,1.0,.82,.68,.56,.46,.38};
}
void sanitizeSuspension(Profile& p){
    auto bounded=[](double& x,double lo,double hi,double fallback){x=std::isfinite(x)?std::clamp(x,lo,hi):fallback;};
    bounded(p.rideHeightMm,-60,120,0);bounded(p.springStiffness,.4,3,1);
    bounded(p.wheelieTune,0,1,1);p.allowWheelie=p.wheelieTune<1;bounded(p.dampingRatio,.25,1.5,.65);bounded(p.frontBias,-.15,.15,0);
}
Settings loadSettings(const std::filesystem::path& file){
    auto v=readIni(file);Settings s;
    if(v["mode"]=="fullscreen")s.mode=WindowMode::Fullscreen;
    if(v["mode"]=="borderless")s.mode=WindowMode::Borderless;
    s.width=integer(v,"width",s.width);s.height=integer(v,"height",s.height);s.fps=integer(v,"fps",s.fps);
    s.quality=Quality(integer(v,"quality",int(s.quality)));
    s.vsync=integer(v,"vsync",s.vsync)!=0;s.showFps=integer(v,"show_fps",s.showFps)!=0;s.sound=integer(v,"sound",s.sound)!=0;
    s.traffic=integer(v,"traffic",1)!=0;s.abs=integer(v,"abs",1)!=0;s.tractionControl=integer(v,"traction_control",1)!=0;
    s.volumes.master=real(v,"volume_master",1);s.volumes.engine=real(v,"volume_engine",1);s.volumes.turbo=real(v,"volume_turbo",1);
    s.volumes.effects=real(v,"volume_effects",1);s.volumes.ambience=real(v,"volume_ambience",1);s.volumes.interface=real(v,"volume_interface",1);s.volumes.music=real(v,"volume_music",1);
    return validate(s);
}
Profile loadProfile(const std::filesystem::path& file,int cars,int rims){
    auto v=readIni(file);Profile p;p.savedName=v["saved_name"].substr(0,48);
    (void)rims;p.rollCage=integer(v,"roll_cage",0)!=0;p.headlights=integer(v,"headlights",0)!=0;p.contentSource=std::clamp(integer(v,"content_source",0),0,2);p.audioSource=std::clamp(integer(v,"audio_source",p.contentSource),0,2);
    for(int slot=0;slot<CosmeticSlotCount;slot++){int id=integer(v,"cosmetic_"+std::to_string(slot),0);auto item=findCosmetic(id);if(item&&item->slot==slot)p.cosmetics[slot]=id;}
    p.car=std::clamp(integer(v,"car",0),0,std::max(0,cars-1));
    p.visualVariant=integer(v,"visual_variant",0);
    if(!std::any_of(std::begin(VehicleCatalog),std::end(VehicleCatalog),[&](const auto& entry){return entry.body==p.car&&entry.source==p.contentSource&&entry.visualVariant==p.visualVariant;}))p.visualVariant=0;
    p.rim=validRimFrame(integer(v,"rim",8));p.rearRim=integer(v,"rear_rim",-1);if(p.rearRim!=-1&&!isRimFrame(p.rearRim))p.rearRim=-1;p.automatic=integer(v,"automatic",1)!=0;
    p.factoryDrive=integer(v,"factory_drive",v.count("drive")?0:1)!=0;
    int layout=integer(v,"drive",1);p.drive=layout>=0&&layout<=2?DriveLayout(layout):DriveLayout::Rear;
    p.soundOn=integer(v,"sound_on",-1);if(p.soundOn< -1||p.soundOn>15)p.soundOn=-1;
    p.soundOff=integer(v,"sound_off",-1);if(p.soundOff< -1||p.soundOff>15)p.soundOff=-1;
    p.bov=integer(v,"bov",-1);if(p.bov< -1||p.bov>3)p.bov=-1;
    for(int slot=0;slot<PartSlotCount;slot++)equipPart(p,PartSlot(slot),integer(v,std::string("part_")+slotKey(PartSlot(slot)),0));
    if(integer(v,"version",1)<2&&p.contentSource==1){if(p.cosmetics[9])p.cosmetics[9]+=200000;if(p.parts[9]==9030||p.parts[9]==9031)p.parts[9]+=200000;}
    for(auto& id:p.parts){id=canonicalPartId(id);}
    for(auto& id:p.cosmetics){id=canonicalCosmeticId(id);}
    p.rim=canonicalRimId(p.rim);if(p.rearRim>=0)p.rearRim=canonicalRimId(p.rearRim);
    try {size_t used=0;p.bestTime=std::stod(v["best_time"],&used);if(used!=v["best_time"].size()||!std::isfinite(p.bestTime)||p.bestTime<0||p.bestTime>120)p.bestTime=0;}catch(...){p.bestTime=0;}
    p.gearboxPreset=integer(v,"gearbox_preset",0);
    p.gearCount=integer(v,"gear_count",6);p.finalDrive=real(v,"final_drive",3.9);p.shiftSeconds=real(v,"shift_seconds",.15);
    for(int i=0;i<10;i++)p.gearRatios[i]=real(v,"gear_"+std::to_string(i+1),p.gearRatios[i]);
    p.rideHeightMm=real(v,"ride_height_mm",0);p.springStiffness=real(v,"spring_stiffness",1);
    p.dampingRatio=real(v,"damping_ratio",.65);p.frontBias=real(v,"front_bias",0);p.allowWheelie=integer(v,"allow_wheelie",0)!=0;
    p.wheelieTune=real(v,"wheelie_tune",p.allowWheelie?0:1);
    p.factoryInitialized=integer(v,"factory_initialized",0)!=0;p.factoryEngineId=integer(v,"factory_engine_id",0);
    sanitizeTransmission(p);sanitizeSuspension(p);
    return p;
}
static bool writeAtomic(const std::filesystem::path& file,const std::string& text,std::string& error){
    std::error_code ec;std::filesystem::create_directories(file.parent_path(),ec);
    if(ec){error=ec.message();return false;}
    auto temp=file;temp+=".tmp";
    {std::ofstream out(temp,std::ios::binary|std::ios::trunc);if(!out){error="Impossible d'ouvrir le fichier de réglages.";return false;}out<<text;out.flush();if(!out){error="Écriture des réglages interrompue.";return false;}}
    return atomicReplace(temp,file,error);
}
bool saveSettings(const std::filesystem::path& file,const Settings& settings,std::string& error){
    auto s=validate(settings);std::ostringstream out;out.imbue(std::locale::classic());
    out<<"version=1\nmode="<<modeKey(s.mode)<<"\nwidth="<<s.width<<"\nheight="<<s.height<<"\nfps="<<s.fps<<"\nvsync="<<s.vsync<<"\nquality="<<int(s.quality)<<"\nshow_fps="<<s.showFps<<"\nsound="<<s.sound<<"\ntraffic="<<s.traffic<<"\n";
    out<<"abs="<<s.abs<<"\ntraction_control="<<s.tractionControl<<'\n';
    out<<std::setprecision(17)<<"volume_master="<<s.volumes.master<<"\nvolume_engine="<<s.volumes.engine<<"\nvolume_turbo="<<s.volumes.turbo<<"\nvolume_effects="<<s.volumes.effects<<"\nvolume_ambience="<<s.volumes.ambience<<"\nvolume_interface="<<s.volumes.interface<<"\nvolume_music="<<s.volumes.music<<'\n';
    return writeAtomic(file,out.str(),error);
}
bool saveProfile(const std::filesystem::path& file,const Profile& raw,std::string& error){
    Profile p=raw;sanitizeTransmission(p);sanitizeSuspension(p);
    std::ostringstream out;out.imbue(std::locale::classic());
    std::string name=p.savedName.substr(0,48);name.erase(std::remove_if(name.begin(),name.end(),[](unsigned char c){return c<32||c==127;}),name.end());
    out<<"saved_name="<<name<<'\n';
    out<<"vehicle_id="<<VehicleCatalog[bodyChoiceIndex(p)].id<<"\nfactory_initialized="<<p.factoryInitialized<<"\nfactory_engine_id="<<p.factoryEngineId<<'\n';
    out<<"version=9\ncar="<<p.car<<"\nvisual_variant="<<p.visualVariant<<"\nrim="<<p.rim<<"\nautomatic="<<p.automatic<<"\ndrive="<<int(p.drive)<<"\nbest_time="<<std::setprecision(12)<<p.bestTime<<"\n";
    out<<"ride_height_mm="<<p.rideHeightMm<<"\nspring_stiffness="<<p.springStiffness<<"\ndamping_ratio="<<p.dampingRatio<<"\nfront_bias="<<p.frontBias<<"\nallow_wheelie="<<p.allowWheelie<<'\n';
    out<<"wheelie_tune="<<p.wheelieTune<<'\n';
    out<<"rear_rim="<<p.rearRim<<'\n';
    out<<"factory_drive="<<p.factoryDrive<<'\n';
    out<<"audio_source="<<p.audioSource<<'\n';
    out<<"roll_cage="<<p.rollCage<<"\nheadlights="<<p.headlights<<'\n';
    out<<"content_source="<<p.contentSource<<'\n';
    for(int slot=0;slot<CosmeticSlotCount;slot++)out<<"cosmetic_"<<slot<<'='<<p.cosmetics[slot]<<'\n';
    out<<"sound_on="<<p.soundOn<<"\nsound_off="<<p.soundOff<<"\nbov="<<p.bov<<'\n';
    out<<"gearbox_preset="<<p.gearboxPreset<<'\n';
    out<<"gear_count="<<p.gearCount<<"\nfinal_drive="<<p.finalDrive<<"\nshift_seconds="<<p.shiftSeconds<<'\n';
    for(int i=0;i<10;i++)out<<"gear_"<<i+1<<'='<<p.gearRatios[i]<<'\n';
    for(int slot=0;slot<PartSlotCount;slot++)out<<"part_"<<slotKey(PartSlot(slot))<<'='<<p.parts[slot]<<'\n';
    return writeAtomic(file,out.str(),error);
}
// Numeric path derived from Unbound ease_linear disassembly, not generic YYRValue semantics.
double easeLinear(double t,double b,double c,double d){return (c*t)/d+b;}
double torqueCurve(const Vehicle& v,double rpm){
    if(v.electric)return std::min(1.0,v.redlineRpm*.35/std::max(1.0,rpm));
    return v.lowTorqueFraction+(1-v.lowTorqueFraction)*std::exp(-std::pow((rpm/v.curveRpmScale-v.torquePeakRpm)/v.torqueWidthRpm,2));
}
double targetBoost(const Vehicle& v,double rpm){
    if(v.supercharged)return v.boostPsi*std::pow(std::clamp(rpm/v.redlineRpm,0.0,1.0),v.superchargerExponent);
    double primary=std::clamp((rpm-v.turboSpoolStartRpm)/(v.turboFullBoostRpm-v.turboSpoolStartRpm),0.0,1.0);
    double secondary=v.turboSecondaryFullRpm>v.turboSecondaryStartRpm
        ?std::clamp((rpm-v.turboSecondaryStartRpm)/(v.turboSecondaryFullRpm-v.turboSecondaryStartRpm),0.0,1.0):primary;
    return v.boostPsi*(v.turboFirstShare*primary+(1-v.turboFirstShare)*secondary);
}
double engineTorque(const Vehicle& v,double rpm,double boost){
    boost=std::clamp(boost,0.0,v.boostPsi);
    double torque=v.torque*torqueCurve(v,rpm)*(1+boost/14.7*v.boostEfficiency);
    if(v.turboFlowHp>0&&boost>0&&rpm>0){
        double base=v.torque*torqueCurve(v,rpm);
        double cap=std::max(base,v.turboFlowHp*745.699872/(rpm*6.283185307179586/60));
        torque=std::min(torque,cap);
    }
    return v.supercharged&&boost>0?torque*.94:torque;
}
double enginePowerHp(const Vehicle& v,double rpm,double boost,bool nitro){
    return engineTorque(v,rpm,boost)*rpm*6.283185307179586/60/745.699872+(nitro?v.nitroHp:0);
}
PowerPeak peakPower(const Vehicle& v,bool boost,bool nitro){
    PowerPeak result;
    for(double rpm=v.idleRpm;rpm<v.redlineRpm;rpm+=10){
        double hp=enginePowerHp(v,rpm,boost?targetBoost(v,rpm):0,nitro);
        if(hp>result.hp)result={hp,rpm};
    }
    return result;
}
static double wheelRpm(const CarState& car,const Vehicle& vehicle,int gear){
    return car.speed*60/(2*3.141592653589793*vehicle.wheelRadius)*vehicle.ratios[std::clamp(gear,1,vehicle.gearCount)-1]*vehicle.finalDrive;
}
static double drivenGrip(const Vehicle& vehicle,bool accelerating){
    if(vehicle.drive==DriveLayout::All)return vehicle.mass*9.81*vehicle.grip;
    // Quasi-static load transfer, solved for the limiting tyre force.
    // Rear axle gains normal load under acceleration; front axle gains it under braking.
    double transfer=vehicle.grip*vehicle.centreOfGravityHeight/vehicle.wheelbase;
    double sign=vehicle.drive==DriveLayout::Rear?1.0:-1.0;
    if(!accelerating)sign=-sign;
    double denominator=std::max(.1,1-sign*transfer);
    return std::min(vehicle.mass*9.81*vehicle.grip,
        vehicle.mass*9.81*vehicle.grip*vehicle.drivenWeightFraction/denominator);
}
static void suspensionLoads(CarState& s,const Vehicle& v){
    const double omega=2*3.141592653589793*1.6*std::sqrt(v.springStiffness);
    const double a=v.wheelbase*(1-v.frontWeightFraction),b=v.wheelbase*v.frontWeightFraction;
    const double kf=v.mass*v.frontWeightFraction*omega*omega,kr=v.mass*(1-v.frontWeightFraction)*omega*omega;
    const double cf=2*v.dampingRatio*v.mass*v.frontWeightFraction*omega,cr=2*v.dampingRatio*v.mass*(1-v.frontWeightFraction)*omega;
    const double front=s.heave+a*s.pitch,rear=s.heave-b*s.pitch,droop=v.suspensionDroop;
    s.frontLift=v.allowWheelie?std::max(0.0,front-droop):0;
    s.rearLift=v.allowWheelie?std::max(0.0,rear-droop):0;
    s.frontLoad=s.frontLift>0?0:std::clamp(v.mass*9.81*v.frontWeightFraction-kf*front-cf*(s.heaveRate+a*s.pitchRate),0.0,3*v.mass*9.81);
    s.rearLoad=s.rearLift>0?0:std::clamp(v.mass*9.81*(1-v.frontWeightFraction)-kr*rear-cr*(s.heaveRate-b*s.pitchRate),0.0,3*v.mass*9.81);
}
static void updateSuspension(CarState& s,const Vehicle& v,double tyreForce,double dt){
    if(!v.suspensionDynamics)return;
    const double a=v.wheelbase*(1-v.frontWeightFraction),b=v.wheelbase*v.frontWeightFraction,inertia=v.mass*v.wheelbase*v.wheelbase*.26;
    s.heaveRate+=(s.frontLoad+s.rearLoad-v.mass*9.81)/v.mass*dt;
    s.pitchRate+=(s.frontLoad*a-s.rearLoad*b+tyreForce*v.centreOfGravityHeight)/inertia*dt;
    s.heave+=s.heaveRate*dt;s.pitch+=s.pitchRate*dt;
    if(!v.allowWheelie||v.wheelieTune>0){
        // An anti-lift constraint represents the grounded setup/wheelie stop.
        // Project position and outgoing velocity, rather than adding tyre grip.
        double droop=.85*v.suspensionDroop+(v.allowWheelie?(1-v.wheelieTune)*.35:0);
        for(double arm:{a,-b}){
            double excess=s.heave+arm*s.pitch-droop;
            if(excess>0){double inverse=1/v.mass+arm*arm/inertia,impulse=excess/inverse;
                s.heave-=impulse/v.mass;s.pitch-=impulse*arm/inertia;
                double velocity=s.heaveRate+arm*s.pitchRate;
                if(velocity>0){impulse=velocity/inverse;s.heaveRate-=impulse/v.mass;s.pitchRate-=impulse*arm/inertia;}
            }
        }
    }
    // Shock travel is mechanical, independent of static spring compression.
    // Rear squat cannot move an axle arbitrarily far through its wheel arch.
    for(double arm:{a,-b}){
        double compression=s.heave+arm*s.pitch+v.suspensionBump;
        if(compression<0){double inverse=1/v.mass+arm*arm/inertia,correction=-compression/inverse;
            s.heave+=correction/v.mass;s.pitch+=correction*arm/inertia;
            double velocity=s.heaveRate+arm*s.pitchRate;
            if(velocity<0){double impulse=-velocity/inverse;s.heaveRate+=impulse/v.mass;s.pitchRate+=impulse*arm/inertia;}
        }
    }
    s.wheelieBarContact=false;
    if(v.wheelieBar){
        // Unilateral rear roller support. A downward-moving bar cannot penetrate
        // the road: its reaction raises the CG and opposes nose-up rotation.
        double arm=v.wheelieBarArm,gap=v.wheelieBarClearance+s.heave+arm*s.pitch;
        if(gap<0){
            double inverse=1/v.mass+arm*arm/inertia,correction=-gap/inverse;
            s.heave+=correction/v.mass;s.pitch+=correction*arm/inertia;
            double velocity=s.heaveRate+arm*s.pitchRate;
            if(velocity<0){double impulse=-velocity/inverse;s.heaveRate+=impulse/v.mass;s.pitchRate+=impulse*arm/inertia;}
            s.wheelieBarContact=true;s.wheelieBarTouched=true;
        }
    }
    // Native travel/angle stops prevent an uncontrolled flip, not unlimited rotation.
    if(s.pitch>.55){s.pitch=.55;s.pitchRate=std::min(0.0,s.pitchRate);}
    if(s.pitch<-.15){s.pitch=-.15;s.pitchRate=std::max(0.0,s.pitchRate);}
    if(s.heave>.4){s.heave=.4;s.heaveRate=std::min(0.0,s.heaveRate);}
    if(s.heave<-.18){s.heave=-.18;s.heaveRate=std::max(0.0,s.heaveRate);}
    suspensionLoads(s,v);s.peakFrontLift=std::max(s.peakFrontLift,s.frontLift);
}
bool shift(CarState& car,int direction,const Vehicle& vehicle){
    if(car.shiftLock>0||car.finished||car.neutral||car.handbraking||direction==0)return false;
    int next=std::clamp(car.gear+(direction>0?1:-1),1,vehicle.gearCount);
    // Reject an unsafe downshift instead of allowing mechanically impossible RPM.
    if(next==car.gear||(next<car.gear&&wheelRpm(car,vehicle,next)>vehicle.redlineRpm))return false;
    car.launchClutch=false;car.launchWheelOmega=-1;
    car.gear=next;car.shiftLock=vehicle.shiftSeconds;
    return true;
}
void stepCar(CarState& s,const Vehicle& v,const DriverInput& input,double dt,double finishDistance){
    if(s.finished||dt<=0||!std::isfinite(dt))return;
    if(v.suspensionDynamics&&!s.suspensionReady){s.suspensionReady=true;suspensionLoads(s,v);}
    s.tcActive=false;s.absActive=false;s.frontLocked=false;s.rearLocked=input.handbrake;s.brakeSlip=0;s.frontBrakeSlip=0;s.rearBrakeSlip=0;
    s.gear=std::clamp(s.gear,1,v.gearCount);
    s.shiftLock=std::max(0.0,s.shiftLock-dt);
    bool wasDisconnected=s.neutral||s.handbraking,wasBurnout=s.burningOut;
    bool braking=input.brake||input.handbrake;s.handbraking=input.handbrake;
    s.neutral=input.neutral;bool freeRev=s.neutral||s.handbraking;
    if(wasDisconnected&&!freeRev){
        // Reconnect safely even if the retained gear would over-rev the engine.
        while(s.gear<v.gearCount&&wheelRpm(s,v,s.gear)>v.redlineRpm)++s.gear;
        s.shiftLock=std::max(s.shiftLock,v.shiftSeconds);
        s.launchClutch=v.tyreDynamics&&!v.tractionControl&&input.throttle&&!braking&&s.speed<8&&s.rpm>v.launchRpm*1.1;
        s.launchWheelOmega=-1;
    }
    if(freeRev||braking||!input.throttle||v.tractionControl){s.launchClutch=false;s.launchWheelOmega=-1;}
    s.burningOut=!s.neutral&&!input.handbrake&&input.brake&&input.throttle&&s.gear==1&&s.speed<3&&s.shiftLock==0;
    if(wasBurnout&&!s.burningOut&&!freeRev&&!braking&&input.throttle&&v.tyreDynamics&&!v.tractionControl){s.launchClutch=true;s.launchWheelOmega=-1;}
    s.launching=!s.neutral&&v.twoStep&&input.launch&&input.throttle&&!braking&&s.speed<3;
    double coupled=wheelRpm(s,v,s.gear);
    if(input.automatic&&!freeRev&&!s.burningOut&&s.shiftLock==0){
        if(input.throttle&&!braking&&coupled>v.upshiftRpm&&s.gear<v.gearCount)shift(s,1,v);
        else if(s.gear>1&&coupled<(input.throttle&&!braking?2600.0:1500.0)
                &&wheelRpm(s,v,s.gear-1)<v.upshiftRpm*.9)shift(s,-1,v);
        coupled=wheelRpm(s,v,s.gear);
    }
    double ratio=v.ratios[s.gear-1]*v.finalDrive;
    bool launchStep=s.launchClutch&&s.shiftLock==0&&!s.launching;
    if(launchStep&&s.launchWheelOmega<0){
        // Couple a freely revving engine to the driven-wheel inertia. Angular
        // momentum is conserved; clutch engagement dissipates, never adds, energy.
        double engineOmega=s.rpm*2*3.141592653589793/60,roadOmega=s.speed/v.wheelRadius;
        s.launchWheelOmega=(v.engineInertia*ratio*engineOmega+v.drivenWheelInertia*roadOmega)/(v.engineInertia*ratio*ratio+v.drivenWheelInertia);
    }
    // Simplified slipping clutch below launch RPM. Above it, RPM follows wheel speed.
    double target=s.launching?4200:std::max(input.throttle&&!braking?v.launchRpm:v.idleRpm,coupled);
    if(freeRev||s.burningOut){
        target=input.throttle?v.redlineRpm*(s.burningOut?.90:.96):v.idleRpm;
        s.rpm+=std::clamp(target-s.rpm,-6500*dt,9000*dt);
    }else if(launchStep)s.rpm=std::clamp(s.launchWheelOmega*ratio*60/(2*3.141592653589793),v.idleRpm,v.redlineRpm);
    else if(s.launchClutch&&s.shiftLock>0)s.rpm=std::min(s.rpm,v.redlineRpm*.96);
    else if(s.shiftLock>0)s.rpm+=std::clamp(target-s.rpm,-13000*dt,15000*dt);
    else s.rpm=target;
    double boostTarget=!s.neutral&&input.throttle&&(!braking||s.launching||s.burningOut)&&s.shiftLock==0
        ?targetBoost(v,s.rpm):0;
    double boostRate=v.boostPsi*(boostTarget>s.boostPsi?(v.supercharged?10:1/v.turboRiseSeconds):8);
    s.boostPsi+=std::clamp(boostTarget-s.boostPsi,-boostRate*dt,boostRate*dt);
    double torque=engineTorque(v,s.rpm,s.boostPsi);
    s.nitroActive=!s.neutral&&!s.burningOut&&input.nitro&&input.throttle&&!braking&&s.shiftLock==0&&!s.launching&&s.speed>2&&coupled<v.redlineRpm&&(!launchStep||s.rpm<v.redlineRpm*.995)&&v.nitroHp>0&&s.nitroRemaining>0;
    double nitroFraction=s.nitroActive?std::min(1.0,s.nitroRemaining/dt):0;
    if(s.nitroActive)s.nitroRemaining=std::max(0.0,s.nitroRemaining-dt);
    bool delivering=!s.neutral&&input.throttle&&!braking&&!s.launching&&s.shiftLock==0&&coupled<v.redlineRpm;
    s.powerHp=(delivering||s.burningOut)?enginePowerHp(v,s.rpm,s.boostPsi,false)+nitroFraction*v.nitroHp:0;
    double tractionLimit=v.suspensionDynamics?v.grip*(v.drive==DriveLayout::Front?s.frontLoad:v.drive==DriveLayout::Rear?s.rearLoad:s.frontLoad+s.rearLoad):drivenGrip(v,true);
    double lateralUse=v.tyreDynamics?std::clamp(std::abs(s.lateralAcceleration)/std::max(.1,v.grip*9.81),0.0,1.0):0;
    double longitudinalGrip=std::sqrt(std::max(0.0,1-lateralUse*lateralUse));
    tractionLimit*=longitudinalGrip;
    double wheelForce=!s.neutral&&input.throttle&&!braking&&!s.launching&&s.shiftLock==0&&coupled<v.redlineRpm
        ?torque*ratio*v.efficiency/v.wheelRadius:0;
    wheelForce+=nitroFraction*v.nitroHp*745.699872*v.efficiency/std::max(10.0,launchStep?s.launchWheelOmega*v.wheelRadius:s.speed);
    if(v.tyreDynamics&&!v.tractionControl&&delivering&&!launchStep&&wheelForce>tractionLimit*1.02){
        // Wheelspin can start in any gear, not just after releasing neutral.
        // Match clutch angular momentum instead of inventing wheel travel from
        // demanded torque while leaving engine RPM tied to road speed.
        double engineOmega=s.rpm*2*3.141592653589793/60,roadOmega=s.speed/v.wheelRadius;
        s.launchClutch=true;launchStep=true;
        s.launchWheelOmega=(v.engineInertia*ratio*engineOmega+v.drivenWheelInertia*roadOmega)/(v.engineInertia*ratio*ratio+v.drivenWheelInertia);
    }
    if(launchStep&&s.rpm>=v.redlineRpm*.995){wheelForce=0;s.powerHp=0;}
    if(v.tyreDynamics&&v.tractionControl&&delivering){
        double factor=std::min(1.0,.98*tractionLimit/std::max(1.0,wheelForce));
        // Fast torque cut, progressive reapplication. Delaying a known adhesion
        // limit produced fictitious spin while wheel RPM remained road-coupled.
        s.tractionFactor=std::min(factor,s.tractionFactor+2*dt);
        s.tcActive=s.tractionFactor<.98;
        wheelForce*=s.tractionFactor;s.powerHp*=s.tractionFactor;
    }else s.tractionFactor=1;
    double driveDemand=wheelForce;
    if(!freeRev&&!s.burningOut&&(!input.throttle||braking)&&s.shiftLock==0){
        // Engine and service braking share the same tyre contact patch.
        wheelForce-=v.engineBrakeTorque*ratio/v.wheelRadius*std::clamp(coupled/v.idleRpm,0.0,1.0);
    }
    if(input.brake)wheelForce-=v.mass*v.brakeDeceleration;
    double rearFraction=v.drive==DriveLayout::Front?1-v.drivenWeightFraction:v.drivenWeightFraction;
    double handbrakeLimit=v.suspensionDynamics?v.grip*s.rearLoad:v.mass*9.81*v.grip*rearFraction/(1+v.grip*v.centreOfGravityHeight/v.wheelbase);
    handbrakeLimit*=longitudinalGrip;
    if(input.handbrake&&!input.brake)wheelForce-=handbrakeLimit;
    double totalGrip=(v.suspensionDynamics?v.grip*(s.frontLoad+s.rearLoad):v.mass*9.81*v.grip)*longitudinalGrip;
    double overrunGrip=v.tyreDynamics&&v.suspensionDynamics
        ?v.grip*(v.drive==DriveLayout::Front?s.frontLoad:v.drive==DriveLayout::Rear?s.rearLoad:s.frontLoad+s.rearLoad)*longitudinalGrip
        :drivenGrip(v,false)*longitudinalGrip;
    double brakingLimit=input.brake?totalGrip:input.handbrake?handbrakeLimit:overrunGrip;
    s.wheelSlip=std::clamp((driveDemand-tractionLimit)/std::max(1.0,tractionLimit),0.0,2.0);
    if(launchStep)s.wheelSlip=std::clamp((s.launchWheelOmega*v.wheelRadius-s.speed)/std::max(2.0,s.speed),0.0,2.0);
    if(v.tyreDynamics){
        if(input.brake&&!s.burningOut){
            double frontGrip=(v.suspensionDynamics?s.frontLoad:v.mass*9.81*v.frontWeightFraction)*v.grip*longitudinalGrip;
            double rearGrip=(v.suspensionDynamics?s.rearLoad:v.mass*9.81*(1-v.frontWeightFraction))*v.grip*longitudinalGrip;
            double service=v.mass*v.brakeDeceleration,engine=std::max(0.0,-wheelForce-service);
            double engineFront=v.drive==DriveLayout::Front?1:v.drive==DriveLayout::Rear?0:v.frontWeightFraction;
            auto axleBrake=[&](double demand,double grip,bool rear){
                bool locked=rear&&input.handbrake;
                double slip=0,force=std::min(demand,grip);
                if(locked){slip=1;force=grip*.72;}
                else if(demand>grip&&s.speed>1){
                    if(v.abs){s.absActive=true;slip=.12;force=grip*.96;}
                    else{locked=true;slip=1;force=grip*.72;}
                }
                if(rear){s.rearLocked=locked;s.rearBrakeSlip=slip;}else{s.frontLocked=locked;s.frontBrakeSlip=slip;}
                return force;
            };
            // Fixed native road-car hydraulic bias; actual axle loads decide
            // which tyres lock first. ABS regulates each axle independently.
            wheelForce=-axleBrake(service*.68+engine*engineFront,frontGrip,false)
                       -axleBrake(service*.32+engine*(1-engineFront),rearGrip,true);
            s.brakeSlip=std::max(s.frontBrakeSlip,s.rearBrakeSlip);
        }
        if(delivering&&!v.tractionControl&&s.wheelSlip>.03)tractionLimit*=.78+.22/(1+4*s.wheelSlip*s.wheelSlip);
    }
    if(s.burningOut)s.wheelSlip=2*std::clamp((s.rpm-v.idleRpm)/(v.redlineRpm-v.idleRpm),0.0,1.0);
    double force=std::clamp(wheelForce,-brakingLimit,tractionLimit);
    double launchTravel=-1;
    if(launchStep){
        double inertia=v.drivenWheelInertia+v.engineInertia*ratio*ratio;
        double stiffness=tractionLimit*v.wheelRadius*v.wheelRadius/(inertia*.10*std::max(2.0,s.speed));
        int slices=std::clamp(int(std::ceil(dt*std::max(960.0,stiffness*2))),1,128);
        double sub=dt/slices,impulse=0,road=s.speed;launchTravel=0;
        for(int n=0;n<slices;n++){
            double old=s.launchWheelOmega;
            double slip=(old*v.wheelRadius-road)/std::max(2.0,road);
            double tyre=tractionLimit*std::clamp(slip/.10,0.0,1.0);
            s.launchWheelOmega=std::clamp(old+(wheelForce-tyre)*v.wheelRadius/inertia*sub,0.0,v.redlineRpm*2*3.141592653589793/(60*ratio));
            impulse+=tyre*sub;road+=tyre/v.mass*sub;
            launchTravel+=(old+s.launchWheelOmega)*.5*v.wheelRadius*sub;
        }
        force=impulse/dt;
        if(s.wheelSlip>.1)s.launchSlipSeconds+=dt;
        if(s.launchWheelOmega*v.wheelRadius<=s.speed*1.03+.2){s.launchClutch=false;s.launchWheelOmega=-1;}
    }
    double resistance=.5*1.225*v.dragArea*s.speed*s.speed+v.mass*9.81*v.rollingResistance+std::max(0.0,s.corneringDrag);
    double previous=s.position,oldSpeed=s.speed;
    s.speed=std::max(0.0,s.speed+(force-resistance)/v.mass*dt);
    // Integrate the stopping fraction so hard braking never moves backwards.
    double movementTime=oldSpeed>0&&s.speed==0?std::min(dt,oldSpeed*v.mass/std::max(1.0,resistance-force)):dt;
    double traveled=(oldSpeed+s.speed)*.5*movementTime;s.position+=traveled;
    // Burnout wheel travel is independent of ground/camera travel, by driven axle.
    double spun=s.burningOut?std::max(traveled,s.rpm*2*3.141592653589793*v.wheelRadius/(60*ratio)*dt):traveled;
    if(v.tyreDynamics&&!s.burningOut&&delivering)spun=traveled*(1+s.wheelSlip);
    if(launchTravel>=0){spun=std::max(traveled,launchTravel);s.launchSlipDistance+=std::max(0.0,spun-traveled);}
    double rolling=traveled*(1-s.brakeSlip);
    if(!s.burningOut&&!delivering)spun=rolling;
    double frontRolling=traveled*(1-s.frontBrakeSlip),rearRolling=traveled*(1-s.rearBrakeSlip);
    if(!s.frontLocked)s.frontRollDistance+=v.drive!=DriveLayout::Rear&&!s.neutral?std::max(frontRolling,spun):frontRolling;
    if(!s.rearLocked)s.rearRollDistance+=v.drive!=DriveLayout::Front&&!s.neutral?std::max(rearRolling,spun):rearRolling;
    updateSuspension(s,v,oldSpeed==0&&s.speed==0?0:force,dt);
    s.elapsed+=dt;
    if(finishDistance>0&&s.position>=finishDistance){double fraction=(finishDistance-previous)/(s.position-previous);s.finishTime=s.elapsed-dt+fraction*dt;s.position=finishDistance;s.finished=true;}
}
FreeDrive::FreeDrive(){for(size_t i=0;i<traffic.size();i++){respawn(traffic[i]);traffic[i].position=70+i*55;}}
void FreeDrive::respawn(TrafficCar& t){
    auto next=[this](){random=1664525u*random+1013904223u;return random;};
    t.position=player.position+120+(next()%260);t.speed=12+(next()%160)/10.0;t.lane=next()%3;t.appearance=next()%191;
}
void FreeDrive::setTraffic(bool enabled){
    if(trafficEnabled==enabled)return;
    trafficEnabled=enabled;collisionCooldown=0;
    if(enabled)for(auto& t:traffic)respawn(t);
}
void FreeDrive::changeLane(int d){targetLane=std::clamp(targetLane+d,0,2);}
void FreeDrive::update(const DriverInput& input,double dt){
    if(dt<=0||!std::isfinite(dt))return;
    time+=dt;collisionCooldown=std::max(0.0,collisionCooldown-dt);
    if(vehicle.tyreDynamics){
        constexpr double laneWidth=3.6;
        double frontContact=vehicle.suspensionDynamics&&player.suspensionReady
            ?std::clamp(player.frontLoad/std::max(1.0,vehicle.mass*9.81*vehicle.frontWeightFraction),0.0,1.0):1;
        double lateralGrip=vehicle.grip*9.81*.85*frontContact*(player.rearLocked?.55:player.frontLocked?.35:1);
        double limit=std::min(4.8,player.speed*.22);
        double desired=std::clamp((targetLane-lane)*laneWidth*1.8,-limit,limit);
        double ay=std::clamp((desired-lateralSpeed)*4,-lateralGrip,lateralGrip);
        double old=lateralSpeed;lateralSpeed+=ay*dt;
        // Steering cannot slide a stopped car sideways. A wheelie also loses
        // front steering authority rather than granting a full-grip lane snap.
        if(player.speed<.05){lateralSpeed=0;ay=0;}
        lane+=.5*(old+lateralSpeed)*dt/laneWidth;
        if(lane<0||lane>2){lane=std::clamp(lane,0.0,2.0);lateralSpeed=0;}
        player.lateralAcceleration=ay;
        player.corneringDrag=vehicle.mass*std::max(0.0,ay*(old+lateralSpeed)*.5)/std::max(2.0,player.speed);
    }else lane+=std::clamp(targetLane-lane,-dt*3,dt*3);
    stepCar(player,vehicle,input,dt,0);
    if(!trafficEnabled)return;
    for(auto& t:traffic){
        double before=t.position-player.position;
        t.position+=t.speed*dt;double gap=t.position-player.position;
        if(before>=-6&&gap<-6)++overtakes;
        if(gap<-90||gap>650){respawn(t);continue;}
        if(std::abs(lane-t.lane)<.36&&std::abs(gap)<6&&collisionCooldown==0){
            player.speed=std::min(player.speed,t.speed)*.55;collisionCooldown=1.2;
            t.position=player.position+9;
        }
    }
}
void Race::update(const DriverInput& input,double dt){
    if(result)return;
    if(countdown>0){countdown=std::max(0.0,countdown-dt);player.rpm+=((input.throttle?4200:1000)-player.rpm)*std::min(1.0,dt*8);return;}
    time+=dt;stepCar(player,vehicle,input,dt);
    rivalVehicle.mass=1280;rivalVehicle.torque=340;
    stepCar(opponent,rivalVehicle,{time>.25,false,true},dt);
    result=player.finished;
}
}
