#pragma once
#include "art.hpp"
#include "exhaust_anchors.hpp"
#include "attachment_anchors.hpp"
#include "attachment_surfaces.hpp"
#include "exhaust_rules.hpp"
#include <algorithm>
#include <array>
namespace pcr {
using Outlet=art::Outlet;
struct ExhaustPlacement { double x=0,y=0;int frame=0,count=1;bool front=false;std::array<Outlet,3> outlets{}; };
inline ExhaustPlacement placeExhaust(int body,int pipe,double rideOffset=0,bool original=false,int /*rearKit*/=0,int /*sideKit*/=0){
    body=std::clamp(body,0,int(std::size(art::bodyExhaustMounts))-1);
    pipe=std::clamp(pipe,0,int(std::size(art::pipeLayouts))-1);
    const auto& anchor=attachments::anchors(body,original);const auto& layout=art::pipeLayouts[pipe];
    const auto& surface=original?attachments::originalSurfaces[body]:attachments::unboundSurfaces[body];
    const int type=attachments::exhaustTypes[pipe];
    ExhaustPlacement p;p.frame=pipe;p.count=layout.count;
    // Source Draw_0 draws types 2/3 before the body at part_exhaust_x/y,
    // and types 1/4 after the body at part_exhaust2_x/y. Both use (40,62).
    // Neither branch adds a body-kit offset: that displaced side pipes twice.
    p.front=type==1||type==4;
    double x=62+(p.front?anchor.exhaust2X:anchor.exhaustX)-40;
    double y=58+(p.front?anchor.exhaust2Y:anchor.exhaustY)-62;
    // Type 0 hood pipes have no draw in those source branches. Keep the native
    // hood adaptation separate; never reuse its surface fit for a side pipe.
    if(type==0){x=surface.hoodX-layout.baseX;y=surface.hoodY-layout.baseY;p.front=true;}
    p.x=x;p.y=y+rideOffset;
    for(int i=0;i<p.count;i++){auto o=layout.outlets[i];o.x+=p.x;o.y+=p.y;p.outlets[i]=o;}
    return p;
}
}
