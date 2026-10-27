#include "raylib.h"
#include "rlgl.h"
#include "model.hpp"
#include "benchmark.hpp"
#include "game_audio.hpp"
#include "effects.hpp"
#include "road_scene.hpp"
#include "platform.hpp"
#include "art.hpp"
#include "original_ui.hpp"
#include "content_renderer.hpp"
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>

namespace fs=std::filesystem;
using namespace pcr;
// Raylib owns this GLFW window. Use its public backend entry points to request
// an actual exclusive video mode; Raylib 6.2 ToggleFullscreen uses desktop size.
struct GLFWwindow;
struct GLFWmonitor;
extern "C" GLFWwindow* glfwGetCurrentContext(void);
extern "C" GLFWmonitor* glfwGetWindowMonitor(GLFWwindow*);
extern "C" void glfwSetWindowMonitor(GLFWwindow*,GLFWmonitor*,int,int,int,int,int);
constexpr Color Ink{10,15,23,255}, Panel{18,27,39,245}, Muted{153,173,190,255}, Accent{75,230,190,255}, Gold{255,191,88,255};
struct Args {
    fs::path data=fs::u8path(defaultDataDirectory()),assets,capture,benchmark,audioCheck;
    bool smoke=false,safe=false,free=false,noAudio=false,dataSpecified=false;
};
struct App {
    enum class Screen { Menu, Garage, Free, Customization, Transmission } screen=Screen::Menu;
    Args args;
    Settings settings,edited,previous;
    Resolution windowLimit{1280,720};
    Profile profile,transmissionDraft; Build configuration;
    bool inventoryOpen=false,searchFocused=false,searchSelectedAll=false,rimPicker=false,cosmeticPicker=false;int cosmeticSlot=0;int customGroup=0,lastCardId=-1;double lastCardClick=-10;std::string tooltipText;
    PartSlot customSlot=PartSlot::Engine; int customPreview=0,customPage=0; std::string customSearch;
    FreeDrive drive;DrivingEffects effects;
    Font font{};std::map<int,Texture2D> atlases;RenderTexture2D render{};
    ContentRenderer content;
    GameAudio audio; bool powerPopup=false,rarityDescending=false; bool audioPopup=false,previewGas=true;double audioPreviewUntil=0;
    Vector2 mouse{-100,-100};bool uiEnabled=true,options=false,paused=false,confirming=false,quit=false;
    double deadline=0,accumulator=0;int garageStyle=0;std::string notice;
    std::function<void()> queued;
    int frames=0;bool smokePassed=true,capMeasuring=false;double capStarted=0,capElapsed=0;
    std::vector<std::string> smokeChecks;
    explicit App(Args a):args(std::move(a)){}
    fs::path settingFile()const{return args.data/"settings.ini";}
    fs::path profileFile()const{return args.data/"profile.ini";}
    std::string asset(const std::string& name)const{return (args.assets/name).u8string();}
    void text(const std::string& value,float x,float y,float size=22,Color color=WHITE){DrawTextEx(font,value.c_str(),{x,y},size,0,color);}
    static int glyphIndex(int cp){if(cp>=32&&cp<128)return cp-32;if(cp>=192&&cp<=255)return cp-64;return -1;}
    float pxWidth(const std::string& value,float size)const{
        float width=0,scale=size/12;for(int offset=0;offset<int(value.size());){int bytes=0,cp=GetCodepointNext(value.c_str()+offset,&bytes);offset+=std::max(1,bytes);int index=glyphIndex(cp);
            width+=cp==32?5*scale:index>=0?(original_ui::glyphs[index].dx+original_ui::glyphs[index].w+2)*scale:size*.7f;
        }return width;
    }
    void pxText(const std::string& value,float x,float y,float size=20,Color color=WHITE){
        float scale=size/12;
        for(int offset=0;offset<int(value.size());){int bytes=0,cp=GetCodepointNext(value.c_str()+offset,&bytes);offset+=std::max(1,bytes);
            if(cp==32){x+=5*scale;continue;}int index=glyphIndex(cp);
            if(index>=0){const auto& f=original_ui::glyphs[index];frame(f,x,y-3*scale,scale,color);x+=(f.dx+f.w+2)*scale;}
            else{std::string fallback=value.substr(offset-bytes,bytes);text(fallback,x,y,size,color);x+=size*.7f;}
        }
    }
    void pxRight(const std::string& value,float right,float y,float size=20,Color color=WHITE){pxText(value,right-pxWidth(value,size),y,size,color);}
    void card(Rectangle r,Color color=Panel){
        DrawRectangleRec(r,color);DrawRectangleLinesEx(r,2,Color{5,5,8,245});
        DrawLine(int(r.x+2),int(r.y+2),int(r.x+r.width-2),int(r.y+2),Color{92,93,100,180});
    }
    bool hit(Rectangle r)const{return uiEnabled&&CheckCollisionPointRec(mouse,r);}
    bool button(Rectangle r,const std::string& label,bool primary=false,bool enabled=true){
        bool hover=enabled&&hit(r);Color fill=primary?Accent:Color{31,45,61,255};
        if(hover)fill=primary?Color{121,247,213,255}:Color{48,66,84,255};
        if(!enabled)fill=Color{31,38,46,255};
        DrawRectangleRec({r.x+2,r.y+3,r.width,r.height},Color{4,4,7,245});DrawRectangleRec(r,fill);DrawRectangleLinesEx(r,2,Color{8,8,12,255});
        DrawLine(int(r.x+2),int(r.y+2),int(r.x+r.width-2),int(r.y+2),hover?WHITE:Color{108,109,119,255});
        float size=20;while(size>10&&pxWidth(label,size)>r.width-14)size-=1;
        float width=pxWidth(label,size);pxText(label,r.x+(r.width-width)/2,r.y+(r.height-size*.85f)/2,size,enabled?(primary?Ink:WHITE):Muted);
        bool clicked=enabled&&hover&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT);if(clicked)audio.click(settings.sound);return clicked;
    }
    void frame(const art::Frame& f,float x,float y,float scale=1,Color tint=WHITE){
        if(f.atlas<0)return;
        DrawTexturePro(atlases.at(f.atlas),{float(f.x),float(f.y),float(f.w),float(f.h)},
          {x+f.dx*scale,y+f.dy*scale,f.w*scale,f.h*scale},{0,0},0,tint);
    }
    void crop(const art::Frame& f,Rectangle destination,Color tint=WHITE){
        DrawTexturePro(atlases.at(f.atlas),{float(f.x),float(f.y),float(f.w),float(f.h)},destination,{0,0},0,tint);
    }
    void tiled(const art::Frame& f,float y,float height,double offset,Color tint=WHITE){
        float w=height*f.w/f.h;float start=-float(std::fmod(offset,w));
        for(float x=start-w;x<1280;x+=w)crop(f,{x,y,w,height},tint);
    }
    void car(int index,int rim,float x,float y,float scale,double wheelAngle,bool shadow=true,int tireFrame=0,double rideOffset=0,int exhaustFrame=-1,double rearAngle=-1,const Profile* outfit=nullptr){
        index=(index+191)%191;rim=validRimFrame(rim);bool original=(outfit?outfit->contentSource:profile.contentSource)==1;auto w=bodyWheels(index,original);tireFrame=std::clamp(tireFrame,0,int(std::size(art::tires))-1);
        if(shadow&&settings.quality!=Quality::Low)DrawEllipse(int(x+110*scale),int(y+(w.y+w.radius)*scale),int(87*scale),int(6*scale),Fade(BLACK,.35f));
        // Draw the body last: opaque fenders and skirts must cover the tyres.
        // All cropped wheel sprites use their original 62x62 canvas and origin.
        if(w.radius>0)for(float cx:{w.rear,w.front}){
            Vector2 center{x+cx*scale,y+w.y*scale};
            auto centered=[&](const art::Frame& f,float factor,float ox,float oy,float angle){
                DrawTexturePro(atlases.at(f.atlas),{float(f.x),float(f.y),float(f.w),float(f.h)},
                    {center.x,center.y,f.w*factor,f.h*factor},
                    {(ox-f.dx)*factor,(oy-f.dy)*factor},angle,WHITE);
            };
            centered(art::wheelWells[0],scale,20,36-float(rideOffset),0);
            DrawCircleV(center,w.radius*.78f*scale,Color{12,13,18,255});
            float wheelScale=scale*(w.radius/25.f);
            double angle=cx==w.rear&&rearAngle>=0?rearAngle:wheelAngle;
            centered(content_art::Tires(original)[tireFrame],wheelScale,31,31,float(angle));
            if(outfit){int brake=cosmeticSubimage(*outfit,8);if(brake)centered(content_art::Brakes(original)[brake],wheelScale,31,31,0);}
            centered(equippedRim(rim,original),wheelScale,31,31,float(angle));
            if(outfit){int lugs=cosmeticSubimage(*outfit,11);if(lugs)for(int bolt=0;bolt<5;bolt++)centered(content_art::Lugs(original)[lugs],wheelScale,1,5,float(angle+bolt*72));}
        }
        auto pipe=outfit?installedExhaust(*outfit,exhaustFrame,rideOffset):placeExhaust(index,exhaustFrame,rideOffset,original);
        auto drawPipe=[&](){frame(content_art::Exhausts(original)[pipe.frame],x+float(pipe.x)*scale,y+float(pipe.y)*scale,scale);};
        if(!pipe.front)drawPipe();
        if(outfit){auto texture=content.compose(*outfit);DrawTexturePro(texture,{0,0,220,134},{x,y+(float(rideOffset)-64)*scale,220*scale,134*scale},{0,0},0,WHITE);}
        else frame(content_art::Cars(original)[index],x,y+float(rideOffset)*scale,scale);
        if(pipe.front)drawPipe();
    }
    std::vector<Resolution> resolutions(WindowMode mode){
        std::vector<Resolution> values;
        if(mode==WindowMode::Fullscreen){
            int monitor=GetCurrentMonitor();auto pos=GetMonitorPosition(monitor);
            values=platformDisplayModes(int(pos.x)+GetMonitorWidth(monitor)/2,int(pos.y)+GetMonitorHeight(monitor)/2);
            if(values.empty())values.push_back({GetMonitorWidth(monitor),GetMonitorHeight(monitor)});
        }else {
            values={{800,450},{960,540},{1280,720},{1600,900},{1920,1080},{2560,1440},{3840,2160}};
            if(mode==WindowMode::Windowed){
                if(!IsWindowFullscreen()){
                    auto limit=platformWindowedLimit(GetWindowHandle());
                    if(limit.width<=0||limit.height<=0)limit={GetMonitorWidth(GetCurrentMonitor())-32,GetMonitorHeight(GetCurrentMonitor())-80};
                    windowLimit=limit;
                }
                values.erase(std::remove_if(values.begin(),values.end(),[this](Resolution r){return r.width>windowLimit.width||r.height>windowLimit.height;}),values.end());
                if(values.empty())values.push_back({800,450});
            }
        }
        return values;
    }
    void normalizeResolution(Settings& s){
        auto values=resolutions(s.mode);
        if(std::find(values.begin(),values.end(),Resolution{s.width,s.height})==values.end()){
            auto nearest=std::min_element(values.begin(),values.end(),[&](Resolution a,Resolution b){return std::abs(a.width-s.width)+std::abs(a.height-s.height)<std::abs(b.width-s.width)+std::abs(b.height-s.height);});
            s.width=nearest->width;s.height=nearest->height;
        }
    }
    bool apply(const Settings& value){
        Settings s=validate(value);
        RenderTexture2D next=LoadRenderTexture(s.width,s.height);
        if(!next.id||!next.texture.id){if(next.id)UnloadRenderTexture(next);notice="Résolution indisponible : réglages conservés.";return false;}
        if(IsWindowFullscreen())ToggleFullscreen();
        if(IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE))ToggleBorderlessWindowed();
        ClearWindowState(FLAG_WINDOW_UNDECORATED);
        SetWindowSize(s.width,s.height);
        if(s.mode==WindowMode::Fullscreen){
            ToggleFullscreen();
            GLFWwindow* window=glfwGetCurrentContext();
            if(auto monitor=glfwGetWindowMonitor(window))glfwSetWindowMonitor(window,monitor,0,0,s.width,s.height,-1);
        }
        else if(s.mode==WindowMode::Borderless)ToggleBorderlessWindowed();
        else {auto pos=GetMonitorPosition(GetCurrentMonitor());SetWindowPosition(int(pos.x)+std::max(0,(GetMonitorWidth(GetCurrentMonitor())-s.width)/2),int(pos.y)+std::max(0,(GetMonitorHeight(GetCurrentMonitor())-s.height)/2));}
        if(s.vsync)SetWindowState(FLAG_VSYNC_HINT);else ClearWindowState(FLAG_VSYNC_HINT);
        SetTargetFPS(s.fps);
        bool modeValid=s.mode==WindowMode::Fullscreen?IsWindowFullscreen():s.mode==WindowMode::Borderless?IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE):(!IsWindowFullscreen()&&!IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE));
        if(!modeValid){UnloadRenderTexture(next);notice="Ce mode d'affichage n'a pas pu être activé.";return false;}
        if(render.id)UnloadRenderTexture(render);
        render=next;SetTextureFilter(render.texture,TEXTURE_FILTER_POINT);
        settings=s;drive.setTraffic(s.traffic);accumulator=0;
        return true;
    }
    void openOptions(){edited=settings;options=true;notice.clear();}
    void preview(){
        if(confirming)return;
        normalizeResolution(edited);previous=settings;
        if(apply(edited)){confirming=true;deadline=GetTime()+15;}
        else {apply(previous);edited=settings;}
    }
    void keep(){
        confirming=false;edited=settings;std::string error;
        if(!saveSettings(settingFile(),settings,error))notice="Réglages actifs, mais enregistrement impossible : "+error;
        else notice="Réglages enregistrés.";
    }
    void revert(){apply(previous);confirming=false;edited=settings;notice="Réglages précédents restaurés.";}
    void saveCar(){configuration=buildVehicle(profile);std::string error;if(!saveProfile(profileFile(),profile,error))notice="Enregistrement du garage impossible : "+error;}
    const char* driveLabel()const{return effectiveDrive(profile)==DriveLayout::Front?"TRACTION":effectiveDrive(profile)==DriveLayout::Rear?"PROPULSION":"4 ROUES MOTRICES";}
    void beginFree(){powerPopup=false;audioPopup=false;audio.reset();effects=DrivingEffects{};drive=FreeDrive{};drive.setTraffic(settings.traffic);configuration=buildVehicle(profile);drive.vehicle=configuration.vehicle;accumulator=0;screen=Screen::Free;options=false;paused=false;}
    void init(){
        if(!fs::exists(args.assets/"provenance.json"))throw std::runtime_error("Ressources manquantes. Extrayez entièrement le ZIP, puis lancez PixelCarRacerNative.exe.");
        settings=loadSettings(settingFile());profile=loadProfile(profileFile(),191,54);configuration=buildVehicle(profile);
        if(args.safe){settings=Settings{};settings.width=960;settings.height=540;settings.vsync=false;settings.fps=60;}
        if(args.smoke){profile.car=20;profile.rim=8;settings=Settings{};settings.width=960;settings.height=540;settings.vsync=false;settings.fps=0;settings.sound=false;}
        SetTraceLogLevel(LOG_WARNING);SetConfigFlags(FLAG_WINDOW_RESIZABLE);
        InitWindow(960,540,"Pixel Car Racer | Unbound Native");
        if(!IsWindowReady())throw std::runtime_error("Impossible d'ouvrir une fenêtre OpenGL 3.3.");
        SetExitKey(KEY_NULL);SetWindowMinSize(800,450);
        normalizeResolution(settings);
        std::vector<int> glyphs;
        for(int i=32;i<=126;i++)glyphs.push_back(i);
        for(int i=160;i<=255;i++)glyphs.push_back(i);
        for(int i:{0x2022,0x2190,0x2191,0x2192,0x2193,0x2013,0x2014})glyphs.push_back(i);
        font=LoadFontEx(asset("ui.ttf").c_str(),64,glyphs.data(),int(glyphs.size()));if(!font.texture.id)throw std::runtime_error("Police d'interface introuvable.");
        SetTextureFilter(font.texture,TEXTURE_FILTER_BILINEAR);
        for(int id:art::atlasIds){auto texture=LoadTexture(asset(TextFormat("texture-%03i.png",id)).c_str());if(!texture.id)throw std::runtime_error("Atlas de jeu illisible : "+std::to_string(id));SetTextureFilter(texture,TEXTURE_FILTER_POINT);atlases[id]=texture;}
        for(int i=0;i<content_art::AtlasCount;i++){auto im=LoadImage(asset(TextFormat("content-%02i.png",i)).c_str());if(!im.data)throw std::runtime_error("Contenu manquant : extraire tout le ZIP.");ImageFormat(&im,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);content.pixels[2000+i]=im;auto t=LoadTextureFromImage(im);SetTextureFilter(t,TEXTURE_FILTER_POINT);atlases[2000+i]=t;}
        for(int i=0;i<original_ui::AtlasCount;i++){auto t=LoadTexture(asset(TextFormat("original-ui-%02i.png",i)).c_str());if(!t.id)throw std::runtime_error("Interface d’origine manquante : extraire tout le ZIP.");SetTextureFilter(t,TEXTURE_FILTER_POINT);atlases[1000+i]=t;}
        if(!apply(settings)){Settings safe;safe.width=960;safe.height=540;if(!apply(safe))throw std::runtime_error("Impossible de créer la surface de rendu.");}
        edited=settings;
        if(!args.noAudio&&!args.smoke){audio.init(args.assets);audio.selectBank(profile.audioSource);}
        if(args.free)beginFree();
    }
    void background(bool driving){
        ClearBackground(Ink);
        if(!driving){crop(art::garages[0],{0,0,1280,720},Color{145,154,172,255});DrawRectangle(0,0,1280,720,Fade(Ink,.74f));return;}
        double pos=drive.player.position;crop(art::sky[0],{0,0,1280,340});
        tiled(art::mountains[0],130,160,scene::layerTravel(pos,scene::Mountains),Color{150,167,190,255});
        if(settings.quality!=Quality::Low)tiled(art::cityFar[0],150,160,scene::layerTravel(pos,scene::City),Color{152,171,193,220});
        tiled(art::trees[0],252,75,scene::layerTravel(pos,scene::Trees),Color{104,132,130,255});
        DrawRectangle(0,318,1280,312,Color{45,49,59,255});
        DrawRectangle(0,322,1280,5,Color{230,222,176,255});DrawRectangle(0,615,1280,4,Color{230,222,176,255});
        float offset=float(scene::roadPhase(pos));
        for(int lane=1;lane<3;lane++)for(float x=-offset;x<1280;x+=float(scene::pixels(scene::MarkSpacingMetres)))DrawRectangle(int(x),324+lane*96,int(scene::pixels(scene::MarkLengthMetres)),4,Color{171,173,181,255});
        if(settings.quality==Quality::High){
            for(int i=0;i<38;i++){float x=float(scene::wrap(i*71.0-scene::pixels(pos),1320))-20;DrawRectangle(int(x),350+(i*47)%252,18,1,Color{65,70,83,255});}
        }
        DrawRectangle(0,625,1280,95,Color{21,30,35,255});
    }
    void menu(){
        card({54,63,480,591},Color{14,22,33,240});
        text("PIXEL CAR",88,94,52);text("UNBOUND",88,152,66,Accent);
        text("NATIF WINDOWS  /  0.10",91,231,17,Muted);
        text("Prenez la route.",91,282,26);
        if(button({89,333,407,62},"MODE LIBRE",true))queued=[this]{beginFree();};
        if(button({89,410,407,53},"GARAGE")){openCustomization();screen=Screen::Garage;}
        if(button({89,477,407,53},"CUSTOMISATION"))openCustomization();
        if(button({89,544,407,45},"PARAMÈTRES"))openOptions();
        if(button({89,600,407,38},"QUITTER"))quit=true;

        DrawRectangle(608,459,610,8,Accent);
        car(profile.car,profile.rim,594,247,2.6,0,true,configuration.tireFrame,configuration.rideOffset,configuration.exhaustFrame,-1,&profile);
        text("MODE LIBRE",656,511,29);text("Route ouverte • circulation • conduite continue",656,555,18,Muted);
        text("239 apparences réunies • 521 jantes nommées",656,588,17,Muted);
    }
    void openCustomization(){screen=Screen::Customization;inventoryOpen=false;searchFocused=false;rimPicker=false;cosmeticPicker=false;customGroup=0;customSlot=PartSlot::Engine;customPreview=profile.parts[0];customPage=0;customSearch.clear();notice.clear();}
    static std::string lower(std::string value){for(char& c:value)c=char(std::tolower(static_cast<unsigned char>(c)));return value;}
    static Color rarityColor(Rarity rarity){
        static const Color colors[]={{173,185,198,255},{101,216,139,255},{92,175,255,255},{196,129,255,255},{255,192,77,255},{255,104,117,255}};
        return colors[std::clamp(int(rarity),0,5)];
    }
    void powerScene(){
        DrawRectangle(0,0,1280,720,Fade(BLACK,.82f));card({213,83,854,566});
        text("BANC DE PUISSANCE",250,109,30,Accent);
        text("Puissance moteur estimée • pleine charge • modèle natif",250,153,17,Muted);
        const auto& b=configuration;const auto& v=b.vehicle;
        text(TextFormat("Moteur catalogue : %.0f HP",b.engineHp),250,190,18);
        text(TextFormat("Pièces atmosphériques : +%.0f HP",b.boltOnHp),250,218,17,Muted);
        text(TextFormat("ECU : courbe étendue ×%.3f",v.redlineRpm/engineRedline(profile)),250,246,17,Muted);
        text(TextFormat("Boost : %.0f psi  •  rendement %.0f %%",v.boostPsi,v.boostEfficiency*100),250,274,17,Muted);
        text(TextFormat("Atmosphérique : %.0f HP",b.baseHp),727,190,18,Muted);
        text(TextFormat("Sans NOS : %.0f HP",b.boostedHp),727,220,23,Gold);
        text(TextFormat("Avec NOS : %.0f HP",b.nitroHp),727,254,23,Accent);
        Rectangle graph{268,337,740,211};
        double scale=std::max(100.0,b.nitroHp)*1.08;
        for(int i=0;i<=4;i++){float y=graph.y+graph.height-i*graph.height/4;
            DrawLine(int(graph.x),int(y),int(graph.x+graph.width),int(y),Color{48,59,72,255});
            text(TextFormat("%.0f",scale*i/4),222,y-8,12,Muted);
        }
        auto plot=[&](bool boost,bool nitro,Color color){Vector2 previous{};
            for(int i=0;i<=120;i++){double rpm=v.idleRpm+(v.redlineRpm-v.idleRpm)*i/120;
                double hp=enginePowerHp(v,rpm,boost?targetBoost(v,rpm):0,nitro);
                Vector2 point{graph.x+graph.width*i/120,graph.y+graph.height-float(hp/scale)*graph.height};
                if(i)DrawLineEx(previous,point,2,color);
                previous=point;
            }
        };
        plot(false,false,Muted);plot(true,false,Gold);if(v.nitroHp>0)plot(true,true,Accent);
        text(TextFormat("%.0f",v.idleRpm),268,558,14,Muted);text("RÉGIME (tr/min)",555,558,14,Muted);text(TextFormat("%.0f",v.redlineRpm),951,558,14,Muted);
        text("Gris : atmosphérique   •   Or : boost   •   Vert : boost + NOS",250,589,16,Muted);
        if(button({850,599,178,35},"FERMER",true))powerPopup=false;
    }
    static constexpr int GaragePageSize=6;
    void chooseGroup(int group,int slot=-1,bool rims=false){
        static const PartSlot defaults[]={PartSlot::Engine,PartSlot::Tires,PartSlot::Nos,PartSlot::Turbo,PartSlot::Suspension,PartSlot::Intake};
        cosmeticPicker=false;customGroup=std::clamp(group,0,5);inventoryOpen=true;rimPicker=rims||(slot<0&&group==1);
        customSlot=slot>=0?PartSlot(slot):defaults[customGroup];customPreview=rimPicker?profile.rim:profile.parts[int(customSlot)];
        customSearch.clear();searchFocused=false;searchSelectedAll=false;customPage=0;
        auto choices=garageChoices();auto found=std::find(choices.begin(),choices.end(),customPreview);
        if(found!=choices.end())customPage=int(found-choices.begin())/GaragePageSize;else if(!choices.empty())customPreview=choices[0];
    }
    void chooseCosmetic(int slot){
        cosmeticPicker=true;rimPicker=false;customGroup=6;cosmeticSlot=(slot+CosmeticSlotCount)%CosmeticSlotCount;
        inventoryOpen=true;searchFocused=false;searchSelectedAll=false;customSearch.clear();customPage=0;customPreview=profile.cosmetics[cosmeticSlot];
        auto choices=garageChoices();auto found=std::find(choices.begin(),choices.end(),customPreview);if(found!=choices.end())customPage=int(found-choices.begin())/GaragePageSize;
    }
    static const char* sourceLabel(int mask){return mask==1?"ORIGINAL":mask==2?"UNBOUND":"ORIGINAL + UNBOUND";}
    int choiceSource(int id)const{
        if(rimPicker||!id)return 3;
        if(cosmeticPicker){auto c=findCosmetic(id);return c?c->sourceMask:3;}
        auto p=findPart(id);return p?p->sourceMask:3;
    }
    int equippedChoice()const{return rimPicker?profile.rim:cosmeticPicker?profile.cosmetics[cosmeticSlot]:profile.parts[int(customSlot)];}
    std::string choiceName(int id)const{
        if(rimPicker){auto rim=findRim(id);return rim?rim->name:TextFormat("JANTE %02i",id+1);}
        if(cosmeticPicker){auto item=findCosmetic(id);return item?item->name:"CONFIGURATION DE BASE";}
        return id?findPart(id)->name:"CONFIGURATION DE BASE";
    }
    std::vector<int> garageChoices()const{
        std::vector<int> choices;
        if(cosmeticPicker){
            if(customSearch.empty())choices.push_back(0);
            for(const auto& c:CosmeticCatalog)if(c.slot==cosmeticSlot&&lower(c.name).find(lower(customSearch))!=std::string::npos)choices.push_back(c.id);
            std::stable_sort(choices.begin(),choices.end(),[this](int a,int b){if(!a||!b)return !a&&b;auto x=findCosmetic(a),y=findCosmetic(b);return rarityDescending?std::string(x->name)>y->name:std::string(x->name)<y->name;});
        }
        else if(rimPicker){for(int i:RimFrames)if(lower(choiceName(i)).find(lower(customSearch))!=std::string::npos)choices.push_back(i);if(rarityDescending)std::reverse(choices.begin(),choices.end());}
        else{
            if(customSearch.empty()||lower("configuration de base").find(lower(customSearch))!=std::string::npos)choices.push_back(0);
            for(const auto& part:PartCatalog)if(part.slot==customSlot&&lower(part.name).find(lower(customSearch))!=std::string::npos)choices.push_back(part.id);
            std::stable_sort(choices.begin(),choices.end(),[this](int a,int b){if(!a||!b)return !a&&b;return rarityDescending?weakerPart(*findPart(b),*findPart(a)):weakerPart(*findPart(a),*findPart(b));});
        }
        return choices;
    }
    void equipGarageChoice(){
        auto choices=garageChoices();if(std::find(choices.begin(),choices.end(),customPreview)==choices.end())return;
        if(rimPicker)profile.rim=customPreview;else if(cosmeticPicker)profile.cosmetics[cosmeticSlot]=customPreview;else equipPart(profile,customSlot,customPreview);
        saveCar();audio.install(settings.sound);notice="ÉQUIPEMENT ENREGISTRÉ";
    }
    Profile garagePreviewProfile()const{
        Profile preview=profile;if(!inventoryOpen)return preview;
        auto choices=garageChoices();if(std::find(choices.begin(),choices.end(),customPreview)==choices.end())return preview;
        if(rimPicker)preview.rim=customPreview;else if(cosmeticPicker)preview.cosmetics[cosmeticSlot]=customPreview;else equipPart(preview,customSlot,customPreview);
        return preview;
    }
    void garageKeyboard(){
        if((IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL))&&IsKeyPressed(KEY_F)){if(!inventoryOpen){if(cosmeticPicker)chooseCosmetic(cosmeticSlot);else chooseGroup(customGroup);}searchFocused=true;searchSelectedAll=true;}
        for(int i=0;i<6;i++)if(IsKeyPressed(KEY_F1+i))chooseGroup(i);
        if(IsKeyPressed(KEY_F7))chooseCosmetic(cosmeticSlot);
        if(IsKeyPressed(KEY_F8)){profile.rollCage=!profile.rollCage;saveCar();}
        if(searchFocused){
            bool changed=false;bool ctrl=IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL);
            if(ctrl&&IsKeyPressed(KEY_A))searchSelectedAll=true;
            for(int c=GetCharPressed();c>0;c=GetCharPressed())if(c>=32&&c<127&&!ctrl){
                if(searchSelectedAll){customSearch.clear();searchSelectedAll=false;}
                if(customSearch.size()<40){customSearch+=char(c);changed=true;}
            }
            if((IsKeyPressed(KEY_BACKSPACE)||IsKeyPressedRepeat(KEY_BACKSPACE))&&!customSearch.empty()){
                if(searchSelectedAll)customSearch.clear();else customSearch.pop_back();searchSelectedAll=false;changed=true;
            }
            if(changed){customPage=0;auto choices=garageChoices();if(!choices.empty())customPreview=choices[0];}
            if(IsKeyPressed(KEY_ENTER)){searchFocused=false;searchSelectedAll=false;equipGarageChoice();}
            return;
        }
        if(IsKeyPressed(KEY_TAB)){if(cosmeticPicker)chooseCosmetic(cosmeticSlot+(IsKeyDown(KEY_LEFT_SHIFT)?-1:1));else chooseGroup((customGroup+(IsKeyDown(KEY_LEFT_SHIFT)?5:1))%6);}
        if(!inventoryOpen){int d=IsKeyPressed(KEY_RIGHT)?1:IsKeyPressed(KEY_LEFT)?-1:0;if(d){cycleBody(profile,d);saveCar();}return;}
        auto choices=garageChoices();if(choices.empty())return;
        int pages=(int(choices.size())+GaragePageSize-1)/GaragePageSize;
        int pageDirection=IsKeyPressed(KEY_PAGE_DOWN)?1:IsKeyPressed(KEY_PAGE_UP)?-1:0;
        if(mouse.x>742&&mouse.y>150&&mouse.y<600){float wheel=GetMouseWheelMove();if(wheel)pageDirection=wheel>0?-1:1;}
        if(pageDirection){customPage=std::clamp(customPage+pageDirection,0,pages-1);customPreview=choices[customPage*GaragePageSize];}
        auto found=std::find(choices.begin(),choices.end(),customPreview);int index=found==choices.end()?0:int(found-choices.begin());
        int d=IsKeyPressed(KEY_RIGHT)?1:IsKeyPressed(KEY_LEFT)?-1:IsKeyPressed(KEY_DOWN)?2:IsKeyPressed(KEY_UP)?-2:0;
        if(IsKeyPressed(KEY_HOME))index=0;else if(IsKeyPressed(KEY_END))index=int(choices.size())-1;else index=std::clamp(index+d,0,int(choices.size())-1);
        if(d||IsKeyPressed(KEY_HOME)||IsKeyPressed(KEY_END)){customPreview=choices[index];customPage=index/GaragePageSize;}
        if(IsKeyPressed(KEY_ENTER))equipGarageChoice();
    }
    void uiImage(const art::Frame& f,Rectangle box,Color tint=WHITE){
        if(f.atlas<0||f.w<=0||f.h<=0)return;
        float scale=std::min(box.width/f.w,box.height/f.h);crop(f,{box.x+(box.width-f.w*scale)/2,box.y+(box.height-f.h*scale)/2,f.w*scale,f.h*scale},tint);
    }
    void rimIcon(int rim,int tire,Rectangle box){
        float scale=std::min(box.width/62,box.height/62);
        float x=box.x+(box.width-62*scale)/2,y=box.y+(box.height-62*scale)/2;
        // Source frames are cropped differently; preserve their common canvas.
        for(const auto* f:{&content_art::Tires(profile.contentSource==1)[tire],&equippedRim(rim,profile.contentSource==1)})
            crop(*f,{x+f->dx*scale,y+f->dy*scale,f->w*scale,f->h*scale});
    }
    bool iconButton(Rectangle r,const art::Frame& image,const std::string& tip,bool selected=false){
        uiImage(image,r);if(selected)DrawRectangleLinesEx(r,2,Accent);
        if(hit(r)){DrawRectangleLinesEx(r,2,WHITE);tooltipText=tip;}
        bool clicked=hit(r)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT);if(clicked)audio.click(settings.sound);return clicked;
    }
    void statBar(float y,double fraction,double extra=0){
        Rectangle r{29,y,244,19};crop(original_ui::bars[0],r);
        auto fill=[&](int image,double value){value=std::clamp(value,0.0,1.0);const auto& f=original_ui::bars[image];if(value>0)DrawTexturePro(atlases.at(f.atlas),{float(f.x),float(f.y),float(f.w*value),float(f.h)},{r.x,r.y,float(r.width*value),r.height},{0,0},0,WHITE);};
        if(extra>0)fill(1,fraction+extra);
        fill(3,fraction);
        for(int i=1;i<7;i++)DrawRectangle(int(r.x+i*r.width/7),int(y),4,19,Fade(BLACK,.35f));
    }
    void garageStats(const Profile& preview,const Build& build){
        DrawRectangle(0,51,300,669,Color{14,14,17,240});DrawRectangle(297,51,4,669,BLACK);
        card({17,77,266,95},Color{20,20,23,245});
        pxText("CAR",28,94,21);pxRight(TextFormat("%03i",preview.car+1),270,94,23);
        const Part* engine=findPart(preview.parts[int(PartSlot::Engine)]);
        pxText("MOTEUR",28,139,16);pxRight(engine?engine->name:"ORIGINE",270,137,19);
        const auto& v=build.vehicle;double maxKmh=v.redlineRpm*6.283185307179586*v.wheelRadius/(60*v.ratios[v.gearCount-1]*v.finalDrive)*3.6;
        pxText("VIT. THÉO.",28,190,13,Accent);pxRight(TextFormat("%.0f KM/H",maxKmh),274,188,20);statBar(221,maxKmh/800);
        pxText("PUISSANCE",28,273,16,Accent);pxRight(TextFormat("%.0f HP",build.boostedHp),274,270,22);statBar(304,build.boostedHp/5000,v.nitroHp/5000);
        pxText("POIDS",28,356,17,Accent);pxRight(TextFormat("%.0f KG",v.mass),274,353,22);statBar(387,v.mass/2200);
        pxText("GRIP",28,439,17,Accent);pxRight(TextFormat("%.0f",v.grip*1000),274,436,22);statBar(470,v.grip/2);
        if(hit({17,181,267,70}))tooltipText="Vitesse théorique au limiteur - puissance et traînée limitent la vitesse réelle";
        if(hit({17,262,267,70}))tooltipText=TextFormat("Sans NOS : %.0f HP | Avec NOS : %.0f HP",build.boostedHp,build.nitroHp);
        if(iconButton({18,502,58,32},original_ui::buttons[36],"Statistiques de la préparation",true))inventoryOpen=false;
        if(iconButton({84,502,58,32},original_ui::buttons[37],"Transmission et boîte (4-10 rapports)"))openTransmission();
        if(iconButton({150,502,58,32},original_ui::tools[10],"Banc de puissance"))powerPopup=true;
        if(iconButton({216,502,58,32},original_ui::buttons[40],"Sons du moteur et valve"))audioPopup=true;
        pxText("CARROSSERIE",28,551,14,Muted);
        if(button({18,574,36,32},"<")){cycleBody(profile,-1);saveCar();}
        pxText(TextFormat("%03i / %i",bodyChoiceIndex(profile)+1,int(std::size(BodyChoices))),78,582,17);
        if(button({246,574,36,32},">")){cycleBody(profile,1);saveCar();}
        pxText(sourceLabel(BodyChoices[bodyChoiceIndex(profile)].sourceMask),78,606,9,Muted);
        if(button({18,617,120,29},"DÉCOR"))garageStyle=(garageStyle+1)%5;
        if(button({148,617,134,29},"JANTES"))chooseGroup(1);
        if(button({18,655,120,30},"PRÉPA MAX",true)){equipBestParts(profile);saveCar();chooseGroup(0);rarityDescending=true;customPage=0;notice="PRÉPA MAX ENREGISTRÉE";}
        if(button({148,655,134,30},"REMETTRE BASE")){profile.parts.fill(0);profile.soundOn=profile.soundOff=profile.bov=-1;saveCar();if(inventoryOpen)chooseGroup(customGroup);notice="PIÈCES D'ORIGINE";}
        if(button({18,690,190,25},"STYLE (F7)"))chooseCosmetic(cosmeticSlot);
        if(button({215,690,67,25},profile.rollCage?"F8 ON":"F8 OFF",profile.rollCage)){profile.rollCage=!profile.rollCage;saveCar();}
    }
    void garageVehicle(const Profile& preview,const Build& build){
        float scale=inventoryOpen?2.45f:3.8f,x=inventoryOpen?270.f:350.f,y=inventoryOpen?335.f:265.f;
        auto wheels=bodyWheels(preview.car,preview.contentSource==1);float left=x+wheels.rear*scale,right=x+wheels.front*scale;
        float sy=2.6f,sx=(right-left)/96,base=y+(wheels.y+wheels.radius)*scale;
        auto lift=[&](int index){const auto& f=original_ui::lifts[index];DrawTexturePro(atlases.at(f.atlas),{float(f.x),float(f.y),float(f.w),float(f.h)},
            {left-1.5f*sx+f.dx*sx,base-100*sy+f.dy*sy,f.w*sx,f.h*sy},{0,0},0,WHITE);};
        if(wheels.radius>0)lift(0);
        car(preview.car,preview.rim,x,y,scale,0,true,build.tireFrame,build.rideOffset,build.exhaustFrame,-1,&preview);
        if(wheels.radius>0){lift(1);lift(2);}
    }
    void garageDock(){
        static const int icons[]={63,0,31,4,46,35};static const char* labels[]={"MOTEUR","ROUES","NOS","SURALIMENTATION","CHÂSSIS","PIÈCES"};
        DrawRectangle(301,599,979,121,Color{15,15,18,235});DrawRectangle(301,598,979,3,BLACK);
        for(int i=0;i<6;i++){
            Rectangle target{float(332+i*153),605,136,101};
            if(iconButton({target.x+24,target.y,87,79},original_ui::garageIcons[icons[i]],std::string(labels[i])+" - F"+std::to_string(i+1),inventoryOpen&&customGroup==i))chooseGroup(i);
            float size=i==3?11:13;std::string label="F"+std::to_string(i+1)+" "+labels[i];pxText(label,target.x+(target.width-pxWidth(label,size))/2,691,size,inventoryOpen&&customGroup==i?Accent:WHITE);
        }
    }
    const art::Frame& partImage(PartSlot slot,int subimage)const{
        auto pick=[&](const auto& frames)->const art::Frame&{return frames[std::clamp(subimage,0,int(std::size(frames))-1)];};
        switch(slot){
        case PartSlot::Engine:return pick(original_ui::engines);case PartSlot::Suspension:return pick(original_ui::suspensions);
        case PartSlot::Turbo:case PartSlot::Supercharger:return pick(original_ui::turbos);case PartSlot::Ecu:return pick(original_ui::ecus);
        case PartSlot::Nos:return pick(original_ui::nos);case PartSlot::Intake:return pick(original_ui::intakes);case PartSlot::Intercooler:return pick(original_ui::intercoolers);
        case PartSlot::Pistons:return pick(original_ui::pistons);case PartSlot::Exhaust:return pick(original_ui::exhausts);case PartSlot::Tires:return pick(art::tires);
        default:return original_ui::garageIcons[35];}
    }
    const art::Frame& cosmeticIcon(int id)const{
        const auto* c=findCosmetic(id);bool original=c&&c->imageSource>=0?c->imageSource==1:profile.contentSource==1;int n=c?c->subimage:0;
        switch(cosmeticSlot){
        case 0:return content_art::sp_paint(original)[n];case 1:return content_art::sp_decals(original)[n];case 2:return content_art::sp_spoiler(original)[n];case 3:return content_art::Racks(original)[n];
        case 4:case 5:case 6:case 7:return content_art::sp_bodykit_box(original)[n];case 8:return content_art::sp_rotor(original)[n];case 9:return content_art::Seats(original)[n];case 10:return content_art::sp_towhook(original)[n];case 11:return content_art::sp_lugnuts(original)[n];case 15:return content_art::sp_bulbs(original)[n];default:return content_art::sp_lighttint(original)[n];}
    }
    void garageInventory(){
        card({742,153,520,443},Color{18,18,22,245});
        pxText(rimPicker?"JANTES":cosmeticPicker?CosmeticLabels[cosmeticSlot]:slotLabel(customSlot),760,167,18,Accent);
        if(button({1222,161,26,26},"X")){inventoryOpen=false;searchFocused=false;return;}
        Rectangle search{759,198,489,31};DrawRectangleRec(search,Color{43,43,49,255});DrawRectangleLinesEx(search,searchFocused?2:1,searchFocused?Accent:Color{93,93,101,255});
        bool selectedText=searchFocused&&searchSelectedAll&&!customSearch.empty();
        if(selectedText)DrawRectangle(767,202,int(MeasureTextEx(font,customSearch.c_str(),16,0).x)+5,23,Accent);
        text(customSearch.empty()?"Rechercher une pièce... (Ctrl+F)":customSearch,769,205,16,selectedText?Ink:customSearch.empty()?Muted:WHITE);
        if(hit(search)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){searchFocused=true;searchSelectedAll=true;}
        std::vector<std::pair<std::string,int>> tabs;
        if(cosmeticPicker){if(button({759,238,42,30},"<"))chooseCosmetic(cosmeticSlot-1);pxText(TextFormat("%02i / 16 : %s",cosmeticSlot+1,CosmeticLabels[cosmeticSlot]),815,248,13,Accent);if(button({1206,238,42,30},">"))chooseCosmetic(cosmeticSlot+1);}
        switch(customGroup){case 0:tabs={{"MOTEURS",0},{"ECU",4}};break;case 1:tabs={{"JANTES",-1},{"PNEUS",10}};break;case 2:tabs={{"NOS",5}};break;case 3:tabs={{"TURBOS",2},{"COMPRESSEURS",3},{"INTERCOOLERS",7}};break;case 4:tabs={{"SUSPENSIONS",1},{"TRANSMISSION",-2}};break;case 6:break;default:tabs={{"ADMISSIONS",6},{"PISTONS",8},{"ÉCHAPPEMENTS",9}};}
        float width=tabs.empty()?0:489.f/tabs.size();for(size_t i=0;i<tabs.size();i++){
            bool selected=tabs[i].second==-1?rimPicker:!rimPicker&&int(customSlot)==tabs[i].second;
            if(button({759+float(i)*width,238,width-5,30},tabs[i].first,selected)){
                if(tabs[i].second==-2)openTransmission();else chooseGroup(customGroup,tabs[i].second,tabs[i].second==-1);
            }
        }
        auto choices=garageChoices();int pages=std::max(1,(int(choices.size())+GaragePageSize-1)/GaragePageSize);customPage=std::clamp(customPage,0,pages-1);
        for(int row=0;row<GaragePageSize;row++){
            int index=customPage*GaragePageSize+row;if(index>=int(choices.size()))break;int id=choices[index];const Part* p=rimPicker||cosmeticPicker||!id?nullptr:findPart(id);
            Rectangle r{float(759+(row%2)*246),float(280+(row/2)*74),240,68};bool selected=id==customPreview;
            DrawRectangleRec(r,selected?Color{53,68,68,255}:Color{43,43,49,255});DrawRectangleLinesEx(r,selected?2:1,selected?Accent:Color{102,102,111,255});
            if(p)DrawRectangle(int(r.x),int(r.y),4,int(r.height),rarityColor(partRarity(*p)));
            if(rimPicker)rimIcon(id,configuration.tireFrame,{r.x+7,r.y+6,48,52});else if(cosmeticPicker)uiImage(cosmeticIcon(id),{r.x+6,r.y+5,50,54});else uiImage(partImage(customSlot,p?p->subimage:0),{r.x+6,r.y+5,50,54},p?WHITE:Fade(WHITE,.5f));
            auto name=choiceName(id);size_t split=name.size()>20?name.rfind(' ',20):std::string::npos;
            if(split!=std::string::npos){text(name.substr(0,split),r.x+62,r.y+7,14);text(name.substr(split+1,23),r.x+62,r.y+25,14);}else text(name.substr(0,23),r.x+62,r.y+13,14);
            pxText(rimPicker||cosmeticPicker?"STYLE":p?rarityLabel(partRarity(*p)):"ORIGINE",r.x+62,r.y+44,9,p?rarityColor(partRarity(*p)):Muted);
            int origin=choiceSource(id);pxText(sourceLabel(origin),r.x+62,r.y+56,9,origin==1?Color{136,206,255,255}:origin==2?Color{229,156,240,255}:Muted);
            if(equippedChoice()==id)DrawCircle(int(r.x+r.width-8),int(r.y+8),3,Gold);
            if(hit(r)){tooltipText=name+" | "+sourceLabel(choiceSource(id));if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){customPreview=id;searchFocused=false;audio.click(settings.sound);}if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)&&GetTime()-lastCardClick<.3&&lastCardId==id)equipGarageChoice();if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){lastCardClick=GetTime();lastCardId=id;}}
        }
        if(choices.empty())text("Aucune pièce trouvée",785,320,20,Muted);
        const Part* selected=rimPicker||cosmeticPicker||!customPreview?nullptr:findPart(customPreview);
        text(choiceName(customPreview).substr(0,36),761,510,16);
        auto preview=buildVehicle(garagePreviewProfile());text(rimPicker||cosmeticPicker?"Style visuel • aucun gain de puissance":TextFormat("Gain : %+.0f HP  |  avec NOS : %+.0f HP",preview.boostedHp-configuration.boostedHp,preview.nitroHp-configuration.nitroHp),761,537,13,Muted);
        if(selected&&hit({759,509,335,45}))tooltipText=TextFormat("%s | statistique %.0f | poids relatif %.0f | valeur catalogue $%.0f",selected->name,selected->stat,selected->weight,selected->value);
        bool equipped=equippedChoice()==customPreview;
        if(button({1102,512,145,43},equipped?"ÉQUIPÉ":customPreview||rimPicker?"ÉQUIPER":"RETIRER",true,!equipped&&!choices.empty()))equipGarageChoice();
        if(button({759,565,37,26},"<",false,customPage>0)){--customPage;customPreview=choices[customPage*GaragePageSize];}
        text(TextFormat("%i / %i • %i choix",customPage+1,pages,int(choices.size())),813,571,13,Muted);
        if(button({965,565,231,26},rarityDescending?"TRI DÉCROISSANT":"TRI CROISSANT")){rarityDescending=!rarityDescending;customPage=0;}
        if(button({1210,565,37,26},">",false,customPage+1<pages)){++customPage;customPreview=choices[customPage*GaragePageSize];}
    }
    void customizationScene(){
        bool originalUi=uiEnabled;uiEnabled=originalUi&&!audioPopup&&!powerPopup;
        DrawRectangle(0,40,1280,654,Color{134,134,137,255});crop(original_ui::garages[garageStyle%5],{0,40,1280,654});
        Profile preview=garagePreviewProfile();auto shown=buildVehicle(preview);garageVehicle(preview,shown);garageStats(preview,shown);garageDock();
        DrawRectangle(0,0,1280,51,Color{28,28,31,255});DrawRectangle(0,47,1280,4,BLACK);
        if(button({17,8,111,32},"< MENU")){screen=Screen::Menu;inventoryOpen=false;}
        pxText("GARAGE",150,14,26);
        card({570,8,412,32},Color{19,22,27,255});pxText("ORIGINAL + UNBOUND",610,18,18,Accent);
        pxText("1220 ÉQUIPEMENTS",1000,18,13);
        if(iconButton({1222,8,36,33},original_ui::buttons[37],"Paramètres PC"))openOptions();
        if(iconButton({1171,65,88,80},original_ui::garageIcons[10],"Prendre la route"))queued=[this]{saveCar();beginFree();};
        pxText("ROUTE",1190,142,13);
        const auto& identity=vehicleIdentity(preview.car,preview.contentSource==1);
        float nameSize=21;while(nameSize>12&&MeasureTextEx(font,identity.name,nameSize,0).x>805)nameSize-=1;
        text(identity.name,327,65,nameSize,identity.tentative?Gold:Accent);
        const auto& stock=stockVehicle(preview.car);const char* factory=stock.drive==0?"TRACTION":stock.drive==1?"PROPULSION":"4 ROUES MOTRICES";
        text(TextFormat("Origine : %.0f HP  /  %.0f kg  /  %.1f L  /  %s",stock.hp,stock.weightLb*.45359237,stock.litres,factory),327,95,14,Muted);
        if(preview.contentSource==0&&vehicleIdentity(preview.car,false).name!=vehicleIdentity(preview.car,true).name)
            text(std::string("Base mécanique : ")+vehicleIdentity(preview.car,true).name,327,116,12,Muted);
        else if(identity.tentative)text("Identification visuelle à confirmer",327,116,12,Gold);
        if(inventoryOpen){garageInventory();}
        if(!notice.empty()&&!inventoryOpen)text(notice,335,566,16,Accent);
        uiEnabled=originalUi;
        if(powerPopup)powerScene();
        if(audioPopup){
            DrawRectangle(0,0,1280,720,Fade(BLACK,.75f));card({263,141,754,457});
            text("SONS DU MOTEUR",305,172,29,Accent);
            text("Profils sonores d'origine • choix indépendant du moteur",305,219,17,Muted);
            if(button({748,164,224,32},profile.audioSource==1?"SONS : ORIGINAL":"SONS : UNBOUND")){profile.audioSource=1-profile.audioSource;audio.selectBank(profile.audioSource);saveCar();}
            auto soundRow=[&](float y,const char* label,int& value,int maximum){
                text(label,306,y+12,19);std::string name=value<0?"AUTO":"PROFIL "+std::to_string(value+1);
                if(button({607,y,43,41},"<")){value=value<0?maximum:value-1;saveCar();}
                text(name,675,y+12,18,Gold);
                if(button({904,y,43,41},">")){value=value>=maximum?-1:value+1;saveCar();}
            };
            soundRow(261,"En accélération",profile.soundOn,15);
            soundRow(315,"En décélération",profile.soundOff,15);
            soundRow(369,"Valve de décharge",profile.bov,3);
            if(button({305,435,204,43},"ÉCOUTER CHARGE",false,audio.ready&&settings.sound)){previewGas=true;audioPreviewUntil=GetTime()+3;}
            if(button({521,435,204,43},"ÉCOUTER LEVER",false,audio.ready&&settings.sound)){previewGas=false;audioPreviewUntil=GetTime()+3;}
            if(button({737,435,210,43},"ÉCOUTER VALVE",false,audio.ready&&settings.sound))audio.valve(profile.bov,settings.sound);
            text("AUTO : attribution native approximative par famille moteur.",305,503,16,Muted);
            if(button({720,539,227,39},"FERMER",true)){audioPopup=false;audioPreviewUntil=0;}
        }
    }

    void openTransmission(){transmissionDraft=profile;screen=Screen::Transmission;notice.clear();}
    void commitTransmission(){profile=transmissionDraft;sanitizeTransmission(profile);saveCar();notice="Transmission enregistrée.";}
    bool ratioSlider(Rectangle track,double& value,double low,double high){
        high=std::max(high,low);double next=value;
        if(high-low>1e-8&&uiEnabled&&IsMouseButtonDown(MOUSE_BUTTON_LEFT)&&CheckCollisionPointRec(mouse,{track.x,track.y-8,track.width,track.height+16}))next=std::round((low+std::clamp(double((mouse.x-track.x)/track.width),0.0,1.0)*(high-low))*100)/100;
        next=std::clamp(next,low,high);bool changed=std::abs(next-value)>1e-8;value=next;
        DrawRectangleRec(track,Color{44,55,67,255});float fill=(high-low>1e-8?float((value-low)/(high-low)):.5f)*track.width;
        DrawRectangle(int(track.x),int(track.y),int(fill),int(track.height),Accent);DrawRectangle(int(track.x+fill)-4,int(track.y)-4,8,int(track.height)+8,WHITE);
        return changed;
    }
    void transmissionScene(){
        crop(original_ui::garages[garageStyle%5],{0,0,1280,720});car(profile.car,profile.rim,365,310,2.3,0,true,configuration.tireFrame,configuration.rideOffset,configuration.exhaustFrame,-1,&profile);
        DrawRectangle(0,0,1280,720,Fade(Ink,.88f));text("TRANSMISSION / BOÎTE",34,25,29,Accent);
        text(notice.empty()?"Boîtes inspirées du réel • enregistrer pour appliquer":notice,34,69,16,Muted);
        if(button({1030,23,217,48},"RETOUR")){screen=Screen::Customization;}
        const char* drives[]={"TRACTION","PROPULSION","4 ROUES MOTRICES"};
        for(int i=0;i<3;i++)if(button({float(34+i*321),105,306,40},drives[i],!transmissionDraft.factoryDrive&&int(transmissionDraft.drive)==i)){transmissionDraft.drive=DriveLayout(i);transmissionDraft.factoryDrive=false;}
        if(button({1030,105,217,40},transmissionDraft.automatic?"AUTOMATIQUE":"MANUELLE"))transmissionDraft.automatic=!transmissionDraft.automatic;
        for(int i=0;i<8;i++)if(button({34,float(163+i*44),235,36},gearboxPresetName(i),transmissionDraft.gearboxPreset==i)){applyGearboxPreset(transmissionDraft,i);notice.clear();}
        auto preview=buildVehicle(transmissionDraft);const auto& v=preview.vehicle;
        for(int i=0;i<10;i++){
            float x=306+float(i/5)*470,y=163+float(i%5)*70;bool active=i<transmissionDraft.gearCount;
            text("RAPPORT "+std::to_string(i+1),x+5,y,16,active?WHITE:Muted);
            if(!active){text("INACTIF",x+180,y,16,Muted);DrawRectangle(int(x+43),int(y+34),340,12,Color{33,42,51,255});continue;}
            text(TextFormat("%.3f",transmissionDraft.gearRatios[i]),x+138,y,17,Gold);
            double kmh=v.redlineRpm*6.283185307179586*v.wheelRadius/(transmissionDraft.gearRatios[i]*transmissionDraft.finalDrive*60)*3.6;
            text(TextFormat("%.0f km/h",kmh),x+290,y,16,Muted);
            double low=i<9?transmissionDraft.gearRatios[i+1]+.05:.3,high=i?transmissionDraft.gearRatios[i-1]-.05:6;
            int d=0;if(button({x,y+25,32,31},"-"))d=-1;if(button({x+395,y+25,32,31},"+"))d=1;
            if(d){transmissionDraft.gearRatios[i]=std::clamp(transmissionDraft.gearRatios[i]+d*.01,low,high);transmissionDraft.gearboxPreset=-1;}
            if(ratioSlider({x+43,y+34,340,12},transmissionDraft.gearRatios[i],low,high))transmissionDraft.gearboxPreset=-1;
        }
        text("NOMBRE DE RAPPORTS",34,535,16,Muted);
        if(button({34,562,38,32},"-")){transmissionDraft.gearCount=std::max(4,transmissionDraft.gearCount-1);transmissionDraft.gearboxPreset=-1;}
        text(std::to_string(transmissionDraft.gearCount),119,568,23,Gold);
        if(button({231,562,38,32},"+")){transmissionDraft.gearCount=std::min(10,transmissionDraft.gearCount+1);transmissionDraft.gearboxPreset=-1;}
        text("PASSAGE DE RAPPORT",34,606,15,Muted);
        if(button({34,632,38,30},"-")){transmissionDraft.shiftSeconds=std::max(.04,transmissionDraft.shiftSeconds-.01);transmissionDraft.gearboxPreset=-1;}
        text(TextFormat("%.0f ms",transmissionDraft.shiftSeconds*1000),102,638,17);
        if(button({231,632,38,30},"+")){transmissionDraft.shiftSeconds=std::min(.5,transmissionDraft.shiftSeconds+.01);transmissionDraft.gearboxPreset=-1;}
        if(button({34,674,235,24},"TRANSMISSION D'ORIGINE",transmissionDraft.factoryDrive))transmissionDraft.factoryDrive=true;
        text("PONT FINAL",316,535,20);text(TextFormat("%.2f",transmissionDraft.finalDrive),920,535,20,Gold);
        if(button({306,566,32,31},"-")){transmissionDraft.finalDrive=std::max(2.0,transmissionDraft.finalDrive-.01);transmissionDraft.gearboxPreset=-1;}
        if(button({1171,566,32,31},"+")){transmissionDraft.finalDrive=std::min(6.0,transmissionDraft.finalDrive+.01);transmissionDraft.gearboxPreset=-1;}
        if(ratioSlider({350,576,809,12},transmissionDraft.finalDrive,2,6))transmissionDraft.gearboxPreset=-1;
        text("km/h au limiteur : valeur théorique, selon les pneus. La puissance et la traînée limitent la vitesse réelle.",306,615,14,Muted);
        if(button({306,654,196,40},"ANNULER")){transmissionDraft=profile;screen=Screen::Customization;}
        if(button({515,654,203,40},"RÉINITIALISER"))applyGearboxPreset(transmissionDraft,0);
        if(button({731,654,231,40},"ENREGISTRER",true))commitTransmission();
        if(button({975,654,272,40},"PRENDRE LA ROUTE",true))queued=[this]{commitTransmission();beginFree();};
    }
    void garage(){customizationScene();}
    void renderEffects(bool front){
        for(const auto& p:effects.particles){
            bool isFront=p.kind!=EffectKind::Smoke&&p.kind!=EffectKind::BrakeSmoke;if(isFront!=front)continue;
            float fade=float(1-p.age/p.life);const art::Frame* sprite=nullptr;float scale=float(p.scale);Vector2 origin{19,15};Color color=Fade(WHITE,fade*.65f);float rotation=0;
            if(p.kind==EffectKind::Smoke||p.kind==EffectKind::BrakeSmoke){sprite=p.kind==EffectKind::Smoke?&art::smoke[0]:&art::smoke2[0];scale*=float(1+p.age*2);}
            else if(p.kind==EffectKind::Flame){sprite=&art::flames[int(p.age*30)%int(std::size(art::flames))];origin={art::flameRoots[int(p.age*30)%int(std::size(art::flames))].x,art::flameRoots[int(p.age*30)%int(std::size(art::flames))].y};scale=float(p.scale);color=Fade(Color{255,185,65,255},fade);rotation=float(std::atan2(p.dy,p.dx)*180/3.141592653589793-180);}
            else if(p.kind==EffectKind::Spark){sprite=&art::sparks[0];origin={0,0};scale=1.5f;color=Fade(Gold,fade);rotation=float(std::atan2(p.vy,p.vx)*180/3.141592653589793);}
            else if(p.kind==EffectKind::Nitro){
                float length=30*float(p.scale),width=5*float(p.scale);
                Vector2 a{float(p.x),float(p.y)};
                Vector2 b{a.x+float(p.dx)*length-float(p.dy)*width,a.y+float(p.dy)*length+float(p.dx)*width};
                Vector2 c{a.x+float(p.dx)*length+float(p.dy)*width,a.y+float(p.dy)*length-float(p.dx)*width};
                DrawTriangle(a,b,c,Fade(SKYBLUE,fade*.75f));DrawCircleV(a,2*float(p.scale),Fade(SKYBLUE,fade*.5f));continue;
            }
            if(sprite)DrawTexturePro(atlases.at(sprite->atlas),{float(sprite->x),float(sprite->y),float(sprite->w),float(sprite->h)},
                {float(p.x),float(p.y),sprite->w*scale,sprite->h*scale},{(origin.x-sprite->dx)*scale,(origin.y-sprite->dy)*scale},rotation,color);
        }
    }
    void freeScene(){
        renderEffects(false);
        for(int lane=0;lane<3;lane++){
            for(const auto& t:drive.traffic)if(drive.trafficEnabled&&t.lane==lane){float x=float(scene::trafficX(t.position,drive.player.position));if(x>-400&&x<1600)car(t.appearance,RimFrames[t.appearance%RimFrames.size()],x,269+lane*96,1.25,scene::wheelAngle(t.position,.32));}
            if(std::clamp(int(std::round(drive.lane)),0,2)==lane)car(profile.car,profile.rim,360,269+float(drive.lane)*96,1.25,scene::wheelAngle(drive.player.position,drive.vehicle.wheelRadius),true,configuration.tireFrame,configuration.rideOffset,configuration.exhaustFrame,scene::wheelAngle(drive.player.rearRollDistance,drive.vehicle.wheelRadius),&profile);
        }
        renderEffects(true);
        if(drive.collisionCooldown>1.0)DrawRectangle(0,0,1280,720,Fade(RED,.10f));
        DrawRectangle(0,0,1280,86,Fade(Ink,.93f));text("MODE LIBRE",35,23,30);text(TextFormat("%.2f km",drive.player.position/1000),280,31,20,Muted);
        if(!drive.trafficEnabled)text("TRAFIC DÉSACTIVÉ",445,32,17,Muted);
        if(button({814,17,238,51},"PARAMÈTRES"))openOptions();
        if(button({1066,17,177,51},paused?"REPRENDRE":"PAUSE"))paused=!paused;
        card({29,578,275,111});text(TextFormat("%03i",int(drive.player.speed*3.6)),52,587,60);text("km/h",192,620,22,Muted);
        text(TextFormat("%.0f HP moteur",drive.player.powerHp),344,560,16,Gold);
        if(drive.player.handbraking)text("FREIN À MAIN",580,560,17,Gold);
        card({320,578,563,111});text(std::string(profile.automatic?"AUTO  •  ":"MANUELLE  •  ")+driveLabel(),344,595,17,Accent);
        text("Z / ↑  Accélérer     S / ↓  Freiner",344,625,17);
        text("← / →  Voies    E / C Rapports  T Boîte  Espace F.à main  N NOS",344,655,14,Muted);
        card({900,578,350,111});text(TextFormat("%i",drive.player.gear),927,596,57,Gold);
        text(TextFormat("%04i tr/min",int(drive.player.rpm)),992,602,23);
        DrawRectangle(994,644,228,9,Color{40,51,65,255});DrawRectangle(994,644,int(228*std::clamp(drive.player.rpm/drive.vehicle.redlineRpm,0.0,1.0)),9,drive.player.rpm>drive.vehicle.upshiftRpm?Gold:Accent);
        text(drive.vehicle.nitroHp>0?TextFormat("Boost %.1f psi   NOS %.1f s",drive.player.boostPsi,drive.player.nitroRemaining):TextFormat("Boost %.1f psi   NOS absent",drive.player.boostPsi),912,669,13,drive.player.nitroActive?Gold:Muted);
        if(const Part* bottle=findPart(profile.parts[int(PartSlot::Nos)]))frame(art::nosIcons[std::clamp(bottle->subimage,0,7)],1180,657,.18f);
        if(paused&&!options){
            DrawRectangle(0,86,1280,480,Fade(Ink,.60f));card({416,184,448,320});
            text("PAUSE",574,211,32);
            if(button({452,271,376,54},"REPRENDRE",true))paused=false;
            if(button({452,340,376,54},"PARAMÈTRES"))openOptions();
            if(button({452,409,376,54},"RETOUR AU MENU")){paused=false;screen=Screen::Menu;}
        }
    }
    int choice(float y,const std::string& label,const std::string& value){
        text(label,213,y+12,21,Muted);card({657,y,410,48},Color{29,41,56,255});
        int d=0;if(button({660,y+3,45,42},"<"))d=-1;if(button({1019,y+3,45,42},">"))d=1;
        float size=value.size()>23?17:20;float w=MeasureTextEx(font,value.c_str(),size,0).x;text(value,862-w/2,y+13,size);
        return d;
    }
    void settingsScene(){
        DrawRectangle(0,0,1280,720,Fade(Ink,.82f));card({174,40,932,639});
        text("PARAMÈTRES",211,66,30);text("AFFICHAGE, SON ET TRAFIC",211,110,15,Accent);
        int d=choice(134,"Mode d'affichage",edited.mode==WindowMode::Windowed?"Fenêtre avec bordure":edited.mode==WindowMode::Borderless?"Fenêtre sans bordure":"Plein écran");
        if(d){edited.mode=WindowMode((int(edited.mode)+d+3)%3);normalizeResolution(edited);}
        d=choice(186,edited.mode==WindowMode::Borderless?"Résolution de rendu":"Résolution",TextFormat("%i × %i",edited.width,edited.height));
        if(d){auto r=resolutions(edited.mode);auto i=std::find(r.begin(),r.end(),Resolution{edited.width,edited.height});int n=i==r.end()?0:int(i-r.begin());auto next=r[(n+d+int(r.size()))%int(r.size())];edited.width=next.width;edited.height=next.height;}
        d=choice(238,"Limite d'images par seconde",edited.fps?std::to_string(edited.fps)+" FPS":"Illimitée");
        if(d){const int choices[]={30,60,120,144,165,240,0};auto i=std::find(std::begin(choices),std::end(choices),edited.fps);int n=i==std::end(choices)?0:int(i-choices);edited.fps=choices[(n+d+7)%7];}
        if(choice(290,"Synchronisation verticale",edited.vsync?"Activée":"Désactivée"))edited.vsync=!edited.vsync;
        d=choice(342,"Qualité des graphismes",edited.quality==Quality::Low?"Faible":edited.quality==Quality::Medium?"Moyenne":"Élevée");
        if(d)edited.quality=Quality((int(edited.quality)+d+3)%3);
        if(choice(394,"Compteur FPS",edited.showFps?"Afficher":"Masquer"))edited.showFps=!edited.showFps;
        if(choice(446,"Son",edited.sound?"Activé":"Désactivé"))edited.sound=!edited.sound;
        if(choice(498,"Trafic en mode libre",edited.traffic?"Activé":"Désactivé"))edited.traffic=!edited.traffic;
        text(edited.mode==WindowMode::Borderless?"Sans bordure : la fenêtre suit la taille du bureau.":"VSync : la fréquence de l'écran peut limiter les FPS.",212,559,16,Muted);
        if(button({212,598,238,49},"RETOUR")){options=false;notice.clear();}
        if(button({470,598,257,49},"PAR DÉFAUT"))edited=Settings{};
        if(button({747,598,320,49},"APPLIQUER",true))queued=[this]{preview();};
        if(!notice.empty()){DrawRectangle(0,690,1280,30,Ink);text(notice,30,695,16,Accent);}
    }
    void confirmScene(){
        DrawRectangle(0,0,1280,720,Fade(Ink,.75f));card({325,220,630,264});
        text("Conserver ces réglages ?",369,250,30);
        text(TextFormat("Rétablissement automatique dans %i s",int(std::max(0.0,std::ceil(deadline-GetTime())))),369,306,20,Muted);
        if(button({368,369,250,61},"CONSERVER",true))queued=[this]{keep();};
        if(button({638,369,273,61},"RÉTABLIR"))queued=[this]{revert();};
        text("Échap : rétablir     F10 : affichage de secours",369,451,16,Muted);
    }
    EffectSources effectSources(){
        auto wheels=bodyWheels(profile.car,profile.contentSource==1);double baseY=269+drive.lane*96;
        EffectSources sources;sources.rearWheel=360+wheels.rear*1.25;sources.frontWheel=360+wheels.front*1.25;sources.wheelY=baseY+(wheels.y+wheels.radius)*1.25;
        auto pipe=installedExhaust(profile,configuration.exhaustFrame,configuration.rideOffset);
        sources.outletCount=pipe.count;
        for(int i=0;i<pipe.count;i++){sources.outlets[i]=pipe.outlets[i];sources.outlets[i].x=360+pipe.outlets[i].x*1.25;sources.outlets[i].y=baseY+pipe.outlets[i].y*1.25;}
        return sources;
    }
    void controls(double dt){
        if((IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL))&&IsKeyPressed(KEY_Q)){quit=true;return;}
        if(IsKeyPressed(KEY_K)&&(screen==Screen::Free||screen==Screen::Garage||screen==Screen::Customization)&&!searchFocused){profile.headlights=!profile.headlights;saveCar();}
        if(IsKeyPressed(KEY_F10)){if(confirming)revert();Settings safe;safe.width=960;safe.height=540;safe.vsync=false;safe.fps=60;apply(safe);edited=settings;options=true;notice="Affichage de secours. Appliquez vos réglages pour les enregistrer.";}
        if(IsKeyPressed(KEY_ESCAPE)){if(confirming)revert();else if(options)options=false;else if(powerPopup)powerPopup=false;else if(audioPopup){audioPopup=false;audioPreviewUntil=0;}else if(screen==Screen::Free)paused=!paused;else if(screen==Screen::Garage||screen==Screen::Customization){if(searchFocused)searchFocused=false;else if(inventoryOpen)inventoryOpen=false;else{saveCar();screen=Screen::Menu;}}else if(screen==Screen::Transmission){screen=Screen::Customization;}}
        if(!confirming&&IsKeyPressed(KEY_ENTER)&&(IsKeyDown(KEY_LEFT_ALT)||IsKeyDown(KEY_RIGHT_ALT))){openOptions();edited.mode=settings.mode==WindowMode::Windowed?WindowMode::Borderless:WindowMode::Windowed;queued=[this]{preview();};}
        if(confirming&&GetTime()>=deadline)revert();
        if(IsKeyPressed(KEY_F3)&&screen!=Screen::Garage&&screen!=Screen::Customization){settings.showFps=!settings.showFps;edited.showFps=settings.showFps;}
        DriverInput input{IsKeyDown(KEY_Z)||IsKeyDown(KEY_W)||IsKeyDown(KEY_UP),IsKeyDown(KEY_S)||IsKeyDown(KEY_DOWN),profile.automatic,IsKeyDown(KEY_N),IsKeyDown(KEY_L),IsKeyDown(KEY_SPACE)};
        if((screen==Screen::Customization||screen==Screen::Garage)&&!options&&!confirming&&!audioPopup&&!powerPopup)garageKeyboard();
        if(screen==Screen::Free&&!paused&&!options&&!confirming){
            if(IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_A)||IsKeyPressed(KEY_Q))drive.changeLane(-1);
            if(IsKeyPressed(KEY_RIGHT)||IsKeyPressed(KEY_D))drive.changeLane(1);
            if(IsKeyPressed(KEY_E)||IsKeyPressed(KEY_LEFT_SHIFT))shift(drive.player,1,drive.vehicle);
            if(IsKeyPressed(KEY_C))shift(drive.player,-1,drive.vehicle);
            if(IsKeyPressed(KEY_T)){profile.automatic=!profile.automatic;input.automatic=profile.automatic;saveCar();}
            if(args.smoke)input={true,frames>=260&&frames<267,true,frames>=235};
            accumulator+=dt;while(accumulator>=Step){drive.update(input,Step);accumulator-=Step;}
            auto sources=effectSources();
            const Part* exhaust=findPart(profile.parts[int(PartSlot::Exhaust)]);
            effects.update(drive.player,drive.vehicle,input,sources,drive.collisionCooldown,dt,exhaust!=nullptr);
        }else accumulator=0;
        bool driving=screen==Screen::Free&&!paused&&!options&&!confirming;
        if(driving&&IsKeyPressed(KEY_H))audio.horn(settings.sound);
        if(audioPopup&&GetTime()<audioPreviewUntil){CarState preview;preview.rpm=4000;
            audio.update(profile,configuration.vehicle,preview,{previewGas,false,true},0,true,settings.sound);
        }else audio.update(profile,drive.vehicle,drive.player,input,drive.collisionCooldown,driving,settings.sound);

    }
    void renderFrame(){
        float sw=float(GetScreenWidth()),sh=float(GetScreenHeight());float outer=std::min(sw/render.texture.width,sh/render.texture.height);
        Rectangle output{(sw-render.texture.width*outer)/2,(sh-render.texture.height*outer)/2,render.texture.width*outer,render.texture.height*outer};
        float uiScale=std::min(render.texture.width/1280.f,render.texture.height/720.f);
        Vector2 pad{(render.texture.width-1280*uiScale)/2,(render.texture.height-720*uiScale)/2};
        auto m=GetMousePosition();mouse={((m.x-output.x)/outer-pad.x)/uiScale,((m.y-output.y)/outer-pad.y)/uiScale};
        BeginTextureMode(render);ClearBackground(BLACK);BeginMode2D(Camera2D{pad,{0,0},0,uiScale});
        tooltipText.clear();uiEnabled=!options&&!confirming; background(screen==Screen::Free);
        if(screen==Screen::Menu)menu();else if(screen==Screen::Garage)garage();else if(screen==Screen::Customization)customizationScene();else if(screen==Screen::Transmission)transmissionScene();else freeScene();
        if(options){uiEnabled=!confirming;settingsScene();}
        if(confirming){uiEnabled=true;confirmScene();}
        if(!tooltipText.empty()&&!options&&!confirming&&!audioPopup&&!powerPopup){float width=std::min(850.f,MeasureTextEx(font,tooltipText.c_str(),15,0).x+22);float x=std::clamp(mouse.x+12,8.f,1270-width),y=std::clamp(mouse.y-40,55.f,670.f);DrawRectangle(int(x),int(y),int(width),31,Color{15,15,18,248});DrawRectangleLines(int(x),int(y),int(width),31,Accent);text(tooltipText,x+10,y+8,15);}
        if(settings.showFps){bool inGarage=(screen==Screen::Garage||screen==Screen::Customization)&&!options&&!confirming;bool inTuning=screen==Screen::Transmission&&!options&&!confirming;
            float x=inGarage?1040:inTuning?1050:1121,y=inGarage?55:inTuning?74:691;
            DrawRectangle(int(x),int(y),inGarage?110:151,24,Ink);text(TextFormat("%i FPS",GetFPS()),x+12,y+4,inGarage?14:16,Accent);
        }
        if(args.smoke&&frames>=420&&frames<=431)exhaustContactSheet();
        EndMode2D();EndTextureMode();
        BeginDrawing();ClearBackground(BLACK);DrawTexturePro(render.texture,{0,0,float(render.texture.width),-float(render.texture.height)},output,{0,0},0,WHITE);EndDrawing();
    }
    // Diagnostic-only contact sheets use the same car() renderer as garage/free drive.
    void exhaustContactSheet(){
        const int pipes[]={7,33,34,40,41,42,43,44,45,46,47,39};
        const int page=std::clamp((frames-420)/3,0,3);
        Profile sample;sample.car=page==1?22:page==2?167:20;sample.contentSource=page==1?1:0;
        if(page==3)sample.cosmetics[4]=104007;
        rlDrawRenderBatchActive();
        DrawRectangle(0,0,1280,720,Color{44,46,53,255});
        text(TextFormat("ANCRAGES SOURCE - %s - CAR %03i%s",sample.contentSource?"ORIGINAL":"UNBOUND",sample.car+1,page==3?" / KIT FORTUNE / SUSPENSION +6":""),14,8,17,WHITE);
        text("Points turquoise : sorties des particules. Ordre et positions issus du code source.",14,33,12,Accent);
        for(int i=0;i<12;i++){
            float x=8+424*(i%3),y=60+164*(i/3);int pipe=pipes[i];
            auto fit=installedExhaust(sample,pipe,page==3?6:0);
            text(TextFormat("%02i %s / ANCRAGE %i",pipe,fit.front?"DEVANT":"DERRIERE",fit.front?2:1),x,y,13,WHITE);
            car(sample.car,9,x+5,y+28,1.7f,0,false,0,page==3?6:0,pipe,-1,&sample);
            for(int k=0;k<fit.count;k++){
                const auto& o=fit.outlets[k];Vector2 pt{x+5+float(o.x)*1.7f,y+28+float(o.y)*1.7f};
                DrawCircleV(pt,2,Accent);DrawLineV(pt,{pt.x+float(o.dx)*9,pt.y+float(o.dy)*9},Accent);
            }
        }
    }
    void check(bool condition,const std::string& name){smokeChecks.push_back((condition?"PASS ":"FAIL ")+name);smokePassed&=condition;}
    void capture(const std::string& name){if(!args.capture.empty()){fs::create_directories(args.capture);TakeScreenshot((args.capture/name).u8string().c_str());}}
    void smoke(){
        if(frames==5)capture("menu.png");
        if(frames==6)screen=Screen::Garage;
        if(frames==8)capture("garage.png");
        if(frames==8)beginFree();
        if(frames==75){check(drive.player.position>0,"free drive advances");capture("mode-libre.png");}
        if(frames==76){drive.changeLane(1);check(drive.targetLane==2,"lane input");}
        if(frames==85)openOptions();
        if(frames==86)capture("parametres.png");
        if(frames==90){edited=settings;edited.mode=WindowMode::Borderless;edited.width=1280;edited.height=720;preview();}
        if(frames==95){check(IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)&&!IsWindowFullscreen(),"borderless backend state");check(GetScreenWidth()==GetMonitorWidth(GetCurrentMonitor()),"borderless desktop dimensions");deadline=GetTime()-1;}
        if(frames==100){check(!confirming&&settings.mode==WindowMode::Windowed,"timeout restores previous mode");check(!fs::exists(settingFile()),"unconfirmed settings are not persisted");}
        if(frames==105){edited=settings;edited.mode=WindowMode::Fullscreen;auto modes=resolutions(edited.mode);edited.width=modes.front().width;edited.height=modes.front().height;edited.quality=Quality::Low;preview();}
        if(frames==110){check(IsWindowFullscreen(),"exclusive fullscreen backend state");check(GetScreenWidth()==settings.width&&GetScreenHeight()==settings.height,"fullscreen resolution applied");keep();}
        if(frames==120){edited=settings;edited.mode=WindowMode::Windowed;edited.width=960;edited.height=540;edited.vsync=true;edited.fps=30;edited.quality=Quality::Medium;edited.showFps=true;preview();}
        if(frames==125){check(!IsWindowFullscreen()&&!IsWindowState(FLAG_BORDERLESS_WINDOWED_MODE)&&!IsWindowState(FLAG_WINDOW_UNDECORATED),"bordered window backend state");check(GetScreenWidth()==960&&GetScreenHeight()==540,"window resolution applied");check(IsWindowState(FLAG_VSYNC_HINT),"VSync request applied");keep();capStarted=GetTime();capMeasuring=true;}
        if(frames==128)capture("parametres-valides.png");
        if(frames==155){capElapsed=GetTime()-capStarted;check(capElapsed>=.9,"30 FPS cap limits wall-clock frame rate");capMeasuring=false;check(loadSettings(settingFile())==settings,"confirmed settings round trip");profile.car=37;profile.rim=8;saveCar();auto p=loadProfile(profileFile(),191,54);check(p.car==37&&p.rim==8,"garage profile round trip");options=false;}
        if(frames==200){check(drive.player.position>20,"free drive resumes after settings");capture("mode-libre-final.png");}
        if(frames==205){openCustomization();equipPart(profile,PartSlot::Engine,1002);equipPart(profile,PartSlot::Turbo,3026);equipPart(profile,PartSlot::Nos,5007);equipPart(profile,PartSlot::Exhaust,9048);equipPart(profile,PartSlot::Tires,10017);saveCar();chooseGroup(0);customPreview=1002;}
        if(frames==213)capture("customisation.png");
        if(frames==216)audioPopup=true;
        if(frames==220)capture("sons-moteur.png");
        if(frames==222){audioPopup=false;auto p=loadProfile(profileFile(),191,54);check(p.parts==profile.parts,"custom equipment persists");beginFree();check(drive.vehicle.boostPsi==35&&drive.vehicle.nitroHp==250,"equipped turbo and NOS affect the active vehicle");}
        if(frames==255){capture("nos-vfx.png");check(drive.player.nitroRemaining<10,"NOS charge is consumed in free drive");check(drive.player.boostPsi>0,"turbo develops boost in free drive");check(std::any_of(effects.particles.begin(),effects.particles.end(),[](const Particle& p){return p.kind==EffectKind::Nitro;}),"NOS visual effect is active");}
        if(frames==270){drive.lane=drive.targetLane;drive.collisionCooldown=0;drive.traffic[0]={drive.player.position,0,drive.targetLane,0};}
        if(frames==272){capture("collision-vfx.png");check(std::any_of(effects.particles.begin(),effects.particles.end(),[](const Particle& p){return p.kind==EffectKind::Spark;}),"collision emits sparks");}
        if(frames==274){openCustomization();equipBestParts(profile);saveCar();customPreview=profile.parts[0];rarityDescending=true;}
        if(frames==277)capture("prepa-max.png");
        if(frames==279)powerPopup=true;
        if(frames==282)capture("banc-puissance.png");
        if(frames==284){check(configuration.boostedHp>4200&&configuration.nitroHp>4500,"maximum preparation displays compound boost and NOS power");
            check(partRarity(*findPart(profile.parts[0]))==Rarity::Contraband,"maximum engine is classified contraband");
            check(std::abs(enginePowerHp(configuration.vehicle,configuration.peakRpm,targetBoost(configuration.vehicle,configuration.peakRpm))-configuration.boostedHp)<.01,"power bench matches the driving torque model");powerPopup=false;}
        if(frames==285){beginFree();openOptions();edited.traffic=false;preview();}
        if(frames==286){keep();options=false;check(!drive.trafficEnabled,"disabling traffic applies to the active free drive");
            check(!loadSettings(settingFile()).traffic,"disabled traffic preference is saved");drive.traffic[0]={drive.player.position+5,0,1,0};}
        if(frames==287){check(drive.collisionCooldown==0,"disabled traffic cannot trigger hidden collisions");}
        if(frames==288){capture("sans-trafic.png");openOptions();edited.traffic=true;preview();check(drive.trafficEnabled,"traffic can be re-enabled");deadline=GetTime()-1;}
        if(frames==289){check(!drive.trafficEnabled&&!settings.traffic,"unconfirmed traffic change is reverted");options=false;}
        // Controlled rendered pairs: 0.1 seconds of travel at the displayed speed.
        // Pause the simulation so the image displacement can be measured exactly.
        if(frames==290){beginFree();check(!drive.trafficEnabled,"new free drive keeps traffic disabled");settings.showFps=false;profile.car=20;drive.player.speed=0;for(auto& t:drive.traffic)t.position=10000;}
        // Windows' software double buffer can expose the preceding presented
        // frame to TakeScreenshot. Hold each state before capturing it.
        if(frames==293)capture("motion-stationary-a.png");
        if(frames==294){capture("motion-stationary-b.png");drive.player.speed=100/3.6;drive.player.position=100;}
        if(frames==297){capture("motion-100-a.png");drive.player.position+=100/3.6*.1;}
        if(frames==300){capture("motion-100-b.png");drive.player.speed=200/3.6;drive.player.position=100;}
        if(frames==303){capture("motion-200-a.png");drive.player.position+=200/3.6*.1;}
        if(frames==306){capture("motion-200-b.png");paused=true;}
        if(frames==309)capture("motion-paused-a.png");
        if(frames==311)capture("motion-paused-b.png");
        auto exhaustCase=[&](int part,int body){profile.car=body;equipPart(profile,PartSlot::Exhaust,part);beginFree();drive.player.gear=2;drive.player.speed=100/3.6;drive.player.nitroActive=true;
            auto sources=effectSources();effects.update(drive.player,drive.vehicle,{true,false,true,true},sources,0,Step,true);
            bool aligned=true;for(const auto& p:effects.particles)if(p.kind==EffectKind::Flame||p.kind==EffectKind::Nitro){auto o=sources.outlets[p.outlet];aligned&=p.x==o.x&&p.y==o.y;}
            check(aligned,"exhaust sprite and flame/NOS roots share their visible outlets");};
        if(frames==313)exhaustCase(9007,20);
        if(frames==316)capture("echappement-arriere.png");
        if(frames==317)exhaustCase(9048,20);
        if(frames==320)capture("echappement-capot.png");
        if(frames==321)exhaustCase(9044,20);
        if(frames==324)capture("echappement-lateral.png");
        if(frames==325)exhaustCase(9039,20);
        if(frames==328)capture("echappement-triple.png");
        if(frames==329)exhaustCase(9050,22);
        if(frames==332)capture("echappement-capot-triple.png");
        if(frames==333){openTransmission();applyGearboxPreset(transmissionDraft,7);commitTransmission();beginFree();check(drive.vehicle.gearCount==10,"ten-speed preset reaches the driving model");openTransmission();}
        if(frames==336)capture("transmission-dix-rapports.png");
        if(frames==337){openCustomization();profile.car=20;saveCar();}
        if(frames==340)capture("garage-pc-original.png");
        if(frames==341)chooseGroup(0);
        if(frames==344)capture("inventaire-pc-original.png");
        if(frames==345)chooseGroup(1);
        if(frames==348)capture("jantes-pc-original.png");
        if(frames==349)chooseGroup(3);
        if(frames==352)capture("turbo-pc-original.png");
        if(frames==353){beginFree();drive.player.speed=30;drive.player.gear=4;DriverInput hand{true,false,true,true,false,true};stepCar(drive.player,drive.vehicle,hand,Step,0);auto sources=effectSources();effects.update(drive.player,drive.vehicle,hand,sources,0,Step,true);
            check(drive.player.handbraking&&drive.player.powerHp==0&&!drive.player.nitroActive,"handbrake blocks engine drive and NOS");
            check(drive.player.speed<30&&drive.player.rearRollDistance==0,"handbrake slows the vehicle and locks rear-wheel rotation");}
        if(frames==356)capture("frein-a-main.png");
        if(frames==357){openCustomization();rarityDescending=false;chooseGroup(1);auto choices=garageChoices();check(choices.size()==RimFrames.size()&&std::all_of(choices.begin(),choices.end(),isRimFrame),"rim inventory excludes tyre and effect frames");customPage=0;customPreview=RimFrames[0];}
        for(int page=0;page<4;page++){
            if(frames==358+page*3){customPage=page;customPreview=RimFrames[page*GaragePageSize];}
            if(frames==360+page*3)capture(TextFormat("jantes-corrigees-%i.png",page+1));
        }
        if(frames==371){profile.rim=10100;profile.contentSource=1;saveCar();chooseGroup(1);customSearch="Four Racing";customPage=0;customPreview=10100;check(garageChoices()==std::vector<int>{10100},"source-named composite rim is searchable and previewable");}
        if(frames==374)capture("jantes-originales-nommees.png");
        if(frames==375){profile.contentSource=0;audio.selectBank(0);saveCar();}
        if(frames==378)capture("contenu-unbound.png");
        if(frames==379){for(const auto& c:CosmeticCatalog)if(!profile.cosmetics[c.slot])profile.cosmetics[c.slot]=c.id;profile.contentSource=1;saveCar();inventoryOpen=false;}
        if(frames==382)capture("garage-complet.png");
        if(frames==383)chooseCosmetic(1);
        if(frames==386)capture("livrees-original-unbound.png");
        if(frames==387)chooseCosmetic(4);
        if(frames==390)capture("kits-carrosserie.png");
        if(frames==391)beginFree();
        if(frames==394)capture("route-personnalisee.png");
        if(frames==395){auto image=LoadImageFromTexture(content.body);auto bounds=GetImageAlphaBorder(image,.01f);check(content.pixels.size()==size_t(content_art::AtlasCount)&&bounds.width>100&&bounds.height>20,"composed body stays visible across graphics-mode changes");UnloadImage(image);saveCar();auto loaded=loadProfile(profileFile(),191,54);check(loaded.rim==10100&&loaded.contentSource==1&&loaded.cosmetics==profile.cosmetics,"named rims and all appearance slots persist together");}
        if(frames==399){openCustomization();profile.car=20;profile.contentSource=0;profile.cosmetics.fill(0);profile.cosmetics[3]=103005;profile.cosmetics[9]=109001;profile.cosmetics[10]=110001;equipPart(profile,PartSlot::Exhaust,9007);saveCar();}
        if(frames==402)capture("accessoires-ancres.png");
        if(frames==403){profile.rollCage=true;profile.headlights=true;profile.cosmetics[4]=104007;profile.cosmetics[9]=309001;saveCar();}
        if(frames==406)capture("ancrages-source.png");
        if(frames==407){profile.car=22;profile.contentSource=1;beginFree();drive.player.speed=100/3.6;drive.player.gear=3;drive.player.nitroActive=true;auto sources=effectSources();effects.update(drive.player,drive.vehicle,{true,false,true,true},sources,0,Step,true);bool attached=true;for(const auto& particle:effects.particles)if(particle.kind==EffectKind::Flame||particle.kind==EffectKind::Nitro){auto outlet=sources.outlets[particle.outlet];attached&=particle.x==outlet.x&&particle.y==outlet.y;}check(attached,"source-bank kit fitting keeps VFX roots attached to the same exhaust transform");}
        if(frames==410)capture("accessoires-route.png");
        if(frames==411){openCustomization();chooseCosmetic(9);customSearch="Pride Comfort";customPreview=109001;customPage=0;}
        if(frames==414)capture("origines-pieces.png");
        if(frames==415){chooseGroup(3);customSearch="Reddy T60AD";customPage=0;customPreview=3028;check(choiceSource(3028)==1,"original-only equipment is identified in the unified catalog");}
        if(frames==418)capture("original-exclusif.png");
        if(frames==419){saveCar();auto loaded=loadProfile(profileFile(),191,54);check(loaded.rollCage&&loaded.headlights,"transferred cage and lighting preferences persist");}
        if(frames==422)capture("echappements-source-unbound.png");
        if(frames==425)capture("echappements-source-original.png");
        if(frames==428)capture("echappements-source-longue.png");
        if(frames==431)capture("echappements-source-kit.png");
        if(frames==433){openCustomization();profile=Profile{};saveCar();check(std::abs(configuration.baseHp-123)<.001&&configuration.vehicle.drive==DriveLayout::Front,"stock hatchback source power and factory traction reach the garage model");}
        if(frames==436)capture("fiche-stock-traction.png");
        if(frames==437){profile.car=2;saveCar();check(configuration.vehicle.drive==DriveLayout::All&&std::abs(configuration.baseHp-300)<.001,"stock AWD model changes power, mass and drivetrain in the garage");}
        if(frames==440)capture("fiche-stock-awd.png");
        if(frames==441){profile.car=134;saveCar();check(configuration.vehicle.mass<600&&std::abs(configuration.baseHp-31)<.001,"source microcar keeps its light chassis and small engine in the garage");}
        if(frames==444)capture("fiche-stock-microcar.png");
        if(frames==445){profile.car=156;saveCar();check(configuration.vehicle.redlineRpm==7000&&std::abs(configuration.baseHp-755)<.001,"stock V8 model uses its own source engine and rev limit");}
        if(frames==448)capture("fiche-stock-v8.png");
        if(frames==449)openTransmission();
        if(frames==452)capture("transmission-origine.png");
        if(frames==453){commitTransmission();auto loaded=loadProfile(profileFile(),191,54);check(loaded.factoryDrive&&effectiveDrive(loaded)==DriveLayout::Rear,"factory drivetrain state round trips from the garage transmission editor");}
        if(frames==456)quit=true;

    }
    int run(){
        init();
        while(!WindowShouldClose()&&!quit){double dt=args.smoke?(frames>=290?0:1.0/30.0):std::clamp(double(GetFrameTime()),0.0,.1);controls(dt);renderFrame();if(IsKeyPressed(KEY_F12))capture(TextFormat("capture-%06i.png",frames));if(queued){auto action=std::move(queued);queued=nullptr;action();}if(args.smoke)smoke();frames++;}
        if(confirming)revert();
        saveCar();
        {std::error_code ec;fs::create_directories(args.data,ec);if(!ec){std::ofstream out(args.data/"last-session.txt");out<<"screen="<<int(screen)<<"\ncustom_group="<<customGroup<<"\ncustom_page="<<customPage<<"\ninventory_open="<<inventoryOpen<<"\nnitro_remaining="<<drive.player.nitroRemaining<<"\nnitro_active="<<drive.player.nitroActive<<"\nhandbraking="<<drive.player.handbraking<<"\nrear_roll_m="<<drive.player.rearRollDistance<<"\ntraffic_enabled="<<drive.trafficEnabled<<"\ntraffic_count="<<(drive.trafficEnabled?drive.traffic.size():0)<<"\ndistance_m="<<drive.player.position<<"\nspeed_mps="<<drive.player.speed<<"\ntarget_lane="<<drive.targetLane<<"\ngear="<<drive.player.gear<<"\nengine_part="<<profile.parts[int(PartSlot::Engine)]<<"\ntire_part="<<profile.parts[int(PartSlot::Tires)]<<"\ngear_count="<<drive.vehicle.gearCount<<"\nfinal_drive="<<drive.vehicle.finalDrive<<"\nshift_seconds="<<drive.vehicle.shiftSeconds<<"\nnative_mass_kg="<<drive.vehicle.mass<<"\nnative_hp="<<configuration.boostedHp<<"\nnative_nos_hp="<<configuration.nitroHp<<"\ncurrent_hp="<<drive.player.powerHp<<"\nnative_torque_nm="<<drive.vehicle.torque<<"\ndrive_layout="<<int(drive.vehicle.drive)<<"\naudio_ready="<<audio.ready<<"\naudio_failures="<<audio.failures<<"\nframes="<<frames<<"\nmode="<<modeKey(settings.mode)<<"\nwidth="<<GetScreenWidth()<<"\nheight="<<GetScreenHeight()<<"\n";}}
        if(args.smoke){fs::create_directories(args.data);std::ofstream out(args.data/"smoke-report.txt");
#ifdef _WIN32
            out<<"Native Windows rendering smoke test. Physical PC GPU and audio are not established.\n";
#else
            out<<"Native Linux rendering smoke test; Windows execution not established by this run.\n";
#endif
            for(auto& s:smokeChecks)out<<s<<'\n';
            out<<"cap_30_fps_elapsed_for_30_frames="<<capElapsed<<"\n";
            std::cout<<(smokePassed?"SMOKE PASS":"SMOKE FAIL")<<'\n';
        }
        return args.smoke&&!smokePassed?2:0;
    }
    ~App(){
        content.clear();
        if(render.id)UnloadRenderTexture(render);
        for(auto& pair:atlases)UnloadTexture(pair.second);
        if(font.texture.id)UnloadFont(font);
        if(IsWindowReady())CloseWindow();
    }
};
int main(int argc,char** argv){
    bool diagnostic=false;
    for(int i=1;i<argc;i++)if(std::string(argv[i])=="--smoke-test"||std::string(argv[i])=="--physics-benchmark-dir"||std::string(argv[i])=="--check-audio-dir")diagnostic=true;
    try{
        Args args;
        for(int i=1;i<argc;i++){std::string a=argv[i];auto value=[&](){if(i+1>=argc)throw std::runtime_error("Argument manquant : "+a);return fs::absolute(fs::u8path(argv[++i]));};
            if(a=="--data-dir"){args.data=value();args.dataSpecified=true;}else if(a=="--assets-dir")args.assets=value();else if(a=="--capture-dir")args.capture=value();
            else if(a=="--check-audio-dir")args.audioCheck=value();
            else if(a=="--physics-benchmark-dir")args.benchmark=value();
            else if(a=="--safe-mode")args.safe=true;else if(a=="--free-drive")args.free=true;else if(a=="--smoke-test")args.smoke=true;else if(a=="--no-audio")args.noAudio=true;
            else if(a=="--help"){std::cout<<"PixelCarRacerNative [--safe-mode] [--free-drive] [--data-dir PATH] [--no-audio] [--physics-benchmark-dir NEW_PATH]\n";return 0;}else throw std::runtime_error("Argument inconnu : "+a);
        }
        if(!args.audioCheck.empty()){setExecutableDirectory();if(args.assets.empty())args.assets=fs::current_path()/"assets";checkOriginalAudio(args.assets,args.audioCheck);return 0;}
        if(!args.benchmark.empty()){
            if(args.smoke||args.free)throw std::runtime_error("Le banc de physique ne se combine pas à un mode de jeu.");
            writePhysicsBenchmark(args.benchmark);return 0;
        }
        if(args.smoke&&(!args.dataSpecified||fs::exists(args.data/"settings.ini")||fs::exists(args.data/"profile.ini")))throw std::runtime_error("Le test graphique exige --data-dir vers un dossier de test neuf.");
        setExecutableDirectory();if(args.assets.empty())args.assets=fs::current_path()/"assets";
        App app(args);return app.run();
    }catch(const std::exception& e){if(diagnostic)std::cerr<<"FAIL: "<<e.what()<<'\n';else showFatalError(e.what());return 1;}
}
