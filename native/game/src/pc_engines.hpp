// Native approximations: rated outputs use mechanical HP, not metric PS.
#pragma once
namespace pcr {
struct PcEngine {
    int id;double redlineRpm,litres;int cylinders;
    double torquePeakRpm,torqueWidthRpm,lowTorqueFraction,inertia;
    int soundOn,soundOff;double factoryBoostSoundPsi;bool blower;
};
inline constexpr PcEngine PcEngines[]={
{1501,7000,4,8,4000,3300,0.66,0.29,24,20,18,false},
{1502,8500,5.2,10,6500,3000,0.4,0.24,73,24,0,false},
{1503,8500,6.5,12,5500,3200,0.44,0.3,78,24,0,false},
{1504,15000,1.6,6,11000,4100,0.25,0.1,81,20,35,false},
{1505,7500,5,8,4600,3000,0.55,0.28,24,20,0,false},
{1506,8250,5,10,6100,2800,0.42,0.25,73,24,0,false},
{1507,9000,4.8,10,6800,3100,0.36,0.19,78,24,0,false},
{1508,9000,4.5,8,6000,3000,0.4,0.22,79,20,0,false},
{1509,9000,4,6,6100,3100,0.42,0.23,47,20,0,false},
{1510,7200,3,6,4000,3100,0.65,0.27,71,23,20,false},
{1511,7000,2.5,5,4000,3000,0.62,0.22,23,21,18,false},
{1512,7000,2,4,3500,2900,0.6,0.19,21,20,18,false},
{1513,8000,1.3,0,5000,2900,0.35,0.15,80,20,12,false},
{1514,6200,6.2,8,4800,3000,0.7,0.35,24,20,11.6,true},
{1515,6700,8,16,4000,3400,0.72,0.48,24,20,23,false},
};
inline const PcEngine* pcEngine(int id){for(const auto& e:PcEngines)if(e.id==id)return &e;return nullptr;}
}
