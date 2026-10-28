#!/usr/bin/env python3
"""Check the actual split showroom renders a large, distinct selected car on the left."""
import argparse,hashlib,json
from pathlib import Path
from PIL import Image,ImageChops
p=argparse.ArgumentParser(description=__doc__);p.add_argument('captures',type=Path);p.add_argument('--report',type=Path,required=True);a=p.parse_args()
def crop(name,box):
 im=Image.open(a.captures/name).convert('RGB');w,h=im.size
 return im.crop(tuple(round(v*s) for v,s in zip(box,(w/1280,h/720,w/1280,h/720))))
def blue(im):return sum(b>75 and b>r*1.4 and b>g*1.15 for r,g,b in im.getdata())
first=crop('showroom-preview-civic.png',(38,260,648,515));second=crop('showroom-preview-corvette.png',(38,260,648,515))
menu=crop('showroom-preview-corvette.png',(700,194,1242,545));empty=crop('garage-vide.png',(38,260,648,515))
different=sum(max(pixel)>12 for pixel in ImageChops.difference(first,second).getdata())
checks={'large_car_preview_on_left':blue(first)>1000 and blue(second)>1000,'vehicle_list_on_right_has_no_tiny_car_grid':blue(menu)<100,'changing_model_changes_actual_car_pixels':different>600,'empty_owned_garage_has_no_car_preview':blue(empty)<50}
report={'checks':checks,'changed_car_pixels':different,'left_car_blue_pixels':[blue(first),blue(second)],'right_list_blue_pixels':blue(menu),'preview_hashes':[hashlib.sha256(im.tobytes()).hexdigest() for im in [first,second]]};a.report.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
if not all(checks.values()):raise SystemExit('Split showroom preview verification failed')
