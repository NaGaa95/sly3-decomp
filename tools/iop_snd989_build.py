"""One mandatory whole source initializer from original module07 E490/76.

Only this exact zero-frame code is admitted. Historical compiler identity,
general framed O32 and custom989snd full IRX relocation/link contracts remain
unconfirmed. Original module/header/table/BSS preservation is never source.
"""
import argparse,copy,hashlib,importlib.util,json,os,struct,subprocess,sys
from pathlib import Path
ROOT=next(p for p in Path(__file__).resolve().parents if(p/'config/target.json').is_file())
sys.path.insert(0,str(ROOT/'tools'));sys.path.insert(0,str(ROOT/'build/iop_extra'))
from common import Elf32
from iop_build import allocated_read,native_inputs,AS_FLAGS
import original_contract as oc
EXPECTED={'schema': 'sly3-partial-iop-snd989-initializer-v1', 'module': 'disc/irx/module_07.irx', 'module_sha256': '9fa190ec393a60cbed1c04764c922e7b41d04ff0f41436cfae4cf198e1cdb6a5', 'functions': [{'name': 'snd_initialize_slots', 'source': 'iop/src/snd989/snd_initialize_slots.c', 'source_sha256': '19b0c6518b356f6074686b33b2edb14ff9c1a3456cfdcbc900ff828be784ff47', 'module_offset': 58512, 'object_offset': 0, 'size': 76, 'original_code_sha256': '99d5d01266d8c382875f0a0fdcce7268ac33c9e5b4a0fabd335b6da0962cea41', 'export_ordinal': None, 'signature': 'void snd_initialize_slots(SndInitialSlotView *slot, int count, u32 kind, u32 stride)', 'input_registers': ['a0: slot pointer', 'a1: signed32 count', 'a2: kind word', 'a3: stride size', 'ra: return address'], 'stack_frame_bytes': 0, 'consumed_incoming_stack_or_fpr': [], 'initialized_data_bytes': 0, 'bss_bytes': 0, 'real_source_relocations': 0, 'source_identifier_kind': 'RECONSTRUCTED_C_NAME_NO_ORIGINAL_ELF_FUNCTION_SYMBOL'}], 'data_objects': [], 'native_profiles': {'114': ['-Os', '-G0', '-mips1', '-mgp32', '-mfp32', '-mlong32', '-mcpu=r3000', '-malign-functions=2', '-fno-schedule-insns', '-fno-schedule-insns2', '-malign-loops=2'], '136': ['-Os', '-G0', '-mips1', '-mgp32', '-mfp32', '-mlong32', '-mcpu=r3000', '-malign-functions=2', '-fno-schedule-insns', '-fno-schedule-insns2', '-malign-loops=2']}, 'assembler_flags': ['-G0', '-mips1', '-mabi=32', '-O0'], 'source_name_original': False, 'source_functions': 1, 'source_code_bytes': 76, 'source_initialized_data_bytes': 0, 'source_BSS_bytes': 0, 'real_native_source_relocations': 0, 'original_pool_storage_source_count': 0, 'historical_compiler_identity': 'UNCONFIRMED', 'general_framed_O32_ABI': 'UNCONFIRMED', 'full_custom989snd_IRX_link_contract': 'UNCONFIRMED', 'pinned_dependencies': {'tools/common.py': 'ea66a7d1022952de2eb5c1d0bbe8551fb0ef6a472d6153b1dde05d0bec42c2ce', 'tools/iop_build.py': 'aed6391f61893537776e417c0e6efd06171f941c4200fd94079f3a537fd89ea7', 'build/iop_extra/original_contract.py': 'b04df5ed4dc80abb8740dead0b81e16bb7664c3d82ba14f9afdbccfe051b5457', 'build/iop_extra/native_trials.py': 'ca8a04c8af05a287c2f0095aae84d0a8a8b1da220d950c2f248299b940cd7ec4', 'build/iop_research/interfaces.json': '5cc886e6bf8d83420f2aa0842f78e1fc48fe48423cd3d8dac2fa93e886dca25b', 'build/iop_extra/module07_allocator/initializer/proposal/verify.py': '08bd9de241959874fb32eee1b84b71cdfc2643c5ac672b034096e4e03b7d70ad', 'build/iop_extra/module07_allocator/initializer/original_contract.json': 'ef1d2692cf15aef15a771c8c759c7c26926d88c924ce4c480921b2d59197f28c', 'build/iop_extra/module07_allocator/initializer/proposal/semantic_receipt.json': 'a0245858fbcf818bc726214eff3eccbf098904f8da256d88a6fb8598b4094302', 'build/iop_extra/module07_allocator/initializer/proposal/guard_receipt.json': 'ab05d055650d5a14405127474fb52a8834be3c0e6c2d9ba7edaedf0fd4f83f09', 'build/reports/iop_extra_module07_initializer_proposal.json': '8e934db176434857ec7b9d9a958edf03b088a8a2404e45523aa6aee73daa42e4', 'build/reports/iop_extra_module07_frozen_frontier.json': '5bb365142c63251e9ed297c969cf57019e916e72abbe862377f6f7b021cc0064', 'build/reports/game_early_tenth_numeric_metadata_classification.json': '154bb4fea66ddcd6c72c68080c2bf373b27f5f417bb60227905ecade80c94827', 'build/reports/vu_matches_early_foreach228_independent_review.json': '78caa6625b269ec266d04e962128e0ca19c4b422853dbe149acdd0018fab6fd2', 'iop/src/snd989/snd_initialize_slots.c': '19b0c6518b356f6074686b33b2edb14ff9c1a3456cfdcbc900ff828be784ff47', 'build/reports/hand_iop_module07_initializer_independent_review.json': 'cbcf1896af51be5aae543fb0b920605026587f17cd88c8e3f2bc094d304c6a17', 'build/leaf_matches/peer_reviews/module07_initializer/native_original_review.json': 'f468aec181c211211a5633c9f1ca47d4dfcf3ecf6355205251e702b24626b077', 'build/leaf_matches/peer_reviews/module07_initializer/pure_guard_receipt.json': 'ab05d055650d5a14405127474fb52a8834be3c0e6c2d9ba7edaedf0fd4f83f09'}, 'independent_peer_prerequisite': {'path': 'build/reports/hand_iop_module07_initializer_independent_review.json', 'sha256': 'cbcf1896af51be5aae543fb0b920605026587f17cd88c8e3f2bc094d304c6a17', 'status': 'PASS_INDEPENDENT_IOP_MODULE07_INITIALIZER76_BOTH_FRESH_NATIVE_FULL_ORIGINAL_AND_GUARDS'}}
PINNED=EXPECTED['pinned_dependencies'];CLAIM=EXPECTED['functions'][0]
MODULE=EXPECTED['module'];MODULE_SHA=EXPECTED['module_sha256'];SOURCE=ROOT/CLAIM['source']
CONTRACT=ROOT/'build/iop_extra/module07_allocator/initializer/original_contract.json'
PURE=ROOT/'build/iop_extra/module07_allocator/initializer/proposal/verify.py'
SEMANTIC=ROOT/'build/iop_extra/module07_allocator/initializer/proposal/semantic_receipt.json'
DEFAULT_MANIFEST=ROOT/'config/iop_snd989_partial.json';DEFAULT_OUTPUT=ROOT/'build/iop/snd989_initializer';REPORT_NAME='partial_iop_report.json'
DIR=DEFAULT_OUTPUT
EXPECTED_MANIFEST=EXPECTED
H=lambda b:hashlib.sha256(b).hexdigest()
canonical=lambda value:json.dumps(value,sort_keys=True,separators=(',',':'))

