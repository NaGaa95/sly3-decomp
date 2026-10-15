"""Maintained exact two-function module02 IOP source build.

Only the independently reviewed16-byte identification pointer getter and16-byte
semaphore-ID getter are admitted. Both measured native scalar profiles include
-fno-delayed-branch; every actual HI16/LO16 field and allocated section is checked.
Original module metadata, globals/BSS and unowned bytes remain preservation.
Historical IOP compiler identity and the general framed O32 ABI are unconfirmed.
"""
import argparse,copy,hashlib,json,random,struct,subprocess,sys
from pathlib import Path
ROOT=next(p for p in Path(__file__).resolve().parents if(p/'config/target.json').is_file());sys.path.insert(0,str(ROOT/'tools'))
import common,iop_build
from common import Elf32
from iop_build import allocated_read,digest,native_inputs,MEASURED_OBJECT_FLAGS
MODULE='disc/irx/module_02.irx'
MODULE_SHA='1fe154231adbd587f9fb6ec1c7d4201c87c76ffcc91c8615474f24d26c05c7b0'
PROOF='build/reports/iop_extra_original_contract.json'
PROOF_SHA='b59d6e4bf104ca620d46a9ff43703c8e03eeadac02ab5a30b778ec094eadefd4'
SOURCE_PROPOSAL='build/reports/iop_extra_mcman_two_leaf_private_proposal.json'
SOURCE_PROPOSAL_SHA='ed829cc05f9f853561a3cd8d478ff3c003edc73b843628fe294afc8fc07e06fe'
PARENT='build/reports/root_iop_extra_independent_review.json'
PARENT_SHA='f086dd6c3a499b529d0405be664e645180b888cb30f4d45f252023769ad0a29b'
PARENT_GUARDS='build/reports/root_iop_extra_independent_guard_validation.json'
PARENT_GUARDS_SHA='e1f74b16c58615ee00d90cec3b33f8c627c68b8794b3b09b9efa794bd8136631'
LICENSE='iop/src/mcman/LICENSE.PS2SDK'
LICENSE_SHA='1ecee940922a6886baccddd9133d17f1ce677d32c5a954fac8e48224f2766fe8'
PROFILE_FLAGS=['-Os','-G0','-mips1','-mgp32','-mfp32','-mlong32','-mcpu=r3000','-malign-functions=2','-fno-delayed-branch']
AS_FLAGS=['-G0','-mips1','-mabi=32','-O0']
PROFILES={'module02-scalar-no-delayed-branch-114':'114','module02-scalar-no-delayed-branch-136':'136'}
BASES=[0,0x1000,0x7000,0x10000,0x17ff0,0x27ff0,0xcfff0,0x80000000,0xa0000000,0xfff00000]
DEFAULT_MANIFEST=ROOT/'config/iop_mcman_partial.json'
DEFAULT_OUTPUT=ROOT/'build/iop/module_02'
REPORT_NAME='partial_iop_report.json'
def sha(b):return hashlib.sha256(b).hexdigest()
SPECS=[{'name': 'McGetModuleInfo', 'source': 'iop/src/mcman/mc_module_info.c', 'start': 760, 'size': 16, 'ordinal': 42, 'binding': 73076, 'external': 'mcman_module_id', 'load_opcode': 9, 'source_sha256': 'ba0c0d7a4020dceeac52fe8a81ec11144599143fa8a60e29643beaec21497585', 'module': 'disc/irx/module_02.irx', 'module_sha256': '1fe154231adbd587f9fb6ec1c7d4201c87c76ffcc91c8615474f24d26c05c7b0', 'module_offset': 760, 'object_offset': 0, 'export_ordinal': 42, 'original_code_sha256': '6ec45b606196632a5a6ad30dcb0abd32625b2121dbd6e456186304fd6169daad', 'signature': 'struct irx_id *McGetModuleInfo(void)', 'input_registers': ['ra: return address'], 'output_registers': ['v0: unchanged32-bit identification-record pointer'], 'FPR_inputs': [], 'stack_bytes': 0}, {'name': 'McGetSemaphoreId', 'source': 'iop/src/mcman/mc_semaphore.c', 'start': 64336, 'size': 16, 'ordinal': 53, 'binding': 151912, 'external': 'mcman_semaphore_id', 'load_opcode': 35, 'source_sha256': '12dcd001bee82ff05800ced1cbc86975fcacedf0188556814b3a4cd198e88f6e', 'module': 'disc/irx/module_02.irx', 'module_sha256': '1fe154231adbd587f9fb6ec1c7d4201c87c76ffcc91c8615474f24d26c05c7b0', 'module_offset': 64336, 'object_offset': 0, 'export_ordinal': 53, 'original_code_sha256': '705e0984fadc53442edfe878a40eaaab3e89dbe8bae9891743986f0a7ab0848c', 'signature': 'int McGetSemaphoreId(void)', 'input_registers': ['ra: return address'], 'output_registers': ['v0: unchanged signed32-bit semaphore ID'], 'FPR_inputs': [], 'stack_bytes': 0}]

