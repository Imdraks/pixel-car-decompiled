#pragma once
#include "model.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <stdexcept>
namespace pcr {
struct SavedCar {int id;Profile profile;};
inline std::filesystem::path savedCarFile(const std::filesystem::path& root,int id){
    if(id<1||id>9999)throw std::invalid_argument("Invalid saved car id");
    return root/("car-"+std::to_string(id)+".ini");
}
inline std::vector<SavedCar> savedCars(const std::filesystem::path& root){
    std::vector<SavedCar> result;if(!std::filesystem::is_directory(root))return result;
    for(const auto& file:std::filesystem::directory_iterator(root)){
        auto name=file.path().filename().string();
        if(!file.is_regular_file()||name.size()<9||name.substr(0,4)!="car-"||name.substr(name.size()-4)!=".ini")continue;
        auto digits=name.substr(4,name.size()-8);
        if(digits.empty()||digits.size()>4||!std::all_of(digits.begin(),digits.end(),[](unsigned char c){return std::isdigit(c);}))continue;
        int id=std::stoi(digits);if(id<1||id>9999||digits!=std::to_string(id))continue;
        result.push_back({id,loadProfile(file.path(),191,54)});
    }
    std::sort(result.begin(),result.end(),[](const SavedCar& a,const SavedCar& b){return a.id<b.id;});return result;
}
inline int nextSavedCarId(const std::filesystem::path& root){
    for(int id=1;id<=9999;id++)if(!std::filesystem::exists(savedCarFile(root,id)))return id;
    return 0;
}
inline bool storeSavedCar(const std::filesystem::path& root,int id,const Profile& profile,std::string& error){
    if(id<1||id>9999){error="Garage plein.";return false;}
    auto file=savedCarFile(root,id);std::error_code ec;
    if(std::filesystem::exists(file)){
        auto backup=file;backup+=".bak";
        std::filesystem::copy_file(file,backup,std::filesystem::copy_options::overwrite_existing,ec);
        if(ec){error="Sauvegarde de securite impossible : "+ec.message();return false;}
    }
    return saveProfile(file,profile,error);
}
}
