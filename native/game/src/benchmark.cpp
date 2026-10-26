#include "benchmark.hpp"
#include "model.hpp"
#include <fstream>
#include <iomanip>
#include <locale>
#include <stdexcept>
#include <cmath>

namespace pcr {
void writePhysicsBenchmark(const std::filesystem::path& output){
    if(output.empty())throw std::runtime_error("Un dossier de mesure est requis.");
    std::filesystem::create_directories(output.parent_path());
    if(!std::filesystem::create_directory(output))throw std::runtime_error("Choisissez un nouveau dossier de mesure : aucun fichier existant ne sera remplacé.");
    std::ofstream csv(output/"telemetry.csv"),json(output/"physics-report.json");
    if(!csv||!json)throw std::runtime_error("Impossible d'écrire les mesures de physique.");
    csv.imbue(std::locale::classic());json.imbue(std::locale::classic());
    csv<<std::setprecision(10);json<<std::setprecision(10);
    csv<<"scenario,time_s,distance_m,speed_kmh,rpm,gear,shift_remaining_s,throttle,brake\n";
    auto sample=[&](const char* name,const CarState& car,DriverInput input,int tick){
        if(tick%12==0)csv<<name<<','<<car.elapsed<<','<<car.position<<','<<car.speed*3.6<<','<<car.rpm<<','<<car.gear<<','<<car.shiftLock<<','<<input.throttle<<','<<input.brake<<'\n';
    };
    Vehicle vehicle;
    CarState launch;double zeroTo100=0,quarter=0;
    for(int tick=0;tick<120*60;tick++){
        double oldSpeed=launch.speed,oldPosition=launch.position;
        stepCar(launch,vehicle,{true,false,true},Step,0);
        if(zeroTo100==0&&launch.speed>=100/3.6)
            zeroTo100=launch.elapsed-Step+Step*(100/3.6-oldSpeed)/(launch.speed-oldSpeed);
        if(quarter==0&&launch.position>=QuarterMile)
            quarter=launch.elapsed-Step+Step*(QuarterMile-oldPosition)/(launch.position-oldPosition);
        sample("launch",launch,{true,false,true},tick);
    }
    CarState brake;brake.speed=100/3.6;brake.gear=4;
    for(int tick=0;tick<120*20&&brake.speed>0;tick++){
        stepCar(brake,vehicle,{false,true,true},Step,0);sample("braking_100_0",brake,{false,true,true},tick);
    }
    CarState coast;coast.speed=100/3.6;coast.gear=4;
    for(int tick=0;tick<120*10;tick++){
        stepCar(coast,vehicle,{false,false,false},Step,0);sample("coast_100",coast,{false,false,false},tick);
    }
    CarState rolling;rolling.speed=80/3.6;rolling.gear=6;
    for(int tick=0;tick<120*30&&rolling.speed<120/3.6;tick++){
        stepCar(rolling,vehicle,{true,false,true},Step,0);sample("rolling_80_120",rolling,{true,false,true},tick);
    }
    CarState manual;
    for(int tick=0;tick<120*15;tick++){
        stepCar(manual,vehicle,{true,false,false},Step,0);sample("manual_first",manual,{true,false,false},tick);
    }
    bool passed=zeroTo100>0&&quarter>0&&brake.speed==0&&rolling.speed>=120/3.6
        &&std::isfinite(launch.speed)&&manual.rpm<vehicle.redlineRpm+50;
    json<<"{\n  \"schema\": 1,\n  \"model\": \"native-provisional-v0.3\",\n"
        <<"  \"original_game_equivalence_validated\": false,\n  \"step_seconds\": "<<Step<<",\n"
        <<"  \"vehicle\": {\"mass_kg\": "<<vehicle.mass<<", \"peak_torque_nm\": "<<vehicle.torque
        <<", \"wheel_radius_m\": "<<vehicle.wheelRadius<<", \"final_drive\": "<<vehicle.finalDrive
        <<", \"tyre_friction\": "<<vehicle.grip<<"},\n"
        <<"  \"measurements\": {\n    \"zero_to_100_s\": "<<zeroTo100<<",\n    \"quarter_mile_s\": "<<quarter
        <<",\n    \"speed_after_60_s_kmh\": "<<launch.speed*3.6
        <<",\n    \"braking_100_to_0_m\": "<<brake.position<<",\n    \"braking_100_to_0_s\": "<<brake.elapsed
        <<",\n    \"coast_speed_after_10_s_kmh\": "<<coast.speed*3.6
        <<",\n    \"rolling_80_to_120_s\": "<<rolling.elapsed
        <<",\n    \"manual_first_speed_after_15_s_kmh\": "<<manual.speed*3.6
        <<"\n  },\n  \"sanity_checks_passed\": "<<(passed?"true":"false")<<"\n}\n";
    csv.flush();json.flush();
    if(!csv||!json)throw std::runtime_error("Écriture des mesures interrompue.");
    if(!passed)throw std::runtime_error("Le banc de physique a détecté une anomalie ; consulter les rapports.");
}
}
