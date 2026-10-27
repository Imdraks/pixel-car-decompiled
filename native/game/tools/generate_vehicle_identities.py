#!/usr/bin/env python3
"""Generate safe model labels from the curated, uncertainty-labelled body identities."""
from pathlib import Path
import json,csv
repo=Path(__file__).resolve().parents[3];data=json.loads((repo/'native/evidence/merged/vehicle-identities.json').read_text());rows=data['records'];assert sorted(r['body'] for r in rows)==list(range(191))
quote=lambda s:json.dumps(s,ensure_ascii=False)
h=['// Generated from native/evidence/merged/vehicle-identities.json.','#pragma once','namespace pcr {','struct VehicleIdentity {const char* name;bool tentative;};','inline constexpr VehicleIdentity OriginalVehicleIdentities[]={']
for r in rows:h.append('{'+quote(r['name'])+','+str(r['status']!='visually_reviewed').lower()+'},')
h+=['};','inline const VehicleIdentity& vehicleIdentity(int body,bool original){','body=body>=0&&body<191?body:0;','if(!original)switch(body){']
for r in data['unbound_visual_replacements']:h.append('case '+str(r['body'])+':{static constexpr VehicleIdentity value{'+quote(r['name'])+',true};return value;}')
h+=['default:break;}','return OriginalVehicleIdentities[body];','}','}'];(repo/'native/game/src/vehicle_identities.hpp').write_text('\n'.join(h)+'\n')
with (repo/'native/evidence/merged/vehicle-identities.csv').open('w',newline='') as f:
 writer=csv.writer(f);writer.writerow(['body_id','display_id','model','confidence','reference'])
 for r in rows:writer.writerow([r['body'],r['body']+1,r['name'],r['status'],'; '.join(v['url'] for v in r['references'])])
print('Generated 191 model labels and six separate mod identities with explicit uncertainty.')
