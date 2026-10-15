"""Maintained exact libsd initialized reverb-data verification.

Compose all three mandatory unchanged base receipts and the original getter
with one reviewed complete680-byte data object. No new code profile or
general historical IOP ABI is admitted. Only build artifacts are written.
"""
import copy,json,re,struct,subprocess,sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'tools'))
import common,iop_build,iop_libsd_build,iop_sources
from common import Elf32,sha256_file
from iop_build import allocated_read,digest,PROFILE_FLAGS,AS_FLAGS,native_inputs

MODULE='disc/irx/module_04.irx'
MODULE_SHA='d26a8dcd121ff4ded9c819b72864ea7f4e723932cc2eab1b4f0f1c93faad43ef'
SOURCE='iop/src/libsd/reverb_presets.c'
SOURCE_SHA='0c3c451b13cdfd1e2ba8a1ff149a2102cdce9e01c069d6038cf254668c766a39'
NAME='libsd_reverb_presets';START=0x4AC0;SIZE=680
DEFAULT_MANIFEST=ROOT/'config/iop_libsd_data_partial.json';DEFAULT_OUTPUT=ROOT/'build/iop/module_04_data'
REPORT_NAME='partial_iop_report.json'
PROOF='build/reports/compiler_iop_reverb_data_private_proposal.json'
PROOF_SHA='42420258704edf1df05eed3cb1111ba9efc31febf436380e9bd045a9cc031908'
TABLE_PROOF='build/reports/compiler_iop_libsd_reverb_metadata_classification.json'
TABLE_PROOF_SHA='4e0926c87efdb800f70759f6bf83f26753f9059aef031600eedf8b106e87fc01'
FLOW_PROOF='build/reports/compiler_iop_libsd_reverb_coefficient_flow.json'
FLOW_PROOF_SHA='836e88c01a655c1412bc665788d81c9a5f2bdb5739e229f5e4ec4bed26c26dd9'
PRIMARY='build/iop_research/primary_ps2sdk/iop/sound/libsd/src/effect.c'
REGISTERS='build/iop_research/primary_ps2sdk/iop/sound/libsd/include/spu2regs.h'
PROVENANCE='build/iop_research/primary_ps2sdk/provenance.json'
LICENSE='iop/src/libsd/LICENSE.PS2SDK'
DATA_SHA='26cbea689ac597a3f0bcaff8d73568eff4c1f94753cae660a31a7c205dde9c48'
EXPECTED_DATA={'name':NAME,'kind':'initialized_data','source':SOURCE,'source_sha256':SOURCE_SHA,
 'module_offset':START,'object_offset':0,'size':SIZE,'section':'.data','original_data_sha256':DATA_SHA,
 'record_count':10,'record_bytes':68,'selection_mask_offset':0,'coefficient_word_offsets':list(range(4,68,4)),
 'profiles':['legacy-scalar-leaf-114','legacy-scalar-leaf-136'],'primary_source':PRIMARY,'register_definitions':REGISTERS,
 'provenance':PROVENANCE,'license':LICENSE,'source_proposal':PROOF,'source_proposal_sha256':PROOF_SHA,
 'original_table_proof':TABLE_PROOF,'original_table_proof_sha256':TABLE_PROOF_SHA,'coefficient_flow_proof':FLOW_PROOF,'coefficient_flow_proof_sha256':FLOW_PROOF_SHA}
GETTER_MANIFEST=ROOT/'config/iop_libsd_partial.json'
GETTER_REPORT=ROOT/'build/iop/module_04/partial_iop_report.json'

def checked_path(path,scope):
 p=Path(path);p=p if p.is_absolute()else ROOT/p;p=p.resolve()
 if not p.is_relative_to((ROOT/scope).resolve()):raise ValueError('Path escapes maintained libsd data scope')
 return p

def expected_manifest():
 base=json.loads(GETTER_MANIFEST.read_text());iop_libsd_build.validate_manifest(base)
 return {**base,'data_objects':[EXPECTED_DATA]}

def dependency_hashes():
 paths=[Path(__file__).resolve(),Path(common.__file__).resolve(),Path(iop_build.__file__).resolve(),Path(iop_libsd_build.__file__).resolve(),Path(iop_sources.__file__).resolve(),ROOT/PROOF,ROOT/TABLE_PROOF,ROOT/FLOW_PROOF,ROOT/PRIMARY,ROOT/REGISTERS,ROOT/PROVENANCE,ROOT/LICENSE]
 return {p.relative_to(ROOT).as_posix():sha256_file(p)for p in paths}

