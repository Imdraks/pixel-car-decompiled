#!/usr/bin/env python3
"""Package exact extracted Unbound atlas pixels; generate native frame metadata."""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import shutil
import struct
import zlib

GAME=Path(__file__).resolve().parents[1]
parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--textures',type=Path,default=Path('/workspace/windows-port/mod-textures'))
parser.add_argument('--audio',type=Path,default=Path('/workspace/windows-port/recovered/assets'))
parser.add_argument('--backgrounds',type=Path,default=Path('/workspace/native-runtime/backgrounds.json'))
args=parser.parse_args()
assets=GAME/'assets';assets.mkdir(parents=True,exist_ok=True)
sprites=json.loads((args.textures/'sprites.json').read_text())['sprites']
textures=json.loads((args.textures/'textures.json').read_text())
selected={'sp_car':'cars','sp_rims':'rims','sp_garage':'garages','sp_title_background':'titleBackground','sp_title_logo2':'logos'}
needed=set();groups={}
for name,group in selected.items():
    sprite=next(s for s in sprites if s['name']==name)
    groups[group]=sprite
    needed.update(f['texture_id'] for f in sprite['frames'] if f)
backgrounds=json.loads(args.backgrounds.read_text())
for name,group in {'bg_sky':'sky','bg_mountain_1':'mountains','bg_city_l1':'cityFar','bg_city_l2':'cityNear','bg_fuji_Treeline_L2':'trees','bg_woodfence_1':'fence'}.items():
    b=next(b for b in backgrounds if b['name']==name)
    groups[group]={'width':b['w'],'height':b['h'],'frames':[{'texture_id':b['texture_id'],'source_rect':[b['x'],b['y'],b['w'],b['h']],'target_offset':[0,0]}]}
    needed.add(b['texture_id'])

def decode_rgba(file):
    b=file.read_bytes();w,h,depth,kind,_,_,interlace=struct.unpack('>IIBBBBB',b[16:29])
    if (depth,kind,interlace)!=(8,6,0):raise ValueError('Expected noninterlaced RGBA8 atlas')
    offset=8;compressed=[]
    while offset<len(b):
        size=struct.unpack_from('>I',b,offset)[0];tag=b[offset+4:offset+8]
        if tag==b'IDAT':compressed.append(b[offset+8:offset+8+size])
        offset+=size+12
    raw=zlib.decompress(b''.join(compressed));stride=w*4;rows=[];prev=bytearray(stride)
    for y in range(h):
        filt=raw[y*(stride+1)];row=bytearray(raw[y*(stride+1)+1:(y+1)*(stride+1)])
        for x in range(stride):
            a=row[x-4] if x>=4 else 0;bb=prev[x];c=prev[x-4] if x>=4 else 0
            if filt==1:predict=a
            elif filt==2:predict=bb
            elif filt==3:predict=(a+bb)//2
            elif filt==4:
                p=a+bb-c;pa,pb,pc=abs(p-a),abs(p-bb),abs(p-c)
                predict=a if pa<=pb and pa<=pc else bb if pb<=pc else c
            elif filt==0:predict=0
            else:raise ValueError('Invalid PNG filter')
            row[x]=(row[x]+predict)&255
        rows.append(row);prev=row
    return rows

decoded={}
def wheels(frame):
    # Only infer visual wheel cutouts; this does not recover vehicle physics data.
    tid=frame['texture_id']
    if tid not in decoded:decoded[tid]=decode_rgba(args.textures/frame['file'])
    rows=decoded[tid];sx,sy,w,h=frame['source_rect'];dx,dy=frame['target_offset']
    white=set()
    for y in range(h//2,h):
        for x in range(w):
            r,g,b,a=rows[sy+y][(sx+x)*4:(sx+x)*4+4]
            if min(r,g,b)>=245 and a>=220:white.add((x,y))
    components=[]
    while white:
        start=white.pop();todo=[start];points=[start]
        while todo:
            x,y=todo.pop()
            for q in [(x-1,y),(x+1,y),(x,y-1),(x,y+1)]:
                if q in white:white.remove(q);todo.append(q);points.append(q)
        xs=[p[0] for p in points];ys=[p[1] for p in points]
        bw,bh=max(xs)-min(xs)+1,max(ys)-min(ys)+1
        if len(points)>=12 and bw>=6 and bh>=5 and max(ys)>=h-3:
            components.append((dx+(min(xs)+max(xs))/2,dy+max(ys)-min(9,bh/2),min(bw,bh)))
    components.sort()
    if len(components)>=2:
        left,right=components[0],components[-1]
        return [left[0],right[0],(left[1]+right[1])/2,max(6,min(13,(left[2]+right[2])/4))]
    return [dx+w*.18,dx+w*.82,dy+h-7,9]

manifest=[]
for tid in sorted(needed):
    t=textures[tid];p=args.textures/t['file'];digest=hashlib.file_digest(p.open('rb'),'sha256').hexdigest()
    if digest!=t['sha256']:raise ValueError('Atlas digest mismatch: '+p.name)
    shutil.copy2(p,assets/p.name);manifest.append({'file':p.name,'sha256':digest})

header=['// Generated from the supplied Unbound sprite metadata. Do not edit.', '#pragma once',
        'namespace pcr::art {',
        'struct Frame { int atlas,x,y,w,h,dx,dy,canvasW,canvasH; };',
        'struct Wheels { float rear,front,y,radius; };']
for group,sprite in groups.items():
    header.append('inline const Frame '+group+'[] = {')
    for f in sprite['frames']:
        if f is None:header.append('{-1,0,0,0,0,0,0,0,0},');continue
        values=[f['texture_id'],*f['source_rect'],*f['target_offset'],sprite['width'],sprite['height']]
        header.append('{'+','.join(map(str,values))+'},')
    header.append('};')
header.append('inline const Wheels wheelPositions[] = {')
for frame in groups['cars']['frames']:
    values=wheels(frame)
    header.append('{'+','.join(f'{v:.3f}f' for v in values)+'},')
header+=['};','inline const int atlasIds[] = {'+','.join(map(str,sorted(needed)))+'};','}']
(GAME/'src/art.hpp').write_text('\n'.join(header)+'\n')

font=Path('/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf')
if not font.exists():raise SystemExit('DejaVuSans.ttf is required for French UI text')
shutil.copy2(font,assets/'ui.ttf')
shutil.copy2('/usr/share/doc/fonts-dejavu-core/copyright',assets/'FONT-LICENSE.txt')
for name in ['snd_town.ogg','snd_button.ogg']:
    shutil.copy2(args.audio/name,assets/name)
manifest.append({'file':'ui.ttf','sha256':hashlib.file_digest(font.open('rb'),'sha256').hexdigest()})
(assets/'provenance.json').write_text(json.dumps({'source':'Supplied Unbound APK; extracted atlas pixels preserved',
  'apk_sha256':'2cc9c22512815321dd26e6ed5d61a11336f1b5cd88c75ae1874ed921c26e9802',
  'car_frames':len(groups['cars']['frames']),'rim_frames':len(groups['rims']['frames']),
  'wheel_positions':'Heuristic visual reconstruction, not recovered original coordinates',
  'files':manifest},indent=2)+'\n')
print(f"Prepared {len(needed)} atlases, {len(groups['cars']['frames'])} cars, {len(groups['rims']['frames'])} rims")
