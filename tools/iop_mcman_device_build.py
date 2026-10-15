"""Mandatory exact two indexed mcman source functions, 128 complete code bytes.

The actual original BSS records are two ports by four slots with388-byte stride;
cardType is byte0x150 and cardFormat is signed word0x160. The current primary
MCDevInfo is384 bytes, so the original extra four-byte tail remains opaque.
Only this independently measured zero-frame cohort is admitted; historical IOP
compiler identity and general framed O32 ABI remain unconfirmed.
"""
import argparse,copy,hashlib,json,random,struct,subprocess,sys
from pathlib import Path
ROOT=next(p for p in Path(__file__).resolve().parents if(p/'config/target.json').is_file());FOLDER=ROOT/'tools'
sys.path.insert(0,str(ROOT/'tools'));sys.path.insert(0,str(FOLDER))
from common import Elf32
from iop_build import allocated_read,native_inputs,MEASURED_OBJECT_FLAGS
import common,iop_build
MODULE='disc/irx/module_02.irx';MODULE_SHA='1fe154231adbd587f9fb6ec1c7d4201c87c76ffcc91c8615474f24d26c05c7b0'
PROOF='build/reports/iop_extra_second_cohort_original_contract.json'
SOURCE_PROPOSAL='build/reports/iop_extra_second_cohort_private_proposal.json'
PROPOSAL=SOURCE_PROPOSAL
PARENT='build/reports/hand_iop_extra_second_getters_independent_review.json'
PARENT_SHA='f91fce6bed39b813e0e07d5466d39d674dedcafe0bccdbe28fe198f1d8abe47d'
BUNDLE='build/reports/iop_extra_second_cohort_frozen_bundle.json'
BUNDLE_SHA='40da13e7b218814a852f45c8f3e5c28fb87218a512fef6479bee856f3cdaac8f'
LICENSE='iop/src/mcman/LICENSE.PS2SDK'
LICENSE_SHA='1ecee940922a6886baccddd9133d17f1ce677d32c5a954fac8e48224f2766fe8'
DEFAULT_MANIFEST=ROOT/'config/iop_mcman_device_partial.json'
DEFAULT_OUTPUT=ROOT/'build/iop/mcman_device'
REPORT_NAME='partial_iop_report.json'
HEADER='iop/src/mcman/mc_device_view.h'
PROFILE_FLAGS=['-Os','-mno-split-addresses','-fno-schedule-insns','-fno-schedule-insns2','-G0','-mips1','-mgp32','-mfp32','-mlong32','-mcpu=r3000','-malign-functions=2']
AS_FLAGS=['-G0','-mips1','-mabi=32','-O0']
BASES=[0,0x1000,0x1c10,0x1c20,0x1c30,0x7000,0x10000,0x17ff0,0x27ff0,0xcfff0,0x80000000,0xa0000000,0xfff00000]
PINNED={'iop/src/mcman/mc_device_view.h': '2e6f4e2f68fd14c3f4b830d905dc2710e7aa7787f826c2a231307286a3c867a3', 'iop/src/mcman/mc_get_format_device.c': '5c658b50503108c22b02d8899cc840fe233b7b0937d2ebba9102552ce223c48c', 'iop/src/mcman/mc_get_type_device.c': 'efa3093b89403d75522dcb8fb9e1efd66081960a89a2df65de5b2ef73f176f4f', 'build/iop_extra/second_cohort/original_device_contract.py': 'ac9620593ff1849a4e2e61ebf7594823af3a08660094c4e906022f7ed5584233', 'build/reports/iop_extra_second_cohort_original_contract.json': 'e39ab9cd7f9214cefe194d6a961574194043426e65bb0bf7a693a1c413f91def', 'build/reports/iop_extra_second_cohort_primary_layout.json': '61d514660c8c9adb9bed7267cf0e9c176d397fa19ae377321db1701e093b3abb', 'tools/common.py': 'ea66a7d1022952de2eb5c1d0bbe8551fb0ef6a472d6153b1dde05d0bec42c2ce', 'tools/iop_build.py': 'aed6391f61893537776e417c0e6efd06171f941c4200fd94079f3a537fd89ea7', 'build/iop_research/primary_ps2sdk/iop/system/loadcore/src/loadcore.c': '2eb29f11cce431de18f8d5f64c64e4eda22507bfca26487a57b53b63750e0d78', 'build/iop_extra/primary_ps2sdk/iop/memorycard/mcman/src/exports.tab': '18ab44f1042c866b9342386114a5ecb74c1567f0e3e4db51d9fdc5f7e80b6fdd', 'build/iop_extra/primary_ps2sdk/iop/memorycard/mcman/include/mcman.h': '4a53cd27aa9ac2407c4f32752b288cc6467f6d5ba21f297c51f4b503a71a557e', 'build/iop_extra/primary_ps2sdk/iop/memorycard/mcman/src/main.c': 'd31c03143c40fcbb7fa55cbb5ed8711eaecf53deb2d0eecc654b125e20626ffb', 'build/iop_extra/primary_ps2sdk/iop/memorycard/mcman/src/mcman-internal.h': '5d388159006e39d0dc5d08757b59ef8169bb5f767ba646692f1e2abb8d4038ea', 'build/iop_extra/primary_ps2sdk/iop/input/padman/src/exports.tab': '16733ebd7cb8378165f000a01534b42c214e8e50c34ec651d5ced4214ec2cda9', 'build/iop_extra/primary_ps2sdk/iop/input/padman/include/xpadman.h': 'bf000873b3b60e19bf298fc38e2cf78c1f88fb97aab3c970ae10720aea09c4eb', 'build/iop_extra/primary_ps2sdk/iop/input/padman/src/freepad.h': 'c7b43e215441a2e4240b73e7e1647b1e87b773a1872ffaeb9f329fd5b37dd909', 'build/iop_extra/primary_ps2sdk/iop/input/padman/src/padMiscFuncs.c': 'cba090f32bed4fb8ff94786ef9ef0fb82cdc0a787bcf90731fdd43679208bcd6', 'build/iop_extra/primary_ps2sdk/iop/input/padman/src/rpcserver.c': '82424e8648d0d09985916cc5643e771269b9aa91c7d5515e7d361447c618d116', 'build/iop_extra/primary_ps2sdk/iop/system/threadman/include/thsemap.h': '91eb96d10fd8d40e1fda5928d7fc2e4da9535e17e0cff9bf26062328fc000636', 'build/iop_extra/second_cohort/src/primary_mc_layout_probe.c': '8dcdc9bb89cc298bde64e799fd637dc7fb4922ec5e85daca3caec32095d18259', 'build/iop_extra/second_cohort/layout_probe/layout_114.o': '803f3e6ea3e9288dbf23272640e6776724e1eb3e5419b3b45fa2520014533b71', 'build/iop_extra/second_cohort/layout_probe/layout_114.s': 'b654282455c71eca9f06ecfc6a88caa7c01fcd66ace0879104aa11c72c8ef831', 'build/iop_extra/second_cohort/layout_probe/layout_136.o': '803f3e6ea3e9288dbf23272640e6776724e1eb3e5419b3b45fa2520014533b71', 'build/iop_extra/second_cohort/layout_probe/layout_136.s': 'e21a2d88b2de7f365883f77dbe9d6ebbfdde8a3071924cf4bba36f00dd4130a7'}
PINNED['build/iop_extra/primary_ps2sdk/LICENSE.PS2SDK']='1ecee940922a6886baccddd9133d17f1ce677d32c5a954fac8e48224f2766fe8'
PINNED[PARENT]=PARENT_SHA
PINNED[BUNDLE]=BUNDLE_SHA
PINNED[SOURCE_PROPOSAL]='41bb98c8d2decbcebb3253fffb032f7e5972d713818b9d0cb40850bb95186768'
PINNED[LICENSE]=LICENSE_SHA
SPECS=[{'name':'McGetFormat','source':'iop/src/mcman/mc_get_format_device.c','start':0x278,'size':64,'ordinal':22,'external':'mcman_device_infos','binding':0x26280,'field_offset':352,'load_opcode':35,'signature':'int McGetFormat(int port, int slot)'},
       {'name':'McGetMcType','source':'iop/src/mcman/mc_get_type_device.c','start':0x2b8,'size':64,'ordinal':39,'external':'mcman_device_infos','binding':0x26280,'field_offset':336,'load_opcode':36,'signature':'int McGetMcType(int port, int slot)'}]

