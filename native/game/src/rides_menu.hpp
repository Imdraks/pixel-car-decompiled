#pragma once
#include <vector>
namespace pcr {
enum class RidesMenu { Home, Style, Body, BodyParts, Paint, Effects, Vanity, Performance, Parts };
enum class RidesAction { Menu, Cosmetic, Part, Showroom, Garage, Stance, Suspension, Transmission, Audio, Dyno, Cage, Lights };
struct RidesEntry {const char* label;const char* description;RidesAction action;int target=0;int slot=-1;};
inline const std::vector<RidesEntry>& ridesEntries(RidesMenu page){
    static const std::vector<RidesEntry> menus[]={
        {{"STYLE","Personnalisez l'apparence de votre voiture.",RidesAction::Menu,1},{"PERFORMANCE","Moteur, pièces et réglages de conduite.",RidesAction::Menu,7},{"ACHETER ET VENDRE","Ajoutez ou retirez des voitures de votre garage.",RidesAction::Showroom},{"TOUTES MES VOITURES","Retrouvez vos voitures et leurs préparations.",RidesAction::Garage}},
        {{"CARROSSERIE","Kits, éléments séparés et posture.",RidesAction::Menu,2},{"PEINTURE ET HABILLAGES","Peintures et décors du catalogue.",RidesAction::Menu,4},{"EFFETS DE CONDUITE","Fumée des pneus, NOS et éclairage.",RidesAction::Menu,5},{"ACCESSOIRES","Équipez les accessoires de votre voiture.",RidesAction::Menu,6},{"SON DE L'ÉCHAPPEMENT","Profils moteur, accélération et valve de décharge.",RidesAction::Audio}},
        {{"KITS CARROSSERIE","Choisissez un kit complet adapté à la voiture.",RidesAction::Cosmetic,4},{"MODIFIER LES ÉLÉMENTS","Pare-chocs, bas de caisse, aileron, roues et feux.",RidesAction::Menu,3},{"POSTURE","Réglez hauteur, ressorts et amortisseurs.",RidesAction::Stance}},
        {{"PARE-CHOCS AVANT","Choisissez le pare-chocs avant.",RidesAction::Cosmetic,5},{"PARE-CHOCS ARRIÈRE","Choisissez le pare-chocs arrière.",RidesAction::Cosmetic,6},{"BAS DE CAISSE","Choisissez les panneaux latéraux.",RidesAction::Cosmetic,7},{"AILERON","Choisissez l'aileron arrière.",RidesAction::Cosmetic,2},{"ROUES","Jantes avant/arrière et pneus.",RidesAction::Part,1,-1},{"FREINS VISUELS","Personnalisez les disques de frein.",RidesAction::Cosmetic,8},{"ÉCROUS","Choisissez les écrous de roues.",RidesAction::Cosmetic,11},{"VITRES","Réglez la teinte des vitres.",RidesAction::Cosmetic,12},{"PHARES","Personnalisez les phares.",RidesAction::Cosmetic,13},{"FEUX ARRIÈRE","Personnalisez les feux arrière.",RidesAction::Cosmetic,14}},
        {{"PEINTURE","Choisissez la couleur de carrosserie.",RidesAction::Cosmetic,0},{"HABILLAGES","Choisissez un habillage existant.",RidesAction::Cosmetic,1}},
        {{"FUMÉE DES PNEUS","La fumée suit le pneu spécial équipé.",RidesAction::Part,1,10},{"NOS","Choisissez votre système de NOS.",RidesAction::Part,2,5},{"COULEUR DES PHARES","Choisissez les ampoules.",RidesAction::Cosmetic,15},{"ALLUMER / ÉTEINDRE LES FEUX","Activez l'éclairage de la voiture.",RidesAction::Lights}},
        {{"ACCESSOIRES DE TOIT","Équipez le toit.",RidesAction::Cosmetic,3},{"SIÈGES","Personnalisez les sièges.",RidesAction::Cosmetic,9},{"CROCHETS DE REMORQUAGE","Choisissez un crochet.",RidesAction::Cosmetic,10},{"ARCEAU : ACTIVER / RETIRER","Équipez ou retirez l'arceau.",RidesAction::Cage}},
        {{"MOTEUR","Choisissez le moteur de votre préparation.",RidesAction::Part,0,0},{"PIÈCES","Parcourez toutes les catégories de pièces.",RidesAction::Menu,8},{"TENUE DE ROUTE","Suspension, équilibre et comportement au départ.",RidesAction::Suspension},{"BOÎTE ET TRANSMISSION","Rapports, pont et transmission.",RidesAction::Transmission},{"BANC DE PUISSANCE","Consultez la courbe de votre préparation.",RidesAction::Dyno}},
        {{"MOTEUR ET ECU","Moteurs universels et gestion électronique.",RidesAction::Part,0,0},{"ROUES ET PNEUS","Jantes et pneumatiques.",RidesAction::Part,1,-1},{"NOS","Systèmes de NOS.",RidesAction::Part,2,5},{"SURALIMENTATION","Turbos, compresseurs et intercoolers.",RidesAction::Part,3,2},{"CHÂSSIS","Suspension, freins et différentiel.",RidesAction::Part,4,1},{"ADMISSION ET ÉCHAPPEMENT","Admission, pistons, échappement et carburant.",RidesAction::Part,5,6},{"MOTORISATION ÉLECTRIQUE","Batterie, composants et surcharge.",RidesAction::Part,7,16},{"BOÎTES ET EMBRAYAGES","Boîtes, embrayages et réglages.",RidesAction::Part,8,15}}
    };
    return menus[static_cast<int>(page)];
}
inline const char* ridesTitle(RidesMenu page){
    static const char* names[]={"PERSONNALISER","STYLE","CARROSSERIE","ÉLÉMENTS","PEINTURE","EFFETS","ACCESSOIRES","PERFORMANCE","PIÈCES"};return names[static_cast<int>(page)];
}
}
