"""Maintained mandatory IOP code/data source ranges.

Fixed base helpers preserve every original verifier/manifest/receipt contract.
The enhanced libsd component adds one independently reviewed data object;
module identity and unowned preservation are counted once.
"""
import importlib
import json
from pathlib import Path

from common import ROOT,Elf32,save_json
from iop_build import allocated_read,digest

BASE_VERIFIERS={'iop_build','iop_libsd_build','iop_nosplit_build'}
COMBINED_OUTPUT=ROOT/'build/iop/combined'


def base_components():
    definitions=(('sio2man','config/iop_partial.json','build/iop/module_00','iop_build'),
        ('libsd','config/iop_libsd_partial.json','build/iop/module_04','iop_libsd_build'),
        ('nosplit-cohort','config/iop_nosplit_partial.json','build/iop/nosplit','iop_nosplit_build'))
    return [{'library':library,'manifest':ROOT/manifest,'output':ROOT/output,'verifier':verifier}
        for library,manifest,output,verifier in definitions]


def base_admission_set(definitions):
    if len(definitions)!=3 or {c.get('verifier')for c in definitions}!=BASE_VERIFIERS:
        raise ValueError('The complete fixed admitted three-component set is required')
    actual={(c['verifier'],str(Path(c['manifest']).resolve()),str(Path(c['output']).resolve()))for c in definitions}
    expected={(v,str((ROOT/m).resolve()),str((ROOT/o).resolve()))for v,m,o in (
        ('iop_build','config/iop_partial.json','build/iop/module_00'),
        ('iop_libsd_build','config/iop_libsd_partial.json','build/iop/module_04'),
        ('iop_nosplit_build','config/iop_nosplit_partial.json','build/iop/nosplit'))}
    if actual!=expected:raise ValueError('Foreign or missing fixed original component provenance')
    return actual


def base_reread(item):
    if item.get('verifier')not in BASE_VERIFIERS:raise ValueError('Unknown IOP verifier is not a source owner')
    verifier=importlib.import_module(item['verifier'])
    path=Path(item['manifest']).resolve();report_path=Path(item.get('report_path',Path(item['output'])/'partial_iop_report.json')).resolve()
    if not path.is_relative_to(ROOT)or not report_path.is_relative_to(ROOT/'build/iop'):
        raise ValueError('IOP report/manifest provenance escapes component ownership')
    return verifier,verifier.current_report(path,report_path)


def current_base_components(require_all=False):
    """Every admitted component is mandatory; the legacy argument cannot skip it."""
    verified=[]
    definitions=base_components();base_admission_set(definitions)
    # Reject every missing mandatory input before any full native verification.
    # The original per-owner checks remain below to catch removal after preflight.
    for c in definitions:
        if not Path(c['manifest']).is_file():raise ValueError('Missing admitted IOP source manifest: '+str(c['manifest']))
        rp=Path(c['output'])/'partial_iop_report.json'
        if not rp.is_file():raise ValueError('Missing admitted IOP source proof: '+str(rp))
    for c in definitions:
        if not Path(c['manifest']).is_file():raise ValueError('Missing admitted IOP source manifest: '+str(c['manifest']))
        rp=Path(c['output'])/'partial_iop_report.json'
        if not rp.is_file():raise ValueError('Missing admitted IOP source proof: '+str(rp))
        item={**c,'report_path':rp};_,report=base_reread(item)
        verified.append({**item,'report':report})
    _base_module_groups(verified)
    return verified


def _native_code(verifier_name,verifier,report,f,original):
    if verifier_name=='iop_build':
        groups=[g for g in report['native_groups']if g['source']==f['source']]
        if len(groups)!=1:raise ValueError('Missing or duplicate source object group')
        bodies=[]
        for p in groups[0]['native_profiles']:
            obj=Elf32((ROOT/p['object']).read_bytes());text=obj.section_data(obj.section('.text'))
            bodies.append(text[f['object_offset']:f['object_offset']+f['size']])
    elif verifier_name=='iop_libsd_build':
        bodies=[verifier.inspect_object(Elf32((ROOT/p['object']).read_bytes()),original)[0]for p in report['native_profiles']]
    else:
        groups=[g for g in report['native_objects']if g['claim']['name']==f['name']]
        if len(groups)!=1 or groups[0]['claim']!=f:raise ValueError('Missing or false narrow source object ownership')
        bodies=[verifier.inspect_object(Elf32((ROOT/p['object']).read_bytes()),f,original)[0]for p in groups[0]['profiles']]
    if len(bodies)!=2 or len(bodies[0])!=f['size']or bodies[0]!=bodies[1]:
        raise ValueError('Two whole native proofs do not produce the exact source span')
    return bodies[0]


