#pragma once
#include "vehicle_garage.hpp"
#include <sstream>

namespace pcr {
constexpr std::size_t GarageCapacity=8;
inline int vehicleIndex(const std::string& key){
    for(std::size_t i=0;i<std::size(VehicleCatalog);++i)if(key==VehicleCatalog[i].id)return int(i);
    return -1;
}
struct VehicleInventory {
    std::vector<int> cars;
    bool owns(int index)const{return std::find(cars.begin(),cars.end(),index)!=cars.end();}
    bool add(int index,std::string& error){
        if(index<0||index>=int(std::size(VehicleCatalog))){error="Voiture inconnue.";return false;}
        if(owns(index)){error="Cette voiture est déjà dans votre garage.";return false;}
        if(cars.size()>=GarageCapacity){error="Garage plein : retirez une voiture pour libérer une place (8 maximum).";return false;}
        cars.push_back(index);return true;
    }
    bool remove(int index){auto at=std::find(cars.begin(),cars.end(),index);if(at==cars.end())return false;cars.erase(at);return true;}
};
inline bool storeVehicleInventory(const std::filesystem::path& file,const VehicleInventory& inventory,std::string& error){
    if(inventory.cars.size()>GarageCapacity){error="Le garage dépasse huit places.";return false;}
    std::vector<int> seen;
    for(int id:inventory.cars){if(id<0||id>=int(std::size(VehicleCatalog))||std::find(seen.begin(),seen.end(),id)!=seen.end()){error="Inventaire du garage invalide.";return false;}seen.push_back(id);}
    std::error_code ec;std::filesystem::create_directories(file.parent_path(),ec);
    if(ec){error=ec.message();return false;}
    auto pending=file;pending+=".pending";
    {std::ofstream out(pending,std::ios::binary|std::ios::trunc);out<<"version=1\n";for(int id:inventory.cars)out<<"vehicle="<<VehicleCatalog[id].id<<'\n';out.flush();if(!out){error="Écriture de l'inventaire impossible.";return false;}}
    if(!backupVehicleProfile(file,error))return false;
    return atomicReplace(pending,file,error);
}
inline bool loadVehicleInventory(const std::filesystem::path& file,VehicleInventory& output,std::string& error){
    std::ifstream in(file);if(!in){error="Lecture de l'inventaire impossible.";return false;}
    VehicleInventory next;bool version=false;std::string line;
    while(std::getline(in,line)){
        if(!line.empty()&&line.back()=='\r')line.pop_back();
        if(line=="version=1")version=true;
        else if(line.rfind("vehicle=",0)==0){if(!next.add(vehicleIndex(line.substr(8)),error))return false;}
        else if(!line.empty()){error="Format de l'inventaire inconnu ; fichier conservé.";return false;}
    }
    if(!in.eof()||!version){error="Inventaire incomplet ; fichier conservé.";return false;}
    output=next;return true;
}
// One-time migration. Old preparations beyond eight stay archived, never deleted.
inline VehicleInventory migrateVehicleInventory(const std::filesystem::path& root,const Profile& active){
    VehicleInventory result;std::string error;result.add(bodyChoiceIndex(active),error);
    std::vector<std::filesystem::directory_entry> files;
    if(std::filesystem::exists(root))for(const auto& item:std::filesystem::directory_iterator(root))
        if(item.is_regular_file()&&item.path().extension()==".ini"&&vehicleIndex(item.path().stem().string())>=0)files.push_back(item);
    std::sort(files.begin(),files.end(),[](const auto& a,const auto& b){auto ta=a.last_write_time(),tb=b.last_write_time();return ta==tb?a.path().filename()<b.path().filename():ta>tb;});
    for(const auto& item:files){int id=vehicleIndex(item.path().stem().string());if(result.cars.size()<GarageCapacity&&!result.owns(id))result.add(id,error);}
    return result;
}
}
