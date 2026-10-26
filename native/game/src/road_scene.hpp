#pragma once
#include <cmath>
namespace pcr::scene {
// Logical 1280x720 canvas. A typical 2.6 m wheelbase spans about 125 px.
// All ground objects share this scale, regardless of render size or quality.
inline constexpr double PixelsPerMetre=48;
inline constexpr double Mountains=.035, City=.16, Trees=.55;
inline constexpr double MarkSpacingMetres=12, MarkLengthMetres=4;
inline double pixels(double metres){return metres*PixelsPerMetre;}
inline double wrap(double value,double period){return value-std::floor(value/period)*period;}
inline double layerTravel(double distance,double depth=1){return pixels(distance)*depth;}
inline double roadPhase(double distance){return wrap(pixels(distance),pixels(MarkSpacingMetres));}
inline double trafficX(double position,double cameraPosition){return 360+pixels(position-cameraPosition);}
inline double wheelAngle(double distance,double radius){return wrap(distance/radius*180/3.14159265358979323846,360);}
}