def require(condition,message):
 if not condition:raise ValueError(message)

def private_pure():
 name='_frozen_module07_initializer_proof'
 if name in sys.modules:return sys.modules[name]
 spec=importlib.util.spec_from_file_location(name,PURE);module=importlib.util.module_from_spec(spec);sys.modules[name]=module;spec.loader.exec_module(module);return module

def checked(path,scope):
 p=Path(path);p=p if p.is_absolute()else ROOT/p;p=p.resolve()
 require(p.is_relative_to((ROOT/scope).resolve()),'Path escapes maintained snd989 component scope');return p

def dependency_hashes():
 result={p:H((ROOT/p).read_bytes())for p in PINNED};result[Path(__file__).resolve().relative_to(ROOT).as_posix()]=H(Path(__file__).read_bytes());return result

def validate_manifest(manifest):
 require(canonical(manifest)==canonical(EXPECTED),'False/missing/foreign complete source/profile/section/ownership/dependency manifest')
 require(EXPECTED['independent_peer_prerequisite']!='PENDING_LEAF_REVIEW','Independent source/native/original peer prerequisite not frozen; prospective stage cannot run')
 for p,h in PINNED.items():require(H((ROOT/p).read_bytes())==h,'Pinned actual source/original/helper/reference/peer changed: '+p)
 text=SOURCE.read_text();require(not any(token in text for token in('__asm','asm(','volatile','register ')),'Unreviewed source/code adapter or scheduling fence')
 peer=EXPECTED['independent_peer_prerequisite'];receipt=json.loads((ROOT/peer['path']).read_bytes());require(receipt['status']==peer['status'] and receipt['remaining_actual_input_or_boundary_blockers']==[] and receipt['source_functions_proposed']==1 and receipt['source_code_bytes_proposed']==76 and receipt['source_initialized_data_bytes']==0 and receipt['source_BSS_bytes']==0 and receipt['source_relocations']==0 and receipt['original_cases']==1120 and receipt['fresh_native_cases']==2240,'Complete independent review absent')
 return True

