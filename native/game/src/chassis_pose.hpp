#pragma once
#include "model.hpp"
#include <cmath>
#include <algorithm>
namespace pcr {
struct ChassisPoint { double x,y; };
// Convert the physical pitch/heave into the car sprite's local coordinate space.
// Wheels stay on their contact plane until the suspension reaches full droop.
struct ChassisPose {
    double pivotX,pivotY,pixelsPerMetre,pitch,heave,frontLift,rearLift,rear,front,wheelY;
    ChassisPoint body(double x,double y)const{
        double c=std::cos(pitch),s=std::sin(pitch),dx=x-pivotX,dy=y-pivotY;
        return {pivotX+c*dx+s*dy,pivotY-s*dx+c*dy-heave*pixelsPerMetre};
    }
    ChassisPoint wheel(bool atFront)const{
        double liftAngle=std::atan2(frontLift-rearLift,(front-rear)/pixelsPerMetre);
        return {atFront?rear+(front-rear)*std::cos(liftAngle):rear,wheelY-(atFront?frontLift:rearLift)*pixelsPerMetre};
    }
};
inline ChassisPose chassisPose(double rear,double front,double wheelY,const Vehicle& v,const CarState& s){
    double ppm=std::max(1.0,front-rear)/v.wheelbase;
    return {rear+(front-rear)*v.frontWeightFraction,wheelY-v.centreOfGravityHeight*ppm,ppm,s.pitch,s.heave,s.frontLift,s.rearLift,rear,front,wheelY};
}
}