def validate_manifest(manifest):
 if manifest!=expected_manifest():raise ValueError('Unknown or missing mandatory libsd getter/data ownership, source, profile, record or proof')
 source=checked_path(ROOT/SOURCE,'iop/src/libsd')
 if sha256_file(source)!=SOURCE_SHA:raise ValueError('Staged source differs from the approved immutable ordinary record source')
 for path,sha in[(PROOF,PROOF_SHA),(TABLE_PROOF,TABLE_PROOF_SHA),(FLOW_PROOF,FLOW_PROOF_SHA)]:
  if sha256_file(ROOT/path)!=sha:raise ValueError('Pinned complete original/primary/native evidence changed')
 proposal=json.loads((ROOT/PROOF).read_text())
 if proposal['module_sha256']!=MODULE_SHA or proposal['source_sha256']!=SOURCE_SHA or proposal['prospective_data_claim_bytes']!=SIZE:raise ValueError('Evidence does not cover complete source/data/module')
 for key,path in[('effect_source_sha256',PRIMARY),('register_definitions_sha256',REGISTERS),('provenance_sha256',PROVENANCE),('license_sha256',LICENSE)]:
  if sha256_file(ROOT/path)!=proposal['primary_reference'][key]:raise ValueError('Primary/semantic/register/provenance/license source is stale')
 return source

def semantic_payload():
 text=(ROOT/PRIMARY).read_text();m=re.search(r'u32 EffectParams\[160\]\s*=\s*\{([^}]+)\}',text,re.S)
 if m is None:raise ValueError('Primary semantic table was not found')
 coeff=[int(x,16)for x in re.findall(r'0x[0-9a-fA-F]+',m[1])]
 if len(coeff)!=160:raise ValueError('Primary coefficient count differs')
 return struct.pack('<170I',*(v for k in range(10)for v in[0,*coeff[k*16:(k+1)*16]]))

def inspect_rows(payload):
 if len(payload)!=SIZE:raise ValueError('Data has an unowned gap/tail or incomplete record')
 expected=semantic_payload();rows=[]
 for k in range(10):
  actual=struct.unpack_from('<17I',payload,k*68);want=struct.unpack_from('<17I',expected,k*68)
  if actual[0]!=0:raise ValueError('Selection mask differs from actual all-parameter semantics')
  if actual[1:]!=want[1:]:raise ValueError('A packed original/primary reverb coefficient differs')
  rows.append({'record':k,'module_offset':START+k*68,'selection_mask':0,'all16_coefficient_words_match':True})
 return rows

def validate_original(original):
 if original.type!=0xFF80 or original.flags!=1 or original.entry!=0xB0:raise ValueError('Unconfirmed original IRX header cohort')
 owner,payload=allocated_read(original,START,SIZE)
 if(owner['name'],owner['type'],owner['flags'],owner['addr'],owner['offset'],owner['size'])!=('.data',1,3,0x4A60,0x4B10,2288):raise ValueError('Original allocated domain/section layout differs')
 rows=inspect_rows(payload)
 if digest(payload)!=DATA_SHA:raise ValueError('Entire initialized original span differs')
 records=iop_libsd_build.original_records(original)
 if any(START<=r['module_offset']<START+SIZE for r in records):raise ValueError('Original table has an unreviewed relocation')
 pinned=json.loads((ROOT/TABLE_PROOF).read_text())
 if pinned['module_sha256']!=MODULE_SHA or pinned['original_table']['whole_original_sha256']!=DATA_SHA:raise ValueError('Original evidence is not this full table')
 for pair in pinned['actual_original_table_pairs']:
  for role in('HI','LO'):
   r=pair[role]
   if r not in records:raise ValueError('An actual table IRX HI/LO consumer field is absent/reordered/changed')
 for proof in pinned['complete_original_consumers']:
  a=int(proof['start'],16);_,b=allocated_read(original,a,proof['bytes'],True)
  if digest(b)!=proof['original_sha256']or sha256_file(ROOT/proof['full_original'])!=proof['full_original_sha256']:raise ValueError('A complete actual original table consumer changed')
 flow=json.loads((ROOT/FLOW_PROOF).read_text());h=flow['whole_original_register_writer_helper'];_,b=allocated_read(original,int(h['start'],16),h['bytes'],True)
 if digest(b)!=h['original_sha256']or sha256_file(ROOT/h['full_original'])!=h['full_original_sha256']:raise ValueError('Complete numeric MMIO helper evidence changed')
 return payload,{'module_offset':START,'file_offset':owner['offset']+START-owner['addr'],'bytes':SIZE,'section':'.data','original_sha256':DATA_SHA,'every_original_record':rows,'all_original_relocations':[]}

