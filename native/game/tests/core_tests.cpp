#include "garage_audio.hpp"
#include "simulated_engine_mix.hpp"
#include "saved_cars.hpp"
#include "vehicle_inventory.hpp"
#include "rides_menu.hpp"
#include "model.hpp"
#include "engine_mix.hpp"
#include "garage_engine.hpp"
#include "benchmark.hpp"
#include "art.hpp"
#include "effects.hpp"
#include "road_scene.hpp"
#include "chassis_pose.hpp"
#include "materials.hpp"
#include "cosmetic_geometry.hpp"
#include "rim_finish_art.hpp"
#include "original_ui.hpp"
#include "content_art.hpp"
#include "base_audio.hpp"
#include "attachment_placement.hpp"
#include <cmath>
#include <algorithm>
#include <numeric>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <set>
using namespace pcr;
static int checks=0;
static void expect(bool value,const char* message){++checks;if(!value)throw std::runtime_error(message);}
static CarState simulated(int framesPerSecond,bool endless){
    CarState car;Vehicle v;double accumulator=0;
    for(int frame=0;frame<framesPerSecond*70&&!car.finished;frame++){
        accumulator+=1.0/framesPerSecond;
        while(accumulator+1e-12>=Step){stepCar(car,v,{true,false,true},Step,endless?0:QuarterMile);accumulator-=Step;}
    }return car;
}
int main(int argc,char**argv){
 try{
    if(argc!=2)throw std::runtime_error("Supply an isolated test directory");
    auto root=std::filesystem::u8path(argv[1]);std::filesystem::create_directories(root);
    expect(std::abs(scene::pixels(2.6)-124.8)<1e-9,"scene scale matches a typical rendered wheelbase");
    expect(std::abs(scene::layerTravel(100/3.6)-1333.333333333)<1e-6,"100 km/h moves the ground 1333 canvas pixels in one second");
    expect(scene::layerTravel(200/3.6)==2*scene::layerTravel(100/3.6),"doubling speed doubles visible ground travel");
    expect(scene::trafficX(110,100)-scene::trafficX(100,100)==scene::pixels(10),"traffic and road share a metre scale");
    expect(scene::Mountains<scene::City&&scene::City<scene::Trees&&scene::Trees<1,"distant layers move slower in depth order");
    expect(std::abs(scene::roadPhase(11.9)+scene::pixels(.2)-scene::roadPhase(12.1)-scene::pixels(12))<1e-9,"road markings wrap seamlessly across their period");
    expect(std::abs(scene::wheelAngle(2*3.14159265358979323846*.32,.32))<1e-9,"a tyre circumference gives one wheel revolution");
    bool motionStable=true;
    for(int fps:{30,60,120,144,165,240}){
        double position=0;for(int frame=0;frame<fps*3;frame++)position+=100/3.6/fps;
        motionStable&=std::abs(scene::layerTravel(position)-4000)<1e-7;
    }
    expect(motionStable,"distance-driven scenery is independent of frame rate");
    // Manually checked against the supplied alpha cutouts for the reported body.
    const auto& reportedWheels=art::wheelPositions[20];
    expect(reportedWheels.rear==62&&reportedWheels.front==160&&reportedWheels.y==58&&reportedWheels.radius==12.5f,
           "body 021 wheels align with the actual arches instead of body-width fractions");
    expect(art::wheelPositions[22].front==125&&art::wheelPositions[190].front==153,
           "short and long wheelbases have independent front axle anchors");
    bool anchorsValid=std::size(art::wheelPositions)==std::size(art::cars);
    for(size_t i=0;i<std::size(art::wheelPositions);++i){
        const auto& w=art::wheelPositions[i];
        anchorsValid&=i==182?w.radius==0:(w.rear==62&&w.front>w.rear+30&&w.front<art::cars[i].canvasW&&w.y==58&&w.radius==12.5f);
    }
    expect(anchorsValid,"all car bodies have reviewed wheel anchors or an explicit archless exception");
    auto reference=simulated(30,false);
    expect(reference.finished&&reference.finishTime>8&&reference.finishTime<40,"native car completes quarter mile");
    for(int fps:{60,120,144,165,240}){auto c=simulated(fps,false);expect(std::abs(c.finishTime-reference.finishTime)<1e-9,"simulation independent of rendering rate");}
    auto endless=simulated(60,true);
    expect(!endless.finished&&endless.position>QuarterMile*2,"free drive does not finish at 402 metres");
    Vehicle v;double before=endless.speed;
    for(int i=0;i<1200;i++)stepCar(endless,v,{false,true,true},Step,0);
    expect(endless.speed<before&&endless.speed==0,"brakes stop the vehicle without reversing");
    // Behavioural regressions for the provisional drivetrain, independent of graphics.
    CarState restart;restart.gear=6;
    for(int i=0;i<1200;i++)stepCar(restart,v,{true,false,true},Step,0);
    expect(restart.speed>20,"automatic gearbox recovers from a high gear at rest");
    CarState manual;manual.speed=55;manual.gear=4;
    expect(!shift(manual,-1,v)&&manual.gear==4,"unsafe manual downshift is rejected");
    CarState changing;changing.speed=15;changing.gear=2;
    expect(shift(changing,1,v),"safe manual upshift accepted");
    double shiftSpeed=changing.speed;
    stepCar(changing,v,{true,false,false},Step,0);
    expect(changing.speed<shiftSpeed,"shift interrupts wheel torque");
    expect(!shift(changing,-1,v),"shift lock prevents instantaneous repeated shifts");
    CarState low,high;low.speed=high.speed=20;low.gear=2;high.gear=5;
    for(int i=0;i<120;i++){stepCar(low,v,{false,false,false},Step,0);stepCar(high,v,{false,false,false},Step,0);}
    expect(low.speed<high.speed,"lower gear provides stronger engine braking");
    CarState braking,conflicting;braking.speed=conflicting.speed=100/3.6;
    double brakingTime=0;bool roadBrakingSame=true;
    for(int i=0;i<1200&&braking.speed>0;i++){
        stepCar(braking,v,{false,true,true},Step,0);stepCar(conflicting,v,{true,true,true},Step,0);brakingTime+=Step;
        if(braking.speed>3)roadBrakingSame&=std::abs(braking.position-conflicting.position)<1e-9;
    }
    expect(braking.speed==0&&braking.position>35&&braking.position<55,"100 km/h stopping distance remains plausible");
    for(int tick=0;tick<120;tick++)stepCar(conflicting,v,{true,true,true},Step,0);
    expect(roadBrakingSame&&conflicting.speed==0,"brake overrides simultaneous throttle at road speed, then holds the low-speed burnout stopped");
    CarState lighter,heavier;lighter.speed=heavier.speed=25;lighter.gear=heavier.gear=3;
    Vehicle heavy=v;heavy.mass*=1.5;
    for(int i=0;i<120;i++){stepCar(lighter,v,{true,false,false},Step,0);stepCar(heavier,heavy,{true,false,false},Step,0);}
    expect(lighter.speed>heavier.speed,"added mass reduces acceleration outside traction limit");
    CarState grip;Vehicle slippery=v;slippery.grip=.4;
    for(int i=0;i<120;i++)stepCar(grip,slippery,{true,false,false},Step,0);
    expect(grip.speed<9.81*slippery.grip,"traction bounds launch acceleration");
    CarState ice;ice.speed=20;ice.gear=1;
    Vehicle iceCar=v;iceCar.grip=.15;iceCar.dragArea=0;iceCar.rollingResistance=0;
    double iceBefore=ice.speed;stepCar(ice,iceCar,{false,true,false},Step,0);
    expect((iceBefore-ice.speed)/Step<=9.81*iceCar.grip+1e-9,"engine and service brakes share tyre adhesion limit");
    Vehicle front=v,rear=v,all=v;
    front.drive=DriveLayout::Front;rear.drive=DriveLayout::Rear;all.drive=DriveLayout::All;
    front.drivenWeightFraction=rear.drivenWeightFraction=.5;
    CarState frontState,rearState,allState;
    stepCar(frontState,front,{true,false,false},Step,0);
    stepCar(rearState,rear,{true,false,false},Step,0);
    stepCar(allState,all,{true,false,false},Step,0);
    expect(rearState.speed>frontState.speed,"rear drive gains launch adhesion through load transfer");
    expect(allState.speed>rearState.speed,"all wheel drive uses more available launch adhesion");
    front.centreOfGravityHeight=rear.centreOfGravityHeight=0;
    frontState=CarState{};rearState=CarState{};
    stepCar(frontState,front,{true,false,false},Step,0);stepCar(rearState,rear,{true,false,false},Step,0);
    expect(std::abs(frontState.speed-rearState.speed)<1e-12,"equal axle loads without transfer give equal launch adhesion");
    CarState limiter;
    for(int i=0;i<120*30;i++)stepCar(limiter,v,{true,false,false},Step,0);
    expect(limiter.gear==1&&limiter.rpm<v.redlineRpm+50,"manual first gear cannot accelerate indefinitely past redline");
    CarState stable;stable.speed=18;stable.gear=3;int changes=0,lastGear=3;
    for(int i=0;i<120*8;i++){
        stepCar(stable,v,{false,false,true},Step,0);
        if(stable.gear!=lastGear){++changes;lastGear=stable.gear;}
    }
    expect(changes<=2,"automatic coastdown does not hunt between gears");
    CarState launch;double zeroToHundred=0;
    std::ofstream trace(root/"physics-baseline.csv");
    trace<<"time_s,speed_kmh,rpm,gear,distance_m\n";
    for(int i=0;i<120*30;i++){
        stepCar(launch,v,{true,false,true},Step,0);
        if(zeroToHundred==0&&launch.speed>=100/3.6)zeroToHundred=launch.elapsed;
        if(i%12==0)trace<<launch.elapsed<<','<<launch.speed*3.6<<','<<launch.rpm<<','<<launch.gear<<','<<launch.position<<'\n';
    }
    expect(zeroToHundred>3&&zeroToHundred<12,"baseline reaches 100 km/h within a plausible broad envelope");
    expect(braking.gear==1,"automatic gearbox returns to first after a full stop");
    std::cout<<"0-100 km/h "<<zeroToHundred<<" s; telemetry physics-baseline.csv\n";
    std::cout<<"Physics baseline (provisional, not original): 100-0 km/h "<<braking.position<<" m / "<<brakingTime
             <<" s; restart in sixth after 10 s "<<restart.speed*3.6<<" km/h\n";
    FreeDrive free;free.changeLane(-100);expect(free.targetLane==0,"left lane clamp");free.changeLane(100);expect(free.targetLane==2,"right lane clamp");
    for(int i=0;i<180;i++)free.update({true,false,true},Step);
    expect(free.lane<=2&&free.lane>=0&&free.player.position>0,"free drive moves and interpolates lanes");
    FreeDrive collision;collision.player.speed=30;collision.traffic[0]={0,10,1,0};collision.update({true,false,true},Step);
    expect(collision.collisionCooldown>0&&collision.player.speed<10,"traffic collision changes vehicle motion");
    FreeDrive emptyRoad;emptyRoad.setTraffic(false);emptyRoad.player.speed=30;emptyRoad.traffic[0]={0,0,1,0};
    for(int i=0;i<120;i++)emptyRoad.update({true,false,true},Step);
    expect(!emptyRoad.trafficEnabled&&emptyRoad.collisionCooldown==0&&emptyRoad.player.speed>30,"disabled traffic cannot slow or collide with the player");
    expect(emptyRoad.traffic[0].position==0&&emptyRoad.overtakes==0,"disabled traffic does not move, respawn or count overtakes");
    emptyRoad.setTraffic(true);bool safeRespawn=true;
    for(const auto& t:emptyRoad.traffic)safeRespawn&=t.position-emptyRoad.player.position>=120;
    expect(emptyRoad.trafficEnabled&&safeRespawn,"re-enabling traffic respawns all cars safely ahead");
    {std::ofstream out(root/"old-settings.ini");out<<"sound=0\n";}
    expect(loadSettings(root/"old-settings.ini").traffic,"existing settings keep traffic enabled by default");
    auto benchmark=root/std::filesystem::u8path("mesures_é_車");
    std::filesystem::remove_all(benchmark); // Only inside the explicitly supplied test directory.
    writePhysicsBenchmark(benchmark);
    expect(std::filesystem::file_size(benchmark/"telemetry.csv")>1000,"physics benchmark produces a time series on a Unicode path");
    std::ifstream benchmarkIn(benchmark/"physics-report.json");
    std::string benchmarkText((std::istreambuf_iterator<char>(benchmarkIn)),std::istreambuf_iterator<char>());
    expect(benchmarkText.find("\"sanity_checks_passed\": true")!=std::string::npos,"benchmark scenarios pass their sanity checks");
    bool refused=false;try{writePhysicsBenchmark(benchmark);}catch(const std::exception&){refused=true;}
    expect(refused,"benchmark refuses to replace an existing directory");
    expect(std::size(PartCatalog)==524,"merged original and Unbound performance entries are included");
    std::array<int,PartSlotCount> counts{};
    for(const auto& part:PartCatalog)++counts[int(part.slot)];
    expect(counts==std::array<int,PartSlotCount>{176,29,43,19,13,9,26,13,7,65,74,6,6,6,6,9,4,4,4,5},"catalog includes every requested category and supercharger split");
    Profile custom;
    expect(equipPart(custom,PartSlot::Engine,1002),"2JZ can be equipped by stable catalog ID");
    auto jz=buildVehicle(custom);
    expect(std::abs(jz.baseHp-410)<.001,"recovered 2JZ catalog power drives the native torque curve");
    Profile lowPower,highPower;equipPart(lowPower,PartSlot::Engine,1001);equipPart(highPower,PartSlot::Engine,1014);
    auto lowBuild=buildVehicle(lowPower),highBuild=buildVehicle(highPower);
    // Isolate engine power from tyre saturation for this rolling comparison.
    lowBuild.vehicle.grip=highBuild.vehicle.grip=4;CarState lowRun,highRun;
    lowRun.speed=highRun.speed=30;lowRun.gear=highRun.gear=4;
    for(int i=0;i<120;i++){stepCar(lowRun,lowBuild.vehicle,{true,false,false},Step,0);stepCar(highRun,highBuild.vehicle,{true,false,false},Step,0);}
    expect(highRun.speed>lowRun.speed+.5&&highRun.rpm<highBuild.vehicle.redlineRpm,"stronger engine improves rolling acceleration below its own rev limit");
    equipPart(custom,PartSlot::Turbo,3002);equipPart(custom,PartSlot::Supercharger,3020);
    expect(custom.parts[int(PartSlot::Turbo)]==0&&custom.parts[int(PartSlot::Supercharger)]==3020,"turbo and supercharger are mutually exclusive");
    expect(!equipPart(custom,PartSlot::Engine,3002)&&!equipPart(custom,PartSlot::Engine,999999),"wrong-category and unknown IDs are rejected");
    equipPart(custom,PartSlot::Turbo,3026);
    auto turboBuild=buildVehicle(custom);CarState spool;spool.speed=30;spool.gear=3;
    for(int i=0;i<240;i++)stepCar(spool,turboBuild.vehicle,{true,false,false},Step,0);
    expect(spool.boostPsi>10&&spool.boostPsi<=35,"equipped turbo develops bounded boost under load");
    for(int i=0;i<120;i++)stepCar(spool,turboBuild.vehicle,{false,false,false},Step,0);
    expect(spool.boostPsi==0,"turbo boost releases when the throttle is lifted");
    equipPart(custom,PartSlot::Ecu,4008);auto ecuBuild=buildVehicle(custom);
    expect(ecuBuild.vehicle.redlineRpm==10500&&ecuBuild.vehicle.upshiftRpm==9500,"ECU raises the native rev limit and automatic shift threshold");
    equipPart(custom,PartSlot::Tires,10017);auto tireBuild=buildVehicle(custom);
    expect(tireBuild.vehicle.grip>1.5&&tireBuild.tireFrame==17,"tires change adhesion and select the matching original tire image");
    equipPart(custom,PartSlot::Suspension,2015);auto lowered=buildVehicle(custom);
    expect(lowered.rideOffset==6&&lowered.vehicle.centreOfGravityHeight<.5,"suspension changes visible ride height and native weight transfer");
    Profile nitroProfile;equipPart(nitroProfile,PartSlot::Nos,5007);auto nitroBuild=buildVehicle(nitroProfile);
    CarState nitroRun,plainRun;nitroRun.speed=plainRun.speed=40;nitroRun.gear=plainRun.gear=4;
    for(int i=0;i<120*2;i++){stepCar(nitroRun,nitroBuild.vehicle,{true,false,false,true},Step,0);stepCar(plainRun,nitroBuild.vehicle,{true,false,false,false},Step,0);}
    expect(nitroRun.speed>plainRun.speed&&std::abs(nitroRun.nitroRemaining-8)<1e-6,"NOS adds power only when activated and consumes its charge");
    double charge=nitroRun.nitroRemaining;stepCar(nitroRun,nitroBuild.vehicle,{true,true,false,true},Step,0);
    expect(!nitroRun.nitroActive&&nitroRun.nitroRemaining==charge,"braking blocks NOS and preserves its charge");
    for(int i=0;i<120*12;i++)stepCar(nitroRun,nitroBuild.vehicle,{true,false,true,true},Step,0);
    expect(nitroRun.nitroRemaining==0&&!nitroRun.nitroActive,"NOS runs out without becoming negative");
    bool allPartsStable=true;
    for(const auto& part:PartCatalog){
        Profile single;if(int(part.slot)>=16)equipPart(single,PartSlot::Engine,20000);allPartsStable&=equipPart(single,part.slot,part.id);auto setup=buildVehicle(single);CarState run;
        for(int i=0;i<120*3;i++)stepCar(run,setup.vehicle,{true,false,true,true},Step,0);
        allPartsStable&=std::isfinite(run.speed)&&std::isfinite(run.rpm)&&run.speed>0&&run.rpm>0&&setup.vehicle.mass>=600;
    }
    expect(allPartsStable,"all 496 parts build a finite driveable configuration");
    std::string customError;
    expect(saveProfile(root/"custom.ini",custom,customError),"custom equipment profile saves");
    auto customLoaded=loadProfile(root/"custom.ini",191,54);
    expect(customLoaded.parts==custom.parts,"all equipment slots persist through a profile round trip");
    {std::ofstream out(root/"custom.ini");out<<"part_engine=3002\npart_tires=999999\npart_turbo=3002\npart_supercharger=3020\n";}
    auto corruptCustom=loadProfile(root/"custom.ini",191,54);
    expect(corruptCustom.parts[0]==0&&corruptCustom.parts[10]==0&&corruptCustom.parts[2]==0&&corruptCustom.parts[3]==3020,"malformed equipment falls back safely and cannot stack forced induction");
    EngineMix audioEnvelope;audioEnvelope.update(8000,true,true,1.0/60);
    expect(enginePlaybackPitch(900,24)==enginePlaybackPitch(900,21)&&enginePlaybackPitch(2500,24)==enginePlaybackPitch(2500,21),"LS playback retains its idle and low-RPM timbre");
    expect(enginePlaybackPitch(8000,24)>1.6&&enginePlaybackPitch(9500,24)>1.79&&enginePlaybackPitch(8000,21)==1.3&&enginePlaybackPitch(8000,71)==1.3,"LS V8 playback reaches a higher register without raising unrelated engine samples");
    bool v8Progressive=true;double prior=0;for(int rpm=800;rpm<=14000;rpm+=25){double pitch=enginePlaybackPitch(rpm,24);v8Progressive&=pitch>=prior&&pitch<=1.95;prior=pitch;}
    expect(v8Progressive,"V8 playback climbs progressively through the rev range and remains bounded");
    expect(audioEnvelope.load>0&&audioEnvelope.load<1&&audioEnvelope.pitch<1.4,"engine load fades in and high RPM avoids the old excessive pitch multiplier");
    for(int i=0;i<120;i++)audioEnvelope.update(8000,true,true,1.0/60);
    expect(audioEnvelope.load>.999,"steady throttle selects the load sample without a permanent detuned coast layer");
    audioEnvelope.update(1000,false,true,1.0/60);
    expect(audioEnvelope.load>0&&audioEnvelope.load<1&&audioEnvelope.pitch>1,"RPM and load transitions are smoothed on throttle release");
    audioEnvelope.update(1000,false,false,1.0/60);expect(audioEnvelope.load==0&&!audioEnvelope.ready,"stopping the engine resets the audio envelope");
    std::vector<float> loopFixture(8000);for(size_t i=0;i<loopFixture.size();i++)loopFixture[i]=float(.4+.3*std::sin(i*.03));
    auto joined=seamlessEngineLoop(loopFixture.data(),4000,2,48000);double maxSeam=0;for(int channel=0;channel<2;channel++)maxSeam=std::max(maxSeam,double(std::abs(joined[channel]-joined[joined.size()-2+channel])));
    expect(joined.size()<loopFixture.size()&&maxSeam<.03&&*std::max_element(joined.begin(),joined.end())<=.7f,"engine loop tail overlaps its head with bounded peaks and continuous wrap");
    expect(std::abs(sourceSound(20,0).volume-.33)<.001&&std::abs(sourceSound(21,0).volume-.81)<.001&&std::abs(sourceSound(24,1).volume-.93)<.001,"original sample gain metadata is retained instead of treating all recordings equally");
    GarageEngine garageMotor;garageMotor.stop();garageMotor.update(v,true,1);
    expect(!garageMotor.running&&garageMotor.state.rpm==0,"garage throttle cannot start a stopped engine");
    garageMotor.toggle(v);for(int i=0;i<240;i++)garageMotor.update(v,true,Step);
    expect(garageMotor.running&&garageMotor.limiting&&garageMotor.state.rpm>=v.redlineRpm*.98&&garageMotor.state.rpm<=v.redlineRpm,"garage ignition and held accelerator reach a bounded audible limiter");
    expect(garageMotor.state.position==0&&garageMotor.state.speed==0&&garageMotor.state.frontRollDistance==0&&garageMotor.state.rearRollDistance==0&&garageMotor.state.nitroRemaining==10,"garage revving never moves wheels or consumes NOS");
    for(int i=0;i<240;i++)garageMotor.update(v,false,Step);
    expect(!garageMotor.limiting&&garageMotor.state.rpm==v.idleRpm,"releasing garage throttle returns to idle");
    auto lowRevGarage=v;lowRevGarage.redlineRpm=6500;for(int i=0;i<120;i++)garageMotor.update(lowRevGarage,true,Step);
    expect(garageMotor.state.rpm<=6500&&garageMotor.limiting,"garage limiter follows a newly installed engine redline");
    garageMotor.toggle(v);expect(!garageMotor.running&&garageMotor.state.rpm==0&&!garageMotor.limiting,"second garage ignition press stops all engine state");
    Profile soundProfile;soundProfile.soundOn=5;soundProfile.soundOff=4;soundProfile.bov=3;
    auto sounds=engineSamples(soundProfile);
    expect(sounds.on==71&&sounds.off==47,"manual sound profiles match the original native dispatch tables");
    bool replacementAudio=true;int engineAudioCases=0;
    for(int source=0;source<2;source++)for(const auto& part:PartCatalog)if(part.slot==PartSlot::Engine&&part.id>=1001&&part.id<=1016){
        Profile p;p.audioSource=source;equipPart(p,PartSlot::Engine,part.id);auto selected=engineSamples(p);
        // Independent fixture from the two source engine_hp/e_s/e_s2 chains.
        int on=part.stat==478?71:part.stat==656?79:part.stat==542?20:part.stat>=505?24:21;
        int off=part.stat==478?23:part.stat==542?24:20;
        replacementAudio&=selected.on==on&&selected.off==off;++engineAudioCases;
    }
    expect(replacementAudio&&engineAudioCases==32,"all sixteen equipped engines select their recovered acceleration and deceleration samples in both audio banks");
    bool pcValid=true;int pcCount=0;
    std::ofstream pcReport(root/"pc-engines.csv");pcReport<<"id,name,hp,redline_rpm,litres,inertia,on,off\n";
    for(const auto& e:PcEngines){
        if(nfsEngine(e.id))continue;
        Profile p;equipPart(p,PartSlot::Engine,e.id);auto b=buildVehicle(p);auto sounds=engineSamples(p);
        const auto* part=findPart(e.id);
        pcValid&=part&&part->sourceMask==4&&std::abs(b.boostedHp-part->stat)<.01&&b.vehicle.redlineRpm==e.redlineRpm;
        pcValid&=b.vehicle.engineInertia==e.inertia&&sounds.on==e.soundOn&&sounds.off==e.soundOff;
        pcValid&=torqueCurve(b.vehicle,1500)!=torqueCurve(b.vehicle,6000);
        std::string err;saveProfile(root/"pc-engine.ini",p,err);auto saved=loadProfile(root/"pc-engine.ini",191,54);
        pcValid&=saved.parts[0]==e.id;
        GarageEngine garage;garage.toggle(b.vehicle);for(int tick=0;tick<480;tick++)garage.update(b.vehicle,true,Step);
        pcValid&=garage.limiting&&garage.state.rpm<=e.redlineRpm;
        CarState state;for(int tick=0;tick<600;tick++)stepCar(state,b.vehicle,{true,false,true},Step,0);
        pcValid&=std::isfinite(state.speed)&&state.speed>0;
        pcReport<<e.id<<','<<part->name<<','<<b.boostedHp<<','<<e.redlineRpm<<','<<e.litres<<','<<e.inertia<<','<<sounds.on<<','<<sounds.off<<'\n';++pcCount;
    }
    expect(pcValid&&pcCount==15,"fifteen PC engine swaps retain rated power, individual curves/inertia, audio, save/load, garage limiter and finite driving");
    Profile pcFactory;equipPart(pcFactory,PartSlot::Engine,1501);
    expect(buildVehicle(pcFactory).vehicle.factoryBoostSoundPsi>0,"factory turbo sound is available without fitting an aftermarket turbo");
    equipPart(pcFactory,PartSlot::Turbo,3026);
    expect(buildVehicle(pcFactory).vehicle.factoryBoostSoundPsi==0&&!buildVehicle(pcFactory).vehicle.supercharged,"aftermarket induction replaces the factory sound layer without stacking it");
    {auto garage=root/"saved-cars";std::filesystem::remove_all(garage);Profile named;named.savedName="Drag ZG";named.car=20;named.rim=10100;named.rearRim=10101;
        named.contentSource=1;named.audioSource=1;named.rollCage=true;named.headlights=true;named.factoryDrive=false;named.drive=DriveLayout::Rear;
        equipBestParts(named);equipPart(named,PartSlot::Engine,1008);applyGearboxPreset(named,7);applySuspensionPreset(named,SuspensionPreset::Wheelie);
        named.cosmetics[6]=106011;named.soundOn=5;named.soundOff=4;named.bov=3;named.bestTime=12.345678;
        std::string error;expect(storeSavedCar(garage,1,named,error),"named garage stores a complete prepared car atomically");
        auto first=savedCars(garage);expect(first.size()==1&&first[0].profile.savedName==named.savedName&&nextSavedCarId(garage)==2,"named garage lists saved cars and chooses a free slot");
        saveProfile(root/"garage-expected.ini",named,error);saveProfile(root/"garage-loaded.ini",first[0].profile,error);
        auto contents=[](const std::filesystem::path& file){std::ifstream in(file,std::ios::binary);return std::string(std::istreambuf_iterator<char>(in),{});};
        expect(contents(root/"garage-expected.ini")==contents(root/"garage-loaded.ini"),"named car round trip retains every serialized mechanical, appearance, gearing, suspension, audio and record setting");
        Profile second=named;second.savedName="AMG Route";second.car=21;equipPart(second,PartSlot::Engine,1501);
        expect(storeSavedCar(garage,2,second,error)&&savedCars(garage).size()==2,"saving another configuration preserves the first car");
        expect(storeSavedCar(garage,1,second,error)&&loadProfile(garage/"car-1.ini.bak",191,54).parts[0]==1008,"updating a saved car preserves its previous full configuration in a backup");
        std::ofstream(garage/"car-0001.ini")<<"car=5\n";
        expect(savedCars(garage).size()==2&&!storeSavedCar(garage,0,named,error),"garage ignores noncanonical filenames and refuses invalid slots");
    }
    // Workbook records have explicit native calibration, separate from source regressions.
    expect(std::size(NfsEngines)==145&&std::size(NfsUpgrades)==122,"145 workbook engines, 113 performance parts and nine new Contraband extensions are installed");
    expect(std::string(rarityLabel(Rarity::Basic))=="BASIC"&&std::string(rarityLabel(Rarity::Sport))=="SPORT"&&std::string(rarityLabel(Rarity::Pro))=="PRO"&&std::string(rarityLabel(Rarity::Super))=="SUPER"&&std::string(rarityLabel(Rarity::Elite))=="ELITE"&&std::string(rarityLabel(Rarity::Contraband))=="CONTREBANDE","class names run Basic through Elite with Contraband highest");
    bool allNfs=true,nfsUpgrades=true,nfsSounds=true,nfsAssociations=true;int nfsCases=0;
    std::ofstream nfsReport(root/"nfs-engines.csv");nfsReport<<"id,stock_hp,potential_hp,measured_stock_hp,measured_elite_hp,redline_rpm,electric,simulated_audio\n";
    for(const auto& e:NfsEngines){
        Profile p;allNfs&=equipPart(p,PartSlot::Engine,e.id);auto stock=buildVehicle(p);
        allNfs&=std::abs(stock.boostedHp-e.hp)<.01&&stock.vehicle.redlineRpm==e.redline;
        allNfs&=int(partRarity(*findPart(e.id)))==e.grade;
        if(e.electric){for(int kind:{16,17,18})for(const auto& u:NfsUpgrades)if(u.kind==kind&&u.grade==4)equipPart(p,PartSlot(kind),u.id);}
        else for(int kind:{6,4,11,9,2})for(const auto& u:NfsUpgrades)if(u.kind==kind&&u.grade==4&&(kind!=2||u.variant==1))equipPart(p,findPart(u.id)->slot,u.id);
        auto elite=buildVehicle(p);allNfs&=std::abs(elite.boostedHp-e.potentialHp)<.02;
        for(int tick=0;tick<120;tick++){CarState state;stepCar(state,elite.vehicle,{true,false,true},Step,0);allNfs&=std::isfinite(state.speed)&&std::isfinite(state.rpm);}
        std::string error;allNfs&=saveProfile(root/"nfs-profile.ini",p,error)&&loadProfile(root/"nfs-profile.ini",191,54).parts==p.parts;
        bool sound=simulatedPack(e.id)!=nullptr;nfsSounds&=e.audioFamily[0]?sound:!sound;
        nfsReport<<e.id<<','<<e.hp<<','<<e.potentialHp<<','<<stock.boostedHp<<','<<elite.boostedHp<<','<<e.redline<<','<<e.electric<<','<<sound<<'\n';++nfsCases;
    }
    expect(allNfs&&nfsCases==145,"all 145 engines retain workbook base power, reach the conservative advertised potential with Elite parts and save their equipment");
    expect(nfsSounds,"every supported workbook engine is bound to its declared physical family and unsupported layouts retain an explicit fallback");
    for(const auto& link:NfsCompatibilities)nfsAssociations&=findPart(link.engineId)&&nfsCompatibility(link.body,link.source,link.engineId)>0;
    expect(nfsAssociations&&nfsFactoryEngine(121,1)>0&&nfsFactoryEngine(121,0)==0&&nfsFactoryEngine(100,0)==0,"spreadsheet compatibility resolves known body generations without inventing identities for Unbound replacements or unknown cars");
    Profile thermal;equipPart(thermal,PartSlot::Engine,20029);Profile electricDrive;equipPart(electricDrive,PartSlot::Engine,20000);
    expect(!equipPart(thermal,PartSlot::Overcharge,21054)&&!equipPart(electricDrive,PartSlot::Turbo,16018),"electric and combustion equipment cannot be mixed");
    equipPart(thermal,PartSlot::Clutch,22013);equipPart(thermal,PartSlot::Brakes,22012);auto chassisParts=buildVehicle(thermal);
    expect(chassisParts.vehicle.shiftSeconds==.04&&chassisParts.vehicle.brakeDeceleration==17,"clutch and brake categories alter real shift timing and deceleration");
    for(const auto& u:NfsUpgrades)if(u.kind==15){Profile p;equipPart(p,PartSlot::Gearbox,u.id);auto b=buildVehicle(p);CarState c;for(int tick=0;tick<600;tick++)stepCar(c,b.vehicle,{true,false,true},Step,0);nfsUpgrades&=b.vehicle.gearCount==int(findPart(u.id)->stat)&&c.gear>=1&&c.gear<=b.vehicle.gearCount&&c.speed>0;}
    expect(nfsUpgrades,"all workbook one- through eight-speed gearboxes and the ten-speed Contraband box drive with valid ratios");
    {
        bool definitions=true,universal=true;std::set<std::string> identities;std::array<int,8> categoryCounts{};
        for(size_t i=0;i<std::size(VehicleCatalog);i++){
            auto p=factoryVehicle(int(i));const auto& entry=vehicleDefinition(p);auto built=buildVehicle(p);categoryCounts[entry.category]++;
            definitions&=bodyChoiceIndex(p)==int(i)&&identities.insert(vehicleKey(p)).second&&p.parts[0]==entry.factoryEngineId;
            double hp=entry.nfsReference?findPart(entry.factoryEngineId)->stat:entry.stock.hp;
            definitions&=std::abs(built.boostedHp-hp)<.02&&built.vehicle.mass>0&&std::isfinite(built.vehicle.redlineRpm);
            for(const auto& engine:NfsEngines){Profile swap=p;universal&=equipPart(swap,PartSlot::Engine,engine.id)&&swap.parts[0]==engine.id;}
        }
        expect(definitions&&identities.size()==std::size(VehicleCatalog)&&std::all_of(categoryCounts.begin(),categoryCounts.end(),[](int n){return n>0;}),"all catalog vehicles have unique stable identities, categories and factory engines");
        expect(universal,"all 145 NFS engines can be fitted to all catalog vehicles without donor restrictions");
        Profile old;old.car=121;old.contentSource=1;old.audioSource=1;old.savedName="Original M5";
        expect(initializeVehicleFactory(old)&&old.parts[0]==nfsFactoryEngine(121,1)&&old.parts[0]>0&&old.savedName=="Original M5","untouched legacy Original BMW receives its declared engine without changing its name");
        Profile porsche,golf;porsche.car=golf.car=63;porsche.contentSource=0;golf.contentSource=1;
        expect(effectiveDrive(porsche)==DriveLayout::Rear&&effectiveDrive(golf)==DriveLayout::Front&&vehicleMechanics(porsche).hp==281&&vehicleDefinition(porsche).provisionalPhysics,"the Unbound 911 has explicit provisional F6/rear-drive mechanics separate from the Original Golf");
        Profile alternate;alternate.car=121;alternate.contentSource=0;initializeVehicleFactory(alternate);
        expect(vehicleDefinition(alternate).category==7&&vehicleForStockEngine(alternate.parts[0]),"unidentified Unbound hypercar keeps its recovered engine instead of the Original BMW engine");
        Profile modified;modified.car=121;modified.parts[0]=1504;modified.rim=10100;modified.gearCount=10;modified.springStiffness=2;auto original=modified;
        initializeVehicleFactory(modified);
        expect(modified.parts==original.parts&&modified.rim==original.rim&&modified.gearCount==original.gearCount&&modified.springStiffness==original.springStiffness&&modified.factoryEngineId==-1,"legacy customized engine, wheels, transmission and suspension remain untouched");
        auto removed=factoryVehicle(0);equipPart(removed,PartSlot::Engine,0);initializeVehicleFactory(removed);
        expect(removed.parts[0]==0,"an intentional engine removal is not undone by factory migration");
        auto garage=root/"per-vehicle";std::string error;auto a=factoryVehicle(0);auto b=factoryVehicle(1);equipPart(a,PartSlot::Engine,1501);equipPart(a,PartSlot::Turbo,16013);a.rim=10100;a.savedName="Civic AMG";
        expect(storeVehicleProfile(garage,a,error)&&storeVehicleProfile(garage,b,error),"different models store independent complete configurations");
        Profile restoredA,restoredB;expect(loadVehicleProfile(garage,0,restoredA,error)&&loadVehicleProfile(garage,1,restoredB,error)&&restoredA.parts==a.parts&&restoredA.rim==a.rim&&restoredB.parts==b.parts,"switching back restores the previous model without transferring its engine or rims");
        equipPart(a,PartSlot::Engine,1504);expect(storeVehicleProfile(garage,a,error),"updated per-vehicle preparation saves atomically");auto backup=vehicleGarageFile(garage,a);backup+=".bak";
        storeVehicleProfile(garage,a,error);expect(loadProfile(backup,191,54).parts[0]==1501,"unchanged autosaves preserve the previous preparation backup");
        auto file=vehicleGarageFile(garage,b);std::ofstream(file)<<"vehicle_id=wrong\ncar=0\n";
        expect(!loadVehicleProfile(garage,1,restoredB,error),"a mismatched vehicle identity cannot silently load or overwrite another model");
        auto customFile=root/"vehicle-metadata.ini";saveProfile(customFile,a,error);auto metadata=loadProfile(customFile,191,54);
        expect(metadata.factoryInitialized&&metadata.factoryEngineId==a.factoryEngineId&&vehicleKey(metadata)==vehicleKey(a),"factory migration metadata and stable vehicle identity persist across restart");
    }
    {
        auto inventoryFile=root/"owned/garage-inventory.ini";std::string error;VehicleInventory owned;
        bool additions=true;for(int id=0;id<8;id++)additions&=owned.add(id,error);
        expect(additions&&owned.cars.size()==8,"eight showroom acquisitions fill the garage");
        auto full=owned.cars;expect(!owned.add(8,error)&&owned.cars==full,"a ninth acquisition is rejected without changing the garage");
        expect(!owned.add(0,error)&&owned.cars==full,"a duplicate vehicle cannot occupy another slot");
        expect(!owned.add(-1,error)&&!owned.add(int(std::size(VehicleCatalog)),error)&&owned.cars==full,"invalid showroom identities are rejected");
        expect(storeVehicleInventory(inventoryFile,owned,error),"owned garage persists atomically");
        VehicleInventory restored;expect(loadVehicleInventory(inventoryFile,restored,error)&&restored.cars==owned.cars,"all eight garage slots survive a restart");
        expect(owned.remove(3)&&!owned.owns(3)&&owned.add(8,error)&&owned.cars.size()==8,"removing any vehicle frees exactly one place for another model");
        expect(!owned.remove(99)&&owned.cars.size()==8,"removing a vehicle not owned leaves the garage unchanged");
        for(int id:full)owned.remove(id);
        owned.remove(8);
        expect(owned.cars.empty()&&storeVehicleInventory(inventoryFile,owned,error)&&loadVehicleInventory(inventoryFile,restored,error)&&restored.cars.empty(),"a deliberately empty garage stays empty after reload");
        auto backup=inventoryFile;backup+=".bak";expect(loadVehicleInventory(backup,restored,error)&&restored.cars==full,"inventory changes keep a recoverable previous garage");
        std::ofstream(inventoryFile)<<"version=1\nvehicle=pcr-shared-000\nvehicle=pcr-shared-000\n";
        auto before=restored.cars;expect(!loadVehicleInventory(inventoryFile,restored,error)&&restored.cars==before,"corrupt or duplicate inventory does not silently reset or partially load the garage");
        std::ofstream(inventoryFile)<<"version=2\n";expect(!loadVehicleInventory(inventoryFile,restored,error),"unsupported inventory versions are preserved and rejected");
        auto legacy=root/"legacy-ownership";for(int id=0;id<12;id++)storeVehicleProfile(legacy,factoryVehicle(id),error);
        auto current=factoryVehicle(11);equipPart(current,PartSlot::Engine,1504);storeVehicleProfile(legacy,current,error);
        auto migrated=migrateVehicleInventory(legacy,current);
        expect(migrated.cars.size()==8&&migrated.cars.front()==11,"legacy migration prioritizes the active vehicle and imports no more than eight");
        int files=0;for(const auto& entry:std::filesystem::directory_iterator(legacy))if(entry.path().extension()==".ini")++files;
        Profile archived;expect(files==12&&loadVehicleProfile(legacy,11,archived,error)&&archived.parts[0]==1504,"legacy migration preserves every preparation including the ones beyond eight slots");
        auto invalid=migrated;invalid.cars.push_back(99);expect(!storeVehicleInventory(root/"invalid.ini",invalid,error),"oversized inventories cannot be written by alternate loading paths");
    }
    {
        auto& home=ridesEntries(RidesMenu::Home);auto& style=ridesEntries(RidesMenu::Style);auto& body=ridesEntries(RidesMenu::Body);
        expect(home.size()==4&&home[0].action==RidesAction::Menu&&home[0].target==int(RidesMenu::Style)&&home[1].target==int(RidesMenu::Performance),"customization home starts with Style and Performance before catalogue leaves");
        expect(home[2].action==RidesAction::Showroom&&home[3].action==RidesAction::Garage,"buy/sell and all rides connect to showroom and owned inventory");
        expect(style.size()==5&&style[0].target==int(RidesMenu::Body)&&style[4].action==RidesAction::Audio,"Style exposes body, paint, driving effects, vanity and sound");
        expect(body.size()==3&&body[0].action==RidesAction::Cosmetic&&body[0].target==4&&body[1].target==int(RidesMenu::BodyParts)&&body[2].action==RidesAction::Stance,"body navigation resolves kits, separate panels and real stance tuning");
        std::set<int> cosmeticSlots;bool valid=true;
        for(int node=0;node<=int(RidesMenu::Parts);node++)for(const auto& entry:ridesEntries(RidesMenu(node))){
            valid&=entry.label[0]&&entry.description[0];
            if(entry.action==RidesAction::Menu)valid&=entry.target>node&&entry.target<=int(RidesMenu::Parts);
            if(entry.action==RidesAction::Cosmetic){valid&=entry.target>=0&&entry.target<16;cosmeticSlots.insert(entry.target);}
            if(entry.action==RidesAction::Part)valid&=entry.target>=0&&entry.target<=8&&entry.slot>=-1&&entry.slot<20;
        }
        expect(valid,"all navigation entries have descriptions and valid non-cyclic destinations");
        expect(cosmeticSlots.size()==16,"all sixteen existing appearance slots remain reachable through the menu hierarchy");
        expect(ridesEntries(RidesMenu::Performance).size()==5&&ridesEntries(RidesMenu::Parts).size()==8,"performance navigation retains engine, parts, suspension, transmission and dyno access");
    }
    bool blendValid=true,continuousBlend=true,overrideBlend=true;int mixCases=0;
    for(const auto& pack:SimulatedPacks){
        for(double rpm:{500.0,1000.0,1999.9,2500.0,4000.0,4500.0,6000.0,8200.0,14000.0,17300.0})for(double load:{0.0,.1,.3,.5,.8,1.0}){
            double sum=0,withoutOn=0,withoutOff=0;
            for(std::size_t i=0;i<pack.count;i++){
                auto m=simulatedClipMix(pack,i,rpm,load);sum+=m.gain;
                blendValid&=std::isfinite(m.gain)&&m.gain>=0&&m.gain<=1&&m.pitch>=.5&&m.pitch<=1.75;
                auto on=simulatedClipMix(pack,i,rpm,load,false,true),off=simulatedClipMix(pack,i,rpm,load,true,false);
                withoutOn+=on.gain;withoutOff+=off.gain;
                overrideBlend&=(pack.clips[i].load==0||on.gain==0)&&(pack.clips[i].load!=0||off.gain==0);
                continuousBlend&=std::abs(m.gain-simulatedClipMix(pack,i,rpm+.001,load).gain)<.00001;
            }
            blendValid&=std::abs(sum-1)<1e-9;overrideBlend&=std::abs(withoutOn+withoutOff-1)<1e-9;++mixCases;
        }
    }
    expect(blendValid&&mixCases==int(std::size(SimulatedPacks))*60,"all simulated engine bindings preserve unity gain across RPM/load anchors and bounded pitches");
    expect(continuousBlend&&overrideBlend,"simulated blend is continuous at RPM anchors and manual on/off overrides mute only the corresponding layers");
    expect(simulatedPack(1008)&&simulatedPack(1501)&&simulatedPack(1502)&&simulatedPack(1503)&&simulatedPack(1504)&&simulatedPack(1505)&&!simulatedPack(1002)&&!simulatedPack(1515),"only the six validated engines use a simulated bank; source engines and W16 retain their original fallback");
    bool turboValid=true;int turboCases=0;std::ofstream turboTrace(root/"pc-turbos.csv");
    turboTrace<<"id,engine_id,psi,flow_hp,actual_hp,boost_2500,boost_4500,boost_7000\n";
    for(const auto& t:PcTurbos)for(int id:{1003,1008,1504,1515}){
        Profile p;equipPart(p,PartSlot::Engine,id);double baseline=buildVehicle(p).boostedHp;
        equipPart(p,PartSlot::Turbo,t.id);equipPart(p,PartSlot::Intercooler,7013);auto b=buildVehicle(p);
        turboValid&=b.vehicle.turboCount==t.count&&b.vehicle.turboFlowHp==t.capacityHp&&b.boostedHp<=std::max(baseline,t.capacityHp)+.01&&b.boostedHp>=baseline-.01;
        turboValid&=targetBoost(b.vehicle,0)==0&&targetBoost(b.vehicle,20000)<=t.psi&&targetBoost(b.vehicle,20000)>.99*t.psi;
        std::string err;saveProfile(root/"turbo-save.ini",p,err);turboValid&=loadProfile(root/"turbo-save.ini",191,54).parts[2]==t.id;
        turboTrace<<t.id<<','<<id<<','<<t.psi<<','<<t.capacityHp<<','<<b.boostedHp<<','<<targetBoost(b.vehicle,2500)<<','<<targetBoost(b.vehicle,4500)<<','<<targetBoost(b.vehicle,7000)<<'\n';++turboCases;
    }
    expect(turboValid&&turboCases==72,"18 turbo assemblies match four engine families, preserve saves and stay within their airflow and pressure envelope");
    Profile parallel;equipPart(parallel,PartSlot::Turbo,16010);auto pv=buildVehicle(parallel).vehicle;
    expect(targetBoost(pv,9000)==48&&pv.turboCount==2,"parallel twin turbos share one manifold pressure instead of doubling boost");
    Profile quad;equipPart(quad,PartSlot::Turbo,16013);auto qv=buildVehicle(quad).vehicle;
    expect(targetBoost(qv,3000)>0&&targetBoost(qv,3700)<64*.56&&targetBoost(qv,20000)==64,"quad sequential assembly progressively brings its second pair online");
    Profile electric;equipPart(electric,PartSlot::Turbo,16004);auto ev=buildVehicle(electric).vehicle;
    expect(targetBoost(ev,2500)>targetBoost(pv,2500)&&ev.turboRiseSeconds<pv.turboRiseSeconds,"electrically assisted turbo responds at lower RPM with a faster pressure rise");
    Profile smallTurbo,bigTurbo;equipPart(smallTurbo,PartSlot::Engine,1003);equipPart(bigTurbo,PartSlot::Engine,1515);
    equipPart(smallTurbo,PartSlot::Turbo,16010);equipPart(bigTurbo,PartSlot::Turbo,16010);
    auto smallTurboVehicle=buildVehicle(smallTurbo).vehicle,bigTurboVehicle=buildVehicle(bigTurbo).vehicle;
    expect(bigTurboVehicle.turboFullBoostRpm<smallTurboVehicle.turboFullBoostRpm&&bigTurboVehicle.turboRiseSeconds<smallTurboVehicle.turboRiseSeconds,"larger displacement supplies earlier and faster turbo response for the same assembly");
    std::ofstream spoolTrace(root/"turbo-response.csv");spoolTrace<<"turbo_id,time_s,rpm,boost_psi,target_psi\n";double slowFraction=0,fastFraction=0;
    for(int id:{16007,16008}){
        Profile p;equipPart(p,PartSlot::Engine,1002);equipPart(p,PartSlot::Turbo,id);auto vehicle=buildVehicle(p).vehicle;
        vehicle.redlineRpm=12000;vehicle.mass=1000000;vehicle.dragArea=0;vehicle.rollingResistance=0;
        CarState car;car.gear=4;double speed=9000*2*3.141592653589793*vehicle.wheelRadius/(60*vehicle.ratios[3]*vehicle.finalDrive);
        for(int tick=0;tick<120;tick++){car.speed=speed;stepCar(car,vehicle,{true,false,false},Step,0);
            spoolTrace<<id<<','<<car.elapsed<<','<<car.rpm<<','<<car.boostPsi<<','<<targetBoost(vehicle,car.rpm)<<'\n';
            if(tick==23){if(id==16007)slowFraction=car.boostPsi/vehicle.boostPsi;else fastFraction=car.boostPsi/vehicle.boostPsi;}
        }
    }
    expect(fastFraction>slowFraction+.4&&fastFraction<=1,"actual time integration gives electric assistance a faster boost rise than a large single turbo");
    equipPart(electric,PartSlot::Supercharger,3020);
    expect(electric.parts[2]==0&&buildVehicle(electric).vehicle.turboFlowHp==0,"fitting a supercharger removes the whole turbo assembly and its airflow parameters");
    {Profile p;equipPart(p,PartSlot::Turbo,16013);auto v=buildVehicle(p).vehicle;
        expect(garageInductionAudio(v,v.idleRpm,0)>0&&garageInductionAudio(v,v.redlineRpm,1)>garageInductionAudio(v,v.idleRpm,0),"garage turbo audition is audible at idle and grows with RPM and throttle");
        expect(garageInductionAudio(v,0,1)==0&&garageInductionAudio(Vehicle{},8000,1)==0,"stopped and atmospheric garage engines have no induction sound");
        GarageEngine g;g.toggle(v);for(int tick=0;tick<240;tick++)g.update(v,true,Step);
        expect(g.state.boostPsi==0&&g.state.speed==0&&g.state.nitroRemaining==10,"garage induction audition never adds physical boost, motion or NOS consumption");
    }
    {Settings levels;levels.volumes={.73,.24,.51,.62,.35,.81,.47};std::string error;
        expect(saveSettings(root/"volumes.ini",levels,error)&&loadSettings(root/"volumes.ini")==levels,"all seven independent audio volumes persist without changing display or driving settings");
        Settings bad;bad.volumes={-1,2,std::numeric_limits<double>::quiet_NaN(),.5,.25,0,2};auto clean=validate(bad);
        expect(clean.volumes.master==0&&clean.volumes.engine==1&&clean.volumes.turbo==1&&clean.volumes.effects==.5&&clean.volumes.ambience==.25&&clean.volumes.interface==0&&clean.volumes.music==1,"audio levels clamp to zero through one and reject nonfinite values");
        std::ofstream(root/"legacy-volumes.ini")<<"width=960\nheight=540\nsound=1\n";
        expect(loadSettings(root/"legacy-volumes.ini").volumes==AudioVolumes{},"older settings files keep the previous full-volume playback by default");
    }
    Profile swappedSound;equipPart(swappedSound,PartSlot::Engine,1007);swappedSound.soundOn=4;
    auto overrideSound=engineSamples(swappedSound);
    expect(overrideSound.on==47&&overrideSound.off==23,"manual acceleration override preserves the equipped engine's recovered deceleration sound");
    {std::ofstream out(root/"engine-audio-assignments.json");out<<"{\n  \"equipped_engine_bank_cases\": "<<engineAudioCases<<",\n  \"source_sample_selection_verified\": "<<(replacementAudio?"true":"false")<<",\n  \"stock_selection_recovered\": false\n}\n";}
    expect(saveProfile(root/"sound.ini",soundProfile,customError),"original audio preferences save");
    auto savedSound=loadProfile(root/"sound.ini",191,54);
    expect(savedSound.soundOn==5&&savedSound.soundOff==4&&savedSound.bov==3,"engine and valve audio preferences persist independently");
    DriverInput burnInput{true,true,true,true};
    for(auto layout:{DriveLayout::Front,DriveLayout::Rear,DriveLayout::All}){
        Vehicle car=v;car.drive=layout;car.nitroHp=250;CarState state;
        for(int tick=0;tick<240;tick++)stepCar(state,car,burnInput,Step,0);
        expect(state.burningOut&&state.gear==1&&state.speed==0&&state.position==0&&state.rpm>car.redlineRpm*.85&&state.rpm<car.redlineRpm,"first-gear brake and throttle hold the car while its engine revs for a burnout");
        expect((layout==DriveLayout::Rear?state.frontRollDistance==0:state.frontRollDistance>10)&&(layout==DriveLayout::Front?state.rearRollDistance==0:state.rearRollDistance>10),"burnout rotates only the driven axle independently of stationary ground travel");
        expect(!state.nitroActive&&state.nitroRemaining==10&&state.powerHp>0&&state.wheelSlip>.5,"burnout drives spinning wheels but blocks NOS consumption");
        stepCar(state,car,{true,false,true},Step,0);
        expect(!state.burningOut&&state.speed>0,"releasing the service brake ends the burnout and launches normally");
    }
    bool handFreeRev=true,handSafeRelease=true,handThrottleDrop=true;
    for(auto layout:{DriveLayout::Front,DriveLayout::Rear,DriveLayout::All}){
        Vehicle car=v;car.drive=layout;car.nitroHp=250;CarState parked;parked.gear=3;
        for(int tick=0;tick<240;tick++)stepCar(parked,car,{true,false,true,true,false,true},Step,0);
        handFreeRev&=parked.handbraking&&!parked.neutral&&parked.rpm>car.redlineRpm*.9&&parked.speed==0&&parked.position==0&&parked.rearRollDistance==0&&parked.frontRollDistance==0&&parked.gear==3&&!parked.nitroActive&&parked.nitroRemaining==10&&parked.powerHp==0;
        handFreeRev&=!shift(parked,1,car);
        stepCar(parked,car,{true,false,true},Step,0);
        handSafeRelease&=!parked.handbraking&&parked.shiftLock>0&&parked.gear==3;
        for(int tick=0;tick<120;tick++)stepCar(parked,car,{true,false,true},Step,0);
        handSafeRelease&=parked.speed>0;
        for(int tick=0;tick<240;tick++)stepCar(parked,car,{false,false,true,false,false,true},Step,0);
        handThrottleDrop&=std::abs(parked.rpm-car.idleRpm)<1;
    }
    expect(handFreeRev,"handbrake throttle revs freely in all drive layouts without wheel torque, shifts or NOS");
    expect(handSafeRelease,"handbrake release safely reconnects the retained gear before normal acceleration");
    expect(handThrottleDrop,"releasing throttle with handbrake held returns the free engine to idle");
    CarState fastHand;fastHand.speed=80;fastHand.gear=1;stepCar(fastHand,v,{true,false,false,false,false,true},Step,0);
    double handFastSpeed=fastHand.speed;stepCar(fastHand,v,{true,false,false},Step,0);
    expect(fastHand.gear>1&&fastHand.shiftLock>0&&fastHand.speed<=handFastSpeed,"handbrake clutch reconnect selects a safe gear at high road speed");
    {std::ofstream out(root/"handbrake-rev.json");out<<"{\n  \"drivetrains_checked\": 3,\n  \"free_rev_without_drive\": "<<(handFreeRev?"true":"false")<<",\n  \"safe_reengagement\": "<<(handSafeRelease?"true":"false")<<"\n}\n";}
    CarState wrongGear;wrongGear.gear=2;stepCar(wrongGear,v,{true,true,false},Step,0);
    expect(!wrongGear.burningOut&&wrongGear.powerHp==0,"manual second gear cannot enter burnout mode");
    CarState fastBurn;fastBurn.speed=20;stepCar(fastBurn,v,burnInput,Step,0);
    expect(!fastBurn.burningOut&&fastBurn.speed<20,"brake plus throttle at road speed continues braking");
    CarState lockedBurn;stepCar(lockedBurn,v,{true,true,true,true,false,true},Step,0);
    expect(!lockedBurn.burningOut&&lockedBurn.powerHp==0&&lockedBurn.rearRollDistance==0,"handbrake has priority over the service-brake burnout");
    Vehicle nosNeutral=v;nosNeutral.nitroHp=250;
    CarState freeRev;freeRev.gear=4;
    for(int tick=0;tick<240;tick++)stepCar(freeRev,nosNeutral,{true,false,true,true,false,false,true},Step,0);
    expect(freeRev.neutral&&freeRev.gear==4&&freeRev.rpm>v.redlineRpm*.9&&freeRev.rpm<v.redlineRpm&&freeRev.position==0&&freeRev.speed==0,"held neutral revs freely without acceleration or automatic shifting");
    expect(!shift(freeRev,-1,v)&&freeRev.powerHp==0&&!freeRev.nitroActive&&freeRev.nitroRemaining==10&&freeRev.wheelSlip==0,"neutral disconnects wheel torque, shift commands and NOS");
    stepCar(freeRev,v,{true,false,false},Step,0);
    expect(!freeRev.neutral&&freeRev.gear==4&&freeRev.shiftLock>0,"releasing neutral reconnects the retained gear through the shift delay");
    CarState coast,engaged;coast.speed=engaged.speed=20;coast.gear=engaged.gear=3;
    for(int tick=0;tick<120;tick++){stepCar(coast,v,{false,false,false,false,false,false,true},Step,0);stepCar(engaged,v,{false,false,false},Step,0);}
    expect(coast.speed>engaged.speed&&coast.speed<20,"neutral retains momentum and rolling resistance without engine braking");
    for(int tick=0;tick<600;tick++)stepCar(coast,v,{true,true,true,true,false,false,true},Step,0);
    expect(coast.speed==0&&!coast.burningOut&&coast.neutral,"service braking remains effective in neutral and cannot trigger burnout");
    CarState reconnect;reconnect.gear=1;reconnect.speed=30;
    stepCar(reconnect,v,{false,false,false,false,false,false,true},Step,0);stepCar(reconnect,v,{true,false,false},Step,0);
    expect(!reconnect.neutral&&reconnect.gear>1&&reconnect.rpm<=v.redlineRpm,"neutral release selects a safe ratio when the retained gear would over-rev");
    for(int frame=0;frame<40;frame++){
        auto tint=tireSmokeTint(frame);bool special=frame>=9&&frame<=16;
        expect((tint!=SmokeTint{255,255,255})==special,"only the eight Burn Slicks colours tint tyre smoke");
    }
    {std::ofstream out(root/"burnout-neutral.json");out<<"{\n  \"burnout_layouts_checked\": 3,\n  \"smoke_tyre_frames_checked\": 40,\n  \"special_smoke_colours\": 8,\n  \"neutral_behaviour_checked\": true\n}\n";}
    DrivingEffects visuals;CarState visibleCar;visibleCar.wheelSlip=.4;
    EffectSources points;points.rearWheel=400;points.frontWheel=520;points.wheelY=450;points.outlets[0]={350,440,-1,0};
    visuals.update(visibleCar,v,{true,false,true},points,0,Step,false);
    expect(!visuals.particles.empty()&&visuals.particles.front().kind==EffectKind::Smoke,"wheel slip emits original smoke particles");
    for(auto layout:{DriveLayout::Front,DriveLayout::Rear,DriveLayout::All}){
        DrivingEffects smoke;Vehicle car=v;car.drive=layout;CarState state;state.burningOut=true;state.wheelSlip=1;
        EffectSources sources=points;sources.tireFrame=13;smoke.update(state,car,burnInput,sources,0,Step,false);
        expect(smoke.particles.size()==(layout==DriveLayout::All?2u:1u)&&std::all_of(smoke.particles.begin(),smoke.particles.end(),[&](const Particle& p){return p.tint==SmokeTint{255,75,75}&&(layout==DriveLayout::All||p.x==(layout==DriveLayout::Front?points.frontWheel:points.rearWheel));}),"coloured burnout smoke originates at the driven tyre contact patch");
        auto tint=smoke.particles.front().tint;sources.tireFrame=0;state.wheelSlip=0;smoke.update(state,car,{false,false,true},sources,0,.1,false);
        expect(smoke.particles.front().tint==tint,"existing smoke keeps its emitted colour when tyre selection changes");
    }
    visibleCar.wheelSlip=0;visibleCar.nitroActive=true;
    visuals.update(visibleCar,v,{true,false,true,true},points,0,Step,false);
    expect(std::any_of(visuals.particles.begin(),visuals.particles.end(),[](const Particle& p){return p.kind==EffectKind::Nitro;}),"active NOS emits a distinct effect");
    visibleCar.nitroActive=false;visibleCar.gear=2;
    visuals.update(visibleCar,v,{true,false,true},points,1.2,Step,true);
    expect(std::any_of(visuals.particles.begin(),visuals.particles.end(),[](const Particle& p){return p.kind==EffectKind::Flame;}),"equipped exhaust emits a gear-change flame");
    expect(std::count_if(visuals.particles.begin(),visuals.particles.end(),[](const Particle& p){return p.kind==EffectKind::Spark;})==14,"collision emits a bounded spark burst");
    for(int i=0;i<240;i++)visuals.update(visibleCar,v,{false,false,true},points,0,Step,false);
    expect(visuals.particles.empty(),"expired visual effects are removed");
    DrivingEffects roadSmoke;CarState moving;moving.speed=100/3.6;moving.wheelSlip=.4;
    roadSmoke.update(moving,v,{true,false,true},points,0,Step,false);
    double smokeX=roadSmoke.particles.front().x,smokeVx=roadSmoke.particles.front().vx;
    moving.wheelSlip=0;moving.position=2;
    roadSmoke.update(moving,v,{false,false,true},points,0,.1,false);
    expect(std::abs(roadSmoke.particles.front().x-(smokeX+smokeVx*.1-96))<1e-9,"smoke moves with the actual road distance instead of a separate speed scale");
    double stoppedX=roadSmoke.particles.front().x;
    roadSmoke.update(moving,v,{false,false,true},points,0,0,false);
    expect(roadSmoke.particles.front().x==stoppedX,"paused effects do not advance");
    Profile launchProfile;equipPart(launchProfile,PartSlot::Ecu,4002);equipPart(launchProfile,PartSlot::Turbo,3026);
    auto launchBuild=buildVehicle(launchProfile);CarState staged;
    for(int i=0;i<240;i++)stepCar(staged,launchBuild.vehicle,{true,false,true,false,true},Step,0);
    expect(staged.position==0&&staged.rpm==4200&&staged.boostPsi>10&&staged.launching,"2STEP holds the clutch and builds boost at a fixed staging RPM");
    for(int i=0;i<120;i++)stepCar(staged,launchBuild.vehicle,{true,false,true,false,false},Step,0);
    expect(staged.speed>0&&!staged.launching,"releasing launch control delivers drive torque");
    Profile ultimate;ultimate.car=20;ultimate.rim=8;ultimate.drive=DriveLayout::All;ultimate.soundOn=4;
    equipBestParts(ultimate);auto full=buildVehicle(ultimate);
    expect(ultimate.parts[0]!=0&&ultimate.parts[2]==16018&&ultimate.parts[3]==0,"maximum preparation selects a complete engine and exclusive induction");
    expect(ultimate.car==20&&ultimate.rim==8&&ultimate.drive==DriveLayout::All&&ultimate.soundOn==4,"maximum preparation preserves appearance, drive and audio preferences");
    expect(full.boostedHp>4200&&full.nitroHp>4500&&full.nitroHp-full.boostedHp==250,"maximum parts combine into over 4500 rated HP with NOS");
    Profile legacyMax=ultimate;for(int i=11;i<PartSlotCount;i++)legacyMax.parts[i]=0;equipPart(legacyMax,PartSlot::Engine,1014);equipPart(legacyMax,PartSlot::Turbo,3026);auto legacyFull=buildVehicle(legacyMax);
    double expectedHp=(755+38+100+95)*((engineRedline(legacyMax)+2300)/engineRedline(legacyMax))*(1+35/14.7);
    expect(std::abs(legacyFull.boostedHp-expectedHp)/expectedHp<.0001,"full preparation matches an independently calculated compound power budget");
    Profile coolerOnly;equipPart(coolerOnly,PartSlot::Intercooler,7013);
    expect(std::abs(buildVehicle(coolerOnly).boostedHp-buildVehicle(Profile{}).boostedHp)<1e-9,"an intercooler cannot add power to an atmospheric engine");
    Profile ecuOnly;equipPart(ecuOnly,PartSlot::Engine,1014);double beforeEcu=buildVehicle(ecuOnly).boostedHp;
    equipPart(ecuOnly,PartSlot::Ecu,4008);
    expect(buildVehicle(ecuOnly).boostedHp>beforeEcu*1.28,"ECU curve extension delivers usable peak power instead of cancelling its own gain");
    Profile turboOnly;equipPart(turboOnly,PartSlot::Engine,1014);equipPart(turboOnly,PartSlot::Turbo,3026);
    double withoutCooler=buildVehicle(turboOnly).boostedHp;equipPart(turboOnly,PartSlot::Intercooler,7013);
    expect(buildVehicle(turboOnly).boostedHp>withoutCooler,"intercooling increases forced-induction power");
    double beforeIntake=buildVehicle(turboOnly).boostedHp;equipPart(turboOnly,PartSlot::Intake,6021);
    expect(buildVehicle(turboOnly).boostedHp-beforeIntake>38,"boost multiplies the intake gain instead of adding it after compression");
    bool ranking=true;int contra=0;
    for(const auto& part:PartCatalog){
        auto tier=partRarity(part);ranking&=int(tier)>=0&&int(tier)<=5;
        for(const auto& other:PartCatalog)if(part.slot==other.slot&&nfsGrade(part.id)<0&&nfsGrade(other.id)<0){
            if(partPerformance(part)<partPerformance(other))ranking&=int(tier)<=int(partRarity(other));
            if(tier==Rarity::Contraband)ranking&=partPerformance(part)>=partPerformance(other);
            if(partPerformance(part)==partPerformance(other))ranking&=tier==partRarity(other);
        }
        if(nfsGrade(part.id)>=0)ranking&=int(tier)==nfsGrade(part.id);
        if(tier==Rarity::Contraband)++contra;
    }
    expect(ranking&&contra>=PartSlotCount,"all rarity tiers follow category performance and only the strongest are contraband");
    expect(partRarity(*findPart(3026))==partRarity(*findPart(3019)),"cosmetic prices do not create a false power rarity difference");
    expect(partRarity(*findPart(1515))==Rarity::Contraband&&partRarity(*findPart(1016))==Rarity::Common,"engine classification spans common through contraband");
    bool noDowngrade=true;int replacements=0;
    for(const auto& part:PartCatalog){Profile alternate=ultimate;equipPart(alternate,part.slot,part.id);auto result=buildVehicle(alternate);
        noDowngrade&=result.nitroHp<=full.nitroHp+.01&&result.boostedHp<=full.boostedHp+.01;++replacements;}
    expect(noDowngrade&&replacements==int(std::size(PartCatalog)),"no catalog replacement beats the maximum preparation peak power");
    // Cross every engine, ECU, induction choice and intercooler (including base).
    std::vector<int> engines,ecus{0},induction{0},coolers{0};
    for(const auto& part:PartCatalog){
        if(nfsGrade(part.id)>=0)continue;
        if(part.slot==PartSlot::Engine)engines.push_back(part.id);
        if(part.slot==PartSlot::Ecu)ecus.push_back(part.id);
        if(part.slot==PartSlot::Turbo||part.slot==PartSlot::Supercharger)induction.push_back(part.id);
        if(part.slot==PartSlot::Intercooler)coolers.push_back(part.id);
    }
    int combinations=0;bool combinationsValid=true;
    for(int engine:engines)for(int ecu:ecus)for(int boost:induction)for(int cooler:coolers){
        Profile trial;equipPart(trial,PartSlot::Engine,engine);equipPart(trial,PartSlot::Ecu,ecu);
        if(boost)equipPart(trial,findPart(boost)->slot,boost);
        equipPart(trial,PartSlot::Intercooler,cooler);auto result=buildVehicle(trial);const auto& engineData=*findPart(engine);
        double target=engineData.stat*result.vehicle.redlineRpm/engineRedline(trial);
        combinationsValid&=std::isfinite(result.boostedHp)&&result.boostedHp>=engineData.stat*.9999&&result.boostedHp<=full.boostedHp+.01;
        combinationsValid&=std::abs(result.baseHp-target)/target<(pcEngine(engine)?.0005:.0001);
        combinationsValid&=std::abs(enginePowerHp(result.vehicle,result.peakRpm,targetBoost(result.vehicle,result.peakRpm))-result.boostedHp)<1e-8;
        if(!boost)combinationsValid&=std::abs(result.baseHp-result.boostedHp)<1e-8;
        ++combinations;
    }
    expect(combinationsValid&&combinations==int(engines.size()*ecus.size()*induction.size()*coolers.size()),"all engine/ECU/induction/intercooler combinations have consistent finite power");
    // Also cross all independent atmospheric-part choices on each engine.
    std::vector<int> intakes{0},pistons{0},exhausts{0};
    for(const auto& part:PartCatalog){if(nfsGrade(part.id)>=0)continue;if(part.slot==PartSlot::Intake)intakes.push_back(part.id);if(part.slot==PartSlot::Pistons)pistons.push_back(part.id);if(part.slot==PartSlot::Exhaust)exhausts.push_back(part.id);}
    bool supportsValid=true;int supports=0;
    for(int engine:engines)for(int intake:intakes)for(int piston:pistons)for(int exhaust:exhausts){
        Profile trial;equipPart(trial,PartSlot::Engine,engine);equipPart(trial,PartSlot::Intake,intake);equipPart(trial,PartSlot::Pistons,piston);equipPart(trial,PartSlot::Exhaust,exhaust);auto result=buildVehicle(trial);
        double target=findPart(engine)->stat+(intake?findPart(intake)->stat:0)+(piston?findPart(piston)->stat:0)+(exhaust?findPart(exhaust)->stat:0);
        supportsValid&=std::abs(result.baseHp-target)<.001;++supports;
    }
    expect(supportsValid&&supports==int(engines.size()*intakes.size()*pistons.size()*exhausts.size()),"all engine/intake/piston/exhaust combinations retain their full additive power budget");
    Vehicle dynoVehicle=full.vehicle;dynoVehicle.grip=10;CarState dyno;dyno.gear=6;dyno.boostPsi=dynoVehicle.boostPsi;
    dyno.speed=full.peakRpm*2*3.141592653589793*dynoVehicle.wheelRadius/(60*dynoVehicle.ratios[5]*dynoVehicle.finalDrive);
    stepCar(dyno,dynoVehicle,{true,false,false,true},Step,0);
    expect(std::abs(dyno.powerHp-full.nitroHp)<.01,"actual driving output matches the displayed full-boost and NOS power at peak RPM");
    dyno.speed=dynoVehicle.redlineRpm*2*3.141592653589793*dynoVehicle.wheelRadius/(60*dynoVehicle.ratios[5]*dynoVehicle.finalDrive)+1;
    stepCar(dyno,dynoVehicle,{true,false,false,true},Step,0);
    expect(!dyno.nitroActive&&dyno.powerHp==0,"NOS cannot bypass the engine rev limiter");
    {std::ofstream out(root/"power-combinations.json");out<<"{\n  \"induction_combinations\": "<<combinations<<",\n  \"atmospheric_combinations\": "<<supports<<",\n  \"max_without_nos_hp\": "<<full.boostedHp<<",\n  \"max_with_nos_hp\": "<<full.nitroHp<<",\n  \"original_game_equivalence_validated\": false\n}\n";}
    std::cout<<"Native maximum: "<<full.boostedHp<<" HP, "<<full.nitroHp<<" HP with NOS; "<<combinations+supports<<" combinations checked.\n";
    auto rearPipe=placeExhaust(20,7),hoodPipe=placeExhaust(20,48),sidePipe=placeExhaust(20,44),triplePipe=placeExhaust(20,50);
    expect(rearPipe.outlets[0].dx==-1&&hoodPipe.outlets[0].dy==-1,"rear and hood effects follow their real pipe directions");
    expect(sidePipe.front&&sidePipe.count==2&&triplePipe.count==3,"twin side and triple hood pipes expose all mouths");
    auto lowHood=placeExhaust(20,48,6);
    expect(lowHood.outlets[0].y-hoodPipe.outlets[0].y==6&&lowHood.y-hoodPipe.y==6,"suspension moves the pipe sprite and its emitter by the same amount");
    int placements=0;bool mountsValid=true;
    for(int body=0;body<191;body++)for(int pipe=0;pipe<51;pipe++){
        if(pipe!=0&&!std::any_of(std::begin(PartCatalog),std::end(PartCatalog),[&](const Part& part){return part.slot==PartSlot::Exhaust&&part.subimage==pipe;}))continue;
        auto placed=placeExhaust(body,pipe);const auto& sprite=art::exhausts[pipe];
        mountsValid&=placed.count>=1&&placed.count<=3;
        for(int k=0;k<placed.count;k++){const auto& o=placed.outlets[k];double localX=o.x-placed.x,localY=o.y-placed.y;
            mountsValid&=std::isfinite(o.x)&&std::isfinite(o.y)&&std::abs(o.dx*o.dx+o.dy*o.dy-1)<1e-7;
            mountsValid&=localX>=sprite.dx-1&&localX<=sprite.dx+sprite.w+1&&localY>=sprite.dy-1&&localY<=sprite.dy+sprite.h+1;
        }
        ++placements;
    }
    expect(mountsValid&&placements==9359,"all 191 bodies and 49 available pipe variants keep finite mouths on their sprites");
    DrivingEffects attachedJets;EffectSources nozzles;nozzles.outletCount=2;nozzles.outlets[0]={350,440,-1,0};nozzles.outlets[1]={355,440,0,-1};
    CarState jetCar;jetCar.speed=100;jetCar.gear=2;jetCar.nitroActive=true;
    attachedJets.update(jetCar,v,{true,false,true,true},nozzles,0,Step,true);
    expect(attachedJets.particles.size()==4,"flames and NOS emit from both visible outlets");
    jetCar.position=100;jetCar.nitroActive=false;
    for(auto& o:nozzles.outlets){o.x+=20;o.y+=96;}
    attachedJets.update(jetCar,v,{true,false,true},nozzles,0,Step,true);
    bool rootsAttached=true;
    for(const auto& particle:attachedJets.particles){auto o=nozzles.outlets[particle.outlet];rootsAttached&=particle.x==o.x&&particle.y==o.y&&particle.dx==o.dx&&particle.dy==o.dy;}
    expect(rootsAttached,"flames and NOS remain attached at high speed and during lane changes");
    bool allBoxesValid=true;
    for(int preset=0;preset<8;preset++){
        Profile box;applyGearboxPreset(box,preset);auto before=box;sanitizeTransmission(box);
        allBoxesValid&=box.gearRatios==before.gearRatios&&box.gearCount>=4&&box.gearCount<=10;
        auto vehicle=buildVehicle(box).vehicle;CarState run;
        for(int tick=0;tick<120*20;tick++)stepCar(run,vehicle,{true,false,true},Step,0);
        allBoxesValid&=run.speed>0&&std::isfinite(run.rpm)&&run.gear<=vehicle.gearCount;
    }
    expect(allBoxesValid,"all eight real-market-inspired and original presets retain their ratios and drive safely");
    bool allCounts=true;
    for(int count=4;count<=10;count++){
        Profile box;box.gearCount=count;auto vehicle=buildVehicle(box).vehicle;CarState run;
        for(int j=0;j<12;j++){run.shiftLock=0;shift(run,1,vehicle);}
        allCounts&=run.gear==count;run.shiftLock=0;allCounts&=!shift(run,1,vehicle);
    }
    expect(allCounts,"manual shifting respects every selectable gearbox size through ten gears");
    Profile ten;applyGearboxPreset(ten,7);auto tenVehicle=buildVehicle(ten).vehicle;CarState ninth;ninth.gear=9;
    ninth.speed=(tenVehicle.upshiftRpm+100)*6.283185307179586*tenVehicle.wheelRadius/(60*tenVehicle.ratios[8]*tenVehicle.finalDrive);
    stepCar(ninth,tenVehicle,{true,false,true},Step,0);
    expect(ninth.gear==10,"automatic transmission can shift from ninth into tenth");
    Profile shortBox,longBox;shortBox.finalDrive=6;longBox.finalDrive=2;
    auto shortVehicle=buildVehicle(shortBox),longVehicle=buildVehicle(longBox);CarState shortRun,longRun;
    shortRun.gear=longRun.gear=2;shortRun.speed=longRun.speed=20;
    stepCar(shortRun,shortVehicle.vehicle,{true,false,false},Step,0);stepCar(longRun,longVehicle.vehicle,{true,false,false},Step,0);
    expect(shortRun.speed>longRun.speed&&shortVehicle.boostedHp==longVehicle.boostedHp,"final drive changes wheel acceleration without inventing engine horsepower");
    expect(saveProfile(root/"gearbox.ini",ten,customError),"ten-speed gearbox preferences save");auto restoredBox=loadProfile(root/"gearbox.ini",191,54);
    expect(restoredBox.gearCount==10&&restoredBox.gearRatios==ten.gearRatios&&restoredBox.finalDrive==ten.finalDrive&&restoredBox.shiftSeconds==ten.shiftSeconds&&restoredBox.gearboxPreset==7,"all ten ratios, final drive, preset and shift timing survive restart");
    {std::ofstream out(root/"bad-box.ini");out<<"gear_count=99\ngear_2=-1\nfinal_drive=nan\nshift_seconds=-1\n";}
    auto safeBox=loadProfile(root/"bad-box.ini",191,54);
    expect(safeBox.gearCount==10&&safeBox.gearRatios==Profile{}.gearRatios&&safeBox.finalDrive==3.9&&safeBox.shiftSeconds==.15,"malformed gearbox settings cannot create unsafe ratios or more than ten gears");
    expect(loadProfile(root/"old-settings.ini",191,54).gearCount==6,"legacy profiles retain the original six-speed behaviour");
    {std::ofstream out(root/"exhaust-gearbox.json");out<<"{\n  \"body_pipe_configurations\": "<<placements<<",\n  \"gearbox_presets\": 8,\n  \"maximum_gears\": 10,\n  \"native_calibration\": true\n}\n";}
    expect(std::size(original_ui::garageIcons)==68&&std::size(original_ui::glyphs)==192&&std::size(original_ui::lifts)==3,"original category icons, pixel glyphs and lift frames are complete");
    bool uiBounds=true;for(const auto& frame:original_ui::glyphs)uiBounds&=frame.atlas>=1000&&frame.atlas<1000+original_ui::AtlasCount&&frame.x+frame.w<=2048&&frame.y+frame.h<=2048;
    expect(uiBounds,"original pixel glyphs fit the verified native UI atlases");
    CarState coastHand,parkHand,footHand;coastHand.speed=parkHand.speed=footHand.speed=100/3.6;coastHand.gear=parkHand.gear=footHand.gear=4;
    for(int i=0;i<120*2;i++){stepCar(coastHand,v,{false,false,false},Step,0);stepCar(parkHand,v,{false,false,false,false,false,true},Step,0);stepCar(footHand,v,{false,true,false},Step,0);}
    expect(coastHand.speed>parkHand.speed&&parkHand.speed>footHand.speed,"rear handbrake slows the car independently of the stronger service brake");
    expect(parkHand.handbraking&&parkHand.rearRollDistance==0&&parkHand.position>0,"handbrake locks rear-wheel rotation while the car keeps moving");
    stepCar(parkHand,v,{true,false,false},Step,0);expect(!parkHand.handbraking&&parkHand.rearRollDistance>0,"rear wheels roll again when the handbrake is released");
    CarState blockedNos;blockedNos.speed=30;blockedNos.gear=4;stepCar(blockedNos,nitroBuild.vehicle,{true,false,false,true,false,true},Step,0);
    expect(!blockedNos.nitroActive&&blockedNos.nitroRemaining==10&&blockedNos.powerHp==0,"handbrake overrides throttle and NOS without consuming its charge");
    for(int i=0;i<120*30;i++)stepCar(parkHand,v,{false,false,false,false,false,true},Step,0);
    expect(parkHand.speed==0&&std::isfinite(parkHand.position),"held handbrake stops the car without reverse motion");
    DrivingEffects lockedSmoke;CarState sliding;sliding.speed=30;Vehicle frontDrive;frontDrive.drive=DriveLayout::Front;
    lockedSmoke.update(sliding,frontDrive,{false,false,true,false,false,true},points,0,Step,false);
    expect(lockedSmoke.particles.size()==1&&lockedSmoke.particles[0].kind==EffectKind::BrakeSmoke&&lockedSmoke.particles[0].x==points.rearWheel,"handbrake smoke comes only from the rear axle, including front-wheel drive");
    auto file=root/std::filesystem::u8path("écran_車.ini");Settings s;s.mode=WindowMode::Borderless;s.width=1920;s.height=1080;s.fps=144;s.vsync=false;s.quality=Quality::Low;s.showFps=true;s.sound=false;s.traffic=false;
    std::string error;expect(saveSettings(file,s,error),"save Unicode settings path");expect(loadSettings(file)==s,"all graphics settings round trip");
    s.fps=60;s.mode=WindowMode::Fullscreen;expect(saveSettings(file,s,error),"atomic replacement of existing settings");expect(loadSettings(file)==s,"replaced graphics settings persist");
    expect(!std::filesystem::exists(file.u8string()+".tmp"),"successful save leaves no temporary file");
    {std::ofstream out(file);out<<"width=-1\nheight=99999999\nfps=not-a-number\nmode=execute-this\nquality=99\n";}
    auto invalid=loadSettings(file);expect(invalid.width==1280&&invalid.height==720&&invalid.fps==120&&invalid.mode==WindowMode::Windowed&&invalid.quality==Quality::High,"invalid settings safely fall back");
    Profile p;p.factoryDrive=false;p.car=190;p.rim=42;p.automatic=false;p.drive=DriveLayout::All;p.bestTime=12.345678;
    expect(saveProfile(root/"profile.ini",p,error),"profile saved");auto loaded=loadProfile(root/"profile.ini",191,54);
    expect(loaded.car==190&&loaded.rim==42&&!loaded.automatic&&loaded.drive==DriveLayout::All&&std::abs(loaded.bestTime-p.bestTime)<1e-9,"garage and driving preferences persist");
    {std::ofstream out(root/"profile.ini");out<<"car=9999\nrim=-2\nbest_time=nan\ndrive=99\n";}
    auto bad=loadProfile(root/"profile.ini",191,54);expect(bad.car==190&&bad.rim==8&&bad.bestTime==0&&bad.drive==DriveLayout::Rear,"malformed profile is bounded");
    bool validRimsPreserved=true,invalidRimsRepaired=true;
    for(int rim=0;rim<54;rim++){
        {std::ofstream out(root/"rim-migration.ini");out<<"rim="<<rim<<"\npart_engine=1002\n";}
        auto migrated=loadProfile(root/"rim-migration.ini",191,54);
        if(isRimFrame(rim))validRimsPreserved&=migrated.rim==rim;
        else invalidRimsRepaired&=migrated.rim==8&&migrated.parts[0]==1002;
    }
    expect(validRimsPreserved,"all 23 real source rims preserve their IDs across profile loading");
    expect(invalidRimsRepaired,"all 31 tyre/effect legacy rim selections migrate without losing equipment");
    expect(std::size(RimCatalog)==567&&std::size(CosmeticCatalog)==735&&std::size(PartCatalog)==524,"merged shop includes 1520 equipment choices including distinct source seat variants");
    bool namedRimsPersist=true,rimImagesValid=true;
    for(const auto& rim:RimCatalog){
        Profile p;p.rim=rim.id;saveProfile(root/"named-rim.ini",p,error);auto loaded=loadProfile(root/"named-rim.ini",191,54);namedRimsPersist&=loaded.rim==canonicalRimId(rim.id);
        for(auto frames:{content_art::unboundRims,content_art::originalRims}){auto f=frames[rim.image];rimImagesValid&=f.atlas>=2000&&f.atlas<2000+content_art::AtlasCount&&f.canvasW==62&&f.canvasH==62&&f.w>0&&f.h>0&&f.x+f.w<=2048&&f.y+f.h<=2048;}
    }
    expect(namedRimsPersist,"all 521 source-named composite rims survive profile reload without legacy clamping");
    expect(rimImagesValid,"both source banks provide valid nonempty composed frames for all 521 rims");
    Profile outfit;outfit.contentSource=1;for(const auto& c:CosmeticCatalog)outfit.cosmetics[c.slot]=c.id;saveProfile(root/"outfit.ini",outfit,error);auto outfitLoaded=loadProfile(root/"outfit.ini",191,54);
    for(auto& id:outfit.cosmetics){id=canonicalCosmeticId(id);}
    expect(outfitLoaded.cosmetics==outfit.cosmetics&&outfitLoaded.contentSource==1,"all sixteen appearance slots and original source selection persist");
    {std::ofstream out(root/"bad-outfit.ini");out<<"content_source=7\ncosmetic_0=102001\ncosmetic_1=999999\n";}
    auto badOutfit=loadProfile(root/"bad-outfit.ini",191,54);expect(badOutfit.contentSource==2&&badOutfit.cosmetics[0]==0&&badOutfit.cosmetics[1]==0,"malformed appearance and wrong-slot IDs cannot corrupt the outfit");
    expect(findPart(3027)&&findPart(3028)&&findPart(3027)->stat==35&&findPart(3028)->stat==35,"original-only Diamond and Ruby turbos join the Unbound equipment catalog");
    {
        bool balanced=true;int variants=0;
        for(const auto& part:PartCatalog)if(part.imageSource==2){
            auto original=findPart(part.id-60000);balanced&=original&&part.slot==original->slot&&part.stat==original->stat&&part.weight==original->weight&&partRarity(part)==partRarity(*original);++variants;
        }
        expect(balanced&&variants==28,"Underground mechanical variants preserve the source power, mass and rarity balance");
        Profile underground;underground.car=7;underground.contentSource=2;underground.audioSource=2;initializeVehicleFactory(underground);
        auto key=vehicleKey(underground);saveProfile(root/"underground.ini",underground,error);auto restored=loadProfile(root/"underground.ini",191,54);
        expect(key=="pcr-underground-007"&&vehicleKey(restored)==key&&restored.audioSource==2,"Underground vehicle identity and audio bank persist without resolving to an older bank");
        bool sounds=std::size(UndergroundSounds)==94;for(int id=0;id<94;id++)sounds&=std::string(sourceSound(id,2).name)==OriginalSounds[id].name;
        expect(sounds&&std::string(sourceSound(20,2).file).find("audio-underground/")==0,"all Underground sound IDs preserve the shared compiled dispatch and select their own samples");
        expect(std::string(vehicleIdentity(85,false).name)=="Lamborghini Huracán"&&std::string(vehicleIdentity(187,false).name)=="Lamborghini Gallardo","confirmed Unbound Lamborghini identities survive the Underground import");
    }
    {
        bool valid=true;int partAliases=0,cosmeticAliases=0,rimAliases=0,vehicleAliases=0,showroom=0;
        for(const auto& p:PartCatalog){auto id=canonicalPartId(p.id);if(id!=p.id){auto target=findPart(id);valid&=target&&target->slot==p.slot&&target->stat==p.stat&&target->weight==p.weight&&canonicalPartId(id)==id;++partAliases;}}
        for(const auto& c:CosmeticCatalog){auto id=canonicalCosmeticId(c.id);if(id!=c.id){auto target=findCosmetic(id);valid&=target&&target->slot==c.slot&&target->weight==c.weight&&canonicalCosmeticId(id)==id;++cosmeticAliases;}}
        for(const auto& r:RimCatalog){auto id=canonicalRimId(r.id);if(id!=r.id){valid&=findRim(id)&&canonicalRimId(id)==id;++rimAliases;}}
        for(size_t i=0;i<std::size(VehicleCatalog);i++){int id=canonicalVehicleIndex(int(i));valid&=id>=0&&id<int(std::size(VehicleCatalog))&&canonicalVehicleIndex(id)==id;vehicleAliases+=id!=int(i);showroom+=reviewedShowroomVehicle(int(i));}
        expect(valid&&partAliases==8&&cosmeticAliases==118&&rimAliases==37&&vehicleAliases==142&&showroom==287,"reviewed aliases retain valid stable IDs and hide only duplicate shop entries");
        bool samePhysics=true;
        for(size_t i=0;i<std::size(VehicleCatalog);i++){int target=canonicalVehicleIndex(int(i));if(target==int(i))continue;auto a=buildVehicle(factoryVehicle(int(i))),b=buildVehicle(factoryVehicle(target));samePhysics&=a.boostedHp==b.boostedHp&&a.vehicle.mass==b.vehicle.mass&&a.vehicle.redlineRpm==b.vehicle.redlineRpm&&a.vehicle.drive==b.vehicle.drive&&a.vehicle.engineInertia==b.vehicle.engineInertia;}
        expect(samePhysics,"hidden duplicate vehicles retain the same factory power, mass, revs, drive and inertia as their canonical model");
        expect(std::string(catalogOriginLabel(19))=="ORIGINAL"&&std::string(catalogOriginLabel(8))=="UNBOUND"&&std::string(catalogOriginLabel(16))=="UNDERGROUND"&&std::string(catalogOriginLabel(4))=="CRÉATION PC","each displayed item has exactly one primary provenance");
        Profile legacy;legacy.rim=200109;legacy.cosmetics[0]=600001;legacy.parts[9]=69026;saveProfile(root/"reviewed-legacy.ini",legacy,error);auto loaded=loadProfile(root/"reviewed-legacy.ini",191,54);
        expect(loaded.rim==canonicalRimId(legacy.rim)&&loaded.cosmetics[0]==100001&&loaded.parts[9]==canonicalPartId(legacy.parts[9]),"saved duplicate equipment resolves to equivalent canonical parts on load");
    }
    {
        std::array<int,7> styles{};bool inherited=true;
        for(const auto& rim:RimCatalog){auto style=rimStyleOf(rim.id);inherited&=int(style)>=1&&int(style)<=6;if(canonicalRimId(rim.id)==rim.id)++styles[int(style)];if(rim.imageSource==2)inherited&=style==rimStyleOf(10000+rim.sourceId);}
        expect(inherited&&std::all_of(styles.begin()+1,styles.end(),[](int n){return n>0;})&&std::accumulate(styles.begin(),styles.end(),0)==530,"all visible wheels belong to one of six populated visual categories and variants inherit their family");
        auto namedStyle=[](const std::string& name){for(const auto& r:RimCatalog)if(name==r.name)return rimStyleOf(r.id);return RimStyle::All;};
        expect(namedStyle("22B OEM")==RimStyle::Offroad&&namedStyle("TE38 White")==RimStyle::Tuner&&namedStyle("USA RACING ALLOY")==RimStyle::Muscle&&namedStyle("Drag Steelie")==RimStyle::Drag&&namedStyle("VIP MODULAR")==RimStyle::Luxury&&namedStyle("Carbon")==RimStyle::Hyper,"rally, tuner, muscle, drag, VIP and lightweight supercar reference families use their reviewed style");
    }
    bool audioBanksValid=std::size(BaseGameSounds)==94;for(int id=0;id<94;id++)audioBanksValid&=std::string(BaseGameSounds[id].name)==OriginalSounds[id].name&&std::string(BaseGameSounds[id].file).find("audio-original/")==0;
    expect(audioBanksValid,"both 94-sample banks preserve stable names, IDs and separate resource paths");
    const auto& sourceAnchors=attachments::anchors(20,false);
    expect(sourceAnchors.roofX==34&&sourceAnchors.roofY==-50&&sourceAnchors.hookX==130&&sourceAnchors.seatX==30,"known body uses recovered roof, hook and seat coordinates instead of generic positions");
    auto fittedRear=placeExhaust(20,7);expect(fittedRear.x==-15&&fittedRear.y==-2&&!fittedRear.front,"rear pipe uses recovered source position and is occluded by the body as in source");
    bool allSourceFits=true;int fittedVariants=0;
    for(int bank=0;bank<2;bank++)for(int car=0;car<191;car++)for(int pipe=0;pipe<51;pipe++){
        if(pipe!=0&&!std::any_of(std::begin(PartCatalog),std::end(PartCatalog),[&](const Part& p){return p.slot==PartSlot::Exhaust&&p.subimage==pipe;}))continue;
        for(int kit=0;kit<13;kit++){auto fit=placeExhaust(car,pipe,6,bank,kit,kit);allSourceFits&=std::isfinite(fit.x)&&std::isfinite(fit.y)&&fit.count>=1&&fit.count<=3;for(int j=0;j<fit.count;j++)allSourceFits&=std::isfinite(fit.outlets[j].x)&&std::isfinite(fit.outlets[j].y);++fittedVariants;}
    }
    expect(allSourceFits&&fittedVariants==243334,"both source banks and all rear/side kit choices retain finite attached pipe mouths");
    {std::ofstream out(root/"attachment-fit.json");out<<"{\n  \"source_body_pipe_configurations\": 18718,\n  \"fitted_variants_checked\": "<<fittedVariants<<",\n  \"recovered_coordinates\": 4584\n}\n";}
    bool choicesValid=true;for(size_t i=0;i<std::size(BodyChoices);i++){Profile p;p.car=BodyChoices[i].body;p.contentSource=BodyChoices[i].source;choicesValid&=bodyChoiceIndex(p)==int(i);cycleBody(p,1);cycleBody(p,-1);choicesValid&=bodyChoiceIndex(p)==int(i);}
    expect(choicesValid&&std::size(BodyChoices)==std::size(VehicleCatalog),"one body selector preserves every distinct source body and accessory bundle without duplicates");
    expect(findPart(3027)->sourceMask==1&&findPart(1002)->sourceMask==19&&findCosmetic(109001)->sourceMask==2&&findCosmetic(309001)->sourceMask==17,"source badges distinguish original exclusives, common parts and both seat variants");
    auto sourceSide=placeExhaust(20,44),sourceStack=placeExhaust(20,34),sourceRearStack=placeExhaust(20,33),sourceDownpipe=placeExhaust(20,43);
    expect(sourceSide.x==22&&sourceSide.y==2&&sourceSide.front&&sourceStack.x==22&&sourceStack.y==2&&sourceStack.front,"side outlets and side stacks use the second source anchor instead of the sill estimate");
    expect(!sourceRearStack.front&&sourceRearStack.x==-15&&!sourceDownpipe.front&&sourceDownpipe.x==-15,"rear stacks and Downpipe retain rear anchors and body occlusion");
    bool sourcePlacementMatches=true;int exactSourceFits=0;
    for(int bank=0;bank<2;bank++)for(int car=0;car<191;car++)for(int pipe=0;pipe<48;pipe++){
        const auto& a=attachments::anchors(car,bank);int type=attachments::exhaustTypes[pipe];bool foreground=type==1||type==4;
        auto fit=placeExhaust(car,pipe,6,bank,7,12);
        double x=22+(foreground?a.exhaust2X:a.exhaustX),y=-4+(foreground?a.exhaust2Y:a.exhaustY)+6;
        sourcePlacementMatches&=fit.x==x&&fit.y==y&&fit.front==foreground;
        for(int j=0;j<fit.count;j++)sourcePlacementMatches&=std::abs(fit.outlets[j].x-x-art::pipeLayouts[pipe].outlets[j].x)<1e-7&&std::abs(fit.outlets[j].y-y-art::pipeLayouts[pipe].outlets[j].y)<1e-7;
        ++exactSourceFits;
    }
    expect(sourcePlacementMatches&&exactSourceFits==18336,"18336 source body/pipe transforms, draw layers and particle roots follow both recovered anchors, independent of kit fitting");
    {std::ofstream out(root/"exhaust-source-rules.json");out<<"{\n  \"source_transforms_checked\": "<<exactSourceFits<<",\n  \"hood_remains_native\": true\n}\n";}
    expect(std::size(StockVehicles)==191,"all source body IDs have a recovered stock mechanical record");
    Profile factoryHatch;auto hatch=buildVehicle(factoryHatch);Profile factoryAwd;factoryAwd.car=2;auto awdStock=buildVehicle(factoryAwd);Profile factoryCoupe;factoryCoupe.car=20;auto coupe=buildVehicle(factoryCoupe);
    expect(std::abs(hatch.vehicle.mass-949.82242278)<1e-6&&std::abs(hatch.baseHp-123)<1e-8&&hatch.vehicle.drive==DriveLayout::Front,"first hatchback uses source 2094 lb, 123 HP and front drive instead of the reference vehicle");
    expect(std::abs(awdStock.vehicle.mass-3263*.45359237)<1e-6&&std::abs(awdStock.baseHp-300)<1e-8&&awdStock.vehicle.drive==DriveLayout::All,"source AWD saloon uses its own 3263 lb and 300 HP");
    expect(std::abs(coupe.baseHp-266)<1e-8&&coupe.vehicle.redlineRpm==8000&&std::abs(coupe.vehicle.grip-1.215)<1e-9,"source chassis grip and rev limit reach the native force model");
    bool engineRevs=true;for(int frame=1;frame<=16;frame++){
        Profile p;p.car=134;equipPart(p,PartSlot::Engine,1000+frame);auto b=buildVehicle(p);
        engineRevs&=b.vehicle.redlineRpm==replacementEngine(frame).redlineRpm&&std::abs(b.baseHp-findPart(1000+frame)->stat)<1e-7;
    }
    expect(engineRevs,"all 16 engine swaps use recovered engine rev limits and power independently of chassis");
    Profile micro;micro.car=134;auto small=buildVehicle(micro);expect(std::abs(small.vehicle.mass-1150*.45359237)<1e-8&&std::abs(small.baseHp-31)<1e-8&&small.vehicle.redlineRpm==9000,"light microcar retains its source mass below 600 kg and its own power/revs");
    factoryHatch.factoryDrive=false;factoryHatch.drive=DriveLayout::Rear;expect(buildVehicle(factoryHatch).vehicle.drive==DriveLayout::Rear,"manual drivetrain conversion overrides factory layout");
    factoryHatch.factoryDrive=true;factoryHatch.car=2;expect(buildVehicle(factoryHatch).vehicle.drive==DriveLayout::All,"factory layout follows the chosen body without overwriting conversion preferences");
    saveProfile(root/"factory-drive.ini",factoryHatch,error);auto restoredFactory=loadProfile(root/"factory-drive.ini",191,54);expect(restoredFactory.factoryDrive&&effectiveDrive(restoredFactory)==DriveLayout::All,"factory drivetrain mode persists independently of conversion choice");
    {std::ofstream out(root/"legacy-drive.ini");out<<"version=2\ncar=0\ndrive=1\n";}
    auto legacyDrive=loadProfile(root/"legacy-drive.ini",191,54);expect(!legacyDrive.factoryDrive&&effectiveDrive(legacyDrive)==DriveLayout::Rear,"legacy saves retain the player's explicit drivetrain conversion");
    expect(loadProfile(root/"new-stock-profile.ini",191,54).factoryDrive,"a new profile starts with the car's factory drivetrain");
    bool everyStockValid=true;std::array<int,3> stockLayouts{};int stockCount=0;
    std::ofstream stockTelemetry(root/"stock-vehicle-physics.csv");stockTelemetry<<"body,mass_kg,stock_hp,redline_rpm,layout,grip_native,speed_after_10s_kmh,seconds_100_0,metres_100_0\n";
    for(int body=0;body<191;body++){
        Profile p;p.car=body;p.contentSource=1;auto b=buildVehicle(p);const auto& raw=stockVehicle(body);CarState launch,stop;stop.speed=100/3.6;double brakeTime=0,brakeStart=stop.position;
        for(int tick=0;tick<1200;tick++){stepCar(launch,b.vehicle,{true,false,true},Step,0);if(stop.speed>0){stepCar(stop,b.vehicle,{false,true,true},Step,0);brakeTime+=Step;}}
        everyStockValid&=std::isfinite(launch.speed)&&launch.speed>0&&stop.speed==0&&std::abs(b.baseHp-raw.hp)<1e-7&&std::abs(b.vehicle.mass-raw.weightLb*.45359237)<1e-7;
        ++stockLayouts[int(b.vehicle.drive)];++stockCount;
        stockTelemetry<<body<<','<<b.vehicle.mass<<','<<b.baseHp<<','<<b.vehicle.redlineRpm<<','<<int(b.vehicle.drive)<<','<<b.vehicle.grip<<','<<launch.speed*3.6<<','<<brakeTime<<','<<stop.position-brakeStart<<'\n';
    }
    expect(everyStockValid&&stockCount==191&&stockLayouts==std::array<int,3>{33,126,32},"all 191 source chassis accelerate, brake to rest and preserve their own power/mass and 33 FWD/126 RWD/32 AWD layouts");
    CarState littleRun,bigRun;littleRun.speed=bigRun.speed=50/3.6;littleRun.gear=bigRun.gear=3;
    for(int tick=0;tick<600;tick++){stepCar(littleRun,small.vehicle,{true,false,true},Step,0);stepCar(bigRun,awdStock.vehicle,{true,false,true},Step,0);}
    expect(bigRun.speed>littleRun.speed+5,"different recovered stock cars produce meaningfully different rolling acceleration");
    for(int fps:{30,60,144,240}){
        CarState x;double acc=0;for(int frame=0;frame<fps*10;frame++){acc+=1.0/fps;while(acc+1e-12>=Step){stepCar(x,awdStock.vehicle,{true,false,true},Step,0);acc-=Step;}}
        CarState reference;for(int tick=0;tick<1200;tick++)stepCar(reference,awdStock.vehicle,{true,false,true},Step,0);
        expect(std::abs(x.position-reference.position)<1e-8&&std::abs(x.speed-reference.speed)<1e-8,"recovered per-car physics stays independent of rendering FPS");
    }
    {std::ofstream out(root/"stock-vehicle-physics.json");out<<"{\n  \"bodies_checked\": "<<stockCount<<",\n  \"fwd\": "<<stockLayouts[0]<<",\n  \"rwd\": "<<stockLayouts[1]<<",\n  \"awd\": "<<stockLayouts[2]<<",\n  \"full_android_dynamics_equivalence\": false\n}\n";}
    expect(std::size(OriginalVehicleIdentities)==191&&std::string(vehicleIdentity(0,true).name).find("Honda Civic")!=std::string::npos,"every body has a stable identity label and the stock hatch is identified from its picture reference");
    expect(vehicleIdentity(100,true).tentative&&vehicleIdentity(153,true).tentative,"unresolved original models remain explicitly uncertain");
    expect(std::string(vehicleIdentity(63,false).name)!=vehicleIdentity(63,true).name&&vehicleIdentity(75,false).tentative,"mod visual replacements retain separate model labels and uncertainty instead of borrowing their base's manufacturer identity");
    Profile chassis;chassis.car=20;chassis.factoryDrive=false;chassis.drive=DriveLayout::Rear;
    auto standard=buildVehicle(chassis);Profile raised=chassis;raised.rideHeightMm=120;auto tall=buildVehicle(raised);
    expect(std::abs(tall.rideOffset-standard.rideOffset+4.608)<1e-8&&std::abs(tall.vehicle.centreOfGravityHeight-standard.vehicle.centreOfGravityHeight-.12)<1e-8,"120 mm ride adjustment moves the body and physical centre of gravity consistently");
    expect(tall.vehicle.mass==standard.vehicle.mass&&tall.baseHp==standard.baseHp,"chassis tuning cannot invent mass or horsepower");
    raised.springStiffness=.7;raised.dampingRatio=.35;raised.frontBias=-.12;raised.allowWheelie=true;
    saveProfile(root/"suspension.ini",raised,error);auto persistedChassis=loadProfile(root/"suspension.ini",191,54);
    expect(persistedChassis.rideHeightMm==120&&persistedChassis.springStiffness==.7&&persistedChassis.dampingRatio==.35&&persistedChassis.frontBias==-.12&&persistedChassis.allowWheelie,"all suspension, mass balance and wheelie adjustments survive restart");
    {std::ofstream out(root/"invalid-suspension.ini");out<<"ride_height_mm=10000\nspring_stiffness=nan\ndamping_ratio=-10\nfront_bias=2\n";}
    auto invalidChassis=loadProfile(root/"invalid-suspension.ini",191,54);
    expect(invalidChassis.rideHeightMm==120&&invalidChassis.springStiffness==1&&invalidChassis.dampingRatio==.25&&invalidChassis.frontBias==.15,"invalid chassis settings are finite and constrained to supported travel and spring ranges");
    {std::ofstream out(root/"old-chassis.ini");out<<"version=3\ncar=20\npart_suspension=2015\n";}
    auto oldChassis=loadProfile(root/"old-chassis.ini",191,54);
    expect(oldChassis.rideHeightMm==0&&oldChassis.springStiffness==1&&oldChassis.dampingRatio==.65&&!oldChassis.allowWheelie&&oldChassis.parts[1]==2015,"old saves retain installed suspension and receive neutral tuning defaults");
    Settings aidsOff;aidsOff.abs=false;aidsOff.tractionControl=false;saveSettings(root/"aids.ini",aidsOff,error);
    auto savedAids=loadSettings(root/"aids.ini");expect(!savedAids.abs&&!savedAids.tractionControl,"ABS and traction control off settings persist independently");
    expect(loadSettings(root/"no-aids-settings.ini").abs&&loadSettings(root/"no-aids-settings.ini").tractionControl,"new and legacy settings enable the driving aids by default");
    CarState equilibrium;
    for(int tick=0;tick<1200;tick++)stepCar(equilibrium,standard.vehicle,{false,false,true},Step,0);
    expect(std::abs(equilibrium.pitch)<1e-9&&std::abs(equilibrium.heave)<1e-9&&std::abs(equilibrium.frontLoad+equilibrium.rearLoad-standard.vehicle.mass*9.81)<1e-6,"front and rear spring preloads support the resting mass without drift");
    // Pin the historical suspension regression chassis to its LT5 fixture.
    Profile powerful=chassis;equipBestParts(powerful);for(int i=11;i<PartSlotCount;i++)powerful.parts[i]=0;powerful.gearCount=6;powerful.gearRatios=Profile{}.gearRatios;equipPart(powerful,PartSlot::Engine,1014);equipPart(powerful,PartSlot::Turbo,3026);auto launchVehicle=buildVehicle(powerful).vehicle;
    std::array<CarState,2> tcRuns{};std::array<double,2> slipIntegral{};std::array<double,2> minFactors{1,1};
    for(int enabled=0;enabled<2;enabled++){
        auto car=launchVehicle;car.tractionControl=enabled;
        for(int tick=0;tick<600;tick++){stepCar(tcRuns[enabled],car,{true,false,true},Step,0);slipIntegral[enabled]+=tcRuns[enabled].wheelSlip*Step;minFactors[enabled]=std::min(minFactors[enabled],tcRuns[enabled].tractionFactor);}
    }
    expect(slipIntegral[1]<slipIntegral[0]*.1&&tcRuns[1].position>tcRuns[0].position,"traction control suppresses sustained excess-power wheelspin and improves this traction-limited launch");
    expect(minFactors[1]<.9&&minFactors[0]==1,"traction control reduces delivered torque only when enabled");
    std::array<CarState,2> absRuns{};std::array<int,2> lockedTicks{},absTicks{};
    for(int enabled=0;enabled<2;enabled++){
        auto car=buildVehicle(Profile{}).vehicle;car.abs=enabled;absRuns[enabled].speed=100/3.6;absRuns[enabled].gear=4;
        for(int tick=0;tick<1200&&absRuns[enabled].speed>0;tick++){stepCar(absRuns[enabled],car,{false,true,true},Step,0);lockedTicks[enabled]+=absRuns[enabled].frontLocked;absTicks[enabled]+=absRuns[enabled].absActive;}
    }
    expect(absRuns[0].speed==0&&absRuns[1].speed==0&&absRuns[1].position<absRuns[0].position*.85,"ABS avoids the lower sliding friction and shortens the reference 100-to-zero stop");
    expect(lockedTicks[0]>100&&lockedTicks[1]==0&&absTicks[0]==0&&absTicks[1]>100,"disabled ABS permits wheel lock while enabled ABS regulates service braking");
    auto withAids=launchVehicle;withAids.abs=withAids.tractionControl=true;CarState deliberateBurn;
    for(int tick=0;tick<240;tick++)stepCar(deliberateBurn,withAids,{true,true,true,true},Step,0);
    expect(deliberateBurn.burningOut&&deliberateBurn.wheelSlip>.5&&!deliberateBurn.tcActive&&!deliberateBurn.absActive&&deliberateBurn.frontLift==0,"aids preserve deliberate stationary burnouts without artificial pitch or wheel lift");
    CarState handAbs;handAbs.speed=25;stepCar(handAbs,withAids,{true,false,true,false,false,true},Step,0);
    expect(handAbs.rearLocked&&handAbs.rearRollDistance==0&&!handAbs.nitroActive,"ABS does not release the manually held rear handbrake");
    std::array<double,2> springPeaks{};
    for(int setup=0;setup<2;setup++){
        auto car=launchVehicle;car.tractionControl=true;car.springStiffness=setup?3:.4;CarState body;
        for(int tick=0;tick<240;tick++){stepCar(body,car,{true,false,true},Step,0);springPeaks[setup]=std::max(springPeaks[setup],body.pitch);}
    }
    expect(springPeaks[0]>springPeaks[1]*2,"stiffer springs reduce actual pitch excursion under the same launch demand");
    std::array<int,2> crossings{};
    for(int damper=0;damper<2;damper++){
        auto car=standard.vehicle;car.dampingRatio=damper?1.3:.25;CarState body;body.pitch=.04;double previous=body.pitch;
        for(int tick=0;tick<480;tick++){stepCar(body,car,{false,false,true},Step,0);if(previous*body.pitch<0)++crossings[damper];previous=body.pitch;}
        expect(std::abs(body.pitch)<.002&&std::abs(body.heave)<.002,"spring and damper motion settles without accumulating energy at rest");
    }
    expect(crossings[0]>crossings[1],"stronger damping suppresses oscillations instead of changing only the sprite");
    Profile drag=powerful;drag.rideHeightMm=120;drag.springStiffness=.5;drag.dampingRatio=.3;drag.frontBias=-.15;drag.allowWheelie=true;drag.wheelieTune=0;
    auto dragVehicle=buildVehicle(drag).vehicle;dragVehicle.tractionControl=true;
    double peakLift=0;CarState wheelieAtPeak,dragState,groundState;auto grounded=dragVehicle;grounded.allowWheelie=false;
    std::ofstream suspensionTrace(root/"suspension-physics.csv");suspensionTrace<<"time_s,speed_mps,pitch_rad,heave_m,front_load_n,rear_load_n,front_lift_m\n";
    for(int tick=0;tick<720;tick++){
        stepCar(dragState,dragVehicle,{true,false,true,true},Step,0);stepCar(groundState,grounded,{true,false,true,true},Step,0);
        if(dragState.frontLift>peakLift){peakLift=dragState.frontLift;wheelieAtPeak=dragState;}
        if(tick%12==0)suspensionTrace<<dragState.elapsed<<','<<dragState.speed<<','<<dragState.pitch<<','<<dragState.heave<<','<<dragState.frontLoad<<','<<dragState.rearLoad<<','<<dragState.frontLift<<'\n';
    }
    expect(peakLift>.1&&wheelieAtPeak.frontLoad==0&&wheelieAtPeak.rearLoad>0,"high-power rearward-balanced drag setup physically unloads and lifts the front axle");
    expect(groundState.frontLift==0&&groundState.rearLift==0,"grounded constraint prevents wheel lift under the same preparation without infinite grip");
    for(int tick=0;tick<1200;tick++)stepCar(dragState,dragVehicle,{false,true,true},Step,0);
    expect(dragState.speed==0&&dragState.frontLift==0&&std::abs(dragState.pitch)<.002,"wheelie returns to the contact plane and the springs settle after braking");
    auto pose=chassisPose(62,160,58,dragVehicle,wheelieAtPeak);auto frontPose=pose.wheel(true),rearPose=pose.wheel(false),pivotPose=pose.body(pose.pivotX,pose.pivotY);
    expect(frontPose.y<rearPose.y&&std::abs(58-frontPose.y-wheelieAtPeak.frontLift*pose.pixelsPerMetre)<1e-9,"rendered front wheel lift uses the simulated metre displacement");
    expect(std::abs(pivotPose.x-pose.pivotX)<1e-9&&std::abs(pivotPose.y-pose.pivotY+wheelieAtPeak.heave*pose.pixelsPerMetre)<1e-9,"body and exhaust transform share the simulated heave and pitch pivot");
    auto archlessPose=chassisPose(0,0,0,dragVehicle,wheelieAtPeak).wheel(true);
    expect(std::isfinite(archlessPose.x)&&std::isfinite(archlessPose.y),"archless special body keeps finite transformed anchors");
    DrivingEffects airborne;EffectSources airPoints=points;CarState air=wheelieAtPeak;air.wheelSlip=1;
    Vehicle awdAir=dragVehicle;awdAir.drive=DriveLayout::All;airborne.update(air,awdAir,{true,false,true},airPoints,0,Step,false);
    expect(std::count_if(airborne.particles.begin(),airborne.particles.end(),[](const Particle& p){return p.kind==EffectKind::Smoke;})==1&&std::all_of(airborne.particles.begin(),airborne.particles.end(),[&](const Particle& p){return p.kind!=EffectKind::Smoke||p.x==points.rearWheel;}),"airborne front tyre cannot emit ground-contact skid smoke");
    bool stableChassis=true;int chassisCases=0;
    for(double height:{-60.,120.})for(double spring:{.4,3.})for(double damper:{.25,1.5})for(double bias:{-.15,.15})for(bool lift:{false,true})for(bool tc:{false,true}){
        Profile p=powerful;p.rideHeightMm=height;p.springStiffness=spring;p.dampingRatio=damper;p.frontBias=bias;p.allowWheelie=lift;
        auto car=buildVehicle(p).vehicle;car.tractionControl=tc;car.abs=true;CarState body;
        for(int tick=0;tick<960;tick++){
            stepCar(body,car,tick<480?DriverInput{true,false,true,true}:DriverInput{false,true,true},Step,0);
            stableChassis&=std::isfinite(body.pitch)&&std::isfinite(body.heave)&&std::isfinite(body.speed)&&body.frontLoad>=0&&body.rearLoad>=0&&body.frontLift>=0&&body.rearLift>=0&&body.pitch<=.55&&body.pitch>=-.15;
            if(!lift)stableChassis&=body.frontLift==0&&body.rearLift==0;
        }++chassisCases;
    }
    expect(stableChassis&&chassisCases==64,"64 extreme chassis, wheelie and aid configurations stay finite through launch and braking");
    for(int fps:{30,60,144,240}){
        CarState body,reference;double acc=0;
        for(int frame=0;frame<fps*6;frame++){acc+=1.0/fps;while(acc+1e-12>=Step){stepCar(body,dragVehicle,{true,false,true,true},Step,0);acc-=Step;}}
        for(int tick=0;tick<720;tick++)stepCar(reference,dragVehicle,{true,false,true,true},Step,0);
        expect(std::abs(body.pitch-reference.pitch)<1e-10&&std::abs(body.heave-reference.heave)<1e-10&&std::abs(body.position-reference.position)<1e-8,"spring dynamics and wheelie remain independent of rendering FPS");
    }
    {std::ofstream out(root/"suspension-aids.json");out<<"{\n  \"chassis_configurations_checked\": "<<chassisCases<<",\n  \"max_wheelie_lift_m\": "<<peakLift<<",\n  \"abs_stop_m\": "<<absRuns[1].position<<",\n  \"locked_stop_m\": "<<absRuns[0].position<<",\n  \"tc_launch_distance_m\": "<<tcRuns[1].position<<",\n  \"uncontrolled_launch_distance_m\": "<<tcRuns[0].position<<",\n  \"full_android_dynamics_equivalence\": false\n}\n";}
    int dragCases=0;bool stableDrag=true,preservedDrag=true,lessPitch=true;double dragMaxPitch=0;
    std::ofstream dragTrace(root/"drag-launch.csv");dragTrace<<"layout,tc,setup,distance_10s_m,speed_10s_kmh,peak_front_lift_m,peak_pitch_rad\n";
    for(auto layout:{DriveLayout::Front,DriveLayout::Rear,DriveLayout::All})for(bool tc:{false,true}){
        Profile launch=powerful;launch.factoryDrive=false;launch.drive=layout;
        std::array<double,2> excursions{};
        for(int setup=0;setup<2;setup++){
            Profile p=launch;applySuspensionPreset(p,setup?SuspensionPreset::Drag:SuspensionPreset::Road);
            preservedDrag&=p.parts==launch.parts&&p.gearRatios==launch.gearRatios&&p.drive==launch.drive&&p.factoryDrive==launch.factoryDrive;
            auto v=buildVehicle(p).vehicle;v.tractionControl=tc;CarState car;
            for(int tick=0;tick<1200;tick++){
                stepCar(car,v,{true,false,true,true},Step,0);excursions[setup]=std::max(excursions[setup],std::abs(car.pitch));
                stableDrag&=std::isfinite(car.speed)&&car.frontLift==0&&car.rearLift==0&&car.frontLoad>0&&car.rearLoad>0;
            }
            if(setup){dragMaxPitch=std::max(dragMaxPitch,excursions[setup]);++dragCases;}
            dragTrace<<int(layout)<<','<<tc<<','<<setup<<','<<car.position<<','<<car.speed*3.6<<','<<car.peakFrontLift<<','<<excursions[setup]<<'\n';
        }
        lessPitch&=excursions[1]<excursions[0];
        Profile p=launch;applySuspensionPreset(p,SuspensionPreset::Drag);
        expect((layout==DriveLayout::Front?p.frontBias>0:layout==DriveLayout::Rear?p.frontBias<0:p.frontBias==0),"drag balance follows the selected driven axle layout");
    }
    expect(stableDrag&&dragCases==6,"all six drag launch layout/TC combinations retain positive tyre contact for ten seconds");
    expect(lessPitch&&dragMaxPitch<.04,"drag setup reduces pitch relative to road without using the extreme wheelie setup");
    expect(preservedDrag,"suspension presets preserve installed power parts, gearing and drive conversion");
    Profile explicitWheelie=powerful;applySuspensionPreset(explicitWheelie,SuspensionPreset::Wheelie);
    expect(explicitWheelie.allowWheelie&&explicitWheelie.rideHeightMm==120,"wheelie remains an explicit separate suspension preset");
    {std::ofstream out(root/"drag-setup.json");out<<"{\n  \"launch_cases_checked\": "<<dragCases<<",\n  \"max_drag_pitch_rad\": "<<dragMaxPitch<<",\n  \"drag_keeps_contact\": "<<(stableDrag?"true":"false")<<",\n  \"original_physics_imported\": false\n}\n";}
    bool barStable=true,barContactValid=true;int barCases=0;double maxBarLift=0;
    std::ofstream barsTrace(root/"wheelie-bars.csv");barsTrace<<"bank,body,peak_front_lift_m,roller_touched,peak_pitch_rad\n";
    for(int bank=0;bank<2;bank++)for(int body=0;body<191;body++){
        Profile p=powerful;p.car=body;p.contentSource=bank;p.factoryDrive=false;p.drive=DriveLayout::Rear;
        applySuspensionPreset(p,SuspensionPreset::Wheelie);p.cosmetics[6]=106011;
        auto v=buildVehicle(p).vehicle;v.tractionControl=true;CarState car;double pitch=0;
        barStable&=v.wheelieBar&&v.allowWheelie&&v.wheelieBarArm<0&&v.wheelieBarClearance>=0;
        for(int tick=0;tick<720;tick++){
            stepCar(car,v,{true,false,true,true},Step,0);pitch=std::max(pitch,car.pitch);
            barStable&=std::isfinite(car.speed)&&std::isfinite(car.pitch)&&car.frontLoad>=0&&car.rearLoad>=0;
            barContactValid&=v.wheelieBarClearance+car.heave+v.wheelieBarArm*car.pitch>=-1e-8;
        }
        maxBarLift=std::max(maxBarLift,car.peakFrontLift);++barCases;
        barsTrace<<bank<<','<<body<<','<<car.peakFrontLift<<','<<car.wheelieBarTouched<<','<<pitch<<'\n';
    }
    expect(barCases==382&&barStable,"DRAG PRO rollers on all 382 source bodies produce finite support without disabling the wheelie setting");
    expect(barContactValid,"rear roller unilateral support prevents penetration of the contact plane on every source body");
    Profile barProfile=drag;barProfile.cosmetics[6]=106011;auto barVehicle=buildVehicle(barProfile).vehicle;barVehicle.tractionControl=true;CarState barred;
    for(int tick=0;tick<720;tick++)stepCar(barred,barVehicle,{true,false,true,true},Step,0);
    expect(barred.wheelieBarTouched&&barred.peakFrontLift<.01&&peakLift>.1,"equipping the source rear roller stops the tested high-power wheelie through rear contact");

    {Profile modern;modern.car=20;modern.factoryDrive=false;modern.drive=DriveLayout::Rear;equipBestParts(modern);applySuspensionPreset(modern,SuspensionPreset::Wheelie);
        auto unbarred=buildVehicle(modern).vehicle;unbarred.tractionControl=true;CarState beforeBar;
        modern.cosmetics[6]=106011;auto supported=buildVehicle(modern).vehicle;supported.tractionControl=true;CarState afterBar;
        for(int tick=0;tick<720;tick++){stepCar(beforeBar,unbarred,{true,false,true,true},Step,0);stepCar(afterBar,supported,{true,false,true,true},Step,0);}
        std::cout<<"Catalogue maximum roller: lift="<<afterBar.peakFrontLift<<" versus "<<beforeBar.peakFrontLift<<" m; contact="<<afterBar.wheelieBarTouched<<'\n';
        expect(afterBar.wheelieBarTouched&&afterBar.peakFrontLift<.05&&afterBar.peakFrontLift<beforeBar.peakFrontLift*.2,"roller support bounds front lift with the new maximum fuel and ten-speed preparation");
    }
    barProfile.cosmetics[6]=0;barProfile.cosmetics[4]=104011;
    expect(buildVehicle(barProfile).vehicle.wheelieBar,"full DRAG PRO kit includes rear roller support");
    barProfile.cosmetics[6]=106002;
    expect(!buildVehicle(barProfile).vehicle.wheelieBar,"deleting or replacing the rear piece removes the full kit wheelie bar effect");
    barProfile.cosmetics[4]=0;barProfile.cosmetics[6]=106005;
    expect(!buildVehicle(barProfile).vehicle.wheelieBar,"ordinary drag rear panel without rollers is not treated as a wheelie bar");
    barProfile.cosmetics[6]=0;auto restoredWheelie=buildVehicle(barProfile).vehicle;restoredWheelie.tractionControl=true;CarState restoredLift;
    for(int tick=0;tick<720;tick++)stepCar(restoredLift,restoredWheelie,{true,false,true,true},Step,0);
    expect(restoredLift.peakFrontLift>.1,"removing the bar restores the original wheelie preparation without overwriting it");
    {std::ofstream out(root/"wheelie-bars.json");out<<"{\n  \"source_bodies_checked\": "<<barCases<<",\n  \"contact_plane_respected\": "<<(barContactValid?"true":"false")<<",\n  \"reference_unbarred_lift_m\": "<<peakLift<<",\n  \"reference_barred_lift_m\": "<<barred.peakFrontLift<<",\n  \"max_lift_across_barred_bodies_m\": "<<maxBarLift<<",\n  \"original_bar_physics_recovered\": false\n}\n";}
    for(auto layout:{DriveLayout::Front,DriveLayout::Rear,DriveLayout::All}){
        Profile balanced=powerful;balanced.factoryDrive=false;balanced.drive=layout;balanced.frontBias=.5-(layout==DriveLayout::Front?.60:.48);
        auto v=buildVehicle(balanced).vehicle;CarState atRest;stepCar(atRest,v,{false,false,true},Step,0);
        expect(std::abs(v.frontWeightFraction-.5)<1e-9&&std::abs(atRest.frontLoad-atRest.rearLoad)<1e-6,"balanced marker gives equal static axle loads for every drivetrain without changing total mass");
    }
    Profile tuned=drag;tuned.wheelieTune=.37;saveProfile(root/"wheelie-tune.ini",tuned,error);
    auto savedTune=loadProfile(root/"wheelie-tune.ini",191,54);
    expect(savedTune.wheelieTune==.37&&savedTune.allowWheelie&&savedTune.frontBias==tuned.frontBias,"wheelie tune saves independently of mass balance and lift permission");
    {std::ofstream out(root/"legacy-wheelie.ini");out<<"version=5\nallow_wheelie=1\n";}
    expect(loadProfile(root/"legacy-wheelie.ini",191,54).wheelieTune==0&&loadProfile(root/"old-chassis.ini",191,54).wheelieTune==1,"legacy wheelie preparations remain free while grounded saves receive balanced tuning");
    tuned.wheelieTune=10;sanitizeSuspension(tuned);expect(tuned.wheelieTune==1,"wheelie tuning is constrained to the supported range");
    std::array<double,5> tunedLifts{};std::ofstream tuneTrace(root/"wheelie-tuning.csv");tuneTrace<<"tune,peak_front_lift_m,distance_6s_m\n";
    bool mechanicalTravel=true;
    for(int i=0;i<5;i++){
        Profile p=drag;p.wheelieTune=i*.25;auto v=buildVehicle(p).vehicle;v.tractionControl=true;CarState car;
        for(int tick=0;tick<720;tick++){
            stepCar(car,v,{true,false,true,true},Step,0);
            double a=v.wheelbase*(1-v.frontWeightFraction),b=v.wheelbase*v.frontWeightFraction;
            mechanicalTravel&=car.heave+a*car.pitch>=-v.suspensionBump-1e-6&&car.heave-b*car.pitch>=-v.suspensionBump-1e-6;
        }
        tunedLifts[i]=car.peakFrontLift;tuneTrace<<i*.25<<','<<car.peakFrontLift<<','<<car.position<<'\n';
    }
    expect(tunedLifts[0]>.1&&tunedLifts[4]==0&&tunedLifts[0]>tunedLifts[1]&&tunedLifts[1]>tunedLifts[2]&&tunedLifts[2]>tunedLifts[3]&&tunedLifts[3]>tunedLifts[4],"five wheelie-to-balanced positions progressively reduce actual lift without changing weight distribution");
    expect(mechanicalTravel,"rear squat and front dive respect finite shock compression through all five launch tunes");
    bool attachedHubs=true,contactHeight=true;int carrierCases=0;
    for(bool original:{false,true})for(int body=0;body<191;body++)for(double ride:{-4.,0.,6.})for(double pitch:{-.1,0.,.15,.35}){
        const float* w=original?content_art::originalAnchors[body]:content_art::unboundAnchors[body];CarState state;state.pitch=pitch;state.heave=.02;state.frontLift=std::max(0.,pitch*.8);state.rearLift=std::max(0.,-pitch*.8);
        auto pose=chassisPose(w[0],w[1],w[2],dragVehicle,state,ride);
        for(bool front:{false,true}){
            auto hub=pose.body(front?w[1]:w[0],w[2]+ride),wheel=pose.wheel(front);
            double localX=std::cos(pitch)*(wheel.x-hub.x)-std::sin(pitch)*(wheel.y-hub.y);
            attachedHubs&=std::isfinite(wheel.x)&&std::abs(localX)<1e-9;
            contactHeight&=std::abs(wheel.y-(w[2]-(front?state.frontLift:state.rearLift)*pose.pixelsPerMetre))<1e-9;++carrierCases;
        }
    }
    expect(attachedHubs&&carrierCases==9168,"wheel hubs remain on the wheel-arch suspension axis across 9168 source-body, stance and pitch cases");
    expect(contactHeight,"wheel carrier correction preserves the physical ground plane and simulated tyre lift");
    {std::ofstream out(root/"wheel-carriers.json");out<<"{\n  \"hub_cases_checked\": "<<carrierCases<<",\n  \"suspension_axes_respected\": "<<(attachedHubs?"true":"false")<<",\n  \"mechanical_travel_respected\": "<<(mechanicalTravel?"true":"false")<<",\n  \"wheelie_endpoint_lift_m\": "<<tunedLifts[0]<<",\n  \"balanced_endpoint_lift_m\": "<<tunedLifts[4]<<",\n  \"full_android_dynamics_equivalence\": false\n}\n";}
    Profile powerWheelie=drag;powerWheelie.cosmetics[4]=powerWheelie.cosmetics[6]=0;powerWheelie.wheelieTune=0;
    auto powerBase=buildVehicle(powerWheelie).vehicle;powerBase.nitroHp=0;powerBase.tractionControl=true;
    const double hpSteps[]={200,400,800,1200,2000};std::array<double,5> powerLifts{};std::array<double,5> liftTimes{};
    bool samePowerChassis=true;std::ofstream powerTrace(root/"power-wheelie.csv");powerTrace<<"engine_hp,peak_front_lift_m,first_lift_s,distance_5s_m,mass_kg,grip,front_weight_fraction\n";
    for(int i=0;i<5;i++){
        auto v=powerBase;v.torque*=hpSteps[i]/peakPower(powerBase).hp;CarState car;liftTimes[i]=-1;
        for(int tick=0;tick<600;tick++){stepCar(car,v,{true,false,true},Step,0);if(car.frontLift>.01&&liftTimes[i]<0)liftTimes[i]=car.elapsed;}
        powerLifts[i]=car.peakFrontLift;samePowerChassis&=v.mass==powerBase.mass&&v.grip==powerBase.grip&&v.frontWeightFraction==powerBase.frontWeightFraction;
        powerTrace<<hpSteps[i]<<','<<car.peakFrontLift<<','<<liftTimes[i]<<','<<car.position<<','<<v.mass<<','<<v.grip<<','<<v.frontWeightFraction<<'\n';
    }
    bool strongerWheelie=powerLifts[0]==0&&powerLifts[1]==0&&powerLifts[2]>0&&powerLifts[3]>powerLifts[2]&&powerLifts[4]>powerLifts[3];
    expect(strongerWheelie&&samePowerChassis,"higher engine power produces stronger wheelie on the same gripping chassis across five controlled power levels");
    expect(liftTimes[2]>liftTimes[3]&&liftTimes[3]>liftTimes[4],"stronger engines unload the front axle earlier under the same launch controls");
    {std::ofstream out(root/"power-wheelie.json");out<<"{\n  \"power_levels_checked\": 5,\n  \"same_chassis_and_grip\": "<<(samePowerChassis?"true":"false")<<",\n  \"stronger_wheelie_verified\": "<<(strongerWheelie?"true":"false")<<",\n  \"native_calibration\": true\n}\n";}
    std::array<double,3> launchPowers{200,400,1200};std::array<double,3> launchExcess{};std::array<double,3> launchDuration{};
    std::ofstream revLaunchTrace(root/"rev-launch.csv");revLaunchTrace<<"power_hp,tc,release,spin_seconds,launch_slip_m,total_slip_m,distance_4s_m\n";
    bool releaseParity=true,launchFinite=true,heldSafe=true;double controlledSlip=0;
    auto revLaunch=[&](double hp,bool tc,bool neutral,double initialRpm=-1){
        auto v=powerBase;v.torque*=hp/peakPower(powerBase).hp;v.tractionControl=tc;CarState car;
        if(initialRpm<0){for(int tick=0;tick<240;tick++)stepCar(car,v,{true,false,true,false,false,!neutral,neutral},Step,0);}
        else {car.neutral=neutral;car.handbraking=!neutral;car.rpm=initialRpm;}
        heldSafe&=car.speed==0&&car.rearRollDistance==0&&car.frontRollDistance==0;
        for(int tick=0;tick<480;tick++){
            stepCar(car,v,{true,false,true},Step,0);launchFinite&=std::isfinite(car.rpm)&&std::isfinite(car.speed)&&car.rpm<=v.redlineRpm+1&&car.speed>=0;
        }
        double slip=(car.rearRollDistance+car.frontRollDistance)*.5-car.position;
        revLaunchTrace<<hp<<','<<tc<<','<<(neutral?"neutral":"handbrake")<<','<<car.launchSlipSeconds<<','<<car.launchSlipDistance<<','<<slip<<','<<car.position<<'\n';return car;
    };
    for(int i=0;i<3;i++){
        auto h=revLaunch(launchPowers[i],false,false),n=revLaunch(launchPowers[i],false,true);
        launchExcess[i]=h.launchSlipDistance;launchDuration[i]=h.launchSlipSeconds;
        releaseParity&=std::abs(h.launchSlipDistance-n.launchSlipDistance)<1e-9;
        auto controlled=revLaunch(launchPowers[i],true,false);controlledSlip=std::max(controlledSlip,controlled.launchSlipDistance);
    }
    expect(heldSafe&&launchFinite,"revved engines remain disconnected until release and launch states stay finite below the limiter");
    expect(launchExcess[0]>0&&launchExcess[1]>launchExcess[0]&&launchExcess[2]>launchExcess[1],"without TC stronger engines produce more launch wheelspin after the same high-RPM clutch release");
    expect(launchDuration[0]<launchDuration[1]&&launchDuration[1]<launchDuration[2],"more engine power sustains the launch spin longer on the controlled low-to-high power range");
    expect(releaseParity&&controlledSlip==0,"handbrake and neutral releases share launch physics while TC controls the initial overspin");
    auto lowRevLaunch=revLaunch(400,false,true,2800),highRevLaunch=revLaunch(400,false,true,7600);
    expect(highRevLaunch.launchSlipDistance>lowRevLaunch.launchSlipDistance+1,"saved engine RPM influences launch spin rather than resetting immediately to launch RPM");
    bool drivenLaunch=true;
    for(auto layout:{DriveLayout::Front,DriveLayout::Rear,DriveLayout::All}){
        auto v=powerBase;v.drive=layout;v.tractionControl=false;CarState car;
        for(int tick=0;tick<240;tick++)stepCar(car,v,{true,false,true,false,false,true},Step,0);
        for(int tick=0;tick<120;tick++)stepCar(car,v,{true,false,true},Step,0);
        drivenLaunch&=layout==DriveLayout::Front?car.frontRollDistance>car.rearRollDistance:layout==DriveLayout::Rear?car.rearRollDistance>car.frontRollDistance:std::abs(car.frontRollDistance-car.rearRollDistance)<1e-8;
    }
    expect(drivenLaunch,"rev-release spin animates only the driven axles for FWD RWD and AWD");
    Vehicle inertialLaunch=powerBase;inertialLaunch.torque=0;inertialLaunch.boostPsi=0;inertialLaunch.tractionControl=false;
    CarState inertiaState;inertiaState.neutral=true;inertiaState.rpm=7600;double initialEnergy=.5*inertialLaunch.engineInertia*std::pow(7600*2*3.141592653589793/60,2);
    for(int tick=0;tick<40&&inertiaState.launchWheelOmega<0;tick++)stepCar(inertiaState,inertialLaunch,{true,false,false},Step,0);
    double launchRatio=inertialLaunch.ratios[0]*inertialLaunch.finalDrive;
    double coupledEnergy=.5*(inertialLaunch.drivenWheelInertia+inertialLaunch.engineInertia*launchRatio*launchRatio)*std::pow(inertiaState.launchWheelOmega,2)+.5*inertialLaunch.mass*inertiaState.speed*inertiaState.speed;
    expect(inertiaState.launchWheelOmega>0&&coupledEnergy<=initialEnergy,"clutch coupling transfers stored rotational energy without creating energy");
    {std::ofstream out(root/"rev-launch.json");out<<"{\n  \"power_levels_checked\": 3,\n  \"handbrake_neutral_parity\": "<<(releaseParity?"true":"false")<<",\n  \"stronger_power_more_spin\": "<<((launchExcess[0]<launchExcess[1]&&launchExcess[1]<launchExcess[2])?"true":"false")<<",\n  \"controlled_initial_slip_m\": "<<controlledSlip<<",\n  \"native_calibration\": true\n}\n";}
    auto stagedVehicle=powerBase;stagedVehicle.twoStep=true;stagedVehicle.tractionControl=false;CarState revStaged;
    for(int tick=0;tick<240;tick++)stepCar(revStaged,stagedVehicle,{true,false,true,false,false,true},Step,0);
    for(int tick=0;tick<120;tick++)stepCar(revStaged,stagedVehicle,{true,false,true,false,true},Step,0);
    expect(revStaged.launching&&revStaged.speed==0&&revStaged.rearRollDistance==0,"two-step staging keeps the clutch open when handbrake is released with launch control held");
    std::array<size_t,2> spinSmokeCounts{};std::array<double,2> spinSmokeScale{};
    for(int intensity=0;intensity<2;intensity++){
        DrivingEffects smoky;CarState car;car.speed=8;car.wheelSlip=intensity?2:.1;
        for(int tick=0;tick<120;tick++){car.position+=car.speed*Step;smoky.update(car,powerBase,{true,false,true},points,0,Step,false);}
        for(const auto& particle:smoky.particles)if(particle.kind==EffectKind::Smoke){spinSmokeCounts[intensity]++;spinSmokeScale[intensity]=std::max(spinSmokeScale[intensity],particle.scale);}
    }
    expect(spinSmokeCounts[1]>spinSmokeCounts[0]&&spinSmokeScale[1]>spinSmokeScale[0],"stronger measured wheel slip creates denser larger dynamic tyre smoke");
    bool paletteTransfer=true;int paletteCases=0;
    for(bool original:{false,true})for(int column=0;column<108;column++)for(int row=0;row<11;row++){
        const auto& pal=original?materials::originalPaint:materials::unboundPaint;
        auto source=materials::unpack(pal[0][row]),expected=materials::unpack(pal[column][row]),actual=materials::paintPixel(source,column+1,original);
        paletteTransfer&=actual.r==expected.r&&actual.g==expected.g&&actual.b==expected.b&&actual.a==expected.a;++paletteCases;
    }
    expect(paletteTransfer&&paletteCases==2376,"all source paint shade texels follow the recovered palette shader mapping");
    auto glass=materials::Rgba{11,12,15,199};auto unchanged=materials::paintPixel(glass,85,false);
    expect(unchanged.r==glass.r&&unchanged.a==glass.a&&materials::paintRow({255,0,0,255},false)<0,"paint palette preserves source glass and non-paint emissive colours");
    auto baseBlue=materials::unpack(materials::unboundPaint[0][5]);auto nearBlue=baseBlue;nearBlue.r+=1;
    expect(materials::paintRow(nearBlue,false)==5,"source shader tolerance includes one integer channel step");nearBlue.g+=1;
    expect(materials::paintRow(nearBlue,false)<0,"source shader tolerance rejects larger colour distances");
    auto tinted=materials::glassTint(glass,2);auto noTint=materials::glassTint(baseBlue,2);
    expect(tinted.a>glass.a&&tinted.b>tinted.r&&noTint.r==baseBlue.r&&noTint.a==baseBlue.a,"glass tint follows actual translucent source pixels instead of a fixed cabin rectangle");
    std::vector<unsigned> tints;
    for(int tint=1;tint<=10;tint++){auto c=materials::lightTint({220,220,220,255},tint);tints.push_back(unsigned(c.r)*65536+unsigned(c.g)*256+c.b);}
    std::sort(tints.begin(),tints.end());expect(std::adjacent_find(tints.begin(),tints.end())==tints.end(),"all ten headlight tint choices produce distinct rendered colours or darkness");
    auto tailTint=materials::lightTint({200,100,40,255},3,true);expect(tailTint.r<70&&tailTint.g<40&&tailTint.r>tailTint.g&&tailTint.g>tailTint.b,"taillight darkness preserves the source lens colours");
    int fitCases=0,unsupported=0,partial=0;
    for(int bank=0;bank<2;bank++)for(int body=0;body<191;body++)for(const auto& c:CosmeticCatalog){Profile p;p.car=body;p.contentSource=bank;auto fit=cosmeticFit(p,c.id);++fitCases;unsupported+=!fit.supported;partial+=fit.partial;}
    expect(fitCases==int(std::size(CosmeticCatalog))*382&&unsupported==129&&partial==2309,"all 503 cosmetic choices across 382 body banks expose source compatibility and partial kits");
    bool hoodFits=true;int hoodCases=0,kitMoves=0;
    for(bool original:{false,true})for(int body=0;body<191;body++)for(int front=0;front<13;front++)for(int pipe=48;pipe<=50;pipe++){
        const auto& mount=materials::hoodMount(body,front,original);auto fit=placeExhaust(body,pipe,6,original,0,front);const auto& shape=art::pipeLayouts[pipe];
        hoodFits&=fit.front&&std::abs(fit.x+shape.baseX-mount.x)<1e-8&&std::abs(fit.y+shape.baseY-mount.y-6)<1e-8&&fit.count==(pipe==50?3:1)&&mount.x>=0&&mount.x<220&&mount.y>=0&&mount.y<70;
        for(int i=0;i<fit.count;i++)hoodFits&=fit.outlets[i].dy==-1&&fit.outlets[i].y<fit.y+shape.baseY;
        if(front&&materials::hoodMount(body,0,original).y!=mount.y)++kitMoves;
        ++hoodCases;
    }
    expect(hoodFits&&hoodCases==14898&&kitMoves>0,"all three hood pipes share per-body and per-front-kit bonnet contact with suspension and separate particle mouths");
    Profile splitRims;splitRims.rim=10101;equipRim(splitRims,10100,1);
    expect(splitRims.rim==10100&&rearRimId(splitRims)==10101,"front-only rim change retains the previously equipped rear rim");
    equipRim(splitRims,RimFrames[5],2);saveProfile(root/"split-rims.ini",splitRims,error);auto reloadedRims=loadProfile(root/"split-rims.ini",191,54);
    expect(reloadedRims.rim==10100&&rearRimId(reloadedRims)==RimFrames[5],"independent front and rear rims survive restart");
    equipRim(splitRims,10101,0);expect(splitRims.rearRim==-1&&rearRimId(splitRims)==splitRims.rim,"both-axle selection restores the linked rim behaviour");
    bool finishes=true;for(int rim:RimFrames){if(findRim(rim)&&findRim(rim)->imageSource==2)continue;auto f=rim_finish::finish(rim);finishes&=f&&f->shine>=0&&f->shine<54&&f->shadow>=0&&f->shadow<4;}
    expect(finishes&&std::size(rim_finish::Finishes)==521,"all named rim recipes retain stationary shine and shadow passes from source data");
    Profile lightSeat;auto seatStock=buildVehicle(lightSeat);lightSeat.cosmetics[9]=109001;auto seatBuild=buildVehicle(lightSeat);
    expect(std::abs(seatBuild.vehicle.mass-seatStock.vehicle.mass+90*.45359237)<1e-8&&seatBuild.baseHp==seatStock.baseHp,"source seat weight reduction affects native mass without creating engine horsepower");
    {std::ofstream out(root/"customization-render.json");out<<"{\n  \"palette_shades_checked\": "<<paletteCases<<",\n  \"cosmetic_cases_checked\": "<<fitCases<<",\n  \"unsupported_choices\": "<<unsupported<<",\n  \"partial_choices\": "<<partial<<",\n  \"hood_body_kit_pipe_cases\": "<<hoodCases<<",\n  \"rim_finish_recipes\": 521,\n  \"hood_coordinates_recovered_from_android\": false\n}\n";}
    Profile flags;flags.rollCage=true;flags.headlights=true;flags.audioSource=1;flags.contentSource=0;saveProfile(root/"flags.ini",flags,error);auto loadedFlags=loadProfile(root/"flags.ini",191,54);
    expect(loadedFlags.rollCage&&loadedFlags.headlights&&loadedFlags.audioSource==1&&loadedFlags.contentSource==0,"cage, headlights and independent audio source survive reload");
    {std::ofstream out(root/"legacy-seat.ini");out<<"version=1\ncontent_source=1\ncosmetic_9=109001\npart_engine=1002\n";}
    auto legacySeat=loadProfile(root/"legacy-seat.ini",191,54);expect(legacySeat.cosmetics[9]==309001&&legacySeat.audioSource==1&&legacySeat.parts[0]==1002,"legacy original bank seats and sound migrate without changing the installed engine");
    expect(easeLinear(0,5,10,2)==5&&easeLinear(2,5,10,2)==15,"reconstructed numeric easing endpoints");
    std::cout<<"PASS: "<<checks<<" checks; quarter mile "<<reference.finishTime<<" s; endless distance "<<simulated(60,true).position<<" m\n";
    return 0;
 }catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
