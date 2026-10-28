#pragma once
namespace pcr {
enum class TurboLayout {Single,Parallel,Sequential,Hybrid,Electric,Quad};
struct PcTurbo {int id;TurboLayout layout;int count;double psi,capacityHp,spoolStartRpm,fullBoostRpm,riseSeconds,secondaryStartRpm,secondaryFullRpm,firstShare,weightLb,soundPitch,soundGain;};
inline constexpr PcTurbo PcTurbos[]={
{16001,TurboLayout::Single,1,10,400,1800,3600,0.35,0,0,1,35,0.95,0.28},
{16002,TurboLayout::Hybrid,1,16,600,1700,3400,0.26,0,0,1,40,1.05,0.3},
{16003,TurboLayout::Parallel,2,20,1000,2100,4000,0.32,0,0,1,80,1.15,0.35},
{16004,TurboLayout::Electric,1,22,800,1000,2300,0.12,0,0,1,65,1.25,0.28},
{16005,TurboLayout::Hybrid,1,28,1000,2200,4300,0.34,0,0,1,50,1.1,0.38},
{16006,TurboLayout::Parallel,2,32,1600,2300,4400,0.38,0,0,1,90,1.05,0.43},
{16007,TurboLayout::Single,1,35,1500,3000,5500,0.52,0,0,1,55,0.85,0.45},
{16008,TurboLayout::Electric,1,38,1800,1300,3200,0.18,0,0,1,80,1.3,0.38},
{16009,TurboLayout::Single,1,44,2200,3600,6200,0.65,0,0,1,65,0.75,0.5},
{16010,TurboLayout::Parallel,2,48,3200,2800,5000,0.4,0,0,1,105,1.05,0.48},
{16011,TurboLayout::Hybrid,1,52,2800,2600,4800,0.36,0,0,1,70,1.15,0.46},
{16012,TurboLayout::Sequential,2,58,4200,1700,4200,0.4,3600,5800,0.55,120,1.15,0.48},
{16013,TurboLayout::Quad,4,64,6000,1800,4000,0.44,3800,6000,0.55,180,1.1,0.48},
{16014,TurboLayout::Electric,1,68,5200,1400,3400,0.22,0,0,1,110,1.35,0.45},
{16015,TurboLayout::Parallel,2,74,9000,3400,6400,0.6,0,0,1,150,0.95,0.55},
{16016,TurboLayout::Quad,4,78,11000,2000,4400,0.48,4000,6500,0.5,220,1.0,0.52},
{16017,TurboLayout::Hybrid,2,82,12000,3000,5600,0.48,0,0,1,165,1.2,0.52},
{16018,TurboLayout::Quad,4,85,14000,2000,4200,0.45,3800,6500,0.5,240,1.15,0.58},
};
inline const PcTurbo* pcTurbo(int id){for(const auto& t:PcTurbos)if(t.id==id)return &t;return nullptr;}
inline const char* turboLayoutName(TurboLayout layout){switch(layout){
case TurboLayout::Single:return "SIMPLE";case TurboLayout::Parallel:return "BITURBO PARALLELE";
case TurboLayout::Sequential:return "BITURBO SEQUENTIEL";case TurboLayout::Hybrid:return "HYBRIDE OEM";
case TurboLayout::Electric:return "ASSISTANCE ELECTRIQUE";case TurboLayout::Quad:return "QUAD SEQUENTIEL";}return "TURBO";}
}
