#include "raylib.h"
#include "rlgl.h"
#include "model.hpp"
#include "benchmark.hpp"
#include "game_audio.hpp"
#include "garage_engine.hpp"
#include "saved_cars.hpp"
#include "effects.hpp"
#include "road_scene.hpp"
#include "chassis_pose.hpp"
#include "platform.hpp"
#include "art.hpp"
#include "original_ui.hpp"
#include "content_renderer.hpp"
#include "rim_finish_art.hpp"
#include "customization_audit.hpp"
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
    fs::path data=fs::u8path(defaultDataDirectory()),assets,capture,benchmark,audioCheck,customizationCheck;
    bool smoke=false,safe=false,free=false,noAudio=false,dataSpecified=false;
};
struct App {
    enum class Screen { Menu, Garage, Free, Customization, Transmission, Suspension, Collection } screen=Screen::Menu;
    int savedSelection=0,savedPage=0;std::string savedName;bool savedNameFocused=false;std::vector<SavedCar> savedEntries;
    Args args;
    Settings settings,edited,previous;
    Resolution windowLimit{1280,720};
    Profile profile,transmissionDraft,suspensionDraft; Build configuration;
    bool inventoryOpen=false,searchFocused=false,searchSelectedAll=false,rimPicker=false,cosmeticPicker=false;int cosmeticSlot=0;int customGroup=0,rimAxle=0,lastCardId=-1;double lastCardClick=-10;std::string tooltipText;
    PartSlot customSlot=PartSlot::Engine; int customPreview=0,customPage=0; std::string customSearch;
    FreeDrive drive;DrivingEffects effects;
    Font font{};std::map<int,Texture2D> atlases;RenderTexture2D render{};
    ContentRenderer content;
    GarageEngine garageEngine;
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
    void car(int index,int rim,float x,float y,float scale,double wheelAngle,bool shadow=true,int tireFrame=0,double rideOffset=0,int exhaustFrame=-1,double rearAngle=-1,const Profile* outfit=nullptr,const CarState* motion=nullptr){
        index=(index+191)%191;rim=validRimFrame(rim);bool original=(outfit?outfit->contentSource:profile.contentSource)==1;auto w=bodyWheels(index,original);tireFrame=std::clamp(tireFrame,0,int(std::size(art::tires))-1);
        ChassisPose pose=chassisPose(w.rear,w.front,w.y,drive.vehicle,motion?*motion:CarState{},rideOffset);
        if(shadow&&settings.quality!=Quality::Low)DrawEllipse(int(x+110*scale),int(y+(w.y+w.radius)*scale),int(87*scale),int(6*scale),Fade(BLACK,.35f));
        // Draw the body last: opaque fenders and skirts must cover the tyres.
        // All cropped wheel sprites use their original 62x62 canvas and origin.
        if(w.radius>0)for(float cx:{w.rear,w.front}){
            auto local=motion?pose.wheel(cx==w.front):ChassisPoint{cx,w.y};
            Vector2 center{x+float(local.x)*scale,y+float(local.y)*scale};
            auto centered=[&](const art::Frame& f,float factor,float ox,float oy,float angle){
                DrawTexturePro(atlases.at(f.atlas),{float(f.x),float(f.y),float(f.w),float(f.h)},
                    {center.x,center.y,f.w*factor,f.h*factor},
                    {(ox-f.dx)*factor,(oy-f.dy)*factor},angle,WHITE);
            };
            {const auto& well=art::wheelWells[0];auto hub=motion?pose.body(cx,w.y+rideOffset):ChassisPoint{cx,w.y+rideOffset};
                DrawTexturePro(atlases.at(well.atlas),{float(well.x),float(well.y),float(well.w),float(well.h)},
                    {x+float(hub.x)*scale,y+float(hub.y)*scale,well.w*scale,well.h*scale},
                    {(20-well.dx)*scale,(36-well.dy)*scale},motion?float(-pose.pitch*180/3.141592653589793):0,WHITE);}

            DrawCircleV(center,w.radius*.78f*scale,Color{12,13,18,255});
            float wheelScale=scale*(w.radius/25.f);
            double angle=cx==w.rear&&rearAngle>=0?rearAngle:wheelAngle;
            centered(content_art::Tires(original)[tireFrame],wheelScale,31,31,float(angle));
            if(outfit){int brake=cosmeticSubimage(*outfit,8);if(brake)centered(content_art::Brakes(original)[brake],wheelScale,31,31,0);}
            centered(equippedRim(outfit&&cx==w.rear&&outfit->rearRim>=0?outfit->rearRim:rim,original),wheelScale,31,31,float(angle));
            int selectedRim=outfit&&cx==w.rear&&outfit->rearRim>=0?outfit->rearRim:rim;
            if(auto finish=rim_finish::finish(selectedRim)){
                if(finish->shine){BeginBlendMode(BLEND_ADDITIVE);centered(rim_finish::shine(original,finish->shine),wheelScale,31,31,0);EndBlendMode();}
                centered(rim_finish::shadow(original,finish->shadow),wheelScale,25,25,0);
            }
            if(outfit){int lugs=cosmeticSubimage(*outfit,11);if(lugs)for(int bolt=0;bolt<5;bolt++)centered(content_art::Lugs(original)[lugs],wheelScale,1,5,float(angle+bolt*72));}
        }
        if(motion){rlPushMatrix();rlTranslatef(x+float(pose.pivotX)*scale,y+float(pose.pivotY-pose.heave*pose.pixelsPerMetre)*scale,0);rlRotatef(float(-pose.pitch*180/3.141592653589793),0,0,1);rlTranslatef(-x-float(pose.pivotX)*scale,-y-float(pose.pivotY)*scale,0);}
        auto pipe=outfit?installedExhaust(*outfit,exhaustFrame,rideOffset):placeExhaust(index,exhaustFrame,rideOffset,original);
        auto drawPipe=[&](){frame(content_art::Exhausts(original)[pipe.frame],x+float(pipe.x)*scale,y+float(pipe.y)*scale,scale);};
        if(!pipe.front)drawPipe();
        if(outfit){auto texture=content.compose(*outfit);DrawTexturePro(texture,{0,0,float(materials::CanvasW),float(materials::CanvasH)},{x-materials::CanvasX*scale,y+(float(rideOffset)-materials::CanvasY)*scale,materials::CanvasW*scale,materials::CanvasH*scale},{0,0},0,WHITE);}
        else frame(content_art::Cars(original)[index],x,y+float(rideOffset)*scale,scale);
        if(pipe.front)drawPipe();
        if(motion)rlPopMatrix();
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
        settings=s;drive.setTraffic(s.traffic);drive.vehicle.abs=s.abs;drive.vehicle.tractionControl=s.tractionControl;accumulator=0;
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
    void beginFree(){garageEngine.stop();audio.stopEngine();powerPopup=false;audioPopup=false;audio.reset();effects=DrivingEffects{};drive=FreeDrive{};drive.setTraffic(settings.traffic);configuration=buildVehicle(profile);drive.vehicle=configuration.vehicle;drive.vehicle.abs=settings.abs;drive.vehicle.tractionControl=settings.tractionControl;accumulator=0;screen=Screen::Free;options=false;paused=false;}
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
        for(int i=0;i<rim_finish::AtlasCount;i++){auto texture=LoadTexture(asset(TextFormat("customization-%02i.png",i)).c_str());if(!texture.id)throw std::runtime_error("Matériaux de jantes manquants : extraire tout le ZIP.");SetTextureFilter(texture,TEXTURE_FILTER_POINT);atlases[3000+i]=texture;}
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
        text("NATIF WINDOWS  /  0.13.9",91,231,17,Muted);
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
    void openCustomization(){garageEngine.stop();audio.stopEngine();screen=Screen::Customization;inventoryOpen=false;searchFocused=false;rimPicker=false;cosmeticPicker=false;customGroup=0;customSlot=PartSlot::Engine;customPreview=profile.parts[0];customPage=0;customSearch.clear();notice.clear();}
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
    static const char* sourceLabel(int mask){return mask==4?"EXTENSION PC":mask==1?"ORIGINAL":mask==2?"UNBOUND":"ORIGINAL + UNBOUND";}
    int choiceSource(int id)const{
        if(rimPicker||!id)return 3;
        if(cosmeticPicker){auto c=findCosmetic(id);return c?c->sourceMask:3;}
        auto p=findPart(id);return p?p->sourceMask:3;
    }
    int equippedChoice()const{return rimPicker?(rimAxle==2?rearRimId(profile):profile.rim):cosmeticPicker?profile.cosmetics[cosmeticSlot]:profile.parts[int(customSlot)];}
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
        if(cosmeticPicker&&!cosmeticFit(profile,customPreview).supported){notice="Pièce sans variante pour cette carrosserie.";return;}
        if(rimPicker)equipRim(profile,customPreview,rimAxle);else if(cosmeticPicker)profile.cosmetics[cosmeticSlot]=customPreview;else equipPart(profile,customSlot,customPreview);
        saveCar();audio.install(settings.sound);notice="ÉQUIPEMENT ENREGISTRÉ";
    }
    Profile garagePreviewProfile()const{
        Profile preview=profile;if(!inventoryOpen)return preview;
        auto choices=garageChoices();if(std::find(choices.begin(),choices.end(),customPreview)==choices.end())return preview;
        if(rimPicker)equipRim(preview,customPreview,rimAxle);else if(cosmeticPicker)preview.cosmetics[cosmeticSlot]=customPreview;else equipPart(preview,customSlot,customPreview);
        return preview;
    }
    void garageKeyboard(){
        if((IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL))&&IsKeyPressed(KEY_F)){if(!inventoryOpen){if(cosmeticPicker)chooseCosmetic(cosmeticSlot);else chooseGroup(customGroup);}searchFocused=true;searchSelectedAll=true;}
        if(IsKeyPressed(KEY_F11)&&!searchFocused){openSavedCars();return;}
        if(IsKeyPressed(KEY_F9)&&!searchFocused){openSuspension();return;}
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
        if(IsKeyPressed(KEY_G)){garageEngine.toggle(configuration.vehicle);if(garageEngine.running)audio.startEngine(profile,settings.sound);else audio.stopEngine(true);}
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
        pxText("MOTEUR",28,139,16);
        std::string engineLabel=engine?engine->name:"ORIGINE";
        if(engine&&pcEngine(engine->id)){auto separator=engineLabel.find(" - ");if(separator!=std::string::npos)engineLabel=engineLabel.substr(separator+3);}
        float engineSize=19;while(engineSize>10&&pxWidth(engineLabel,engineSize)>138)engineSize-=1;
        pxRight(engineLabel,270,137,engineSize);
        if(engine&&hit({17,125,266,47}))tooltipText=engine->name;
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
        if(rimPicker){const char* axles[]={"AV + AR","AVANT","ARRIÈRE"};for(int i=0;i<3;i++)if(button({900+float(i)*98,161,94,26},axles[i],rimAxle==i)){rimAxle=i;customPreview=equippedChoice();customSearch.clear();customPage=0;}}
        if(customGroup==4&&button({957,161,252,26},"RÉGLAGES [F9]",true))openSuspension();
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
        auto fit=cosmeticPicker?cosmeticFit(profile,customPreview):CosmeticFit{};
        auto preview=buildVehicle(garagePreviewProfile());
        const auto* visual=cosmeticPicker?findCosmetic(customPreview):nullptr;
        text(!fit.supported?"Indisponible sur cette carrosserie":visual?TextFormat("Poids : %+.1f kg • aucun gain de puissance",visual->weight*.45359237):rimPicker?"Style visuel • aucun gain de puissance":TextFormat("Gain : %+.0f HP  |  avec NOS : %+.0f HP",preview.boostedHp-configuration.boostedHp,preview.nitroHp-configuration.nitroHp),761,537,13,Muted);
        if(selected&&hit({759,509,335,45}))tooltipText=TextFormat("%s | statistique %.0f | poids relatif %.0f | valeur catalogue $%.0f",selected->name,selected->stat,selected->weight,selected->value);
        if(selected)if(const auto* e=pcEngine(selected->id)){
            text(TextFormat("%.1f L | %.0f HP | %.0f tr/min | %s",e->litres,selected->stat,e->redlineRpm,simulatedPack(e->id)?"son simule":"son adapte"),761,551,11,Gold);
        }
        if(fit.partial)text("Kit partiel : panneaux absents conservés d'origine",761,551,11,Gold);
        bool equipped=equippedChoice()==customPreview;
        if(button({1102,512,145,43},equipped?"ÉQUIPÉ":customPreview||rimPicker?"ÉQUIPER":"RETIRER",true,!equipped&&!choices.empty()&&fit.supported))equipGarageChoice();
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
        if(button({1000,8,205,32},"MES VOITURES F11"))openSavedCars();
        if(iconButton({1222,8,36,33},original_ui::buttons[37],"Paramètres PC"))openOptions();
        if(iconButton({1171,65,88,80},original_ui::garageIcons[10],"Prendre la route"))queued=[this]{saveCar();beginFree();};
        pxText("ROUTE",1190,142,13);
        text(garageEngine.running?TextFormat("G : COUPER   Z : GAZ   %i tr/min%s",int(garageEngine.state.rpm),garageEngine.limiting?"  RUPTEUR":""):"G : DÉMARRER   Z : GAZ",327,145,15,garageEngine.running?Accent:Muted);
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
            text("Sons du jeu • adaptations PC pour les nouveaux moteurs",305,219,17,Muted);
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
            const auto* pack=simulatedPack(profile.parts[0]);
            text(pack?std::string("AUTO : simulation ")+pack->name:"AUTO : son du moteur équipé ; moteur stock à confirmer.",305,503,pack?14:16,Muted);
            if(button({720,539,227,39},"FERMER",true)){audioPopup=false;audioPreviewUntil=0;}
        }
    }

    void openSavedCars(){
        garageEngine.stop();audio.stopEngine();audioPopup=false;powerPopup=false;audioPreviewUntil=0;
        savedEntries=savedCars(args.data/"cars");savedName=profile.savedName.empty()?vehicleIdentity(profile.car,profile.contentSource==1).name:profile.savedName;
        savedNameFocused=false;savedSelection=0;savedPage=0;notice.clear();screen=Screen::Collection;
    }
    void storeCurrentCar(bool update){
        int id=update?savedSelection:nextSavedCarId(args.data/"cars");if(update&&!id)return;
        Profile copy=profile;copy.savedName=savedName.empty()?"Ma voiture":savedName;std::string error;
        if(!storeSavedCar(args.data/"cars",id,copy,error)){notice="Enregistrement impossible : "+error;return;}
        profile.savedName=copy.savedName;saveCar();
        savedEntries=savedCars(args.data/"cars");savedSelection=id;savedName=copy.savedName;savedNameFocused=false;
        for(std::size_t i=0;i<savedEntries.size();i++)if(savedEntries[i].id==id)savedPage=int(i)/6;
        notice=update?"CONFIGURATION MISE À JOUR":"VOITURE ENREGISTRÉE";
    }
    void loadSelectedCar(){
        for(const auto& entry:savedEntries)if(entry.id==savedSelection){
            profile=entry.profile;saveCar();openCustomization();notice="VOITURE CHARGÉE : "+profile.savedName;return;
        }
    }
    void savedCarsScene(){
        card({35,32,1210,650},Color{16,22,29,250});text("MES VOITURES",68,56,31,Accent);
        text("Enregistrez la voiture équipée ; chargez une sauvegarde pour la retrouver.",68,96,17,Muted);
        Rectangle field{68,132,730,47};DrawRectangleRec(field,Color{43,43,49,255});DrawRectangleLinesEx(field,savedNameFocused?2:1,savedNameFocused?Accent:Muted);
        text(savedName.empty()?"Nom de la voiture...":savedName,82,146,19,savedName.empty()?Muted:WHITE);
        if(uiEnabled&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT))savedNameFocused=hit(field);
        if(button({824,132,385,47},"ENREGISTRER UNE NOUVELLE",true))storeCurrentCar(false);
        int pages=std::max(1,(int(savedEntries.size())+5)/6);savedPage=std::clamp(savedPage,0,pages-1);
        for(int row=0;row<6;row++){
            int index=savedPage*6+row;if(index>=int(savedEntries.size()))break;const auto& entry=savedEntries[index];
            Rectangle r{float(68+(row%2)*582),float(207+(row/2)*106),559,91};
            DrawRectangleRec(r,savedSelection==entry.id?Color{47,73,68,255}:Color{32,42,51,255});DrawRectangleLinesEx(r,1,savedSelection==entry.id?Accent:Muted);
            auto name=entry.profile.savedName.empty()?"Voiture "+std::to_string(entry.id):entry.profile.savedName;
            text(name.substr(0,38),r.x+16,r.y+10,21);auto build=buildVehicle(entry.profile);
            const auto* engine=findPart(entry.profile.parts[0]);
            text(std::string(vehicleIdentity(entry.profile.car,entry.profile.contentSource==1).name).substr(0,47),r.x+16,r.y+38,16,Muted);
            text(TextFormat("%.0f HP | %i rapports | %s",build.boostedHp,entry.profile.gearCount,engine?engine->name:"Moteur stock"),r.x+16,r.y+63,13,Accent);
            if(hit(r)&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){savedSelection=entry.id;savedName=entry.profile.savedName;savedNameFocused=false;}
        }
        if(savedEntries.empty())text("Aucune voiture enregistrée. Donnez un nom à votre première configuration.",92,307,22,Muted);
        if(button({68,543,43,31},"<",false,savedPage>0))--savedPage;
        text(TextFormat("%i / %i  |  %i voitures",savedPage+1,pages,int(savedEntries.size())),132,552,16,Muted);
        if(button({450,543,43,31},">",false,savedPage+1<pages))++savedPage;
        if(button({68,596,305,48},"CHARGER",true,savedSelection>0))loadSelectedCar();
        if(button({392,596,305,48},"METTRE À JOUR",false,savedSelection>0))storeCurrentCar(true);
        if(button({904,596,305,48},"RETOUR GARAGE"))openCustomization();
        if(!notice.empty())text(notice.substr(0,87),68,658,16,Accent);
    }
    void savedCarsKeyboard(){
        if(savedNameFocused){
            bool ctrl=IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL);
            if(ctrl&&IsKeyPressed(KEY_A))savedName.clear();
            for(int c=GetCharPressed();c>0;c=GetCharPressed())if(!ctrl&&c>=32&&c!=127){
                int size=0;const char* utf8=CodepointToUTF8(c,&size);
                if(savedName.size()+size<=40)savedName.append(utf8,size);
            }
            if((IsKeyPressed(KEY_BACKSPACE)||IsKeyPressedRepeat(KEY_BACKSPACE))&&!savedName.empty()){
                std::size_t end=savedName.size()-1;while(end>0&&(static_cast<unsigned char>(savedName[end])&0xc0)==0x80)--end;savedName.erase(end);
            }
            if(IsKeyPressed(KEY_ENTER))storeCurrentCar(false);
        }else{
            if(IsKeyPressed(KEY_ENTER)&&savedSelection)loadSelectedCar();
            if(IsKeyPressed(KEY_PAGE_DOWN))++savedPage;
            if(IsKeyPressed(KEY_PAGE_UP))--savedPage;
        }
    }
    void openSuspension(){suspensionDraft=profile;screen=Screen::Suspension;notice.clear();}
    void commitSuspension(){sanitizeSuspension(suspensionDraft);profile=suspensionDraft;saveCar();notice="Suspension enregistrée.";}
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
    void suspensionScene(){
        crop(original_ui::garages[garageStyle%5],{0,0,1280,720});
        auto preview=buildVehicle(suspensionDraft);
        car(suspensionDraft.car,suspensionDraft.rim,150,245,2.5,0,true,preview.tireFrame,preview.rideOffset,preview.exhaustFrame,-1,&suspensionDraft);
        card({34,18,1212,81});text("RÉGLAGES SUSPENSION",57,34,28,Accent);
        text("Hauteur, ressorts, amortissement et équilibre de la voiture",57,72,16,Muted);
        if(button({1040,35,180,43},"RETOUR"))screen=Screen::Customization;
        card({734,120,510,491});
        auto slider=[&](int row,const char* name,double& value,double lo,double hi,double step,const std::string& label){
            float y=143+row*86;text(name,754,y,18,Muted);text(label,1037,y,18,Accent);
            if(button({754,y+30,33,30},"-"))value=std::max(lo,value-step);
            ratioSlider({802,y+40,374,10},value,lo,hi);
            if(button({1190,y+30,33,30},"+"))value=std::min(hi,value+step);
        };
        slider(0,"HAUTEUR (ajustement)",suspensionDraft.rideHeightMm,-60,120,5,TextFormat("%+.0f mm",suspensionDraft.rideHeightMm));
        slider(1,"RIGIDITÉ DES RESSORTS",suspensionDraft.springStiffness,.4,3,.1,TextFormat("×%.2f",suspensionDraft.springStiffness));
        slider(2,"AMORTISSEMENT",suspensionDraft.dampingRatio,.25,1.5,.05,TextFormat("%.2f",suspensionDraft.dampingRatio));
        slider(3,"MASSE AVANT / ARRIÈRE",suspensionDraft.frontBias,-.15,.15,.01,TextFormat("%.0f / %.0f %%",preview.vehicle.frontWeightFraction*100,(1-preview.vehicle.frontWeightFraction)*100));
        // Same weight adjustment, with the actual static 50/50 reference marked.
        double baseFront=preview.vehicle.drive==DriveLayout::Front?.60:.48;
        float balancedX=802+float((.5-baseFront+.15)/.30)*374;
        DrawLine(int(balancedX),435,int(balancedX),456,Gold);
        text("ARRIÈRE",802,422,11,Muted);text("AVANT",1138,422,11,Muted);
        if(button({balancedX-71,465,142,22},"50/50",std::abs(preview.vehicle.frontWeightFraction-.5)<.005))suspensionDraft.frontBias=.5-baseFront;
        if(button({754,493,469,43},suspensionDraft.allowWheelie?"WHEELIE : AUTORISÉ":"WHEELIE : LIMITÉ AU SOL",suspensionDraft.allowWheelie))suspensionDraft.allowWheelie=!suspensionDraft.allowWheelie;
        text(preview.vehicle.wheelieBar?"Wheelie bar équipée : appui arrière contre le cabrage.":"Un wheelie exige assez de couple et d'adhérence.",754,553,14,Muted);
        text(TextFormat("Avant %.0f kg / Arrière %.0f kg",preview.vehicle.mass*preview.vehicle.frontWeightFraction,preview.vehicle.mass*(1-preview.vehicle.frontWeightFraction)),754,576,14,Muted);
        card({34,424,674,85});
        pxText("WHEELIE",54,434,17,WHITE);pxText("BALANCED",529,434,17,WHITE);
        Rectangle tuneTrack{54,466,634,22};
        if(uiEnabled&&IsMouseButtonDown(MOUSE_BUTTON_LEFT)&&CheckCollisionPointRec(mouse,{54,456,634,42}))suspensionDraft.wheelieTune=std::round(std::clamp(double((mouse.x-tuneTrack.x)/tuneTrack.width),0.0,1.0)*100)/100;
        if(uiEnabled&&IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){if(hit({54,430,155,25}))suspensionDraft.wheelieTune=0;else if(hit({529,430,159,25}))suspensionDraft.wheelieTune=1;}
        DrawRectangleRec(tuneTrack,Color{21,80,140,255});
        float tuneX=tuneTrack.x+float(suspensionDraft.wheelieTune)*tuneTrack.width;
        DrawRectangle(int(tuneTrack.x),int(tuneTrack.y),int(tuneX-tuneTrack.x),int(tuneTrack.height),Color{44,133,222,255});
        DrawRectangle(int(tuneX)-10,459,20,36,Color{210,215,219,255});DrawRectangle(int(tuneX)-10,459,20,5,WHITE);
        text("Cabrage",54,496,10,Muted);text("Stabilité au départ",548,496,10,Muted);
        card({34,519,674,92});text("PRÉRÉGLAGES",53,535,16,Muted);
        if(button({53,562,153,33},"ROUTE"))applySuspensionPreset(suspensionDraft,SuspensionPreset::Road);
        if(button({214,562,153,33},"DRAG"))applySuspensionPreset(suspensionDraft,SuspensionPreset::Drag);
        if(button({375,562,153,33},"PISTE"))applySuspensionPreset(suspensionDraft,SuspensionPreset::Track);
        if(button({536,562,151,33},"WHEELIE"))applySuspensionPreset(suspensionDraft,SuspensionPreset::Wheelie);
        if(button({34,644,244,46},"ANNULER")){screen=Screen::Customization;}
        if(button({489,644,288,46},"ENREGISTRER",true))commitSuspension();
        if(button({797,644,447,46},"ENREGISTRER ET PRENDRE LA ROUTE",true))queued=[this]{commitSuspension();beginFree();};
        if(!notice.empty())text(notice,57,619,16,Accent);
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
            bool isFront=p.foreground||(p.kind!=EffectKind::Smoke&&p.kind!=EffectKind::BrakeSmoke);if(isFront!=front)continue;
            float fade=float(1-p.age/p.life);const art::Frame* sprite=nullptr;float scale=float(p.scale);Vector2 origin{19,15};Color color=Fade(WHITE,fade*.65f);float rotation=0;
            if(p.kind==EffectKind::Smoke||p.kind==EffectKind::BrakeSmoke){sprite=p.kind==EffectKind::Smoke?&art::smoke[0]:&art::smoke2[0];scale*=float(1+p.age*2);color=Fade(Color{p.tint[0],p.tint[1],p.tint[2],255},fade*.65f);}
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
            if(std::clamp(int(std::round(drive.lane)),0,2)==lane)car(profile.car,profile.rim,360,269+float(drive.lane)*96,1.25,scene::wheelAngle(drive.player.frontRollDistance,drive.vehicle.wheelRadius),true,configuration.tireFrame,configuration.rideOffset,configuration.exhaustFrame,scene::wheelAngle(drive.player.rearRollDistance,drive.vehicle.wheelRadius),&profile,&drive.player);
        }
        renderEffects(true);
        if(drive.collisionCooldown>1.0)DrawRectangle(0,0,1280,720,Fade(RED,.10f));
        DrawRectangle(0,0,1280,86,Fade(Ink,.93f));text("MODE LIBRE",35,23,30);text(TextFormat("%.2f km",drive.player.position/1000),280,31,20,Muted);
        if(!drive.trafficEnabled)text("TRAFIC DÉSACTIVÉ",445,32,17,Muted);
        if(button({814,17,238,51},"PARAMÈTRES"))openOptions();
        if(button({1066,17,177,51},paused?"REPRENDRE":"PAUSE"))paused=!paused;
        card({29,578,275,111});text(TextFormat("%03i",int(drive.player.speed*3.6)),52,587,60);text("km/h",192,620,22,Muted);
        text(TextFormat("%.0f HP moteur",drive.player.powerHp),344,560,16,Gold);
        text(std::string("ABS ")+(drive.vehicle.abs?(drive.player.absActive?"ACTIF":"ON"):"OFF")+"   TC "+(drive.vehicle.tractionControl?(drive.player.tcActive?"ACTIF":"ON"):"OFF"),34,551,15,(drive.player.absActive||drive.player.tcActive)?Gold:Muted);
        if(drive.player.wheelieBarContact)text("WHEELIE BAR",742,560,16,Accent);
        else if(drive.player.frontLift>.02)text("WHEELIE",742,560,16,Accent);
        if(drive.player.burningOut)text("BURNOUT",580,560,17,Accent);
        else if(drive.player.launchClutch&&drive.player.wheelSlip>.15)text("PATINAGE",580,560,17,Accent);
        else if(drive.player.neutral)text("POINT MORT",580,560,17,Accent);
        else if(drive.player.handbraking)text("FREIN À MAIN",580,560,17,Gold);
        card({320,578,563,111});text(std::string(profile.automatic?"AUTO  •  ":"MANUELLE  •  ")+driveLabel(),344,595,17,Accent);
        text("Z / ↑ Accélérer   S / ↓ Freiner   1re + les deux : burnout",344,625,17);
        text("← / → Voies   E/C Rapports   T Boîte   Espace F.à main   N NOS   V Neutre",344,655,14,Muted);
        card({900,578,350,111});text(drive.player.neutral?"N":TextFormat("%i",drive.player.gear),927,596,57,Gold);
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
        text("PARAMÈTRES",211,66,30);text("AFFICHAGE, SON ET CONDUITE",211,110,15,Accent);
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
        if(button({212,551,410,30},edited.abs?"ABS : ACTIVÉ":"ABS : DÉSACTIVÉ",edited.abs))edited.abs=!edited.abs;
        if(button({657,551,410,30},edited.tractionControl?"ANTIPATINAGE : ACTIVÉ":"ANTIPATINAGE : DÉSACTIVÉ",edited.tractionControl))edited.tractionControl=!edited.tractionControl;
        text(edited.mode==WindowMode::Borderless?"Sans bordure : la fenêtre suit la taille du bureau.":"VSync : la fréquence de l'écran peut limiter les FPS.",212,584,11,Muted);
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
        EffectSources sources;sources.tireFrame=configuration.tireFrame;sources.rearWheel=360+wheels.rear*1.25;sources.frontWheel=360+wheels.front*1.25;sources.wheelY=baseY+(wheels.y+wheels.radius)*1.25;
        auto pose=chassisPose(wheels.rear,wheels.front,wheels.y,drive.vehicle,drive.player,configuration.rideOffset);
        auto rear=pose.wheel(false),front=pose.wheel(true);
        sources.rearWheel=360+rear.x*1.25;sources.frontWheel=360+front.x*1.25;
        sources.rearWheelY=baseY+(rear.y+wheels.radius)*1.25;sources.frontWheelY=baseY+(front.y+wheels.radius)*1.25;
        auto pipe=installedExhaust(profile,configuration.exhaustFrame,configuration.rideOffset);
        sources.outletCount=pipe.count;
        for(int i=0;i<pipe.count;i++){
            auto point=pose.body(pipe.outlets[i].x,pipe.outlets[i].y);auto& o=sources.outlets[i];
            o=pipe.outlets[i];o.x=360+point.x*1.25;o.y=baseY+point.y*1.25;
            o.dx=std::cos(pose.pitch)*pipe.outlets[i].dx+std::sin(pose.pitch)*pipe.outlets[i].dy;
            o.dy=-std::sin(pose.pitch)*pipe.outlets[i].dx+std::cos(pose.pitch)*pipe.outlets[i].dy;
        }
        return sources;
    }
    void controls(double dt){
        if((IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL))&&IsKeyPressed(KEY_Q)){quit=true;return;}
        if(IsKeyPressed(KEY_K)&&(screen==Screen::Free||screen==Screen::Garage||screen==Screen::Customization)&&!searchFocused){profile.headlights=!profile.headlights;saveCar();}
        if(IsKeyPressed(KEY_F10)){if(confirming)revert();Settings safe;safe.width=960;safe.height=540;safe.vsync=false;safe.fps=60;apply(safe);edited=settings;options=true;notice="Affichage de secours. Appliquez vos réglages pour les enregistrer.";}
        if(IsKeyPressed(KEY_ESCAPE)){if(confirming)revert();else if(options)options=false;else if(powerPopup)powerPopup=false;else if(audioPopup){audioPopup=false;audioPreviewUntil=0;}else if(screen==Screen::Free)paused=!paused;else if(screen==Screen::Garage||screen==Screen::Customization){if(searchFocused)searchFocused=false;else if(inventoryOpen)inventoryOpen=false;else{saveCar();screen=Screen::Menu;}}else if(screen==Screen::Transmission||screen==Screen::Suspension||screen==Screen::Collection){screen=Screen::Customization;}}
        if(!confirming&&IsKeyPressed(KEY_ENTER)&&(IsKeyDown(KEY_LEFT_ALT)||IsKeyDown(KEY_RIGHT_ALT))){openOptions();edited.mode=settings.mode==WindowMode::Windowed?WindowMode::Borderless:WindowMode::Windowed;queued=[this]{preview();};}
        if(confirming&&GetTime()>=deadline)revert();
        if(IsKeyPressed(KEY_F3)&&screen!=Screen::Garage&&screen!=Screen::Customization){settings.showFps=!settings.showFps;edited.showFps=settings.showFps;}
        if(screen==Screen::Collection&&!options&&!confirming)savedCarsKeyboard();
        DriverInput input{IsKeyDown(KEY_Z)||IsKeyDown(KEY_W)||IsKeyDown(KEY_UP),IsKeyDown(KEY_S)||IsKeyDown(KEY_DOWN),profile.automatic,IsKeyDown(KEY_N),IsKeyDown(KEY_L),IsKeyDown(KEY_SPACE),IsKeyDown(KEY_V)};
        if((screen==Screen::Customization||screen==Screen::Garage)&&!options&&!confirming&&!audioPopup&&!powerPopup)garageKeyboard();
        if(screen==Screen::Free&&!paused&&!options&&!confirming){
            if(IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_A)||IsKeyPressed(KEY_Q))drive.changeLane(-1);
            if(IsKeyPressed(KEY_RIGHT)||IsKeyPressed(KEY_D))drive.changeLane(1);
            if(!input.neutral&&(IsKeyPressed(KEY_E)||IsKeyPressed(KEY_LEFT_SHIFT)))shift(drive.player,1,drive.vehicle);
            if(!input.neutral&&IsKeyPressed(KEY_C))shift(drive.player,-1,drive.vehicle);
            if(IsKeyPressed(KEY_T)){profile.automatic=!profile.automatic;input.automatic=profile.automatic;saveCar();}
            if(args.smoke)input={true,frames>=260&&frames<267,true,frames>=235};
            accumulator+=dt;while(accumulator>=Step){drive.update(input,Step);accumulator-=Step;}
            auto sources=effectSources();
            const Part* exhaust=findPart(profile.parts[int(PartSlot::Exhaust)]);
            effects.update(drive.player,drive.vehicle,input,sources,drive.collisionCooldown,dt,exhaust!=nullptr);
        }else accumulator=0;
        bool garageScreen=screen==Screen::Garage||screen==Screen::Customization;
        if(!garageScreen&&garageEngine.running){garageEngine.stop();audio.stopEngine();}
        bool garageAvailable=garageScreen&&!options&&!confirming&&!powerPopup&&!audioPopup;
        bool garageGas=garageAvailable&&!searchFocused&&IsKeyDown(KEY_Z);
        if(garageAvailable)garageEngine.update(configuration.vehicle,garageGas,dt);
        bool driving=screen==Screen::Free&&!paused&&!options&&!confirming;
        if(driving&&IsKeyPressed(KEY_H))audio.horn(settings.sound);
        if(audioPopup&&GetTime()<audioPreviewUntil){CarState preview;preview.rpm=4000;
            audio.update(profile,configuration.vehicle,preview,{previewGas,false,true},0,true,settings.sound);
        }else if(garageEngine.running&&garageAvailable){
            audio.update(profile,configuration.vehicle,garageEngine.state,{garageGas,false,true},0,true,settings.sound,garageEngine.limiting);
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
        if(screen==Screen::Menu)menu();else if(screen==Screen::Garage)garage();else if(screen==Screen::Customization)customizationScene();else if(screen==Screen::Transmission)transmissionScene();else if(screen==Screen::Suspension)suspensionScene();else if(screen==Screen::Collection)savedCarsScene();else freeScene();
        if(options){uiEnabled=!confirming;settingsScene();}
        if(confirming){uiEnabled=true;confirmScene();}
        if(!tooltipText.empty()&&!options&&!confirming&&!audioPopup&&!powerPopup){float width=std::min(850.f,MeasureTextEx(font,tooltipText.c_str(),15,0).x+22);float x=std::clamp(mouse.x+12,8.f,1270-width),y=std::clamp(mouse.y-40,55.f,670.f);DrawRectangle(int(x),int(y),int(width),31,Color{15,15,18,248});DrawRectangleLines(int(x),int(y),int(width),31,Accent);text(tooltipText,x+10,y+8,15);}
        if(settings.showFps){bool inGarage=(screen==Screen::Garage||screen==Screen::Customization)&&!options&&!confirming;bool inTuning=(screen==Screen::Transmission||screen==Screen::Suspension)&&!options&&!confirming;
            float x=inGarage?1040:inTuning?1050:1121,y=inGarage?55:inTuning?74:691;
            DrawRectangle(int(x),int(y),inGarage?110:151,24,Ink);text(TextFormat("%i FPS",GetFPS()),x+12,y+4,inGarage?14:16,Accent);
        }
        if(args.smoke&&frames>=420&&frames<=431)exhaustContactSheet();
        if(args.smoke&&frames>=552&&frames<=557)hoodContactSheet();
        if(args.smoke&&frames>=558&&frames<=560)materialsContactSheet();
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
    void hoodContactSheet(){
        bool original=frames>=555;rlDrawRenderBatchActive();DrawRectangle(0,0,1280,720,Color{44,46,53,255});
        text(std::string("POTS DE CAPOT / ")+(original?"ORIGINAL":"UNBOUND"),14,8,19,WHITE);
        text("Contact du pied sur le capot du kit installé ; points turquoise : bouches des particules.",14,34,13,Accent);
        const int bodies[]={22,20,20,156};
        for(int i=0;i<12;i++){
            int row=i/3,pipe=48+i%3;Profile sample;sample.car=bodies[row];sample.contentSource=original?1:0;
            if(row>=2)sample.cosmetics[5]=row==2?105007:105012;
            float x=8+424*(i%3),y=60+164*row;double ride=row==3?6:0;
            text(TextFormat("CAR %03i / POT %02i / AVANT %02i",sample.car+1,pipe,installedKit(sample,0)),x,y,13,WHITE);
            auto fit=installedExhaust(sample,pipe,ride);car(sample.car,10100,x+5,y+28,1.7f,0,false,0,ride,pipe,-1,&sample);
            for(int k=0;k<fit.count;k++){auto o=fit.outlets[k];Vector2 at{x+5+float(o.x)*1.7f,y+28+float(o.y)*1.7f};DrawCircleV(at,2,Accent);DrawLineV(at,{at.x+float(o.dx)*10,at.y+float(o.dy)*10},Accent);}
        }
    }
    void materialsContactSheet(){
        rlDrawRenderBatchActive();DrawRectangle(0,0,1280,720,Color{44,46,53,255});
        text("MATÉRIAUX / PALETTES ORIGINALES",14,8,22,Accent);
        text("Nuances source, intérieur et optiques séparés ; aucun éditeur de livrées.",14,36,13,WHITE);
        const int paints[]={85,50,86,89,83,49,24,105,15,14,90,91};
        for(int i=0;i<12;i++){
            float x=8+424*(i%3),y=60+164*(i/3);Profile sample;sample.car=20;sample.cosmetics[0]=100000+paints[i];sample.rollCage=true;sample.cosmetics[9]=109010;
            const auto* paint=findCosmetic(sample.cosmetics[0]);text(paint?paint->name:"",x,y,15,WHITE);
            car(sample.car,10100,x+5,y+28,1.7f,0,false,0,0,0,-1,&sample);
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
        if(frames==294){capture("motion-stationary-b.png");drive.player.speed=100/3.6;drive.player.position=100;drive.player.frontRollDistance=drive.player.rearRollDistance=100;}
        if(frames==297){capture("motion-100-a.png");drive.player.position+=100/3.6*.1;drive.player.frontRollDistance=drive.player.rearRollDistance=drive.player.position;}
        if(frames==300){capture("motion-100-b.png");drive.player.speed=200/3.6;drive.player.position=100;drive.player.frontRollDistance=drive.player.rearRollDistance=100;}
        if(frames==303){capture("motion-200-a.png");drive.player.position+=200/3.6*.1;drive.player.frontRollDistance=drive.player.rearRollDistance=drive.player.position;}
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
        for(int color=0;color<8;color++){
            int start=457+color*4;
            if(frames==start){
                profile=Profile{};profile.car=20;profile.factoryDrive=false;profile.drive=DriveLayout::Rear;equipPart(profile,PartSlot::Tires,10009+color);beginFree();
                DriverInput input{true,true,true,true};
                for(int tick=0;tick<240;tick++){drive.update(input,Step);effects.update(drive.player,drive.vehicle,input,effectSources(),0,Step,false);}
                check(drive.player.burningOut&&drive.player.speed==0&&drive.player.rearRollDistance>10&&drive.player.frontRollDistance==0&&!effects.particles.empty()&&std::all_of(effects.particles.begin(),effects.particles.end(),[&](const Particle& p){return p.tint==tireSmokeTint(9+color);}),"stationary first-gear burnout renders the equipped Burn Slicks colour at the driven axle");
            }
            if(frames==start+2)capture(TextFormat("burnout-%02i.png",color+9));
        }
        if(frames==490){beginFree();DriverInput input{true,false,true,true,false,false,true};for(int tick=0;tick<240;tick++)drive.update(input,Step);
            check(drive.player.neutral&&drive.player.rpm>7000&&drive.player.speed==0&&drive.player.gear==1&&!drive.player.nitroActive,"held neutral displays free engine revs without movement or NOS");}
        if(frames==492)capture("neutre-maintenu.png");
        if(frames==494){for(int tick=0;tick<120;tick++)drive.update({true,false,true},Step);check(!drive.player.neutral&&drive.player.speed>0,"releasing neutral reconnects the transmission and moves the car");}
        if(frames==496)capture("neutre-relache.png");
        if(frames==499){profile=Profile{};profile.car=20;profile.factoryDrive=false;profile.drive=DriveLayout::Rear;equipBestParts(profile);openSuspension();
            suspensionDraft.rideHeightMm=120;suspensionDraft.springStiffness=.5;suspensionDraft.dampingRatio=.3;suspensionDraft.frontBias=-.15;suspensionDraft.allowWheelie=true;suspensionDraft.wheelieTune=0;commitSuspension();
            auto loaded=loadProfile(profileFile(),191,54);check(loaded.rideHeightMm==120&&loaded.springStiffness==.5&&loaded.allowWheelie,"garage suspension tuning survives save and reload");}
        if(frames==502)capture("suspension-reglages.png");
        if(frames==503){settings.abs=true;settings.tractionControl=true;beginFree();CarState best;
            for(int tick=0;tick<720;tick++){drive.update({true,false,true,true},Step);if(drive.player.frontLift>best.frontLift)best=drive.player;}
            drive.player=best;auto sources=effectSources();effects.update(drive.player,drive.vehicle,{true,false,true,true},sources,0,Step,true);
            check(drive.player.frontLift>.1&&drive.player.frontLoad==0&&sources.frontWheelY<sources.rearWheelY,"rendered wheelie setup uses actual front contact loss and lifted wheel anchors");}
        if(frames==506)capture("wheelie-drag.png");
        if(frames==507){profile.allowWheelie=false;beginFree();for(int tick=0;tick<720;tick++)drive.update({true,false,true,true},Step);check(drive.player.peakFrontLift==0,"grounded setup keeps both tyres on the contact plane under full preparation");}
        if(frames==510)capture("chassis-au-sol.png");
        if(frames==511){openOptions();edited.abs=false;edited.tractionControl=false;preview();keep();check(!drive.vehicle.abs&&!drive.vehicle.tractionControl&&!loadSettings(settingFile()).abs&&!loadSettings(settingFile()).tractionControl,"ABS and traction control toggles apply to live driving and persist");}
        if(frames==514)capture("aides-conduite.png");
        if(frames==515){edited.abs=true;edited.tractionControl=true;preview();check(drive.vehicle.abs&&drive.vehicle.tractionControl,"unconfirmed driving-aid preview changes the live model");deadline=GetTime()-1;}
        if(frames==516){check(!drive.vehicle.abs&&!drive.vehicle.tractionControl,"timed-out aid settings restore the prior live state");options=false;}
        if(frames==517){profile=Profile{};settings.abs=true;settings.tractionControl=true;beginFree();drive.player.speed=100/3.6;drive.player.gear=4;for(int tick=0;tick<30;tick++)drive.update({false,true,true},Step);
            check(drive.player.absActive&&!drive.player.frontLocked&&!drive.player.rearLocked,"ABS regulates the rendered service-braking stop without locked wheels");}
        if(frames==520)capture("abs-actif.png");
        if(frames==521){settings.abs=false;beginFree();drive.player.speed=100/3.6;drive.player.gear=4;for(int tick=0;tick<30;tick++)drive.update({false,true,true},Step);
            check(drive.player.frontLocked&&drive.player.rearLocked&&drive.player.frontRollDistance==0,"disabled ABS renders a stop with locked wheel rotation");}
        if(frames==524)capture("freins-bloques.png");
        if(frames==525){profile=Profile{};profile.car=20;profile.factoryDrive=false;profile.drive=DriveLayout::Rear;equipBestParts(profile);settings.tractionControl=true;beginFree();CarState bestCut;for(int tick=0;tick<120;tick++){drive.update({true,false,true},Step);if(drive.player.speed>2&&drive.player.tractionFactor<bestCut.tractionFactor)bestCut=drive.player;}drive.player=bestCut;
            check(drive.player.tcActive&&drive.player.tractionFactor<1,"traction-control indicator follows a real wheel-torque reduction");}
        if(frames==528)capture("antipatinage-actif.png");
        if(frames==529){settings.tractionControl=false;beginFree();for(int tick=0;tick<60;tick++)drive.update({true,false,true},Step);auto sources=effectSources();effects.update(drive.player,drive.vehicle,{true,false,true},sources,0,Step,false);
            check(!drive.player.tcActive&&drive.player.wheelSlip>.5,"disabled traction control permits excess-power tyre slip");}
        if(frames==532)capture("antipatinage-desactive.png");
        if(frames==534){profile=Profile{};profile.car=20;profile.cosmetics[0]=100085;saveCar();openCustomization();inventoryOpen=false;check(materials::paintRow({34,79,223,255},false)>=0,"source paint mask is active in the PC garage renderer");}
        if(frames==537)capture("peinture-mate.png");
        if(frames==538){profile.cosmetics[0]=100050;saveCar();}
        if(frames==541)capture("peinture-brillante.png");
        if(frames==542){profile.cosmetics[0]=100086;saveCar();check(atlases.count(3000)==1,"source stationary rim material atlas is loaded by the native renderer");}
        if(frames==545)capture("peinture-chrome.png");
        if(frames==546){equipRim(profile,10100,1);equipRim(profile,10101,2);saveCar();chooseGroup(1,-1,true);rimAxle=2;
            auto saved=loadProfile(profileFile(),191,54);check(saved.rim==10100&&rearRimId(saved)==10101,"garage front and rear rim choices persist independently");}
        if(frames==550)capture("jantes-essieux.png");
        if(frames==554)capture("capots-unbound.png");
        if(frames==557)capture("capots-original.png");
        if(frames==560)capture("materiaux-source.png");
        if(frames==561){profile=Profile{};profile.car=20;const Cosmetic* missing=nullptr;
            for(int body=0;body<191&&!missing;body++){profile.car=body;for(const auto& c:CosmeticCatalog)if(!cosmeticFit(profile,c.id).supported){missing=&c;break;}}
            saveCar();
            if(missing){chooseCosmetic(missing->slot);customPreview=missing->id;auto before=profile.cosmetics[missing->slot];equipGarageChoice();check(profile.cosmetics[missing->slot]==before,"incompatible cosmetic choice cannot silently equip a missing body variant");}
            else check(false,"source compatibility example is available");}
        if(frames==564)capture("compatibilite-accessoires.png");
        if(frames==565){profile=Profile{};profile.car=20;equipBestParts(profile);applySuspensionPreset(profile,SuspensionPreset::Drag);openSuspension();commitSuspension();
            auto saved=loadProfile(profileFile(),191,54);check(!saved.allowWheelie&&saved.rideHeightMm==-10&&saved.dampingRatio==.9,"drag preset saves a controlled launch separately from the wheelie preset");}
        if(frames==567)capture("drag-reglages.png");
        if(frames==568){settings.tractionControl=true;beginFree();for(int tick=0;tick<600;tick++)drive.update({true,false,true,true},Step);
            check(drive.player.peakFrontLift==0&&drive.player.position>20,"drag launch progresses with both wheels on the ground");}
        if(frames==571)capture("drag-depart.png");
        if(frames==572){profile=Profile{};profile.car=20;profile.factoryDrive=false;profile.drive=DriveLayout::Rear;equipBestParts(profile);applySuspensionPreset(profile,SuspensionPreset::Wheelie);profile.cosmetics[6]=106011;settings.tractionControl=true;beginFree();
            for(int tick=0;tick<600;tick++)drive.update({true,false,true,true},Step);
            check(profile.allowWheelie&&drive.vehicle.wheelieBar&&drive.player.wheelieBarTouched&&drive.player.peakFrontLift<.01,"equipped source DRAG PRO rear roller arrests wheelie without changing the garage tuning");}
        if(frames==574)capture("wheelie-bar-appui.png");
        if(frames==575){openSuspension();suspensionDraft.frontBias=.5-(effectiveDrive(suspensionDraft)==DriveLayout::Front?.60:.48);commitSuspension();
            check(std::abs(configuration.vehicle.frontWeightFraction-.5)<1e-9&&profile.allowWheelie,"balanced static weight setting preserves independent wheelie tuning");}
        if(frames==577)capture("balance-repartition.png");
        if(frames==578){suspensionDraft.wheelieTune=1;commitSuspension();check(loadProfile(profileFile(),191,54).wheelieTune==1,"blue wheelie-to-balanced control persists independently of static axle balance");}
        if(frames==580)capture("reglage-wheelie-balanced.png");
        if(frames==583){beginFree();for(int tick=0;tick<240;tick++)drive.update({true,false,true,true,false,true},Step);
            check(drive.player.handbraking&&drive.player.rpm>7000&&drive.player.speed==0&&drive.player.rearRollDistance==0&&!drive.player.nitroActive,"handbrake permits free engine revs while locking the rear wheels without NOS");}
        if(frames==585)capture("frein-main-regime.png");
        if(frames==586){for(int tick=0;tick<120;tick++)drive.update({true,false,true},Step);check(!drive.player.handbraking&&drive.player.position>1,"releasing handbrake with throttle reconnects and launches the vehicle");}
        if(frames==588)capture("frein-main-depart.png");
        if(frames==590){settings.tractionControl=false;beginFree();for(int tick=0;tick<240;tick++)drive.update({true,false,true,false,false,true},Step);
            for(int tick=0;tick<90;tick++){drive.update({true,false,true},Step);effects.update(drive.player,drive.vehicle,{true,false,true},effectSources(),0,Step,false);}
            check(drive.player.launchSlipDistance>3&&drive.player.rearRollDistance>drive.player.frontRollDistance+3,"rev limiter handbrake release with TC off transmits stored RPM into actual driven-wheel spin");}
        if(frames==592)capture("depart-rupteur-patinage.png");
        if(frames==593){settings.tractionControl=true;beginFree();for(int tick=0;tick<240;tick++)drive.update({true,false,true,false,false,false,true},Step);
            for(int tick=0;tick<90;tick++){drive.update({true,false,true},Step);effects.update(drive.player,drive.vehicle,{true,false,true},effectSources(),0,Step,false);}
            check(drive.player.launchSlipDistance==0,"traction control regulates the same rev-limiter launch");}
        if(frames==595)capture("depart-rupteur-tc.png");
        if(frames==597){openCustomization();garageEngine.toggle(configuration.vehicle);check(garageEngine.running,"garage ignition starts the equipped engine");}
        if(frames==598){for(int tick=0;tick<240;tick++)garageEngine.update(configuration.vehicle,true,Step);check(garageEngine.limiting&&garageEngine.state.speed==0&&garageEngine.state.rpm<=configuration.vehicle.redlineRpm,"garage rev limiter uses installed engine redline without moving the vehicle");}
        if(frames==600)capture("garage-moteur-rupteur.png");
        if(frames==601){garageEngine.stop();check(!garageEngine.running&&garageEngine.state.rpm==0,"garage ignition stops the audition");}
        if(frames==603){profile=Profile{};profile.car=20;equipPart(profile,PartSlot::Engine,1501);saveCar();chooseGroup(0);customSearch="AMG";customPreview=1501;
            check(garageChoices()==std::vector<int>{1501}&&sourceLabel(choiceSource(1501))==std::string("EXTENSION PC"),"PC engine search and provenance are visible independently of recovered content");}
        if(frames==605)capture("moteurs-extension-pc.png");
        if(frames==606){equipPart(profile,PartSlot::Engine,1504);saveCar();inventoryOpen=false;garageEngine.toggle(configuration.vehicle);
            for(int tick=0;tick<480;tick++)garageEngine.update(configuration.vehicle,true,Step);
            check(garageEngine.limiting&&garageEngine.state.rpm>14500&&configuration.vehicle.redlineRpm==15000,"F1 PC swap revs to its own 15000 RPM garage limiter");}
        if(frames==608)capture("moteur-f1-rupteur.png");
        if(frames==609){garageEngine.stop();openSavedCars();savedName="F1 Drag";storeCurrentCar(false);
            check(savedEntries.size()==1&&savedEntries[0].profile.parts[0]==1504,"named car saves the full equipped engine configuration");}
        if(frames==611){profile.car=21;equipPart(profile,PartSlot::Engine,1501);saveCar();savedName="AMG Route";storeCurrentCar(false);
            check(savedEntries.size()==2&&savedEntries[0].profile.car==20&&savedEntries[1].profile.car==21,"saving another car preserves the earlier chassis and engine");}
        if(frames==613)capture("mes-voitures.png");
        if(frames==614){savedSelection=1;loadSelectedCar();check(profile.car==20&&profile.parts[0]==1504&&profile.savedName=="F1 Drag","loading a named car restores its chassis, engine and name");}
        if(frames==616)capture("voiture-chargee.png");
        if(frames==617)quit=true;

    }
    int run(){
        init();
        while(!WindowShouldClose()&&!quit){double dt=args.smoke?(frames>=290?0:1.0/30.0):std::clamp(double(GetFrameTime()),0.0,.1);controls(dt);renderFrame();if(IsKeyPressed(KEY_F12))capture(TextFormat("capture-%06i.png",frames));if(queued){auto action=std::move(queued);queued=nullptr;action();}if(args.smoke)smoke();frames++;}
        if(confirming)revert();
        saveCar();
        {std::error_code ec;fs::create_directories(args.data,ec);if(!ec){std::ofstream out(args.data/"last-session.txt");out<<"simulated_audio_engine="<<audio.simulatedStatus.engineId<<"\nsimulated_audio_stream_starts="<<audio.simulatedStatus.streamStarts<<"\nsimulated_audio_startups="<<audio.simulatedStatus.startupEvents<<"\nsimulated_audio_shutdowns="<<audio.simulatedStatus.shutdownEvents<<"\nsimulated_audio_gain="<<audio.simulatedStatus.gainSum<<"\ngarage_engine_running="<<garageEngine.running<<"\ngarage_engine_rpm="<<garageEngine.state.rpm<<"\ngarage_engine_limiter="<<garageEngine.limiting<<"\nscreen="<<int(screen)<<"\ncustom_group="<<customGroup<<"\ncustom_page="<<customPage<<"\ninventory_open="<<inventoryOpen<<"\nnitro_remaining="<<drive.player.nitroRemaining<<"\nnitro_active="<<drive.player.nitroActive<<"\nhandbraking="<<drive.player.handbraking<<"\nneutral="<<drive.player.neutral<<"\nlaunch_wheelspin="<<drive.player.launchClutch<<"\nlaunch_slip_seconds="<<drive.player.launchSlipSeconds<<"\nlaunch_slip_distance="<<drive.player.launchSlipDistance<<"\nwheel_slip="<<drive.player.wheelSlip<<"\nburnout="<<drive.player.burningOut<<"\nrpm="<<drive.player.rpm<<"\nabs_enabled="<<drive.vehicle.abs<<"\ntc_enabled="<<drive.vehicle.tractionControl<<"\nabs_active="<<drive.player.absActive<<"\ntc_active="<<drive.player.tcActive<<"\npitch_rad="<<drive.player.pitch<<"\nheave_m="<<drive.player.heave<<"\nwheelie_tune="<<profile.wheelieTune<<"\nwheelie_bar_installed="<<drive.vehicle.wheelieBar<<"\nwheelie_bar_touched="<<drive.player.wheelieBarTouched<<"\nfront_lift_m="<<drive.player.frontLift<<"\npeak_front_lift_m="<<drive.player.peakFrontLift<<"\nrear_lift_m="<<drive.player.rearLift<<"\nfront_load_n="<<drive.player.frontLoad<<"\nrear_load_n="<<drive.player.rearLoad<<"\nfront_roll_m="<<drive.player.frontRollDistance<<"\nrear_roll_m="<<drive.player.rearRollDistance<<"\ntraffic_enabled="<<drive.trafficEnabled<<"\ntraffic_count="<<(drive.trafficEnabled?drive.traffic.size():0)<<"\ndistance_m="<<drive.player.position<<"\nspeed_mps="<<drive.player.speed<<"\ntarget_lane="<<drive.targetLane<<"\ngear="<<drive.player.gear<<"\nfront_rim="<<profile.rim<<"\nrear_rim="<<rearRimId(profile)<<"\nengine_part="<<profile.parts[int(PartSlot::Engine)]<<"\ntire_part="<<profile.parts[int(PartSlot::Tires)]<<"\ngear_count="<<drive.vehicle.gearCount<<"\nfinal_drive="<<drive.vehicle.finalDrive<<"\nshift_seconds="<<drive.vehicle.shiftSeconds<<"\nnative_mass_kg="<<drive.vehicle.mass<<"\nnative_hp="<<configuration.boostedHp<<"\nnative_nos_hp="<<configuration.nitroHp<<"\ncurrent_hp="<<drive.player.powerHp<<"\nnative_torque_nm="<<drive.vehicle.torque<<"\ndrive_layout="<<int(drive.vehicle.drive)<<"\naudio_ready="<<audio.ready<<"\naudio_failures="<<audio.failures<<"\nframes="<<frames<<"\nmode="<<modeKey(settings.mode)<<"\nwidth="<<GetScreenWidth()<<"\nheight="<<GetScreenHeight()<<"\n";}}
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
    for(int i=1;i<argc;i++)if(std::string(argv[i])=="--smoke-test"||std::string(argv[i])=="--physics-benchmark-dir"||std::string(argv[i])=="--check-audio-dir"||std::string(argv[i])=="--check-customization-dir")diagnostic=true;
    try{
        Args args;
        for(int i=1;i<argc;i++){std::string a=argv[i];auto value=[&](){if(i+1>=argc)throw std::runtime_error("Argument manquant : "+a);return fs::absolute(fs::u8path(argv[++i]));};
            if(a=="--data-dir"){args.data=value();args.dataSpecified=true;}else if(a=="--assets-dir")args.assets=value();else if(a=="--capture-dir")args.capture=value();
            else if(a=="--check-audio-dir")args.audioCheck=value();
            else if(a=="--check-customization-dir")args.customizationCheck=value();
            else if(a=="--physics-benchmark-dir")args.benchmark=value();
            else if(a=="--safe-mode")args.safe=true;else if(a=="--free-drive")args.free=true;else if(a=="--smoke-test")args.smoke=true;else if(a=="--no-audio")args.noAudio=true;
            else if(a=="--help"){std::cout<<"PixelCarRacerNative [--safe-mode] [--free-drive] [--data-dir PATH] [--no-audio] [--physics-benchmark-dir NEW_PATH]\n";return 0;}else throw std::runtime_error("Argument inconnu : "+a);
        }
        if(!args.customizationCheck.empty()){setExecutableDirectory();if(args.assets.empty())args.assets=fs::current_path()/"assets";checkCustomization(args.assets,args.customizationCheck);return 0;}
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
