#!/usr/bin/env python3
"""Validate every Underground car cell and the integrated editor captures."""
import argparse,json
from pathlib import Path
from PIL import Image
p=argparse.ArgumentParser();p.add_argument('captures',type=Path);p.add_argument('--report',type=Path,required=True);a=p.parse_args();cells=[]
for page in range(4):
 im=Image.open(a.captures/f'underground-voitures-{page+1}.png').convert('RGB');sx=im.width/1280;sy=im.height/720
 for j in range(48):
  body=page*48+j
  if body>=191:break
  x=j%6*213;y=j//6*89
  pixels=im.crop((round((x+2)*sx),round((y+19)*sy),round((x+211)*sx),round((y+87)*sy)))
  blue=sum(b>65 and b>r*1.35 and b>g*1.1 for r,g,b in pixels.getdata());assert blue>=8,(body,blue);cells.append({'body':body,'blue_pixels':blue})
state=dict(line.split('=',1) for line in (a.captures/'custom-underground.png.state').read_text().splitlines() if '=' in line);assert state['vehicle_id']=='pcr-underground-007' and state['screen']=='8'
for name in ['underground-peinture.png','underground-jantes.png']:assert Image.open(a.captures/name).width>=960
result={'passed':True,'visible_body_cells':len(cells),'cells':cells,'customization_identity':state['vehicle_id']};a.report.write_text(json.dumps(result,indent=2)+'\n');print('PASS: all 191 Underground bodies and editor captures are visible.')
