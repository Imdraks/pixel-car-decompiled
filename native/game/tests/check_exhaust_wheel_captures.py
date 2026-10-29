#!/usr/bin/env python3
"""Compare wheel interiors with and without the rear exhaust in actual GPU captures."""
import argparse,json,math
from pathlib import Path
from PIL import Image
p=argparse.ArgumentParser(description=__doc__);p.add_argument('captures',type=Path);p.add_argument('--report',type=Path,required=True);a=p.parse_args()
im=Image.open(a.captures/'exhaust-wheel-occlusion.png').convert('RGB');w,h=im.size;sx=w/1280;sy=h/720
rows=json.loads((a.captures/'exhaust-wheel-occlusion.json').read_text());results=[];visible=0
for entry in rows:
 cx=entry['left_x']*sx;cy=entry['y']*sy;rx=entry['radius']*sx;ry=entry['radius']*sy;offset=round((entry['right_x']-entry['left_x'])*sx);diff=total=0
 for y in range(math.floor(cy-ry),math.ceil(cy+ry)+1):
  for x in range(math.floor(cx-rx),math.ceil(cx+rx)+1):
   if ((x+.5-cx)/rx)**2+((y+.5-cy)/ry)**2<=1:
    left=im.getpixel((x,y));right=im.getpixel((x+offset,y));total+=1;diff+=max(abs(a-b) for a,b in zip(left,right))>3
 # The rear outlet must remain visible outside the opaque wheel/body.
 top=round((70+entry['row']*156)*sy);bottom=min(h,top+round(135*sy))
 for y in range(top,bottom):
  for x in range(round(60*sx),round(480*sx)):
   visible+=max(abs(a-b) for a,b in zip(im.getpixel((x,y)),im.getpixel((x+round(640*sx),y))))>12
 results.append({'row':entry['row'],'wheel_pixels':total,'changed_wheel_pixels':diff})
checks={'rear_exhaust_never_covers_wheel_interiors':len(results)==4 and all(row['changed_wheel_pixels']==0 for row in results),'rear_exhaust_still_visible_outside_wheels':visible>4}
report={'checks':checks,'cases':results,'visible_exhaust_pixels_outside_wheel':visible};a.report.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
if not all(checks.values()):raise SystemExit('Rear exhaust obscures near wheel pixels')
