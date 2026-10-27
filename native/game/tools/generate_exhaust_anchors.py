#!/usr/bin/env python3
"""Derive native exhaust mounts from body alpha and explicit original pipe mouths."""
from pathlib import Path
import json,math
from PIL import Image
root=Path(__file__).resolve().parents[1];source=Path('/workspace/windows-port/mod-textures')
sprites=json.loads((source/'sprites.json').read_text())['sprites'];cache={}
def crop(f):
 if f['file'] not in cache:cache[f['file']]=Image.open(source/f['file']).convert('RGBA')
 x,y,w,h=f['source_rect'];return cache[f['file']].crop((x,y,x+w,y+h))
cars=next(s for s in sprites if s['name']=='sp_car');ex=next(s for s in sprites if s['name']=='sp_car_exhaust');flames=next(s for s in sprites if s['name']=='sp_flame')
wheels=json.loads((root/'validation/wheel-anchors.json').read_text())['bodies'];mounts=[]
for i,f in enumerate(cars['frames']):
 pic=crop(f);dx,dy=f['target_offset'];w,h=pic.size
 def solid(x,y):return dx<=x<dx+w and dy<=y<dy+h and pic.getpixel((x-dx,y-dy))[3]>128
 rear,front=62,wheels[i].get('front',dx+w*.75);sillx=(rear+front)*.5;hoodx=front-12
 hoodys=[y for y in range(dy,dy+h) if solid(round(hoodx),y)]
 sillys=[y for y in range(dy,dy+h) if solid(round(sillx),y)]
 hood=min(hoodys) if hoodys else dy+h*.45;sill=max(sillys) if sillys else dy+h-1
 y=min(63,dy+h-1);edges=[x for x in range(dx,min(dx+w,56)) if solid(x,y)]
 if not edges:
  edges=[x for yy in range(max(dy,y-4),min(dy+h,y+4)) for x in range(dx,min(dx+w,56)) if solid(x,yy)]
 rearx=min(edges) if edges else dx
 mounts.append({'car':i+1,'rear':[rearx,y+2],'hood':[hoodx,hood+2],'side':[sillx,sill+2]})
layouts=[]
# Long source pipes have real visible upper tips; miniature side outlets are
# placed below the sill. These are native mounts, not recovered YYC offsets.
tops={11:[(39.5,46)],18:[(39.5,45)],32:[(43.5,4)],33:[(22.5,10)],34:[(41.5,6),(46.5,2)],35:[(26.5,21)],36:[(30.5,37)],37:[(35.5,15),(37.5,4)],38:[(33.5,7)],39:[(33.5,23),(36.5,12),(38.5,4)]}
side={40:[(57.5,57),(61.5,57)],41:[(59.5,62)],44:[(59.5,63),(63.5,63)],45:[(58.5,60.5),(63.5,60.5)],46:[(59,62.5)],47:[(59,62.5),(64,62.5)]}
for i,f in enumerate(ex['frames']):
 dx,dy=f['target_offset'];w,h=crop(f).size
 kind='rear';direction=(-1,0)
 if i>=48:
  kind='hood';points=[(44.5,58)] if i<50 else [(44.5,59),(46.5,59),(48.5,59)];direction=(0,-1);base=(dx+w*.5,dy+h-1)
 elif i in side:
  kind='side';points=side[i];direction=(-.8,.6);base=(sum(p[0] for p in points)/len(points),sum(p[1] for p in points)/len(points))
 elif i in tops:
  kind='stack';points=tops[i];direction=(0,-1) if i in [11,18] else (-.35,-math.sqrt(1-.35**2));base=(dx+w-2,dy+h-3)
 elif i==43:
  points=[(41.5,64.5)];direction=(-.8,.6);base=points[0]
 elif i==42:
  points=[(41.5,57),(41.5,62)];base=(41.5,59.5)
 else:
  pic=crop(f);ys=[y for y in range(h) if pic.getpixel((0,y))[3]>0]
  points=[(dx+.5,dy+(sum(ys)/len(ys) if ys else h*.5))];base=points[0]
 layouts.append({'frame':i,'mount':kind,'base':base,'outlets':[[*p,*direction] for p in points]})
roots=[]
for f in flames['frames']:
 pic=crop(f);w,h=pic.size
 x=max(x for x in range(w) for y in range(h) if pic.getpixel((x,y))[3]>0)
 ys=[y for y in range(h) if pic.getpixel((x,y))[3]>0];dx,dy=f['target_offset'];roots.append([dx+x+.5,dy+sum(ys)/len(ys)+.5])
header=['// Generated native mounts from original sprite pixels; see exhaust-anchors.json.','#pragma once','namespace pcr::art {','struct BodyExhaustMount { float rearX,rearY,hoodX,hoodY,sideX,sideY; };','struct Outlet { double x=0,y=0,dx=-1,dy=0; };','struct PipeLayout { int mount; float baseX,baseY; int count; Outlet outlets[3]; };','inline const BodyExhaustMount bodyExhaustMounts[] = {']
fmt=lambda x:format(x,'.9g')
for b in mounts:header.append('{'+','.join(fmt(x)+'f' if '.' in fmt(x) else fmt(x)+'.0f' for k in ['rear','hood','side'] for x in b[k])+'},')
header+=['};','inline const PipeLayout pipeLayouts[] = {'];types={'rear':0,'hood':1,'side':2,'stack':3}
for p in layouts:
 outlets=','.join('{'+','.join(fmt(v) for v in point)+'}' for point in p['outlets'])
 header.append('{'+str(types[p['mount']])+','+','.join(fmt(x)+('f' if '.' in fmt(x) else '.0f') for x in p['base'])+','+str(len(p['outlets']))+',{'+outlets+'}},')
header+=['};','struct FlameRoot { float x,y; };','inline const FlameRoot flameRoots[] = {']
for p in roots:header.append('{'+','.join(fmt(x)+('f' if '.' in fmt(x) else '.0f') for x in p)+'},')
header+=['};','}'];(root/'src/exhaust_anchors.hpp').write_text('\n'.join(header)+'\n')
(root/'validation/exhaust-anchors.json').write_text(json.dumps({'method':'Body alpha silhouette; manually identified visible source pipe mouths; native placement, not recovered YYC offsets','bodies':mounts,'pipes':layouts,'flame_roots':roots},indent=2)+'\n')
print('Generated',len(mounts),'body mounts,',len(layouts),'pipe layouts and',len(roots),'flame roots')
