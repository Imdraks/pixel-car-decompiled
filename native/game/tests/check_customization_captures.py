#!/usr/bin/env python3
"""Detect stale/reused GPU body textures across the twelve paint previews."""
import argparse, hashlib, json
from pathlib import Path
from PIL import Image
p=argparse.ArgumentParser(description=__doc__)
p.add_argument('captures',type=Path);p.add_argument('--report',type=Path,required=True);a=p.parse_args()
im=Image.open(a.captures/'materiaux-source.png').convert('RGBA');w,h=im.size
hashes=[]
for i in range(12):
 x=8+424*(i%3)+5;y=60+164*(i//3)+28
 box=tuple(round(v) for v in (x*w/1280,y*h/720,(x+400)*w/1280,(y+125)*h/720))
 hashes.append(hashlib.sha256(im.crop(box).tobytes()).hexdigest())
checks={'twelve_paint_previews_have_distinct_body_pixels':len(set(hashes))==12}
r={'checks':checks,'body_crop_sha256':hashes};a.report.write_text(json.dumps(r,indent=2)+'\n');print(json.dumps(r,indent=2))
if not all(checks.values()):raise SystemExit('Paint previews reused a different body texture')
