"""Whole native VU0 math and VU1 bootstrap proofs; existing renderer stays untouched.
All pure review APIs reread source, original CPU protocol and native receipts.
"""
import argparse,hashlib,json,struct,subprocess,sys
from pathlib import Path
import rabbitizer
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve();ROOT=next(p for p in HERE.parents if(p/'disc/SCUS_974.64').is_file())
sys.path.insert(0,str(ROOT/'tools'))
from common import Elf32
import vu_build as renderer
rabbitizer.config.regNames_gprAbiNames=rabbitizer.Abi.O32
ORIGINAL_SHA=renderer.ORIGINAL_SHA
DEFAULT_BUNDLE=HERE.parents[1]
DEFAULT_OUTPUT=ROOT/'build/vu/extra'
REPORT_NAME='vu_extra_report.json'
EXPECTED_MATH=[('vu0_idle_entry', 0, 16), ('vu0_transform_and_expand_bounds', 16, 80), ('vu0_multiply_four_vectors', 96, 144), ('vu0_transform_affine_vf5', 240, 48), ('vu0_transform_affine_vf6', 288, 48), ('vu0_transform_and_normalize_plane', 336, 112), ('vu0_clipped_radial_ratio', 448, 224)]
PROGRAM_SHA='7ad0c6fd345f5875ab3b9a659b2f1e2a4c2301a0daebafdfa44220490854aa68'
CHAIN_SHA='22cebde7e1c67ca1785f3d47180a09eb3bbec0623c7b88b156f27a53a544456b'
EXPECTED_COMPONENTS=[{'family': '11753275', 'processor': 'VU0', 'source': 'src/vu/math/vu0_math_final.vsm', 'chain_source': 'src/vu/math/vu0_startup_chain_final.vif', 'source_sha256': '29513609e12388e94b4951061a247b134b66e3c215c376ee827a4e31de1e0c2d', 'chain_source_sha256': 'dd8a2e067f39e89dff2eae57ff5ab9cb5ba7a1b8f4ed0e03413112d12a422a76', 'code_bytes': 672, 'chain_bytes': 720, 'DMA_protocol_bytes': 16, 'VIF_protocol_bytes': 32, 'EE_chain_begin': 2884176, 'EE_payload_begin': 2884192, 'program_sha256': '7ad0c6fd345f5875ab3b9a659b2f1e2a4c2301a0daebafdfa44220490854aa68', 'chain_sha256': '22cebde7e1c67ca1785f3d47180a09eb3bbec0623c7b88b156f27a53a544456b', 'evidence': 'docs/evidence/vu_math_input_review.json', 'evidence_sha256': 'df52ad1ddfd6febf1ac48f561151bfbffc498ffd64b7f745c73b9bc0a6eac9a1'}, {'family': '376118779', 'processor': 'VU1', 'source': 'src/vu/bootstrap/vu1_idle.vsm', 'chain_source': 'src/vu/bootstrap/vu1_startup_chain.vif', 'source_sha256': '2fd1fc9fc9abbda89e707281d24595dbcd378e395249f269c896a1af8847a61b', 'chain_source_sha256': '8c378db3a03ddb978eed1b145b13606bb2d4c8568ac8f5b3dcd3a98d7b0b302d', 'code_bytes': 16, 'chain_bytes': 64, 'DMA_protocol_bytes': 16, 'VIF_protocol_bytes': 32, 'EE_chain_begin': 2901440, 'EE_payload_begin': 2901456, 'program_sha256': '5eb74410b7d656eb5a22ee9e60eef38c6896a22506b84d1277503a6641acc0df', 'chain_sha256': '4e50d8fff11f14510fc77ab8b5a2109cbb4d8ee97263101c38cb2d2cbe8ed3de', 'evidence': 'docs/evidence/vu_bootstrap_input_review.json', 'evidence_sha256': 'b8d72b7d95db755d06e61756cb3b7a4d01e4074a0b5815c33899b4f6317bdca4'}]

def sha(data):return hashlib.sha256(data).hexdigest()
def receipt(p):return renderer.file_receipt(Path(p).resolve(),ROOT)
def disasm(word,address):return rabbitizer.Instruction(word,vram=address,category=rabbitizer.InstrCategory.R5900).disassemble()