def load_original():
 raw=(ROOT/MODULE).read_bytes()
 if digest(raw)!=MODULE_SHA:raise ValueError('Original complete module is stale')
 original=Elf32(raw);validate_original(original);return raw,original

def inspect_object(elf,original):
 target,ownership=validate_original(original)
 if elf.type!=1 or elf.flags!=iop_build.MEASURED_OBJECT_FLAGS or elf.entry!=0 or elf.phnum:raise ValueError('Unmeasured native data ELF header/type/flags')
 allocated=[s for s in elf.sections if s['flags']&2]
 actual=[tuple(s[k]for k in('name','type','flags','addr','size','alignment'))for s in allocated]
 if actual!=[('.text',1,6,0,0,4),('.data',1,3,0,SIZE,4),('.bss',8,3,0,0,1)]:raise ValueError('Extra/missing/malformed allocated data, code, BSS or empty-section contract')
 for name in('.text','.data','.bss'):
  if len([s for s in elf.sections if s['name']==name])!=1:raise ValueError('Duplicate allocated/empty section name')
 if any(s['type']in(4,9)for s in elf.sections):raise ValueError('Any native REL/RELA section is outside zero-relocation data ownership')
 symbols=elf.symbols();data_section=elf.section('.data');owned=[]
 for s in symbols:
  if s['type']==2:raise ValueError('A data-only object emits a function')
  if s['index']==0 and s['name']==''and s['shndx']==0 and all(s[k]==0 for k in('value','size','type','binding','visibility')):continue
  if s['shndx']==0:raise ValueError('Unknown undefined/external data symbol')
  if s['type']==3:
   if s['name']or s['value']or s['size']or s['binding']or s['visibility']or not 0<s['shndx']<len(elf.sections):raise ValueError('Unknown section symbol ownership')
   continue
  if s['name']in('gcc2_compiled.','__gnu_compiled_c'):
   if(s['value'],s['size'],s['type'],s['binding'],s['visibility'],s['shndx'])!=(0,0,0,0,0,elf.section('.text')['index']):raise ValueError('Malformed empty compiler marker')
   continue
  if(s['name'],s['value'],s['size'],s['type'],s['binding'],s['visibility'],s['shndx'])!=(NAME,0,SIZE,1,1,0,data_section['index']):raise ValueError('Unknown/partial/rebound/extra native data symbol')
  owned.append(s)
 if len(owned)!=1:raise ValueError('Missing or duplicated whole680-byte data object')
 payload=elf.section_data(data_section);rows=inspect_rows(payload)
 if payload!=target:raise ValueError('Whole emitted initialized section differs')
 proof={'all_allocated_sections_verified':True,'allocated_sections':[dict(zip(('name','type','flags','addr','size','alignment'),v))for v in actual],'only_defined_object':NAME,'functions':[],'relocations':[],'BSS_bytes':0,'emitted_code_bytes':0,'initialized_data_bytes':SIZE,'native_padding_bytes':0,'entire_initialized_section_sha256':digest(payload),'every_record':rows,'original_allocated_ownership':ownership}
 return payload,proof

def baseline_receipts():
 components=iop_sources.current_base_components(require_all=True)
 if len(components)!=3:raise ValueError('Mandatory three admitted components are incomplete')
 getter=next(c for c in components if c['verifier']=='iop_libsd_build')
 report=iop_libsd_build.current_report(GETTER_MANIFEST,GETTER_REPORT)
 if getter['report']!=report:raise ValueError('Getter baseline differs from admitted libsd receipt')
 return components,report