def original(raw,contract):return private_pure().original(raw,contract)

def validate_original(raw):
 contract=json.loads(CONTRACT.read_bytes());e=original(raw,contract);require(not e.symbols(),'Original has no named ELF function symbol; reconstructed identifier qualification stale');return e

def inspect_native(raw,target):
 e=Elf32(raw);h=struct.unpack_from('<16sHHIIIIIHHHHHH',raw)
 require(h[0]==bytes.fromhex('7f454c46010101000000000000000000') and h[3]==1 and h[8]==52,'Native ELF ident/version/header extent differs')
 require((e.phoff,e.phentsize,e.phnum,e.shentsize,e.shnum,e.shstrndx)==(0,0,0,40,9,6),'Native program/section header ownership differs')
 result=private_pure().inspect_native(raw,target)
 require(all(not s['addr'] and not s['flags']for s in e.sections if s['name']not in('.text','.data','.bss')),'Unknown native metadata address/allocation')
 ranges=[(0,52),(e.shoff,e.shoff+9*40)]+[(s['offset'],s['offset']+s['size'])for s in e.sections if s['size']and s['type']!=8]
 for i,a in enumerate(ranges):
  require(0<=a[0]<a[1]<=len(raw),'Native complete range outside object')
  for b in ranges[i+1:]:require(max(a[0],b[0])>=min(a[1],b[1]),'Overlapping native complete file owners')
 ordered=sorted(ranges);require(max(z for a,z in ordered)==len(raw),'Unowned trailing native payload');require(not any(any(raw[a[1]:b[0]])for a,b in zip(ordered,ordered[1:])),'Unowned nonzero native alignment payload')
 return result

def inspect_object_bytes(raw,original_elf):
 owner,target=allocated_read(original_elf,0xe490,76,True);require(owner['name']=='.text'and H(target)==CLAIM['original_code_sha256'],'Unknown original allocated executable placement')
 result=inspect_native(raw,target);return {'status':'PASS_ENTIRE_NATIVE76_SOURCE_CODE_ZERO_DATA_BSS_RELOCATIONS_AND_FULL_METADATA','source_functions':1,'source_code_bytes':76,'source_initialized_data_bytes':0,'source_BSS_bytes':0,'native_source_relocations':[],'whole_native_code_sha256':H(target),'object_sha256':H(raw),'whole_function_and_all_allocated_sections':result,'all_native_file_ranges_and_metadata_verified':True}