def context(elf,address,size,role):
 data=elf.at_vram(address,size)
 return {'address':address,'size':size,'role':role,'original_bytes':data.hex(),'sha256':sha(data),'instructions':[{'address':address+i,'instruction':disasm(struct.unpack_from('<I',data,i)[0],address+i)} for i in range(0,size,4)]}
def allocated(e,expected):
    if e.type!=1 or e.phnum:raise ValueError('Only whole native relocatable objects, without hidden load segments, are supported')
    a=[s for s in e.sections if s['flags']&2]
    if len(a)!=3 or {(s['name'],s['type'],s['flags'])for s in a}!={('.vutext',1,6),('.vudata',1,3),('.vubss',8,3)}:raise ValueError('Unsupported or missing allocated section')
    t=e.section('.vutext')
    if t['size']!=len(expected)or e.section_data(t)!=expected:raise ValueError('Incomplete/different entire native allocated code')
    if e.section('.vudata')['size']or e.section('.vubss')['size']:raise ValueError('Any whole initialized data/BSS must be mapped before admission')
    return a,t

def math_program(data,expected):
    e=Elf32(data);a,t=allocated(e,expected)
    if len(expected)!=672 or sha(expected)!=PROGRAM_SHA:raise ValueError('Wrong whole original program')
    if any(s['type']in[4,9]and s['size']for s in e.sections):raise ValueError('Unexpected native VU relocation')
    functions=[s for s in e.symbols()if s['type']==2]
    if sorted((s['name'],s['value'],s['size'])for s in functions)!=sorted(EXPECTED_MATH):raise ValueError('Incomplete/duplicate/overlapping original VU routine boundary')
    if any(s['shndx']!=t['index']or s['visibility']!=0xeb for s in functions):raise ValueError('An EE address cannot alias a local VU routine')
    cursor=0
    for name,begin,size in EXPECTED_MATH:
        if begin!=cursor:raise ValueError('Original native VU instructions have a gap')
        pairs=list(struct.iter_unpack('<II',e.section_data(t)[begin:begin+size]))
        if [i*8 for i,(lo,hi)in enumerate(pairs)if hi&0x40000000]!=[size-16]:raise ValueError('Wrong original E termination or missing final delay pair')
        cursor+=size
    if cursor!=672:raise ValueError('Unowned native VU instructions')
    branches=[]
    for i,(lo,hi)in enumerate(struct.iter_unpack('<II',expected)):
        pc=i*8
        if hi&0x80000000:continue
        op=lo>>25
        if op in [0x20,0x21,0x28,0x29,0x2c,0x2d,0x2e,0x2f]:
            imm=lo&2047;imm=imm-2048 if imm&1024 else imm;target=pc+8+8*imm
            owner=next(f for f in EXPECTED_MATH if f[1]<=pc<f[1]+f[2])
            if not(owner[1]<=target<owner[1]+owner[2]and pc+8<owner[1]+owner[2]):raise ValueError('Unresolved/cross-owner native branch or delay')
            branches.append({'VU_byte_PC':pc,'VU_byte_target':target,'VU_byte_delay':pc+8,'owner':owner[0],'original_lower_word':lo})
        elif op in [0x24,0x25]:raise ValueError('Unresolved indirect native VU branch')
    if [(b['VU_byte_PC'],b['VU_byte_target'])for b in branches]!=[(576,656),(624,656)]:raise ValueError('Wrong real radial kernel direct branches')
    return e,a,t,branches

