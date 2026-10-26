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
bool operator==(const Settings&a,const Settings&b){return a.mode==b.mode&&a.width==b.width&&a.height==b.height&&a.fps==b.fps&&a.vsync==b.vsync&&a.showFps==b.showFps&&a.sound==b.sound&&a.quality==b.quality;}
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
Settings loadSettings(const std::filesystem::path& file){
    auto v=readIni(file);Settings s;
    if(v["mode"]=="fullscreen")s.mode=WindowMode::Fullscreen;
    if(v["mode"]=="borderless")s.mode=WindowMode::Borderless;
    s.width=integer(v,"width",s.width);s.height=integer(v,"height",s.height);s.fps=integer(v,"fps",s.fps);
    s.quality=Quality(integer(v,"quality",int(s.quality)));
    s.vsync=integer(v,"vsync",s.vsync)!=0;s.showFps=integer(v,"show_fps",s.showFps)!=0;s.sound=integer(v,"sound",s.sound)!=0;
    return validate(s);
}
Profile loadProfile(const std::filesystem::path& file,int cars,int rims){
    auto v=readIni(file);Profile p;
    p.car=std::clamp(integer(v,"car",0),0,std::max(0,cars-1));
    p.rim=std::clamp(integer(v,"rim",0),0,std::max(0,rims-1));p.automatic=integer(v,"automatic",1)!=0;
    try {size_t used=0;p.bestTime=std::stod(v["best_time"],&used);if(used!=v["best_time"].size()||!std::isfinite(p.bestTime)||p.bestTime<0||p.bestTime>120)p.bestTime=0;}catch(...){p.bestTime=0;}
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
    out<<"version=1\nmode="<<modeKey(s.mode)<<"\nwidth="<<s.width<<"\nheight="<<s.height<<"\nfps="<<s.fps<<"\nvsync="<<s.vsync<<"\nquality="<<int(s.quality)<<"\nshow_fps="<<s.showFps<<"\nsound="<<s.sound<<"\n";
    return writeAtomic(file,out.str(),error);
}
bool saveProfile(const std::filesystem::path& file,const Profile& p,std::string& error){
    std::ostringstream out;out.imbue(std::locale::classic());
    out<<"version=1\ncar="<<p.car<<"\nrim="<<p.rim<<"\nautomatic="<<p.automatic<<"\nbest_time="<<std::setprecision(12)<<p.bestTime<<"\n";
    return writeAtomic(file,out.str(),error);
}
// Numeric path derived from Unbound ease_linear disassembly, not generic YYRValue semantics.
double easeLinear(double t,double b,double c,double d){return (c*t)/d+b;}
void shift(CarState& car,int direction){if(car.shiftLock>0||car.finished)return;int next=std::clamp(car.gear+direction,1,6);if(next!=car.gear){car.gear=next;car.shiftLock=.15;}}
void stepCar(CarState& s,const Vehicle& v,const DriverInput& input,double dt,double finishDistance){
    if(s.finished||dt<=0)return;
    s.shiftLock=std::max(0.0,s.shiftLock-dt);
    double ratio=v.ratios[s.gear-1]*v.finalDrive;
    double coupled=s.speed/(2*3.141592653589793*v.wheelRadius)*60*ratio;
    double target=std::max(input.throttle?2800.0:1000.0,coupled);
    s.rpm+=std::clamp(target-s.rpm,-13000*dt,15000*dt);
    if(input.automatic&&s.rpm>7100&&s.gear<6){shift(s,1);ratio=v.ratios[s.gear-1]*v.finalDrive;}
    double torque=v.torque*(.62+.38*std::exp(-std::pow((s.rpm-5200)/2700,2)));
    double force=input.throttle&&s.shiftLock==0&&s.rpm<8100?torque*ratio*.87/v.wheelRadius:0;
    force=std::min(force,v.mass*9.81*1.08);
    double resistance=.5*1.225*.67*s.speed*s.speed+v.mass*9.81*.014;
    if(!input.throttle)resistance+=240;
    if(input.brake)resistance+=v.mass*8.5;
    double previous=s.position;
    s.speed=std::max(0.0,s.speed+(force-resistance)/v.mass*dt);
    s.position+=s.speed*dt;s.elapsed+=dt;
    if(finishDistance>0&&s.position>=finishDistance){double fraction=(finishDistance-previous)/(s.position-previous);s.finishTime=s.elapsed-dt+fraction*dt;s.position=finishDistance;s.finished=true;}
}
FreeDrive::FreeDrive(){for(size_t i=0;i<traffic.size();i++){respawn(traffic[i]);traffic[i].position=70+i*55;}}
void FreeDrive::respawn(TrafficCar& t){
    auto next=[this](){random=1664525u*random+1013904223u;return random;};
    t.position=player.position+120+(next()%260);t.speed=12+(next()%160)/10.0;t.lane=next()%3;t.appearance=next()%191;
}
void FreeDrive::changeLane(int d){targetLane=std::clamp(targetLane+d,0,2);}
void FreeDrive::update(const DriverInput& input,double dt){
    time+=dt;collisionCooldown=std::max(0.0,collisionCooldown-dt);
    lane+=std::clamp(targetLane-lane,-dt*3,dt*3);
    stepCar(player,vehicle,input,dt,0);
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
