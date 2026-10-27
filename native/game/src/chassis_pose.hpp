#pragma once
#include "model.hpp"
#include <cmath>
#include <algorithm>
namespace pcr {
struct ChassisPoint { double x,y; };
// Convert the physical pitch/heave into the car sprite's local coordinate space.
// Wheels stay on their contact plane until the suspension reaches full droop.
struct ChassisPose {
    double pivotX,pivotY,pixelsPerMetre,pitch,heave,frontLift,rearLift,rear,front,wheelY,rideOffset;
    ChassisPoint body(double x,double y)const{
        double c=std::cos(pitch),s=std::sin(pitch),dx=x-pivotX,dy=y-pivotY;
        return {pivotX+c*dx+s*dy,pivotY-s*dx+c*dy-heave*pixelsPerMetre};
    }
    ChassisPoint wheel(bool atFront)const{
        auto hub=body(atFront?front:rear,wheelY+rideOffset);
        double targetY=wheelY-(atFront?frontLift:rearLift)*pixelsPerMetre;
        // Suspension travel follows the strut attached to this wheel arch.
        // Projecting onto the body vertical preserves the hub's local X,
        // including CG rotation and ride-height offsets during a wheelie.
        double extension=(targetY-hub.y)/std::max(.1,std::cos(pitch));
        return {hub.x+std::sin(pitch)*extension,targetY};
    }
};
inline ChassisPose chassisPose(double rear,double front,double wheelY,const Vehicle& v,const CarState& s,double rideOffset=0){
    double ppm=std::max(1.0,front-rear)/v.wheelbase;
    return {rear+(front-rear)*v.frontWeightFraction,wheelY-v.centreOfGravityHeight*ppm,ppm,s.pitch,s.heave,s.frontLift,s.rearLift,rear,front,wheelY,rideOffset};
}
}
