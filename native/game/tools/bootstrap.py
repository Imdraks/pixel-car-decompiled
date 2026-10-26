#!/usr/bin/env python3
"""Install pinned verified native build tools under a caller-owned directory."""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import tarfile
import tempfile
import urllib.request
import zipfile

game=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--root',type=Path,default=Path('/workspace/native-runtime'))
args=parser.parse_args();root=args.root.resolve();root.mkdir(parents=True,exist_ok=True)
cache=root/'downloads';cache.mkdir(exist_ok=True)
for item in json.loads((game/'toolchain.json').read_text()):
    archive=cache/item['archive']
    if not archive.exists():
        temp=archive.with_suffix('.download')
        urllib.request.urlretrieve(item['url'],temp)
        if hashlib.file_digest(temp.open('rb'),'sha256').hexdigest()!=item['sha256']:raise SystemExit('Checksum mismatch: '+item['name'])
        temp.rename(archive)
    if hashlib.file_digest(archive.open('rb'),'sha256').hexdigest()!=item['sha256']:raise SystemExit('Cached checksum mismatch: '+item['name'])
    with tempfile.TemporaryDirectory(dir=root,prefix='native-tool-') as scratch:
        staging=Path(scratch)
        if archive.suffix=='.zip':
            with zipfile.ZipFile(archive) as z:
                for name in z.namelist():
                    if not (staging/name).resolve().is_relative_to(staging):raise ValueError('Unsafe archive path')
                z.extractall(staging)
        else:
            with tarfile.open(archive) as t:t.extractall(staging,filter='data')
        for p in sorted(staging.rglob('*')):
            target=root/p.relative_to(staging)
            if not target.resolve().is_relative_to(root):raise ValueError('Target escapes tool root')
            if p.is_dir():target.mkdir(exist_ok=True,parents=True);continue
            target.parent.mkdir(parents=True,exist_ok=True)
            if p.is_symlink():
                if target.is_symlink() and target.readlink()==p.readlink():continue
                if target.exists() or target.is_symlink():raise FileExistsError(target)
                target.symlink_to(p.readlink())
            elif target.exists():
                if hashlib.file_digest(target.open('rb'),'sha256').digest()!=hashlib.file_digest(p.open('rb'),'sha256').digest():raise FileExistsError('Refusing to overwrite changed tool file: '+str(target))
            else:shutil.copy2(p,target)
    print('Verified and available:',item['name'],flush=True)
