#include "model.hpp"
#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
using namespace pcr;
static int checks=0;
static void expect(bool value,const char* message){++checks;if(!value)throw std::runtime_error(message);}
static CarState simulated(int framesPerSecond,bool endless){
    CarState car;Vehicle v;double accumulator=0;
    for(int frame=0;frame<framesPerSecond*70&&!car.finished;frame++){
        accumulator+=1.0/framesPerSecond;
        while(accumulator+1e-12>=Step){stepCar(car,v,{true,false,true},Step,endless?0:QuarterMile);accumulator-=Step;}
    }return car;
}
int main(int argc,char**argv){
 try{
    if(argc!=2)throw std::runtime_error("Supply an isolated test directory");
    auto root=std::filesystem::u8path(argv[1]);std::filesystem::create_directories(root);
    auto reference=simulated(30,false);
    expect(reference.finished&&reference.finishTime>8&&reference.finishTime<40,"native car completes quarter mile");
    for(int fps:{60,120,144,165,240}){auto c=simulated(fps,false);expect(std::abs(c.finishTime-reference.finishTime)<1e-9,"simulation independent of rendering rate");}
    auto endless=simulated(60,true);
    expect(!endless.finished&&endless.position>QuarterMile*2,"free drive does not finish at 402 metres");
    Vehicle v;double before=endless.speed;
    for(int i=0;i<1200;i++)stepCar(endless,v,{false,true,true},Step,0);
    expect(endless.speed<before&&endless.speed==0,"brakes stop the vehicle without reversing");
    // Behavioural regressions for the provisional drivetrain, independent of graphics.
    CarState restart;restart.gear=6;
    for(int i=0;i<1200;i++)stepCar(restart,v,{true,false,true},Step,0);
    expect(restart.speed>20,"automatic gearbox recovers from a high gear at rest");
    CarState manual;manual.speed=55;manual.gear=4;
    expect(!shift(manual,-1,v)&&manual.gear==4,"unsafe manual downshift is rejected");
    CarState changing;changing.speed=15;changing.gear=2;
    expect(shift(changing,1,v),"safe manual upshift accepted");
    double shiftSpeed=changing.speed;
    stepCar(changing,v,{true,false,false},Step,0);
    expect(changing.speed<shiftSpeed,"shift interrupts wheel torque");
    expect(!shift(changing,-1,v),"shift lock prevents instantaneous repeated shifts");
    CarState low,high;low.speed=high.speed=20;low.gear=2;high.gear=5;
    for(int i=0;i<120;i++){stepCar(low,v,{false,false,false},Step,0);stepCar(high,v,{false,false,false},Step,0);}
    expect(low.speed<high.speed,"lower gear provides stronger engine braking");
    CarState braking,conflicting;braking.speed=conflicting.speed=100/3.6;
    double brakingTime=0;
    for(int i=0;i<1200&&braking.speed>0;i++){
        stepCar(braking,v,{false,true,true},Step,0);stepCar(conflicting,v,{true,true,true},Step,0);brakingTime+=Step;
    }
    expect(braking.speed==0&&braking.position>35&&braking.position<55,"100 km/h stopping distance remains plausible");
    expect(std::abs(braking.position-conflicting.position)<1e-9,"brake overrides simultaneous throttle");
    CarState lighter,heavier;lighter.speed=heavier.speed=25;lighter.gear=heavier.gear=3;
    Vehicle heavy=v;heavy.mass*=1.5;
    for(int i=0;i<120;i++){stepCar(lighter,v,{true,false,false},Step,0);stepCar(heavier,heavy,{true,false,false},Step,0);}
    expect(lighter.speed>heavier.speed,"added mass reduces acceleration outside traction limit");
    CarState grip;Vehicle slippery=v;slippery.grip=.4;
    for(int i=0;i<120;i++)stepCar(grip,slippery,{true,false,false},Step,0);
    expect(grip.speed<9.81*slippery.grip,"traction bounds launch acceleration");
    CarState limiter;
    for(int i=0;i<120*30;i++)stepCar(limiter,v,{true,false,false},Step,0);
    expect(limiter.gear==1&&limiter.rpm<v.redlineRpm+50,"manual first gear cannot accelerate indefinitely past redline");
    CarState stable;stable.speed=18;stable.gear=3;int changes=0,lastGear=3;
    for(int i=0;i<120*8;i++){
        stepCar(stable,v,{false,false,true},Step,0);
        if(stable.gear!=lastGear){++changes;lastGear=stable.gear;}
    }
    expect(changes<=2,"automatic coastdown does not hunt between gears");
    CarState launch;double zeroToHundred=0;
    std::ofstream trace(root/"physics-baseline.csv");
    trace<<"time_s,speed_kmh,rpm,gear,distance_m\n";
    for(int i=0;i<120*30;i++){
        stepCar(launch,v,{true,false,true},Step,0);
        if(zeroToHundred==0&&launch.speed>=100/3.6)zeroToHundred=launch.elapsed;
        if(i%12==0)trace<<launch.elapsed<<','<<launch.speed*3.6<<','<<launch.rpm<<','<<launch.gear<<','<<launch.position<<'\n';
    }
    expect(zeroToHundred>3&&zeroToHundred<12,"baseline reaches 100 km/h within a plausible broad envelope");
    expect(braking.gear==1,"automatic gearbox returns to first after a full stop");
    std::cout<<"0-100 km/h "<<zeroToHundred<<" s; telemetry physics-baseline.csv\n";
    std::cout<<"Physics baseline (provisional, not original): 100-0 km/h "<<braking.position<<" m / "<<brakingTime
             <<" s; restart in sixth after 10 s "<<restart.speed*3.6<<" km/h\n";
    FreeDrive free;free.changeLane(-100);expect(free.targetLane==0,"left lane clamp");free.changeLane(100);expect(free.targetLane==2,"right lane clamp");
    for(int i=0;i<180;i++)free.update({true,false,true},Step);
    expect(free.lane<=2&&free.lane>=0&&free.player.position>0,"free drive moves and interpolates lanes");
    FreeDrive collision;collision.player.speed=30;collision.traffic[0]={0,10,1,0};collision.update({true,false,true},Step);
    expect(collision.collisionCooldown>0&&collision.player.speed<10,"traffic collision changes vehicle motion");
    auto file=root/std::filesystem::u8path("écran_車.ini");Settings s;s.mode=WindowMode::Borderless;s.width=1920;s.height=1080;s.fps=144;s.vsync=false;s.quality=Quality::Low;s.showFps=true;s.sound=false;
    std::string error;expect(saveSettings(file,s,error),"save Unicode settings path");expect(loadSettings(file)==s,"all graphics settings round trip");
    s.fps=60;s.mode=WindowMode::Fullscreen;expect(saveSettings(file,s,error),"atomic replacement of existing settings");expect(loadSettings(file)==s,"replaced graphics settings persist");
    expect(!std::filesystem::exists(file.u8string()+".tmp"),"successful save leaves no temporary file");
    {std::ofstream out(file);out<<"width=-1\nheight=99999999\nfps=not-a-number\nmode=execute-this\nquality=99\n";}
    auto invalid=loadSettings(file);expect(invalid.width==1280&&invalid.height==720&&invalid.fps==120&&invalid.mode==WindowMode::Windowed&&invalid.quality==Quality::High,"invalid settings safely fall back");
    Profile p;p.car=190;p.rim=53;p.automatic=false;p.bestTime=12.345678;
    expect(saveProfile(root/"profile.ini",p,error),"profile saved");auto loaded=loadProfile(root/"profile.ini",191,54);
    expect(loaded.car==190&&loaded.rim==53&&!loaded.automatic&&std::abs(loaded.bestTime-p.bestTime)<1e-9,"garage and driving preferences persist");
    {std::ofstream out(root/"profile.ini");out<<"car=9999\nrim=-2\nbest_time=nan\n";}
    auto bad=loadProfile(root/"profile.ini",191,54);expect(bad.car==190&&bad.rim==0&&bad.bestTime==0,"malformed profile is bounded");
    expect(easeLinear(0,5,10,2)==5&&easeLinear(2,5,10,2)==15,"reconstructed numeric easing endpoints");
    std::cout<<"PASS: "<<checks<<" checks; quarter mile "<<reference.finishTime<<" s; endless distance "<<simulated(60,true).position<<" m\n";
    return 0;
 }catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
