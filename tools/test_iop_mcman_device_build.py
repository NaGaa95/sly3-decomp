"""Pure rejection guards for complete two-indexed-getter native objects and claims."""
import copy,hashlib,json,struct,sys
from pathlib import Path
ROOT=next(p for p in Path(__file__).resolve().parents if(p/'config/target.json').is_file());FOLDER=ROOT/'tools';sys.path.insert(0,str(FOLDER))
import iop_mcman_device_build as v
from unittest.mock import patch as mock_patch
from common import Elf32

def patch(raw,offset,value,size=4):
 b=bytearray(raw);struct.pack_into({1:'<B',2:'<H',4:'<I'}[size],b,offset,value);return bytes(b)

def run(result_path=None):
 v.validate_manifest(v.EXPECTED);original_raw=(ROOT/v.MODULE).read_bytes();original=v.validate_original(original_raw)
 output=v.DEFAULT_OUTPUT/'tests/native';built=v.run(v.DEFAULT_MANIFEST,output)
 proposal={'functions':[{**g['claim'],'native_profiles':g['profiles']}for g in built['native_objects']],'input_state_validation':built['input_state_validation']}
 families={};labels=[]
 def reject(family,label,fn):
  try:fn()
  except(ValueError,AssertionError,struct.error,IndexError,StopIteration):
   families[family]=families.get(family,0)+1;labels.append(family+':'+label);return
  raise AssertionError('Guard accepted '+family+':'+label)
 m=v.EXPECTED
 for field in m:
  mutated=copy.deepcopy(m);mutated[field]=None
  reject('manifest',field,lambda q=mutated:v.validate_manifest(q))
 for index in range(2):
  for field in m['functions'][index]:
   mutated=copy.deepcopy(m);mutated['functions'][index][field]=None
   reject('function claim',str(index)+':'+field,lambda q=mutated:v.validate_manifest(q))
 for field in m['layout']:
  mutated=copy.deepcopy(m);mutated['layout'][field]+=1
  reject('layout',field,lambda q=mutated:v.validate_manifest(q))
 for revision in('114','136'):
  for flag in v.PROFILE_FLAGS:
   mutated=copy.deepcopy(m);mutated['profiles'][revision].remove(flag)
   reject('profile',revision+':without '+flag,lambda q=mutated:v.validate_manifest(q))
 for p in v.PINNED:
  mutated=copy.deepcopy(m);mutated['pinned_dependencies'][p]='0'*64
  reject('proof/source dependency',p,lambda q=mutated:v.validate_manifest(q))
 for spec in v.SPECS:
  owner,_=v.allocated_read(original,spec['start'],64,True);off=owner['offset']+spec['start']-owner['addr']
  for index in range(16):
   for bit in range(32):
    word=struct.unpack_from('<I',original_raw,off+4*index)[0]
    corrupted=patch(original_raw,off+4*index,word^(1<<bit))
    reject('whole original code',spec['name']+':'+str(index)+':'+str(bit),lambda q=corrupted:v.validate_original(q))
  export=owner['offset']+20+4*spec['ordinal']
  reject('original export',spec['name'],lambda q=patch(original_raw,export,spec['start']+4):v.validate_original(q))
 for offset,values,size in[(16,[1,0],2),(18,[0,62],2),(20,[0,2],4),(24,[0,0x278],4),(36,[0,0x20921000],4)]:
  for value in values:reject('original metadata',str(offset)+':'+str(value),lambda q=patch(original_raw,offset,value,size):v.validate_original(q))
 object_count=0
 for spec,function in zip(v.SPECS,proposal['functions']):
  for native in function['native_profiles']:
   raw=(ROOT/native['object']).read_bytes();e=Elf32(raw);baseline=v.inspect_object_bytes(raw,spec,original)
   if baseline!=native['whole_object_proof']:raise ValueError('Baseline strict whole-object receipt stale')
   tag=spec['name']+':'+native['revision'];object_count+=1
   def object_reject(family,label,corrupted):reject(family,tag+':'+label,lambda q=corrupted:v.inspect_object_bytes(q,spec,original))
   for offset,values,size in[(7,[1,3],1),(8,[1],1),(15,[1],1),(16,[0,2],2),(18,[0,62],2),(20,[0,2],4),(24,[4,0x278],4),(28,[1],4),(36,[0,1,0x1000],4),(40,[0,64],2),(42,[32],2),(44,[1],2),(46,[0,44],2),(48,[9,11],2),(50,[0,9],2)]:
    for value in values:object_reject('native ELF identity',str(offset)+':'+str(value),patch(raw,offset,value,size))
   text=e.section('.text')
   for index in range(16):
    for bit in range(32):
     word=struct.unpack_from('<I',raw,text['offset']+4*index)[0]
     object_reject('whole native code',str(index)+':'+str(bit),patch(raw,text['offset']+4*index,word^(1<<bit)))
   object_reject('extra native payload','extra nonzero',raw+b'\x01\x02\x03\x04')
   object_reject('extra native payload','extra zero',raw+b'\0'*4)
   for name in('.text','.data','.bss'):
    sec=e.section(name);head=e.shoff+sec['index']*40
    for field,delta,values in [('name_offset',0,[0,e.section('.text')['name_offset'] if name!='.text'else e.section('.data')['name_offset']]),('type',4,[0,2,9]),('flags',8,[0,1,2,7]),('addr',12,[4,0x26280]),('size',20,[sec['size']+4]),('alignment',32,[2,8]),('entsize',36,[4]),('link',24,[8]),('info',28,[1])]:
     for value in values:
      if value!=sec[field]:object_reject('allocated section',name+':'+field+':'+str(value),patch(raw,head+delta,value))
   for name in('.reginfo','.mdebug','.strtab'):
    sec=e.section(name);head=e.shoff+sec['index']*40
    for flag in(2,3,6):object_reject('unknown allocation',name+':'+str(flag),patch(raw,head+8,flag))
   for name in('.reginfo','.symtab','.rel.text'):
    sec=e.section(name);head=e.shoff+sec['index']*40
    for field,delta,values in [('type',4,[0,4,9]),('size',20,[0,sec['size']+4]),('alignment',32,[1,8]),('entsize',36,[0,4]),('link',24,[0,7]),('info',28,[0,4])]:
     for value in values:
      if value!=sec[field]:object_reject('native metadata owner',name+':'+field+':'+str(value),patch(raw,head+delta,value))
   reg=e.section('.reginfo')
   for offset in range(0,24,4):object_reject('no-frame register metadata',str(offset),patch(raw,reg['offset']+offset,struct.unpack_from('<I',raw,reg['offset']+offset)[0]^1))
   symbols=e.symbols();symtab=e.section('.symtab')
   for sym in symbols:
    at=symtab['offset']+sym['index']*16
    for field,delta,size,value in [('value',4,4,sym['value']+4),('size',8,4,sym['size']+4),('visibility',13,1,2),('shndx',14,2,0xfff2)]:
     object_reject('symbol ownership',str(sym['index'])+':'+field,patch(raw,at+delta,value,size))
   for sym in symbols:
    at=symtab['offset']+sym['index']*16
    object_reject('symbol ownership',str(sym['index'])+':info',patch(raw,at+12,0x12 if sym['type']!=2 else 0x11,1))
   rel=e.section('.rel.text')
   for index in range(2):
    at=rel['offset']+8*index
    for off in(0,40,48,56,64):object_reject('real relocation',str(index)+':off'+str(off),patch(raw,at,off))
    for kind in(0,1,2,4,7,255):object_reject('real relocation',str(index)+':kind'+str(kind),patch(raw,at+4,(9<<8)|kind))
    for symidx in(0,1,8,10,0xffff):object_reject('real relocation',str(index)+':symbol'+str(symidx),patch(raw,at+4,(symidx<<8)|(5 if index==0 else 6)))
   for field in spec:
    changed=copy.deepcopy(spec);changed[field]=None
    reject('unknown partial function API',tag+':'+field,lambda q=changed:v.inspect_object_bytes(raw,q,original))
 pure_core_count=len(labels)

 # Every final public source/header, proof/license/helper and exact native input
 # is tested as stale in memory; no project tree or build tree fixture is copied.
 real_read=Path.read_bytes
 for relative in built['dependency_hashes']:
  changed=(ROOT/relative).resolve()
  def stale(path,changed=changed):
   raw=real_read(path)
   return raw[:-1]+bytes([raw[-1]^1])if path.resolve()==changed else raw
  with mock_patch.object(Path,'read_bytes',stale):reject('actual final dependency freshness',relative,lambda:v.current_report(v.DEFAULT_MANIFEST,output/v.REPORT_NAME))
 real_inputs=v.native_inputs
 for revision in('114','136'):
  for dependency in real_inputs(revision):
   def stale_inputs(asked,revision=revision,dependency=dependency):
    result=real_inputs(asked)
    if str(asked)==revision:result[dependency]='0'*64
    return result
   with mock_patch.object(v,'native_inputs',stale_inputs):reject('actual native input freshness',revision+':'+dependency,lambda:v.current_report(v.DEFAULT_MANIFEST,output/v.REPORT_NAME))
 for g in built['native_objects']:
  for row in g['profiles']:
   for key in('assembly','object'):
    changed=(ROOT/row[key]).resolve()
    def stale(path,changed=changed):
     raw=real_read(path)
     return raw[:-1]+bytes([raw[-1]^1])if path.resolve()==changed else raw
    with mock_patch.object(Path,'read_bytes',stale):reject('actual final artifact freshness',row[key],lambda:v.current_report(v.DEFAULT_MANIFEST,output/v.REPORT_NAME))
 real_text=Path.read_text;report_path=(output/v.REPORT_NAME).resolve()
 edits=[('status',lambda r:r.update(status='UNVERIFIED')),('manifest path',lambda r:r.update(manifest='config/foreign.json')),('manifest hash',lambda r:r.update(manifest_sha256='0'*64)),('report path',lambda r:r.update(report_path='build/iop/module_02/partial_iop_report.json')),('module identity',lambda r:r.update(module_sha256='0'*64)),('dependencies',lambda r:r.update(dependency_hashes={})),('function ownership',lambda r:r['functions'][0].update(size=60)),('function omission',lambda r:r['functions'].pop()),('function duplication',lambda r:r['functions'].append(copy.deepcopy(r['functions'][0]))),('object group omission',lambda r:r['native_objects'].pop()),('profile omission',lambda r:r['native_objects'][0]['profiles'].pop()),('false source count',lambda r:r['progress'].update(verified_source_code_bytes=132)),('false data count',lambda r:r['progress'].update(verified_source_initialized_data_bytes=256)),('false source header',lambda r:r.update(source_header='iop/src/mcman/foreign.h')),('false header hash',lambda r:r.update(source_header_sha256='0'*64)),('false file ownership',lambda r:r['original_source_ownership'][0].update(file_offset=0)),('false initialized section',lambda r:r['native_objects'][0]['profiles'][0]['whole_object_proof'].update(initialized_data_bytes=4)),('false relocations',lambda r:r['native_objects'][0]['profiles'][0]['whole_object_proof'].update(all_source_relocations=[])),('false original states',lambda r:r['input_state_validation'].update(original_states=0)),('false FPR input contract',lambda r:r['input_state_validation'].update(stack_FPRs_HI_LO_untouched=False)),('historical compiler',lambda r:r.update(historical_iop_compiler_identity='CONFIRMED')),('general framed ABI',lambda r:r.update(general_original_o32_abi='CONFIRMED')),('whole module claim',lambda r:r.update(whole_module_source_ownership=True)),('preserved metadata counted',lambda r:r.update(all_unowned_bytes_and_metadata='SOURCE')),('partial original path',lambda r:r.update(partial_module='build/iop/module_00/module_00.partial.irx'))]
 for label,edit in edits:
  corrupted=copy.deepcopy(built);edit(corrupted);text=json.dumps(corrupted)
  def forged(path,*args,_text=text,**kwargs):return _text if path.resolve()==report_path else real_text(path,*args,**kwargs)
  with mock_patch.object(Path,'read_text',forged):reject('actual current report',label,lambda:v.current_report(v.DEFAULT_MANIFEST,report_path))
 current=v.current_report(v.DEFAULT_MANIFEST,report_path)
 if pure_core_count<4066 or current['progress']['verified_source_code_bytes']!=128:raise ValueError('Original pure guard families or entire final source cohort skipped')
 result={'status':'PASS_MAINTAINED_MCMan_DEVICE_FINAL_PUBLIC_SOURCE_AND_NATIVE_FRESHNESS_GUARDS' ,'tested_whole_native_objects':object_count,'rejected_cases':len(labels),'case_family_counts':families,'case_labels_sha256':v.sha(('\n'.join(labels)+'\n').encode()),'original_states':proposal['input_state_validation'],'native_manifest_and_code_rel_sections_sources_profiles_exports_layout_proofs_guarded':True,'zero_probe_data_counted':True,'frozen_source_proposal':v.PROPOSAL,'frozen_source_proposal_sha256':v.sha((ROOT/v.PROPOSAL).read_bytes()),'verifier_sha256':v.sha((ROOT/'tools/iop_mcman_device_build.py').read_bytes()),'guard_driver_sha256':v.sha(Path(__file__).read_bytes()),'mutations_in_memory_only':True,'public_files_mutated':False,'public_progress_delta':0}
 result['pure_core_rejected_cases']=pure_core_count;result['final_public_source_paths']=[s['source']for s in v.SPECS]+[v.HEADER];result['verified_source_functions']=2;result['verified_source_code_bytes']=128;result['verified_source_initialized_data_bytes']=0
 path=Path(result_path)if result_path else v.DEFAULT_OUTPUT/'tests/guard_results.json';path=v.checked_path(path,'build/iop/mcman_device');path.parent.mkdir(parents=True,exist_ok=True);path.write_text(json.dumps(result,indent=2)+'\n')
 print('PASS '+str(len(labels))+' pure rejection guards across'+str(object_count)+' fresh whole native objects; whole code, all real HI/LO fields, allocated sections, API/layout/source/profile/export/dependency claims.')
 return result
def main(result_path=None):return run(result_path)
if __name__=='__main__':main()
