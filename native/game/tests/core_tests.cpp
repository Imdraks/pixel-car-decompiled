#include "model.hpp"
#include "benchmark.hpp"
#include "art.hpp"
#include "effects.hpp"
#include "road_scene.hpp"
#include <cmath>
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <stdexcept>
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
    double brakingTime=0;
    for(int i=0;i<1200&&braking.speed>0;i++){
        stepCar(braking,v,{false,true,true},Step,0);stepCar(conflicting,v,{true,true,true},Step,0);brakingTime+=Step;
    }
    expect(braking.speed==0&&braking.position>35&&braking.position<55,"100 km/h stopping distance remains plausible");
    expect(std::abs(braking.position-conflicting.position)<1e-9,"brake overrides simultaneous throttle");
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
    auto benchmark=root/std::filesystem::u8path("mesures_é_車");
    std::filesystem::remove_all(benchmark); // Only inside the explicitly supplied test directory.
    writePhysicsBenchmark(benchmark);
    expect(std::filesystem::file_size(benchmark/"telemetry.csv")>1000,"physics benchmark produces a time series on a Unicode path");
    std::ifstream benchmarkIn(benchmark/"physics-report.json");
    std::string benchmarkText((std::istreambuf_iterator<char>(benchmarkIn)),std::istreambuf_iterator<char>());
    expect(benchmarkText.find("\"sanity_checks_passed\": true")!=std::string::npos,"benchmark scenarios pass their sanity checks");
    bool refused=false;try{writePhysicsBenchmark(benchmark);}catch(const std::exception&){refused=true;}
    expect(refused,"benchmark refuses to replace an existing directory");
    expect(std::size(PartCatalog)==194,"all requested Unbound catalog entries are included");
    std::array<int,PartSlotCount> counts{};
    for(const auto& part:PartCatalog)++counts[int(part.slot)];
    expect(counts==std::array<int,PartSlotCount>{16,16,14,10,8,5,21,13,7,48,36},"catalog includes every requested category and supercharger split");
    Profile custom;
    expect(equipPart(custom,PartSlot::Engine,1002),"2JZ can be equipped by stable catalog ID");
    auto jz=buildVehicle(custom);
    expect(std::abs(jz.baseHp-410)<.001,"recovered 2JZ catalog power drives the native torque curve");
    Profile lowPower,highPower;equipPart(lowPower,PartSlot::Engine,1001);equipPart(highPower,PartSlot::Engine,1014);
    auto lowBuild=buildVehicle(lowPower),highBuild=buildVehicle(highPower);CarState lowRun,highRun;
    lowRun.speed=highRun.speed=40;lowRun.gear=highRun.gear=4;
    for(int i=0;i<120*3;i++){stepCar(lowRun,lowBuild.vehicle,{true,false,false},Step,0);stepCar(highRun,highBuild.vehicle,{true,false,false},Step,0);}
    expect(highRun.speed>lowRun.speed+2,"selecting a stronger engine actually improves a rolling acceleration");
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
    expect(ecuBuild.vehicle.redlineRpm==10400&&ecuBuild.vehicle.upshiftRpm==9400,"ECU raises the native rev limit and automatic shift threshold");
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
        Profile single;allPartsStable&=equipPart(single,part.slot,part.id);auto setup=buildVehicle(single);CarState run;
        for(int i=0;i<120*3;i++)stepCar(run,setup.vehicle,{true,false,true,true},Step,0);
        allPartsStable&=std::isfinite(run.speed)&&std::isfinite(run.rpm)&&run.speed>0&&run.rpm>0&&setup.vehicle.mass>=600;
    }
    expect(allPartsStable,"all 194 parts build a finite driveable configuration");
    std::string customError;
    expect(saveProfile(root/"custom.ini",custom,customError),"custom equipment profile saves");
    auto customLoaded=loadProfile(root/"custom.ini",191,54);
    expect(customLoaded.parts==custom.parts,"all equipment slots persist through a profile round trip");
    {std::ofstream out(root/"custom.ini");out<<"part_engine=3002\npart_tires=999999\npart_turbo=3002\npart_supercharger=3020\n";}
    auto corruptCustom=loadProfile(root/"custom.ini",191,54);
    expect(corruptCustom.parts[0]==0&&corruptCustom.parts[10]==0&&corruptCustom.parts[2]==0&&corruptCustom.parts[3]==3020,"malformed equipment falls back safely and cannot stack forced induction");
    Profile soundProfile;soundProfile.soundOn=5;soundProfile.soundOff=4;soundProfile.bov=3;
    auto sounds=engineSamples(soundProfile);
    expect(sounds.on==71&&sounds.off==47,"manual sound profiles match the original native dispatch tables");
    expect(saveProfile(root/"sound.ini",soundProfile,customError),"original audio preferences save");
    auto savedSound=loadProfile(root/"sound.ini",191,54);
    expect(savedSound.soundOn==5&&savedSound.soundOff==4&&savedSound.bov==3,"engine and valve audio preferences persist independently");
    DrivingEffects visuals;CarState visibleCar;visibleCar.wheelSlip=.4;
    EffectSources points{400,520,450,350,440,false};
    visuals.update(visibleCar,v,{true,false,true},points,0,Step,false);
    expect(!visuals.particles.empty()&&visuals.particles.front().kind==EffectKind::Smoke,"wheel slip emits original smoke particles");
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
    expect(ultimate.parts[0]==1014&&ultimate.parts[2]==3026&&ultimate.parts[3]==0,"maximum preparation selects LT5 and the best exclusive induction");
    expect(ultimate.car==20&&ultimate.rim==8&&ultimate.drive==DriveLayout::All&&ultimate.soundOn==4,"maximum preparation preserves appearance, drive and audio preferences");
    expect(full.boostedHp>4200&&full.nitroHp>4500&&full.nitroHp-full.boostedHp==250,"maximum parts combine into over 4500 rated HP with NOS");
    double expectedHp=(755+38+100+95)*(10400.0/8100)*(1+35/14.7);
    expect(std::abs(full.boostedHp-expectedHp)/expectedHp<.0001,"full preparation matches an independently calculated compound power budget");
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
        for(const auto& other:PartCatalog)if(part.slot==other.slot){
            if(partPerformance(part)<partPerformance(other))ranking&=int(tier)<=int(partRarity(other));
            if(tier==Rarity::Contraband)ranking&=partPerformance(part)>=partPerformance(other);
            if(partPerformance(part)==partPerformance(other))ranking&=tier==partRarity(other);
        }
        if(tier==Rarity::Contraband)++contra;
    }
    expect(ranking&&contra>=PartSlotCount,"all rarity tiers follow category performance and only the strongest are contraband");
    expect(partRarity(*findPart(3026))==partRarity(*findPart(3019)),"cosmetic prices do not create a false power rarity difference");
    expect(partRarity(*findPart(1014))==Rarity::Contraband&&partRarity(*findPart(1016))==Rarity::Common,"engine classification spans common through contraband");
    bool noDowngrade=true;int replacements=0;
    for(const auto& part:PartCatalog){Profile alternate=ultimate;equipPart(alternate,part.slot,part.id);auto result=buildVehicle(alternate);
        noDowngrade&=result.nitroHp<=full.nitroHp+.01&&result.boostedHp<=full.boostedHp+.01;++replacements;}
    expect(noDowngrade&&replacements==194,"no catalog replacement beats the maximum preparation peak power");
    // Cross every engine, ECU, induction choice and intercooler (including base).
    std::vector<int> engines,ecus{0},induction{0},coolers{0};
    for(const auto& part:PartCatalog){
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
        double target=engineData.stat*result.vehicle.curveRpmScale;
        combinationsValid&=std::isfinite(result.boostedHp)&&result.boostedHp>=engineData.stat*.9999&&result.boostedHp<=full.boostedHp+.01;
        combinationsValid&=std::abs(result.baseHp-target)/target<.0001;
        combinationsValid&=std::abs(enginePowerHp(result.vehicle,result.peakRpm,targetBoost(result.vehicle,result.peakRpm))-result.boostedHp)<1e-8;
        if(!boost)combinationsValid&=std::abs(result.baseHp-result.boostedHp)<1e-8;
        ++combinations;
    }
    expect(combinationsValid&&combinations==50400,"50400 engine/ECU/induction/intercooler combinations have consistent finite power");
    // Also cross all independent atmospheric-part choices on each engine.
    std::vector<int> intakes{0},pistons{0},exhausts{0};
    for(const auto& part:PartCatalog){if(part.slot==PartSlot::Intake)intakes.push_back(part.id);if(part.slot==PartSlot::Pistons)pistons.push_back(part.id);if(part.slot==PartSlot::Exhaust)exhausts.push_back(part.id);}
    bool supportsValid=true;int supports=0;
    for(int engine:engines)for(int intake:intakes)for(int piston:pistons)for(int exhaust:exhausts){
        Profile trial;equipPart(trial,PartSlot::Engine,engine);equipPart(trial,PartSlot::Intake,intake);equipPart(trial,PartSlot::Pistons,piston);equipPart(trial,PartSlot::Exhaust,exhaust);auto result=buildVehicle(trial);
        double target=findPart(engine)->stat+(intake?findPart(intake)->stat:0)+(piston?findPart(piston)->stat:0)+(exhaust?findPart(exhaust)->stat:0);
        supportsValid&=std::abs(result.baseHp-target)<.001;++supports;
    }
    expect(supportsValid&&supports==137984,"137984 engine/intake/piston/exhaust combinations retain their full additive power budget");
    Vehicle dynoVehicle=full.vehicle;dynoVehicle.grip=10;CarState dyno;dyno.gear=6;dyno.boostPsi=dynoVehicle.boostPsi;
    dyno.speed=full.peakRpm*2*3.141592653589793*dynoVehicle.wheelRadius/(60*dynoVehicle.ratios[5]*dynoVehicle.finalDrive);
    stepCar(dyno,dynoVehicle,{true,false,false,true},Step,0);
    expect(std::abs(dyno.powerHp-full.nitroHp)<.01,"actual driving output matches the displayed full-boost and NOS power at peak RPM");
    dyno.speed=dynoVehicle.redlineRpm*2*3.141592653589793*dynoVehicle.wheelRadius/(60*dynoVehicle.ratios[5]*dynoVehicle.finalDrive)+1;
    stepCar(dyno,dynoVehicle,{true,false,false,true},Step,0);
    expect(!dyno.nitroActive&&dyno.powerHp==0,"NOS cannot bypass the engine rev limiter");
    {std::ofstream out(root/"power-combinations.json");out<<"{\n  \"induction_combinations\": "<<combinations<<",\n  \"atmospheric_combinations\": "<<supports<<",\n  \"max_without_nos_hp\": "<<full.boostedHp<<",\n  \"max_with_nos_hp\": "<<full.nitroHp<<",\n  \"original_game_equivalence_validated\": false\n}\n";}
    std::cout<<"Native maximum: "<<full.boostedHp<<" HP, "<<full.nitroHp<<" HP with NOS; "<<combinations+supports<<" combinations checked.\n";
    auto file=root/std::filesystem::u8path("écran_車.ini");Settings s;s.mode=WindowMode::Borderless;s.width=1920;s.height=1080;s.fps=144;s.vsync=false;s.quality=Quality::Low;s.showFps=true;s.sound=false;
    std::string error;expect(saveSettings(file,s,error),"save Unicode settings path");expect(loadSettings(file)==s,"all graphics settings round trip");
    s.fps=60;s.mode=WindowMode::Fullscreen;expect(saveSettings(file,s,error),"atomic replacement of existing settings");expect(loadSettings(file)==s,"replaced graphics settings persist");
    expect(!std::filesystem::exists(file.u8string()+".tmp"),"successful save leaves no temporary file");
    {std::ofstream out(file);out<<"width=-1\nheight=99999999\nfps=not-a-number\nmode=execute-this\nquality=99\n";}
    auto invalid=loadSettings(file);expect(invalid.width==1280&&invalid.height==720&&invalid.fps==120&&invalid.mode==WindowMode::Windowed&&invalid.quality==Quality::High,"invalid settings safely fall back");
    Profile p;p.car=190;p.rim=53;p.automatic=false;p.drive=DriveLayout::All;p.bestTime=12.345678;
    expect(saveProfile(root/"profile.ini",p,error),"profile saved");auto loaded=loadProfile(root/"profile.ini",191,54);
    expect(loaded.car==190&&loaded.rim==53&&!loaded.automatic&&loaded.drive==DriveLayout::All&&std::abs(loaded.bestTime-p.bestTime)<1e-9,"garage and driving preferences persist");
    {std::ofstream out(root/"profile.ini");out<<"car=9999\nrim=-2\nbest_time=nan\ndrive=99\n";}
    auto bad=loadProfile(root/"profile.ini",191,54);expect(bad.car==190&&bad.rim==0&&bad.bestTime==0&&bad.drive==DriveLayout::Rear,"malformed profile is bounded");
    expect(easeLinear(0,5,10,2)==5&&easeLinear(2,5,10,2)==15,"reconstructed numeric easing endpoints");
    std::cout<<"PASS: "<<checks<<" checks; quarter mile "<<reference.finishTime<<" s; endless distance "<<simulated(60,true).position<<" m\n";
    return 0;
 }catch(const std::exception& e){std::cerr<<"FAIL: "<<e.what()<<'\n';return 1;}
}