def getter_reference(report):
 return {'manifest':GETTER_MANIFEST.relative_to(ROOT).as_posix(),'manifest_sha256':sha256_file(GETTER_MANIFEST),'report':GETTER_REPORT.relative_to(ROOT).as_posix(),'report_sha256':sha256_file(GETTER_REPORT),'current_unchanged_getter_report':report}

def progress(raw,original):
 return {'verified_source_functions':1,'verified_source_code_bytes':16,'verified_source_initialized_data_bytes':SIZE,'preserved_original_file_bytes_excluded_from_source':len(raw)-16-SIZE,'original_file_size':len(raw),'original_text_bytes_including_tables_and_stubs':original.section('.text')['size']}

def data_record():return {**copy.deepcopy(EXPECTED_DATA),'status':'EXACT_ENTIRE_INITIALIZED_SECTION','initialized_data_bytes':SIZE,'source_code_bytes':0,'source_functions':0,'actual_relocations':0}

def run(manifest_path,output):
 manifest_path=checked_path(manifest_path,'config');output=checked_path(output,'build/iop');output.mkdir(parents=True,exist_ok=True);report_path=output/REPORT_NAME
 report_path.write_text(json.dumps({'status':'UNVERIFIED_CURRENT_BUILD','progress':{'verified_source_functions':0,'verified_source_code_bytes':0,'verified_source_initialized_data_bytes':0}},indent=2)+'\n')
 manifest_raw=manifest_path.read_bytes();manifest=json.loads(manifest_raw);source=validate_manifest(manifest);_,getter=baseline_receipts();deps=dependency_hashes();raw,original=load_original();native=[];data=None
 assembler=ROOT/'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe'
 for revision in(114,136):
  compiler=ROOT/f'tools/third_party/ee-gcc2.95.3-{revision}/bin/ee-gcc.exe';lib=compiler.parent.parent/'lib/gcc-lib/ee/2.95.3';assembly=output/f'reverb_{revision}.raw.s';obj=output/f'reverb_{revision}.o';inputs=native_inputs(revision)
  commands=[[str(compiler),'-S','-x','c',*PROFILE_FLAGS,'-B'+lib.as_posix()+'/',source.as_posix(),'-o',assembly.as_posix()],[str(assembler),*AS_FLAGS,'-o',obj.as_posix(),assembly.as_posix()]]
  for cmd in commands:
   p=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True,timeout=60)
   if p.returncode:raise RuntimeError(json.dumps({'command':cmd,'exit':p.returncode,'stderr':p.stderr}))
  payload,proof=inspect_object(Elf32(obj.read_bytes()),original)
  if data is not None and data!=payload:raise ValueError('Two complete native profiles disagree')
  if native_inputs(revision)!=inputs or sha256_file(source)!=SOURCE_SHA or dependency_hashes()!=deps:raise ValueError('Native/source/evidence/dependency changed during compile')
  data=payload;native.append({'profile':f'legacy-scalar-leaf-{revision}','compiler_flags':PROFILE_FLAGS,'assembler_flags':AS_FLAGS,'native_input_hashes':inputs,'assembly':assembly.relative_to(ROOT).as_posix(),'assembly_sha256':sha256_file(assembly),'assembly_unchanged':True,'object':obj.relative_to(ROOT).as_posix(),'object_sha256':sha256_file(obj),'whole_object_proof':proof})
 _,ownership=validate_original(original);rebuilt=bytearray(raw);a=ownership['file_offset'];rebuilt[a:a+SIZE]=data
 if bytes(rebuilt)!=raw:raise ValueError('Partial data patch changes an original byte')
 partial=output/'module_04.partial.irx';partial.write_bytes(rebuilt)
 report={'status':'PASS_LIBSD_GETTER_AND_COMPLETE_REVERB_DATA','manifest':manifest_path.relative_to(ROOT).as_posix(),'manifest_sha256':digest(manifest_raw),'report_path':report_path.relative_to(ROOT).as_posix(),'dependency_hashes':deps,'module':MODULE,'module_sha256':MODULE_SHA,'functions':getter['functions'],'native_profiles':getter['native_profiles'],'unchanged_getter':getter_reference(getter),'data_objects':[data_record()],'data_native_profiles':native,'original_data_ownership':ownership,'partial_module':partial.relative_to(ROOT).as_posix(),'partial_module_sha256':sha256_file(partial),'full_file_bytes_equal':True,'progress':progress(raw,original),'whole_module_source_ownership':False,'all_unowned_bytes_and_metadata':'PRESERVATION_EXCLUDED_FROM_SOURCE','historical_iop_compiler_identity':'UNCONFIRMED','general_original_o32_abi':'UNCONFIRMED','public_mutations':False}
 report_path.write_text(json.dumps(report,indent=2)+'\n');current_report(manifest_path,report_path);return report

