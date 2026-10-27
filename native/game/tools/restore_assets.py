#!/usr/bin/env python3
"""Restore verified v0.9.1 assets without executing an APK or overwriting edits."""
import argparse
import hashlib
from pathlib import Path
import urllib.request
import zipfile

parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--destination',type=Path,required=True)
parser.add_argument('--cache',type=Path,default=Path('/workspace/native-runtime/downloads/native-release-0.9.1.zip'))
args=parser.parse_args()
expected='9a5a6c8c2cf8ae8d48b8cd1665f8fd3eb72b16ffcd3a8d1f893810846c291f13'
url='https://github.com/Imdraks/pixel-car-decompiled/releases/download/v0.9.1-native-preview/PixelCarRacerNative-Windows-x64.zip'
args.cache.parent.mkdir(parents=True,exist_ok=True)
if not args.cache.exists():
    temp=args.cache.with_suffix('.download')
    urllib.request.urlretrieve(url,temp)
    if hashlib.file_digest(temp.open('rb'),'sha256').hexdigest()!=expected:raise SystemExit('Downloaded native release digest mismatch')
    temp.rename(args.cache)
if hashlib.file_digest(args.cache.open('rb'),'sha256').hexdigest()!=expected:raise SystemExit('Cached native release digest mismatch')
root=args.destination.resolve();root.mkdir(parents=True,exist_ok=True)
count=0
with zipfile.ZipFile(args.cache) as z:
    for info in z.infolist():
        if not info.filename.startswith('assets/') or info.is_dir():continue
        relative=Path(info.filename).relative_to('assets')
        target=root/relative
        if not target.resolve().is_relative_to(root):raise SystemExit('Invalid resource path')
        data=z.read(info)
        if target.exists() and target.read_bytes()!=data:raise FileExistsError('Refusing to overwrite changed resource: '+str(target))
        target.parent.mkdir(parents=True,exist_ok=True)
        if not target.exists():target.write_bytes(data)
        count+=1
print('Verified native release; restored or reused',count,'resource files.')
