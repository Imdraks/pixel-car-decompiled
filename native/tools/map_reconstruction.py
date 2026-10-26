#!/usr/bin/env python3
"""Join exact exported object names to ELF game-event symbols; no code inference."""
import json
import argparse
from pathlib import Path
import re

parser=argparse.ArgumentParser(description=__doc__)
parser.add_argument('--root',type=Path,default=Path('/workspace/native-investigation'))
root=parser.parse_args().root
for label in ['unbound','original']:
    folder=root/label
    structure=json.loads((folder/'utmt-structure.json').read_text())
    native=json.loads((folder/'native-inventory.json').read_text())['x86']
    events={}
    unknown=[]
    for f in native['game_functions']:
        if not f['demangled'].startswith('gml_Object_'):continue
        m=re.match(r'^gml_Object_(.+)_([A-Za-z]+)_(\d+)\(',f['demangled'])
        if not m:unknown.append(f);continue
        name,event,subtype=m.groups()
        events.setdefault(name,[]).append({'event':event,'subtype':int(subtype),
            'address':f['address'],'size':f['size'],'symbol':f['name']})
    objects=[]
    for o in structure['objects']:
        objects.append({**o,'native_events':events.get(o['name'],[])})
    result={
        'project':structure['project'],'yyc':structure['yyc'],
        'code_entry_count':structure['code_entry_count'],
        'native_sha256':native['sha256'],
        'objects':objects,'rooms':structure['rooms'],
        'unmatched_native_objects':sorted(set(events)-{o['name'] for o in objects}),
        'unparsed_native_object_symbols':unknown,
        'limitations':['Exact name joins only; event addresses are Android ELF addresses, not Windows code.',
                      'No event semantics, event ordering, physics or execution equivalence is reconstructed.']}
    (folder/'reconstruction-map.json').write_text(json.dumps(result,indent=2)+'\n')
    print(json.dumps({'label':label,'objects':len(objects),'objects_with_named_events':sum(bool(o['native_events']) for o in objects),
        'native_events':sum(len(o['native_events']) for o in objects),'rooms':len(structure['rooms']),
        'initial_instances':sum(len(r['instances']) for r in structure['rooms']),
        'code_entry_count':structure['code_entry_count'],'unmatched_native_objects':result['unmatched_native_objects']}))
