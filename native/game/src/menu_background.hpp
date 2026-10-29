#pragma once
#include <algorithm>
namespace pcr {
struct BackgroundCrop { double x,y,width,height; };
// Centre-crop the source to cover the destination without stretching its pixels.
inline BackgroundCrop menuBackgroundCrop(double sw,double sh,double dw,double dh){
    sw=std::max(1.0,sw);sh=std::max(1.0,sh);dw=std::max(1.0,dw);dh=std::max(1.0,dh);
    double scale=std::max(dw/sw,dh/sh),w=dw/scale,h=dh/scale;
    return {(sw-w)*.5,(sh-h)*.5,w,h};
}
}