def _base_module_groups(verified):
    expected=base_admission_set(base_components())
    if len(verified)!=3 or {(c['verifier'],str(Path(c['manifest']).resolve()),str(Path(c['output']).resolve()))for c in verified}!=expected:
        raise ValueError('Aggregate cannot use an incomplete or foreign admitted component receipt set')
    modules={};source_owners=set()
    for item in verified:
        verifier,report=base_reread(item)
        if item.get('report')!=report:raise ValueError('Caller supplied stale/false component receipt')
        progress=report['progress'];functions=report['functions']
        if progress['verified_source_functions']!=len(functions)or progress['verified_source_code_bytes']!=sum(f['size']for f in functions)or progress['verified_source_initialized_data_bytes']!=0:
            raise ValueError('Unknown data/function/count admission contract')
        for f in functions:
            relative=f.get('module',report.get('module'))
            path=(ROOT/relative).resolve()
            if not path.is_relative_to((ROOT/'disc/irx').resolve()):raise ValueError('Original IOP identity is outside extracted modules')
            claimed_hash=f.get('module_sha256',report.get('module_sha256'));raw=path.read_bytes()
            if digest(raw)!=claimed_hash:raise ValueError('Original module identity/hash differs between source owners')
            key=path.as_posix();original=Elf32(raw)
            if key not in modules:
                modules[key]={'module':path.relative_to(ROOT).as_posix(),'module_sha256':claimed_hash,'raw':raw,'original':original,'claims':[],'evidence':[]}
            group=modules[key]
            if group['module_sha256']!=claimed_hash:raise ValueError('Contradictory original identity for one module')
            a,n=f['module_offset'],f['size']
            if a<0 or a%4 or n<=0 or n%4:raise ValueError('Invalid complete function range')
            owner,target=allocated_read(original,a,n,True)
            if owner['name']!='.text'or digest(target)!=f['original_code_sha256']:
                raise ValueError('Original function does not have the proved allocated code ownership')
            identity=(key,f['name']);span=(a,a+n)
            if identity in source_owners:raise ValueError('Duplicate function source ownership')
            source_owners.add(identity)
            for old in group['claims']:
                if span[0]<old['module_offset']+old['size']and old['module_offset']<span[1]:
                    raise ValueError('Overlapping source function claims within original module')
            native=_native_code(item['verifier'],verifier,report,f,original)
            if native!=target:raise ValueError('Native function patch changes an original byte')
            file_offset=owner['offset']+a-owner['addr']
            claim={'name':f['name'],'source':f['source'],'source_sha256':f['source_sha256'],'module_offset':a,'size':n,
                'file_offset':file_offset,'section':'.text','code_sha256':digest(native),'native_code_hex':native.hex(),
                'verifier':item['verifier'],'component_manifest':Path(item['manifest']).resolve().relative_to(ROOT).as_posix()}
            group['claims'].append(claim)
            evidence={'path':Path(item['report_path']).resolve().relative_to(ROOT).as_posix(),'sha256':digest(Path(item['report_path']).read_bytes()),'freshness':report['freshness']}
            if evidence not in group['evidence']:group['evidence'].append(evidence)
    return modules


import iop_libsd_data_build as data_verifier
import iop_mcman_build as mcman_verifier
import iop_mcman_device_build as device_verifier
import iop_mcman_ecc_build as ecc_verifier
import iop_snd989_build as snd989_verifier
import iop_snd989_chain_build as chain_verifier
import iop_snd989_volume_build as volume_verifier
from common import sha256_file
DEFAULT_OUTPUT=COMBINED_OUTPUT
REPORT_NAME='combined_iop_report.json'
def checked_output(path):
 p=Path(path).resolve()
 if not p.is_relative_to(ROOT/'build/iop'):raise ValueError('IOP aggregate output escapes maintained build tree')
 return p

def components():
 base=base_components();result=[]
 for c in base:
  if c['verifier']=='iop_libsd_build':result.append({'library':c['library'],'manifest':data_verifier.DEFAULT_MANIFEST,'output':data_verifier.DEFAULT_OUTPUT,'verifier':'iop_libsd_data_build'})
  else:result.append(c)
 result.append({'library':'mcman','manifest':mcman_verifier.DEFAULT_MANIFEST,'output':mcman_verifier.DEFAULT_OUTPUT,'verifier':'iop_mcman_build'})
 result.append({'library':'mcman-device','manifest':device_verifier.DEFAULT_MANIFEST,'output':device_verifier.DEFAULT_OUTPUT,'verifier':'iop_mcman_device_build'})
 result.append({'library':'mcman-ecc-data','manifest':ecc_verifier.DEFAULT_MANIFEST,'output':ecc_verifier.DEFAULT_OUTPUT,'verifier':'iop_mcman_ecc_build'})
 result.append({'library':'snd989-initializer','manifest':snd989_verifier.DEFAULT_MANIFEST,'output':snd989_verifier.DEFAULT_OUTPUT,'verifier':'iop_snd989_build'})
 result.append({'library':'snd989-chain-count','manifest':chain_verifier.DEFAULT_MANIFEST,'output':chain_verifier.DEFAULT_OUTPUT,'verifier':'iop_snd989_chain_build'})
 result.append({'library':'snd989-volume','manifest':volume_verifier.DEFAULT_MANIFEST,'output':volume_verifier.DEFAULT_OUTPUT,'verifier':'iop_snd989_volume_build'})
 return result

def admission_set(definitions):
 expected={(v,str((ROOT/m).resolve()),str((ROOT/o).resolve()))for v,m,o in (
  ('iop_build','config/iop_partial.json','build/iop/module_00'),
  ('iop_libsd_data_build','config/iop_libsd_data_partial.json','build/iop/module_04_data'),
  ('iop_nosplit_build','config/iop_nosplit_partial.json','build/iop/nosplit'),
  ('iop_mcman_build','config/iop_mcman_partial.json','build/iop/module_02'),
  ('iop_mcman_device_build','config/iop_mcman_device_partial.json','build/iop/mcman_device'),
  ('iop_mcman_ecc_build','config/iop_mcman_ecc_partial.json','build/iop/mcman_ecc'),
  ('iop_snd989_build','config/iop_snd989_partial.json','build/iop/snd989_initializer'),
  ('iop_snd989_chain_build','config/iop_snd989_chain_partial.json','build/iop/snd989_chain_count'),
  ('iop_snd989_volume_build','config/iop_snd989_volume_partial.json','build/iop/snd989_volume'))}
 actual={(d.get('verifier'),str(Path(d.get('manifest','')).resolve()),str(Path(d.get('output','')).resolve()))for d in definitions}
 if len(definitions)!=9 or {d.get('verifier')for d in definitions}!={'iop_build','iop_libsd_data_build','iop_nosplit_build','iop_mcman_build','iop_mcman_device_build','iop_mcman_ecc_build','iop_snd989_build','iop_snd989_chain_build','iop_snd989_volume_build'} or actual!=expected:raise ValueError('Exact complete nine admitted components required; no optional or fallback data owner')
 return expected

