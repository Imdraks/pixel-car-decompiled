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