def math_chain(data,expected):
    e=Elf32(data);a,t=allocated(e,expected)
    if len(expected)!=720 or sha(expected)!=CHAIN_SHA:raise ValueError('Wrong complete original startup chain')
    words=lambda at:struct.unpack_from('<4I',expected,at)
    if words(0)!=(0x1000002b,0,0,0x4a540000)or words(688)!=(0x14000000,0,0,0)or words(704)!=(0x70000000,0,0,0):raise ValueError('Wrong native DMA count, packed84-instruction MPG, startup entry or END protocol')
    rels=[s for s in e.sections if s['type']in[4,9]and s['size']]
    if len(rels)!=1 or rels[0]['name']!='.rel.DVP.ovlytab'or rels[0]['type']!=9 or rels[0]['size']!=16 or rels[0]['flags']!=0x40 or rels[0]['entsize']!=8:raise ValueError('Only two actual nonallocated metadata R_MIPS32 relocations are supported')
    tab=e.section('.DVP.ovlytab');strings=e.section('.DVP.ovlystrtab');symtab=e.section('.symtab');rel=rels[0]
    if tab['type']!=0x7ffff420 or tab['flags']!=1 or tab['size']!=12 or strings['type']!=3 or strings['flags']!=1 or rel['info']!=tab['index']or rel['link']!=symtab['index']:raise ValueError('Wrong native overlay metadata domain')
    symbols=e.symbols();byname={s['name']:s for s in symbols};resolved=[]
    for off,info in struct.iter_unpack('<II',e.section_data(rel)):
        s=symbols[info>>8];addend=struct.unpack_from('<I',e.section_data(tab),off)[0]
        if info&255!=2 or off not in[0,4]or s['type']!=3 or s['value']!=0 or s['shndx']!=(t['index']if off==4 else strings['index']):raise ValueError('Unresolved/incorrect native metadata relocation')
        resolved.append({'offset':off,'type':2,'symbol':s['name'],'native_addend':addend,'resolved_value':addend+(0x2c0250 if off==4 else 0),'domain':'EE payload address'if off==4 else'DVP string-table relative offset'})
    if {r['offset']for r in resolved}!={0,4}:raise ValueError('Missing or duplicated real metadata relocation')
    no,lma,vma=struct.unpack('<III',e.section_data(tab));name=e.section_data(strings)[no:].split(b'\0',1)[0].decode('ascii');shadow=e.section(name)
    shadows=[s for s in e.sections if s['name'].startswith('.DVP.overlay.')]
    if no!=1 or lma!=16 or vma!=0 or len(shadows)!=1 or shadow['type']!=0x7ffff421 or shadow['flags']!=5 or shadow['size']!=672 or any(e.section_data(shadow)):raise ValueError('Wrong native whole-program zero-shadow/EE-load/local-VU mapping')
    for name,begin,size in EXPECTED_MATH:
        f=byname[name];stored=byname['_$'+name]
        if f['value']!=begin or f['shndx']!=shadow['index']or f['visibility']!=0xeb or stored['value']!=begin+16 or stored['shndx']!=t['index']or stored['visibility']!=0xeb:raise ValueError('Wrong local VU label or separate stored EE payload alias')
    if byname['vu0_startup_chain']['value']!=0 or byname['vu0_startup_chain_end']['value']!=720:raise ValueError('Wrong complete native startup chain boundary')
    return e,a,t,resolved,{'VU_byte_begin':0,'EE_payload_begin':0x2c0260,'native_payload_offset':16,'bytes':672,'zero_nonallocated_shadow_excluded':shadow['name']}