def checked_path(path,scope):
 p=Path(path);p=p if p.is_absolute()else ROOT/p;p=p.resolve()
 if not p.is_relative_to((ROOT/scope).resolve()):raise ValueError('Path escapes maintained module02 scope')
 return p

def expected_manifest():
 return {'schema':'sly3-iop-mcman-two-leaf-v1','module':MODULE,'module_sha256':MODULE_SHA,'profiles':list(PROFILES),'compiler_flags':PROFILE_FLAGS,'assembler_flags':AS_FLAGS,'functions':copy.deepcopy(SPECS),'source_proposal':SOURCE_PROPOSAL,'source_proposal_sha256':SOURCE_PROPOSAL_SHA,'original_contract':PROOF,'original_contract_sha256':PROOF_SHA,'parent_independent_review':PARENT,'parent_independent_review_sha256':PARENT_SHA,'parent_guard_review':PARENT_GUARDS,'parent_guard_review_sha256':PARENT_GUARDS_SHA,'license':LICENSE,'license_sha256':LICENSE_SHA}
EXPECTED=expected_manifest()

def validate_manifest(m):
 if m!=EXPECTED:raise ValueError('Unknown manifest entry/profile/source/boundary/export/binding/proof/license or ownership')
 for p,h in[(PROOF,PROOF_SHA),(SOURCE_PROPOSAL,SOURCE_PROPOSAL_SHA),(PARENT,PARENT_SHA),(PARENT_GUARDS,PARENT_GUARDS_SHA),(LICENSE,LICENSE_SHA)]:
  if sha((ROOT/p).read_bytes())!=h:raise ValueError('Pinned original/native/independent/license evidence changed')
 for s in SPECS:
  source=checked_path(ROOT/s['source'],'iop/src/mcman')
  if sha(source.read_bytes())!=s['source_sha256']:raise ValueError('Current ordinary C source differs')
  text=source.read_text()
  if '__asm' in text or 'asm(' in text or 'volatile' in text:raise ValueError('Unreviewed original-code or scheduling adapter')
 parent=json.loads((ROOT/PARENT).read_text())
 if parent['status']!='PASS_PARENT_INDEPENDENT_WHOLE_TWO32_IOP_ZERO_DATA' or parent['blockers'] or parent['new_source_functions_pending_publication']!=2 or parent['new_code_bytes_pending_publication']!=32 or parent['initialized_data_bytes']!=0:raise ValueError('Missing independent complete code/input/boundary review')
 proof=json.loads((ROOT/PROOF).read_text())
 if proof['status']!='PASS_PRIVATE_MODULE02_ENTRIES_ARGUMENTS_BOUNDARIES_AND_FULL_CONSUMERS' or proof['blockers'] or len(proof['functions'])!=2:raise ValueError('Missing complete original entry review')
 for r in proof['primary_references']['records']:
  if sha((ROOT/r['path']).read_bytes())!=r['sha256']:raise ValueError('Primary reference stale')
 for key in('primary_irx_type_definition','loader_carry_primary'):
  r=proof[key]
  if sha((ROOT/r['path']).read_bytes())!=r['sha256']:raise ValueError('Primary type/loader evidence stale')
 if sha((ROOT/proof['external_actual_consumers']['module']).read_bytes())!=proof['external_actual_consumers']['module_sha256']:raise ValueError('Actual complete original caller stale')
 return [ROOT/s['source']for s in SPECS]

