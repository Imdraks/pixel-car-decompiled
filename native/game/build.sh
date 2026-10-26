#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
task_runtime="${PCR_NATIVE_TOOL_ROOT:-/workspace/native-runtime}"
ray_linux="$task_runtime/raylib-6.2_linux_amd64"
ray_windows="$task_runtime/raylib-6.2_win64_mingw-w64"
zig_bin="$task_runtime/zig-x86_64-linux-0.17.0/zig"
export ZIG_GLOBAL_CACHE_DIR="$task_runtime/zig-cache"
mkdir -p build/linux build/windows build/test-data
g++ -std=c++17 -O2 -Wall -Wextra -Werror -Isrc tests/core_tests.cpp src/model.cpp src/platform.cpp -o build/linux/core-tests
build/linux/core-tests build/test-data
g++ -std=c++17 -O2 -Wall -Wextra -Werror -Isrc -I"$ray_linux/include" src/main.cpp src/model.cpp src/platform.cpp \
    "$ray_linux/lib/libraylib.a" -l:libGL.so.1 -l:libX11.so.6 -lpthread -ldl -lm -lrt -o build/linux/PixelCarRacerNative
"$zig_bin" c++ -target x86_64-windows-gnu -std=c++17 -O2 -s -static -Isrc -I"$ray_windows/include" \
    src/main.cpp src/model.cpp src/platform.cpp "$ray_windows/lib/libraylib.a" \
    -lopengl32 -lgdi32 -lwinmm -lshell32 -luser32 -o build/windows/PixelCarRacerNative.exe -Wl,--subsystem,windows
"$zig_bin" c++ -target x86_64-windows-gnu -std=c++17 -O2 -s -static -Isrc \
    tests/core_tests.cpp src/model.cpp src/platform.cpp -luser32 -o build/windows/core-tests.exe
printf 'Linux and Windows native builds completed.\n'