def math_inputs(e):
    text=e.section('.text');calls=[]
    for i,(word,)in enumerate(struct.iter_unpack('<I',e.section_data(text))):
        if word>>26!=18 or word&63 not in[56,57]:continue
        address=text['addr']+4*i;assembly=disasm(word,address)
        if 'vcall'not in assembly:continue
        calls.append({'address':address,'word':word,'assembly':assembly,'VU_byte_entry':(word>>6&0x7fff)*8})
    if len(calls)!=9 or {c['VU_byte_entry']for c in calls}!={16,96,240,288,336}:raise ValueError('Wrong complete original main-EE direct VU0 call inventory')
    bodies=[context(e,a,size,role)for a,size,role in [
        (0x1cb540,108,'Complete StartupVU0: no incoming arguments; enables TTE0x40 on actual channel0, FlushCache0, submits2C0250 DMA chain, waits mode0, then clears TTE. Zero4 alignment excluded.'),
        (0x174408,116,'Complete DMA startup: gets channel0 with real A0zero through29FA38, stores returned pointer36BD38 in call-delay slot; other channels initialized separately. Zero4 alignment excluded.'),
        (0x29fa38,40,'Complete channel getter A0index: original initialized table34C330 maps channel0 to MMIO10008000, the actual VIF0 DMA channel.'),
        (0x29fd20,104,'Complete send-chain body A0channel/A1chain: translates address29F9D8, waits29F960, writes TADR+30 when notFFFFFFFF, clears QWC+20 and sets chain/STR bits0x105 while retaining caller-enabledTTE. Adjacent16 non-return words are reviewed separately, not silently attached.'),
        (0x29f960,112,'Complete DMA wait body A0channel: polls CHCR STR0x100, retains original timeout/error calls. Adjacent8 non-return words are reviewed separately.'),
        (0x29f9d8,40,'Complete input address translator A0; supplied2C0250 passes unchanged because its top nibble is0, rather than scratchpad7.'),
        (0x29fde8,56,'Complete wait/query wrapper A0channel/A1mode: actual StartupVU0 supplies mode0 and physical A2zero, which this native body does not consume. No fabricated A2 formal input.'),
        (0x293920,16,'Complete FlushCache syscall wrapper, StartupVU0 explicitly supplies A0zero.'),
        (0x11d558,64,'Complete matrix helper: real A0output/A1matrixcolumns/A2four input vectors; loadsVF1..4 andVF5..8, VCALLMS60, CFC2.I synchronization, stores all four output qwords and returns A0.'),
        (0x149e58,360,'Complete bounds/vertex caller: actual matrixA0, packedscaleA1 low32bits, offset/carrier and output bufferA2, position outputA3, metadataT0/countT1/optionT2/minT3/max pointer[entrySP]. ActualVF31/30/29/28 matrix, VF27scale, VF25/26initialbounds; each active record loadsVF24 and currentA2 qwordVF23 before VCALLMS10. StoresVF22/VF21 after CFC2.I, finalVF26/VF25 to actual min/max pointers.'),
        (0x18b168,116,'Complete affine array producer: real matrixA0/countA1/inputA2/outputA3, loads allVF1..4 matrix columns, alternatesVF6/VF5 with VCALLMS120/F0, retains original input preload/CPU macro-stall behavior. Zero4 alignment excluded.'),
        (0x18b1e0,332,'Complete object state/plane producer: actual A0receiver only; reads matrix/context/count/pointers from its real fields, prepares inverse/transpose columns using complete11C6F8 then PEXT/PCPY, supplies normalVF5 and transformed-positionVF4 to VCALLMS150; CFC2.I then stores every outputVF5 lane. Zero4 alignment excluded.'),
        (0x11c6f8,156,'Complete inverse3x3/cofactor helper A0output/A1matrix: exact COP2 cross products, determinant and DIV Q scaling; producer18B1E0 then transposes those actual stored columns. Zero4 alignment excluded.'),
        (0x18e3a8,340,'Complete display-list matrix producer: actual headerA1, conditional byte selector supplies either originalVF1..4 andVF5..8 or CPU-saved T6/T5/T4/T7/T8/T3/T2/T1 qword registers, VCALLMS60, then storesVF5..8 into actual packet stream; includes both producer paths. Zero4 alignment excluded.'),
        (0x28ca78,7216,'Complete large object update matrix producer: saves receiverA0, actual final matrixVF1..4 comes from selected object/context pointers and VF5..8 from S1 four qwords; VCALLMS60 at28E54C then CFC2.I and full output stores. Entire7216 bytes retained, rather than a narrow call fragment.'),
        (0x28e768,320,'Complete second object matrix producer A0receiver: either linked object matrix(+40..70) or original matrix34F200, plus four object qwords; exact VCALLMS60 and original alternate cached-register paths; both original return paths included.')]]
    table=e.at_vram(0x34c330,40)
    if struct.unpack('<10I',table)!=(0x10008000,0x10009000,0x1000a000,0x1000b000,0x1000b400,0x1000c000,0x1000c400,0x1000c800,0x1000d000,0x1000d400):raise ValueError('Wrong actual channel0/VIF0 producer table')
    return {'all_original_main_EE_direct_VCALLMS_sites':calls,'original_main_EE_VCALLMSR_sites':0,'complete_original_EE_support_bodies':bodies,'original_initialized_DMA_channel_table':{'address':0x34c330,'bytes':40,'sha256':sha(table),'original_bytes':table.hex(),'input_evidence_only_source_counts_added':0},'unattached_adjacent_EE_words':[{'address':a,'bytes':n,'original_bytes':e.at_vram(a,n).hex(),'sha256':sha(e.at_vram(a,n)),'source_counts_added':0}for a,n in[(0x29fd88,16),(0x29f9d0,8)]],'radial_entry_1C0_direct_CPU_sites_identified':0,'radial_entry_other_dynamic_VIF_or_generated_launch_sites_unconfirmed':True,'radial_incoming_architectural_VF_contract_derived_from_original_instruction_reads_not_fabricated_C_formals':['VF10.xyzw','VF11.xyzw','VF12.xyzw','VF13.xyzw','VF14.x','VF15.xyzw','VF16.x','VF17.x'],'source_counts_added':0}
