#!/usr/bin/env python3
"""Build a Windows distribution from the existing, tested native executable."""
import argparse
import datetime
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import tempfile
import zipfile

game=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--audio-packs-dir',type=Path,help='Optional validated standalone simulation ZIPs, copied without changing game audio')
parser.add_argument('--output',type=Path,default=Path('/workspace/deliverables/PixelCarRacerNative-Windows-x64.zip'))
args=parser.parse_args()
work=tempfile.TemporaryDirectory(dir=game/'build',prefix='native-distribution-')
stage=Path(work.name)
exe=game/'build/windows/PixelCarRacerNative.exe'
if not exe.exists():raise SystemExit('Build the Windows executable first')
shutil.copy2(exe,stage/exe.name)
for slug in ['gm_ls_v8','amg_gt63s_2021','huracan_v10','aventador_svj_v12','f1_v6','ford_coyote_v8']:
    folder=game/'assets/engine-packs'/slug
    manifest=json.loads((folder/'manifest.json').read_text())
    for clip in manifest['clips']:
        if not (folder/clip['ogg']).is_file():raise RuntimeError('Missing active simulated audio: '+clip['ogg'])
shutil.copytree(game/'assets',stage/'assets',dirs_exist_ok=True)
if args.audio_packs_dir:
    destination=stage/'Audio-Simulation';destination.mkdir()
    for pack in sorted(args.audio_packs_dir.glob('*.zip')):
        with zipfile.ZipFile(pack) as archive:
            if archive.testzip() is not None:raise RuntimeError('Audio archive CRC failed')
            report=json.loads(archive.read('validation.json'))
            if report.get('passed') is not True:raise RuntimeError('Audio pack validation missing')
        shutil.copy2(pack,destination/pack.name)
shutil.copytree(game/'licenses',stage/'licenses',dirs_exist_ok=True)
for name in ['README.md','REVUE-CONTENU.md','CLASSIFICATION-JANTES.md','UNDERGROUND.md','RIDES-NAVIGATION.md','CINEMATIC-UI.md','SHOWROOM.md','VEHICLES-GARAGE.md','NFS-CATALOGUE.md','VOLUMES.md','TURBOS.md','SAVED-CARS.md','PC-ENGINES.md','AUDIO-SIMULATION.md','ENGINE-AUDIO.md','AUDIO-MIX.md','VALIDATION.md','PHYSICS.md','CUSTOMIZATION.md','CUSTOMIZATION-COMPLETE.md','PERFORMANCE.md','TRANSMISSION.md','EXHAUST.md','GARAGE-PC.md','CONTENT.md','ATTACHMENTS.md','VEHICLES.md','SUSPENSION.md','DRAG.md','THIRD-PARTY.txt']:
    shutil.copy2(game/name,stage/('LISEZ-MOI.md' if name=='README.md' else name))
shutil.copy2(game/'underground-catalog.json',stage/'catalogue-Underground.json')
shutil.copy2(game/'catalogue-review.json',stage/'revue-catalogue.json')
shutil.copy2(game/'rim-styles.json',stage/'classification-jantes.json')
shutil.copy2(game/'vehicles.json',stage/'catalogue-voitures.json')
shutil.copy2(game/'nfs-catalog.json',stage/'catalogue-NFS.json')
shutil.copy2(game/'nfs-correspondances.csv',stage/'correspondances-NFS.csv')
shutil.copy2(game/'pc-turbos.json',stage/'turbos-extension-pc.json')
shutil.copy2(game.parent/'evidence/pc-turbos/research.json',stage/'recherche-turbos.json')
shutil.copy2(game/'pc-engines.json',stage/'moteurs-extension-pc.json')
shutil.copy2(game.parent/'evidence/merged/catalog.json',stage/'catalogue-pieces.json')
shutil.copy2(game.parent/'evidence/merged/engine-audio-assignments.json',stage/'associations-moteurs-sons.json')
shutil.copy2(game.parent/'evidence/merged/customization-render.json',stage/'personnalisation-source.json')
shutil.copy2(game.parent/'evidence/merged/drag-physics/drag-physics-source.json',stage/'drag-physique-source.json')
shutil.copy2(game.parent/'evidence/merged/wheelie-bars.json',stage/'wheelie-bars-source.json')
shutil.copy2(game.parent/'evidence/merged/stock-vehicles.json',stage/'fiches-vehicules-source.json')
shutil.copy2(game.parent/'evidence/merged/vehicle-identities.json',stage/'identification-vehicules.json')
shutil.copy2(game.parent/'evidence/merged/vehicle-identities.csv',stage/'identification-vehicules.csv')
shutil.copy2(game/'validation/native-physics-baseline.json',stage/'native-physics-baseline.json')
(stage/'Mode-secours.cmd').write_bytes(b'@echo off\r\nstart "" "%~dp0PixelCarRacerNative.exe" --safe-mode\r\n')
(stage/'Mode-libre.cmd').write_bytes(b'@echo off\r\nstart "" "%~dp0PixelCarRacerNative.exe" --free-drive\r\n')
digest=hashlib.file_digest(exe.open('rb'),'sha256').hexdigest()
(stage/'SHA256SUMS.txt').write_text(digest+'  PixelCarRacerNative.exe\n')
commit=subprocess.check_output(['git','rev-parse','HEAD'],cwd=game,text=True).strip()
(stage/'BUILD-INFO.json').write_text(json.dumps({'version':(game/'VERSION').read_text().strip(),'source_commit':commit,
 'target':'windows-x86_64','engine':'Native C++17 and Raylib 6.2; no Android runtime',
 'scope':'Reconstructed free-drive mode with Unbound resources, not a complete original-game port',
 'exe_sha256':digest,'created_utc':datetime.datetime.now(datetime.timezone.utc).isoformat(),
 'toolchain':json.loads((game/'toolchain.json').read_text())},indent=2)+'\n')
args.output.parent.mkdir(exist_ok=True,parents=True)
with zipfile.ZipFile(args.output,'w',compression=zipfile.ZIP_DEFLATED,compresslevel=9) as z:
    for p in sorted(stage.rglob('*')):
        if p.is_file():z.write(p,p.relative_to(stage))
with zipfile.ZipFile(args.output) as z:
    bad=z.testzip()
    if bad:raise SystemExit('Corrupted packaged file: '+bad)
h=hashlib.file_digest(args.output.open('rb'),'sha256').hexdigest()
args.output.with_suffix(args.output.suffix+'.sha256').write_text(h+'  '+args.output.name+'\n')
print(json.dumps({'archive':str(args.output),'size':args.output.stat().st_size,'sha256':h,'exe_sha256':digest,'source_commit':commit}))
work.cleanup()
