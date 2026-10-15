"""Maintained complete ECC data/native/consumer/freshness rejection suite."""
import copy,json,struct,sys
from pathlib import Path
from unittest.mock import patch as mock_patch
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'tools'))
import iop_mcman_ecc_build as v
from common import Elf32

def patch(raw,offset,value,size=4):
 b=bytearray(raw);struct.pack_into({1:'<B',2:'<H',4:'<I'}[size],b,offset,value);return bytes(b)

def main():
 v.validate_manifest(v.EXPECTED);raw_original=(ROOT/v.MODULE).read_bytes();original=v.validate_original(raw_original);current=v.current_report();proposal={'native_profiles':current['data_native_profiles']};families={};labels=[]
 if v.semantic_states(original,proposal['native_profiles'])!=v.semantic_receipt():raise ValueError('Fresh actual native table/kernel2816 replay differed')
 def reject(family,label,fn):
  try:fn()
  except(ValueError,OSError,AssertionError,struct.error,IndexError,StopIteration,KeyError):families[family]=families.get(family,0)+1;labels.append(family+':'+label);return
  raise AssertionError('Guard accepted '+family+':'+label)
 for field in v.EXPECTED:
  changed=copy.deepcopy(v.EXPECTED);changed[field]=None
  reject('manifest',field,lambda m=changed:v.validate_manifest(m))
 for p in v.PINNED:
  changed=copy.deepcopy(v.EXPECTED);changed['pinned_dependencies'][p]='0'*64
  reject('source/primary/license/loader dependency',p,lambda m=changed:v.validate_manifest(m))
 owner,_=v.allocated_read(original,v.START,256);at=owner['offset']+v.START-owner['addr']
 for index in range(256):
  for bit in range(8):reject('entire original table',str(index)+':'+str(bit),lambda q=patch(raw_original,at+index,raw_original[at+index]^(1<<bit),1):v.validate_original(q))
 for off,value,size in[(16,1,2),(18,62,2),(20,0,4),(24,0,4),(36,0,4)]:reject('original identity',str(off),lambda q=patch(raw_original,off,value,size):v.validate_original(q))
 for native in proposal['native_profiles']:
  raw=(ROOT/native['object']).read_bytes();e=Elf32(raw)
  if v.inspect_object_bytes(raw,original)!=native['whole_object_proof']:raise ValueError('Baseline whole native table receipt stale')
  tag=native['revision']
  def objreject(family,label,data):reject(family,tag+':'+label,lambda q=data:v.inspect_object_bytes(q,original))
  sec=e.section('.data')
  for index in range(256):
   for bit in range(8):objreject('entire native table',str(index)+':'+str(bit),patch(raw,sec['offset']+index,raw[sec['offset']+index]^(1<<bit),1))
  for offset,values,size in[(7,[1,3],1),(8,[1],1),(15,[1],1),(16,[0,2],2),(18,[0,62],2),(20,[0,2],4),(24,[4,v.START],4),(28,[1],4),(36,[0,1,0x1000],4),(40,[0,64],2),(42,[32],2),(44,[1],2),(46,[0,44],2),(48,[8,10],2),(50,[0,8],2)]:
   for value in values:objreject('native ELF identity',str(offset)+':'+str(value),patch(raw,offset,value,size))
  objreject('unowned native tail','nonzero',raw+b'\x01\x02\x03\x04');objreject('unowned native tail','zero',raw+b'\0'*4)
  for name in('.text','.data','.bss'):
   s=e.section(name);head=e.shoff+s['index']*40
   for field,delta,values in[('name_offset',0,[0,e.section('.data'if name!='.data'else'.text')['name_offset']]),('type',4,[0,2,9]),('flags',8,[0,1,2,7]),('addr',12,[4,v.START]),('size',20,[s['size']+4]),('alignment',32,[2,8]),('entsize',36,[4]),('link',24,[7]),('info',28,[1])]:
    for value in values:
     if value!=s[field]:objreject('native allocated section',name+':'+field+':'+str(value),patch(raw,head+delta,value))
  for name in('.reginfo','.mdebug','.strtab'):
   s=e.section(name);head=e.shoff+s['index']*40
   for flag in(2,3,6):objreject('unknown native allocation',name+':'+str(flag),patch(raw,head+8,flag))
  for name in('.reginfo','.symtab'):
   s=e.section(name);head=e.shoff+s['index']*40
   for field,delta,values in[('type',4,[0,4,9]),('size',20,[0,s['size']+4]),('alignment',32,[1,8]),('entsize',36,[0,4]),('link',24,[0,6]),('info',28,[0,4])]:
    for value in values:
     if value!=s[field]:objreject('native metadata owner',name+':'+field+':'+str(value),patch(raw,head+delta,value))
  reg=e.section('.reginfo')
  for i in range(6):objreject('unexpected producer register metadata',str(i),patch(raw,reg['offset']+4*i,1))
  sy=e.symbols();symtab=e.section('.symtab')
  for symbol in sy:
   at=symtab['offset']+symbol['index']*16
   for field,delta,size,value in[('value',4,4,symbol['value']+4),('size',8,4,symbol['size']+4),('visibility',13,1,2),('shndx',14,2,0xfff2),('function',12,1,0x12)]:objreject('whole native symbol ownership',str(symbol['index'])+':'+field,patch(raw,at+delta,value,size))
 # Every final source/primary/proof/original dependency is required live.
 real_read=Path.read_bytes
 for path in v.PINNED:
  target=(ROOT/path).resolve()
  def stale_read(p,target=target):
   data=real_read(p)
   return data+b'\0'if p.resolve()==target else data
  with mock_patch.object(Path,'read_bytes',stale_read):reject('actual final dependency freshness',path,v.current_report)
 for revision in ['114','136']:
  inputs=v.native_inputs(revision)
  real_inputs=v.native_inputs
  for path in inputs:
   def stale_inputs(asked,revision=revision,path=path):
    data=real_inputs(asked)
    if str(asked)==revision:data[path]='0'*64
    return data
   with mock_patch.object(v,'native_inputs',stale_inputs):reject('actual native input freshness',revision+':'+path,v.current_report)
 for row in proposal['native_profiles']:
  for kind in ['object','assembly']:
   target=(ROOT/row[kind]).resolve()
   def stale_artifact(p,target=target):
    data=real_read(p)
    return data+b'\0'if p.resolve()==target else data
   with mock_patch.object(Path,'read_bytes',stale_artifact):reject('actual native artifact freshness',row['revision']+':'+kind,v.current_report)
 report_path=v.DEFAULT_OUTPUT/v.REPORT_NAME
 def put(obj,path,value):
  node=obj
  for key in path[:-1]:node=node[key]
  node[path[-1]]=value
 raw_report=json.loads(report_path.read_bytes())
 changes=[(['status'],'UNVERIFIED'),(['manifest'],'wrong.json'),(['manifest_sha256'],'0'*64),(['dependency_hashes'],{}),(['functions'],[{'name':'fake_checksum'}]),(['data_objects'],[]),(['data_objects'],raw_report['data_objects']*2),(['data_objects',0,'mutable'],False),(['data_objects',0,'module_offset'],v.START+4),(['data_objects',0,'size'],252),(['data_objects',0,'source_functions'],1),(['data_objects',0,'source_code_bytes'],116),(['data_objects',0,'source_BSS_bytes'],256),(['data_objects',0,'source_relocations'],1),(['semantic_states'],{}),(['semantic_states','native_generated_table_kernel_replays'],0),(['semantic_states','original_kernel_input_chunks'],1),(['semantic_states','status'],'CACHED_UNKNOWN'),(['progress','verified_source_functions'],1),(['progress','verified_source_code_bytes'],116),(['progress','verified_source_initialized_data_bytes'],252),(['progress','verified_source_BSS_bytes'],256),(['progress','preserved_original_file_bytes_excluded_from_source'],len(raw_original)),(['whole_module_source_ownership'],True),(['unmatched_checksum_and_correction_source_count'],116),(['all_unowned_bytes_and_metadata'],'SOURCE'),(['historical_iop_compiler_identity'],'CONFIRMED'),(['general_original_o32_abi'],'CONFIRMED'),(['public_mutations'],True),(['original_contract'],{}),(['data_native_profiles'],[]),(['data_native_profiles'],raw_report['data_native_profiles'][:1]),(['data_native_profiles'],list(reversed(raw_report['data_native_profiles']))),(['data_native_profiles',0,'native_input_hashes'],{}),(['data_native_profiles',0,'assembly_unchanged'],False),(['data_native_profiles',0,'profile'],'UNKNOWN'),(['data_native_profiles',0,'whole_object_proof'],{}),(['partial_module_sha256'],'0'*64),(['full_file_bytes_equal'],False)]
 for path,value in changes:
  changed=copy.deepcopy(raw_report);put(changed,path,value);encoded=(json.dumps(changed)+'\n').encode()
  def false_report(p,encoded=encoded):return encoded if p.resolve()==report_path.resolve()else real_read(p)
  with mock_patch.object(Path,'read_bytes',false_report):reject('actual current report',str(path),v.current_report)
 for field in ['status','functions','data_objects','semantic_states','original_contract','data_native_profiles','progress']:
  changed=copy.deepcopy(raw_report);changed.pop(field);encoded=json.dumps(changed).encode()
  def omitted_report(p,encoded=encoded):return encoded if p.resolve()==report_path.resolve()else real_read(p)
  with mock_patch.object(Path,'read_bytes',omitted_report):reject('actual omitted report',field,v.current_report)
 if len(labels)<6507:raise ValueError('Original complete pure guard floor omitted')
 if current!=v.current_report():raise ValueError('Pure/freshness guards mutated final source/native/proof artifacts')
 result={'status':'PASS_MAINTAINED_COMPLETE_ECC_DATA_FINAL_PUBLIC_SOURCE_NATIVE_AND_CONSUMER_GUARDS','tested_native_objects':2,'rejected_cases':len(labels),'case_family_counts':families,'case_labels_sha256':v.sha(('\n'.join(labels)+'\n').encode()),'original_private_guard_floor':6507,'all_whole_source_native_data_sections_symbols_metadata_and_current_dependencies_guarded':True,'actual_final_public_source':v.SOURCE,'actual_final_public_source_sha256':v.PINNED[v.SOURCE],'fresh_complete_semantic_replays':2816,'full_original_consumers_and_IRX_real_relocations_verified':True,'source_functions':0,'source_code_bytes':0,'source_initialized_data_bytes':256,'source_BSS_bytes':0,'source_relocations':0,'unmatched_checksum_and_correction_source_count':0,'verifier_sha256':v.sha(Path(v.__file__).read_bytes()),'guard_driver_sha256':v.sha(Path(__file__).read_bytes()),'mutations_in_memory_only':True,'public_files_mutated':False}
 output=v.DEFAULT_OUTPUT/'tests/guard_results.json';output.parent.mkdir(parents=True,exist_ok=True);output.write_text(json.dumps(result,indent=2)+'\n')
 print('PASS '+str(len(labels))+' complete ECC pure/freshness guards;2816 kernel/native table replays;data256;zero code/functions/BSS/relocs.',flush=True)
 return result

if __name__=='__main__':main()
