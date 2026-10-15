"""Maintained complete libsd-data and mandatory-registry rejection guards.

Only owned build artifacts and in-memory fixtures are modified. Public source,
license, primary evidence and original modules are simulated as stale without
writing them. All three unchanged baseline sources/tools/receipts are protected.
"""
import copy,json,struct,sys,time
from contextlib import contextmanager
from pathlib import Path
from unittest.mock import patch
ROOT=Path(__file__).resolve().parents[1];STAGE=ROOT/'build/iop/module_04_data'
sys.path.insert(0,str(ROOT/'tools'));sys.path.append(str(STAGE))
from common import Elf32,sha256_file
import iop_libsd_data_build as v
import iop_sources as r

CHECKED=[]
def rejected(name,fn):
 try:fn()
 except (ValueError,FileNotFoundError,KeyError,StopIteration,struct.error)as e:CHECKED.append({'name':name,'status':'REJECTED','reason':str(e)});return
 raise AssertionError('Guard unexpectedly accepted: '+name)

@contextmanager
def private_bytes(path,data):
 path=Path(path).resolve();assert path.is_relative_to(ROOT/'build/iop');old=path.read_bytes()
 try:path.write_bytes(data);yield
 finally:path.write_bytes(old)

@contextmanager
def private_missing(path):
 path=Path(path).resolve();assert path.is_relative_to(ROOT/'build/iop');saved=path.with_name(path.name+'.guard_saved');assert not saved.exists();path.rename(saved)
 try:yield
 finally:saved.rename(path)

def section_change(raw,name,key,value):
 out=bytearray(raw);e=Elf32(raw);s=e.section(name);keys=['name_offset','type','flags','addr','offset','size','link','info','alignment','entsize'];struct.pack_into('<I',out,e.shoff+s['index']*e.shentsize+4*keys.index(key),value);return bytes(out)

def symbol_change(raw,name,key,value):
 out=bytearray(raw);e=Elf32(raw);s=next(s for s in e.symbols()if s['name']==name);table=e.sections[s['table']];pos=table['offset']+s['index']*16;formats={'value':(4,'I'),'size':(8,'I'),'info':(12,'B'),'visibility':(13,'B'),'shndx':(14,'H')};offset,fmt=formats[key];struct.pack_into('<'+fmt,out,pos+offset,value);return bytes(out)

def put(obj,path,value,remove=False):
 p=obj
 for key in path[:-1]:p=p[key]
 if remove:p.pop(path[-1])
 else:p[path[-1]]=value

def mutate_report(name,path,value,report_path,reader,remove=False):
 report=json.loads(report_path.read_text());put(report,path,value,remove)
 with private_bytes(report_path,(json.dumps(report,indent=2)+'\n').encode()):rejected(name,reader)

def protected_hashes():
 paths=[ROOT/'tools'/name for name in('iop_build.py','iop_libsd_build.py','iop_nosplit_build.py','iop_sources.py','test_iop_build.py','test_iop_libsd_build.py','test_iop_nosplit_build.py','test_iop_sources.py')]
 paths +=[Path(c['manifest'])for c in r.base_components()]+[Path(c['output'])/'partial_iop_report.json'for c in r.base_components()]
 paths +=list((ROOT/'iop/src').rglob('*.c'))
 paths +=[ROOT/v.PROOF,ROOT/v.TABLE_PROOF,ROOT/v.FLOW_PROOF,ROOT/'build/iop_research/libsd_reverb_table/reverb_presets.c',ROOT/'build/reports/compiler_gcc_exception_lookup_save_width_frontier.json',ROOT/'build/reports/compiler_large_sdk_ordinary_negative_frontiers.json']
 return {p.relative_to(ROOT).as_posix():sha256_file(p)for p in paths if p.is_file()}

