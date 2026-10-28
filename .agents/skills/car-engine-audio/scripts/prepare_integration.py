#!/usr/bin/env python3
"""Prepare an isolated game assets folder and integration plan from a validated pack."""
import argparse,hashlib,json,shutil,re
from pathlib import Path
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--pack',type=Path,required=True);p.add_argument('--output',type=Path,required=True);a=p.parse_args();pack=a.pack.resolve();report=json.loads((pack/'validation.json').read_text());manifest=json.loads((pack/'manifest.json').read_text());vehicle=json.loads((pack/'vehicle.json').read_text())
if report.get('passed') is not True:raise SystemExit('Audio pack has not passed validation')
if not re.fullmatch('[a-z0-9_]+',vehicle['slug']):raise ValueError('Invalid output slug')
# Check everything before creating the destination.
for row in report['files']:
 for kind in ['wav','ogg']:
  name=row[kind]
  if Path(name).name!=name:raise ValueError('Unsafe pack path')
  if hashlib.sha256((pack/name).read_bytes()).hexdigest()!=row[kind+'_sha256']:raise ValueError('Audio digest mismatch: '+name)
a.output=a.output.resolve();a.output.mkdir(parents=True,exist_ok=False);slug=vehicle['slug'];target=a.output/'assets/engine-packs'/slug;target.mkdir(parents=True)
for row in report['files']:
 for kind in ['wav','ogg']:shutil.copy2(pack/row[kind],target/row[kind])
for name in ['manifest.json','vehicle.json','validation.json','ENGINE-SIM-LICENSE.txt']:shutil.copy2(pack/name,target/name)
plan={'schema':1,'runtime_activated':False,'source_files_replaced':False,'original_bank_files_untouched':True,'game_engine_ids':manifest['game_engine_ids'],'assets_relative_directory':'engine-packs/'+slug,'manifest':'manifest.json','loop_strategy':{'rpm':'interpolate adjacent anchors, pitch=actual_rpm/anchor_rpm with bounded ratios','load':'crossfade coast/part/full layers, preserve phase and gain headroom','events':'startup on G start, ignition_off on G stop, acceleration/deceleration are optional previews'},'needed_runtime_changes':['Add separate manifest-driven bank for AUTO PC engine assignments','Preserve existing manual sound overrides and Original/Unbound fallback','Load and keep neighbouring streams alive, crossfade without per-frame restarts','Re-run source audio hashes, real mixer and Windows validation before activation']}
(a.output/'integration-plan.json').write_text(json.dumps(plan,indent=2)+'\n');print(a.output)
