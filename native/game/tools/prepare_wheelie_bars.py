#!/usr/bin/env python3
"""Recover DRAG PRO rear roller contact pixels from hash-verified source sprites."""
import json,re,hashlib
from pathlib import Path
from PIL import Image
repo=Path(__file__).resolve().parents[3];root=Path('/workspace/windows-port');banks={};header=['// Generated from source sp_drag2_rear roller outlines; mechanical response is native.','#pragma once','namespace pcr::wheelie_bars {','struct Roller {int x,bottom;bool present;double rear,front,y,radius;};']
art=(repo/'native/game/src/content_art.hpp').read_text()
for bank,folder in [('original','original-textures'),('unbound','mod-textures')]:
 path=root/folder;sprites={s['name']:s for s in json.loads((path/'sprites.json').read_text())['sprites']};hashes={t['file']:t['sha256'] for t in json.loads((path/'textures.json').read_text())};cache={};rows=[];proof=[]
 anchors=[list(map(float,re.findall(r'(-?[\d.]+)f',v))) for v in art.split('inline constexpr float '+bank+'Anchors[][5]={')[1].split('};')[0].splitlines() if v.startswith('{')]
 for body,f in enumerate(sprites['sp_drag2_rear']['frames']):
  im=Image.new('RGBA',(220,70))
  if f:
   if f['file'] not in cache:
    b=(path/f['file']).read_bytes();assert hashlib.sha256(b).hexdigest()==hashes[f['file']];cache[f['file']]=Image.open(path/f['file']).convert('RGBA')
   x,y,w,h=f['source_rect'];im.paste(cache[f['file']].crop((x,y,x+w,y+h)),f['target_offset'])
  # Rollers are the leftmost opaque component, behind the rear wheel; do not
  # confuse the painted bumper with a roller on an unsupported body variant.
  pixels=[(x,y) for x in range(max(0,int(anchors[body][0])-20)) for y in range(45,70) if im.getpixel((x,y))[3]>=200]
  if pixels:
   left=min(x for x,y in pixels);foot=[(x,y) for x,y in pixels if x<left+6];bottom=max(y for x,y in foot)+1;cx=round(sum(x for x,y in foot)/len(foot));present=True
  else:cx=bottom=0;present=False
  rows.append((cx,bottom,int(present),*anchors[body][:4]));proof.append({'body':body,'roller_x':cx,'roller_bottom_y':bottom,'present':present})
 assert len(rows)==191
 banks[bank]={'source_sprite':'sp_drag2_rear','texture_sha256':{f:hashes[f] for f in cache},'bodies':proof,'roller_bodies':sum(r[2] for r in rows)}
 header+=['inline constexpr Roller '+bank+'[191]={']+['{'+str(v[0])+','+str(v[1])+','+('true' if v[2] else 'false')+','+','.join(str(n) for n in v[3:])+'},' for v in rows]+['};']
header+=['inline const Roller& roller(int body,bool isOriginal){return (isOriginal?original:unbound)[body>=0&&body<191?body:0];}','}']
(repo/'native/game/src/wheelie_bars.hpp').write_text('\n'.join(header)+'\n');(repo/'native/evidence/merged/wheelie-bars.json').write_text(json.dumps({'source_equipment':[104011,106011],'banks':banks,'original_bar_physics_recovered':False},indent=2)+'\n');print({k:v['roller_bodies'] for k,v in banks.items()})
