"""Maintained module02 whole-object/relocation/manifest/freshness rejection guards.

Native outputs stay under build/iop/module_02/tests; protected source, original
and compiler files are simulated in memory and never modified.
"""
import copy,json,struct,sys
from pathlib import Path
ROOT=next(p for p in Path(__file__).resolve().parents if(p/'config/target.json').is_file());sys.path.insert(0,str(ROOT/'tools'))
from common import Elf32
import iop_mcman_build as v
from unittest.mock import patch

def mutate(data,offset,value,size=4):
 b=bytearray(data);struct.pack_into({1:'<B',2:'<H',4:'<I'}[size],b,offset,value);return bytes(b)
def sh(elf,sec,field):return elf.shoff+sec['index']*elf.shentsize+field*4

def run(result_path=None):
 output=v.DEFAULT_OUTPUT/'tests/native';built=v.run(v.DEFAULT_MANIFEST,output);proposal={'functions':[{**g['claim'],'native_profiles':g['profiles']}for g in built['native_objects']],'input_state_validation':built['input_state_validation']};original=v.validate_original((ROOT/v.MODULE).read_bytes());cases=[]
 def reject(name,op):
  try:op()
  except (ValueError,KeyError,IndexError,struct.error) as e:cases.append({'name':name,'status':'REJECTED','reason':str(e)})
  else:raise AssertionError('Invalid object/manifest/original admitted: '+name)
 for spec,row in zip(v.SPECS,proposal['functions']):
  for native in row['native_profiles']:
   data=(ROOT/native['object']).read_bytes();e=Elf32(data);text=e.section('.text');ds=e.section('.data');bs=e.section('.bss');ri=e.section('.reginfo');rel=e.section('.rel.text');syms=e.symbols();fn=next(s for s in syms if s['name']==spec['name']);ext=next(s for s in syms if s['name']==spec['external']);symtab=e.sections[fn['table']];fo=symtab['offset']+fn['index']*16;eo=symtab['offset']+ext['index']*16;marker=next(s for s in syms if s['name']=='gcc2_compiled.');mo=symtab['offset']+marker['index']*16
   key=spec['name']+'_'+native['revision']+'/'
   def no(name,off,val,size=4):reject(key+name,lambda:v.inspect_object_bytes(mutate(data,off,val,size),spec,original))
   no('elf_type',16,2,2);no('elf_machine',18,10,2);no('elf_flags',36,e.flags^1)
   for name,sec,field,value in [('text_small',text,5,12),('text_extra_zero_tail',text,5,20),('text_bad_address',text,3,4),('text_nonexecutable',text,2,2),('text_bad_alignment',text,8,8),('text_wrong_type',text,1,8),('unowned_initialized_data',ds,5,4),('unowned_bss',bs,5,4),('empty_data_bad_alignment',ds,8,4),('empty_data_wrong_flags',ds,2,2),('empty_bss_wrong_type',bs,1,1),('extra_allocated_reginfo',ri,2,2),('duplicate_allocated_name',bs,0,ds['name_offset']),('missing_whole_reloc_pair',rel,5,8),('extra_reloc_field',rel,5,24),('reloc_wrong_owner',rel,7,ds['index']),('reloc_wrong_symtab',rel,6,e.shstrndx),('reloc_wrong_type',rel,1,4),('reloc_bad_entsize',rel,9,4)]:no(name,sh(e,sec,field),value)
   for name,off,val,size in [('fn_offset',fo+4,4,4),('fn_size_small',fo+8,12,4),('fn_size_extra',fo+8,20,4),('fn_not_function',fo+12,0x10,1),('fn_weak',fo+12,0x22,1),('fn_visibility',fo+13,1,1),('fn_wrong_section',fo+14,ds['index'],2),('ext_value',eo+4,4,4),('ext_size',eo+8,4,4),('ext_typed_object',eo+12,0x11,1),('ext_weak',eo+12,0x20,1),('ext_visibility',eo+13,1,1),('ext_defined',eo+14,ds['index'],2),('extra_function',mo+12,2,1),('rel_hi_offset',rel['offset'],4,4),('rel_hi_kind',rel['offset']+4,(ext['index']<<8)|4,4),('rel_hi_wrong_symbol',rel['offset']+4,(fn['index']<<8)|5,4),('rel_lo_offset',rel['offset']+8,8,4),('rel_lo_kind',rel['offset']+12,(ext['index']<<8)|5,4),('rel_lo_wrong_symbol',rel['offset']+12,(fn['index']<<8)|6,4)]:no(name,off,val,size)
   for name,offset,value in [('native_hi_addend',0,0x3c020001),('native_hi_wrong_gpr',0,0x3c030000),('native_lo_addend',4,0x24420004 if spec['load_opcode']==9 else 0x8c420004),('native_lo_wrong_opcode',4,0x34420000),('native_return_wrong_register',8,0x00800008),('native_delay_not_original',12,0x00001021)]:no(name,text['offset']+offset,value)
 for i,spec in enumerate(v.SPECS):
  def bad(label,fn):
   m=copy.deepcopy(v.EXPECTED);fn(m);reject('manifest/'+spec['name']+'/'+label,lambda:v.validate_manifest(m))
  bad('boundary',lambda m:m['functions'][i].update(size=12));bad('module_address',lambda m:m['functions'][i].update(start=spec['start']+4));bad('export_ordinal',lambda m:m['functions'][i].update(ordinal=spec['ordinal']+1));bad('real_symbol_binding',lambda m:m['functions'][i].update(binding=spec['binding']+4));bad('source_sha256',lambda m:m['functions'][i].update(source_sha256='0'*64));bad('source_path',lambda m:m['functions'][i].update(source='build/iop_extra/src/not_the_source.c'));bad('source_external_name',lambda m:m['functions'][i].update(external=spec['external']+'_wrong'));bad('source_function_name',lambda m:m['functions'][i].update(name=spec['name']+'_wrong'))
 for label,fn in [('module_identity',lambda m:m.update(module='disc/irx/module_00.irx')),('module_sha256',lambda m:m.update(module_sha256='0'*64)),('profile_136_missing',lambda m:m['profiles'].pop()),('profile_schedule_changed',lambda m:m['compiler_flags'].remove('-fno-delayed-branch')),('profile_G8',lambda m:m['compiler_flags'].append('-G8')),('assembler_schedule',lambda m:m['assembler_flags'].append('-O1')),('proof_receipt',lambda m:m.update(original_contract_sha256='0'*64)),('unreviewed_extra_manifest_field',lambda m:m.update(public_counts_enabled=True)),('duplicate_ownership',lambda m:m['functions'].append(copy.deepcopy(m['functions'][0]))),('parent_independent_review_freshness',lambda m:m.update(parent_independent_review_sha256='0'*64))]:
  m=copy.deepcopy(v.EXPECTED);fn(m);reject('manifest/'+label,lambda:v.validate_manifest(m))
 data=(ROOT/v.MODULE).read_bytes();e=Elf32(data);text=e.section('.text');rs=v.original_records(e);relt=e.section('.rel.text')
 for name,offset,val,size in [('original_header_type',16,1,2),('original_flags',36,0,4),('original_entry',24,0x110,4),('original_export42_field',text['offset']+20+42*4,0x2fc,4),('original_export53_field',text['offset']+20+53*4,0xfb54,4),('original_getter42_lo',text['offset']+0x2fc,0x24421d78,4),('original_getter53_lo',text['offset']+0xfb54,0x8c42516c,4),('original_getter42_return',text['offset']+0x300,0x00800008,4),('original_getter53_delay',text['offset']+0xfb5c,0x00001021,4),('original_unowned_file_byte',text['offset']+0x120,0,4)]:reject(name,lambda off=offset,val=val,size=size:v.validate_original(mutate(data,off,val,size)))
 relbytes=e.section_data(relt);records=list(struct.iter_unpack('<II',relbytes))
 for address in(0x2f8,0xfb50,0xbc,0xe8):
  idx=next(i for i,(p,x)in enumerate(records)if p==address);offset=relt['offset']+idx*8+4;old=records[idx][1]
  reject('original_relocation_kind_'+hex(address),lambda offset=offset,old=old:v.validate_original(mutate(data,offset,(old&~255)|4)))
 # The known default branch scheduling source was genuinely compiled and remains rejected.
 default=ROOT/'build/iop_extra/native/mc_module_info_114_default.o'
 reject('ordinary_default12byte_negative_not_admitted',lambda:v.inspect_object_bytes(default.read_bytes(),v.SPECS[0],original))
 # Real source/proof/license/primary/compiler/object/report freshness guards.
 real_read=Path.read_bytes
 evidence=[s['source']for s in v.SPECS]+[v.PROOF,v.SOURCE_PROPOSAL,v.PARENT,v.PARENT_GUARDS,v.LICENSE]
 proof=json.loads((ROOT/v.PROOF).read_text());evidence.extend(r['path']for r in proof['primary_references']['records'])
 for relative in evidence:
  changed=(ROOT/relative).resolve()
  def stale(path,changed=changed):
   raw=real_read(path)
   if path.resolve()==changed:raw=raw[:-1]+bytes([raw[-1]^1])
   return raw
  with patch.object(Path,'read_bytes',stale):reject('actual_freshness/'+relative,lambda:v.current_report(v.DEFAULT_MANIFEST,output/v.REPORT_NAME))
 real_inputs=v.native_inputs
 for revision in('114','136'):
  for dependency in real_inputs(revision):
   def stale_inputs(asked,revision=revision,dependency=dependency):
    result=real_inputs(asked)
    if str(asked)==revision:result[dependency]='0'*64
    return result
   with patch.object(v,'native_inputs',stale_inputs):reject('actual_native_freshness/'+revision+'/'+dependency,lambda:v.current_report(v.DEFAULT_MANIFEST,output/v.REPORT_NAME))
 for g in built['native_objects']:
  for row in g['profiles']:
   for key in('assembly','object'):
    changed=(ROOT/row[key]).resolve()
    def stale(path,changed=changed):
     raw=real_read(path)
     return raw[:-1]+bytes([raw[-1]^1])if path.resolve()==changed else raw
    with patch.object(Path,'read_bytes',stale):reject('actual_artifact_freshness/'+row[key],lambda:v.current_report(v.DEFAULT_MANIFEST,output/v.REPORT_NAME))
 real_text=Path.read_text;report_path=(output/v.REPORT_NAME).resolve()
 for name,edit in [('wrong_report_status',lambda r:r.update(status='UNVERIFIED')),('wrong_report_manifest_path',lambda r:r.update(manifest='config/other.json')),('wrong_report_manifest_hash',lambda r:r.update(manifest_sha256='0'*64)),('wrong_report_module_hash',lambda r:r.update(module_sha256='0'*64)),('wrong_report_dependencies',lambda r:r.update(dependency_hashes={})),('wrong_report_function_tail',lambda r:r['functions'][0].update(size=20)),('wrong_report_native_count',lambda r:r['native_objects'].pop()),('wrong_report_profile_count',lambda r:r['native_objects'][0]['profiles'].pop()),('wrong_report_counts',lambda r:r['progress'].update(verified_source_code_bytes=36)),('wrong_report_data_claim',lambda r:r['progress'].update(verified_source_initialized_data_bytes=4)),('wrong_original_file_ownership',lambda r:r['original_source_ownership'][0].update(file_offset=0)),('wrong_partial_module_path',lambda r:r.update(partial_module='build/iop/module_00/module_00.partial.irx')),('false_historical_compiler',lambda r:r.update(historical_iop_compiler_identity='CONFIRMED')),('false_general_ABI',lambda r:r.update(general_original_o32_abi='CONFIRMED')),('false_whole_module_source',lambda r:r.update(whole_module_source_ownership=True)),('false_preservation_classification',lambda r:r.update(all_unowned_bytes_and_metadata='SOURCE')),('false_raw_return_states',lambda r:r['input_state_validation'].update(cases=0))]:
  mutated=json.loads(json.dumps(built));edit(mutated);text=json.dumps(mutated)
  def forged(path,*args,_text=text,**kwargs):return _text if path.resolve()==report_path else real_text(path,*args,**kwargs)
  with patch.object(Path,'read_text',forged):reject('actual_report/'+name,lambda:v.current_report(v.DEFAULT_MANIFEST,report_path))
 current=v.current_report(v.DEFAULT_MANIFEST,output/v.REPORT_NAME)
 result={'status':'PASS_MAINTAINED_MODULE02_COMPLETE_NATIVE_AND_FRESHNESS_GUARDS','rejected_cases':len(cases),'cases':cases,'fresh_native_profiles':4,'verified_source_functions':2,'verified_source_code_bytes':32,'verified_source_initialized_data_bytes':0,'unowned_preservation_counted':False,'input_state_validation':proposal['input_state_validation'],'test_source_sha256':v.sha(Path(__file__).read_bytes()),'verifier_sha256':v.sha((ROOT/'tools/iop_mcman_build.py').read_bytes())}
 destination=Path(result_path)if result_path else v.DEFAULT_OUTPUT/'tests/guard_results.json';destination=v.checked_path(destination,'build/iop/module_02');destination.parent.mkdir(parents=True,exist_ok=True);destination.write_text(json.dumps(result,indent=2)+'\n');print('PASS',len(cases),'maintained module02 ownership/byte/relocation/profile/freshness guards and',proposal['input_state_validation']['cases'],'R3000 return states.')
 return result
def main(result_path=None):return run(result_path)
if __name__=='__main__':main()