def dependency_hashes():
 proof=json.loads((ROOT/PROOF).read_text());paths=[Path(__file__).resolve(),Path(common.__file__).resolve(),Path(iop_build.__file__).resolve(),ROOT/PROOF,ROOT/SOURCE_PROPOSAL,ROOT/PARENT,ROOT/PARENT_GUARDS,ROOT/LICENSE]
 paths.extend(ROOT/r['path']for r in proof['primary_references']['records'])
 paths.extend(ROOT/proof[k]['path']for k in('primary_irx_type_definition','loader_carry_primary'))
 paths.append(ROOT/proof['external_actual_consumers']['module'])
 return {p.relative_to(ROOT).as_posix():sha(p.read_bytes())for p in paths}

def original_records(e):
 result=[]
 for s in e.sections:
  if s['type']==4 and s['size']:raise ValueError('Unexpected original RELA')
  if s['type']!=9:continue
  if s['size']%8 or s['entsize']not in(0,8):raise ValueError('Original REL extent differs')
  for p,i in struct.iter_unpack('<II',e.section_data(s)):
   if p%4 or i>>8:raise ValueError('Unreviewed original relocation domain')
   owner,b=allocated_read(e,p,4,bool(e.sections[s['info']]['flags']&4))
   if owner['index']!=s['info']:raise ValueError('Original relocation owner differs')
   result.append({'module_address':p,'type':i&255,'symbol_index':i>>8,'section':owner['name'],'word':struct.unpack('<I',b)[0]})
 return result

def native_relocations(e):
 result=[];symbols={(s['table'],s['index']):s for s in e.symbols()}
 for sec in e.sections:
  if sec['type']==4 and sec['size']:raise ValueError('Unowned native RELA')
  if sec['type']!=9:continue
  if sec['entsize']not in(0,8)or sec['size']%8:raise ValueError('Native REL extent differs')
  for off,info in struct.iter_unpack('<II',e.section_data(sec)):
   sym=symbols.get((sec['link'],info>>8));result.append({'owner':e.sections[sec['info']]['name'],'offset':off,'type':info&255,'symbol':sym['name']if sym else None,'symbol_index':info>>8})
 return result
def validate_original(data):
 e=data if isinstance(data,Elf32)else Elf32(data)
 data=e.data
 if (e.type,e.flags,e.entry)!=(0xff80,1,0x178):raise ValueError('Unreviewed original module header')
 rs=original_records(e)
 if len(rs)!=2699:raise ValueError('Original relocation fields differ')
 for s in SPECS:
  sec,b=allocated_read(e,s['start'],16,True);expected=[0x3c020000|((s['binding']+0x8000)>>16),0x24420000|(s['binding']&0xffff) if s['load_opcode']==9 else 0x8c420000|(s['binding']&0xffff),0x03e00008,0]
  if list(struct.unpack('<4I',b))!=expected or sec['name']!='.text' or sec['addr']!=0:raise ValueError('Original whole code extent/opcodes or output differ')
  r=[r for r in rs if s['start']<=r['module_address']<s['start']+16]
  if [(x['module_address'],x['type'],x['symbol_index'])for x in r]!=[(s['start'],5,0),(s['start']+4,6,0)]:raise ValueError('Original whole pair ownership differs')
  field=20+s['ordinal']*4;_,w=allocated_read(e,field,4,True)
  if struct.unpack('<I',w)[0]!=s['start']:raise ValueError('Original actual export entry differs')
  export=[r for r in rs if r['module_address']==field]
  if len(export)!=1 or export[0]['type']!=2 or export[0]['symbol_index'] or export[0]['word']!=s['start']:raise ValueError('Original export real relocation differs')
 if sha(data)!=MODULE_SHA:raise ValueError('Whole original module freshness differs')
 return e

def replay_original(body,spec,base):
 hi,lo,jr,nop=struct.unpack('<4I',body)
 # This arithmetic uses the original signed low and actual high operands.
 address=(base+((hi&0xffff)<<16)+((lo&0x7fff)-(lo&0x8000)))&0xffffffff
 if address!=(base+spec['binding'])&0xffffffff:raise ValueError('Actual original addend does not resolve binding')
 return struct.pack('<4I',(hi&0xffff0000)|((((address>>15)+1)>>1)&0xffff),(lo&0xffff0000)|((base+lo)&0xffff),jr,nop)