def current_components(require_all=False):
 # Definition and presence checks are rejection-only; no receipt is trusted here.
 defs=components();admission_set(defs)
 for d in defs:
  manifest=Path(d['manifest']);report=Path(d['output'])/'partial_iop_report.json'
  if not manifest.is_file()or not report.is_file():raise ValueError('A mandatory staged/base manifest or report is absent')
 base_defs=base_components();base_admission_set(base_defs)
 for c in base_defs:
  if not Path(c['manifest']).is_file():raise ValueError('Missing admitted IOP source manifest: '+str(c['manifest']))
  rp=Path(c['output'])/'partial_iop_report.json'
  if not rp.is_file():raise ValueError('Missing admitted IOP source proof: '+str(rp))
 baseline=current_base_components(require_all=True);by={r['verifier']:r for r in baseline};result=[]
 for d in defs:
  manifest=Path(d['manifest']);report=Path(d['output'])/'partial_iop_report.json'
  if not manifest.is_file()or not report.is_file():raise ValueError('A mandatory staged/base manifest or report is absent')
  if d['verifier']=='iop_libsd_data_build':receipt=data_verifier.current_report(manifest,report)
  elif d['verifier']=='iop_mcman_build':receipt=mcman_verifier.current_report(manifest,report)
  elif d['verifier']=='iop_mcman_device_build':receipt=device_verifier.current_report(manifest,report)
  elif d['verifier']=='iop_mcman_ecc_build':receipt=ecc_verifier.current_report(manifest,report)
  elif d['verifier']=='iop_snd989_build':receipt=snd989_verifier.current_report(manifest,report)
  elif d['verifier']=='iop_snd989_chain_build':receipt=chain_verifier.current_report(manifest,report)
  elif d['verifier']=='iop_snd989_volume_build':receipt=volume_verifier.current_report(manifest,report)
  else:
   receipt=by[d['verifier']]['report']
   if by[d['verifier']]['manifest']!=manifest or by[d['verifier']]['report_path']!=report:raise ValueError('Original admitted component provenance differs')
  result.append({**d,'report_path':report,'report':receipt})
 return result

def disjoint(ranges):
 seen=set();ordered=[]
 for r in ranges:
  start,size=r['module_offset'],r['size'];kind=r['kind'];identity=(kind,r['name'])
  if not isinstance(start,int)or not isinstance(size,int)or start<0 or size<=0 or start%4 or size%4 or kind not in('code','initialized_data'):raise ValueError('Invalid complete scalar range or kind')
  if identity in seen:raise ValueError('Duplicate object/function source ownership')
  seen.add(identity)
  for old in ordered:
   if start<old['module_offset']+old['size']and old['module_offset']<start+size:raise ValueError('Overlapping code/data/source ranges')
  ordered.append(r)
 return sorted(ordered,key=lambda r:r['module_offset'])

def module_groups(supplied=None):
 fresh=current_components(require_all=True);expected=admission_set(fresh)
 verified=fresh if supplied is None else supplied
 if len(verified)!=9 or admission_set(verified)!=expected:raise ValueError('Incomplete or foreign receipt set')
 for item,want in zip(sorted(verified,key=lambda r:r['verifier']),sorted(fresh,key=lambda r:r['verifier'])):
  if item!=want:raise ValueError('Caller supplied false/stale component evidence')
 baseline=current_base_components(require_all=True);groups=_base_module_groups(baseline)
 libsd=next(r for r in verified if r['verifier']=='iop_libsd_data_build');receipt=libsd['report'];key=(ROOT/data_verifier.MODULE).resolve().as_posix()
 if key not in groups or groups[key]['module_sha256']!=data_verifier.MODULE_SHA:raise ValueError('Data is not the same original libsd module identity')
 if receipt['unchanged_getter']['current_unchanged_getter_report']!=next(r for r in baseline if r['verifier']=='iop_libsd_build')['report']:raise ValueError('Data extension changed or duplicated getter proof')
 g=groups[key];original=g['original'];claim=receipt['data_objects'][0];profiles=receipt['data_native_profiles'];bodies=[]
 for row in profiles:
  b,_=data_verifier.inspect_object(Elf32((ROOT/row['object']).read_bytes()),original);bodies.append(b)
 if len(bodies)!=2 or bodies[0]!=bodies[1]:raise ValueError('The two entire native data sections disagree')
 owner,target=allocated_read(original,claim['module_offset'],claim['size'])
 if owner['name']!=claim['section']or bodies[0]!=target:raise ValueError('Data claim was moved to an unverified allocated domain')
 d={'name':claim['name'],'kind':'initialized_data','source':claim['source'],'source_sha256':claim['source_sha256'],'module_offset':claim['module_offset'],'size':claim['size'],'file_offset':owner['offset']+claim['module_offset']-owner['addr'],'section':'.data','data_sha256':digest(bodies[0]),'native_data_hex':bodies[0].hex(),'verifier':'iop_libsd_data_build','component_manifest':libsd['manifest'].relative_to(ROOT).as_posix()}
 g['data_objects']=[d]
 g['evidence'].append({'path':libsd['report_path'].relative_to(ROOT).as_posix(),'sha256':sha256_file(libsd['report_path']),'freshness':receipt['freshness']})
 _add_mcman_code(groups,verified)
 _add_mcman_device_code(groups,verified)
 _add_mcman_ecc_data(groups,verified)
 _add_snd989_initializer_code(groups,verified)
 _add_snd989_chain_code(groups,verified)
 _add_snd989_volume_code(groups,verified)
 for group in groups.values():
  group.setdefault('data_objects',[])
  ranges=[{**c,'kind':'code'}for c in group['claims']]+group['data_objects'];disjoint(ranges)
  for r in ranges:
   executable=r['kind']=='code';section,payload=allocated_read(group['original'],r['module_offset'],r['size'],executable)
   if r['section']!=section['name']or r['file_offset']!=section['offset']+r['module_offset']-section['addr']:raise ValueError('False file/section/address ownership')
 return groups

