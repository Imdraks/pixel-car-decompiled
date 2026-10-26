#pragma once
#include <string>
#include <vector>
#include "model.hpp"
namespace pcr {
std::string defaultDataDirectory();
bool atomicReplace(const std::filesystem::path& from,const std::filesystem::path& to,std::string& error);
std::vector<Resolution> platformDisplayModes(int monitorX,int monitorY);
void setExecutableDirectory();
void showFatalError(const std::string&);
}
