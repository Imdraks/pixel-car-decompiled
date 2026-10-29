#pragma once
#include "customization_data.hpp"
#include <algorithm>
#include <array>
#include <cstdint>
namespace pcr::materials {
struct Rgba {unsigned char r,g,b,a;};
inline Rgba unpack(unsigned color){return {static_cast<unsigned char>(color>>24),static_cast<unsigned char>(color>>16),static_cast<unsigned char>(color>>8),static_cast<unsigned char>(color)};}
inline int paintRow(Rgba color,int original){
    const auto& palette=original==2?undergroundPaint:original==1?originalPaint:unboundPaint;
    for(int row=0;row<11;row++){
        auto c=unpack(palette[0][row]);int r=int(color.r)-c.r,g=int(color.g)-c.g,b=int(color.b)-c.b,a=int(color.a)-c.a;
        // Source shader: Euclidean RGBA distance <= 0.004 in [0,1].
        if(r*r+g*g+b*b+a*a<=1)return row;
    }return -1;
}
inline Rgba paintPixel(Rgba color,int paint,int original,int paintSource=-1){
    int row=paintRow(color,original);if(row<0||paint<=0||paint>108)return color;
    int bank=paintSource<0?original:paintSource;return unpack((bank==2?undergroundPaint:bank==1?originalPaint:unboundPaint)[paint-1][row]);
}
inline bool glassPixel(Rgba c){return c.a>0&&c.a<255&&std::max({c.r,c.g,c.b})<40;}
inline Rgba glassTint(Rgba c,int tint){
    if(tint<=0||!glassPixel(c))return c;
    static constexpr Rgba colors[]={{0,0,0,255},{14,25,65,255},{185,155,35,255}};
    auto t=colors[std::clamp(tint-1,0,2)];c.r=(c.r+t.r)/2;c.g=(c.g+t.g)/2;c.b=(c.b+t.b)/2;
    c.a=static_cast<unsigned char>(c.a+(255-c.a)*.5);return c;
}
inline Rgba lightTint(Rgba c,int tint,bool tail=false){
    if(!c.a||tint<=0)return c;
    static constexpr double darkness[]={.2,.4,.7};
    if(tint<=3||tint==10){double k=1-(tint==10?.9:darkness[tint-1]);c.r=static_cast<unsigned char>(c.r*k);c.g=static_cast<unsigned char>(c.g*k);c.b=static_cast<unsigned char>(c.b*k);return c;}
    if(tail)return c;
    static constexpr Rgba colors[]={{255,225,50,255},{95,190,255,255},{170,95,255,255},{255,45,45,255},{65,255,95,255},{255,65,220,255}};
    auto t=colors[std::clamp(tint-4,0,5)];c.r=static_cast<unsigned char>(c.r*t.r/255);c.g=static_cast<unsigned char>(c.g*t.g/255);c.b=static_cast<unsigned char>(c.b*t.b/255);return c;
}
}