def _add_mcman_code(groups,verified):
 item=next(v for v in verified if v['verifier']=='iop_mcman_build')
 verifier,report=reread(item)
 if item['report']!=report:raise ValueError('Caller supplied stale/false module02 component receipt')
 functions=report['functions'];progress=report['progress']
 if len(functions)!=2 or progress['verified_source_functions']!=2 or progress['verified_source_code_bytes']!=32 or progress['verified_source_initialized_data_bytes']!=0:raise ValueError('Unreviewed module02 code/data/source count')
 raw=(ROOT/mcman_verifier.MODULE).read_bytes()
 if digest(raw)!=mcman_verifier.MODULE_SHA:raise ValueError('Original module02 identity changed')
 original=mcman_verifier.validate_original(raw);key=(ROOT/mcman_verifier.MODULE).resolve().as_posix()
 if key not in groups:groups[key]={'module':mcman_verifier.MODULE,'module_sha256':mcman_verifier.MODULE_SHA,'raw':raw,'original':original,'claims':[],'data_objects':[],'evidence':[]}
 group=groups[key]
 if group['module_sha256']!=mcman_verifier.MODULE_SHA or group['raw']!=raw:raise ValueError('Contradictory original module02 identity')
 for f in functions:
  owner,target=allocated_read(original,f['module_offset'],f['size'],True)
  if owner['name']!='.text'or digest(target)!=f['original_code_sha256']:raise ValueError('Original module02 function has false complete section ownership')
  matching=[g for g in report['native_objects']if g['claim']==f]
  if len(matching)!=1:raise ValueError('Missing or duplicate full native module02 object')
  bodies=[verifier.inspect_object(Elf32((ROOT/p['object']).read_bytes()),f,original)[0]for p in matching[0]['profiles']]
  if len(bodies)!=2 or bodies[0]!=bodies[1]or bodies[0]!=target:raise ValueError('Native complete module02 code differs')
  for old in group['claims']:
   if f['name']==old['name']or f['module_offset']<old['module_offset']+old['size']and old['module_offset']<f['module_offset']+f['size']:raise ValueError('Duplicate or overlapping module02 ownership')
  native=bodies[0];group['claims'].append({'name':f['name'],'source':f['source'],'source_sha256':f['source_sha256'],'module_offset':f['module_offset'],'size':f['size'],'file_offset':owner['offset']+f['module_offset']-owner['addr'],'section':'.text','code_sha256':digest(native),'native_code_hex':native.hex(),'verifier':'iop_mcman_build','component_manifest':Path(item['manifest']).resolve().relative_to(ROOT).as_posix()})
 group['evidence'].append({'path':Path(item['report_path']).resolve().relative_to(ROOT).as_posix(),'sha256':digest(Path(item['report_path']).read_bytes()),'freshness':report['freshness']})
 return groups


def _add_mcman_device_code(groups,verified):
 item=next(v for v in verified if v['verifier']=='iop_mcman_device_build')
 verifier,report=reread(item)
 if item['report']!=report:raise ValueError('Caller supplied stale/false module02 component receipt')
 functions=report['functions'];progress=report['progress']
 if len(functions)!=2 or progress['verified_source_functions']!=2 or progress['verified_source_code_bytes']!=128 or progress['verified_source_initialized_data_bytes']!=0:raise ValueError('Unreviewed module02 code/data/source count')
 raw=(ROOT/device_verifier.MODULE).read_bytes()
 if digest(raw)!=device_verifier.MODULE_SHA:raise ValueError('Original module02 identity changed')
 original=device_verifier.validate_original(raw);key=(ROOT/device_verifier.MODULE).resolve().as_posix()
 if key not in groups:raise ValueError('Prior mandatory module02 identity and32-byte source owner absent')
 group=groups[key]
 if group['module_sha256']!=device_verifier.MODULE_SHA or group['raw']!=raw:raise ValueError('Contradictory original module02 identity')
 for f in functions:
  owner,target=allocated_read(original,f['module_offset'],f['size'],True)
  if owner['name']!='.text'or digest(target)!=f['original_code_sha256']:raise ValueError('Original module02 function has false complete section ownership')
  matching=[g for g in report['native_objects']if g['claim']==f]
  if len(matching)!=1:raise ValueError('Missing or duplicate full native module02 object')
  bodies=[verifier.inspect_object(Elf32((ROOT/p['object']).read_bytes()),f,original)[0]for p in matching[0]['profiles']]
  if len(bodies)!=2 or bodies[0]!=bodies[1]or bodies[0]!=target:raise ValueError('Native complete module02 code differs')
  for old in group['claims']:
   if f['name']==old['name']or f['module_offset']<old['module_offset']+old['size']and old['module_offset']<f['module_offset']+f['size']:raise ValueError('Duplicate or overlapping module02 ownership')
  native=bodies[0];group['claims'].append({'name':f['name'],'source':f['source'],'source_sha256':f['source_sha256'],'module_offset':f['module_offset'],'size':f['size'],'file_offset':owner['offset']+f['module_offset']-owner['addr'],'section':'.text','code_sha256':digest(native),'native_code_hex':native.hex(),'verifier':'iop_mcman_device_build','component_manifest':Path(item['manifest']).resolve().relative_to(ROOT).as_posix()})
 group['evidence'].append({'path':Path(item['report_path']).resolve().relative_to(ROOT).as_posix(),'sha256':digest(Path(item['report_path']).read_bytes()),'freshness':report['freshness']})
 return groups


