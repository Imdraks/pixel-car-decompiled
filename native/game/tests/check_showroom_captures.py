#!/usr/bin/env python3
"""Verify the large showroom car, right stats and independently rendered bottom carousel."""
import argparse,hashlib,json
from pathlib import Path
from PIL import Image,ImageChops
p=argparse.ArgumentParser(description=__doc__);p.add_argument('captures',type=Path);p.add_argument('--report',type=Path,required=True);a=p.parse_args()
def crop(name,box):
 im=Image.open(a.captures/name).convert('RGB');w,h=im.size
 return im.crop(tuple(round(v*s) for v,s in zip(box,(w/1280,h/720,w/1280,h/720))))
def blue(im):return sum(b>75 and b>r*1.4 and b>g*1.15 for r,g,b in im.getdata())
first=crop('showroom-preview-civic.png',(24,210,940,471));second=crop('showroom-preview-corvette.png',(24,210,940,471))
right=crop('showroom-preview-corvette.png',(956,120,1248,465));empty=crop('garage-vide.png',(24,210,940,471))
carousel=crop('garage-huit-places.png',(38,556,1240,623))
thumbs=[crop('garage-huit-places.png',(38+i*202+18,558,38+i*202+176,618)) for i in range(6)]
hashes=[hashlib.sha256(im.tobytes()).hexdigest() for im in thumbs]
different=sum(max(pixel)>12 for pixel in ImageChops.difference(first,second).getdata())
checks={'large_central_car_preview':blue(first)>2500 and blue(second)>2500,'compact_stats_panel_on_right':blue(right)<100,'distinct_selected_models':different>1000,'empty_garage_has_no_car':blue(empty)<50,'visible_bottom_carousel':blue(carousel)>500,'six_thumbnails_keep_their_own_body_texture':len(set(hashes))==6 and all(blue(im)>40 for im in thumbs)}
custom_previews=[crop('custom-carrousel-'+kind+'.png',(24,210,940,471)) for kind in ['moteur','turbo','style']]
custom_icons=[crop('custom-carrousel-'+kind+'.png',(99,546,169,598)) for kind in ['moteur','turbo','style']]
checks['large_preview_in_all_custom_categories']=all(blue(im)>2500 for im in custom_previews)
checks['part_icons_visible_in_bottom_carousel']=all(sum(max(rgb)>110 for rgb in im.getdata())>50 for im in custom_icons)
report={'checks':checks,'changed_car_pixels':different,'large_car_blue_pixels':[blue(first),blue(second)],'right_panel_blue_pixels':blue(right),'carousel_blue_pixels':blue(carousel),'thumbnail_hashes':hashes};a.report.write_text(json.dumps(report,indent=2)+'\n');print(json.dumps(report,indent=2))
if not all(checks.values()):raise SystemExit('Showroom carousel rendering verification failed')