def idle_program(data,expected):
    e=Elf32(data);a,t=allocated(e,expected)
    if any(s['type']in[4,9]and s['size']for s in e.sections):raise ValueError('Unexpected native relocation')
    functions=[s for s in e.symbols()if s['type']==2]
    if len(functions)!=1 or(functions[0]['name'],functions[0]['value'],functions[0]['size'],functions[0]['visibility'],functions[0]['shndx'])!=('vu1_startup_idle',0,16,0xeb,t['index']):raise ValueError('Wrong complete VU-local idle boundary/domain')
    if list(struct.iter_unpack('<II',expected))!=[(0x8000033c,0x400002ff),(0x8000033c,0x2ff)]:raise ValueError('Whole idle entry must include original E and final delay without register/data operations')
    return e,a,t

def idle_chain(data,expected):
    e=Elf32(data);a,t=allocated(e,expected)
    if len(expected)!=64 or struct.unpack_from('<4I',expected)!=(0x10000002,0,0,0x4a020000)or struct.unpack_from('<4I',expected,32)!=(0x14000000,0,0,0)or struct.unpack_from('<4I',expected,48)!=(0x70000000,0,0,0):raise ValueError('Wrong whole DMA CNT2/MPG2/MSCAL0/END chain')
    rels=[s for s in e.sections if s['type']in[4,9]and s['size']];tab=e.section('.DVP.ovlytab');strings=e.section('.DVP.ovlystrtab');symtab=e.section('.symtab')
    if len(rels)!=1 or rels[0]['type']!=9 or rels[0]['name']!='.rel.DVP.ovlytab'or rels[0]['size']!=16 or rels[0]['flags']!=0x40 or rels[0]['info']!=tab['index']or rels[0]['link']!=symtab['index']:raise ValueError('Wrong actual nonallocated metadata relocations')
    if(tab['type'],tab['flags'],tab['size'])!=(0x7ffff420,1,12)or(strings['type'],strings['flags'])!=(3,1):raise ValueError('Wrong overlay metadata domain')
    syms=e.symbols();fields=[]
    for off,info in struct.iter_unpack('<II',e.section_data(rels[0])):
        s=syms[info>>8];addend=struct.unpack_from('<I',e.section_data(tab),off)[0]
        if info&255!=2 or off not in[0,4]or s['type']!=3 or s['value']or s['shndx']!=(t['index']if off==4 else strings['index']):raise ValueError('Unsupported/misresolved real native metadata relocation')
        fields.append({'offset':off,'type':2,'symbol':s['name'],'native_addend':addend,'resolved_value':addend+(0x2c45c0 if off==4 else 0),'domain':'EE payload address'if off==4 else'DVP string-table relative offset'})
    if {r['offset']for r in fields}!={0,4}:raise ValueError('Missing/duplicate actual relocation')
    no,lma,vma=struct.unpack('<III',e.section_data(tab));shadowname=e.section_data(strings)[no:].split(b'\0',1)[0].decode('ascii');shadow=e.section(shadowname)
    if(no,lma,vma)!=(1,16,0)or(shadow['type'],shadow['flags'],shadow['size'])!=(0x7ffff421,5,16)or any(e.section_data(shadow))or len([s for s in e.sections if s['name'].startswith('.DVP.overlay.')])!=1:raise ValueError('Wrong zero-shadow/local-VU/EE-load mapping')
    names={s['name']:s for s in syms};vu=names['vu1_startup_idle'];stored=names['_$vu1_startup_idle']
    if(vu['value'],vu['visibility'],vu['shndx'])!=(0,0xeb,shadow['index'])or(stored['value'],stored['visibility'],stored['shndx'])!=(16,0xeb,t['index'])or names['vu1_startup_chain']['value']!=0 or names['vu1_startup_chain_end']['value']!=64:raise ValueError('Wrong VU symbol domain or whole startup chain boundary')
    return e,a,t,fields