def current_report(manifest_path=None,report_path=None):
 manifest_path=checked_path(manifest_path or DEFAULT_MANIFEST,'config');report_path=checked_path(report_path or DEFAULT_OUTPUT/REPORT_NAME,'build/iop');manifest_raw=manifest_path.read_bytes();manifest=json.loads(manifest_raw);validate_manifest(manifest);_,getter=baseline_receipts();raw,original=load_original();report=json.loads(report_path.read_text())
 if report.get('status')!='PASS_LIBSD_GETTER_AND_COMPLETE_REVERB_DATA' or report.get('manifest')!=manifest_path.relative_to(ROOT).as_posix()or report.get('manifest_sha256')!=digest(manifest_raw)or report.get('report_path')!=report_path.relative_to(ROOT).as_posix()or report.get('dependency_hashes')!=dependency_hashes():raise ValueError('Stale/unverified manifest/report/dependencies/provenance')
 if report.get('module')!=MODULE or report.get('module_sha256')!=MODULE_SHA or report.get('unchanged_getter')!=getter_reference(getter)or report.get('functions')!=getter['functions']or report.get('native_profiles')!=getter['native_profiles']:raise ValueError('Missing/false/stale unchanged getter or original module ownership')
 if report.get('public_mutations')is not False or report.get('historical_iop_compiler_identity')!='UNCONFIRMED'or report.get('general_original_o32_abi')!='UNCONFIRMED'or report.get('all_unowned_bytes_and_metadata')!='PRESERVATION_EXCLUDED_FROM_SOURCE':raise ValueError('False publication, historical ABI or preservation classification')
 if report.get('data_objects')!=[data_record()]:raise ValueError('Missing/duplicate/altered data-object ownership')
 _,ownership=validate_original(original)
 if report.get('original_data_ownership')!=ownership or report.get('progress')!=progress(raw,original)or report.get('whole_module_source_ownership')is not False:raise ValueError('False original span/range/count/preservation ownership')
 profiles=report.get('data_native_profiles',[])
 if [p.get('profile')for p in profiles]!=EXPECTED_DATA['profiles']:raise ValueError('Missing/reordered/duplicate/unknown native data profiles')
 for p,revision in zip(profiles,(114,136)):
  assembly=report_path.parent/f'reverb_{revision}.raw.s';obj=report_path.parent/f'reverb_{revision}.o'
  if p.get('compiler_flags')!=PROFILE_FLAGS or p.get('assembler_flags')!=AS_FLAGS or p.get('native_input_hashes')!=native_inputs(revision)or p.get('assembly_unchanged')is not True:raise ValueError('Stale or unmeasured compiler/assembler/profile contract')
  if p.get('assembly')!=assembly.relative_to(ROOT).as_posix()or p.get('object')!=obj.relative_to(ROOT).as_posix()or sha256_file(assembly)!=p.get('assembly_sha256')or sha256_file(obj)!=p.get('object_sha256'):raise ValueError('Stale raw assembly/object/hash/path')
  _,proof=inspect_object(Elf32(obj.read_bytes()),original)
  if proof!=p.get('whole_object_proof'):raise ValueError('Entire current native object proof differs')
 partial=report_path.parent/'module_04.partial.irx'
 if report.get('partial_module')!=partial.relative_to(ROOT).as_posix()or partial.read_bytes()!=raw or report.get('partial_module_sha256')!=sha256_file(partial)or report.get('full_file_bytes_equal')is not True:raise ValueError('Unverified partial-module preservation')
 return {**report,'freshness':'CURRENT_GETTER_PLUS_DATA_ALL_THREE_BASE_COMPONENTS_AND_WHOLE_NATIVE_SECTIONS_VERIFIED'}

if __name__=='__main__':run(DEFAULT_MANIFEST,DEFAULT_OUTPUT)
