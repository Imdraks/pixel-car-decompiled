// Control-only extension: use the upstream physics solver and synthesizer unchanged.
void exportSweep(const ExportOptions& options,const std::string& baseName,
                 std::vector<ClipManifestRow>* manifest,bool acceleration) {
    LoadedSimulation loaded=loadSimulation(options.scriptPath);
    const int low=options.rpmTargets.empty()?1000:*std::min_element(options.rpmTargets.begin(),options.rpmTargets.end());
    const int high=options.rpmTargets.empty()?int(units::toRpm(loaded.engine->getRedline())*.95):*std::max_element(options.rpmTargets.begin(),options.rpmTargets.end());
    prepareSteadyRpm(&loaded,acceleration?low:high,options.warmupSeconds,acceleration?1.0:0.0);
    std::vector<int16_t> samples;
    for(double t=0;t<options.durationSeconds;t+=OfflineFrameSeconds){
        double progress=std::clamp(t/options.durationSeconds,0.0,1.0);
        int rpm=int(acceleration?low+(high-low)*progress:high-(high-low)*progress);
        setRunningState(&loaded,acceleration?1.0:0.0,false,true,rpm);
        double end=std::min(options.durationSeconds,t+OfflineFrameSeconds);
        advanceSimulation(&loaded,end-t,&samples,int(std::lround(end*AudioSampleRate)));
    }
    samples.resize(size_t(std::lround(options.durationSeconds*AudioSampleRate)));
    std::string kind=acceleration?"acceleration":"deceleration";
    exportClip(options.outputDirectory/(baseName+"_"+kind+".wav"),samples,manifest,kind,0,acceleration?100:0,false,options.durationSeconds);
    destroySimulation(&loaded);
}