def link_native(payload,spec,base):
 hi,lo,jr,nop=struct.unpack('<4I',payload)
 if hi!=0x3c020000 or lo!=(0x24420000 if spec['load_opcode']==9 else 0x8c420000) or jr!=0x03e00008 or nop:raise ValueError('Unreviewed native opcode, register, delay or nonzero addend')
 address=(base+spec['binding'])&0xffffffff
 return struct.pack('<4I',hi|(((address+0x8000)>>16)&0xffff),lo|(address&0xffff),jr,nop)

def inspect_object_bytes(data,spec,original):
 e=Elf32(data)
 if e.type!=1 or e.flags!=MEASURED_OBJECT_FLAGS or e.entry or e.phnum:raise ValueError('Unmeasured native type/flags')
 allocated=[s for s in e.sections if s['flags']&2]
 if len(allocated)!=3 or {s['name']for s in allocated}!={'.text','.data','.bss'}:raise ValueError('Unknown/missing/duplicate allocated sections')
 text=next(s for s in allocated if s['name']=='.text')
 if tuple(text[k]for k in('addr','size','type','flags','alignment'))!=(0,16,1,6,4):raise ValueError('Incomplete whole code section ownership')
 for s in allocated:
  if s['name']=='.text':continue
  if tuple(s[k]for k in('addr','size','type','flags','alignment'))!=(0,0,8 if s['name']=='.bss'else 1,3,1):raise ValueError('Unowned emitted initialized data/BSS or empty-section contract')
 symbols=e.symbols();fn=[s for s in symbols if s['type']==2]
 if len(fn)!=1 or tuple(fn[0][k]for k in('name','value','size','shndx','binding','visibility'))!=(spec['name'],0,16,text['index'],1,0):raise ValueError('Every emitted function must be complete and owned')
 undefined=[s for s in symbols if s['binding'] and s['shndx']==0]
 if len(undefined)!=1 or tuple(undefined[0][k]for k in('name','value','size','type','binding','visibility'))!=(spec['external'],0,0,0,1,0):raise ValueError('Undefined external binding contract differs')
 for s in symbols:
  if s['index']==0 and not s['name']and not s['shndx']and all(s[k]==0 for k in('value','size','type','binding','visibility')):continue
  if s['type']==3:
   if s['name']or s['value']or s['size']or s['binding']or s['visibility']or not 0<s['shndx']<len(e.sections):raise ValueError('Unowned native section symbol')
   continue
  if s['name']in('gcc2_compiled.','__gnu_compiled_c'):
   if tuple(s[k]for k in('value','size','type','binding','visibility','shndx'))!=(0,0,0,0,0,text['index']):raise ValueError('Unowned/malformed compiler marker')
   continue
  if s not in fn and s not in undefined:raise ValueError('Unowned defined or external symbol')
 for name in('.text','.data','.bss'):
  if len([x for x in e.sections if x['name']==name])!=1:raise ValueError('Duplicate allocated or empty-section name')
 relsecs=[s for s in e.sections if s['type']in(4,9)]
 if len(relsecs)!=1:raise ValueError('Missing/extra relocation section')
 relsec=relsecs[0]
 if tuple(relsec[k]for k in('type','flags','addr','size','info','alignment','entsize'))!=(9,0,0,16,text['index'],4,8):raise ValueError('Relocation format/owner/complete extent differs')
 if relsec['link']!=fn[0]['table']:raise ValueError('Relocation symbol table differs')
 rel=native_relocations(e)
 if [(r['owner'],r['offset'],r['type'],r['symbol'],r['symbol_index'])for r in rel]!=[('.text',0,5,spec['external'],undefined[0]['index']),('.text',4,6,spec['external'],undefined[0]['index'])]:raise ValueError('Every native relocation must resolve the actual reviewed external')
 payload=e.section_data(text);_,target=allocated_read(original,spec['start'],16,True)
 comparisons=[]
 for base in BASES:
  native=link_native(payload,spec,base);ori=replay_original(target,spec,base)
  if native!=ori:raise ValueError('Entire native code differs after actual signed loader carry')
  comparisons.append({'load_base':hex(base),'resolved_address':hex((base+spec['binding'])&0xffffffff),'whole_original_code_sha256':sha(ori),'whole_native_code_sha256':sha(native),'status':'EXACT_ENTIRE_FUNCTION'})
 return {'status':'PASS_COMPLETE_NATIVE_OBJECT_WITH_ALL_REAL_RELOCATIONS','name':spec['name'],'code_bytes':16,'initialized_data_bytes':0,'all_allocated_sections':[{'section':s['name'],'size':s['size'],'type':s['type'],'flags':s['flags'],'alignment':s['alignment'],'sha256':sha(e.section_data(s))}for s in allocated],'source_relocations':rel,'loader_carry_cases':comparisons,'object_sha256':sha(data)}


