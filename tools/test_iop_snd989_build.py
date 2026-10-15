"""In-memory negative guards; private reports only, no original/source mutation."""
import copy,hashlib,json,struct,collections
from pathlib import Path
from unittest.mock import patch as mock_patch
import iop_snd989_build as v
H=v.H

def changed(raw,off,width=1,mask=1):
 b=bytearray(raw);n=int.from_bytes(b[off:off+width],'little')^mask;b[off:off+width]=n.to_bytes(width,'little');return bytes(b)

def run():
 original,target,native,inspections=v.verify_files();labels=[];families=collections.Counter();contract=json.loads(v.CONTRACT.read_bytes());originalraw=original.data
 def reject(label,fn):
  try:fn()
  except (ValueError,AssertionError,StopIteration,IndexError,KeyError,struct.error,UnicodeError):labels.append(label);families[label.split(':',1)[0]]+=1;return
  raise AssertionError('Invalid owner/bytes unexpectedly admitted: '+label)
 for i in range(76):reject(f'original_owned_byte:{i}',lambda i=i:v.original(changed(originalraw,160+0xe490+i),contract))
 for i in range(92):reject(f'full_actual_caller_byte:{i}',lambda i=i:v.original(changed(originalraw,160+0xe4dc+i),contract))
 for s in original.sections:
  if s['type']==9:
   for i in range(0,s['size'],8):
    for field in(0,4):reject(f'complete_original_real_REL:{s["index"]}:{i//8}:{field}',lambda off=s['offset']+i+field:v.original(changed(originalraw,off,4),contract))
  if s['name']=='.iopmod':
   for i in range(s['size']):reject(f'original_IOP_metadata_byte:{i}',lambda off=s['offset']+i:v.original(changed(originalraw,off),contract))
 for q in native:
  raw=(v.ROOT/q['object']).read_bytes();e=v.Elf32(raw);t=e.section('.text');rev=q['revision']
  for i in range(76):reject(f'complete_native_code_byte:{rev}:{i}',lambda off=t['offset']+i:v.inspect_native(changed(raw,off),target))
  for key,off,width in[('type',16,2),('machine',18,2),('entry',24,4),('flags',36,4),('phnum',44,2),('shentsize',46,2),('shnum',48,2)]:reject(f'native_ELF_header:{rev}:{key}',lambda off=off,width=width:v.inspect_native(changed(raw,off,width),target))
  for sec in e.sections:
   if sec['flags']&2:
    for key,field in[('type',4),('flags',8),('addr',12),('offset',16),('size',20),('alignment',32),('link',24),('info',28),('entsize',36)]:reject(f'entire_allocated_section:{rev}:{sec["name"]}:{key}',lambda off=e.shoff+40*sec['index']+field:v.inspect_native(changed(raw,off,4),target))
   elif sec['name']:
    reject(f'foreign_allocated_metadata:{rev}:{sec["name"]}',lambda off=e.shoff+40*sec['index']+8:v.inspect_native(changed(raw,off,4,2),target))
  ri=e.section('.reginfo')
  for i in range(24):reject(f'whole_native_register_metadata:{rev}:{i}',lambda off=ri['offset']+i:v.inspect_native(changed(raw,off),target))
  st=e.section('.symtab');last=st['offset']+8*16
  for key,field,width in[('name',0,4),('offset',4,4),('whole_size',8,4),('type_binding',12,1),('visibility',13,1),('section_owner',14,2)]:reject(f'whole_native_function_owner:{rev}:{key}',lambda off=last+field,width=width:v.inspect_native(changed(raw,off,width),target))
  reject(f'extra_defined_source_symbol:{rev}',lambda:v.inspect_native(changed(raw,st['offset']+6*16+12),target))
 for q in native:
  raw=(v.ROOT/q['object']).read_bytes();e=v.Elf32(raw);rev=q['revision']
  for i in range(16):reject(f'complete_native_EI:{rev}:{i}',lambda i=i:v.inspect_native(changed(raw,i),target))
  for key,off,width in[('version',20,4),('phoff',28,4),('ehsize',40,2),('phentsize',42,2),('shstrndx',50,2)]:reject(f'complete_native_header_extra:{rev}:{key}',lambda off=off,width=width:v.inspect_native(changed(raw,off,width),target))
  for byte in(0,1):reject(f'unowned_native_trailing_payload:{rev}:{byte}',lambda byte=byte:v.inspect_native(raw+bytes([byte]),target))
  md=e.section('.mdebug');mut=bytearray(raw);struct.pack_into('<I',mut,e.shoff+40*md['index']+16,52);reject(f'whole_native_file_range_overlap:{rev}',lambda mut=bytes(mut):v.inspect_native(mut,target))
 paths={Path(v.ROOT/k).resolve():changed((v.ROOT/k).read_bytes(),0)for k in v.EXPECTED_MANIFEST['pinned_dependencies']};paths[v.SOURCE.resolve()]=v.SOURCE.read_bytes()+b'\n';paths[(v.ROOT/v.MODULE).resolve()]=changed(originalraw,0);paths[v.CONTRACT.resolve()]=v.CONTRACT.read_bytes()+b' '
 for q in native:
  for name in('object','assembly'):
   p=(v.ROOT/q[name]).resolve();paths[p]=changed(p.read_bytes(),0)
  for k in q['native_input_hashes']:
   p=(v.ROOT/k).resolve();paths[p]=changed(p.read_bytes(),0)
 paths[Path(v.__file__).resolve()]=changed(Path(v.__file__).read_bytes(),0)
 old_read=Path.read_bytes
 for path,bad in paths.items():
  def stale(p,path=path,bad=bad):return bad if p.resolve()==path else old_read(p)
  def guarded_read():
   with mock_patch.object(Path,'read_bytes',stale):v.verify_files()
  reject('source_native_dependency_freshness:'+path.relative_to(v.ROOT).as_posix(),guarded_read)
 manifest=json.loads(v.DEFAULT_MANIFEST.read_bytes());manifestpath=v.DEFAULT_MANIFEST.resolve();base_report=json.loads((v.DEFAULT_OUTPUT/v.REPORT_NAME).read_bytes())
 def fake_file(path,value):
  if path.resolve()==(v.DEFAULT_OUTPUT/v.REPORT_NAME).resolve():
   full=copy.deepcopy(base_report);full['native_profiles']=value;value=full
  b=json.dumps(value).encode()
  def stale(p):return b if p.resolve()==path.resolve()else old_read(p)
  with mock_patch.object(Path,'read_bytes',stale):v.verify_files()
 for key in manifest:
  bad=copy.deepcopy(manifest);bad[key]=None;reject('false_or_omitted_source_ownership:'+key,lambda bad=bad:fake_file(manifestpath,bad))
 for key in manifest['functions'][0]:
  bad=copy.deepcopy(manifest);bad['functions'][0][key]=False if manifest['functions'][0][key]is None else None;reject('false_whole_function_contract:'+key,lambda bad=bad:fake_file(manifestpath,bad))
 np=v.DEFAULT_OUTPUT/v.REPORT_NAME
 for rev,row in enumerate(native):
  for key in row:
   bad=copy.deepcopy(native);bad[rev][key]=None;reject(f'false_native_profile_outcome:{rev}:{key}',lambda bad=bad:fake_file(np,bad))
 for variant in('omit114','omit136','duplicate114','reverse'):
  bad={'omit114':native[1:],'omit136':native[:1],'duplicate114':[native[0],native[0]],'reverse':list(reversed(native))}[variant];reject('both_complete_profiles:'+variant,lambda bad=bad:fake_file(np,bad))
 require=v.require;require(len(labels)==len(set(labels)),'Duplicate guard labels');v.verify_files();semantic=v.semantic_states(original,native);receipt={'status':'PASS_ALL_PRIVATE_PURE_SOURCE_NATIVE_ORIGINAL_FRESHNESS_REJECTION_GUARDS','case_count':len(labels),'case_families':dict(sorted(families.items())),'case_labels_sha256':H(json.dumps(labels,separators=(',',':')).encode()),'both_profiles':['114','136'],'complete_owned_code_bytes':76,'complete_original_real_REL_count':6374,'false_manifest_native_status_count_fields_rejected':True,'all_allocated_sections_and_functions_guarded':True,'all_mutations_in_memory_only':True,'source_functions':1,'source_code_bytes':76,'source_initialized_data_bytes':0,'source_BSS_bytes':0,'source_relocations':0,'fresh_complete_original_replays':1120,'fresh_complete_native_replays':2240,'semantic_case_labels_sha256':semantic['semantic_case_labels_sha256'],'all_public_files_unchanged':True}
 out=v.DEFAULT_OUTPUT/'tests/guard_results.json';out.parent.mkdir(parents=True,exist_ok=True);out.write_text(json.dumps(receipt,indent=2)+'\n');print('PASS pure guards',len(labels),'families',len(families));return receipt
def main():return run()
if __name__=='__main__':main()