def main():
 start=time.time();v.run(v.DEFAULT_MANIFEST,v.DEFAULT_OUTPUT);r.combine_components();before=protected_hashes();_,original=v.load_original();manifest=json.loads(v.DEFAULT_MANIFEST.read_text());base=v.current_report();aggregate=r.current_report();assert aggregate['progress']['verified_source_functions']==24 and aggregate['progress']['verified_source_code_bytes']==608 and aggregate['progress']['verified_source_initialized_data_bytes']==936 and aggregate['progress']['preserved_original_file_bytes_excluded_from_source']==308651 and aggregate['progress']['unique_original_module_count']==4
 for row in base['data_native_profiles']:v.inspect_object(Elf32((ROOT/row['object']).read_bytes()),original)
 # Manifest fields are a fixed complete getter+data contract, not suggestions.
 for path,value in[(['schema'],'unknown'),(['module'],'disc/irx/module_00.irx'),(['module_sha256'],'0'*64),(['profiles'],['legacy-scalar-leaf-114']),(['profiles'],list(reversed(manifest['profiles']))),(['functions'],[]),(['functions'],manifest['functions']*2),(['data_objects'],[]),(['data_objects'],manifest['data_objects']*2),(['data_objects',0,'name'],'other'),(['data_objects',0,'kind'],'code'),(['data_objects',0,'source'],'iop/src/libsd/spu2_argument.c'),(['data_objects',0,'source_sha256'],'0'*64),(['data_objects',0,'module_offset'],0x3EF8),(['data_objects',0,'object_offset'],4),(['data_objects',0,'size'],676),(['data_objects',0,'section'],'.text'),(['data_objects',0,'record_count'],9),(['data_objects',0,'record_bytes'],64),(['data_objects',0,'selection_mask_offset'],4),(['data_objects',0,'coefficient_word_offsets'],list(range(0,64,4))),(['data_objects',0,'profiles'],['legacy-scalar-leaf-114']*2),(['data_objects',0,'primary_source'],v.REGISTERS),(['data_objects',0,'source_proposal_sha256'],'0'*64),(['symbol_bindings'],{})]:
  m=copy.deepcopy(manifest);put(m,path,value);rejected('manifest:'+'.'.join(map(str,path)),lambda m=m:v.validate_manifest(m))
 m=copy.deepcopy(manifest);m['unexpected_fourth_owner']={};rejected('manifest:unknown_extra_owner',lambda:v.validate_manifest(m))
 for field in('data_objects','functions','profiles','module_sha256'):
  m=copy.deepcopy(manifest);m.pop(field);rejected('manifest:missing_'+field,lambda m=m:v.validate_manifest(m))
 print('Manifest guards',len(CHECKED),flush=True)
 # Raw ELF fixtures. No byte substitutions are used in the production object.
 raw=(ROOT/base['data_native_profiles'][0]['object']).read_bytes();e=Elf32(raw);data=e.section('.data');symbol=next(s for s in e.symbols()if s['name']==v.NAME)
 fixtures=[]
 for name,key,values in[('.text','type',[4,8]),('.text','flags',[2,7]),('.text','addr',[4]),('.text','size',[4]),('.text','alignment',[1,8]),('.data','type',[4,8,9]),('.data','flags',[2,6,7]),('.data','addr',[4]),('.data','size',[0,676,684]),('.data','alignment',[1,8,16]),('.bss','type',[1,4]),('.bss','flags',[2,6]),('.bss','addr',[4]),('.bss','size',[4]),('.bss','alignment',[4])]:
  for value in values:fixtures.append((f'ELF:{name}:{key}={value}',section_change(raw,name,key,value)))
 for sec in e.sections:
  if sec['name']in('.comment','.pdr','.mdebug.abi32'):
   fixtures.append(('ELF:unknown_allocated_'+sec['name'],section_change(raw,sec['name'],'flags',2)))
   fixtures.append(('ELF:any_empty_RELA_'+sec['name'],section_change(raw,sec['name'],'type',4)))
 for key,values in[('value',[4]),('size',[0,676,684]),('info',[0x12,0x21,0x01]),('visibility',[1,2]),('shndx',[0,e.section('.text')['index'],e.section('.bss')['index']])]:
  for value in values:fixtures.append((f'ELF:symbol:{key}={value}',symbol_change(raw,v.NAME,key,value)))
 fixtures.append(('ELF:extra_defined_marker',symbol_change(raw,'gcc2_compiled.','info',0x11)))
 for offset,label in[(16,'ELF:wrong_type'),(18,'ELF:wrong_machine'),(24,'ELF:nonzero_entry'),(36,'ELF:wrong_ABI_flags')]:
  out=bytearray(raw);struct.pack_into('<H'if offset in(16,18)else'<I',out,offset,2 if offset!=36 else 0);fixtures.append((label,bytes(out)))
 for row in range(10):
  for word,label in[(0,'selection_mask'),(1,'coefficient')]:
   out=bytearray(raw);a=data['offset']+row*68+word*4;out[a]^=1;fixtures.append((f'ELF:record{row}:{label}',bytes(out)))
 out=bytearray(raw);a=data['offset'];out[a:a+68],out[a+68:a+136]=out[a+68:a+136],out[a:a+68];fixtures.append(('ELF:reordered_modes',bytes(out)))
 for name,fixture in fixtures:rejected(name,lambda fixture=fixture:v.inspect_object(Elf32(fixture),original))
 print('Native/row guards',len(CHECKED),flush=True)
 # Only mutable stage copies are touched, restoring their exact prior bytes.
 real_sha=v.sha256_file
 for field,label in[(v.SOURCE,'source'),(v.LICENSE,'license')]:
  selected=(ROOT/field).resolve()
  def stale_sha(path,selected=selected):return '0'*64 if Path(path).resolve()==selected else real_sha(path)
  with patch.object(v,'sha256_file',stale_sha):rejected('freshness:'+label,v.current_report)
 selected=(ROOT/v.SOURCE).resolve()
 def missing_sha(path):
  if Path(path).resolve()==selected:raise FileNotFoundError('Simulated missing canonical source')
  return real_sha(path)
 with patch.object(v,'sha256_file',missing_sha):rejected('freshness:missing_source',v.current_report)
 report_path=v.DEFAULT_OUTPUT/v.REPORT_NAME
 report_cases=[(['status'],'UNVERIFIED_CURRENT_BUILD'),(['manifest'],'wrong.json'),(['manifest_sha256'],'0'*64),(['report_path'],'wrong.json'),(['dependency_hashes'],{}),(['module_sha256'],'0'*64),(['functions'],[]),(['native_profiles'],[]),(['unchanged_getter','report_sha256'],'0'*64),(['data_objects'],[]),(['data_objects'],base['data_objects']*2),(['data_objects',0,'size'],684),(['original_data_ownership','file_offset'],0),(['original_data_ownership','module_offset'],0),(['original_data_ownership','section'],'.text'),(['original_data_ownership','bytes'],684),(['original_data_ownership','every_original_record'],[]),(['progress','verified_source_functions'],2),(['progress','verified_source_code_bytes'],696),(['progress','verified_source_initialized_data_bytes'],0),(['progress','preserved_original_file_bytes_excluded_from_source'],len(original.data)-16),(['whole_module_source_ownership'],True),(['public_mutations'],True),(['historical_iop_compiler_identity'],'CONFIRMED'),(['general_original_o32_abi'],'CONFIRMED'),(['all_unowned_bytes_and_metadata'],'SOURCE'),(['data_native_profiles'],base['data_native_profiles'][:1]),(['data_native_profiles'],list(reversed(base['data_native_profiles']))),(['data_native_profiles',0,'profile'],'unknown'),(['data_native_profiles',0,'compiler_flags'],['-O3']),(['data_native_profiles',0,'assembler_flags'],['-O1']),(['data_native_profiles',0,'native_input_hashes'],{}),(['data_native_profiles',0,'assembly_unchanged'],False),(['data_native_profiles',0,'assembly_sha256'],'0'*64),(['data_native_profiles',0,'object_sha256'],'0'*64),(['data_native_profiles',0,'object'],'wrong.o'),(['data_native_profiles',0,'whole_object_proof','initialized_data_bytes'],684),(['partial_module_sha256'],'0'*64),(['full_file_bytes_equal'],False)]
 for path,value in report_cases:mutate_report('data_receipt:'+'.'.join(map(str,path)),path,value,report_path,v.current_report)
 for field in('original_data_ownership','unchanged_getter','data_objects','data_native_profiles'):
  mutate_report('data_receipt:missing_'+field,[field],None,report_path,v.current_report,True)
 native_obj=ROOT/base['data_native_profiles'][0]['object'];assembly=ROOT/base['data_native_profiles'][0]['assembly'];partial=ROOT/base['partial_module']
 with private_bytes(native_obj,native_obj.read_bytes()+b'\0'):rejected('freshness:native_object',v.current_report)
 with private_missing(native_obj):rejected('freshness:missing_native_object',v.current_report)
 with private_bytes(assembly,assembly.read_bytes()+b'\n'):rejected('freshness:raw_assembly',v.current_report)
 with private_bytes(partial,partial.read_bytes()+b'\0'):rejected('freshness:partial_IRX',v.current_report)
 print('Data receipt/freshness guards',len(CHECKED),flush=True)
 # Missing original manifests/reports are simulated without writing protected files.
 real_is_file=Path.is_file
 for definition in r.base_components():
  for target in[Path(definition['manifest']),Path(definition['output'])/'partial_iop_report.json']:
   def absent(path,target=target):return False if path.resolve()==target.resolve()else real_is_file(path)
   with patch.object(Path,'is_file',absent):rejected('mandatory_original_missing:'+target.relative_to(ROOT).as_posix(),lambda:r.current_components(require_all=False))
 for target in[v.DEFAULT_MANIFEST,report_path]:
  def absent_data(path,target=target):return False if path.resolve()==target.resolve()else real_is_file(path)
  with patch.object(Path,'is_file',absent_data):rejected('mandatory_data_missing:'+target.name,lambda:r.current_components(require_all=False))
 fresh=r.current_components();rejected('registry:incomplete2components',lambda:r.module_groups(fresh[:2]));rejected('registry:duplicate_component',lambda:r.module_groups([fresh[0],fresh[0],fresh[2]]));false=copy.deepcopy(fresh);false[1]['report']['progress']['verified_source_initialized_data_bytes']=0;rejected('registry:false_supplied_receipt',lambda:r.module_groups(false))
 valid_code={'name':'getter','kind':'code','module_offset':0x3EF8,'size':16};valid_data={'name':v.NAME,'kind':'initialized_data','module_offset':v.START,'size':v.SIZE};assert len(r.disjoint([valid_code,valid_data]))==2
 for label,ranges in[('duplicate_data',[valid_data,valid_data]),('overlapping_data',[valid_data,{**valid_data,'name':'alias','module_offset':v.START+4}]),('code_data_overlap',[valid_code,{**valid_data,'module_offset':0x3EF8}]),('same_name_code',[valid_code,valid_code]),('zero_size',[{**valid_data,'size':0}]),('unaligned',[{**valid_data,'module_offset':v.START+1}]),('unknown_kind',[{**valid_data,'kind':'metadata'}])]:rejected('registry:ranges:'+label,lambda ranges=ranges:r.disjoint(ranges))
 aggregate_path=r.DEFAULT_OUTPUT/r.REPORT_NAME
 for path,value in[(['status'],'UNVERIFIED'),(['report_path'],'wrong.json'),(['dependencies'],{}),(['components'],aggregate['components'][:2]),(['components'],aggregate['components']*2),(['modules'],aggregate['modules']*2),(['progress','verified_source_functions'],19),(['progress','verified_source_code_bytes'],1020),(['progress','verified_source_initialized_data_bytes'],0),(['progress','preserved_original_file_bytes_excluded_from_source'],34962),(['progress','unique_original_module_count'],5),(['whole_module_source_ownership'],True),(['all_source_claims_admitted'],False),(['public_mutations'],True),(['artifacts'],[])]:mutate_report('aggregate_receipt:'+'.'.join(map(str,path)),path,value,aggregate_path,r.current_report)
 after=protected_hashes();assert before==after,'Protected public/frozen files changed'
 final=v.current_report();union=r.current_report();assert final['progress']['verified_source_initialized_data_bytes']==680 and union['progress']==aggregate['progress']
 report={'status':'PASS_MAINTAINED_DATA_EXTENSION_AND_THREE_COMPONENT_GUARDS','guard_count':len(CHECKED),'guards':CHECKED,'positive_native_profiles':2,'positive_records_per_profile':10,'positive_code_data_disjoint_ranges':True,'positive_current_data_report':final['freshness'],'positive_current_union_report':union['freshness'],'prospective_union_counts':union['progress'],'public_and_frozen_hashes_unchanged':True,'protected_hashes':before,'test_sha256':sha256_file(Path(__file__)),'verifier_sha256':sha256_file(Path(v.__file__)),'registry_sha256':sha256_file(Path(r.__file__)),'elapsed_seconds':time.time()-start,'public_mutations':False}
 out=STAGE/'data_guard_results.json';out.write_text(json.dumps(report,indent=2)+'\n');print('PASS',len(CHECKED),'rejectionguards;2nativeprofiles/20records;24/608/936/4modules;allpublicandfrozenfilesunchanged',flush=True)
if __name__=='__main__':main()
