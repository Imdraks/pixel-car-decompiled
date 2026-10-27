#!/usr/bin/env python3
"""Check the eight rendered Burn Slicks smoke hues around the driven axle."""
import argparse
import colorsys
import json
from pathlib import Path
from PIL import Image

p = argparse.ArgumentParser(description=__doc__)
p.add_argument('screens', type=Path)
p.add_argument('--report', type=Path, required=True)
a = p.parse_args()
# Broad visual hue ranges by named tyre colour; independent of renderer RGBs.
colours = [('green', 90, 150), ('teal', 155, 195), ('purple', 255, 295),
           ('pink', 305, 345), ('red', 345, 20), ('orange', 20, 45),
           ('yellow', 45, 75), ('blue', 200, 245)]
counts = {}
for frame, (name, low, high) in enumerate(colours, 9):
    with Image.open(a.screens / f'burnout-{frame:02d}.png') as im:
        im = im.convert('RGB')
        box = tuple(round(v * (im.width / 1280 if i % 2 == 0 else im.height / 720))
                    for i, v in enumerate((375, 370, 470, 475)))
        count = 0
        for rgb in im.crop(box).getdata():
            hue, sat, value = colorsys.rgb_to_hsv(*(v / 255 for v in rgb))
            hue *= 360
            inside = low <= hue <= high if low <= high else hue >= low or hue <= high
            count += inside and sat > .30 and value > .12
        counts[name] = count
checks = {name + '_smoke_visible': count >= 80 for name, count in counts.items()}
a.report.parent.mkdir(parents=True, exist_ok=True)
a.report.write_text(json.dumps({'checks': checks, 'matching_pixels': counts}, indent=2) + '\n')
print(json.dumps({'checks': checks, 'matching_pixels': counts}, indent=2))
if not all(checks.values()):
    raise SystemExit('Missing or incorrectly coloured rendered burnout smoke')