def idle_inputs(e):
    body=context(e,0x1cb5b0,108,'Complete StartupVU1 no incoming arguments: actual36BD3C channel1, enables TTE0x40, FlushCache0, starts2C45C0 chain, waits mode0 with unused physicalA2zero, clears TTE. Zero4 alignment excluded.')
    support=[context(e,a,n,role)for a,n,role in[(0x174408,116,'Complete channel initialization: channel1 getter result is stored at36BD3C in actual174444 delay slot.'),(0x29fa38,40,'Complete channel getter; initialized34C330 table index1 is10009000/VIF1.'),(0x29fd20,104,'Complete DMA send A0channel/A1chain, waits actual channel, writes chain TADR/QWC and STR/MOD while retaining callerTTE.'),(0x29f960,112,'Complete actual channel wait, polling STR0x100 with original timeout path.'),(0x29f9d8,40,'Complete address translator; actual2C45C0 pointer remains unchanged.'),(0x29fde8,56,'Complete wait/query wrapper actualA1mode0; no consumedA2 formal is fabricated.'),(0x293920,16,'Complete FlushCache syscall, actualA0zero.')]]
    table=e.at_vram(0x34c330,40)
    if struct.unpack_from('<I',table,4)[0]!=0x10009000:raise ValueError('Wrong actual VIF1 channel identity')
    return {'complete_CPU_entry':body,'complete_original_support_bodies':support,'DMA_input_table':{'EE_address':0x34c330,'bytes':40,'sha256':sha(table),'original_bytes':table.hex(),'source_data_bytes_added':0},'incoming_VI_VF_VU_memory_Q_P_I_flags':[],'native_action':'Terminate VU1 micro execution through E, retaining its required final NOP delay pair; all VU data, VI/VF, arithmetic flags and Q/P/I values stay intact while execution-control state terminates.','distinct_original_family_and_processor_from_VU0_idle_entry':True,'source_counts_added':0}

def output_path(output):
    p=Path(output).resolve()
    if not(p.is_relative_to(ROOT/'build/vu/extra')or p.is_relative_to(ROOT/'build/vu_matches/union_stage')):raise ValueError('Extra VU output escapes maintained/private ownership')
    return p

