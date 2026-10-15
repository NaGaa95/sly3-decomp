"""Private mandatory original/native/ownership/type/freshness rejection guards."""
import copy,hashlib,importlib.util,json,struct,sys,time
from pathlib import Path
from unittest.mock import patch as mock_patch
ROOT=next(p for p in Path(__file__).resolve().parents if(p/'config/target.json').is_file())
sys.path.insert(0,str(ROOT/'tools'))
import iop_snd989_chain_build as v
DIR=ROOT/'build/iop_extra/module07_chain_count'
H=lambda b:hashlib.sha256(b).hexdigest()
CASE=[]

def reject(label,call):
 try:call()
 except (ValueError,IndexError,struct.error,UnicodeError,OverflowError)as exc:CASE.append({'case':label,'status':'REJECTED','reason':str(exc)})
 else:raise AssertionError('Unreviewed source/proof/native mutation accepted: '+label)

def replace_word(data,offset):
 b=bytearray(data);struct.pack_into('<I',b,offset,struct.unpack_from('<I',b,offset)[0]^1);return bytes(b)

def field_mutations(value,path=()):
 if isinstance(value,dict):
  for key,item in value.items():
   yield from field_mutations(item,path+(key,))
 elif isinstance(value,list):
  yield path,[] if value else['FOREIGN_OWNER']
  for index,item in enumerate(value):yield from field_mutations(item,path+(index,))
 elif value is None:yield path,'FALSE_NOT_NULL'
 elif isinstance(value,bool):yield path,not value
 elif isinstance(value,int):yield path,value+1
 elif isinstance(value,str):yield path,value+'_false'
 else:raise ValueError('Unreviewed proof field type')

def set_field(value,path,new):
 q=copy.deepcopy(value);cur=q
 for key in path[:-1]:cur=cur[key]
 cur[path[-1]]=new;return q

def patched_read(path,payload,call):
 wanted=Path(path).resolve();real=Path.read_bytes
 def fake(p):return payload if p.resolve()==wanted else real(p)
 with mock_patch.object(Path,'read_bytes',fake):call()

