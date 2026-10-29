#pragma once
#include "content_renderer.hpp"
#include <filesystem>
#include <fstream>
#include <cstdint>
namespace pcr {
inline void checkCustomization(const std::filesystem::path& assets,const std::filesystem::path& output){
    if(!std::filesystem::create_directory(output))throw std::runtime_error("L'audit de personnalisation exige un dossier neuf.");
    ContentRenderer renderer;int cases=0,unsupported=0,partial=0,renders=0,mounts=0,hoodCases=0,hoodFallbacks=0;
    std::ofstream details(output/"compatibility.csv"),hashes(output/"render-hashes.csv");
    details<<"bank,body,item,supported,partial\n";hashes<<"bank,body,style,rgba_fnv64\n";
    try{
        for(int i=0;i<content_art::AtlasCount;i++){
            auto path=(assets/("content-"+std::string(i<10?"0":"")+std::to_string(i)+".png")).u8string();
            Image image=LoadImage(path.c_str());if(!image.data)throw std::runtime_error("Atlas de personnalisation manquant.");
            ImageFormat(&image,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);renderer.pixels[2000+i]=image;
        }
        auto inside=[](double x,double y,const art::Frame& f){return x+f.dx>=0&&y+f.dy>=0&&x+f.dx+f.w<=materials::CanvasW&&y+f.dy+f.h<=materials::CanvasH;};
        for(int bank=0;bank<2;bank++){
            Image sheet{};int page=0;
            for(int body=0;body<191;body++){
                Profile base;base.car=body;base.contentSource=bank;bool original=bank==1;
                for(const auto& c:CosmeticCatalog){auto fit=cosmeticFit(base,c.id);++cases;unsupported+=!fit.supported;partial+=fit.partial;details<<bank<<','<<body<<','<<c.id<<','<<fit.supported<<','<<fit.partial<<'\n';}
                const auto& anchor=attachments::anchors(body,original);
                auto mounted=[&](const auto* frames,int count,double x,double y){
                    for(int n=1;n<count;n++){const auto& f=frames[n];if(!inside(x,y,f))throw std::runtime_error("Accessoire tronqué par le canevas.");++mounts;}
                };
                mounted(content_art::Racks(original),int(std::size(content_art::unboundRacks)),materials::CanvasX+62+anchor.roofX-60,materials::CanvasY+58+anchor.roofY-45);
                mounted(content_art::Hooks(original),int(std::size(content_art::unboundHooks)),materials::CanvasX+62+anchor.hookX-12,materials::CanvasY+58+anchor.hookY-13);
                mounted(content_art::Seats(original),int(std::size(content_art::unboundSeats)),materials::CanvasX+62+anchor.seatX-16,materials::CanvasY+58+anchor.seatY-16);
                for(int front=0;front<13;front++){
                    const auto& mount=materials::hoodMount(body,front,original);Image surface=renderer.image(content_art::Cars(original)[body]);
                    auto replacement=kitFrames(original,front,0);
                    if(front&&(front==2||(replacement&&replacement[body].w*replacement[body].h>1))){
                        Image mask=renderer.image(content_art::Front(original)[body]);auto dst=static_cast<Color*>(surface.data);auto px=static_cast<Color*>(mask.data);
                        for(int i=0;i<surface.width*surface.height;i++)if(px[i].a>128)dst[i]=BLANK;
                        UnloadImage(mask);if(replacement)renderer.overlayFrame(surface,replacement[body]);
                    }
                    auto contact=GetImageColor(surface,mount.x,mount.y);
                    if(!mount.fallback&&contact.a<200){UnloadImage(surface);throw std::runtime_error("Pied du pot de capot hors de sa surface.");}
                    for(int pipe=48;pipe<=50;pipe++){auto fit=placeExhaust(body,pipe,0,original,0,front);if(fit.count!=(pipe==50?3:1))throw std::runtime_error("Bouches de capot incorrectes.");++hoodCases;hoodFallbacks+=mount.fallback;}
                    UnloadImage(surface);
                }
                if(body%24==0){sheet=GenImageColor(1320,1140,Color{22,27,33,255});page=body/24;}
                for(int style=0;style<4;style++){
                    Profile p=base;
                    if(style){
                        p.cosmetics[0]=style==1?100085:style==2?100086:100050;
                        p.cosmetics[3]=103005;p.cosmetics[9]=109010;p.cosmetics[10]=110001;
                        p.cosmetics[12]=112002;p.cosmetics[13]=113005;p.cosmetics[14]=114003;p.cosmetics[15]=115002;p.rollCage=true;p.headlights=true;
                        if(style==3)p.cosmetics[1]=101005;
                        for(const auto& c:CosmeticCatalog)if(c.slot==2&&cosmeticFit(p,c.id).supported){p.cosmetics[2]=c.id;break;}
                        for(const auto& c:CosmeticCatalog)if(c.slot==4&&c.subimage!=2&&cosmeticFit(p,c.id).supported){p.cosmetics[4]=c.id;break;}
                    }
                    Image image=renderer.composeImage(p);
                    if(image.width!=materials::CanvasW||image.height!=materials::CanvasH)throw std::runtime_error("Dimensions du rendu incorrectes.");
                    const auto* pixels=static_cast<const unsigned char*>(image.data);std::uint64_t hash=1469598103934665603ull;int visible=0;
                    for(int i=0;i<image.width*image.height*4;i++){hash^=pixels[i];hash*=1099511628211ull;if(i%4==3&&pixels[i])++visible;}
                    if(visible<100)throw std::runtime_error("Carrosserie vide dans l'audit de rendu.");
                    hashes<<bank<<','<<body<<','<<style<<','<<hash<<'\n';++renders;
                    if(style==2){
                        int cell=body%24;ContentRenderer::overlay(sheet,image,float((cell%4)*330+15),float((cell/4)*190+8),1.3f);
                        // Small CPU-only digit labels avoid requiring an OpenGL font context.
                        static const char* digits[]={"111101101101111","010110010010111","111001111100111","111001111001111","101101111001001","111100111001111","111100111101111","111001001001001","111101111101111","111101111001111"};
                        std::string label=std::to_string(body+1);int dx=(cell%4)*330+10,dy=(cell/4)*190+174;
                        for(char ch:label){for(int y=0;y<5;y++)for(int x=0;x<3;x++)if(digits[ch-'0'][y*3+x]=='1')ImageDrawRectangle(&sheet,dx+x*2,dy+y*2,2,2,WHITE);dx+=9;}
                    }
                    UnloadImage(image);
                }
                if(body%24==23||body==190){auto name="cars-"+std::string(original?"original-":"unbound-")+std::to_string(page)+".png";if(!ExportImage(sheet,(output/name).u8string().c_str()))throw std::runtime_error("Export du contact impossible.");UnloadImage(sheet);}
            }
        }
        if(cases!=int(std::size(CosmeticCatalog))*382||renders!=1528||mounts!=27122||hoodCases!=14898)throw std::runtime_error("Couverture de personnalisation incomplète.");
        std::ofstream report(output/"customization-audit.json");report<<"{\n  \"body_banks_checked\": 382,\n  \"cosmetic_cases_checked\": "<<cases<<",\n  \"unsupported_choices\": "<<unsupported<<",\n  \"partial_choices\": "<<partial<<",\n  \"generic_mounts_checked\": "<<mounts<<",\n  \"full_body_renders\": "<<renders<<",\n  \"hood_cases_checked\": "<<hoodCases<<",\n  \"hood_fallback_cases\": "<<hoodFallbacks<<",\n  \"android_full_render_equivalence\": false\n}\n";
        renderer.clear();
    }catch(...){renderer.clear();throw;}
}
}