def original_support():
 raw=(ROOT/MODULE).read_bytes();e=validate_original(raw);contract=json.loads(CONTRACT.read_bytes());rs=oc.records(e);require(len(rs)==6374,'All original real REL fields required')
 m=next(x for x in json.loads((ROOT/'build/iop_research/interfaces.json').read_bytes())['modules']if x['module']=='module_07.irx');tables=[]
 for t in m['tables']:
  sec,data=allocated_read(e,t['header_address'],t['byte_length'],True);require(H(data)==t['sha256'],'Complete original import/export table differs');tables.append({'kind':t['kind'],'library':t['library'],'address':t['header_address'],'size':t['byte_length'],'sha256':H(data)})
 text=e.section_data(e.section('.text'));excluded=[(t['header_address'],t['header_address']+t['byte_length'])for t in m['tables']];controls=[]
 for pc in range(0,len(text),4):
  if any(a<=pc<z for a,z in excluded):continue
  w=struct.unpack_from('<I',text,pc)[0];op=w>>26
  if op in(2,3):dest=(w&0x3ffffff)*4
  elif op in(4,5,6,7)or op==1 and(w>>16)&31 in(0,1,16,17):dest=pc+4+((w&0x7fff)-(w&0x8000))*4
  else:continue
  if 0xe490<=dest<0xe4dc:controls.append({'pc':pc,'target':dest,'op':op})
 require(controls==contract['all_incoming_control_edges'],'Actual entire original function boundaries/sole direct caller differ')
 require([(q['pc'],q['target'])for q in controls if not 0xe490<=q['pc']<0xe4dc]==[(0xe4f4,0xe490)],'Unreviewed exterior/interior entry')
 before=allocated_read(e,0xe488,8,True)[1];after=allocated_read(e,0xe4dc,8,True)[1];caller=allocated_read(e,0xe4dc,92,True)[1]
 require(list(struct.unpack('<2I',before))==[0x03e00008,0x27bd0028] and struct.unpack_from('<I',after)[0]==0x27bdffe8,'Original preceding terminal/following frame differs')
 require(struct.unpack_from('<I',caller,24)[0]==0x0c003924 and struct.unpack_from('<I',caller,28)[0]==0x24070124,'Actual caller entry/stride delay differs')
 for p,w in[(0xe4e4,0x3c040002),(0xe4e8,0x2484fc38),(0xe4ec,0x24050040),(0xe4f0,0x24060005)]:require(struct.unpack('<I',allocated_read(e,p,4,True)[1])[0]==w,'Real original pool/count/kind arguments differ')
 return {'whole_module_sha256':MODULE_SHA,'whole_module_file_bytes':len(raw),'whole_module_real_REL_count':6374,'original_owned_code_sha256':CLAIM['original_code_sha256'],'entire_owned_original_code_bytes':76,'original_function_relocations':[],'original_relocated_function_pointer_entries':[],'original_exports_to_source':[],'all_original_module_tables':tables,'all_actual_incoming_controls':controls,'complete_original_caller_sha256':H(caller),'complete_original_caller_bytes':92,'actual_original_call':{'site':0xe4f4,'head':0x1fc38,'count':64,'kind':5,'stride':292,'pool_end':0x24538},'actual_GPR_inputs':CLAIM['input_registers'],'incoming_stack_and_FPR_inputs':[],'frame_bytes':0,'source_identifier_kind':CLAIM['source_identifier_kind'],'original_metadata_BSS_bytes':m['bss_size'],'original_NOBITS_sections':[],'pool_storage_source_admitted':0,'full_custom989snd_linker_or_unowned_relocations_verified_as_source':False}

def native_compile(revision,output):
 compiler=ROOT/f'tools/third_party/ee-gcc2.95.3-{revision}/bin/ee-gcc.exe';library=compiler.parent.parent/'lib/gcc-lib/ee/2.95.3';assembler=ROOT/'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe';flags=EXPECTED['native_profiles'][revision];assembly=output/f'snd_initialize_slots_{revision}.raw.s';obj=output/f'snd_initialize_slots_{revision}.o';inputs=native_inputs(revision)
 for cmd in [[str(compiler),'-S','-x','c',*flags,'-B'+library.as_posix()+'/',SOURCE.as_posix(),'-o',assembly.as_posix()],[str(assembler),*AS_FLAGS,'-o',obj.as_posix(),assembly.as_posix()]]:
  q=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True,timeout=60);require(q.returncode==0,'Native compiler/assembler failed: '+json.dumps({'command':cmd,'stderr':q.stderr,'exit':q.returncode}))
 return {'revision':revision,'profile':'r3000-scalar-slot-initializer-'+revision,'compiler_flags':flags[:],'assembler_flags':AS_FLAGS[:],'native_input_hashes':inputs,'source':CLAIM['source'],'source_sha256':CLAIM['source_sha256'],'assembly':assembly.relative_to(ROOT).as_posix(),'assembly_sha256':H(assembly.read_bytes()),'assembly_unchanged':True,'object':obj.relative_to(ROOT).as_posix(),'object_sha256':H(obj.read_bytes())}

