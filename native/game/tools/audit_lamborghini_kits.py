#!/usr/bin/env python3
"""Compare slots 086/188 against extracted Android frames, without editing assets."""
import argparse
import hashlib
import json
from pathlib import Path
import re

from PIL import Image, ImageDraw

parser = argparse.ArgumentParser(description=__doc__)
parser.add_argument('--original', type=Path, default=Path('/workspace/windows-port/original-textures'))
parser.add_argument('--unbound', type=Path, default=Path('/workspace/windows-port/mod-textures'))
parser.add_argument('--underground', type=Path, default=Path('/workspace/underground/textures'))
parser.add_argument('--output', type=Path, required=True)
parser.add_argument('--all-bodies', action='store_true', help='Verify every body/panel frame in the three banks')
args = parser.parse_args()
game = Path(__file__).resolve().parents[1]
args.output.mkdir(parents=True, exist_ok=True)
groups = {name: [tuple(map(int, row.split(','))) for row in re.findall(r'\{([\d,]+)\}', rows)]
          for name, rows in re.findall(r'inline const Frame (\w+)\[\]=\{(.*?)\n\};',
                                      (game/'src/content_art.hpp').read_text(), re.S)}
kits = {1: 'rocketbunny', 3: 'bn', 4: 'stickerbomb', 5: 'drag', 6: 'pandem',
        7: 'fortune', 8: 'vxlip', 9: 'bashbar', 10: 'heavybashbar', 11: 'drag2', 12: 'tuner'}
cache = {}


def atlas(path):
    if path not in cache:
        cache[path] = Image.open(path).convert('RGBA')
    return cache[path]


def normalized(im):
    # Texture packers may retain arbitrary RGB behind completely transparent texels.
    alpha = im.getchannel('A')
    result = Image.composite(im.convert('RGB'), Image.new('RGB', im.size),
                             alpha.point(lambda a: 255 if a else 0))
    result.putalpha(alpha)
    return result


checks = []
for bank in ('original', 'unbound', 'underground'):
    root = getattr(args, bank)
    sprites = {s['name']: s for s in json.loads((root/'sprites.json').read_text())['sprites']}
    digests = {t['file']: t['sha256'] for t in json.loads((root/'textures.json').read_text())}
    verified = set()

    def source(name, body):
        sprite = sprites[name]
        image = Image.new('RGBA', (sprite['width'], sprite['height']))
        f = sprite['frames'][body]
        if f:
            path = root/f['file']
            if path not in verified:
                assert hashlib.sha256(path.read_bytes()).hexdigest() == digests[f['file']], path
                verified.add(path)
            x, y, w, h = f['source_rect']
            image.paste(atlas(path).crop((x, y, x+w, y+h)), f['target_offset'])
        return image

    names = {'Cars': 'sp_car', 'Front': 'sp_car_front', 'Rear': 'sp_car_rear'}
    for kid, name in kits.items():
        for side in ('front', 'rear', 'side'):
            if 'sp_'+name+'_'+side in sprites:
                names[f'Kit_{kid}_{side}'] = 'sp_'+name+'_'+side
    sheet = Image.new('RGB', (1320, 165*(len(kits)+1)), (32, 35, 42))
    draw = ImageDraw.Draw(sheet)
    for body in (range(191) if args.all_bodies else (85, 187)):
        for suffix, sprite in names.items():
            raw = normalized(source(sprite, body))
            aid, x, y, w, h, dx, dy, cw, ch = groups[bank+suffix][body]
            packed = Image.new('RGBA', (cw, ch))
            packed.paste(atlas(game/'assets'/f'content-{aid-2000:02d}.png').crop((x, y, x+w, y+h)), (dx, dy))
            packed = normalized(packed)
            assert raw.size == packed.size and raw.tobytes() == packed.tobytes(), (bank, body, suffix)
            checks.append({'bank': bank, 'body_index': body, 'display_id': body+1,
                           'sprite': sprite, 'native_group': bank+suffix,
                           'rgba_sha256': hashlib.sha256(raw.tobytes()).hexdigest(), 'matched': True})
        if body not in (85, 187):
            continue
        col = 0 if body == 85 else 1
        for row, (kid, name) in enumerate({0: 'stock', **kits}.items()):
            image = source('sp_car', body)
            if kid:
                for side in ('front', 'rear', 'side'):
                    sprite = 'sp_'+name+'_'+side
                    if sprite not in sprites:
                        continue
                    layer = source(sprite, body)
                    if not layer.getbbox():
                        continue
                    if side != 'side':
                        mask = source('sp_car_'+side, body).getchannel('A').point(lambda a: 255 if a > 128 else 0)
                        image.paste((0, 0, 0, 0), (0, 0), mask)
                    image.alpha_composite(layer)
            scaled = image.resize((660, 140), Image.Resampling.NEAREST)
            sheet.paste(scaled, (col*660, row*165+22), scaled)
            draw.text((col*660+5, row*165+3), f'{bank} {body+1:03d} {name}', fill='white')
    sheet.save(args.output/f'{bank}-086-188.png')

report = {'method': 'Texture-hash-verified Android frames compared to active native atlas frames; transparent RGB ignored.',
          'frame_checks': len(checks), 'all_frames_match_their_own_source_index': True,
          'swapped_086_188_frames_found': False,
          'model_identifications': [
              {'display_id': 86, 'source': 'Unbound', 'model': 'Lamborghini Aventador',
               'basis': '573 base frames and candidate kit families visually reviewed; Aventador reference photographs.',
               'confidence': 'visually_reviewed_family', 'year_and_trim': 'unconfirmed', 'stable_vehicle_id': 'pcr-unbound-085'},
              {'display_id': 188, 'source': 'Unbound', 'model': 'Lamborghini Huracán',
               'basis': 'User explicitly confirmed the exact extracted 188 base sprite in the supplied image.',
               'confidence': 'user_confirmed_family', 'year_and_trim': 'unconfirmed', 'stable_vehicle_id': 'pcr-unbound-187'}],
          'all_frames_digest': hashlib.sha256(json.dumps(checks, sort_keys=True).encode()).hexdigest(),
          'frame_details_scope': '086/188; frame_checks and digest cover all checked bodies',
          'limitations': ['Pixel identity proves correct frame import, not a manufacturer-certified model identification.',
                         'Sheets reconstruct source body panels; they are not captures of an Android runtime.'],
          'frames': [c for c in checks if c['body_index'] in (85, 187)]}
if (game/'vehicle-variants.json').exists():
    report['named_conversions'] = json.loads((game/'vehicle-variants.json').read_text())['variants']
(args.output/'lamborghini-kits-audit.json').write_text(json.dumps(report, ensure_ascii=False, indent=2)+'\n')
print(f'{len(checks)} source frames match their native counterpart; no 086/188 interchange.')
