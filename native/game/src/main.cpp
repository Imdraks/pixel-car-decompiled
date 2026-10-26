#include "raylib.h"
#include "model.hpp"
#include "benchmark.hpp"
#include "game_audio.hpp"
#include "effects.hpp"
#include "platform.hpp"
#include "art.hpp"
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
    enum class Screen { Menu, Garage, Free, Customization } screen=Screen::Menu;
    Args args;
    Settings settings,edited,previous;
    Resolution windowLimit{1280,720};
    Profile profile; Build configuration;
    PartSlot customSlot=PartSlot::Engine; int customPreview=0,customPage=0; std::string customSearch;
    FreeDrive drive;DrivingEffects effects;
    Font font{};std::map<int,Texture2D> atlases;RenderTexture2D render{};
    GameAudio audio; bool audioPopup=false,previewGas=true;double audioPreviewUntil=0;
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
    void card(Rectangle r,Color color=Panel){DrawRectangleRounded(r,.07f,8,color);}
    bool hit(Rectangle r)const{return uiEnabled&&CheckCollisionPointRec(mouse,r);}
    bool button(Rectangle r,const std::string& label,bool primary=false,bool enabled=true){
        bool hover=enabled&&hit(r);Color fill=primary?Accent:Color{31,45,61,255};
        if(hover)fill=primary?Color{121,247,213,255}:Color{48,66,84,255};
        if(!enabled)fill=Color{31,38,46,255};
        DrawRectangleRounded(r,.13f,8,fill);
        float size=label.size()>29?17:20;
        auto width=MeasureTextEx(font,label.c_str(),size,0).x;
        text(label,r.x+(r.width-width)/2,r.y+(r.height-size)/2-1,size,enabled?(primary?Ink:WHITE):Muted);
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
    void car(int index,int rim,float x,float y,float scale,double speed,bool shadow=true,int tireFrame=0,double rideOffset=0){
        index=(index+191)%191;rim=(rim+54)%54;auto w=art::wheelPositions[index];tireFrame=std::clamp(tireFrame,0,int(std::size(art::tires))-1);
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
            centered(art::tires[tireFrame],wheelScale,31,31,float(speed*GetTime()*8));
            centered(art::rims[rim],wheelScale,31,31,float(speed*GetTime()*8));
        }
        frame(art::cars[index],x,y+float(rideOffset)*scale,scale);
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
        settings=s;accumulator=0;
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
    const char* driveLabel()const{return profile.drive==DriveLayout::Front?"TRACTION":profile.drive==DriveLayout::Rear?"PROPULSION":"4 ROUES MOTRICES";}
    void beginFree(){audio.reset();effects=DrivingEffects{};drive=FreeDrive{};configuration=buildVehicle(profile);drive.vehicle=configuration.vehicle;accumulator=0;screen=Screen::Free;options=false;paused=false;}
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
        if(!apply(settings)){Settings safe;safe.width=960;safe.height=540;if(!apply(safe))throw std::runtime_error("Impossible de créer la surface de rendu.");}
        edited=settings;
        if(!args.noAudio&&!args.smoke)audio.init(args.assets);
        if(args.free)beginFree();
    }
    void background(bool driving){
        ClearBackground(Ink);
        if(!driving){crop(art::garages[0],{0,0,1280,720},Color{145,154,172,255});DrawRectangle(0,0,1280,720,Fade(Ink,.74f));return;}
        double pos=drive.player.position;crop(art::sky[0],{0,0,1280,340});
        tiled(art::mountains[0],130,160,pos*.16,Color{150,167,190,255});
        if(settings.quality!=Quality::Low)tiled(art::cityFar[0],150,160,pos*.4,Color{152,171,193,220});
        tiled(art::trees[0],252,75,pos*.9,Color{104,132,130,255});
        DrawRectangle(0,318,1280,312,Color{45,49,59,255});
        DrawRectangle(0,322,1280,5,Color{230,222,176,255});DrawRectangle(0,615,1280,4,Color{230,222,176,255});
        float offset=float(std::fmod(pos*9,144));
        for(int lane=1;lane<3;lane++)for(float x=-offset;x<1280;x+=144)DrawRectangle(int(x),324+lane*96,74,4,Color{171,173,181,255});
        if(settings.quality==Quality::High){
            for(int i=0;i<38;i++){float x=float(std::fmod(i*71.0-pos*12+100000,1320))-20;DrawRectangle(int(x),350+(i*47)%252,18,1,Color{65,70,83,255});}
        }
        DrawRectangle(0,625,1280,95,Color{21,30,35,255});
    }
    void menu(){
        card({54,63,480,591},Color{14,22,33,240});
        text("PIXEL CAR",88,94,52);text("UNBOUND",88,152,66,Accent);
        text("NATIF WINDOWS  /  0.4",91,231,17,Muted);
        text("Prenez la route.",91,282,26);
        if(button({89,333,407,62},"MODE LIBRE",true))queued=[this]{beginFree();};
        if(button({89,410,407,53},"GARAGE"))screen=Screen::Garage;
        if(button({89,477,407,53},"CUSTOMISATION"))openCustomization();
        if(button({89,544,407,45},"PARAMÈTRES"))openOptions();
        if(button({89,600,407,38},"QUITTER"))quit=true;

        DrawRectangle(608,459,610,8,Accent);
        car(profile.car,profile.rim,594,247,2.6,0,true,configuration.tireFrame,configuration.rideOffset);
        text("MODE LIBRE",656,511,29);text("Route ouverte • circulation • conduite continue",656,555,18,Muted);
        text("191 carrosseries et 54 styles de jantes Unbound",656,588,17,Muted);
    }
    void openCustomization(){screen=Screen::Customization;customSlot=PartSlot::Engine;customPreview=profile.parts[0];customPage=0;customSearch.clear();notice.clear();}
    static std::string lower(std::string value){for(char& c:value)c=char(std::tolower(static_cast<unsigned char>(c)));return value;}
    void customizationScene(){
        bool originalUi=uiEnabled;if(audioPopup)uiEnabled=false;
        DrawRectangle(0,0,1280,720,Fade(Ink,.92f));
        text("CUSTOMISATION",31,26,30);text("Pièces d'Unbound • équipement libre",349,37,17,Muted);
        if(button({1037,20,210,51},"GARAGE")){saveCar();screen=Screen::Garage;}
        for(int slot=0;slot<PartSlotCount;slot++){
            bool active=int(customSlot)==slot;
            if(button({31,float(106+slot*43),226,36},slotLabel(PartSlot(slot)),active)){
                customSlot=PartSlot(slot);customPreview=profile.parts[slot];customPage=0;customSearch.clear();notice.clear();
            }
        }
        if(button({31,633,226,43},"TOUT DE BASE")){profile.parts.fill(0);profile.soundOn=profile.soundOff=profile.bov=-1;saveCar();customPreview=0;notice="Configuration de base rétablie.";}
        card({282,99,566,43},Color{28,39,51,255});
        text(customSearch.empty()?"Recherche : tapez un nom...":customSearch,297,112,18,customSearch.empty()?Muted:WHITE);
        std::vector<const Part*> choices;
        if(customSearch.empty()||lower("configuration de base").find(lower(customSearch))!=std::string::npos)choices.push_back(nullptr);
        for(const auto& part:PartCatalog)if(part.slot==customSlot&&lower(part.name).find(lower(customSearch))!=std::string::npos)choices.push_back(&part);
        constexpr int perPage=8;int pages=std::max(1,(int(choices.size())+perPage-1)/perPage);
        customPage=std::clamp(customPage,0,pages-1);
        for(int row=0;row<perPage;row++){
            int index=customPage*perPage+row;if(index>=int(choices.size()))break;
            const Part* part=choices[index];int id=part?part->id:0;
            Rectangle rect{282,float(154+row*53),566,46};
            std::string label=part?part->name:"CONFIGURATION DE BASE";
            if(part&&std::count_if(std::begin(PartCatalog),std::end(PartCatalog),[&](const Part& p){return p.slot==part->slot&&std::string(p.name)==part->name;})>1)label+=" ["+std::to_string(part->subimage)+"]";
            if(button(rect,label,id==customPreview))customPreview=id;
            if(profile.parts[int(customSlot)]==id)DrawCircle(832,rect.y+8,4,Gold);
        }
        if(choices.empty())text("Aucune pièce trouvée",302,177,21,Muted);
        if(button({282,594,65,40},"<",false,customPage>0))--customPage;
        text(TextFormat("%i / %i  •  %i choix",customPage+1,pages,int(choices.size())),421,607,17,Muted);
        if(button({783,594,65,40},">",false,customPage+1<pages))++customPage;
        const Part* part=findPart(customPreview);
        if(part&&part->slot!=customSlot){customPreview=profile.parts[int(customSlot)];part=findPart(customPreview);}
        card({875,99,372,480});text(slotLabel(customSlot),897,123,23,Accent);
        std::string name=part?part->name:"Configuration de base";
        if(name.size()>24){auto at=name.rfind(' ',24);if(at!=std::string::npos){text(name.substr(0,at),897,172,19);text(name.substr(at+1),897,198,19);}else text(name,897,172,17);}
        else text(name,897,172,21);
        if(part){
            const char* stat=customSlot==PartSlot::Ecu?"Régime supplémentaire":customSlot==PartSlot::Tires?"Indice d'adhérence":customSlot==PartSlot::Turbo||customSlot==PartSlot::Supercharger?"Pression cible":customSlot==PartSlot::Suspension?"Gain de puissance":"Puissance catalogue";
            const char* unit=customSlot==PartSlot::Ecu?"tr/min":customSlot==PartSlot::Tires?"":customSlot==PartSlot::Turbo||customSlot==PartSlot::Supercharger?"psi":"HP";
            text(stat,897,252,16,Muted);text(TextFormat("%.0f %s",part->stat,unit),897,279,26,Gold);
            text(TextFormat("Poids relatif : %.0f",part->weight),897,324,16,Muted);
            text(TextFormat("Valeur catalogue : $%.0f",part->value),897,352,16,Muted);
            text(TextFormat("Variante %i",part->subimage),897,380,16,Muted);
            if(part->slot==PartSlot::Ecu&&std::string(part->name).find("2STEP")!=std::string::npos)text("L + accélérateur : launch control",897,407,14,Accent);
        }else text("Retirer la pièce de cette catégorie",897,262,16,Muted);
        bool equipped=profile.parts[int(customSlot)]==customPreview;
        if(button({896,435,330,50},equipped?"ÉQUIPÉ":"ÉQUIPER",true,!equipped)){
            equipPart(profile,customSlot,customPreview);saveCar();audio.install(settings.sound);notice="Pièce équipée et sauvegardée.";
        }
        text(TextFormat("Base moteur : %.0f HP",configuration.baseHp),897,509,18);
        text(TextFormat("Masse estimée : %.0f kg",configuration.vehicle.mass),897,538,17,Muted);
        if(button({875,594,372,50},"PRENDRE LA ROUTE",true))queued=[this]{saveCar();beginFree();};
        text("194 pièces et moteurs • tous disponibles",284,651,16,Accent);
        text(notice.empty()?"Performances provisoires • N : activer le NOS équipé":notice,284,681,16,Muted);
        if(button({875,656,372,38},"SON DU MOTEUR"))audioPopup=true;
        uiEnabled=originalUi;
        if(audioPopup){
            DrawRectangle(0,0,1280,720,Fade(BLACK,.75f));card({263,141,754,457});
            text("SONS DU MOTEUR",305,172,29,Accent);
            text("Profils sonores d'origine • choix indépendant du moteur",305,219,17,Muted);
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

    void garage(){
        crop(art::garages[garageStyle%23],{0,0,1280,654});DrawRectangle(0,0,1280,94,Fade(Ink,.90f));
        text("GARAGE",46,26,31);text("Votre véhicule pour le mode libre",236,36,18,Muted);
        if(button({1003,20,230,52},"RETOUR")){saveCar();screen=Screen::Menu;}
        car(profile.car,profile.rim,249,249,3.5,0,true,configuration.tireFrame,configuration.rideOffset);
        card({48,516,1184,172});
        text(TextFormat("CARROSSERIE  %03i / 191",profile.car+1),80,540,23);
        if(button({83,586,52,44},"<")){profile.car=(profile.car+190)%191;saveCar();}
        if(button({376,586,52,44},">")){profile.car=(profile.car+1)%191;saveCar();}
        text("Apparence Unbound",153,597,18,Muted);
        text(TextFormat("JANTES  %02i / 54",profile.rim+1),493,540,23);
        if(button({493,586,52,44},"<")){profile.rim=(profile.rim+53)%54;saveCar();}
        if(button({724,586,52,44},">")){profile.rim=(profile.rim+1)%54;saveCar();}
        text("Changer le style",561,597,17,Muted);
        if(button({845,574,344,64},"PRENDRE LA ROUTE",true))queued=[this]{saveCar();beginFree();};
        text("Personnalisez moteur et pièces dans CUSTOMISATION. Performances provisoires.",81,654,16,Muted);
        if(button({742,114,257,40},"CUSTOMISATION"))openCustomization();
        if(button({1015,114,218,40},"DÉCOR SUIVANT"))garageStyle=(garageStyle+1)%23;
        if(button({972,166,261,44},driveLabel())){profile.drive=DriveLayout((int(profile.drive)+1)%3);saveCar();}
    }
    void renderEffects(bool front){
        for(const auto& p:effects.particles){
            bool isFront=p.kind!=EffectKind::Smoke&&p.kind!=EffectKind::BrakeSmoke;if(isFront!=front)continue;
            float fade=float(1-p.age/p.life);const art::Frame* sprite=nullptr;float scale=float(p.scale);Vector2 origin{19,15};Color color=Fade(WHITE,fade*.65f);float rotation=0;
            if(p.kind==EffectKind::Smoke||p.kind==EffectKind::BrakeSmoke){sprite=p.kind==EffectKind::Smoke?&art::smoke[0]:&art::smoke2[0];scale*=float(1+p.age*2);}
            else if(p.kind==EffectKind::Flame){sprite=&art::flames[int(p.age*30)%int(std::size(art::flames))];origin={50,36};scale=1.3f;color=Fade(WHITE,fade);rotation=p.hood?90.f:0;}
            else if(p.kind==EffectKind::Spark){sprite=&art::sparks[0];origin={0,0};scale=1.5f;color=Fade(Gold,fade);rotation=float(std::atan2(p.vy,p.vx)*180/3.141592653589793);}
            else if(p.kind==EffectKind::Nitro){
                Vector2 a{float(p.x),float(p.y)},b{float(p.x-30),float(p.y-6)},c{float(p.x-30),float(p.y+6)};
                if(p.hood){b={float(p.x-6),float(p.y-30)};c={float(p.x+6),float(p.y-30)};}
                if(p.hood)DrawTriangle(a,b,c,Fade(SKYBLUE,fade*.75f));else DrawTriangle(a,c,b,Fade(SKYBLUE,fade*.75f));DrawCircleV(a,5,Fade(SKYBLUE,fade*.5f));continue;
            }
            if(sprite)DrawTexturePro(atlases.at(sprite->atlas),{float(sprite->x),float(sprite->y),float(sprite->w),float(sprite->h)},
                {float(p.x),float(p.y),sprite->w*scale,sprite->h*scale},{(origin.x-sprite->dx)*scale,(origin.y-sprite->dy)*scale},rotation,color);
        }
    }
    void freeScene(){
        renderEffects(false);
        for(int lane=0;lane<3;lane++){
            for(const auto& t:drive.traffic)if(t.lane==lane){float x=360+float((t.position-drive.player.position)*8);if(x>-400&&x<1600)car(t.appearance,t.appearance%54,x,269+lane*96,1.25,t.speed);}
            if(std::clamp(int(std::round(drive.lane)),0,2)==lane)car(profile.car,profile.rim,360,269+float(drive.lane)*96,1.25,drive.player.speed,true,configuration.tireFrame,configuration.rideOffset);
        }
        renderEffects(true);
        if(drive.collisionCooldown>1.0)DrawRectangle(0,0,1280,720,Fade(RED,.10f));
        DrawRectangle(0,0,1280,86,Fade(Ink,.93f));text("MODE LIBRE",35,23,30);text(TextFormat("%.2f km",drive.player.position/1000),280,31,20,Muted);
        if(button({814,17,238,51},"PARAMÈTRES"))openOptions();
        if(button({1066,17,177,51},paused?"REPRENDRE":"PAUSE"))paused=!paused;
        card({29,578,275,111});text(TextFormat("%03i",int(drive.player.speed*3.6)),52,587,60);text("km/h",192,620,22,Muted);
        card({320,578,563,111});text(std::string(profile.automatic?"AUTO  •  ":"MANUELLE  •  ")+driveLabel(),344,595,17,Accent);
        text("Z / ↑  Accélérer     S / ↓  Freiner",344,625,17);
        text("← / →  Voies    E / C  Rapports    T  Boîte    N NOS  L 2STEP  H Klaxon",344,655,14,Muted);
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
        text("PARAMÈTRES",211,66,30);text("AFFICHAGE ET GRAPHISMES",211,110,15,Accent);
        int d=choice(144,"Mode d'affichage",edited.mode==WindowMode::Windowed?"Fenêtre avec bordure":edited.mode==WindowMode::Borderless?"Fenêtre sans bordure":"Plein écran");
        if(d){edited.mode=WindowMode((int(edited.mode)+d+3)%3);normalizeResolution(edited);}
        d=choice(203,edited.mode==WindowMode::Borderless?"Résolution de rendu":"Résolution",TextFormat("%i × %i",edited.width,edited.height));
        if(d){auto r=resolutions(edited.mode);auto i=std::find(r.begin(),r.end(),Resolution{edited.width,edited.height});int n=i==r.end()?0:int(i-r.begin());auto next=r[(n+d+int(r.size()))%int(r.size())];edited.width=next.width;edited.height=next.height;}
        d=choice(262,"Limite d'images par seconde",edited.fps?std::to_string(edited.fps)+" FPS":"Illimitée");
        if(d){const int choices[]={30,60,120,144,165,240,0};auto i=std::find(std::begin(choices),std::end(choices),edited.fps);int n=i==std::end(choices)?0:int(i-choices);edited.fps=choices[(n+d+7)%7];}
        if(choice(321,"Synchronisation verticale",edited.vsync?"Activée":"Désactivée"))edited.vsync=!edited.vsync;
        d=choice(380,"Qualité des graphismes",edited.quality==Quality::Low?"Faible":edited.quality==Quality::Medium?"Moyenne":"Élevée");
        if(d)edited.quality=Quality((int(edited.quality)+d+3)%3);
        if(choice(439,"Compteur FPS",edited.showFps?"Afficher":"Masquer"))edited.showFps=!edited.showFps;
        if(choice(498,"Son",edited.sound?"Activé":"Désactivé"))edited.sound=!edited.sound;
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
    void controls(double dt){
        if((IsKeyDown(KEY_LEFT_CONTROL)||IsKeyDown(KEY_RIGHT_CONTROL))&&IsKeyPressed(KEY_Q)){quit=true;return;}
        if(IsKeyPressed(KEY_F10)){if(confirming)revert();Settings safe;safe.width=960;safe.height=540;safe.vsync=false;safe.fps=60;apply(safe);edited=settings;options=true;notice="Affichage de secours. Appliquez vos réglages pour les enregistrer.";}
        if(IsKeyPressed(KEY_ESCAPE)){if(confirming)revert();else if(options)options=false;else if(audioPopup){audioPopup=false;audioPreviewUntil=0;}else if(screen==Screen::Free)paused=!paused;else if(screen==Screen::Garage){saveCar();screen=Screen::Menu;}else if(screen==Screen::Customization){screen=Screen::Garage;customSearch.clear();}}
        if(!confirming&&IsKeyPressed(KEY_ENTER)&&(IsKeyDown(KEY_LEFT_ALT)||IsKeyDown(KEY_RIGHT_ALT))){openOptions();edited.mode=settings.mode==WindowMode::Windowed?WindowMode::Borderless:WindowMode::Windowed;queued=[this]{preview();};}
        if(confirming&&GetTime()>=deadline)revert();
        if(IsKeyPressed(KEY_F3)){settings.showFps=!settings.showFps;edited.showFps=settings.showFps;}
        DriverInput input{IsKeyDown(KEY_Z)||IsKeyDown(KEY_W)||IsKeyDown(KEY_UP)||IsKeyDown(KEY_SPACE),IsKeyDown(KEY_S)||IsKeyDown(KEY_DOWN),profile.automatic,IsKeyDown(KEY_N),IsKeyDown(KEY_L)};
        if(screen==Screen::Customization&&!options&&!confirming&&!audioPopup){
            for(int c=GetCharPressed();c>0;c=GetCharPressed())if(c>=32&&c<127&&customSearch.size()<42){customSearch+=char(c);customPage=0;}
            if(IsKeyPressed(KEY_BACKSPACE)&&!customSearch.empty()){customSearch.pop_back();customPage=0;}
        }
        if(screen==Screen::Free&&!paused&&!options&&!confirming){
            if(IsKeyPressed(KEY_LEFT)||IsKeyPressed(KEY_A)||IsKeyPressed(KEY_Q))drive.changeLane(-1);
            if(IsKeyPressed(KEY_RIGHT)||IsKeyPressed(KEY_D))drive.changeLane(1);
            if(IsKeyPressed(KEY_E)||IsKeyPressed(KEY_LEFT_SHIFT))shift(drive.player,1,drive.vehicle);
            if(IsKeyPressed(KEY_C))shift(drive.player,-1,drive.vehicle);
            if(IsKeyPressed(KEY_T)){profile.automatic=!profile.automatic;input.automatic=profile.automatic;saveCar();}
            if(args.smoke)input={true,frames>=260&&frames<267,true,frames>=235};
            accumulator+=dt;while(accumulator>=Step){drive.update(input,Step);accumulator-=Step;}
            auto wheels=art::wheelPositions[profile.car];double baseY=269+drive.lane*96;
            EffectSources sources{360+wheels.rear*1.25,360+wheels.front*1.25,baseY+(wheels.y+wheels.radius)*1.25,
                360+art::cars[profile.car].dx*1.25,baseY+(wheels.y+5+configuration.rideOffset)*1.25,false};
            const Part* exhaust=findPart(profile.parts[int(PartSlot::Exhaust)]);
            if(exhaust&&std::string(exhaust->name).find("Hood")!=std::string::npos){sources.exhaustX=sources.frontWheel-15;sources.exhaustY=baseY+35;sources.hood=true;}
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
        uiEnabled=!options&&!confirming; background(screen==Screen::Free);
        if(screen==Screen::Menu)menu();else if(screen==Screen::Garage)garage();else if(screen==Screen::Customization)customizationScene();else freeScene();
        if(options){uiEnabled=!confirming;settingsScene();}
        if(confirming){uiEnabled=true;confirmScene();}
        if(settings.showFps){DrawRectangle(1121,691,151,27,Ink);text(TextFormat("%i FPS",GetFPS()),1141,694,18,Accent);}
        EndMode2D();EndTextureMode();
        BeginDrawing();ClearBackground(BLACK);DrawTexturePro(render.texture,{0,0,float(render.texture.width),-float(render.texture.height)},output,{0,0},0,WHITE);EndDrawing();
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
        if(frames==205){openCustomization();equipPart(profile,PartSlot::Engine,1002);equipPart(profile,PartSlot::Turbo,3026);equipPart(profile,PartSlot::Nos,5007);equipPart(profile,PartSlot::Exhaust,9048);equipPart(profile,PartSlot::Tires,10017);saveCar();customPreview=1002;}
        if(frames==213)capture("customisation.png");
        if(frames==216)audioPopup=true;
        if(frames==220)capture("sons-moteur.png");
        if(frames==222){audioPopup=false;auto p=loadProfile(profileFile(),191,54);check(p.parts==profile.parts,"custom equipment persists");beginFree();check(drive.vehicle.boostPsi==35&&drive.vehicle.nitroHp==250,"equipped turbo and NOS affect the active vehicle");}
        if(frames==255){capture("nos-vfx.png");check(drive.player.nitroRemaining<10,"NOS charge is consumed in free drive");check(drive.player.boostPsi>0,"turbo develops boost in free drive");check(std::any_of(effects.particles.begin(),effects.particles.end(),[](const Particle& p){return p.kind==EffectKind::Nitro;}),"NOS visual effect is active");}
        if(frames==270){drive.lane=drive.targetLane;drive.collisionCooldown=0;drive.traffic[0]={drive.player.position,0,drive.targetLane,0};}
        if(frames==272){capture("collision-vfx.png");check(std::any_of(effects.particles.begin(),effects.particles.end(),[](const Particle& p){return p.kind==EffectKind::Spark;}),"collision emits sparks");}
        if(frames==280)quit=true;
    }
    int run(){
        init();
        while(!WindowShouldClose()&&!quit){double dt=args.smoke?1.0/30.0:std::clamp(double(GetFrameTime()),0.0,.1);controls(dt);renderFrame();if(IsKeyPressed(KEY_F12))capture(TextFormat("capture-%06i.png",frames));if(queued){auto action=std::move(queued);queued=nullptr;action();}if(args.smoke)smoke();frames++;}
        if(confirming)revert();
        saveCar();
        {std::error_code ec;fs::create_directories(args.data,ec);if(!ec){std::ofstream out(args.data/"last-session.txt");out<<"screen="<<int(screen)<<"\ndistance_m="<<drive.player.position<<"\nspeed_mps="<<drive.player.speed<<"\ntarget_lane="<<drive.targetLane<<"\ngear="<<drive.player.gear<<"\nengine_part="<<profile.parts[int(PartSlot::Engine)]<<"\ntire_part="<<profile.parts[int(PartSlot::Tires)]<<"\nnative_mass_kg="<<drive.vehicle.mass<<"\nnative_torque_nm="<<drive.vehicle.torque<<"\ndrive_layout="<<int(drive.vehicle.drive)<<"\naudio_ready="<<audio.ready<<"\naudio_failures="<<audio.failures<<"\nframes="<<frames<<"\nmode="<<modeKey(settings.mode)<<"\nwidth="<<GetScreenWidth()<<"\nheight="<<GetScreenHeight()<<"\n";}}
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
