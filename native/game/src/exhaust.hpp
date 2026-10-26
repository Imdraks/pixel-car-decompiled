#pragma once
#include "art.hpp"
#include "exhaust_anchors.hpp"
#include <algorithm>
#include <array>
namespace pcr {
using Outlet=art::Outlet;
struct ExhaustPlacement { double x=0,y=0;int frame=0,count=1;bool front=false;std::array<Outlet,3> outlets{}; };
inline ExhaustPlacement placeExhaust(int body,int pipe,double rideOffset=0){
    body=std::clamp(body,0,int(std::size(art::bodyExhaustMounts))-1);
    pipe=std::clamp(pipe,0,int(std::size(art::pipeLayouts))-1);
    const auto& mount=art::bodyExhaustMounts[body];const auto& layout=art::pipeLayouts[pipe];
    ExhaustPlacement p;p.frame=pipe;p.count=layout.count;p.front=layout.mount==2;
    double x=mount.rearX-3,y=mount.rearY;
    if(layout.mount==1){x=mount.hoodX;y=mount.hoodY;}
    if(layout.mount==2){x=mount.sideX;y=mount.sideY;}
    if(layout.mount==3)x=mount.rearX+8;
    p.x=x-layout.baseX;p.y=y+rideOffset-layout.baseY;
    for(int i=0;i<p.count;i++){auto o=layout.outlets[i];o.x+=p.x;o.y+=p.y;p.outlets[i]=o;}
    return p;
}
}
