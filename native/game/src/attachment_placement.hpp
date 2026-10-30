#pragma once
#include "model.hpp"
#include "exhaust.hpp"
namespace pcr {
inline int cosmeticSubimage(const Profile& p,int slot){auto c=findCosmetic(p.cosmetics[slot]);return c&&c->slot==slot?c->subimage:0;}
inline int installedKit(const Profile& p,int side){int part=cosmeticSubimage(p,5+side);if(part)return part;part=cosmeticSubimage(p,4);return part?part:VehicleCatalog[bodyChoiceIndex(p)].baseKit;}
inline ExhaustPlacement installedExhaust(const Profile& p,int pipe,double ride){return placeExhaust(p.car,pipe,ride,p.contentSource,installedKit(p,1),installedKit(p,0));}
}
