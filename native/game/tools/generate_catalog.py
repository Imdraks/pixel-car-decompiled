#!/usr/bin/env python3
"""Generate the native catalog from the verified static item export."""
import json
from pathlib import Path
root=Path(__file__).resolve().parents[1]
report=json.loads((root.parent/'evidence/merged/performance.json').read_text())
slots={'engine':'Engine','suspension':'Suspension','turbo':'Turbo','supercharger':'Supercharger','ecu':'Ecu','nos':'Nos','intake':'Intake','intercooler':'Intercooler','pistons':'Pistons','exhaust':'Exhaust','tires':'Tires'}
lines=['// Generated from native/evidence/merged/performance.json.','#pragma once','namespace pcr {',
'enum class PartSlot { Engine, Suspension, Turbo, Supercharger, Ecu, Nos, Intake, Intercooler, Pistons, Exhaust, Tires, Count };',
'constexpr int PartSlotCount=11;',
'struct Part { int id; PartSlot slot; const char* name; double stat,weight,value; int subimage; };',
'inline constexpr Part PartCatalog[] = {']
for p in report['parts']:
 lines.append('{'+str(p['id'])+',PartSlot::'+slots[p['category']]+','+json.dumps(p['name'])+','+','.join(str(p[k]) for k in ['stat','weight','value','subimage'])+'},')
lines+=['};','}'];(root/'src/catalog.hpp').write_text('\n'.join(lines)+'\n')
print('Generated',len(report['parts']),'catalog entries')
