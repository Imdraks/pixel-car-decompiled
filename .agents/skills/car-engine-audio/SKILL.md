---
name: car-engine-audio
description: Generate and validate physically simulated automotive engine WAV/OGG audio with Talhasarac/engine-sim-sound-exporter, then prepare safe integration into Pixel Car Racer native. Use for requests such as “Génère les sons moteur d’une Lamborghini Aventador SVJ V12.”
---

# Car engine audio

Generate real audio files by running the existing physical Engine Sim exporter.
Do not substitute oscillators, pitch-shift an unrelated recording and call it a
simulation, or claim that simulated output is an authentic vehicle recording.
Use the user's language. Continue through execution, validation and delivery;
report precise errors and logs if export is blocked. No approval is needed for
local reversible generation already requested by the user.

## Sources and environment

Reference: https://github.com/Talhasarac/engine-sim-sound-exporter
Pinned revision: `a548360a33c6ddcc28265ac08b71b8a5f514ed3c`.
MIT license by Ange Yaghi; preserve it with exported packs and redistributed code.
The repo was cloned to `/workspace/engine-sim-sound-exporter` during initial setup.
Do not depend on that absolute path in new environments.

The reusable scripts are alongside this file in `scripts/`; sample descriptions
are in `profiles/`. Resolve their paths against this skill directory.

On Linux x86_64, first check for an already tested binary. In the current cloud:
`/workspace/native-runtime/engine-audio-exporter/build/engine-sim-exporter`.
Run `--help` and inspect `source-provenance.json` in its parent work directory.
If unavailable, run:

```bash
python scripts/setup_environment.py --work /workspace/native-runtime/car-engine-audio
```

Requires Python 3.12+, g++ with C++17, GNU Make, dpkg-deb, FFmpeg with libvorbis,
network access for pinned GitHub sources, PyPI wheels and Debian build tools.
Setup installs CMake/NumPy locally and extracts Bison/Flex/M4 below `--work`;
it never changes system packages. If prerequisites are already installed:

```bash
python scripts/build_exporter.py --work /workspace/native-runtime/car-engine-exporter
```

This exporter-only Linux build reuses upstream combustion, mechanics, solver,
convolution and synthesis. Portability adapters cover Windows include slashes,
inline constants, C++ template spelling, filesystem, missing standard includes,
POSIX aligned allocation and MSVC names. No UI, Discord, Delta Studio, Boost
library or GoogleTest dependency is needed for this target. Do not claim this
wrapper builds on Windows; upstream supports Windows via CMake `BUILD_APP=OFF`,
`DISCORD_ENABLED=OFF`, Flex/Bison. The local exporter extension adds controlled
dyno acceleration/coast sweeps, pre-PCM output headroom and an RPM tracking guard.

## Resolve the vehicle

1. Identify model/year/version, layout/cylinder count, displacement, bore/stroke,
   idle/redline, firing/bank geometry and induction. Prefer manufacturer technical
   data when available; record URLs and accessed details in the description.
   Distinguish mechanical HP from metric PS/ch. If details cannot be verified,
   mark them as estimates. Never silently substitute another model or layout.
2. Reuse bundled configurations where possible. `generate.py` supports V12, V10,
   V8, V6, I6, I5, I4, H4. Rotary, flat-six, W16 and any unrecognized geometry
   need a compatible reviewed `.mr` adapter; report this limit rather than fake it.
3. Select or create a JSON description. Required fields: `slug`, `model`, `layout`,
   `cylinders`, `litres`, `redline_rpm`, `rpm_anchors`; optional `bore_mm`,
   `stroke_mm`, `exhaust`, `turbo`, `game_engine_ids`, `approximation`.
   Always include coast (0) and full-load (100) throttle layers. The adapter
   rejects inconsistent bore/stroke/displacement. RPM anchors stay below redline.