def _add_mcman_ecc_data(groups,verified):
 item=next(v for v in verified if v['verifier']=='iop_mcman_ecc_build')
 verifier,report=reread(item)
 if item['report']!=report:raise ValueError('Caller supplied stale/false ECC data component receipt')
 if report['functions']or len(report['data_objects'])!=1 or report['progress']['verified_source_functions']or report['progress']['verified_source_code_bytes']or report['progress']['verified_source_initialized_data_bytes']!=256 or report['progress']['verified_source_BSS_bytes']:raise ValueError('ECC is one complete data-only object, no code/functions/BSS')
 raw=(ROOT/ecc_verifier.MODULE).read_bytes()
 if digest(raw)!=ecc_verifier.MODULE_SHA:raise ValueError('Original module02 identity changed')
 key=(ROOT/ecc_verifier.MODULE).resolve().as_posix()
 if key not in groups:raise ValueError('Mandatory existing module02 code owners absent')
 group=groups[key]
 if group['raw']!=raw or group['module_sha256']!=ecc_verifier.MODULE_SHA:raise ValueError('ECC cannot introduce a second original module02 identity')
 if sorted((c['module_offset'],c['size'])for c in group['claims'])!=[(0x278,64),(0x2b8,64),(0x2f8,16),(0xfb50,16)]:raise ValueError('Existing four module02 code owners changed or omitted')
 claim=report['data_objects'][0];profiles=report['data_native_profiles'];payloads=[]
 for row in profiles:
  data=(ROOT/row['object']).read_bytes();proof=verifier.inspect_object_bytes(data,group['original'])
  if proof!=row['whole_object_proof']or proof['source_functions']or proof['source_code_bytes']or proof['source_BSS_bytes']or proof['native_source_relocations']:raise ValueError('Unknown native ECC code/metadata/relocation ownership')
  elf=Elf32(data);payloads.append(elf.section_data(elf.section('.data')))
 if len(payloads)!=2 or payloads[0]!=payloads[1]or len(payloads[0])!=256:raise ValueError('Two whole native ECC data sections disagree')
 owner,target=allocated_read(group['original'],claim['module_offset'],claim['size'])
 if owner['name']!='.data'or owner['flags']!=3 or target!=payloads[0]or digest(target)!=claim['original_data_sha256']:raise ValueError('ECC moved to unverified allocated original domain')
 existing=group.setdefault('data_objects',[])
 for old in existing:
  if old['name']==claim['name']or claim['module_offset']<old['module_offset']+old['size']and old['module_offset']<claim['module_offset']+claim['size']:raise ValueError('Duplicate/overlapping module02 ECC data ownership')
 existing.append({'name':claim['name'],'kind':'initialized_data','source':claim['source'],'source_sha256':claim['source_sha256'],'module_offset':claim['module_offset'],'size':claim['size'],'file_offset':owner['offset']+claim['module_offset']-owner['addr'],'section':'.data','data_sha256':digest(payloads[0]),'native_data_hex':payloads[0].hex(),'verifier':'iop_mcman_ecc_build','component_manifest':Path(item['manifest']).resolve().relative_to(ROOT).as_posix(),'source_identifier_kind':claim['source_identifier_kind']})
 group['evidence'].append({'path':Path(item['report_path']).resolve().relative_to(ROOT).as_posix(),'sha256':sha256_file(Path(item['report_path'])),'freshness':report['freshness']})
 return groups

