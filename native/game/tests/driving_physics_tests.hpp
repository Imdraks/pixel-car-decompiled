#pragma once
#include <iomanip>
// Behavioural checks use SI units and compare forces/motion, not source literals.
static void checkDrivingPhysics(const std::filesystem::path& root){
    const int initial=checks;
    Profile slider;slider.allowWheelie=false;slider.wheelieTune=.35;
    expect(buildVehicle(slider).vehicle.allowWheelie,"wheelie slider alone enables physical lift despite a stale disabled legacy flag");
    slider.allowWheelie=true;slider.wheelieTune=1;
    expect(!buildVehicle(slider).vehicle.allowWheelie,"Balanced slider endpoint grounds the chassis despite a stale enabled legacy flag");
    {std::ofstream old(root/"wheelie-slider-conflict.ini");old<<"version=8\nallow_wheelie=0\nwheelie_tune=0.2\n";}
    auto restored=loadProfile(root/"wheelie-slider-conflict.ini",191,54);
    expect(restored.allowWheelie&&restored.wheelieTune==.2,"existing explicit slider values take precedence over the obsolete enable switch");
    std::string error;saveProfile(root/"wheelie-slider-roundtrip.ini",restored,error);auto roundtrip=loadProfile(root/"wheelie-slider-roundtrip.ini",191,54);
    expect(roundtrip.allowWheelie&&roundtrip.wheelieTune==.2,"single wheelie control remains authoritative after saving and restarting");
    auto native=buildVehicle(Profile{}).vehicle;
    native.mass=1200;native.torque=1700;native.boostPsi=0;native.nitroHp=0;
    native.grip=.95;native.drive=DriveLayout::Rear;native.frontWeightFraction=.48;
    native.drivenWeightFraction=.52;native.tractionControl=false;
    native.redlineRpm=8500;native.upshiftRpm=7800;native.launchRpm=2800;
    auto roadRpm=[](const CarState& s,const Vehicle& v){return s.speed/v.wheelRadius*v.ratios[s.gear-1]*v.finalDrive*60/(2*3.141592653589793);};
    std::ofstream trace(root/"driving-physics.csv");trace<<std::setprecision(10);
    trace<<"scenario,time_s,distance_m,speed_mps,rpm,gear,wheel_slip,driven_wheel_rad_s,front_load_n,rear_load_n,front_brake_slip,rear_brake_slip,lane,lateral_speed_mps,lateral_acceleration_mps2,tc,abs\n";
    auto sample=[&](const char* name,const CarState& s,double lane=1,double lateral=0){trace<<name<<','<<s.elapsed<<','<<s.position<<','<<s.speed<<','<<s.rpm<<','<<s.gear<<','<<s.wheelSlip<<','<<std::max(s.speed/native.wheelRadius,s.launchWheelOmega)<<','<<s.frontLoad<<','<<s.rearLoad<<','<<s.frontBrakeSlip<<','<<s.rearBrakeSlip<<','<<lane<<','<<lateral<<','<<s.lateralAcceleration<<','<<s.tcActive<<','<<s.absActive<<'\n';};
    CarState spinning;spinning.speed=18;spinning.gear=3;
    for(int t=0;t<120;t++){stepCar(spinning,native,{true,false,false},Step,0);if(t%12==0)sample("third_gear_power",spinning);}
    expect(spinning.launchClutch&&spinning.rpm>roadRpm(spinning,native)*1.15,"excess power in third gear spins driven wheels and raises engine RPM above road RPM");
    expect(spinning.rearRollDistance>spinning.position+2&&std::abs(spinning.frontRollDistance-spinning.position)<1e-7,"rolling acceleration rotates only the driven axle faster than ground travel");
    auto mild=native;mild.torque=100;CarState gentle;gentle.speed=18;gentle.gear=3;
    for(int t=0;t<120;t++)stepCar(gentle,mild,{true,false,false},Step,0);
    expect(!gentle.launchClutch&&gentle.wheelSlip==0&&std::abs(gentle.rearRollDistance-gentle.position)<1e-8,"low torque at road speed remains coupled without fabricated wheelspin");
    auto controlled=native;controlled.tractionControl=true;CarState tc;tc.speed=18;tc.gear=3;
    double peakFactor=1;
    for(int t=0;t<120;t++){stepCar(tc,controlled,{true,false,false},Step,0);peakFactor=std::min(peakFactor,tc.tractionFactor);if(t%12==0)sample("third_gear_tc",tc);}
    expect(!tc.launchClutch&&peakFactor<.9&&tc.rearRollDistance-tc.position<.25,"TC meters rolling acceleration rather than allowing uncontrolled wheel RPM");
    double rpmBefore=spinning.rpm;stepCar(spinning,native,{false,false,false},Step,0);
    expect(!spinning.launchClutch&&spinning.powerHp==0&&spinning.rpm<rpmBefore,"lifting the throttle ends powered wheelspin without adding wheel power");
    auto slowWheel=native;slowWheel.engineInertia=2;auto fastWheel=native;fastWheel.engineInertia=.12;
    std::array<CarState,2> inertias{};
    for(auto& s:inertias){s.speed=18;s.gear=3;}
    for(int t=0;t<24;t++){stepCar(inertias[0],slowWheel,{true,false,false},Step,0);stepCar(inertias[1],fastWheel,{true,false,false},Step,0);}
    expect(inertias[0].rpm<inertias[1].rpm,"rotational inertia controls how fast RPM flares under the same excess torque");
    CarState burnout;
    for(int t=0;t<240;t++)stepCar(burnout,native,{true,true,false},Step,0);
    stepCar(burnout,native,{true,false,false},Step,0);
    expect(!burnout.burningOut&&burnout.launchClutch&&burnout.launchWheelOmega>0,"releasing a burnout reconnects stored engine rotation through the same clutch model");
    auto braking=native;braking.torque=0;braking.frontWeightFraction=.70;braking.brakeDeceleration=9.3;braking.abs=false;
    CarState rearLock;rearLock.speed=25;rearLock.gear=4;
    stepCar(rearLock,braking,{false,true,false,false,false,false,true},Step,0);
    expect(!rearLock.frontLocked&&rearLock.rearLocked&&rearLock.frontRollDistance>0&&rearLock.rearRollDistance==0,"brake bias and axle loads can lock the rear while the front continues rolling");
    braking.abs=true;CarState independentAbs;independentAbs.speed=25;independentAbs.gear=4;
    stepCar(independentAbs,braking,{false,true,false,false,false,false,true},Step,0);
    expect(independentAbs.absActive&&!independentAbs.frontLocked&&!independentAbs.rearLocked&&independentAbs.frontBrakeSlip==0&&independentAbs.rearBrakeSlip>0,"ABS regulates the overloaded axle independently of the axle retaining grip");
    auto wheelieBrake=braking;wheelieBrake.allowWheelie=true;wheelieBrake.wheelieTune=0;
    CarState airStop;airStop.speed=25;airStop.pitch=.25;airStop.heave=.1;airStop.gear=4;
    stepCar(airStop,wheelieBrake,{false,true,false,false,false,false,true},Step,0);
    expect(airStop.frontLift>0&&airStop.frontLoad==0&&airStop.speed>0,"airborne front tyres contribute no fictitious service-braking grip");
    CarState dualBrake;dualBrake.speed=25;dualBrake.gear=4;
    stepCar(dualBrake,braking,{false,true,false,false,false,true},Step,0);
    expect(dualBrake.rearLocked&&dualBrake.rearRollDistance==0,"service-brake ABS does not unlock a simultaneously held rear handbrake");
    FreeDrive stopped;stopped.vehicle=native;stopped.setTraffic(false);stopped.changeLane(-1);
    for(int t=0;t<240;t++)stopped.update({false,false,false},Step);
    expect(stopped.lane==1&&stopped.lateralSpeed==0,"steering input cannot translate a stationary car sideways");
    auto course=[&](double speed,double grip,double seconds){FreeDrive d;d.vehicle=native;d.vehicle.torque=0;d.vehicle.grip=grip;d.player.speed=speed;d.player.gear=4;d.setTraffic(false);d.changeLane(-1);for(int t=0;t<int(seconds/Step);t++)d.update({false,false,false,false,false,false,true},Step);return d;};
    auto slow=course(3,.95,.5),fast=course(25,.95,.5),ice=course(25,.15,.5);
    expect(fast.lane<slow.lane&&fast.lateralSpeed<0,"low-speed steering takes longer to cross a lane than road-speed steering");
    expect(ice.lane>fast.lane,"low-grip tyres limit lateral acceleration and delay a requested lane change");
    expect(std::abs(ice.player.lateralAcceleration)<=.15*9.81*.85+1e-8,"steering demand respects tyre lateral force capacity");
    double lateralBefore=fast.lateralSpeed;fast.changeLane(2);fast.update({false,false,false},Step);
    expect(fast.lateralSpeed<0&&std::abs(fast.lateralSpeed-lateralBefore)<=native.grip*9.81*Step,"reversing steering first decelerates the lateral motion rather than teleporting it");
    FreeDrive turning,straight;turning.vehicle=straight.vehicle=controlled;turning.player.speed=straight.player.speed=18;turning.player.gear=straight.player.gear=3;turning.setTraffic(false);straight.setTraffic(false);turning.changeLane(-1);
    for(int t=0;t<60;t++){turning.update({true,false,false},Step);straight.update({true,false,false},Step);if(t%6==0)sample("accelerating_lane_change",turning.player,turning.lane,turning.lateralSpeed);}
    expect(turning.player.position<straight.player.position&&turning.player.speed<straight.player.speed,"turning and acceleration share finite tyre grip and lateral kinetic energy is not free");
    FreeDrive airborne;airborne.vehicle=native;airborne.setTraffic(false);airborne.player.speed=20;airborne.player.suspensionReady=true;airborne.player.frontLoad=0;airborne.player.rearLoad=native.mass*9.81;airborne.changeLane(-1);airborne.update({false,false,false},Step);
    expect(airborne.lane==1&&airborne.lateralSpeed==0,"front-wheel lift removes steering authority until front contact is restored");
    bool allFinite=true;int cars=0;
    for(int i=0;i<430;i++){
        auto p=factoryVehicle(i);FreeDrive d;d.vehicle=buildVehicle(p).vehicle;d.vehicle.abs=d.vehicle.tractionControl=true;d.setTraffic(false);d.player.speed=25;d.player.gear=3;d.changeLane(i%2?1:-1);
        for(int t=0;t<360;t++){d.update({t<120,t>=120,true},Step);allFinite&=std::isfinite(d.player.speed)&&std::isfinite(d.player.rpm)&&std::isfinite(d.player.pitch)&&std::isfinite(d.lane)&&d.player.speed>=0&&d.lane>=0&&d.lane<=2&&d.player.frontLoad>=0&&d.player.rearLoad>=0;}
        ++cars;
    }
    expect(allFinite&&cars==430,"all stored Original Unbound Underground vehicles retain finite steering, acceleration and braking");
    std::array<FreeDrive,3> fpsRuns;
    for(int run=0;run<3;run++){
        auto& d=fpsRuns[run];d.vehicle=controlled;d.player.speed=18;d.player.gear=3;d.setTraffic(false);d.changeLane(1);double accumulator=0;int fps=std::array<int,3>{30,60,144}[run];
        for(int f=0;f<fps*3;f++){accumulator+=1.0/fps;while(accumulator+1e-12>=Step){d.update({true,false,true},Step);accumulator-=Step;}}
    }
    expect(std::abs(fpsRuns[0].lane-fpsRuns[2].lane)<1e-10&&std::abs(fpsRuns[0].player.position-fpsRuns[1].player.position)<1e-8,"combined longitudinal and lateral motion remains identical at 30 60 and 144 render FPS");
    {std::ofstream out(root/"driving-physics.json");out<<std::setprecision(10)<<"{\n  \"checks_passed\": "<<checks-initial<<",\n  \"vehicles_checked\": "<<cars<<",\n  \"rolling_spin_rpm\": "<<rpmBefore<<",\n  \"gentle_rpm\": "<<gentle.rpm<<",\n  \"tc_rolling_distance_m\": "<<tc.position<<",\n  \"turning_distance_m\": "<<turning.player.position<<",\n  \"straight_distance_m\": "<<straight.player.position<<",\n  \"low_grip_lane\": "<<ice.lane<<",\n  \"road_grip_lane\": "<<course(25,.95,.5).lane<<",\n  \"independent_axle_abs\": true,\n  \"physics_reconstructed_native\": true,\n  \"full_android_dynamics_equivalence\": false\n}\n";}
}
