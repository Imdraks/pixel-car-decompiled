#include "game_audio.hpp"
#include "garage_engine.hpp"
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <cmath>
static std::vector<float> recorded;
static void capture(void* buffer,unsigned frames){auto* samples=static_cast<float*>(buffer);recorded.insert(recorded.end(),samples,samples+frames*2);}
int main(int argc,char**argv){
 if(argc!=3)return 2;SetTraceLogLevel(LOG_INFO);
 pcr::GameAudio audio;audio.init(argv[1]);if(!audio.ready)return 3;
 pcr::Profile warmProfile;pcr::Vehicle warmVehicle;pcr::CarState warmState;
 for(int i=0;i<200;i++){audio.update(warmProfile,warmVehicle,warmState,{},0,false,false);std::this_thread::sleep_for(std::chrono::milliseconds(10));}
 std::vector<float> tone(44100*2);for(size_t i=0;i<tone.size();i++)tone[i]=float(.2*std::sin(i*6.283185307179586*1000/44100));
 Wave reference{};reference.frameCount=unsigned(tone.size());reference.sampleRate=44100;reference.sampleSize=32;reference.channels=1;reference.data=tone.data();
 Sound toneSound=LoadSoundFromWave(reference);recorded.reserve(48000*2*5);AttachAudioMixedProcessor(capture);PlaySound(toneSound);std::this_thread::sleep_for(std::chrono::milliseconds(1000));DetachAudioMixedProcessor(capture);StopSound(toneSound);UnloadSound(toneSound);
 std::vector<double> crosses;for(size_t i=2;i<recorded.size();i+=2)if(recorded[i-2]<0&&recorded[i]>=0)crosses.push_back(double(i/2));
 if(crosses.size()<100){std::cerr<<"Calibration unavailable frames="<<recorded.size()/2<<" crosses="<<crosses.size()<<'\n';return 7;}
 double estimated=1000*(crosses.back()-crosses.front())/(crosses.size()-1);
 unsigned sampleRate=std::abs(estimated-44100)<std::abs(estimated-48000)?44100:48000;if(std::abs(estimated-sampleRate)>sampleRate*.01)return 8;
 std::cout<<"Capture PCM sample rate="<<sampleRate<<" calibrated with 1000 Hz tone estimated="<<estimated<<'\n';
 for(auto choice:{std::pair<int,const char*>{1002,"2JZ"},{1014,"LT5"},{1009,"FR9"}}){
  pcr::Profile profile;profile.audioSource=1;pcr::equipPart(profile,pcr::PartSlot::Engine,choice.first);auto build=pcr::buildVehicle(profile);pcr::CarState car;car.neutral=true;
  recorded.clear();recorded.reserve(48000*2*5);AttachAudioMixedProcessor(capture);
  for(int tick=0;tick<400;tick++){
   double time=tick*.01;bool gas=time>=.4&&time<3;
   car.rpm=time<.4?900:time<2.4?900+(time-.4)*3550:time<3?8000:std::max(900.0,8000-(time-3)*7100);car.elapsed=time;
   audio.update(profile,build.vehicle,car,{gas,false,true},0,true,true,false);
   std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }
  DetachAudioMixedProcessor(capture);
  pcr::CarState silent;audio.update(profile,build.vehicle,silent,{},0,false,true);
  Wave wave{};wave.frameCount=unsigned(recorded.size()/2);wave.sampleRate=sampleRate;wave.sampleSize=32;wave.channels=2;wave.data=recorded.data();
  std::string name=std::string(argv[2])+"/"+choice.second+".wav";
  if(!ExportWave(wave,name.c_str()))return 4;
  double square=0,peak=0;size_t clipped=0;for(float v:recorded){if(!std::isfinite(v))return 5;square+=v*v;peak=std::max(peak,double(std::abs(v)));clipped+=std::abs(v)>=.999f;}
  std::cout<<choice.second<<" frames="<<wave.frameCount<<" peak="<<peak<<" rms="<<std::sqrt(square/recorded.size())<<" clipped="<<clipped<<'\n';
 }
 return audio.failures?6:0;
}
