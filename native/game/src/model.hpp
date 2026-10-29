#pragma once
#include "catalog_review.hpp"
#include <filesystem>
#include <cmath>
#include <algorithm>
#include <string>
#include <vector>
#include <array>
#include "catalog.hpp"
#include "rims.hpp"
#include "rim_styles.hpp"
#include "content_catalog.hpp"
#include "body_choices.hpp"
#include "stock_vehicles.hpp"
#include "pc_engines.hpp"
#include "pc_turbos.hpp"
#include "vehicle_identities.hpp"
#include "vehicle_catalog.hpp"

namespace pcr {
enum class WindowMode { Windowed, Borderless, Fullscreen };
enum class DriveLayout { Front, Rear, All };
enum class Quality { Low, Medium, High };
struct Resolution { int width, height; bool operator==(const Resolution& r) const {return width==r.width && height==r.height;} };
struct AudioVolumes {double master=1,engine=1,turbo=1,effects=1,ambience=1,interface=1,music=1;};
inline AudioVolumes validateVolumes(AudioVolumes v){
    auto clamp=[](double x){return std::isfinite(x)?std::clamp(x,0.0,1.0):1.0;};
    v.master=clamp(v.master);v.engine=clamp(v.engine);v.turbo=clamp(v.turbo);v.effects=clamp(v.effects);v.ambience=clamp(v.ambience);v.interface=clamp(v.interface);v.music=clamp(v.music);return v;
}
inline bool operator==(const AudioVolumes& a,const AudioVolumes& b){return a.master==b.master&&a.engine==b.engine&&a.turbo==b.turbo&&a.effects==b.effects&&a.ambience==b.ambience&&a.interface==b.interface&&a.music==b.music;}
struct Settings {
    WindowMode mode=WindowMode::Windowed;
    int width=1280, height=720, fps=120;
    bool vsync=true, showFps=false, sound=true, traffic=true,abs=true,tractionControl=true;
    AudioVolumes volumes{};
    Quality quality=Quality::High;
};
struct Profile { bool factoryInitialized=false;int factoryEngineId=0;std::string savedName;int car=0, rim=8,rearRim=-1,contentSource=0,audioSource=0;std::array<int,CosmeticSlotCount> cosmetics{};bool rollCage=false,headlights=false,factoryDrive=true; double bestTime=0; bool automatic=true; DriveLayout drive=DriveLayout::Rear; std::array<int,PartSlotCount> parts{}; int soundOn=-1,soundOff=-1,bov=-1;
    int gearboxPreset=0,gearCount=6;std::array<double,10> gearRatios{3.15,2.10,1.55,1.22,1.0,.82,.68,.56,.46,.38};
    double finalDrive=3.9,shiftSeconds=.15;
    double rideHeightMm=0,springStiffness=1,dampingRatio=.65,frontBias=0,wheelieTune=1;bool allowWheelie=false; // Derived legacy mirror; the slider is authoritative.
};
int bodyChoiceIndex(const Profile&);
inline const StockVehicle& vehicleMechanics(const Profile& p){return VehicleCatalog[bodyChoiceIndex(p)].stock;}
inline DriveLayout effectiveDrive(const Profile& p){return p.factoryDrive?DriveLayout(vehicleMechanics(p).drive):p.drive;}
enum class SuspensionPreset { Road, Drag, Track, Wheelie };
void applySuspensionPreset(Profile&,SuspensionPreset);
inline int rearRimId(const Profile& p){return p.rearRim<0?p.rim:p.rearRim;}
void equipRim(Profile&,int id,int axle);
int bodyChoiceIndex(const Profile&);
void cycleBody(Profile&,int);
void sanitizeTransmission(Profile&);
void sanitizeSuspension(Profile&);
void applyGearboxPreset(Profile&,int preset);
const char* gearboxPresetName(int preset);
bool operator==(const Settings&, const Settings&);
Settings validate(Settings);
Settings loadSettings(const std::filesystem::path&);
Profile loadProfile(const std::filesystem::path&, int carCount, int rimCount);
bool saveSettings(const std::filesystem::path&, const Settings&, std::string& error);
bool saveProfile(const std::filesystem::path&, const Profile&, std::string& error);
const char* modeKey(WindowMode);
double easeLinear(double t, double b, double c, double d);

// Native integration defaults for the diagnostic reference car. buildVehicle applies
// recovered per-body stock mass/power/revs/grip/layout before installed parts.
struct Vehicle {
    double mass=1240, torque=345, wheelRadius=.32, finalDrive=3.9;
    int gearCount=6;std::array<double,10> ratios{3.15,2.10,1.55,1.22,1.0,.82,.68,.56,.46,.38};
    // SI units; provisional calibration, not recovered GameMaker constants.
    double idleRpm=1000, launchRpm=2800, upshiftRpm=7100, redlineRpm=8100;
    double shiftSeconds=.15, efficiency=.87, grip=1.08;
    double dragArea=.67, rollingResistance=.014, brakeDeceleration=8.5;
    double engineBrakeTorque=18;
    double engineInertia=.24,drivenWheelInertia=2.4; // Native kg m² clutch-launch calibration.
    DriveLayout drive=DriveLayout::Rear;
    double drivenWeightFraction=.52, wheelbase=2.6, centreOfGravityHeight=.50;
    double curveRpmScale=1,boostEfficiency=.7;
    double torquePeakRpm=5200,torqueWidthRpm=2700,lowTorqueFraction=.62;
    bool electric=false;double factoryBoostSoundPsi=0;
    double turboFlowHp=0,turboSpoolStartRpm=2200,turboFullBoostRpm=4700,turboRiseSeconds=.5;
    double turboSecondaryStartRpm=0,turboSecondaryFullRpm=0,turboFirstShare=1;
    int turboCount=1,turboAutoValve=-1;double turboSoundPitch=1,turboSoundGain=0;
    double superchargerExponent=1;double boostPsi=0,nitroHp=0; bool supercharged=false,twoStep=false;
    bool suspensionDynamics=false,tyreDynamics=false,allowWheelie=false,abs=false,tractionControl=false;
    bool wheelieBar=false;double wheelieBarArm=0,wheelieBarClearance=0;
    double springStiffness=1,dampingRatio=.65,frontWeightFraction=.48,wheelieTune=1;
    double suspensionDroop=.12,suspensionBump=.08;

};
const Part* findPart(int id);
const char* slotKey(PartSlot);
const char* slotLabel(PartSlot);
bool equipPart(Profile&,PartSlot,int id);
struct EngineSamples { int on=21,off=22; };
EngineSamples engineSamples(const Profile&);
int audioEngineId(const Profile&);
bool partCompatibleWithPowertrain(const Profile&,PartSlot,int);
enum class Rarity { Basic, Sport, Pro, Super, Elite, Contraband, Common=Basic, Uncommon=Sport, Rare=Pro, Epic=Super, Legendary=Elite };
Rarity partRarity(const Part&);
const char* rarityLabel(Rarity);
double partPerformance(const Part&);
bool weakerPart(const Part&,const Part&);
void equipBestParts(Profile&);
double torqueCurve(const Vehicle&,double rpm);
double targetBoost(const Vehicle&,double rpm);
double engineTorque(const Vehicle&,double rpm,double boostPsi);
double enginePowerHp(const Vehicle&,double rpm,double boostPsi,bool nitro=false);
struct PowerPeak { double hp=0,rpm=0; };
PowerPeak peakPower(const Vehicle&,bool boost=true,bool nitro=false);
struct Build {
    Vehicle vehicle; double baseHp=0,engineHp=0,boltOnHp=0,boostedHp=0,nitroHp=0,peakRpm=0,rideOffset=0;
    int tireFrame=0,exhaustFrame=0;
};
double engineRedline(const Profile&);
Build buildVehicle(const Profile&);
struct DriverInput { bool throttle=false, brake=false, automatic=true,nitro=false,launch=false,handbrake=false,neutral=false; };
struct CarState {
    double position=0, speed=0, rpm=1000, elapsed=0, finishTime=0, shiftLock=0;
    int gear=1;
    double powerHp=0,boostPsi=0,nitroRemaining=10,wheelSlip=0; bool nitroActive=false,launching=false,handbraking=false; double rearRollDistance=0,frontRollDistance=0;
    bool neutral=false,burningOut=false,finished=false;
    bool launchClutch=false;double launchWheelOmega=-1,launchSlipSeconds=0,launchSlipDistance=0;
    double pitch=0,pitchRate=0,heave=0,heaveRate=0,frontLoad=0,rearLoad=0,frontLift=0,rearLift=0,peakFrontLift=0;
    double tractionFactor=1,brakeSlip=0,frontBrakeSlip=0,rearBrakeSlip=0;
    // Lateral demand consumes the same tyre adhesion as acceleration/braking.
    double lateralAcceleration=0,corneringDrag=0;
    bool wheelieBarContact=false,wheelieBarTouched=false;
    bool suspensionReady=false,tcActive=false,absActive=false,frontLocked=false,rearLocked=false;

};
constexpr double Step=1.0/120.0, QuarterMile=402.336;
bool shift(CarState&, int direction, const Vehicle& vehicle=Vehicle{});
void stepCar(CarState&, const Vehicle&, const DriverInput&, double dt, double finishDistance=QuarterMile);
struct TrafficCar { double position, speed; int lane, appearance; };
struct FreeDrive {
    CarState player;
    Vehicle vehicle;
    std::array<TrafficCar,8> traffic;
    bool trafficEnabled=true;
    int targetLane=1, overtakes=0;
    double lane=1,lateralSpeed=0, collisionCooldown=0, time=0;
    unsigned int random=0x504352;
    FreeDrive();
    void setTraffic(bool enabled);
    void changeLane(int direction);
    void update(const DriverInput&,double dt);
    void respawn(TrafficCar&);
};
struct Race {
    CarState player, opponent;
    Vehicle vehicle, rivalVehicle;
    double countdown=3, time=0;
    bool result=false, newRecord=false;
    void update(const DriverInput&, double dt);
};
}
