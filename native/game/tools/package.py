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
parser.add_argument('--output',type=Path,default=Path('/workspace/deliverables/PixelCarRacerNative-Windows-x64.zip'))
args=parser.parse_args()
work=tempfile.TemporaryDirectory(dir=game/'build',prefix='native-distribution-')
stage=Path(work.name)
exe=game/'build/windows/PixelCarRacerNative.exe'
if not exe.exists():raise SystemExit('Build the Windows executable first')
shutil.copy2(exe,stage/exe.name)
shutil.copytree(game/'assets',stage/'assets',dirs_exist_ok=True)
shutil.copytree(game/'licenses',stage/'licenses',dirs_exist_ok=True)
for name in ['README.md','VALIDATION.md','PHYSICS.md','CUSTOMIZATION.md','PERFORMANCE.md','TRANSMISSION.md','EXHAUST.md','GARAGE-PC.md','CONTENT.md','ATTACHMENTS.md','VEHICLES.md','SUSPENSION.md','THIRD-PARTY.txt']:
    shutil.copy2(game/name,stage/('LISEZ-MOI.md' if name=='README.md' else name))
shutil.copy2(game.parent/'evidence/merged/catalog.json',stage/'catalogue-pieces.json')
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