def inspect_object(elf,claim,original):
 if claim not in SPECS:raise ValueError('Unknown complete module02 function/source/API claim')
 audit=inspect_object_bytes(elf.data,claim,original)
 linked=link_native(elf.section_data(elf.section('.text')),claim,0)
 return linked,audit

def execute(body,regs,memory):
 regs=regs[:];before=regs[:];pending=None;return_pc=None
 for w in struct.unpack('<4I',body):
  op=w>>26;rs=(w>>21)&31;rt=(w>>16)&31;rd=(w>>11)&31;old_pending=pending;pending=None
  if op==15:regs[rt]=(w&0xffff)<<16
  elif op==9:regs[rt]=(regs[rs]+((w&0x7fff)-(w&0x8000)))&0xffffffff
  elif op==35:pending=(rt,memory[(regs[rs]+((w&0x7fff)-(w&0x8000)))&0xffffffff])
  elif w==0x03e00008:return_pc=regs[31]
  elif w==0:pass
  else:raise ValueError('Unsupported original instruction in scalar return model')
  if old_pending:regs[old_pending[0]]=old_pending[1]
  regs[0]=0
 if pending or return_pc!=before[31] or any(regs[i]!=before[i]for i in range(32)if i!=2):raise ValueError('Unproved load delay/return or clobber/input contract')
 return regs[2]

def input_states(original,objects):
 rng=random.Random(0x534C5933);patterns=[0,1,0x7fff,0x8000,0x7fffffff,0x80000000,0xffffffff,0x55aa55aa,0xaa55aa55]+[rng.getrandbits(32)for _ in range(503)]
 cases=0
 for spec,obj in zip(SPECS,objects):
  payload=Elf32((ROOT/obj['object']).read_bytes()).section_data(Elf32((ROOT/obj['object']).read_bytes()).section('.text'));_,body=allocated_read(original,spec['start'],16,True)
  for base in BASES:
   for value in patterns:
    regs=[rng.getrandbits(32)for _ in range(32)];regs[0]=0;regs[31]=0x01234560
    mem={(base+spec['binding'])&0xffffffff:value}
    observed=execute(replay_original(body,spec,base),regs,mem);native=execute(link_native(payload,spec,base),regs,mem)
    expected=(base+spec['binding'])&0xffffffff if spec['load_opcode']==9 else value
    if observed!=expected or native!=expected:raise ValueError('Opaque pointer or signed integer raw result changed')
    cases+=1
 return {'status':'PASS_ORIGINAL_R3000_LOAD_DELAY_AND_RETURN_STATES','cases':cases,'load_bases':len(BASES),'values_or_nonresult_gpr_seed_states':len(patterns),'unconsumed_input_gprs_preserved':True,'stack_untouched':True,'fprs_untouched':True,'only_v0_changed':True}


def native_compile(spec,revision,output):
 source=ROOT/spec['source'];compiler=ROOT/f'tools/third_party/ee-gcc2.95.3-{revision}/bin/ee-gcc.exe';lib=compiler.parent.parent/'lib/gcc-lib/ee/2.95.3';assembler=ROOT/'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe'
 assembly=output/f'{source.stem}_{revision}.raw.s';obj=output/f'{source.stem}_{revision}.o';inputs=native_inputs(revision)
 commands=[[str(compiler),'-S','-x','c',*PROFILE_FLAGS,'-B'+lib.as_posix()+'/',source.as_posix(),'-o',assembly.as_posix()],[str(assembler),*AS_FLAGS,'-o',obj.as_posix(),assembly.as_posix()]]
 for cmd in commands:
  result=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True,timeout=60)
  if result.returncode:raise RuntimeError(json.dumps({'command':cmd,'exit':result.returncode,'stdout':result.stdout,'stderr':result.stderr}))
 return {'profile':next(k for k,v in PROFILES.items()if v==revision),'revision':revision,'compiler_flags':PROFILE_FLAGS,'assembler_flags':AS_FLAGS,'native_input_hashes':inputs,'assembly':assembly.relative_to(ROOT).as_posix(),'assembly_sha256':sha(assembly.read_bytes()),'assembly_unchanged':True,'object':obj.relative_to(ROOT).as_posix(),'object_sha256':sha(obj.read_bytes())}

