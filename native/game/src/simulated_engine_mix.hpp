#pragma once
#include <algorithm>
#include <cmath>
#include <iterator>
#include "simulated_audio_data.hpp"
namespace pcr {
struct SimulatedClipMix {double gain=0,pitch=1;};
// Piecewise linear interpolation preserves a gain sum <= 1 across RPM/load.
inline SimulatedClipMix simulatedClipMix(const SimulatedPack& pack,std::size_t index,double rpm,double load,bool autoOn=true,bool autoOff=true){
    rpm=std::max(0.0,rpm);load=std::clamp(load,0.0,1.0);
    double lowRpm=pack.clips[0].rpm,highRpm=pack.clips[pack.count-1].rpm;
    for(std::size_t i=0;i<pack.count;i++){
        double anchor=pack.clips[i].rpm;
        if(anchor<=rpm)lowRpm=std::max(lowRpm,anchor);
        if(anchor>=rpm)highRpm=std::min(highRpm,anchor);
    }
    lowRpm=std::min(lowRpm,highRpm);
    if(rpm<pack.clips[0].rpm)lowRpm=highRpm=pack.clips[0].rpm;
    if(rpm>pack.clips[pack.count-1].rpm)lowRpm=highRpm=pack.clips[pack.count-1].rpm;
    double lowLoad=0,highLoad=1;
    for(std::size_t i=0;i<pack.count;i++){
        double anchor=pack.clips[i].load;
        if(anchor<=load)lowLoad=std::max(lowLoad,anchor);
        if(anchor>=load)highLoad=std::min(highLoad,anchor);
    }
    auto weight=[](double value,double low,double high,double anchor){
        if(low==high)return anchor==low?1.0:0.0;
        if(anchor==low)return (high-value)/(high-low);
        if(anchor==high)return (value-low)/(high-low);
        return 0.0;
    };
    const auto& clip=pack.clips[index];
    double gain=weight(rpm,lowRpm,highRpm,clip.rpm)*weight(load,lowLoad,highLoad,clip.load);
    if(clip.load==0?!autoOff:!autoOn)gain=0;
    return {std::clamp(gain,0.0,1.0),std::clamp(rpm/clip.rpm,.5,1.75)};
}
}
