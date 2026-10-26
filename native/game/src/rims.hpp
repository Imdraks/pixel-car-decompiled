#pragma once
#include <array>
#include <algorithm>

namespace pcr {
// sp_rims is a mixed rendering sheet, not an equipment catalog. Its other
// frames are tyres, shadow/highlight passes and colour effects. Keep source
// frame IDs stable so existing valid equipment never changes appearance.
inline constexpr std::array<int,23> RimFrames{
    8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,36,42
};
inline bool isRimFrame(int frame){return std::find(RimFrames.begin(),RimFrames.end(),frame)!=RimFrames.end();}
inline int validRimFrame(int frame){return isRimFrame(frame)?frame:RimFrames.front();}
}