def checked_manifest(bundle=DEFAULT_BUNDLE):
    bundle=Path(bundle).resolve();p=renderer.contained(bundle,'config/vu_extra_sources.json');m=json.loads(p.read_text())
    if m.get('schema')!=1 or m.get('kind')!='two-mandatory-extra-readable-native-VU-components'or m.get('components')!=EXPECTED_COMPONENTS or m.get('original_sha256')!=ORIGINAL_SHA or m.get('renderer_original_registry_unchanged_and_mandatory')is not True or m.get('initialized_data_bytes')!=0 or m.get('BSS_bytes')!=0 or m.get('historical_original_compiler_identity_confirmed')is not False or m.get('full_source_relink_complete')is not False or m.get('unconfirmed_dynamic_VU0_entry_1C0')is not True:raise ValueError('Missing/duplicate/foreign original extra-VU ownership or unsupported source claim')
    parent_path=renderer.contained(bundle,'docs/evidence/vu_math_bootstrap_parent_review.json')
    if sha(parent_path.read_bytes())!='4f977c3c173120e6e07ea6aee262370f8311db7d7f87539ed233a0c79905b6ce':raise ValueError('Independent parent complete native/input review changed')
    parent=json.loads(parent_path.read_text())
    if parent['status']!='PASS_PARENT_INDEPENDENT_COMPLETE_VU0_MATH672_AND_VU1_BOOTSTRAP16_WITH_ENTIRE_NATIVE_CHAINS_AND_REAL_INPUTS':raise ValueError('Independent parent review is incomplete')
    legacy=renderer.current_report(ROOT,renderer.DEFAULT_OUTPUT)
    e,_,_,programs=renderer.original_mapping();deps={'docs/evidence/vu_math_bootstrap_parent_review.json':renderer.file_receipt(parent_path,bundle)};proofs={}
    for c in EXPECTED_COMPONENTS:
        for key,h in [('source','source_sha256'),('chain_source','chain_source_sha256'),('evidence','evidence_sha256')]:
            path=renderer.contained(bundle,c[key]);r=renderer.file_receipt(path,bundle)
            if r['sha256']!=c[h]:raise ValueError('Reviewed extra source/CPU input evidence changed')
            deps[c[key]]=r
        source=renderer.contained(bundle,c['source']).read_text();wrapper=renderer.contained(bundle,c['chain_source']).read_text()
        if '.include'in source.lower()or wrapper.count('.include "'+Path(c['source']).name+'"')!=1 or any(t in(source+wrapper).lower()for t in['.word','.byte','.long','.quad','.incbin','.space','.org']):raise ValueError('Unowned include or preserved literal words cannot be VU source')
        body=e.at_vram(c['EE_payload_begin'],c['code_bytes']);chain=e.at_vram(c['EE_chain_begin'],c['chain_bytes'])
        if sha(body)!=c['program_sha256']or sha(chain)!=c['chain_sha256']:raise ValueError('Wrong whole original native extra program/chain')
        original_family=next(p for p in programs if p['family_file_name_hash']==c['family'])
        if original_family['VU_bytes']!=c['code_bytes']or original_family['entire_program_sha256']!=c['program_sha256']:raise ValueError('Wrong original unique-program scope')
        evidence=json.loads(renderer.contained(bundle,c['evidence']).read_text())
        actual=math_inputs(e)if c['processor']=='VU0'else idle_inputs(e)
        expected=evidence['CPU_setup_and_actual_input_review']if c['processor']=='VU0'else evidence['CPU_input_review']
        if actual!=expected:raise ValueError('Stale/false actual complete CPU launch/input/header/flags proof')
        proofs[c['family']]={'program':body,'chain':chain,'CPU_input_review':actual}
    for rel in ['config/vu_extra_sources.json','tools/vu_extra_build.py','tools/vu_union_sources.py','tools/test_vu_union.py']:
        deps[rel]=renderer.file_receipt(renderer.contained(bundle,rel),bundle)
    current={**legacy['dependency_hashes'],'build/vu/renderer/vu_source_report.json':renderer.file_receipt(renderer.DEFAULT_OUTPUT/renderer.REPORT_NAME,ROOT)['sha256']}
    for rel,r in deps.items():current[renderer.contained(bundle,rel).relative_to(ROOT).as_posix()]=r['sha256']
    return m,e,proofs,legacy,deps,dict(sorted(current.items()))

def inspect_native(family,program_object,chain_object,expected):
    pv=math_program if family=='11753275'else idle_program;cv=math_chain if family=='11753275'else idle_chain
    p=pv(program_object,expected['program']);c=cv(chain_object,expected['chain'])
    def sections(parsed):return [{**s,'whole_native_sha256':sha(parsed[0].section_data(s))}for s in parsed[1]]
    return {'program_allocated_sections':sections(p),'chain_allocated_sections':sections(c),'entire_native_program_sha256':sha(p[0].section_data(p[2])),'entire_native_chain_sha256':sha(c[0].section_data(c[2])),'actual_resolved_nonallocated_metadata_relocations':c[3],'initialized_data_bytes':0,'BSS_bytes':0,'unsupported_allocated_sections':0,'original_nonallocated_debug_shadow_bytes_excluded':len(expected['program'])}

