#!/usr/bin/env python3
"""Confirm visible blue NOS and warm flames in the actual native renderer."""
import argparse,json
from pathlib import Path
from PIL import Image
p=argparse.ArgumentParser(description=__doc__);p.add_argument('captures',type=Path);p.add_argument('--report',type=Path,required=True);a=p.parse_args()
im=Image.open(a.captures/'echappement-arriere.png').convert('RGB');w,h=im.size;blue=warm=0
for y in range(round(300*h/720),round(500*h/720)):
 for x in range(round(300*w/1280),round(410*w/1280)):
  r,g,b=im.getpixel((x,y));blue+=r>50 and g>r+30 and b>r+50;warm+=r>150 and g>60 and b<r-70
checks={'blue_nos_is_visible':blue>=5,'warm_backfire_is_visible':warm>=5}
r={'checks':checks,'blue_pixels':blue,'warm_pixels':warm};a.report.write_text(json.dumps(r,indent=2)+'\n');print(json.dumps(r,indent=2))
if not all(checks.values()):raise SystemExit('Exhaust jets not visibly rendered')
