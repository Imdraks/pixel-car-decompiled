#pragma once
#include "model.hpp"
#include "platform.hpp"
#include <fstream>
#include <stdexcept>
namespace pcr {
inline const VehicleDefinition& vehicleDefinition(const Profile& p){return VehicleCatalog[bodyChoiceIndex(p)];}
inline std::string vehicleKey(const Profile& p){return vehicleDefinition(p).id;}
inline bool untouchedVehicleConfiguration(const Profile& p){
    Profile d;d.parts[0]=p.factoryInitialized?p.factoryEngineId:0;
    return p.parts==d.parts&&p.cosmetics==d.cosmetics&&p.rim==d.rim&&p.rearRim==d.rearRim&&p.factoryDrive==d.factoryDrive&&p.automatic==d.automatic&&p.drive==d.drive&&p.rollCage==d.rollCage&&p.headlights==d.headlights&&p.soundOn==d.soundOn&&p.soundOff==d.soundOff&&p.bov==d.bov&&p.gearboxPreset==d.gearboxPreset&&p.gearCount==d.gearCount&&p.gearRatios==d.gearRatios&&p.finalDrive==d.finalDrive&&p.shiftSeconds==d.shiftSeconds&&p.rideHeightMm==d.rideHeightMm&&p.springStiffness==d.springStiffness&&p.dampingRatio==d.dampingRatio&&p.frontBias==d.frontBias&&p.wheelieTune==d.wheelieTune;
}
inline bool initializeVehicleFactory(Profile& p){
    if(p.factoryInitialized&&p.factoryEngineId<0)return false;
    bool untouched=untouchedVehicleConfiguration(p);bool changed=!p.factoryInitialized;
    if(untouched){int engine=vehicleDefinition(p).factoryEngineId;changed|=p.parts[0]!=engine||p.factoryEngineId!=engine;equipPart(p,PartSlot::Engine,engine);p.factoryEngineId=engine;}
    else if(!p.factoryInitialized)p.factoryEngineId=-1;
    p.factoryInitialized=true;return changed;
}
inline Profile factoryVehicle(int index){
    index=std::clamp(index,0,int(std::size(VehicleCatalog))-1);const auto& v=VehicleCatalog[index];
    Profile p;p.car=v.body;p.contentSource=v.source;p.audioSource=v.source;p.visualVariant=v.visualVariant;initializeVehicleFactory(p);return p;
}
inline std::filesystem::path vehicleGarageFile(const std::filesystem::path& root,const Profile& p){return root/(vehicleKey(p)+".ini");}
inline bool backupVehicleProfile(const std::filesystem::path& file,std::string& error){
    std::error_code ec;if(!std::filesystem::exists(file))return true;
    auto backup=file;backup+=".bak";std::filesystem::copy_file(file,backup,std::filesystem::copy_options::overwrite_existing,ec);
    if(ec){error="Sauvegarde de sécurité impossible : "+ec.message();return false;}return true;
}
inline bool storeVehicleProfile(const std::filesystem::path& root,const Profile& p,std::string& error){
    auto file=vehicleGarageFile(root,p);auto candidate=file;candidate+=".pending";
    if(!saveProfile(candidate,p,error))return false;
    auto bytes=[](const std::filesystem::path& path){std::ifstream in(path,std::ios::binary);return std::string(std::istreambuf_iterator<char>(in),{});};
    if(std::filesystem::exists(file)&&bytes(file)==bytes(candidate)){std::filesystem::remove(candidate);return true;}
    if(!backupVehicleProfile(file,error))return false;
    return atomicReplace(candidate,file,error);
}
inline bool loadVehicleProfile(const std::filesystem::path& root,int index,Profile& output,std::string& error){
    if(index<0||index>=int(std::size(VehicleCatalog))){error="Voiture inconnue.";return false;}
    auto base=factoryVehicle(index);auto file=vehicleGarageFile(root,base);
    if(!std::filesystem::exists(file)){output=base;return true;}
    std::ifstream check(file);std::string line;bool identity=false;
    while(std::getline(check,line)){if(!line.empty()&&line.back()=='\r')line.pop_back();if(line=="vehicle_id="+vehicleKey(base))identity=true;}
    if(!identity){error="Identité manquante ou incorrecte dans la sauvegarde de cette voiture.";return false;}
    auto loaded=loadProfile(file,191,54);
    if(vehicleKey(loaded)!=vehicleKey(base)){error="Identité incohérente dans la sauvegarde de cette voiture.";return false;}
    initializeVehicleFactory(loaded);output=loaded;return true;
}
}