def _add_snd989_initializer_code(groups,verified):
 item=next(v for v in verified if v['verifier']=='iop_snd989_build');verifier,report=reread(item)
 if item['report']!=report:raise ValueError('Caller supplied stale/false whole module07 source component')
 raw=(ROOT/snd989_verifier.MODULE).read_bytes();original=snd989_verifier.validate_original(raw)
 if report['functions']!=[snd989_verifier.CLAIM]or report['data_objects']or report['progress']!=snd989_verifier.progress(raw,original):raise ValueError('Unreviewed source code/data/BSS/original preservation count')
 key=(ROOT/snd989_verifier.MODULE).resolve().as_posix()
 if key not in groups:groups[key]={'module':snd989_verifier.MODULE,'module_sha256':snd989_verifier.MODULE_SHA,'raw':raw,'original':original,'claims':[],'data_objects':[],'evidence':[]}
 group=groups[key]
 if group['module_sha256']!=snd989_verifier.MODULE_SHA or group['raw']!=raw:raise ValueError('Contradictory original module07 identity; never duplicate same original')
 f=report['functions'][0];owner,target=allocated_read(original,f['module_offset'],f['size'],True);payloads=[]
 for row in report['native_profiles']:
  data=(ROOT/row['object']).read_bytes();proof=verifier.inspect_object_bytes(data,original)
  if proof!=row['whole_object_proof']or proof['source_functions']!=1 or proof['source_code_bytes']!=76 or proof['source_initialized_data_bytes']or proof['source_BSS_bytes']or proof['native_source_relocations']:raise ValueError('False native complete source/code/data/BSS/relocation/metadata owner')
  elf=Elf32(data);payloads.append(elf.section_data(elf.section('.text')))
 if len(payloads)!=2 or payloads[0]!=payloads[1]or payloads[0]!=target or len(target)!=76 or digest(target)!=f['original_code_sha256']:raise ValueError('Two whole native module07 source code sections disagree')
 for old in group['claims']:
  if old['name']==f['name']or f['module_offset']<old['module_offset']+old['size']and old['module_offset']<f['module_offset']+f['size']:raise ValueError('Duplicate or overlapping module07 function owner')
 group.setdefault('data_objects',[])
 group['claims'].append({'name':f['name'],'source':f['source'],'source_sha256':f['source_sha256'],'module_offset':f['module_offset'],'size':f['size'],'file_offset':owner['offset']+f['module_offset']-owner['addr'],'section':'.text','code_sha256':digest(target),'native_code_hex':target.hex(),'verifier':'iop_snd989_build','component_manifest':Path(item['manifest']).resolve().relative_to(ROOT).as_posix(),'source_identifier_kind':f['source_identifier_kind']})
 group['evidence'].append({'path':Path(item['report_path']).resolve().relative_to(ROOT).as_posix(),'sha256':sha256_file(Path(item['report_path'])),'freshness':report['freshness']})
 return groups

def _add_snd989_chain_code(groups,verified):
 item=next(v for v in verified if v['verifier']=='iop_snd989_chain_build');verifier,report=reread(item)
 if item['report']!=report:raise ValueError('Caller supplied stale/false whole chain32 source component')
 raw=(ROOT/chain_verifier.MODULE).read_bytes();original=chain_verifier.validate_original(raw)
 if report['functions']!=[chain_verifier.CLAIM]or report['data_objects']or report['progress']!=chain_verifier.progress(raw,original):raise ValueError('Unreviewed complete chain32 code/data/BSS/preservation ownership')
 key=(ROOT/chain_verifier.MODULE).resolve().as_posix()
 if key not in groups:raise ValueError('Existing mandatory module07 initializer/original identity absent; never fabricate a second original')
 group=groups[key]
 if group['module_sha256']!=chain_verifier.MODULE_SHA or group['raw']!=raw:raise ValueError('Contradictory existing module07 identity')
 if not any(c['verifier']=='iop_snd989_build'and(c['module_offset'],c['size'])==(0xe490,76)for c in group['claims']):raise ValueError('Mandatory prior initializer76 owner missing')
 f=report['functions'][0];owner,target=allocated_read(original,f['module_offset'],f['size'],True);payloads=[]
 for row in report['native_profiles']:
  data=(ROOT/row['object']).read_bytes();proof=verifier.inspect_object_bytes(data,original)
  if proof!=row['whole_object_proof']or(proof['source_functions'],proof['source_code_bytes'],proof['source_initialized_data_bytes'],proof['source_BSS_bytes'],proof['native_header_flags'])!=(1,32,0,0,0x1001)or proof['native_source_relocations']:raise ValueError('False complete native chain32 owner/data/BSS/real-relocation/profile proof')
  elf=Elf32(data);payloads.append(elf.section_data(elf.section('.text')))
 if len(payloads)!=2 or payloads[0]!=payloads[1]or payloads[0]!=target or len(target)!=32 or digest(target)!=f['original_code_sha256']:raise ValueError('Two complete native chain32 source sections disagree')
 for old in group['claims']:
  if old['name']==f['name']or f['module_offset']<old['module_offset']+old['size']and old['module_offset']<f['module_offset']+f['size']:raise ValueError('Duplicate or overlapping module07 source ownership')
 group.setdefault('data_objects',[])
 group['claims'].append({'name':f['name'],'source':f['source'],'source_sha256':f['source_sha256'],'module_offset':f['module_offset'],'size':f['size'],'file_offset':owner['offset']+f['module_offset']-owner['addr'],'section':'.text','code_sha256':digest(target),'native_code_hex':target.hex(),'verifier':'iop_snd989_chain_build','component_manifest':Path(item['manifest']).resolve().relative_to(ROOT).as_posix(),'source_identifier_kind':f['source_identifier_kind']})
 group['evidence'].append({'path':Path(item['report_path']).resolve().relative_to(ROOT).as_posix(),'sha256':sha256_file(Path(item['report_path'])),'freshness':report['freshness']})
 return groups