def semantic_receipt():return json.loads(SEMANTIC.read_bytes())

def semantic_states(original_elf,rows):
 pure=private_pure();target=allocated_read(original_elf,0xe490,76,True)[1];codes=[];inspections=[]
 for q in rows:
  raw=(ROOT/q['object']).read_bytes();e=Elf32(raw);codes.append(e.section_data(e.section('.text')));inspections.append(inspect_native(raw,target))
 cases=[]
 for count in(-2147483648,-1,0,1,2,4,64,256,257):
  for kind in(0,1,5,0x7f,0xff,0x100,0xffffffff,0x123600):
   for stride in(0,32,36,52,292,320):
    for seed in(17,911):cases.append((count,kind,stride,seed))
 for kind in range(256):cases.append((64,kind,292,101+kind))
 results=[]
 for case in cases:
  expected=pure.replay(target,*case)
  for code in codes:require(pure.replay(code,*case)==expected,'Fresh public-source full native semantic replay differs')
  results.append(expected)
 receipt=semantic_receipt();require(len(cases)==1120 and len(codes)==2 and H(json.dumps(cases,separators=(',',':')).encode())==receipt['semantic_case_labels_sha256'] and H(json.dumps(results,separators=(',',':')).encode())==receipt['semantic_results_sha256']and inspections==receipt['native_whole_object_inspections'],'Entire source/native original state cohort differs from frozen semantic receipt')
 return receipt

def progress(raw,original_elf):return {'verified_source_functions':1,'verified_source_code_bytes':76,'verified_source_initialized_data_bytes':0,'verified_source_BSS_bytes':0,'preserved_original_file_bytes_excluded_from_source':len(raw)-76,'original_file_size':len(raw),'original_text_bytes_including_tables_and_stubs':original_elf.section('.text')['size']}

def wanted_report(manifest_path,output,rows,semantic):
 raw=(ROOT/MODULE).read_bytes();original_elf=validate_original(raw);support=original_support();objects=[]
 require(isinstance(rows,list) and len(rows)==2 and all(isinstance(q,dict)for q in rows),'False/omitted native profile rows');require([q['revision']for q in rows]==['114','136'],'Both complete measured native profiles required')
 for row in rows:
  rev=row['revision'];require(set(row)=={'revision','profile','compiler_flags','assembler_flags','native_input_hashes','source','source_sha256','assembly','assembly_sha256','assembly_unchanged','object','object_sha256','whole_object_proof'},'False/missing native whole-source row fields')
  require(row['profile']=='r3000-scalar-slot-initializer-'+rev and row['compiler_flags']==EXPECTED['native_profiles'][rev] and row['assembler_flags']==AS_FLAGS and row['native_input_hashes']==native_inputs(rev) and row['source']==CLAIM['source']and row['source_sha256']==CLAIM['source_sha256'],'Stale/foreign native profile/source/input contract')
  require(row['assembly']==(output/f'snd_initialize_slots_{rev}.raw.s').relative_to(ROOT).as_posix()and row['object']==(output/f'snd_initialize_slots_{rev}.o').relative_to(ROOT).as_posix(),'Foreign native object/assembly output owner')
  require(row['assembly_unchanged']is True and H((ROOT/row['assembly']).read_bytes())==row['assembly_sha256']and H((ROOT/row['object']).read_bytes())==row['object_sha256'],'Stale whole native object/unchanged assembly')
  proof=inspect_object_bytes((ROOT/row['object']).read_bytes(),original_elf);require(canonical(proof)==canonical(row['whole_object_proof']),'False caller-supplied whole native code/data/BSS/relocation/metadata proof');objects.append(proof)
 require(canonical(semantic)==canonical(semantic_receipt()),'False omitted/edited source/native whole-state semantic receipt')
 partial=output/'module_07.partial.irx';require(partial.read_bytes()==raw,'Whole partial module differs; original unowned bytes remain preservation')
 return {'status':'PASS_PARTIAL_IOP_SND989_COMPLETE_INITIALIZER_CODE_ONLY','report_path':(output/REPORT_NAME).relative_to(ROOT).as_posix(),'manifest':manifest_path.relative_to(ROOT).as_posix(),'manifest_sha256':H(manifest_path.read_bytes()),'module':MODULE,'module_sha256':MODULE_SHA,'functions':[copy.deepcopy(CLAIM)],'data_objects':[],'native_profiles':rows,'native_objects':[{'claim':copy.deepcopy(CLAIM),'profiles':rows}],'original_complete_entry_arguments_caller_and_metadata':support,'source_native_semantics':semantic,'dependency_hashes':dependency_hashes(),'partial_module':partial.relative_to(ROOT).as_posix(),'partial_module_sha256':H(raw),'full_file_bytes_equal':True,'progress':progress(raw,original_elf),'whole_module_source_ownership':False,'original_unowned_code_data_tables_headers_BSS':'PRESERVATION_NOT_SOURCE','historical_iop_compiler_identity':'UNCONFIRMED','general_original_framed_O32_ABI':'UNCONFIRMED','full_custom989snd_IRX_link_contract':'UNCONFIRMED','source_identifier_kind':CLAIM['source_identifier_kind'],'all_allocated_source_sections_and_real_relocations_verified':True}

