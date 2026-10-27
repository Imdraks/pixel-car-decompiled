#!/usr/bin/env python3
"""Recover paint palette colours and audit/fix source-image accessory geometry.
Does not execute Android code. Source files are verified against texture hashes.
"""
import argparse,hashlib,json,re
from pathlib import Path
from functools import lru_cache
from PIL import Image
p=argparse.ArgumentParser(description=__doc__);p.add_argument('--root',type=Path,default=Path('/workspace/windows-port'));a=p.parse_args()
repo=Path(__file__).resolve().parents[3];out=repo/'native/evidence/merged';banks={};headers=[];canvas=[0,-64,220,70]
# Keep source names in sync with the original content preparation, not guesses.
src=(repo/'native/game/tools/prepare_content.py').read_text();m=re.search(r'kit_names=(\{[^\n]+\})',src);assert m
import ast
kitnames=ast.literal_eval(m[1]);finish_page=Image.new('RGBA',(1024,512));finish_frames={};finish_cell=0
recipes=json.loads((out/'rims.json').read_text())['rims']
for bank,folder in [('unbound','mod-textures'),('original','original-textures')]:
 root=a.root/folder;ss={s['name']:s for s in json.loads((root/'sprites.json').read_text())['sprites']};hashes={t['file']:t['sha256'] for t in json.loads((root/'textures.json').read_text())};verified={}
 @lru_cache(maxsize=12)
 def atlas(file):
  b=(root/file).read_bytes();digest=hashlib.sha256(b).hexdigest();assert digest==hashes[file];verified[file]=digest;return Image.open(root/file).convert('RGBA')
 def image(name,index):
  s=ss[name];im=Image.new('RGBA',(s['width'],s['height']));f=s['frames'][index]
  if f:
   x,y,w,h=f['source_rect'];im.paste(atlas(f['file']).crop((x,y,x+w,y+h)),f['target_offset'])
  return im
 for group,name in [('Shine','sp_rims'),('Shadow','sp_rimshadow')]:
  frames=[]
  for idx in range(len(ss[name]['frames'])):
   im=image(name,idx);bbox=im.getbbox() or (0,0,1,1);crop=im.crop(bbox);w,h=crop.size
   px=(finish_cell%16)*64+1;py=(finish_cell//16)*64+1;finish_cell+=1;finish_page.paste(crop,(px,py))
   frames.append([3000,px,py,w,h,bbox[0],bbox[1],im.width,im.height])
  finish_frames[bank+group]=frames
 pal=image('sp_color_pal',0);assert pal.size==(108,11);palette=[[list(pal.getpixel((c,r))) for r in range(11)] for c in range(108)]
 shaderdata=(a.root/('original-recovered' if bank=='original' else 'recovered')/'assets/game.droid').read_bytes()
 shaders=[m.group().decode() for m in re.finditer(rb'[\x09\x0a\x0d\x20-\x7e]{80,}',shaderdata) if b'gl_FragColor' in m.group() and b'palette_index' in m.group()]
 assert len(shaders) in (2,4) and all('<= 0.004' in s for s in shaders)
 anchors=json.loads((out/'attachment-positions.json').read_text())['banks'][bank]['bodies'];assert [v['body'] for v in anchors]==list(range(191))
 surface=(repo/'native/game/src/attachment_surfaces.hpp').read_text();block=surface.split('inline constexpr Surface '+bank+'Surfaces[]={')[1].split('};')[0]
 surfaces=[tuple(map(float,re.findall(r'([\d.]+)f',r))) for r in block.splitlines() if r.startswith('{')]
 # Exhaustive source-frame compatibility and generic accessory canvas bounds.
 cosmetics=[tuple(map(int,m)) for m in re.findall(r'^\{(\d+),(\d+),(\d+),"[^"\n]+",[^,]+,\d+,(-?\d+)\},', (repo/'native/game/src/content_catalog.hpp').read_text(),re.M)]
 assert len(cosmetics)==503
 spoiler_names=dict(re.findall(r'SPOILER\((\d+),([A-Za-z0-9_]+)\)',(repo/'native/game/src/cosmetic_geometry.hpp').read_text()));spoiler_names={int(k):v for k,v in spoiler_names.items()}
 @lru_cache(maxsize=None)
 def visible(name,index):return name in ss and image(name,index).getbbox() is not None
 compat=[];cases=0;generic_cases=0
 generic=[('sp_bike','roof'),('sp_towhook_part','hook'),('sp_seats','seat')]
 generic_images={name:[image(name,i) for i in range(1,len(ss[name]['frames']))] for name,_ in generic}
 for body in range(191):
  missing=[];partial=[]
  for cid,slot,part,image_source in cosmetics:
   available=True;ispartial=False
   if slot==2:available=visible('sp_spoiler_'+spoiler_names[part],body)
   if 4<=slot<=7 and part!=2:
    sides=['front','rear','side'] if slot==4 else [['front','rear','side'][slot-5]]
    count=sum(visible('sp_'+str(kitnames.get(part))+'_'+side,body) for side in sides)
    available=count>0;ispartial=available and count<len(sides)
   if not available:missing.append(cid)
   if ispartial:partial.append(cid)
   cases+=1
  compat.append({'body':body,'unsupported_cosmetic_ids':missing,'partial_cosmetic_ids':partial})
  anchor=anchors[body]['values']
  for name,kind in generic:
   ox,oy=ss[name]['origin'];x=62+anchor['part_'+kind+'_x']-ox;y=58+anchor['part_'+kind+'_y']-oy
   for im in generic_images[name]:
    box=im.getbbox()
    if box:
     canvas[0]=min(canvas[0],x+box[0]);canvas[1]=min(canvas[1],y+box[1]);canvas[2]=max(canvas[2],x+box[2]);canvas[3]=max(canvas[3],y+box[3])
    generic_cases+=1
 hood=[];audit=[]
 for body in range(191):
  base=image('sp_car',body);mask=image('sp_car_front',body);rows=[]
  for kit in range(13):
   im=base.copy();name=kitnames.get(kit);key='sp_'+str(name)+'_front';replacement=image(key,body) if key in ss else None
   compatible=kit==0 or kit==2 or replacement is not None and replacement.getbbox() is not None
   if kit and compatible:
    for yy in range(70):
     for xx in range(220):
      if mask.getpixel((xx,yy))[3]>128:im.putpixel((xx,yy),(0,0,0,0))
    if replacement is not None:im.alpha_composite(replacement)
   # Bonnet contact is taken from the visible top silhouette of the installed
   # front panel, ahead of the cabin. Three pipe feet share that exact surface.
   # The original Draw branches omit type-0 exhausts; this fit is a native one.
   old=surfaces[body]
   hx=int(old[0]);candidates=[]
   for x in range(max(0,hx-8),min(220,hx+9)):
    ys=[y for y in range(18,54) if im.getpixel((x,y))[3]>=250 and y+1<54 and im.getpixel((x,y+1))[3]>=250]
    if ys:
     y=min(ys)
     # Exclude near-vertical windscreen boundaries in favour of a flat hood.
     nearby=[]
     for nx in range(max(0,x-2),min(220,x+3)):
      q=[ny for ny in range(10,54) if im.getpixel((nx,ny))[3]>=250]
      if q:nearby.append(min(q))
     slope=max(nearby)-min(nearby) if nearby else 99
     candidates.append((slope*3+abs(x-hx),x,y))
   if not candidates:
    # Delete/archless exception retains the mechanical engine bay anchor.
    x,y=hx,int(old[1])-2;fallback=True
   else:_,x,y=min(candidates);fallback=kit==2 or not compatible
   rows.append([x,y+1,int(compatible),int(fallback)])
  hood.append(rows)
  audit.append({'body':body,'hood_front_variants':rows})
 banks[bank]={'palette_rgba':palette,'shader_sha256':[hashlib.sha256(s.encode()).hexdigest() for s in shaders],'source_textures_sha256':verified,'bodies':audit,'compatibility':compat,'cosmetic_cases_checked':cases,'generic_mount_cases_checked':generic_cases,'game_droid_sha256':hashlib.sha256(shaderdata).hexdigest()}
 headers+=['inline constexpr HoodMount '+bank+'Hoods[191][13]={']+['{'+','.join('{'+','.join(map(str,r))+'}' for r in rows)+'},' for rows in hood]+['};']
 headers+=['inline constexpr unsigned '+bank+'Paint[108][11]={']+['{'+','.join('0x'+''.join(f'{c:02x}' for c in rgba)+'u' for rgba in col)+'},' for col in palette]+['};']
finish_page.save(repo/'native/game/assets/customization-00.png')
fh=['// Source stationary rim reflection/shadow passes. Generated by prepare_customization.py.','#pragma once','#include "model.hpp"','namespace pcr::rim_finish {','inline constexpr int AtlasCount=1;']
for name,frames in finish_frames.items():fh+=['inline const art::Frame '+name+'[]={']+['{'+','.join(map(str,f))+'},' for f in frames]+['};']
fh+=['struct Finish {int shine,shadow;};','inline constexpr Finish Finishes[]={']+['{'+str(v['fields']['shine'])+','+str(v['fields']['shadow'])+'},' for v in recipes]+['};','inline const Finish* finish(int rim){const auto* r=findRim(rim);return r?&Finishes[r->image]:nullptr;}','inline const art::Frame& shine(bool original,int id){return original?originalShine[id]:unboundShine[id];}','inline const art::Frame& shadow(bool original,int id){return original?originalShadow[id]:unboundShadow[id];}','}']
(repo/'native/game/src/rim_finish_art.hpp').write_text('\n'.join(fh)+'\n')
report={'method':'Hash-verified source palette texels and shader comparison threshold; native bonnet silhouette fitting by body and front kit','palette_columns':108,'palette_rows':11,'hood_body_kit_cases':191*13*2,'canvas_bounds':canvas,'cosmetic_cases_checked':sum(v['cosmetic_cases_checked'] for v in banks.values()),'generic_mount_cases_checked':sum(v['generic_mount_cases_checked'] for v in banks.values()),'banks':banks,'limitations':['Type-0 hood exhaust drawing is absent from the inspected source car branches; bonnet coordinates are a native geometric fit, not recovered Android draw coordinates.']}
(out/'customization-render.json').write_text(json.dumps(report,indent=2)+'\n')
headers+=['inline constexpr int CanvasX='+str(int(-canvas[0]+2))+';', 'inline constexpr int CanvasY='+str(int(-canvas[1]+2))+';', 'inline constexpr int CanvasW='+str(int(canvas[2]-canvas[0]+4))+';', 'inline constexpr int CanvasH='+str(int(canvas[3]-canvas[1]+4))+';']
h=['// Generated by prepare_customization.py from hash-verified source images.','#pragma once','namespace pcr::materials {','struct HoodMount {int x,y,compatible,fallback;};']+headers+['inline const HoodMount& hoodMount(int body,int kit,bool original){return (original?originalHoods:unboundHoods)[body>=0&&body<191?body:0][kit>=0&&kit<13?kit:0];}','}']
(repo/'native/game/src/customization_data.hpp').write_text('\n'.join(h)+'\n');print('Recovered 2376 palette texels and fitted all 4966 body/front-kit combinations.')
