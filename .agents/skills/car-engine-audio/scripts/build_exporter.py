#!/usr/bin/env python3
"""Build the pinned upstream physical simulator as a headless Linux exporter."""
import argparse,hashlib,io,json,os,re,shutil,subprocess,tarfile,urllib.request
from pathlib import Path
def write_text(path,text):
    if not path.exists() or path.read_text()!=text:path.write_text(text)
UPSTREAM='https://github.com/Talhasarac/engine-sim-sound-exporter'
REV='a548360a33c6ddcc28265ac08b71b8a5f514ed3c'
DEPS={'csv-io':'2112c55e1e831c8f7a1b91de23722b7926ad3d00','piranha':'432f0b122bb1663b686c553c7e7269300afac3bc','simple-2d-constraint-solver':'e009f4ff1c9c4c5874e865e893cdb62e208fb2b3'}
def snapshot(url,target):
    data=urllib.request.urlopen(url,timeout=120).read();target.mkdir(parents=True,exist_ok=False)
    with tarfile.open(fileobj=io.BytesIO(data),mode='r:gz') as t:
        for m in t.getmembers():
            parts=Path(m.name).parts
            if len(parts)<2:continue
            m.name=str(Path(*parts[1:]));t.extract(m,target,filter='data')
    return hashlib.sha256(data).hexdigest()