def current_report(manifest_path=None,report_path=None):
 manifest_path=checked(manifest_path or DEFAULT_MANIFEST,'config');report_path=checked(report_path or DEFAULT_OUTPUT/REPORT_NAME,'build/iop/snd989_initializer');require(manifest_path==DEFAULT_MANIFEST,'Foreign component manifest owner');manifest=json.loads(manifest_path.read_bytes());validate_manifest(manifest);report=json.loads(report_path.read_bytes());wanted=wanted_report(manifest_path,report_path.parent,report['native_profiles'],report['source_native_semantics']);require(canonical(report)==canonical(wanted),'Stale/false current whole source/native/dependency/count/metadata provenance');return {**report,'freshness':'CURRENT_COMPLETE_MODULE07_CODE76_ZERO_DATA_BSS_RELOCS_ALL_NATIVE_SECTIONS_AND_FROZEN_SEMANTICS'}

def verify_files():
 report=current_report();original_elf=validate_original((ROOT/MODULE).read_bytes());target=allocated_read(original_elf,0xe490,76,True)[1];rows=report['native_profiles'];return original_elf,target,rows,[inspect_native((ROOT/q['object']).read_bytes(),target)for q in rows]

def run(manifest_path=None,output=None):
 manifest_path=checked(manifest_path or DEFAULT_MANIFEST,'config');output=checked(output or DEFAULT_OUTPUT,'build/iop/snd989_initializer');require(manifest_path==DEFAULT_MANIFEST and output==DEFAULT_OUTPUT,'Foreign maintained source/native output owner');manifest=json.loads(manifest_path.read_bytes());validate_manifest(manifest);raw=(ROOT/MODULE).read_bytes();original_elf=validate_original(raw);original_support();output.mkdir(parents=True,exist_ok=True);report_path=output/REPORT_NAME;report_path.write_text(json.dumps({'status':'UNVERIFIED_CURRENT_SND989_SOURCE_BUILD','progress':{'verified_source_functions':0,'verified_source_code_bytes':0,'verified_source_initialized_data_bytes':0}},indent=2)+'\n');rows=[]
 for rev in('114','136'):
  row=native_compile(rev,output);row['whole_object_proof']=inspect_object_bytes((ROOT/row['object']).read_bytes(),original_elf);rows.append(row)
 semantic=semantic_states(original_elf,rows);target=allocated_read(original_elf,0xe490,76,True)[1];rebuilt=bytearray(raw);owner=original_elf.section('.text');offset=owner['offset']+0xe490-owner['addr'];rebuilt[offset:offset+76]=target;require(bytes(rebuilt)==raw,'Unexpected byte transformation');(output/'module_07.partial.irx').write_bytes(rebuilt);report=wanted_report(manifest_path,output,rows,semantic);report_path.write_text(json.dumps(report,indent=2)+'\n');current_report(manifest_path,report_path);print('PASS module07 one full source function/76 code/zero data BSS relocations; both measured profiles; original unowned bytes excluded.');return report
if __name__=='__main__':run()