4. Templates retain estimated cams, heads, intake/exhaust and crank geometry
   unless explicitly adapted. The SVJ example converts Ferrari 412 T2 V12 bank,
   TDC, cam and ignition offsets from 75° to 60°, with 95 × 76.4 mm displacement
   and an 8700 RPM ceiling. It remains an approximation, not a validated SVJ.
   The Huracán example inherits the LFA template's 72° geometry; do not call it an
   exact Huracán sound. Implement and test a compatible 90°/crank/firing adapter
   if exact geometry is requested. Turbo metadata does not simulate a turbine.

## Execute and verify

```bash
python scripts/generate.py \
  --description profiles/aventador-svj.json \
  --exporter-root /workspace/native-runtime/engine-audio-exporter \
  --output /workspace/deliverables/engine-audio/aventador-svj-NEW-RUN \
  --duration 3 --warmup 3
```

Use a **new output directory on every run**. Upstream deletes prior WAV files in
its output directory; this wrapper isolates it in `simulation/raw` under a newly
created directory. Never direct upstream at existing game assets. Do not overwrite
an existing audio pack or description without a checksum-verified backup.
Keep raw simulation WAVs, adapted scripts, description, manifest, commands and log.
If an attempt fails, keep it and use a new run directory after correcting it.

The output must contain startup, idle/part/full-load/coast RPM loops, acceleration,
deceleration and ignition-off in WAV and OGG. The sweeps are dyno-controlled RPM
trajectories, not a measured real-world free acceleration. Add turbo or backfire
only from a supported simulation or a licensed, appropriate audio source; otherwise
explicitly report them as absent. Never invent these effects as recovered audio.

`validation.json` must say `passed: true`. Verify all files exist and compare their
SHA-256 values with the report. The tool checks mono PCM16 44100 Hz source, duration,
non-silence, no source rail clipping, finite decoded audio, WAV/OGG headroom, and
loop endpoints. It conditions loops with a wrap overlap and 3 ms endpoint fades,
then applies only constant gain; raw files are preserved. OGG is encoded with
FFmpeg/libvorbis q6 and decoded again for analysis. Seam thresholds: WAV ≤0.01,
OGG ≤0.04 full scale. These are numerical checks, not a promise of inaudibility.
Listen if an audio playback tool is available; otherwise state that physical
speaker listening remains unverified. Inspect `RPM_CHECK` lines in `export.log`;
the exporter rejects a steady-state error exceeding max(150 RPM, 5%).

A failed run is not a successful deliverable. Report the command, phase, exact
error and retained logs; fix routine build/compiler failures autonomously and
retry. Do not describe scripts alone as generated audio.

## Prepare game integration

Read `native/game/src/game_audio.cpp`, `game_audio.hpp`, `engine_mix.hpp`,
`original_audio.hpp`, `base_audio.hpp` and `customization.cpp` before modifying
runtime audio. Original/Unbound use the same 94 IDs, with 12 engine samples in each
bank. The recovered 16 swap assignments must remain intact. New PC engines use
`pc_engines.hpp`; user-selected manual profiles have priority over AUTO.

Run `scripts/prepare_integration.py --pack PACK --output NEW_INTEGRATION_DIR`.
It copies only validated WAV/OGG into a new namespaced assets folder, includes
license/provenance and creates a machine-readable integration plan. It does not
replace or automatically activate the original game sounds. When runtime activation
is requested, add a separate manifest-driven bank with neighboring RPM interpolation,
load crossfades, pitch near anchor ratios, and distinct startup/shutdown events.
Avoid restarting streams every frame. Preserve G/Z, driving/NOS effects, audio-bank
selection, manual overrides and all source archives. Test the real mixer, source
file hashes, loops, transitions, save/load and Windows build before release.

Deliver the audio pack/ZIP, sample counts, validation results, simulation limits,
and actual integration status. Keep earlier engine-catalog work and user priorities;
do not discard it while creating this skill.
