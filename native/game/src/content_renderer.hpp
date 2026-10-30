#pragma once
#include "model.hpp"
#include "rlgl.h"
#include "content_art.hpp"
#include "attachment_placement.hpp"
#include "cosmetic_geometry.hpp"
#include "materials.hpp"
#include "raylib.h"
#include <map>
#include <sstream>
namespace pcr {
inline const art::Frame& equippedRim(int id,int original){auto r=findRim(id);return r?content_art::Rims(r->imageSource>=0?r->imageSource:original)[r->image]:art::rims[validRimFrame(id)];}
inline art::Wheels bodyWheels(int car,int original){const float* a=original==2?content_art::undergroundAnchors[car]:original==1?content_art::originalAnchors[car]:content_art::unboundAnchors[car];return {a[0],a[1],a[2],a[3]};}
inline art::Wheels bodyWheels(const Profile& p){auto wheels=bodyWheels(p.car,p.contentSource);float front=VehicleCatalog[bodyChoiceIndex(p)].wheelFront;if(front>0)wheels.front=front;return wheels;}
class ContentRenderer {
public:
    std::map<int,Image> pixels;Texture2D body{};Rectangle bodyBounds{};std::string key;std::map<std::string,Texture2D> thumbnails;
    Image image(const art::Frame& f)const{
        Image out=GenImageColor(f.canvasW,f.canvasH,BLANK);auto at=pixels.find(f.atlas);
        if(at!=pixels.end())ImageDrawImagePro(&out,at->second,{float(f.x),float(f.y),float(f.w),float(f.h)},{float(f.dx),float(f.dy),float(f.w),float(f.h)},{0,0},0,WHITE);
        return out;
    }
    static void overlay(Image& dest,const Image& src,float x=0,float y=0,float scale=1,Color color=WHITE){ImageDrawImagePro(&dest,src,{0,0,float(src.width),float(src.height)},{x,y,src.width*scale,src.height*scale},{0,0},0,color);}
    void overlayFrame(Image& dest,const art::Frame& f,float x=0,float y=0,float scale=1,Color color=WHITE){Image im=image(f);overlay(dest,im,x,y,scale,color);UnloadImage(im);}
    void materialize(Image& im,const Profile& p,bool wrapEnabled=true,bool glassEnabled=true){
        int original=p.contentSource;int paint=cosmeticSubimage(p,0),wrap=wrapEnabled?cosmeticSubimage(p,1):0,tint=cosmeticSubimage(p,12);
        Image decal{};if(wrap){auto c=findCosmetic(p.cosmetics[1]);decal=image(content_art::Wraps(c&&c->imageSource>=0?c->imageSource:original)[wrap]);}auto wp=static_cast<Color*>(decal.data);auto px=static_cast<Color*>(im.data);
        for(int y=0;y<im.height;y++)for(int x=0;x<im.width;x++){
            auto& c=px[y*im.width+x];materials::Rgba source{c.r,c.g,c.b,c.a};int row=materials::paintRow(source,original);
            auto result=materials::paintPixel(source,paint,original,findCosmetic(p.cosmetics[0])&&findCosmetic(p.cosmetics[0])->imageSource>=0?findCosmetic(p.cosmetics[0])->imageSource:original);
            if(row>=0&&wp&&x<decal.width&&y<decal.height){
                auto over=wp[y*decal.width+x];double alpha=over.a/255.,gray=(source.r+source.g+source.b)/255.;
                result.r=static_cast<unsigned char>(std::clamp(result.r*(1-alpha)+over.r*gray*alpha,0.,255.));
                result.g=static_cast<unsigned char>(std::clamp(result.g*(1-alpha)+over.g*gray*alpha,0.,255.));
                result.b=static_cast<unsigned char>(std::clamp(result.b*(1-alpha)+over.b*gray*alpha,0.,255.));
            }
            if(glassEnabled&&y<49)result=materials::glassTint(result,tint);
            c={result.r,result.g,result.b,result.a};
        }
        if(decal.data)UnloadImage(decal);
    }
    Image composeImage(const Profile& p){
        int original=p.contentSource;const auto& anchor=attachments::anchors(p.car,original==1);
        Image im=image(content_art::Cars(original)[p.car]);int kit=cosmeticSubimage(p,4);
        int baseKit=VehicleCatalog[bodyChoiceIndex(p)].baseKit;
        auto applyPanel=[&](int part,int side){
            if(!part)return;
            const auto* replacement=kitFrames(original,part,side);
            if(part!=2&&(!replacement||replacement[p.car].w*replacement[p.car].h<=1))return;
            if(side<2){Image mask=image((side==0?content_art::Front(original):content_art::Rear(original))[p.car]);auto out=static_cast<Color*>(im.data);auto m=static_cast<Color*>(mask.data);for(int i=0;i<im.width*im.height;i++)if(m[i].a>128)out[i]=BLANK;UnloadImage(mask);}
            if(replacement)overlayFrame(im,replacement[p.car]);
        };
        if(baseKit)for(int side=0;side<3;side++)applyPanel(baseKit,side);
        for(int side=0;side<3;side++){
            int part=cosmeticSubimage(p,5+side);if(!part)part=kit;
            // A named conversion keeps its own body even if an old or edited
            // save contains a kit belonging to another model in the source slot.
            if(baseKit)continue;
            applyPanel(part,side);
        }
        // Palette/material operations happen on the body, never on the seats or cage.
        materialize(im,p);
        Image interior=GenImageColor(220,70,BLANK);
        if(p.rollCage)overlayFrame(interior,content_art::Rollcages(original)[p.car]);
        int seat=cosmeticSubimage(p,9);const auto* seatItem=findCosmetic(p.cosmetics[9]);int originalSeat=seatItem&&seatItem->imageSource>=0?seatItem->imageSource:original;
        if(seat)overlayFrame(interior,content_art::Seats(originalSeat)[seat],62+anchor.seatX-16,58+anchor.seatY-16);
        overlay(interior,im);UnloadImage(im);im=interior;
        int head=cosmeticSubimage(p,13),tail=cosmeticSubimage(p,14),bulb=cosmeticSubimage(p,15);
        int frontKit=installedKit(p,0),rearKit=installedKit(p,1);
        auto headFor=[&](int bank){
            const auto* frames=p.headlights?content_art::HeadlightsNeo(bank):content_art::Headlights(bank);
            if(frontKit==7)frames=content_art::HeadlightsFortune(bank);
            if(frontKit==11)frames=content_art::HeadlightsDrag(bank);
            if(frontKit==12)frames=content_art::HeadlightsTuner(bank);
            return frames;
        };
        auto tailFor=[&](int bank){return rearKit==7?content_art::TaillightsFortune(bank):rearKit==12?content_art::TaillightsTuner(bank):content_art::Taillights(bank);};
        const auto* headFrames=headFor(original);const auto* tailFrames=tailFor(original);
        auto lights=[&](const art::Frame& frame,int tint,bool isTail){
            Image layer=image(frame);auto px=static_cast<Color*>(layer.data);
            for(int i=0;i<layer.width*layer.height;i++){
                materials::Rgba c{px[i].r,px[i].g,px[i].b,px[i].a};
                if(!isTail&&p.headlights){
                    if(bulb==2){c.r=static_cast<unsigned char>(c.r*.65);c.g=static_cast<unsigned char>(c.g*.85);}
                    if(bulb==3){c.g=static_cast<unsigned char>(c.g*.88);c.b=static_cast<unsigned char>(c.b*.4);}
                }
                c=materials::lightTint(c,tint,isTail);px[i]={c.r,c.g,c.b,c.a};
            }overlay(im,layer);UnloadImage(layer);
        };
        // Named conversions already contain their correct lamp artwork. The
        // base slot's separate masks belong to a different car silhouette.
        auto sameFrame=[](const art::Frame& a,const art::Frame& b){return a.atlas==b.atlas&&a.x==b.x&&a.y==b.y&&a.w==b.w&&a.h==b.h&&a.dx==b.dx&&a.dy==b.dy&&a.canvasW==b.canvasW&&a.canvasH==b.canvasH;};
        bool legacy=VehicleCatalog[bodyChoiceIndex(p)].legacyLampMasks;
        if(!baseKit){
            if(!legacy||!sameFrame(headFrames[p.car],headFor(1)[p.car]))lights(headFrames[p.car],head,false);
            if(!legacy||!sameFrame(tailFrames[p.car],tailFor(1)[p.car]))lights(tailFrames[p.car],tail,true);
        }
        int spoiler=cosmeticSubimage(p,2);
        if(auto frames=spoilerFrames(original,spoiler)){Image layer=image(frames[p.car]);materialize(layer,p,true,false);overlay(im,layer);UnloadImage(layer);}
        Image expanded=GenImageColor(materials::CanvasW,materials::CanvasH,BLANK);
        overlay(expanded,im,materials::CanvasX,materials::CanvasY);UnloadImage(im);im=expanded;
        int rack=cosmeticSubimage(p,3);if(rack)overlayFrame(im,content_art::Racks(findCosmetic(p.cosmetics[3])->imageSource>=0?findCosmetic(p.cosmetics[3])->imageSource:original)[rack],materials::CanvasX+62+anchor.roofX-60,materials::CanvasY+58+anchor.roofY-45);
        int hook=cosmeticSubimage(p,10);if(hook)overlayFrame(im,content_art::Hooks(findCosmetic(p.cosmetics[10])->imageSource>=0?findCosmetic(p.cosmetics[10])->imageSource:original)[hook],materials::CanvasX+62+anchor.hookX-12,materials::CanvasY+58+anchor.hookY-13);
        return im;
    }
    Texture2D compose(const Profile& p){
        std::ostringstream id;id<<p.car<<':'<<p.contentSource<<':'<<p.visualVariant<<':'<<p.rollCage<<':'<<p.headlights;for(int c:p.cosmetics)id<<':'<<c;
        if(body.id&&key==id.str())return body;
        key=id.str();Image im=composeImage(p);bodyBounds=GetImageAlphaBorder(im,.01f);
        if(body.id){rlDrawRenderBatchActive();UnloadTexture(body);}
        body=LoadTextureFromImage(im);SetTextureFilter(body,TEXTURE_FILTER_POINT);UnloadImage(im);return body;
    }
    Texture2D thumbnail(const Profile& p){
        std::ostringstream id;id<<p.car<<':'<<p.contentSource<<':'<<p.visualVariant<<':'<<p.rollCage<<':'<<p.headlights;for(int c:p.cosmetics)id<<':'<<c;
        auto name=id.str();auto at=thumbnails.find(name);if(at!=thumbnails.end())return at->second;
        if(thumbnails.size()>=16){rlDrawRenderBatchActive();auto old=thumbnails.begin();UnloadTexture(old->second);thumbnails.erase(old);}
        Image im=composeImage(p);auto texture=LoadTextureFromImage(im);SetTextureFilter(texture,TEXTURE_FILTER_POINT);UnloadImage(im);thumbnails[name]=texture;return texture;
    }
    void clear(){if(body.id)UnloadTexture(body);for(auto& entry:thumbnails)UnloadTexture(entry.second);thumbnails.clear();
        body={};for(auto& entry:pixels)UnloadImage(entry.second);pixels.clear();}
};
}