def load_original():
 raw=(ROOT/MODULE).read_bytes();return raw,validate_original(raw)

def progress(raw,original):
 return {'verified_source_functions':2,'verified_source_code_bytes':32,'verified_source_initialized_data_bytes':0,'preserved_original_file_bytes_excluded_from_source':len(raw)-32,'original_file_size':len(raw),'original_text_bytes_including_tables_and_stubs':original.section('.text')['size']}

def run(manifest_path=None,output=None):
 manifest_path=checked_path(manifest_path or DEFAULT_MANIFEST,'config');output=checked_path(output or DEFAULT_OUTPUT,'build/iop/module_02');output.mkdir(parents=True,exist_ok=True);report_path=output/REPORT_NAME
 report_path.write_text(json.dumps({'status':'UNVERIFIED_CURRENT_MODULE02_BUILD','progress':{'verified_source_functions':0,'verified_source_code_bytes':0,'verified_source_initialized_data_bytes':0},'previous_success_must_not_count':True},indent=2)+'\n')
 manifest_bytes=manifest_path.read_bytes();manifest=json.loads(manifest_bytes);validate_manifest(manifest);deps=dependency_hashes();raw,original=load_original();groups=[];chosen=[];rebuilt=bytearray(raw);ownership=[]
 for spec in SPECS:
  rows=[];code=None
  for revision in('114','136'):
   row=native_compile(spec,revision,output);payload,audit=inspect_object(Elf32((ROOT/row['object']).read_bytes()),spec,original)
   if code is not None and payload!=code:raise ValueError('Two whole native revisions disagree')
   if native_inputs(revision)!=row['native_input_hashes']or sha((ROOT/spec['source']).read_bytes())!=spec['source_sha256']or dependency_hashes()!=deps:raise ValueError('Source/native/compiler/proof dependency changed during compilation')
   code=payload;rows.append({**row,'whole_object_proof':audit})
  groups.append({'claim':spec,'profiles':rows});chosen.append(rows[0]);owner,target=allocated_read(original,spec['start'],16,True);a=owner['offset']+spec['start']-owner['addr'];rebuilt[a:a+16]=code;ownership.append({'name':spec['name'],'module_offset':spec['start'],'size':16,'file_offset':a,'section':'.text'})
 if bytes(rebuilt)!=raw:raise ValueError('Partial source module changes an original byte')
 states=input_states(original,chosen);partial=output/'module_02.partial.irx';partial.write_bytes(rebuilt)
 report={'status':'PASS_SEPARATE_TWO_MCMan_COMPLETE_LEAF_SOURCE_BUILD','manifest':manifest_path.relative_to(ROOT).as_posix(),'manifest_sha256':sha(manifest_bytes),'report_path':report_path.relative_to(ROOT).as_posix(),'dependency_hashes':deps,'module':MODULE,'module_sha256':MODULE_SHA,'functions':copy.deepcopy(SPECS),'native_objects':groups,'progress':progress(raw,original),'original_source_ownership':ownership,'input_state_validation':states,'partial_module':partial.relative_to(ROOT).as_posix(),'partial_module_sha256':sha(partial.read_bytes()),'full_file_bytes_equal':True,'historical_iop_compiler_identity':'UNCONFIRMED','general_original_o32_abi':'UNCONFIRMED_BY_ZERO_FRAME_LEAVES','all_unowned_bytes_and_metadata':'PRESERVATION_EXCLUDED_FROM_SOURCE','whole_module_source_ownership':False,'main_ee_source_index_compiler_and_progress_changed':False}
 report_path.write_text(json.dumps(report,indent=2)+'\n');current_report(manifest_path,report_path);return report

