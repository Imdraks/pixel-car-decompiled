#include "platform.hpp"
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <iostream>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
namespace pcr {
void setExecutableDirectory(){
#ifdef _WIN32
    wchar_t path[32768];DWORD n=GetModuleFileNameW(nullptr,path,32768);
    if(n==0||n>=32768)throw std::runtime_error("Chemin de l'exécutable inaccessible");
    std::filesystem::current_path(std::filesystem::path(path).parent_path());
#else
    std::filesystem::current_path(std::filesystem::read_symlink("/proc/self/exe").parent_path());
#endif
}
void showFatalError(const std::string& error){
    std::cerr<<error<<std::endl;
#ifdef _WIN32
    int n=MultiByteToWideChar(CP_UTF8,0,error.c_str(),-1,nullptr,0);
    std::wstring message(n,L'\0');MultiByteToWideChar(CP_UTF8,0,error.c_str(),-1,message.data(),n);
    MessageBoxW(nullptr,message.c_str(),L"Pixel Car Racer Native",MB_OK|MB_ICONERROR);
#endif
}
std::string defaultDataDirectory() {
#ifdef _WIN32
    wchar_t buffer[32768];
    DWORD length=GetEnvironmentVariableW(L"LOCALAPPDATA",buffer,32768);
    if(length>0 && length<32768) {
        int n=WideCharToMultiByte(CP_UTF8,0,buffer,length,nullptr,0,nullptr,nullptr);
        std::string utf8(n,'\0');
        WideCharToMultiByte(CP_UTF8,0,buffer,length,utf8.data(),n,nullptr,nullptr);
        return utf8+"/PixelCarRacerNative";
    }
#else
    if(const char* x=std::getenv("XDG_STATE_HOME")) return std::string(x)+"/pixel-car-native";
    if(const char* h=std::getenv("HOME")) return std::string(h)+"/.local/state/pixel-car-native";
#endif
    return (std::filesystem::temp_directory_path()/"PixelCarRacerNative").u8string();
}
bool atomicReplace(const std::filesystem::path& from,const std::filesystem::path& to,std::string& error) {
#ifdef _WIN32
    if(MoveFileExW(from.c_str(),to.c_str(),MOVEFILE_REPLACE_EXISTING|MOVEFILE_WRITE_THROUGH))return true;
    error="Impossible de remplacer le fichier (Windows "+std::to_string(GetLastError())+").";
    return false;
#else
    std::error_code ec;std::filesystem::rename(from,to,ec);
    if(ec){error=ec.message();return false;}return true;
#endif
}
std::vector<Resolution> platformDisplayModes(int x,int y) {
    std::vector<Resolution> result;
#ifdef _WIN32
    POINT point{x,y};
    HMONITOR monitor=MonitorFromPoint(point,MONITOR_DEFAULTTOPRIMARY);
    MONITORINFOEXW info{};info.cbSize=sizeof(info);
    if(!GetMonitorInfoW(monitor,&info))return result;
    DEVMODEW mode{};mode.dmSize=sizeof(mode);
    for(DWORD i=0;EnumDisplaySettingsW(info.szDevice,i,&mode);++i) {
        if(mode.dmBitsPerPel>=24 && mode.dmPelsWidth>=800 && mode.dmPelsHeight>=450 &&
           mode.dmPelsWidth<=7680 && mode.dmPelsHeight<=4320)
            result.push_back({int(mode.dmPelsWidth),int(mode.dmPelsHeight)});
    }
#else
    (void)x;(void)y;
#endif
    if(result.size()>1){
        std::sort(result.begin(),result.end(),[](Resolution a,Resolution b){return a.width==b.width?a.height<b.height:a.width<b.width;});
        result.erase(std::unique(result.begin(),result.end()),result.end());
    }
    return result;
}
Resolution platformWindowedLimit(void* nativeWindow){
#ifdef _WIN32
    HWND window=static_cast<HWND>(nativeWindow);
    MONITORINFO info{};info.cbSize=sizeof(info);
    if(!GetMonitorInfoW(MonitorFromWindow(window,MONITOR_DEFAULTTOPRIMARY),&info))return {0,0};
    RECT frame{0,0,0,0};
    using DpiFunction=UINT (WINAPI*)(HWND);
    using AdjustFunction=BOOL (WINAPI*)(LPRECT,DWORD,BOOL,DWORD,UINT);
    auto dpi=reinterpret_cast<DpiFunction>(GetProcAddress(GetModuleHandleW(L"user32.dll"),"GetDpiForWindow"));
    auto adjust=reinterpret_cast<AdjustFunction>(GetProcAddress(GetModuleHandleW(L"user32.dll"),"AdjustWindowRectExForDpi"));
    if(dpi&&adjust)adjust(&frame,WS_OVERLAPPEDWINDOW,FALSE,0,dpi(window));
    else AdjustWindowRectEx(&frame,WS_OVERLAPPEDWINDOW,FALSE,0);
    return {int(info.rcWork.right-info.rcWork.left-(frame.right-frame.left)),
            int(info.rcWork.bottom-info.rcWork.top-(frame.bottom-frame.top))};
#else
    (void)nativeWindow;return {0,0};
#endif
}
}
