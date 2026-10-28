#pragma once
#include "model.hpp"
#include <algorithm>
#include <cmath>
namespace pcr {
// Equivalent audio control only: a stationary audition never creates driving boost.
inline double garageInductionAudio(const Vehicle& vehicle,double rpm,double load){
    double nominal=std::max(vehicle.boostPsi,vehicle.factoryBoostSoundPsi);
    if(nominal<=0||rpm<=0)return 0;
    double revs=std::clamp((rpm-vehicle.idleRpm)/std::max(1.0,vehicle.redlineRpm-vehicle.idleRpm),0.0,1.0);
    return nominal*(.08+.22*std::sqrt(revs)+.45*std::clamp(load,0.0,1.0)*revs);
}
}