def current_report(manifest_path=None,report_path=None):
 manifest_path=checked_path(manifest_path or DEFAULT_MANIFEST,'config');report_path=checked_path(report_path or DEFAULT_OUTPUT/REPORT_NAME,'build/iop/module_02');manifest_bytes=manifest_path.read_bytes();manifest=json.loads(manifest_bytes);validate_manifest(manifest);raw,original=load_original();report=json.loads(report_path.read_text())
 if report.get('status')!='PASS_SEPARATE_TWO_MCMan_COMPLETE_LEAF_SOURCE_BUILD'or report.get('manifest')!=manifest_path.relative_to(ROOT).as_posix()or report.get('manifest_sha256')!=sha(manifest_bytes)or report.get('report_path')!=report_path.relative_to(ROOT).as_posix()or report.get('dependency_hashes')!=dependency_hashes():raise ValueError('Stale/unverified current module02 manifest/report/dependencies')
 if report.get('module')!=MODULE or report.get('module_sha256')!=MODULE_SHA or report.get('functions')!=SPECS or report.get('progress')!=progress(raw,original):raise ValueError('False current module02 source counts/functions/identity')
 if report.get('historical_iop_compiler_identity')!='UNCONFIRMED'or report.get('general_original_o32_abi')!='UNCONFIRMED_BY_ZERO_FRAME_LEAVES'or report.get('all_unowned_bytes_and_metadata')!='PRESERVATION_EXCLUDED_FROM_SOURCE'or report.get('whole_module_source_ownership')is not False or report.get('main_ee_source_index_compiler_and_progress_changed')is not False:raise ValueError('Unreviewed historical ABI, preservation or source ownership claim')
 ownership=[];groups=report.get('native_objects',[]);chosen=[]
 if len(groups)!=2:raise ValueError('Missing/duplicate current whole native function groups')
 for spec,group in zip(SPECS,groups):
  if group.get('claim')!=spec:raise ValueError('Incomplete/overlapping current module02 function ownership')
  rows=group.get('profiles',[])
  if [r.get('profile')for r in rows]!=list(PROFILES):raise ValueError('Both measured native revisions mandatory')
  for revision,row in zip(('114','136'),rows):
   assembly=report_path.parent/f'{Path(spec['source']).stem}_{revision}.raw.s';obj=report_path.parent/f'{Path(spec['source']).stem}_{revision}.o'
   if row.get('revision')!=revision or row.get('compiler_flags')!=PROFILE_FLAGS or row.get('assembler_flags')!=AS_FLAGS or row.get('native_input_hashes')!=native_inputs(revision)or row.get('assembly_unchanged')is not True:raise ValueError('Changed/unmeasured native compiler/assembler/profile')
   if row.get('assembly')!=assembly.relative_to(ROOT).as_posix()or row.get('object')!=obj.relative_to(ROOT).as_posix()or sha(assembly.read_bytes())!=row.get('assembly_sha256')or sha(obj.read_bytes())!=row.get('object_sha256'):raise ValueError('Stale current native source assembly/object/hash/provenance')
   _,proof=inspect_object(Elf32(obj.read_bytes()),spec,original)
   if row.get('whole_object_proof')!=proof:raise ValueError('Complete current native code/relocation/initialized-section proof differs')
  owner,_=allocated_read(original,spec['start'],16,True);ownership.append({'name':spec['name'],'module_offset':spec['start'],'size':16,'file_offset':owner['offset']+spec['start']-owner['addr'],'section':'.text'});chosen.append(rows[0])
 if report.get('original_source_ownership')!=ownership or report.get('input_state_validation')!=input_states(original,chosen):raise ValueError('False complete original bounds or R3000 result/input contract')
 partial=report_path.parent/'module_02.partial.irx'
 if report.get('partial_module')!=partial.relative_to(ROOT).as_posix()or report.get('partial_module_sha256')!=sha(partial.read_bytes())or partial.read_bytes()!=raw or report.get('full_file_bytes_equal')is not True:raise ValueError('Unverified partial-module preservation')
 return {**report,'freshness':'CURRENT_MODULE02_TWO_WHOLE_FUNCTIONS_REAL_HI_LO_ALL_NATIVE_SECTIONS_AND_INPUTS'}

def main():
 parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--manifest',type=Path,default=DEFAULT_MANIFEST);parser.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);args=parser.parse_args();run(args.manifest,args.output)
if __name__=='__main__':main()
