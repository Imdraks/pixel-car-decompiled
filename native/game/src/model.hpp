#pragma once
#include <filesystem>
#include <string>
#include <vector>
#include <array>

namespace pcr {
enum class WindowMode { Windowed, Borderless, Fullscreen };
enum class Quality { Low, Medium, High };
struct Resolution { int width, height; bool operator==(const Resolution& r) const {return width==r.width && height==r.height;} };
struct Settings {
    WindowMode mode=WindowMode::Windowed;
    int width=1280, height=720, fps=120;
    bool vsync=true, showFps=false, sound=true;
    Quality quality=Quality::High;
};
struct Profile { int car=0, rim=0; double bestTime=0; bool automatic=true; };
bool operator==(const Settings&, const Settings&);
Settings validate(Settings);
Settings loadSettings(const std::filesystem::path&);
Profile loadProfile(const std::filesystem::path&, int carCount, int rimCount);
bool saveSettings(const std::filesystem::path&, const Settings&, std::string& error);
bool saveProfile(const std::filesystem::path&, const Profile&, std::string& error);
const char* modeKey(WindowMode);
double easeLinear(double t, double b, double c, double d);

// New native simulation. These parameters are not recovered original vehicle data.
struct Vehicle {
    double mass=1240, torque=345, wheelRadius=.32, finalDrive=3.9;
    double ratios[6]={3.15,2.10,1.55,1.22,1.0,.82};
    // SI units; provisional calibration, not recovered GameMaker constants.
    double idleRpm=1000, launchRpm=2800, upshiftRpm=7100, redlineRpm=8100;
    double shiftSeconds=.15, efficiency=.87, grip=1.08;
    double dragArea=.67, rollingResistance=.014, brakeDeceleration=8.5;
    double engineBrakeTorque=18;
};
struct DriverInput { bool throttle=false, brake=false, automatic=true; };
struct CarState {
    double position=0, speed=0, rpm=1000, elapsed=0, finishTime=0, shiftLock=0;
    int gear=1;
    bool finished=false;
};
constexpr double Step=1.0/120.0, QuarterMile=402.336;
bool shift(CarState&, int direction, const Vehicle& vehicle=Vehicle{});
void stepCar(CarState&, const Vehicle&, const DriverInput&, double dt, double finishDistance=QuarterMile);
struct TrafficCar { double position, speed; int lane, appearance; };
struct FreeDrive {
    CarState player;
    Vehicle vehicle;
    std::array<TrafficCar,8> traffic;
    int targetLane=1, overtakes=0;
    double lane=1, collisionCooldown=0, time=0;
    unsigned int random=0x504352;
    FreeDrive();
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
