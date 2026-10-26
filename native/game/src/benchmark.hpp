#pragma once
#include <filesystem>
namespace pcr {
// Writes deterministic native-model measurements into a new directory.
// Refuses to overwrite an existing directory, settings, or player profile.
void writePhysicsBenchmark(const std::filesystem::path& output);
}
