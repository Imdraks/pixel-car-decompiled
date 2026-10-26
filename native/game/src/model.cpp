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
int bodyChoiceIndex(const Profile& p){for(size_t i=0;i<std::size(BodyChoices);i++)if(BodyChoices[i].body==p.car&&(BodyChoices[i].source==p.contentSource||BodyChoices[i].sourceMask==3))return int(i);return 0;}
void cycleBody(Profile& p,int direction){int index=(bodyChoiceIndex(p)+direction+int(std::size(BodyChoices)))%int(std::size(BodyChoices));p.car=BodyChoices[index].body;p.contentSource=BodyChoices[index].source;}

bool operator==(const Settings&a,const Settings&b){return a.mode==b.mode&&a.width==b.width&&a.height==b.height&&a.fps==b.fps&&a.vsync==b.vsync&&a.showFps==b.showFps&&a.sound==b.sound&&a.traffic==b.traffic&&a.quality==b.quality;}
const char* modeKey(WindowMode mode){switch(mode){case WindowMode::Fullscreen:return "fullscreen";case WindowMode::Borderless:return "borderless";default:return "windowed";}}
Settings validate(Settings s){
    if(s.mode!=WindowMode::Windowed&&s.mode!=WindowMode::Borderless&&s.mode!=WindowMode::Fullscreen)s.mode=WindowMode::Windowed;
    if(s.width<800||s.width>7680||s.height<450||s.height>4320){s.width=1280;s.height=720;}
    if(s.fps!=0&&s.fps!=30&&s.fps!=60&&s.fps!=120&&s.fps!=144&&s.fps!=165&&s.fps!=240)s.fps=120;
    if(s.quality!=Quality::Low&&s.quality!=Quality::Medium&&s.quality!=Quality::High)s.quality=Quality::High;
    return s;
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
    p.gearCount=std::clamp(p.gearCount,4,10);
    if(p.gearboxPreset< -1||p.gearboxPreset>7)p.gearboxPreset=0;
    if(!std::isfinite(p.finalDrive)||p.finalDrive<2||p.finalDrive>6)p.finalDrive=3.9;
    if(!std::isfinite(p.shiftSeconds)||p.shiftSeconds<.04||p.shiftSeconds>.5)p.shiftSeconds=.15;
    bool valid=true;double previous=7;
    for(double ratio:p.gearRatios){valid&=std::isfinite(ratio)&&ratio>=.3&&ratio<=6&&previous-ratio>=.05-1e-9;previous=ratio;}
    if(!valid)p.gearRatios={3.15,2.10,1.55,1.22,1.0,.82,.68,.56,.46,.38};
}
Settings loadSettings(const std::filesystem::path& file){
    auto v=readIni(file);Settings s;
    if(v["mode"]=="fullscreen")s.mode=WindowMode::Fullscreen;
    if(v["mode"]=="borderless")s.mode=WindowMode::Borderless;
    s.width=integer(v,"width",s.width);s.height=integer(v,"height",s.height);s.fps=integer(v,"fps",s.fps);
    s.quality=Quality(integer(v,"quality",int(s.quality)));
    s.vsync=integer(v,"vsync",s.vsync)!=0;s.showFps=integer(v,"show_fps",s.showFps)!=0;s.sound=integer(v,"sound",s.sound)!=0;
    s.traffic=integer(v,"traffic",1)!=0;
    return validate(s);
}
Profile loadProfile(const std::filesystem::path& file,int cars,int rims){
    auto v=readIni(file);Profile p;
    (void)rims;p.rollCage=integer(v,"roll_cage",0)!=0;p.headlights=integer(v,"headlights",0)!=0;p.contentSource=std::clamp(integer(v,"content_source",0),0,1);p.audioSource=std::clamp(integer(v,"audio_source",p.contentSource),0,1);
    for(int slot=0;slot<CosmeticSlotCount;slot++){int id=integer(v,"cosmetic_"+std::to_string(slot),0);auto item=findCosmetic(id);if(item&&item->slot==slot)p.cosmetics[slot]=id;}
    p.car=std::clamp(integer(v,"car",0),0,std::max(0,cars-1));
    p.rim=validRimFrame(integer(v,"rim",8));p.automatic=integer(v,"automatic",1)!=0;
    int layout=integer(v,"drive",1);p.drive=layout>=0&&layout<=2?DriveLayout(layout):DriveLayout::Rear;
    p.soundOn=integer(v,"sound_on",-1);if(p.soundOn< -1||p.soundOn>15)p.soundOn=-1;
    p.soundOff=integer(v,"sound_off",-1);if(p.soundOff< -1||p.soundOff>15)p.soundOff=-1;
    p.bov=integer(v,"bov",-1);if(p.bov< -1||p.bov>3)p.bov=-1;
    for(int slot=0;slot<PartSlotCount;slot++)equipPart(p,PartSlot(slot),integer(v,std::string("part_")+slotKey(PartSlot(slot)),0));
    if(integer(v,"version",1)<2&&p.contentSource==1){if(p.cosmetics[9])p.cosmetics[9]+=200000;if(p.parts[9]==9030||p.parts[9]==9031)p.parts[9]+=200000;}
    try {size_t used=0;p.bestTime=std::stod(v["best_time"],&used);if(used!=v["best_time"].size()||!std::isfinite(p.bestTime)||p.bestTime<0||p.bestTime>120)p.bestTime=0;}catch(...){p.bestTime=0;}
    p.gearboxPreset=integer(v,"gearbox_preset",0);
    p.gearCount=integer(v,"gear_count",6);p.finalDrive=real(v,"final_drive",3.9);p.shiftSeconds=real(v,"shift_seconds",.15);
    for(int i=0;i<10;i++)p.gearRatios[i]=real(v,"gear_"+std::to_string(i+1),p.gearRatios[i]);
    sanitizeTransmission(p);
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
    return writeAtomic(file,out.str(),error);
}
bool saveProfile(const std::filesystem::path& file,const Profile& raw,std::string& error){
    Profile p=raw;sanitizeTransmission(p);
    std::ostringstream out;out.imbue(std::locale::classic());
    out<<"version=2\ncar="<<p.car<<"\nrim="<<p.rim<<"\nautomatic="<<p.automatic<<"\ndrive="<<int(p.drive)<<"\nbest_time="<<std::setprecision(12)<<p.bestTime<<"\n";
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
    return .62+.38*std::exp(-std::pow((rpm/v.curveRpmScale-5200)/2700,2));
}
double targetBoost(const Vehicle& v,double rpm){
    return v.boostPsi*std::clamp((rpm-(v.supercharged?0:2200))/(v.supercharged?v.redlineRpm:2500),0.0,1.0);
}
double engineTorque(const Vehicle& v,double rpm,double boost){
    boost=std::clamp(boost,0.0,v.boostPsi);
    double torque=v.torque*torqueCurve(v,rpm)*(1+boost/14.7*v.boostEfficiency);
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
bool shift(CarState& car,int direction,const Vehicle& vehicle){
    if(car.shiftLock>0||car.finished||direction==0)return false;
    int next=std::clamp(car.gear+(direction>0?1:-1),1,vehicle.gearCount);
    // Reject an unsafe downshift instead of allowing mechanically impossible RPM.
    if(next==car.gear||(next<car.gear&&wheelRpm(car,vehicle,next)>vehicle.redlineRpm))return false;
    car.gear=next;car.shiftLock=vehicle.shiftSeconds;
    return true;
}
void stepCar(CarState& s,const Vehicle& v,const DriverInput& input,double dt,double finishDistance){
    if(s.finished||dt<=0||!std::isfinite(dt))return;
    s.gear=std::clamp(s.gear,1,v.gearCount);
    s.shiftLock=std::max(0.0,s.shiftLock-dt);
    bool braking=input.brake||input.handbrake;s.handbraking=input.handbrake;
    s.launching=v.twoStep&&input.launch&&input.throttle&&!braking&&s.speed<3;
    double coupled=wheelRpm(s,v,s.gear);
    if(input.automatic&&s.shiftLock==0){
        if(input.throttle&&!braking&&coupled>v.upshiftRpm&&s.gear<v.gearCount)shift(s,1,v);
        else if(s.gear>1&&coupled<(input.throttle&&!braking?2600.0:1500.0)
                &&wheelRpm(s,v,s.gear-1)<v.upshiftRpm*.9)shift(s,-1,v);
        coupled=wheelRpm(s,v,s.gear);
    }
    // Simplified slipping clutch below launch RPM. Above it, RPM follows wheel speed.
    double target=s.launching?4200:std::max(input.throttle&&!braking?v.launchRpm:v.idleRpm,coupled);
    if(s.shiftLock>0)s.rpm+=std::clamp(target-s.rpm,-13000*dt,15000*dt);
    else s.rpm=target;
    double ratio=v.ratios[s.gear-1]*v.finalDrive;
    double boostTarget=input.throttle&&(!braking||s.launching)&&s.shiftLock==0
        ?targetBoost(v,s.rpm):0;
    double boostRate=v.boostPsi*(boostTarget>s.boostPsi?(v.supercharged?10:2):8);
    s.boostPsi+=std::clamp(boostTarget-s.boostPsi,-boostRate*dt,boostRate*dt);
    double torque=engineTorque(v,s.rpm,s.boostPsi);
    s.nitroActive=input.nitro&&input.throttle&&!braking&&s.shiftLock==0&&!s.launching&&s.speed>2&&coupled<v.redlineRpm&&v.nitroHp>0&&s.nitroRemaining>0;
    double nitroFraction=s.nitroActive?std::min(1.0,s.nitroRemaining/dt):0;
    if(s.nitroActive)s.nitroRemaining=std::max(0.0,s.nitroRemaining-dt);
    bool delivering=input.throttle&&!braking&&!s.launching&&s.shiftLock==0&&coupled<v.redlineRpm;
    s.powerHp=delivering?enginePowerHp(v,s.rpm,s.boostPsi,false)+nitroFraction*v.nitroHp:0;
    double tractionLimit=drivenGrip(v,true);
    double wheelForce=input.throttle&&!braking&&!s.launching&&s.shiftLock==0&&coupled<v.redlineRpm
        ?torque*ratio*v.efficiency/v.wheelRadius:0;
    wheelForce+=nitroFraction*v.nitroHp*745.699872*v.efficiency/std::max(10.0,s.speed);
    if((!input.throttle||braking)&&s.shiftLock==0){
        // Engine and service braking share the same tyre contact patch.
        wheelForce-=v.engineBrakeTorque*ratio/v.wheelRadius*std::clamp(coupled/v.idleRpm,0.0,1.0);
    }
    if(input.brake)wheelForce-=v.mass*v.brakeDeceleration;
    double rearFraction=v.drive==DriveLayout::Front?1-v.drivenWeightFraction:v.drivenWeightFraction;
    double handbrakeLimit=v.mass*9.81*v.grip*rearFraction/(1+v.grip*v.centreOfGravityHeight/v.wheelbase);
    if(input.handbrake&&!input.brake)wheelForce-=handbrakeLimit;
    double brakingLimit=input.brake?v.mass*9.81*v.grip:input.handbrake?handbrakeLimit:drivenGrip(v,false);
    s.wheelSlip=std::clamp((wheelForce-tractionLimit)/std::max(1.0,tractionLimit),0.0,2.0);
    double force=std::clamp(wheelForce,-brakingLimit,tractionLimit);
    double resistance=.5*1.225*v.dragArea*s.speed*s.speed+v.mass*9.81*v.rollingResistance;
    double previous=s.position,oldSpeed=s.speed;
    s.speed=std::max(0.0,s.speed+(force-resistance)/v.mass*dt);
    // Integrate the stopping fraction so hard braking never moves backwards.
    double movementTime=oldSpeed>0&&s.speed==0?std::min(dt,oldSpeed*v.mass/std::max(1.0,resistance-force)):dt;
    double traveled=(oldSpeed+s.speed)*.5*movementTime;s.position+=traveled;if(!input.handbrake)s.rearRollDistance+=traveled;s.elapsed+=dt;
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
    time+=dt;collisionCooldown=std::max(0.0,collisionCooldown-dt);
    lane+=std::clamp(targetLane-lane,-dt*3,dt*3);
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