def _add_snd989_volume_code(groups,verified):
 item=next(v for v in verified if v['verifier']=='iop_snd989_volume_build');verifier,report=reread(item)
 if item['report']!=report:raise ValueError('Caller supplied stale/false entire volume68 component')
 raw=(ROOT/volume_verifier.MODULE).read_bytes();original=volume_verifier.validate_original(raw)
 if report['functions']!=[volume_verifier.CLAIM]or report['data_objects']or report['progress']!=volume_verifier.progress(raw,original):raise ValueError('Unreviewed complete volume68 code/data/BSS/ownership')
 key=(ROOT/volume_verifier.MODULE).resolve().as_posix()
 if key not in groups:raise ValueError('Existing mandatory module07 initializer and chain original identity absent')
 group=groups[key]
 if group['module_sha256']!=volume_verifier.MODULE_SHA or group['raw']!=raw:raise ValueError('Volume cannot create contradictory original module07 identity')
 if [(c['module_offset'],c['size'])for c in sorted(group['claims'],key=lambda c:c['module_offset'])]!=[(0xe490,76),(0x18c1c,32)]:raise ValueError('Mandatory prior two module07 owners missing/duplicated/changed')
 rows=report['native_profiles']
 if len(rows)!=1 or rows[0]['profile']!='measured-volume68-iop323-existing-as3000':raise ValueError('Only one measured genuine IOP323/AS3000 volume profile admitted')
 f=report['functions'][0];owner,target=allocated_read(original,f['module_offset'],f['size'],True);row=rows[0];proof=verifier.inspect_object_bytes((ROOT/row['object']).read_bytes(),original)
 if proof!=row['whole_object_proof']or(proof['source_functions'],proof['source_code_bytes'],proof['source_initialized_data_bytes'],proof['source_BSS_bytes'],proof['native_header_flags'])!=(1,68,0,0,0x1001)or len(proof['native_source_relocations'])!=2 or proof['whole_resolved_code_sha256']!=digest(target):raise ValueError('False entire native volume68 sections/realR26/preservation')
 for old in group['claims']:
  if old['name']==f['name']or f['module_offset']<old['module_offset']+old['size']and old['module_offset']<f['module_offset']+f['size']:raise ValueError('Duplicate or overlapping module07 volume source owner')
 group['claims'].append({'name':f['name'],'source':f['source'],'source_sha256':f['source_sha256'],'module_offset':f['module_offset'],'size':f['size'],'file_offset':owner['offset']+f['module_offset']-owner['addr'],'section':'.text','code_sha256':digest(target),'native_code_hex':target.hex(),'verifier':'iop_snd989_volume_build','component_manifest':Path(item['manifest']).resolve().relative_to(ROOT).as_posix(),'source_identifier_kind':f['source_identifier_kind']})
 group['evidence'].append({'path':Path(item['report_path']).resolve().relative_to(ROOT).as_posix(),'sha256':sha256_file(Path(item['report_path'])),'freshness':report['freshness']})
 return groups

def current_modules(verified=None):
 groups=module_groups(verified);records=[]
 for key,g in sorted(groups.items()):
  claims=sorted(g['claims'],key=lambda f:f['module_offset']);data=g['data_objects'];code_size=sum(c['size']for c in claims);data_size=sum(c['size']for c in data)
  records.append({'module':g['module'],'module_sha256':g['module_sha256'],'source_claims':claims,'data_objects':data,'source_evidence':g['evidence'],'progress':{'verified_source_functions':len(claims),'verified_source_code_bytes':code_size,'verified_source_initialized_data_bytes':data_size,'preserved_original_file_bytes_excluded_from_source':len(g['raw'])-code_size-data_size,'original_file_size':len(g['raw']),'original_text_bytes_including_tables_and_stubs':g['original'].section('.text')['size']},'freshness':'CURRENT_NINE_MANDATORY_COMPONENTS_PLUS_DISJOINT_SOURCE_CODE_DATA_UNION','whole_module_source_ownership':False,'original_metadata_and_unclaimed_bytes':'PRESERVATION_NOT_SOURCE'})
 return records

def totals(records):
 keys=('verified_source_functions','verified_source_code_bytes','verified_source_initialized_data_bytes','preserved_original_file_bytes_excluded_from_source','original_file_size','original_text_bytes_including_tables_and_stubs')
 return {**{k:sum(r['progress'][k]for r in records)for k in keys},'unique_original_module_count':len(records)}

def dependencies():
 return {'registry':sha256_file(Path(__file__)),'data_verifier':sha256_file(Path(data_verifier.__file__)),'fixed_base_helpers':sha256_file(Path(__file__)),'mcman_verifier':sha256_file(Path(mcman_verifier.__file__)),'mcman_device_verifier':sha256_file(Path(device_verifier.__file__)),'mcman_ecc_verifier':sha256_file(Path(ecc_verifier.__file__)),'snd989_verifier':sha256_file(Path(snd989_verifier.__file__)),'chain_verifier':sha256_file(Path(chain_verifier.__file__)),'volume_verifier':sha256_file(Path(volume_verifier.__file__))}

def module_artifact_record(record,directory):
 path=directory/(Path(record['module']).stem+'.partial.irx')
 return {**record,'partial_module':path.relative_to(ROOT).as_posix(),
  'partial_sha256':record['module_sha256'],'full_file_bytes_equal':True}

