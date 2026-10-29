#pragma once
#include <algorithm>
namespace pcr {
inline constexpr const char* MenuMusicDryFile="music/menu-underground.ogg";
inline constexpr const char* MenuMusicGarageFile="music/menu-underground-garage.ogg";
enum class MenuMusicContext {Silent,Menu,Garage,Customization};
inline MenuMusicContext menuMusicContext(int track){return track<0?MenuMusicContext::Silent:track==5?MenuMusicContext::Garage:track==4?MenuMusicContext::Customization:MenuMusicContext::Menu;}
inline const char* menuMusicContextLabel(MenuMusicContext context){switch(context){case MenuMusicContext::Menu:return "MENU";case MenuMusicContext::Garage:return "GARAGE";case MenuMusicContext::Customization:return "CUSTOMISATION";default:return "SILENCE";}}
struct MenuMusicMix {double dry=0,garage=0;};
inline MenuMusicMix menuMusicMix(int track,double musicVolume,bool enabled){
    if(!enabled||track<0)return {};
    double gain=std::clamp(musicVolume,0.0,1.0);auto context=menuMusicContext(track);
    if(context==MenuMusicContext::Garage)return {0,.55*gain};
    if(context==MenuMusicContext::Customization)return {0,.22*gain};
    return {.55*gain,0};
}
}