PINNED.update({'build/reports/hand_iop_extra_second_getters_independent_native_review.json': '3cb79f4f3460a6dedda9f824c8c5c16f0caf6ab3563de15642ee68e6ab9e8768', 'build/reports/hand_iop_extra_second_getters_independent_guard_review.json': 'be2ebf0d5537d902485c4416e82b670cb02bee2e9dba6c8c1163370686cb3715', 'build/leaf_matches/peer_reviews/iop_getter_pair/review_pair.py': 'cbd5d4d70f1c49507efb114910391505d8c111f2ddee8a6aae3423f527a50c0e', 'build/leaf_matches/peer_reviews/iop_getter_pair/device_guard_private_copy.py': '46cec818863144a83a4f2b65069ebf717596143d97e879fd985b13da99522d48'})
for _spec in SPECS:
 _spec.update(module=MODULE,module_sha256=MODULE_SHA,module_offset=_spec['start'],object_offset=0,source_sha256=PINNED[_spec['source']])
 _spec['original_code_sha256']=next(f['body']['original_code_sha256']for f in json.loads((ROOT/PROOF).read_text())['functions']if f['name']==_spec['name'])

def sha(b):return hashlib.sha256(b).hexdigest()
def words(b):return list(struct.unpack('<%dI'%(len(b)//4),b))
def expected_manifest():
 return {'schema':'sly3-iop-mcman-device-two-functions-v1','module':MODULE,'module_sha256':MODULE_SHA,'profiles':{'114':PROFILE_FLAGS[:],'136':PROFILE_FLAGS[:]},'assembler_flags':AS_FLAGS[:],'functions':[{**s,'source_sha256':PINNED[s['source']]}for s in SPECS],'source_header':HEADER,'source_header_sha256':PINNED[HEADER],'original_contract':PROOF,'original_contract_sha256':PINNED[PROOF],'license':LICENSE,'license_sha256':LICENSE_SHA,'parent_review':PARENT,'parent_review_sha256':PARENT_SHA,'private_source_proposal':SOURCE_PROPOSAL,'private_source_proposal_sha256':PINNED[SOURCE_PROPOSAL],'frozen_bundle':BUNDLE,'frozen_bundle_sha256':BUNDLE_SHA,'pinned_dependencies':PINNED.copy(),'layout':{'record_head':0x26280,'record_stride':388,'outer_ports':2,'slots_per_port':4,'record_count':8,'array_bytes':3104,'primary_bytes':384,'opaque_extra_tail_bytes':4},'public_counts_enabled':True,'historical_compiler_identity':'UNCONFIRMED','general_framed_ABI':'UNCONFIRMED'}
EXPECTED=expected_manifest()

def validate_manifest(m):
 if m!=EXPECTED:raise ValueError('Unreviewed API/original/boundary/source/header/profile/layout/ownership/identity claim')
 for p,h in PINNED.items():
  if sha((ROOT/p).read_bytes())!=h:raise ValueError('Pinned private proof/source/primary/compiler helper changed: '+p)
 for p in[HEADER]+[s['source']for s in SPECS]:
  source=(ROOT/p).read_text()
  if '__asm' in source or 'asm('in source or 'volatile'in source:raise ValueError('Unreviewed source adapter or scheduling fence')
 proof=json.loads((ROOT/PROOF).read_text())
 if proof['status']!='PASS_PRIVATE_TWO_INDEXED_GETTERS_ORIGINAL_ENTRIES_ARGUMENTS_AND_FULL_CALLERS'or proof['blockers']or len(proof['actual_calls'])!=6:raise ValueError('Complete actual entry, arguments, or callers proof absent')
 if sha((ROOT/proof['complete_external_caller']['module']).read_bytes())!=proof['complete_external_caller']['module_sha256']:raise ValueError('Actual consumer original changed')
 parent=json.loads((ROOT/PARENT).read_text())
 if parent.get('remaining_blockers') or parent.get('independently_reviewed_new_functions')!=2 or parent.get('reviewed_complete_code_bytes')!=128 or parent.get('reviewed_complete_initialized_data_bytes')!=0 or parent.get('reviewed_source_BSS_bytes')!=0 or parent.get('rejection_guards')!=4066 or parent.get('original_valid_input_states')!=79872 or parent.get('fresh_native_valid_input_comparisons')!=159744:raise ValueError('Independent complete code/entry/arguments/native/guard review absent')
 return True

def validate_original(data):
 if sha(data)!=MODULE_SHA:raise ValueError('Whole original module freshness differs')
 e=Elf32(data)
 if(e.type,e.flags,e.entry)!=(0xff80,1,0x178):raise ValueError('Unreviewed original native module header')
 rs=original_records(e)
 if len(rs)!=2699:raise ValueError('Original complete REL ownership differs')
 proof=json.loads((ROOT/PROOF).read_text())
 for spec,p in zip(SPECS,proof['functions']):
  sec,b=allocated_read(e,spec['start'],64,True)
  if sec['name']!='.text'or sec['addr']or sha(b)!=p['body']['original_code_sha256']:raise ValueError('Original full64-byte function differs')
  pair=[r for r in rs if spec['start']<=r['module_address']<spec['start']+64]
  if pair!=p['original_real_HI_LO']:raise ValueError('Original actual HI/LO ownership differs')
  field=20+4*spec['ordinal'];er=[r for r in rs if r['module_address']==field]
  if er!=[p['export']['relocation']]:raise ValueError('Actual original export REL differs')
 return e

def replay_original(payload,spec,base):
 w=words(payload)
 if len(w)!=16:raise ValueError('Whole original64-byte function required')
 high,low=w[11],w[13]
 effective=(base+((high&0xffff)<<16)+((low&0x7fff)-(low&0x8000)))&0xffffffff
 if effective!=(base+spec['binding']+spec['field_offset'])&0xffffffff:raise ValueError('Actual original field addend/binding differs')
 # Loadcore ApplyElfRelSection uses signed LO for HI carry and base+originalLO for LO.
 w[11]=(high&0xffff0000)|((((effective>>15)+1)>>1)&0xffff)
 w[13]=(low&0xffff0000)|((base+low)&0xffff)
 return struct.pack('<16I',*w)

def link_native(payload,spec,base):
 w=words(payload)
 if len(w)!=16 or w[11]!=0x3c020000 or w[13]!=((spec['load_opcode']<<26)|0x00420000|spec['field_offset']):raise ValueError('Unreviewed native actual HI/LO opcode/register/addend')
 address=(base+spec['binding']+spec['field_offset'])&0xffffffff
 w[11]=(w[11]&0xffff0000)|(((address+0x8000)>>16)&0xffff)
 w[13]=(w[13]&0xffff0000)|(address&0xffff)
 return struct.pack('<16I',*w)

def native_relocations(e):
 symbols={(s['table'],s['index']):s for s in e.symbols()};out=[]
 for sec in e.sections:
  if sec['type']!=9:continue
  if sec['entsize']!=8 or sec['size']%8:raise ValueError('Native REL size differs')
  if not 0<=sec['info']<len(e.sections):raise ValueError('Invalid REL target owner')
  for off,info in struct.iter_unpack('<II',e.section_data(sec)):
   sym=symbols.get((sec['link'],info>>8))
   if sym is None:raise ValueError('Native unresolved symbol table/index')
   out.append({'owner':e.sections[sec['info']]['name'],'offset':off,'type':info&255,'symbol':sym['name'],'symbol_index':info>>8})
 return out

def inspect_object_bytes(data,spec,original):
 if spec not in SPECS:raise ValueError('Unknown whole indexed-function claim')
 e=Elf32(data);header=struct.unpack_from('<16sHHIIIIIHHHHHH',data)
 if(e.type,e.flags,e.entry,e.phnum,e.phoff,e.phentsize,e.shentsize,e.shnum,e.shstrndx)!=(1,MEASURED_OBJECT_FLAGS,0,0,0,0,40,10,7)or header[3]!=1 or header[8]!=52 or header[0]!=bytes.fromhex('7f454c46010101000000000000000000'):raise ValueError('Unmeasured native ELF header/type/flags')
 names=['','.text','.rel.text','.data','.bss','.reginfo','.mdebug','.shstrtab','.symtab','.strtab']
 types=[0,1,9,1,8,0x70000006,0x70000005,3,2,3]
 if[e['name']for e in e.sections]!=names or[e['type']for e in e.sections]!=types:raise ValueError('Unknown/duplicate/missing native metadata or allocated section')
 if any(s['addr']or s['flags']for s in e.sections if s['name']not in('.text','.data','.bss')):raise ValueError('Unowned allocation or native section address')
 if e.shoff<52 or e.shoff+e.shnum*40>len(data):raise ValueError('Native section table extent differs')
 ranges=[(0,52,'ELF header'),(e.shoff,e.shoff+e.shnum*40,'section table')]+[(s['offset'],s['offset']+s['size'],s['name'])for s in e.sections if s['size']and s['type']!=8]
 for i,a in enumerate(ranges):
  if a[0]<0 or a[1]>len(data):raise ValueError('Native file range outside object')
  for b in ranges[i+1:]:
   if max(a[0],b[0])<min(a[1],b[1]):raise ValueError('Overlapping native file ownership')
 ordered=sorted(ranges)
 if max(r[1]for r in ordered)!=len(data):raise ValueError('Unowned trailing native file payload')
 for a,b in zip(ordered,ordered[1:]):
  if any(data[a[1]:b[0]]):raise ValueError('Unowned nonzero native alignment payload')
 allocated=[s for s in e.sections if s['flags']&2]
 if len(allocated)!=3 or[s['name']for s in allocated]!=['.text','.data','.bss']:raise ValueError('Every allocated native section must be owned')
 text=e.section('.text')
 if tuple(text[k]for k in('addr','size','type','flags','alignment','entsize','link','info'))!=(0,64,1,6,4,0,0,0):raise ValueError('Incomplete whole original code-section ownership')
 for name,kind in[('.data',1),('.bss',8)]:
  s=e.section(name)
  if tuple(s[k]for k in('addr','size','type','flags','alignment','entsize','link','info'))!=(0,0,kind,3,1,0,0,0):raise ValueError('Unowned initialized data/BSS or empty-section contract')
 reg=e.section('.reginfo')
 if tuple(reg[k]for k in('size','alignment','entsize','link','info'))!=(24,4,1,0,0)or e.section_data(reg)!=bytes.fromhex('3c0000900000000000000000000000000000000000000000'):raise ValueError('Native no-frame register/FPR/GP metadata differs')
 symtab=e.section('.symtab')
 if tuple(symtab[k]for k in('size','entsize','alignment','link','info'))!=(160,16,4,9,6):raise ValueError('All native symbols must be reviewed')
 symbols=e.symbols();fn=[s for s in symbols if s['type']==2];undefined=[s for s in symbols if s['binding']and s['shndx']==0]
 if len(fn)!=1 or tuple(fn[0][k]for k in('name','value','size','shndx','binding','visibility'))!=(spec['name'],0,64,1,1,0):raise ValueError('Every emitted function must be complete and owned')
 if len(undefined)!=1 or tuple(undefined[0][k]for k in('name','value','size','type','binding','visibility'))!=(spec['external'],0,0,0,1,0):raise ValueError('Actual record-head external differs')
 if len(symbols)!=10:raise ValueError('Extra/missing native symbol')
 for s in symbols:
  if s['index']==0 and not s['name']and not s['shndx']and all(s[k]==0 for k in('value','size','type','binding','visibility')):continue
  if s['type']==3:
   if s['name']or s['value']or s['size']or s['binding']or s['visibility']or s['shndx']not in(1,3,4,5,6):raise ValueError('Unreviewed native section symbol')
   continue
  if s['name']in('gcc2_compiled.','__gnu_compiled_c'):
   if tuple(s[k]for k in('value','size','type','binding','visibility','shndx'))!=(0,0,0,0,0,1):raise ValueError('Malformed/unowned compiler marker')
   continue
  if s not in fn and s not in undefined:raise ValueError('Unowned defined/external/alias symbol')
 if sorted(s['shndx']for s in symbols if s['type']==3)!=[1,3,4,5,6]:raise ValueError('Duplicate or missing native section symbol')
 relsec=e.section('.rel.text')
 if tuple(relsec[k]for k in('type','flags','addr','size','info','alignment','entsize','link'))!=(9,0,0,16,1,4,8,8):raise ValueError('Complete real REL format/owner/extent differs')
 rel=native_relocations(e)
 if[(r['owner'],r['offset'],r['type'],r['symbol'],r['symbol_index'])for r in rel]!=[('.text',44,5,spec['external'],9),('.text',52,6,spec['external'],9)]:raise ValueError('Every real native field must resolve actual record head')
 payload=e.section_data(text);_,target=allocated_read(original,spec['start'],64,True);cases=[]
 for base in BASES:
  native=link_native(payload,spec,base);ori=replay_original(target,spec,base)
  if native!=ori:raise ValueError('Whole native64-byte code differs after actual signed LO loader carry')
  cases.append({'load_base':hex(base),'actual_record_head':hex((base+spec['binding'])&0xffffffff),'native_field_addend':spec['field_offset'],'resolved_first_field':hex((base+spec['binding']+spec['field_offset'])&0xffffffff),'entire_original_code_sha256':sha(ori),'entire_native_code_sha256':sha(native),'status':'EXACT_COMPLETE_FUNCTION'})
 return {'status':'PASS_COMPLETE64_BYTE_NATIVE_FUNCTION_ALL_REAL_RELOCATIONS_AND_SECTIONS','name':spec['name'],'code_bytes':64,'initialized_data_bytes':0,'BSS_bytes':0,'all_allocated_sections':[{'section':s['name'],'size':s['size'],'type':s['type'],'flags':s['flags'],'alignment':s['alignment'],'sha256':sha(e.section_data(s))}for s in allocated],'all_source_relocations':rel,'loader_carry_cases':cases,'object_sha256':sha(data)}

def execute(body,regs,memory):
 regs=regs[:];before=regs[:];pending=None;return_pc=None;reads=[]
 for index,w in enumerate(words(body)):
  op=w>>26;rs=(w>>21)&31;rt=(w>>16)&31;rd=(w>>11)&31;oldpending=pending;pending=None
  if op==0 and w&63==0:regs[rd]=(regs[rt]<<((w>>6)&31))&0xffffffff
  elif op==0 and w&63==33:regs[rd]=(regs[rs]+regs[rt])&0xffffffff
  elif op==15:regs[rt]=(w&0xffff)<<16
  elif op in(35,36):
   address=(regs[rs]+((w&0x7fff)-(w&0x8000)))&0xffffffff;width=4 if op==35 else 1
   if width==4 and address%4:raise ValueError('Unaligned original indexed word access')
   value=sum(memory[(address+i)&0xffffffff]<<(8*i)for i in range(width));pending=(rt,value);reads.append({'address':address,'width':width})
  elif w==0x03e00008:
   if index!=14:raise ValueError('Early/missing complete return')
   return_pc=regs[31]
  else:raise ValueError('Unreviewed indexed getter instruction')
  if oldpending:regs[oldpending[0]]=oldpending[1]
  regs[0]=0
 if len(body)!=64 or pending or return_pc!=before[31]or any(regs[i]!=before[i]for i in range(32)if i not in(2,3))or len(reads)!=1:raise ValueError('Indexed input/load-delay/clobber/return contract differs')
 return {'value':regs[2],'address':reads[0]['address'],'width':reads[0]['width'],'v1':regs[3],'return_pc':return_pc}

def input_states(original,objects):
 rng=random.Random(0x334D4344);patterns=[0,1,0x7fff,0x8000,0x7fffffff,0x80000000,0xffffffff,0x55aa55aa,0xaa55aa55]+[rng.getrandbits(32)for _ in range(503)]
 cases=0;comparisons=0
 for spec,group in zip(SPECS,objects):
  payloads=[]
  for obj in group:
   e=Elf32((ROOT/obj['object']).read_bytes());payloads.append(e.section_data(e.section('.text')))
  _,ori=allocated_read(original,spec['start'],64,True)
  values=patterns if spec['load_opcode']==35 else list(range(256))
  for base in BASES:
   original_body=replay_original(ori,spec,base);native_bodies=[link_native(p,spec,base)for p in payloads]
   for port in range(2):
    for slot in range(4):
     displacement=port*1552+slot*388;address=(base+spec['binding']+displacement+spec['field_offset'])&0xffffffff
     for value in values:
      regs=[rng.getrandbits(32)for _ in range(32)];regs[0]=0;regs[4]=port;regs[5]=slot;regs[31]=rng.getrandbits(30)<<2
      memory={(address+i)&0xffffffff:(value>>(8*i))&255 for i in range(4)}
      expected={'value':value,'address':address,'width':4 if spec['load_opcode']==35 else 1,'v1':displacement,'return_pc':regs[31]}
      if execute(original_body,regs,memory)!=expected:raise ValueError('Actual original raw return or record address differs')
      for b in native_bodies:
       if execute(b,regs,memory)!=expected:raise ValueError('Whole native valid-record argument/load/output contract differs')
       comparisons+=1
      cases+=1
 return {'status':'PASS_ORIGINAL_R3000_TWO_SIGNED_WORD_ARGUMENTS_VALID_RECORD_DOMAIN','original_states':cases,'fresh_native_profile_comparisons':comparisons,'load_bases':len(BASES),'ports':2,'slots_per_port':4,'format_patterns':512,'all_card_type_values':256,'unconsumed_argument_and_nonresult_gprs_preserved':True,'stack_FPRs_HI_LO_untouched':True,'only_v0_v1_clobbered':True,'one_actual_field_load':True,'R3000_load_delay_and_JR_delay_executed':True,'out_of_domain_C_semantics_claimed':False,'getter_bounds_checks_present':False}

def native_compile(spec,revision,output):
 source=ROOT/spec['source'];compiler=ROOT/f'tools/third_party/ee-gcc2.95.3-{revision}/bin/ee-gcc.exe';lib=compiler.parent.parent/'lib/gcc-lib/ee/2.95.3';assembler=ROOT/'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe'
 output.mkdir(parents=True,exist_ok=True);assembly=output/f'{source.stem}_{revision}.raw.s';obj=output/f'{source.stem}_{revision}.o';inputs=native_inputs(revision)
 commands=[[str(compiler),'-S','-x','c',*PROFILE_FLAGS,'-B'+lib.as_posix()+'/',source.as_posix(),'-o',assembly.as_posix()],[str(assembler),*AS_FLAGS,'-o',obj.as_posix(),assembly.as_posix()]]
 for cmd in commands:
  result=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True,timeout=60)
  if result.returncode:raise RuntimeError(json.dumps({'command':cmd,'exit':result.returncode,'stdout':result.stdout,'stderr':result.stderr}))
 return {'revision':revision,'profile':'module02-two-indexed-record-getters-nosplit-noschedule-'+revision,'compiler_flags':PROFILE_FLAGS[:],'assembler_flags':AS_FLAGS[:],'native_input_hashes':inputs,'assembly':assembly.relative_to(ROOT).as_posix(),'assembly_sha256':sha(assembly.read_bytes()),'assembly_unchanged':True,'object':obj.relative_to(ROOT).as_posix(),'object_sha256':sha(obj.read_bytes())}


def checked_path(path,scope):
 p=Path(path);p=p if p.is_absolute()else ROOT/p;p=p.resolve()
 if not p.is_relative_to((ROOT/scope).resolve()):raise ValueError('Path escapes maintained mcman device scope')
 return p


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


def dependency_hashes():
 validate_manifest(EXPECTED)
 paths={p:ROOT/p for p in PINNED}
 paths['tools/iop_mcman_device_build.py']=ROOT/'tools/iop_mcman_device_build.py'
 proof=json.loads((ROOT/PROOF).read_text());p=proof['complete_external_caller']['module'];paths[p]=ROOT/p
 return {p:sha(path.read_bytes())for p,path in paths.items()}

def inspect_object(elf,claim,original):
 proof=inspect_object_bytes(elf.data,claim,original)
 return link_native(elf.section_data(elf.section('.text')),claim,0),proof

def load_original():
 raw=(ROOT/MODULE).read_bytes();return raw,validate_original(raw)

def progress(raw,original):
 return {'verified_source_functions':2,'verified_source_code_bytes':128,'verified_source_initialized_data_bytes':0,'preserved_original_file_bytes_excluded_from_source':len(raw)-128,'original_file_size':len(raw),'original_text_bytes_including_tables_and_stubs':original.section('.text')['size']}


def run(manifest_path=None,output=None):
 manifest_path=checked_path(manifest_path or DEFAULT_MANIFEST,'config');output=checked_path(output or DEFAULT_OUTPUT,'build/iop/mcman_device');output.mkdir(parents=True,exist_ok=True);report_path=output/REPORT_NAME
 report_path.write_text(json.dumps({'status':'UNVERIFIED_CURRENT_MCMan_DEVICE_BUILD','progress':{'verified_source_functions':0,'verified_source_code_bytes':0,'verified_source_initialized_data_bytes':0},'previous_success_must_not_count':True},indent=2)+'\n')
 manifest_bytes=manifest_path.read_bytes();manifest=json.loads(manifest_bytes);validate_manifest(manifest);deps=dependency_hashes();raw,original=load_original();groups=[];chosen=[];rebuilt=bytearray(raw);ownership=[]
 for spec in SPECS:
  rows=[];code=None
  for revision in('114','136'):
   row=native_compile(spec,revision,output);payload,audit=inspect_object(Elf32((ROOT/row['object']).read_bytes()),spec,original)
   if code is not None and payload!=code:raise ValueError('Two whole native revisions disagree')
   if native_inputs(revision)!=row['native_input_hashes']or sha((ROOT/spec['source']).read_bytes())!=spec['source_sha256']or dependency_hashes()!=deps:raise ValueError('Source/native/compiler/proof dependency changed during compilation')
   code=payload;rows.append({**row,'whole_object_proof':audit})
  groups.append({'claim':spec,'profiles':rows});chosen.append(rows[0]);owner,target=allocated_read(original,spec['start'],64,True);a=owner['offset']+spec['start']-owner['addr'];rebuilt[a:a+64]=code;ownership.append({'name':spec['name'],'module_offset':spec['start'],'size':64,'file_offset':a,'section':'.text'})
 if bytes(rebuilt)!=raw:raise ValueError('Partial source module changes an original byte')
 states=input_states(original,[[g['profiles'][0],g['profiles'][1]]for g in groups]);partial=output/'module_02.partial.irx';partial.write_bytes(rebuilt)
 report={'status':'PASS_SEPARATE_TWO_MCMan_DEVICE_FUNCTION_SOURCE_BUILD','manifest':manifest_path.relative_to(ROOT).as_posix(),'manifest_sha256':sha(manifest_bytes),'report_path':report_path.relative_to(ROOT).as_posix(),'dependency_hashes':deps,'module':MODULE,'module_sha256':MODULE_SHA,'functions':copy.deepcopy(SPECS),'native_objects':groups,'progress':progress(raw,original),'original_source_ownership':ownership,'input_state_validation':states,'partial_module':partial.relative_to(ROOT).as_posix(),'partial_module_sha256':sha(partial.read_bytes()),'full_file_bytes_equal':True,'historical_iop_compiler_identity':'UNCONFIRMED','general_original_o32_abi':'UNCONFIRMED_BY_TWO_ZERO_FRAME_INDEXED_FUNCTIONS','all_unowned_bytes_and_metadata':'PRESERVATION_EXCLUDED_FROM_SOURCE','whole_module_source_ownership':False,'main_ee_source_index_compiler_and_progress_changed':False}
 report['source_header']=HEADER;report['source_header_sha256']=PINNED[HEADER];report_path.write_text(json.dumps(report,indent=2)+'\n');current_report(manifest_path,report_path);return report


def current_report(manifest_path=None,report_path=None):
 manifest_path=checked_path(manifest_path or DEFAULT_MANIFEST,'config');report_path=checked_path(report_path or DEFAULT_OUTPUT/REPORT_NAME,'build/iop/mcman_device');manifest_bytes=manifest_path.read_bytes();manifest=json.loads(manifest_bytes);validate_manifest(manifest);raw,original=load_original();report=json.loads(report_path.read_text())
 if report.get('status')!='PASS_SEPARATE_TWO_MCMan_DEVICE_FUNCTION_SOURCE_BUILD'or report.get('manifest')!=manifest_path.relative_to(ROOT).as_posix()or report.get('manifest_sha256')!=sha(manifest_bytes)or report.get('report_path')!=report_path.relative_to(ROOT).as_posix()or report.get('dependency_hashes')!=dependency_hashes():raise ValueError('Stale/unverified current module02 manifest/report/dependencies')
 if report.get('module')!=MODULE or report.get('module_sha256')!=MODULE_SHA or report.get('functions')!=SPECS or report.get('progress')!=progress(raw,original):raise ValueError('False current module02 source counts/functions/identity')
 if report.get('historical_iop_compiler_identity')!='UNCONFIRMED'or report.get('general_original_o32_abi')!='UNCONFIRMED_BY_TWO_ZERO_FRAME_INDEXED_FUNCTIONS'or report.get('all_unowned_bytes_and_metadata')!='PRESERVATION_EXCLUDED_FROM_SOURCE'or report.get('whole_module_source_ownership')is not False or report.get('main_ee_source_index_compiler_and_progress_changed')is not False:raise ValueError('Unreviewed historical ABI, preservation or source ownership claim')
 if report.get('source_header')!=HEADER or report.get('source_header_sha256')!=PINNED[HEADER]:raise ValueError('Current source header provenance differs')
 ownership=[];groups=report.get('native_objects',[]);chosen=[]
 if len(groups)!=2:raise ValueError('Missing/duplicate current whole native function groups')
 for spec,group in zip(SPECS,groups):
  if group.get('claim')!=spec:raise ValueError('Incomplete/overlapping current module02 function ownership')
  rows=group.get('profiles',[])
  if [r.get('profile')for r in rows]!=['module02-two-indexed-record-getters-nosplit-noschedule-'+r for r in('114','136')]:raise ValueError('Both measured native revisions mandatory')
  for revision,row in zip(('114','136'),rows):
   assembly=report_path.parent/f'{Path(spec['source']).stem}_{revision}.raw.s';obj=report_path.parent/f'{Path(spec['source']).stem}_{revision}.o'
   if row.get('revision')!=revision or row.get('compiler_flags')!=PROFILE_FLAGS or row.get('assembler_flags')!=AS_FLAGS or row.get('native_input_hashes')!=native_inputs(revision)or row.get('assembly_unchanged')is not True:raise ValueError('Changed/unmeasured native compiler/assembler/profile')
   if row.get('assembly')!=assembly.relative_to(ROOT).as_posix()or row.get('object')!=obj.relative_to(ROOT).as_posix()or sha(assembly.read_bytes())!=row.get('assembly_sha256')or sha(obj.read_bytes())!=row.get('object_sha256'):raise ValueError('Stale current native source assembly/object/hash/provenance')
   _,proof=inspect_object(Elf32(obj.read_bytes()),spec,original)
   if row.get('whole_object_proof')!=proof:raise ValueError('Complete current native code/relocation/initialized-section proof differs')
  owner,_=allocated_read(original,spec['start'],64,True);ownership.append({'name':spec['name'],'module_offset':spec['start'],'size':64,'file_offset':owner['offset']+spec['start']-owner['addr'],'section':'.text'});chosen.append(rows)
 if report.get('original_source_ownership')!=ownership or report.get('input_state_validation')!=input_states(original,chosen):raise ValueError('False complete original bounds or R3000 result/input contract')
 partial=report_path.parent/'module_02.partial.irx'
 if report.get('partial_module')!=partial.relative_to(ROOT).as_posix()or report.get('partial_module_sha256')!=sha(partial.read_bytes())or partial.read_bytes()!=raw or report.get('full_file_bytes_equal')is not True:raise ValueError('Unverified partial-module preservation')
 return {**report,'freshness':'CURRENT_MODULE02_TWO_INDEXED_FUNCTIONS128_REAL_ADDEND_HI_LO_ALL_NATIVE_SECTIONS_AND79872_INPUT_STATES'}


def main():
 parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--manifest',type=Path,default=DEFAULT_MANIFEST);parser.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);args=parser.parse_args();run(args.manifest,args.output)

if __name__=='__main__':main()