def main():
 start=time.monotonic();e,target,native,inspections=v.verify_files();module=(ROOT/v.MODULE).read_bytes();contract=json.loads((DIR/'original_contract.json').read_bytes());manifest=json.loads(v.DEFAULT_MANIFEST.read_bytes())
 for key in manifest:
  mutated=copy.deepcopy(manifest);mutated.pop(key);reject('manifest_missing:'+key,lambda q=mutated:v.validate_manifest(q))
 mutated=copy.deepcopy(manifest);mutated['foreign_owner']=True;reject('manifest_foreign_field',lambda:v.validate_manifest(mutated))
 for path,new in field_mutations(manifest):
  q=set_field(manifest,path,new);reject('manifest_field:'+'.'.join(map(str,path)),lambda q=q:v.validate_manifest(q))
 # Type-confused integer counts cannot compare equal to a boolean.
 for key in ('source_functions','source_code_bytes','source_initialized_data_bytes','source_BSS_bytes','real_native_source_relocations'):
  q=copy.deepcopy(manifest);q[key]=bool(q[key]);reject('manifest_integer_boolean:'+key,lambda q=q:v.validate_manifest(q))
 for key in ('source_name_original','framed_E538_compiler_requirement_resolved'):
  q=copy.deepcopy(manifest);q[key]=0;reject('manifest_boolean_integer:'+key,lambda q=q:v.validate_manifest(q))
 for key in contract:
  q=copy.deepcopy(contract);q.pop(key);reject('original_contract_missing:'+key,lambda q=q:v.original(module,q))
 for off in range(16):
  b=bytearray(module);b[off]^=1;reject('original_identification_byte:'+str(off),lambda b=bytes(b):v.original(b,contract))
 for off in range(16,52,4):reject('original_header_word:'+str(off),lambda off=off:v.original(replace_word(module,off),contract))
 for sec in e.sections:
  for field in range(10):
   off=e.shoff+40*sec['index']+4*field;reject('original_section_field:'+sec['name']+':'+str(field),lambda off=off:v.original(replace_word(module,off),contract))
 for a,n,label in [(0x18c1c,32,'source32'),(0x11ce8,528,'caller528'),(0x18c14,8,'previous_JR_delay'),(0x18c3c,16,'next_entry'),(0x11ce0,8,'caller_previous_JR_delay'),(0x11ef8,8,'caller_next_entry')]:
  sec,_=v.allocated_read(e,a,n,True);base=sec['offset']+a-sec['addr']
  for byte in range(n):
   b=bytearray(module);b[base+byte]^=1;reject('original_entire_byte:'+label+':'+str(byte),lambda b=bytes(b):v.original(b,contract))
 # IRX r_offset is module-relative. Preserve and guard every real record field.
 real_rel_fields=0
 for sec in e.sections:
  if sec['type']!=9:continue
  for off in range(0,sec['size'],8):
   for member in(0,4):
    at=sec['offset']+off+member;reject('original_REL_field:'+sec['name']+':'+str(off//8)+':'+str(member),lambda at=at:v.original(replace_word(module,at),contract));real_rel_fields+=1
 v.require(real_rel_fields==12748,'All6374 original REL offset/info fields must be guarded')
 for q in native:
  revision=q['revision'];ob=(ROOT/q['object']).read_bytes();ne=v.Elf32(ob)
  for off in range(16):
   b=bytearray(ob);b[off]^=1;reject('native_identification:'+revision+':'+str(off),lambda b=bytes(b):v.inspect_native(b,target))
  for off in range(16,52,2):
   b=bytearray(ob);b[off]^=1;reject('native_header_field:'+revision+':'+str(off),lambda b=bytes(b):v.inspect_native(b,target))
  for sec in ne.sections:
   for field in range(10):
    off=ne.shoff+40*sec['index']+4*field;reject('native_section_field:'+revision+':'+sec['name']+':'+str(field),lambda off=off:v.inspect_native(replace_word(ob,off),target))
  for byte in range(32):
   b=bytearray(ob);b[52+byte]^=1;reject('native_complete_code_byte:'+revision+':'+str(byte),lambda b=bytes(b):v.inspect_native(b,target))
  for byte in range(24):
   b=bytearray(ob);b[84+byte]^=1;reject('native_reginfo_byte:'+revision+':'+str(byte),lambda b=bytes(b):v.inspect_native(b,target))
  for sym in ne.symbols():
   off=ne.section('.symtab')['offset']+16*sym['index']
   for field in(0,4,8,12):reject('native_symbol_field:'+revision+':'+str(sym['index'])+':'+str(field),lambda at=off+field:v.inspect_native(replace_word(ob,at),target))
  reject('native_trailing_payload:'+revision,lambda ob=ob:v.inspect_native(ob+b'\x01',target))
  reject('native_truncated_object:'+revision,lambda ob=ob:v.inspect_native(ob[:-1],target))
  reject('native_wrong_target32:'+revision,lambda ob=ob:v.inspect_native(ob,bytes(32)))
  # Whole native file/debug/command freshness is separate from allocated bytes.
  for off,label in [(ne.section('.mdebug')['offset'],'debug_payload'),(ne.section('.strtab')['offset']+1,'string_payload')]:
   b=bytearray(ob);b[off]^=1;reject('native_whole_file_freshness:'+revision+':'+label,lambda b=bytes(b),p=ROOT/q['object']:patched_read(p,b,v.verify_files))
 for q in json.loads((DIR/'first_trials.json').read_bytes())+json.loads((DIR/'base_trials.json').read_bytes()):
  ob=(ROOT/q['object']).read_bytes();reject('old_default_CPU44_not_admitted:'+q['label']+':'+q['revision'],lambda ob=ob:v.inspect_native(ob,target));b=bytearray(ob);struct.pack_into('<I',b,36,0x1001);reject('old44_even_with_forged_R3000_flags:'+q['label']+':'+q['revision'],lambda b=bytes(b):v.inspect_native(b,target))
 for path in (v.DEFAULT_MANIFEST,DIR/'manifest_canonical.json',DIR/'reservation.json',DIR/'original_contract.json',v.SOURCE):
  raw=path.read_bytes();reject('mandatory_owner_file_freshness:'+path.name,lambda path=path,raw=raw:patched_read(path,raw+b' ',v.verify_files))
 for rel in manifest['pinned_dependencies']:
  path=ROOT/rel;raw=path.read_bytes();reject('actual_dependency_fingerprint:'+rel,lambda path=path,raw=raw:patched_read(path,raw+b' ',v.verify_files))
 for revision in('114','136'):
  for rel in v.native_inputs(revision):
   path=ROOT/rel;raw=path.read_bytes();reject('actual_native_input:'+revision+':'+rel,lambda path=path,raw=raw:patched_read(path,raw+b'\0',v.verify_files))
 report_path=v.DEFAULT_OUTPUT/v.REPORT_NAME;base_report=json.loads(report_path.read_bytes())
 for i,q in enumerate(native):
  for key in q:
   changed=copy.deepcopy(base_report);changed['native_profiles'][i].pop(key);payload=json.dumps(changed).encode();reject('complete_native_record_omission:'+str(i)+':'+key,lambda payload=payload:patched_read(report_path,payload,v.verify_files))
  changed=copy.deepcopy(base_report);changed['native_profiles'].pop(i);payload=json.dumps(changed).encode();reject('missing_complete_native_profile:'+str(i),lambda payload=payload:patched_read(report_path,payload,v.verify_files))
 for key in base_report:
  changed=copy.deepcopy(base_report);changed[key]=None;payload=json.dumps(changed).encode();reject('false_current_entire_source_report:'+key,lambda payload=payload:patched_read(report_path,payload,v.verify_files))
 for key in base_report['source_native_semantics']:
  changed=copy.deepcopy(base_report);changed['source_native_semantics'][key]=None;payload=json.dumps(changed).encode();reject('false_canonical_original_native_semantics:'+key,lambda payload=payload:patched_read(report_path,payload,v.verify_files))
 for key in base_report['functions'][0]:
  changed=copy.deepcopy(base_report);changed['functions'][0][key]='INVALID_NOT_NULL'if base_report['functions'][0][key]is None else None;payload=json.dumps(changed).encode();reject('false_actual_public_function_owner:'+key,lambda payload=payload:patched_read(report_path,payload,v.verify_files))
 for variant,rows in [('omit114',native[1:]),('omit136',native[:1]),('duplicate114',[native[0],native[0]]),('reverse',list(reversed(native)))]:
  changed=copy.deepcopy(base_report);changed['native_profiles']=rows;payload=json.dumps(changed).encode();reject('both_whole_profiles:'+variant,lambda payload=payload:patched_read(report_path,payload,v.verify_files))
 final=v.semantic_states(e,native);v.verify_files();receipt={'status':'PASS_MAINTAINED_CHAIN32_COMPLETE_ORIGINAL_NATIVE_PROFILE_OWNERSHIP_AND_FRESHNESS_GUARDS','case_count':len(CASE),'case_label_sha256':H(json.dumps([q['case']for q in CASE],separators=(',',':')).encode()),'case_families':sorted(set(q['case'].split(':')[0]for q in CASE)),'cases':CASE,'source_functions':1,'source_code_bytes':32,'source_initialized_data_bytes':0,'source_BSS_bytes':0,'source_real_relocations':0,'all6374_original_REAL_REL_fields_guarded':real_rel_fields,'fresh_original_states':final['fresh_original_cases'],'fresh_native_states':final['fresh_native_cases'],'both_complete_native_profiles':['114','136'],'actual_compiler_assembly_untouched':True,'documented_new_assembler_option':'-mcpu=3000','native_complete_header_flags':'0x1001','semantics_receipt_sha256':H(v.SEMANTIC.read_bytes()),'verifier_sha256':H(Path(v.__file__).read_bytes()),'test_sha256':H(Path(__file__).read_bytes()),'public_mutations':False,'pure_mutations_in_memory_only':True,'elapsed_seconds':time.monotonic()-start}
 out=v.DEFAULT_OUTPUT/'tests/guard_results.json';out.parent.mkdir(parents=True,exist_ok=True);out.write_text(json.dumps(receipt,indent=2)+'\n');print('PASS private chain32 guards',len(CASE),'all12748 realREL fields; original/native states768/1536',flush=True)
if __name__=='__main__':main()
