#!/usr/bin/env python3
"""Package exact extracted Unbound atlas pixels; generate native frame metadata."""
import argparse
import collections
import hashlib
import json
from pathlib import Path
import shutil
import struct
import statistics
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
selected={'sp_car':'cars','sp_rims':'rims','sp_tire_0':'tires','sp_wheelwell':'wheelWells','sp_flame':'flames','sp_smoke':'smoke','sp_smoke2':'smoke2','sp_sparks':'sparks','sp_nos':'nosIcons','sp_garage':'garages','sp_title_background':'titleBackground','sp_title_logo2':'logos'}
needed=set();groups={}
for name,group in selected.items():
    sprite=next(s for s in sprites if s['name']==name)
    if group=='wheelWells':sprite={**sprite,'frames':sprite['frames'][:1]}
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
wheel_audit=[]
def wheels(frame,index):
    # The supplied car sprite origin is the rear axle anchor. Front axle spacing
    # is derived from the transparent arch, never from overall body width/colour.
    sprite=groups['cars'];rear,cy=sprite['origin'];tid=frame['texture_id']
    if tid not in decoded:decoded[tid]=decode_rgba(args.textures/frame['file'])
    rows=decoded[tid];sx,sy,w,h=frame['source_rect'];dx,dy=frame['target_offset']
    if index==182:
        # Special Unbound sled/box sprite has no wheel openings. Do not invent wheels.
        wheel_audit.append({'car':index+1,'visible':False,'reason':'Special body without wheel arches'})
        return [rear,rear,cy,0]
    def alpha(x,y):
        if not(dx<=x<dx+w and dy<=y<dy+h):return 0
        return rows[sy+y-dy][(sx+x-dx)*4+3]
    candidates=[]
    for y in range(cy-14,cy+1):
        start=None
        for x in range(dx,dx+w):
            if alpha(x,y)<128:
                if start is None:start=x
            elif start is not None:
                center=(start+x)/2
                if start>dx and 5<=x-start<=44 and rear+30<=center<=sprite['width']-10:
                    candidates.append((center,y))
                start=None
    clusters=[]
    for center,y in candidates:
        group=next((g for g in clusters if abs(statistics.median(p[0] for p in g)-center)<=2.5),None)
        if group is None:clusters.append([(center,y)])
        else:group.append((center,y))
    if not clusters:raise ValueError(f'No front wheel arch for body {index+1}; explicit review required')
    best=max(clusters,key=lambda g:len({p[1] for p in g}))
    support=len({p[1] for p in best})
    if support<3:raise ValueError(f'Ambiguous wheel arch for body {index+1}; explicit review required')
    front=statistics.median(p[0] for p in best)
    # Original 62x62 wheel artwork is rendered at half the car sprite scale.
    # Its visible tyre is 50px wide, so the actual outside radius is 12.5px.
    radius=12.5
    wheel_audit.append({'car':index+1,'visible':True,'rear':rear,'front':front,'y':cy,
                        'radius':radius,'arch_support_rows':support})
    return [rear,front,cy,radius]

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
for index,frame in enumerate(groups['cars']['frames']):
    values=wheels(frame,index)
    header.append('{'+','.join(f'{v:.3f}f' for v in values)+'},')
header+=['};','inline const int atlasIds[] = {'+','.join(map(str,sorted(needed)))+'};','}']
(GAME/'src/art.hpp').write_text('\n'.join(header)+'\n')
(GAME/'validation/wheel-anchors.json').write_text(json.dumps({'method':'Sprite rear origin and transparent front wheel arches; no width fallback', 'bodies':wheel_audit},indent=2)+'\n')

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
  'wheel_positions':'Rear axle from sprite origin; front axle from transparent arches; see validation/wheel-anchors.json; special archless body has no added wheels',
  'files':manifest},indent=2)+'\n')
print(f"Prepared {len(needed)} atlases, {len(groups['cars']['frames'])} cars, {len(groups['rims']['frames'])} rims")
