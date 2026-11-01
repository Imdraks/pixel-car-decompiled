// CPU-only exhaustive content rendering, also runnable under ASan/UBSan.
#include "raylib.h"
#include "customization_audit.hpp"
#include <iostream>
int main(int argc,char** argv){
    if(argc!=3){std::cerr<<"Usage: content-bounds-test ASSETS NEW_OUTPUT\n";return 2;}
    try{pcr::checkCustomization(argv[1],argv[2]);return 0;}
    catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