def current_report(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT):
    bundle=Path(bundle).resolve();out=output_path(output);m,e,proofs,legacy,deps,dependency_hashes=checked_manifest(bundle)
    r=json.loads((out/REPORT_NAME).read_text())
    if r['dependency_hashes']!=dependency_hashes or r['bundle_root']!=bundle.relative_to(ROOT).as_posix()or r['components']!=EXPECTED_COMPONENTS or set(r['native_components'])!={'11753275','376118779'}:raise ValueError('Stale/incomplete extra VU source/registry/renderer receipt')
    for c in EXPECTED_COMPONENTS:
        family=c['family'];item=r['native_components'][family];folder=out/family
        for name in['program.o','chain.o','chain.bin']:
            if item['files'][name]!=receipt(folder/name):raise ValueError('Changed complete extra native object/chain')
        proof=inspect_native(family,(folder/'program.o').read_bytes(),(folder/'chain.o').read_bytes(),proofs[family])
        if item['native_proof']!=proof or(folder/'chain.bin').read_bytes()!=proofs[family]['chain']or item['CPU_input_review']!=proofs[family]['CPU_input_review']:raise ValueError('False native or complete CPU proof')
    if r['initialized_data_bytes']or r['BSS_bytes']or r['historical_original_compiler_identity_confirmed']or r['full_source_relink_complete']or not r['unconfirmed_dynamic_VU0_entry_1C0']:raise ValueError('False extra data/compiler/entry claim')
    return {**r,'freshness':'CURRENT_TWO_WHOLE_EXTRA_VU_PROGRAMS_AND_CHAINS_VERIFIED'}

def run(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT,fresh=False):
    bundle=Path(bundle).resolve();out=output_path(output)
    if fresh and out.exists()and any(out.iterdir()):raise ValueError('Independent extra replay needs a new empty output')
    m,e,proofs,legacy,deps,dependency_hashes=checked_manifest(bundle);exe=ROOT/'tools/third_party/dvp/bin/dvp-as.exe';native={};out.mkdir(parents=True,exist_ok=True)
    for c in EXPECTED_COMPONENTS:
        family=c['family'];folder=out/family;folder.mkdir(exist_ok=True);commands=[]
        for mode,source,flags in[('program',c['source'],['--defsym','VU_NATIVE_STANDALONE=1']),('chain',c['chain_source'],['-I',str(renderer.contained(bundle,c['source']).parent)])]:
            cmd=[str(exe),*flags,'-o',str(folder/(mode+'.o')),str(renderer.contained(bundle,source))];p=subprocess.run(cmd,capture_output=True,timeout=30,cwd=renderer.contained(bundle,source).parent)
            if p.returncode:raise ValueError('Pinned DVP extra assembly failed: '+p.stderr.decode(errors='replace'))
            commands.append(cmd)
        proof=inspect_native(family,(folder/'program.o').read_bytes(),(folder/'chain.o').read_bytes(),proofs[family]);o=Elf32((folder/'chain.o').read_bytes());(folder/'chain.bin').write_bytes(o.section_data(o.section('.vutext')))
        native[family]={'native_proof':proof,'CPU_input_review':proofs[family]['CPU_input_review'],'files':{n:receipt(folder/n)for n in['program.o','chain.o','chain.bin']},'actual_native_commands':commands}
    r={'kind':'two-mandatory-readable-native-VU-extra-source-components','bundle_root':bundle.relative_to(ROOT).as_posix(),'components':EXPECTED_COMPONENTS,'dependency_hashes':dependency_hashes,'native_components':native,'initialized_data_bytes':0,'BSS_bytes':0,'historical_original_compiler_identity_confirmed':False,'full_source_relink_complete':False,'unconfirmed_dynamic_VU0_entry_1C0':True,'renderer_native_proof_and_all_files_unchanged':True}
    (out/REPORT_NAME).write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8');return current_report(bundle,out)

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--fresh',action='store_true');p.add_argument('--check',action='store_true');a=p.parse_args();r=current_report(a.bundle_root,a.output)if a.check else run(a.bundle_root,a.output,a.fresh);print(json.dumps({'status':'PASS','report':receipt(output_path(a.output)/REPORT_NAME),'freshness':r['freshness']}))
if __name__=='__main__':main()