def run(output=None):
 # Missing or stale admitted receipts must reject before any aggregate write.
 verified=current_components(require_all=True);groups=module_groups(verified);records=current_modules(verified)
 output=checked_output(output or DEFAULT_OUTPUT);output.mkdir(parents=True,exist_ok=True);report_path=output/REPORT_NAME
 report_path.write_text(json.dumps({'status':'UNVERIFIED_IOP_AGGREGATE','progress':{'verified_source_functions':0,'verified_source_code_bytes':0,'verified_source_initialized_data_bytes':0}},indent=2)+'\n')
 artifacts=[]
 for key,g in sorted(groups.items()):
  rebuilt=bytearray(g['raw'])
  for c in g['claims']:
   body=bytes.fromhex(c['native_code_hex']);a=c['file_offset'];rebuilt[a:a+c['size']]=body
  for d in g['data_objects']:
   body=bytes.fromhex(d['native_data_hex']);a=d['file_offset'];rebuilt[a:a+d['size']]=body
  if bytes(rebuilt)!=g['raw']:raise ValueError('Full composed private module differs')
  path=output/(Path(g['module']).stem+'.partial.irx');path.write_bytes(rebuilt);artifacts.append({'module':g['module'],'path':path.relative_to(ROOT).as_posix(),'sha256':sha256_file(path),'full_file_bytes_equal':True})
 report={'status':'PASS_DISJOINT_IOP_COMPONENT_SOURCE_UNIONS','report_path':report_path.relative_to(ROOT).as_posix(),'dependencies':dependencies(),'components':[{'verifier':v['verifier'],'manifest':v['manifest'].relative_to(ROOT).as_posix(),'manifest_sha256':sha256_file(v['manifest']),'report':v['report_path'].relative_to(ROOT).as_posix(),'report_sha256':sha256_file(v['report_path'])}for v in verified],'modules':[module_artifact_record(record,output)for record in records],'progress':totals(records),'artifacts':artifacts,'public_mutations':False,'whole_module_source_ownership':False,'all_source_claims_admitted':True}
 report_path.write_text(json.dumps(report,indent=2)+'\n');current_report(report_path);return report

def current_report(report_path=None):
 report_path=checked_output(report_path or DEFAULT_OUTPUT/REPORT_NAME);report=json.loads(report_path.read_text());verified=current_components(require_all=True);records=current_modules(verified)
 wanted=[{'verifier':v['verifier'],'manifest':v['manifest'].relative_to(ROOT).as_posix(),'manifest_sha256':sha256_file(v['manifest']),'report':v['report_path'].relative_to(ROOT).as_posix(),'report_sha256':sha256_file(v['report_path'])}for v in verified]
 if report.get('status')!='PASS_DISJOINT_IOP_COMPONENT_SOURCE_UNIONS'or report.get('report_path')!=report_path.relative_to(ROOT).as_posix()or report.get('dependencies')!=dependencies()or report.get('components')!=wanted:raise ValueError('Aggregate is missing, stale or has false component/provenance dependencies')
 if report.get('public_mutations')is not False:raise ValueError('Private aggregate cannot claim public mutations')
 if report.get('modules')!=[module_artifact_record(record,report_path.parent)for record in records] or report.get('progress')!=totals(records)or report.get('whole_module_source_ownership')is not False or report.get('all_source_claims_admitted')is not True:raise ValueError('False source counts, data/code ownership, preservation or duplicate original identity')
 artifacts=report.get('artifacts',[])
 if len(artifacts)!=len(records):raise ValueError('Missing/extra composed module artifact')
 for a,r in zip(artifacts,records):
  path=report_path.parent/(Path(r['module']).stem+'.partial.irx');original=(ROOT/r['module']).read_bytes()
  if a!={'module':r['module'],'path':path.relative_to(ROOT).as_posix(),'sha256':digest(original),'full_file_bytes_equal':True}or path.read_bytes()!=original:raise ValueError('Unverified composed original-preserving module')
 return {**report,'freshness':'CURRENT_ALL_NINE_COMPONENTS_DISJOINT_CODE_DATA_AND_UNIQUE_MODULE_ARTIFACTS'}

def summarize(verified):return totals(current_modules(verified))

def combine_components(verified=None,output=None):
 # Validate before touching any aggregate artifact, including failure reports.
 module_groups(verified)
 return run(output)

def _module_groups(verified):return module_groups(verified)

def reread(item):
 allowed={'iop_build','iop_libsd_data_build','iop_nosplit_build','iop_mcman_build','iop_mcman_device_build','iop_mcman_ecc_build','iop_snd989_build','iop_snd989_chain_build','iop_snd989_volume_build'}
 if item.get('verifier')not in allowed:raise ValueError('Unknown IOP verifier is not a source owner')
 definition=next(d for d in components()if d['verifier']==item['verifier'])
 for key in('manifest','output'):
  if Path(item[key]).resolve()!=Path(definition[key]).resolve():raise ValueError('Foreign admitted IOP component provenance')
 expected=Path(definition['output'])/'partial_iop_report.json'
 if Path(item.get('report_path',expected)).resolve()!=expected.resolve():raise ValueError('Foreign admitted IOP report provenance')
 verifier=importlib.import_module(item['verifier'])
 return verifier,verifier.current_report(item['manifest'],expected)

def build_components():
 # Mandatory fresh baselines precede the libsd data wrapper: no recursion.
 for component in base_components():
  importlib.import_module(component['verifier']).run(component['manifest'],component['output'])
 data_verifier.run(data_verifier.DEFAULT_MANIFEST,data_verifier.DEFAULT_OUTPUT)
 mcman_verifier.run(mcman_verifier.DEFAULT_MANIFEST,mcman_verifier.DEFAULT_OUTPUT)
 device_verifier.run(device_verifier.DEFAULT_MANIFEST,device_verifier.DEFAULT_OUTPUT)
 ecc_verifier.run(ecc_verifier.DEFAULT_MANIFEST,ecc_verifier.DEFAULT_OUTPUT)
 snd989_verifier.run(snd989_verifier.DEFAULT_MANIFEST,snd989_verifier.DEFAULT_OUTPUT)
 chain_verifier.run(chain_verifier.DEFAULT_MANIFEST,chain_verifier.DEFAULT_OUTPUT)
 volume_verifier.run(volume_verifier.DEFAULT_MANIFEST,volume_verifier.DEFAULT_OUTPUT)
 return combine_components()
