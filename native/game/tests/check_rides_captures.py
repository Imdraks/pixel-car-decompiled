#!/usr/bin/env python3
"""Check the captured menu hierarchy, landing layout and UI-free photo view."""
import argparse,json
from pathlib import Path
from PIL import Image
p=argparse.ArgumentParser(description=__doc__);p.add_argument('captures',type=Path);p.add_argument('--report',type=Path,required=True);a=p.parse_args()
def state(name):return dict(line.split('=',1) for line in (a.captures/(name+'.state')).read_text().splitlines() if '=' in line)
def crop(name,box):
 im=Image.open(a.captures/name).convert('RGB');w,h=im.size
 return im.crop(tuple(round(v*s) for v,s in zip(box,(w/1280,h/720,w/1280,h/720))))
def blue(im):return sum(b>75 and b>r*1.4 and b>g*1.15 for r,g,b in im.getdata())
def bright(im):return sum(min(rgb)>210 for rgb in im.getdata())
expected={'custom-accueil.png':(8,0,4,0),'custom-menu-style.png':(8,1,5,1),'custom-menu-carrosserie.png':(8,2,3,2),'custom-menu-elements.png':(8,3,10,3),'custom-menu-peinture.png':(8,4,2,2),'custom-menu-performance.png':(8,7,5,1)}
checks={}
for name,(screen,page,count,depth) in expected.items():
 s=state(name);checks[name]=s['screen']==str(screen) and s['rides_page']==str(page) and s['entry_count']==str(count) and s['rides_depth']==str(depth)
s=state('custom-posture.png');checks['stance_is_unsaved_draft']=s['screen']=='9' and s['ride_height_mm']!=s['draft_ride_height_mm']
hero=blue(crop('custom-accueil.png',(450,210,1250,600)));menu=bright(crop('custom-accueil.png',(38,312,490,605)));photo=bright(crop('custom-photo.png',(38,312,490,605)))
checks['large_vehicle_on_right_of_navigation']=hero>5000
checks['left_landing_menu_visible']=menu>500
checks['no_parts_carousel_on_initial_menu']=blue(crop('custom-accueil.png',(20,635,1250,715)))<100
checks['photo_mode_hides_navigation']=state('custom-photo.png')['hide_ui']=='1' and photo<100
report={'checks':checks,'hero_blue_pixels':hero,'landing_menu_bright_pixels':menu,'hidden_menu_bright_pixels':photo};a.report.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
if not all(checks.values()):raise SystemExit('Rides hierarchy capture validation failed')
