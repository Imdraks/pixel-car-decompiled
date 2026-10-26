#pragma once
#include "art.hpp"
#include "exhaust_anchors.hpp"
#include "attachment_anchors.hpp"
#include "attachment_surfaces.hpp"
#include <algorithm>
#include <array>
namespace pcr {
using Outlet=art::Outlet;
struct ExhaustPlacement { double x=0,y=0;int frame=0,count=1;bool front=false;std::array<Outlet,3> outlets{}; };
inline ExhaustPlacement placeExhaust(int body,int pipe,double rideOffset=0,bool original=false,int rearKit=0,int sideKit=0){
    body=std::clamp(body,0,int(std::size(art::bodyExhaustMounts))-1);
    pipe=std::clamp(pipe,0,int(std::size(art::pipeLayouts))-1);
    const auto& anchor=attachments::anchors(body,original);const auto& layout=art::pipeLayouts[pipe];
    const auto& surface=original?attachments::originalSurfaces[body]:attachments::unboundSurfaces[body];
    ExhaustPlacement p;p.frame=pipe;p.count=layout.count;p.front=true;
    // Ordinary/vertical pipes use the recovered source position and sprite origin.
    // Hood and side modifications retain native fitting to their actual body surface.
    double x=62+anchor.exhaustX-40,y=58+anchor.exhaustY-62;
    if(layout.mount==1){x=surface.hoodX-layout.baseX;y=surface.hoodY-layout.baseY;}
    else if(layout.mount==2){
        double sill=surface.sideY;sideKit=std::clamp(sideKit,0,12);
        sill=std::max(sill,double(original?attachments::originalSideFit[body][sideKit]:attachments::unboundSideFit[body][sideKit]));
        x=surface.sideX-layout.baseX;y=sill-layout.baseY;
    }else{
        rearKit=std::clamp(rearKit,0,12);const auto& offset=original?attachments::originalRearFit[body][rearKit]:attachments::unboundRearFit[body][rearKit];x+=offset[0];y+=offset[1];
    }
    p.x=x;p.y=y+rideOffset;
    for(int i=0;i<p.count;i++){auto o=layout.outlets[i];o.x+=p.x;o.y+=p.y;p.outlets[i]=o;}
    return p;
}
}
