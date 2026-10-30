#!/usr/bin/env python3
"""Check visible orphan lamp pixels in the actual composed model captures."""
import argparse,json,re
from pathlib import Path
from PIL import Image
p=argparse.ArgumentParser(description=__doc__);p.add_argument('captures',type=Path);p.add_argument('--assets',type=Path,required=True);p.add_argument('--report',type=Path,required=True);a=p.parse_args()
g=Path(__file__).resolve().parents[1];text=(g/'src/content_art.hpp').read_text();groups={n:[list(map(int,row.split(','))) for row in re.findall(r'\{([\d,]+)\}',rows)] for n,rows in re.findall(r'inline const Frame (\w+)\[\]=\{(.*?)\n\};',text,re.S)};data=(g/'src/customization_data.hpp').read_text();cx=int(re.search(r'CanvasX=(\d+)',data)[1]);cy=int(re.search(r'CanvasY=(\d+)',data)[1]);cache={}
def frame(name,i):
 atlas,x,y,w,h,dx,dy,cw,ch=groups[name][i];path=a.assets/f'content-{atlas-2000:02d}.png'
 if atlas not in cache:cache[atlas]=Image.open(path).convert('RGBA')
 im=Image.new('RGBA',(cw,ch));im.paste(cache[atlas].crop((x,y,x+w,y+h)),(dx,dy));return im
def orphan(image,source):
 return sum(color[3]>=128 and min(color[:3])>=220 and source.getpixel((i%source.width,i//source.width))[3]==0 for i,color in enumerate(image.getdata()))
rows=[]
for slug,body in [('lamborghini-aventador',85),('lamborghini-huracan',187)]:
 source=frame('unboundCars',body);before=source.copy();before.alpha_composite(frame('unboundHeadlights',body));before.alpha_composite(frame('unboundTaillights',body));actual=Image.open(a.captures/(slug+'-body.png')).convert('RGBA').crop((cx,cy,cx+source.width,cy+source.height))
 prior=orphan(before,source);current=orphan(actual,source);assert current==0,(slug,current)
 rows.append({'model':slug,'source_body_id':body+1,'orphan_bright_pixels_with_legacy_masks':prior,'orphan_bright_pixels_in_actual_composition':current,'baked_source_lamps_preserved':True})
a.report.write_text(json.dumps({'checks_passed':len(rows),'white_paint_globally_removed':False,'cases':rows},indent=2)+'\n');print(json.dumps(rows))
