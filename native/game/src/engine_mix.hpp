#pragma once
#include <algorithm>
#include <cmath>
#include <vector>
namespace pcr {
inline double enginePlaybackPitch(double rpm,int accelerationSample){
    rpm=std::max(0.0,rpm);
    double target=.5+rpm/10000.0;
    if(accelerationSample==24){
        // sfx_engine4 (LS/Hemi/LT5) needs more upper-register travel while
        // retaining its low idle. Independent of ECU/redline changes.
        double high=std::clamp((rpm-2500)/6500.0,0.0,1.0);
        target+=.35*high*high*(3-2*high);
    }
    return std::clamp(target,.5,accelerationSample==24?1.95:1.65);
}
// Native playback calibration, not a recovered Android pitch equation.
struct EngineMix {
    double load=0,pitch=.6;bool ready=false;
    void update(double rpm,bool throttle,bool audible,double dt,int accelerationSample=21){
        double target=enginePlaybackPitch(rpm,accelerationSample);
        if(!audible){load=0;pitch=target;ready=false;return;}
        dt=std::clamp(dt,0.0,.1);
        if(!ready){pitch=target;ready=true;}
        pitch+=(target-pitch)*(1-std::exp(-dt/.035));
        load+=((throttle?1.0:0.0)-load)*(1-std::exp(-dt/(throttle?.065:.100)));
    }
};
// Overlap the tail with the head, then wrap into the unmodified continuation.
// Convex weights preserve peak headroom; the source files remain untouched.
inline std::vector<float> seamlessEngineLoop(const float* samples,unsigned frames,unsigned channels,unsigned rate){
    if(!samples||!channels||frames<32||!rate)return {};
    float seam=0;for(unsigned c=0;c<channels;c++)seam=std::max(seam,std::abs(samples[c]-samples[size_t(frames-1)*channels+c]));
    if(seam<=.04f)return std::vector<float>(samples,samples+size_t(frames)*channels);
    unsigned overlap=std::min(unsigned(rate*.012),frames/16);
    if(overlap<2)return {};
    unsigned length=frames-overlap;std::vector<float> result(size_t(length)*channels);
    for(unsigned frame=0;frame<length;frame++)for(unsigned channel=0;channel<channels;channel++){
        float value=samples[size_t(frame+overlap)*channels+channel];
        if(frame>=length-overlap){
            unsigned j=frame-(length-overlap);
            double weight=.5-.5*std::cos(3.141592653589793*j/(overlap-1));
            value=float(value*(1-weight)+samples[size_t(j)*channels+channel]*weight);
        }
        result[size_t(frame)*channels+channel]=std::clamp(value,-1.f,1.f);
    }
    return result;
}
}
