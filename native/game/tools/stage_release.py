#!/usr/bin/env python3
"""Stage a verified native candidate on an existing draft, then dispatch Windows CI.

Large cloud-proxy uploads are split into 4 MiB assets. Published releases and
existing assets with different bytes are never modified by this helper.
"""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import subprocess
import urllib.parse
import urllib.request
import zipfile


def gh_json(*args):
    return json.loads(subprocess.check_output(['gh',*args],text=True))


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--repo',default='Imdraks/pixel-car-decompiled')
    parser.add_argument('--tag',required=True)
    parser.add_argument('--archive',type=Path,required=True)
    parser.add_argument('--core',type=Path,required=True)
    args=parser.parse_args()
    if not re.fullmatch(r'v[0-9]+\.[0-9]+\.[0-9]+-native-preview',args.tag):
        raise SystemExit('Invalid native preview tag')
    if args.archive.name!='PixelCarRacerNative-Windows-x64.zip':raise SystemExit('Unexpected archive name')
    with zipfile.ZipFile(args.archive) as archive:
        if archive.testzip():raise SystemExit('Archive CRC failure')
        info=json.loads(archive.read('BUILD-INFO.json'))
        if 'v'+info['version']!=args.tag:raise SystemExit('Tag and packaged version differ')
        if hashlib.sha256(archive.read('PixelCarRacerNative.exe')).hexdigest()!=info['exe_sha256']:
            raise SystemExit('Packaged EXE identity mismatch')
    # The tags endpoint can return 404 for an untagged draft; list authenticated releases.
    releases=gh_json('api',f'repos/{args.repo}/releases?per_page=100')
    release=next((r for r in releases if r['tag_name']==args.tag),None)
    if release is None:raise SystemExit('Create the native draft release before staging')
    if not release['draft']:raise SystemExit('Refusing to modify a published release')
    if release['target_commitish']!=info['source_commit']:raise SystemExit('Draft target and packaged source commit differ')
    existing={a['name']:a for a in release['assets']}
    token=os.environ.get('GH_RELEASE_TOKEN') or os.environ.get('GH_TOKEN')
    if not token:raise SystemExit('A configured GitHub release credential is required')
    def upload(name,data):
        digest=hashlib.sha256(data).hexdigest()
        if name in existing:
            old=existing[name]
            if old.get('digest')!='sha256:'+digest or old['size']!=len(data):
                raise RuntimeError('Refusing to replace a different draft asset: '+name)
            print('Verified existing asset:',name,flush=True);return
        url=f'https://uploads.github.com/repos/{args.repo}/releases/{release["id"]}/assets?name='+urllib.parse.quote(name)
        request=urllib.request.Request(url,data=data,headers={'Authorization':'Bearer '+token,
            'Content-Type':'application/octet-stream','User-Agent':'PixelCarNativeRelease'},method='POST')
        with urllib.request.urlopen(request,timeout=90) as response:asset=json.load(response)
        if asset['size']!=len(data) or asset.get('digest')!='sha256:'+digest:
            raise RuntimeError('Remote upload digest mismatch: '+name)
        print('Uploaded and verified:',name,len(data),flush=True)
    core=args.core.read_bytes()
    upload('Core-Tests-Windows.exe',core)
    archive_digest=hashlib.file_digest(args.archive.open('rb'),'sha256').hexdigest()
    count=0
    with args.archive.open('rb') as source:
        while part:=source.read(4*1024*1024):
            upload(args.archive.name+f'.part-{count:03d}',part);count+=1
    state={'tag':args.tag,'release_id':release['id'],'source_commit':info['source_commit'],
           'archive_sha256':archive_digest,'core_sha256':hashlib.sha256(core).hexdigest(),'part_count':count}
    args.archive.with_name('staging.json').write_text(json.dumps(state,indent=2)+'\n')
    subprocess.run(['gh','workflow','run','publish-native-release.yml','--repo',args.repo,'--ref','main',
        '--field','release_tag='+args.tag,'--field','archive_sha256='+archive_digest,
        '--field','core_sha256='+state['core_sha256'],'--field','part_count='+str(count)],check=True)
    print('Windows validation dispatched; publication requires all checks to pass.',flush=True)


if __name__=='__main__':main()