def main():
    p=argparse.ArgumentParser(description=__doc__);p.add_argument('--work',type=Path,required=True);p.add_argument('--cmake',default='cmake');p.add_argument('--flex',default='flex');p.add_argument('--bison',default='bison');a=p.parse_args()
    a.work=a.work.resolve();a.work.mkdir(parents=True,exist_ok=True);src=a.work/'source';provenance=a.work/'source-provenance.json'
    if not src.exists():
        hashes={'exporter':snapshot(f'https://codeload.github.com/Talhasarac/engine-sim-sound-exporter/tar.gz/{REV}',src)}
        for name,rev in DEPS.items():
            dest=src/'dependencies/submodules'/name
            if dest.exists():dest.rmdir() # Empty gitlink directory from tar only.
            hashes[name]=snapshot(f'https://codeload.github.com/ange-yaghi/{name}/tar.gz/{rev}',dest)
        provenance.write_text(json.dumps({'upstream':UPSTREAM,'revision':REV,'dependencies':DEPS,'archive_sha256':hashes},indent=2)+'\n')
    # Portable filesystem adapter only; preserve upstream combustion/solver/synthesizer.
    h=src/'dependencies/submodules/piranha/include/path.h';s=h.read_text()
    if '// Forward Boost declaration' in s:
        start=s.index('// Forward Boost declaration');end=s.index('namespace piranha',start)
        s=s[:start]+'#include <filesystem>\n\n'+s[end:]
    write_text(h,s.replace('boost::filesystem','std::filesystem'))
    h=src/'dependencies/submodules/piranha/src/path.cpp';s=h.read_text().replace('<boost/filesystem.hpp>','<filesystem>').replace('boost::filesystem','std::filesystem').replace('->is_complete()','->is_absolute()');write_text(h,s)
    # Correct POSIX alignment size requirement without changing simulation equations.
    h=src/'dependencies/submodules/piranha/include/standard_allocator.h';s=h.read_text().replace('std::aligned_alloc(alignment, sizeof(t_alloc) * n)','std::aligned_alloc(alignment, ((sizeof(t_alloc) * n + alignment - 1) / alignment) * alignment)');write_text(h,s)
    h=src/'dependencies/submodules/piranha/include/language_rules.h';s=h.read_text()
    s=re.sub(r'        template<> std::string getLiteralBuiltinName.*?\n','',s)
    s=s.replace('std::string getLiteralBuiltinName() const { return ""; }','std::string getLiteralBuiltinName() const { return resolveLiteralBuiltinType(LiteralTypeLookup<NativeType>()); }');write_text(h,s)
    h=src/'dependencies/submodules/piranha/include/ir_value_constant.h';s=h.read_text().replace('        template <>\n        const piranha::native_string validateData<piranha::native_string>','        const piranha::native_string validateData');write_text(h,s)
    for h in list(src.rglob('*.cpp'))+list(src.rglob('*.h')):
        s=h.read_text().replace('extern constexpr','inline constexpr');s=re.sub(r'(#include\s+["<])([^">]+)([">])',lambda m:m[1]+m[2].replace('\\','/')+m[3],s);write_text(h,s)
    h=src/'include/gas_system.h';s=h.read_text().replace('double p_fuel = 0.0;\n            double p_inert = 1.0;\n            double p_o2 = 0.0;','double p_fuel, p_inert, p_o2;\n            constexpr Mix(double f=0, double i=1, double o=0):p_fuel(f),p_inert(i),p_o2(o) {}');write_text(h,s)
    h=src/'src/synthesizer.cpp';write_text(h,re.sub(r'(?<!std::)\bfpclassify\(', 'std::fpclassify(', h.read_text()))
    h=src/'dependencies/submodules/piranha/include/memory_management.h';write_text(h,h.read_text().replace('unsigned __int64','unsigned long long'))
    h=src/'scripting/include/channel_types.h';s=h.read_text().replace('extern inline','inline').replace('static_assert(false,','static_assert(sizeof(Type)==0,');write_text(h,s)
    h=src/'scripting/include/object_reference_node.h';s=h.read_text().replace('template <typename Type>\n        void overrideType()', 'template <typename OtherType>\n        void overrideType()').replace('LookupChannelType<Type>()','LookupChannelType<OtherType>()');write_text(h,s)
    h=src/'src/audio_export_main.cpp';s=h.read_text()
    if '// car-engine-audio extensions' not in s:
        s=s.replace('    audioParams.inputSampleNoise', '    audioParams.volume = .25f; // Output headroom before PCM16 conversion.\n    audioParams.inputSampleNoise',1)
        marker='void cleanupGeneratedOutput('
        extension=(Path(__file__).parent/'exporter_sweeps.cpp').read_text()
        s=s.replace(marker,'// car-engine-audio extensions\n'+extension+'\n'+marker,1)
        s=s.replace('    writeManifest(options.outputDirectory / "unity_audio_manifest.csv", manifest);','    exportSweep(options,baseName,&manifest,true);\n    exportSweep(options,baseName,&manifest,false);\n    writeManifest(options.outputDirectory / "unity_audio_manifest.csv", manifest);',1)
        s=s.replace('    const double speedControl = throttlePercent / 100.0;','    const double speedControl = throttlePercent / 100.0;',1)
        s=s.replace('    std::vector<int16_t> samples =\n        captureSeconds(&loaded, options.durationSeconds, true, options.loopCrossfadeSeconds);',
            '    double measured=loaded.engine->getRpm();\n    if(std::abs(measured-rpm)>std::max(150.0,rpm*.05))throw std::runtime_error("Dyno target not attained: target="+std::to_string(rpm)+" actual="+std::to_string(measured));\n    std::cout<<"RPM_CHECK target="<<rpm<<" actual="<<measured<<" throttle="<<throttlePercent<<std::endl;\n    std::vector<int16_t> samples =\n        captureSeconds(&loaded, options.durationSeconds, true, options.loopCrossfadeSeconds);',1)
        write_text(h,s)
    core=re.search(r'add_library\(engine-sim STATIC(.*?)\n\)',(src/'CMakeLists.txt').read_text(),re.S)[1]
    core='\n'.join(str(src/v) for v in re.findall(r'\b(src/[\w_]+\.cpp)\b',core))
    cmake=f'''cmake_minimum_required(VERSION 3.16)
project(car_engine_audio LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(ATG_ENGINE_SIM_PIRANHA_ENABLED __forceinline=inline)
add_compile_options(-fpermissive -includecstring -includecmath -includecstdint)
find_package(Threads REQUIRED)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
set(P "{src}/dependencies/submodules/piranha")
set(G "${{P}}/build-native")
file(MAKE_DIRECTORY "${{G}}")
FLEX_TARGET(lexer "${{P}}/flex-bison/scanner.l" "${{G}}/scanner.auto.cpp" DEFINES_FILE "${{G}}/scanner.auto.h")
BISON_TARGET(parser "${{P}}/flex-bison/specification.y" "${{G}}/parser.auto.cpp" DEFINES_FILE "${{G}}/parser.auto.h")
ADD_FLEX_BISON_DEPENDENCY(lexer parser)
include_directories("{src}/include" "{src}/scripting/include" "{src}/dependencies/submodules" "${{P}}/include" "${{P}}/dependencies/libraries/flex/include" "${{G}}")
file(GLOB P_SRC "${{P}}/src/*.cpp")
file(GLOB SCS_SRC "{src}/dependencies/submodules/simple-2d-constraint-solver/src/*.cpp")
file(GLOB SCRIPT_SRC "{src}/scripting/src/*.cpp")
add_library(piranha STATIC ${{P_SRC}} ${{FLEX_lexer_OUTPUTS}} ${{BISON_parser_OUTPUTS}})
add_library(scs STATIC ${{SCS_SRC}})
add_library(engine STATIC {core})
add_library(interpreter STATIC ${{SCRIPT_SRC}})
target_link_libraries(engine PUBLIC scs Threads::Threads)
target_link_libraries(interpreter PUBLIC piranha engine)
add_executable(engine-sim-exporter "{src}/src/audio_export_main.cpp")
target_link_libraries(engine-sim-exporter PRIVATE engine interpreter)
'''
    (a.work/'CMakeLists.txt').write_text(cmake)
    subprocess.run([a.cmake,'-S',str(a.work),'-B',str(a.work/'build'),'-DCMAKE_BUILD_TYPE=Release','-DFLEX_EXECUTABLE='+str(Path(a.flex).resolve() if '/' in a.flex else a.flex),'-DBISON_EXECUTABLE='+str(Path(a.bison).resolve() if '/' in a.bison else a.bison)],check=True)
    subprocess.run([a.cmake,'--build',str(a.work/'build'),'--parallel','4'],check=True)
    print(a.work/'build/engine-sim-exporter')
if __name__=='__main__':main()
