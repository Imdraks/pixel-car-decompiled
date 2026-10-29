#pragma once
#include "model.hpp"
#include "content_art.hpp"
namespace pcr {
inline const art::Frame* kitFrames(int original,int id,int side){
#define KIT(ID,SIDE) case ID:return side==0?content_art::Kit_##ID##_front(original):side==1?content_art::Kit_##ID##_rear(original):content_art::Kit_##ID##_side(original);
    // Only source-backed combinations are returned; blank/delete remains blank.
    if(side==0){switch(id){case 1:return content_art::Kit_1_front(original);case 3:return content_art::Kit_3_front(original);case 4:return content_art::Kit_4_front(original);case 5:return content_art::Kit_5_front(original);case 6:return content_art::Kit_6_front(original);case 7:return content_art::Kit_7_front(original);case 8:return content_art::Kit_8_front(original);case 9:return content_art::Kit_9_front(original);case 10:return content_art::Kit_10_front(original);case 11:return content_art::Kit_11_front(original);case 12:return content_art::Kit_12_front(original);}}
    if(side==1){switch(id){case 1:return content_art::Kit_1_rear(original);case 3:return content_art::Kit_3_rear(original);case 5:return content_art::Kit_5_rear(original);case 6:return content_art::Kit_6_rear(original);case 7:return content_art::Kit_7_rear(original);case 9:return content_art::Kit_9_rear(original);case 10:return content_art::Kit_10_rear(original);case 11:return content_art::Kit_11_rear(original);case 12:return content_art::Kit_12_rear(original);}}
    if(side==2){switch(id){case 1:return content_art::Kit_1_side(original);case 3:return content_art::Kit_3_side(original);case 4:return content_art::Kit_4_side(original);case 6:return content_art::Kit_6_side(original);case 7:return content_art::Kit_7_side(original);case 8:return content_art::Kit_8_side(original);case 12:return content_art::Kit_12_side(original);}}
#undef KIT
    return nullptr;
}
inline const art::Frame* spoilerFrames(int original,int id){
#define SPOILER(ID,NAME) case ID:return content_art::Spoiler_##NAME(original);
    switch(id){SPOILER(1,6666) SPOILER(2,stock) SPOILER(3,universal) SPOILER(4,duck) SPOILER(5,drag) SPOILER(6,new) SPOILER(7,carbongt) SPOILER(8,demolisher) SPOILER(9,esp) SPOILER(10,gt) SPOILER(11,bfw) SPOILER(12,street) SPOILER(13,gta) SPOILER(14,360) SPOILER(15,xtreme) SPOILER(16,fg500) SPOILER(17,demolisherV2) SPOILER(18,demolisherV3) SPOILER(19,pro1) SPOILER(20,pro2) SPOILER(21,pro3) SPOILER(22,BCLpaint) SPOILER(23,1850L) SPOILER(24,1850S) SPOILER(25,banshee) SPOILER(26,samurai) SPOILER(27,326)}return nullptr;
#undef SPOILER
}
struct CosmeticFit {bool supported=true,partial=false;};
inline CosmeticFit cosmeticFit(const Profile& p,int id){
    const auto* c=findCosmetic(id);if(!c)return {};
    int original=p.contentSource;int part=c->subimage;
    if(c->slot==2){auto frames=spoilerFrames(original,part);return {frames&&frames[p.car].w*frames[p.car].h>1,false};}
    if(c->slot>=4&&c->slot<=7){
        if(part==2)return {};
        int available=0,requested=c->slot==4?3:1;
        for(int side=0;side<3;side++)if(c->slot==4||side==c->slot-5){auto frames=kitFrames(original,part,side);available+=frames&&frames[p.car].w*frames[p.car].h>1;}
        return {available>0,available>0&&available<requested};
    }
    return {};
}
}
