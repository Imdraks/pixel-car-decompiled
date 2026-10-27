#pragma once
#include "model.hpp"
#include <algorithm>
#include <cmath>
namespace pcr {
// Stationary garage audition. Never advances the driving simulation or save data.
struct GarageEngine {
    bool running=false,limiting=false;
    CarState state{};
    GarageEngine(){stop();}
    void stop(){running=false;limiting=false;state=CarState{};state.rpm=0;}
    void toggle(const Vehicle& vehicle){
        if(running){stop();return;}
        running=true;limiting=false;state=CarState{};state.neutral=true;state.rpm=vehicle.idleRpm;
    }
    void update(const Vehicle& vehicle,bool throttle,double dt){
        if(!running||dt<=0||!std::isfinite(dt))return;
        state.elapsed+=dt;
        double ceiling=std::max(vehicle.idleRpm,vehicle.redlineRpm);
        state.rpm=std::clamp(state.rpm,vehicle.idleRpm,ceiling);
        double target=throttle?ceiling:vehicle.idleRpm;
        state.rpm+=std::clamp(target-state.rpm,-6500*dt,9000*dt);
        limiting=throttle&&state.rpm>=ceiling*.98;
        if(limiting)state.rpm=ceiling*(.985+.015*(.5+.5*std::sin(state.elapsed*62.831853)));
    }
};
}
