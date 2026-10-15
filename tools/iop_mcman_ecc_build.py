"""Mandatory original mcman initialized ECC parity table, exactly256 data bytes.

Both measured scalar compiler profiles emit only mutable .data256; no function,
code, BSS or relocation is admitted. Source name is reconstructed: original IRX
has only its null ELF symbol. Original checksum/correction code remains unowned.
"""
import copy,hashlib,json,random,re,struct,subprocess,sys
from pathlib import Path
ROOT=next(p for p in Path(__file__).resolve().parents if(p/'config/target.json').is_file());FOLDER=ROOT/'tools'
sys.path.insert(0,str(ROOT/'tools'));sys.path.insert(0,str(ROOT/'build/iop_extra'));sys.path.insert(0,str(ROOT/'build/iop_extra/second_cohort'))
from common import Elf32
from iop_build import allocated_read,native_inputs,MEASURED_OBJECT_FLAGS
import common,iop_build
import original_contract as oc
import original_device_contract as dc
MODULE='disc/irx/module_02.irx';MODULE_SHA=oc.SHA
SOURCE='iop/src/mcman/mc_ecc_parity_table.c';NAME='mcman_xor_table';START=0x11da8;SIZE=256
PRIMARY='build/iop_extra/primary_ps2sdk/iop/memorycard/mcman/src/main.c';LICENSE='iop/src/mcman/LICENSE.PS2SDK'
PROOF='build/reports/iop_extra_ecc_table_original_contract.json';PROPOSAL='build/reports/iop_extra_ecc_table_private_proposal.json'
FRONTIER='build/reports/iop_extra_ecc_table_frozen_frontier.json';PEER='build/reports/hand_iop_extra_ecc_table_independent_review.json';PEER_NATIVE='build/reports/hand_iop_extra_ecc_table_independent_native_review.json'
TABLE_SHA='4c942cad2423da5561ae3e0b35f2d9560ca66abe70da64dcbb2b8af9419e8bf9'
KERNEL_SHA='fa185228bbaebfa96d4dfb5a9e6b45e11967c6d253159fa7f7b23f7a85dc4fe2'
FLAGS=['-Os', '-G0', '-mips1', '-mgp32', '-mfp32', '-mlong32', '-mcpu=r3000', '-malign-functions=2']
AS_FLAGS=['-G0', '-mips1', '-mabi=32', '-O0']
PINNED={'iop/src/mcman/mc_ecc_parity_table.c': '34587ac8ea00ae70f6c6c87bca49d5b69475ad6f0660ef013c724ba588ec45b2', 'iop/src/mcman/LICENSE.PS2SDK': '1ecee940922a6886baccddd9133d17f1ce677d32c5a954fac8e48224f2766fe8', 'build/iop_extra/primary_ps2sdk/iop/memorycard/mcman/src/main.c': 'd31c03143c40fcbb7fa55cbb5ed8711eaecf53deb2d0eecc654b125e20626ffb', 'build/iop_extra/primary_ps2sdk/iop/memorycard/mcman/include/mcman.h': '4a53cd27aa9ac2407c4f32752b288cc6467f6d5ba21f297c51f4b503a71a557e', 'build/iop_research/primary_ps2sdk/iop/system/loadcore/src/loadcore.c': '2eb29f11cce431de18f8d5f64c64e4eda22507bfca26487a57b53b63750e0d78', 'build/iop_research/interfaces.json': '5cc886e6bf8d83420f2aa0842f78e1fc48fe48423cd3d8dac2fa93e886dca25b', 'build/iop_extra/original_contract.py': 'b04df5ed4dc80abb8740dead0b81e16bb7664c3d82ba14f9afdbccfe051b5457', 'build/iop_extra/second_cohort/original_device_contract.py': 'ac9620593ff1849a4e2e61ebf7594823af3a08660094c4e906022f7ed5584233', 'build/reports/iop_extra_ecc_table_original_contract.json': 'a841e3d0217f8ad81cd2a9caac039149186427f36d2fa9dcb7046b4914c86441', 'build/reports/iop_extra_ecc_table_private_proposal.json': '807d094c6dd3c24a5ec13266263fb2d2dddf2485e9000a4997b5c37ff88515ef', 'build/reports/iop_extra_ecc_table_guard_validation.json': 'b051213e8e22422d87ecf9d1c078762a439c409db9823e80110391e55841797d', 'build/reports/iop_extra_ecc_table_frozen_frontier.json': 'cbafebef9afe117b03e3b817337ee717983d8c1d421b2e9350f92d067237ccfc', 'build/reports/hand_iop_extra_ecc_table_independent_review.json': 'f0c3df798faa539926d8dbe16e7eea75e7b870b16e68862dbe4757947584970d', 'build/reports/hand_iop_extra_ecc_table_independent_native_review.json': '26affb0dae7fd1af39e7a60df01062c271fb199a7165866ae13640fc46c1f4a7', 'build/reports/hand_iop_extra_ecc_table_independent_guard_review.json': 'aef944f7279d6fdfd56d583166a6e5c978c1b3b7ad9b32b440c79557ef3e184b', 'build/iop_extra/ecc_cohort/verify_ecc_table.py': '5d83dfacd2397229660e31e9f138b893b2801f530cf18f57fc06867d1ba81874', 'build/iop_extra/ecc_cohort/table_guard_validation.py': '87493a5081578ce26cf0c089d9bb5f16ee579b6b4a81d8f86558316736c45d07', 'tools/common.py': 'ea66a7d1022952de2eb5c1d0bbe8551fb0ef6a472d6153b1dde05d0bec42c2ce', 'tools/iop_build.py': 'aed6391f61893537776e417c0e6efd06171f941c4200fd94079f3a537fd89ea7', 'disc/irx/module_00.irx': '565ec77e75f174cfddf72c41ccc446c1c07a3d5fb0a2ccfefad337cb8a7d0728', 'disc/irx/module_01.irx': '78ca085ba4d0719b6753c271d9f911b37bcb8dd8ac910924e504b0e99c7f8816', 'disc/irx/module_02.irx': '1fe154231adbd587f9fb6ec1c7d4201c87c76ffcc91c8615474f24d26c05c7b0', 'disc/irx/module_03.irx': '9c9a7d8fff21ccd11eae79592842bef1c4d1ddb716f918b1facb9d2b03a76800', 'disc/irx/module_04.irx': 'd26a8dcd121ff4ded9c819b72864ea7f4e723932cc2eab1b4f0f1c93faad43ef', 'disc/irx/module_05.irx': 'c6b249bc32f021df08a572429ec47f56d3cd0e7da5364076557a4b806f0c0b13', 'disc/irx/module_06.irx': '5d0bfa40ad6e927efed0c8d5c3e6a6c9e3d05b7a7338196594f1c72ee3046a6d', 'disc/irx/module_07.irx': '9fa190ec393a60cbed1c04764c922e7b41d04ff0f41436cfae4cf198e1cdb6a5', 'disc/irx/module_08.irx': '9f761df401dfefda6f2122218fc6e2f53908c4def3ea59699c397f18f6e17201'}
CLAIM={'name': 'mcman_xor_table', 'kind': 'initialized_data', 'source': 'iop/src/mcman/mc_ecc_parity_table.c', 'source_sha256': '34587ac8ea00ae70f6c6c87bca49d5b69475ad6f0660ef013c724ba588ec45b2', 'module_offset': 73128, 'object_offset': 0, 'size': 256, 'section': '.data', 'native_flags': 3, 'native_alignment': 4, 'original_data_sha256': '4c942cad2423da5561ae3e0b35f2d9560ca66abe70da64dcbb2b8af9419e8bf9', 'source_identifier_kind': 'RECONSTRUCTED_C_NAME_NO_ORIGINAL_ELF_DATA_SYMBOL', 'mutable': True, 'profiles': ['legacy-scalar-leaf-114', 'legacy-scalar-leaf-136'], 'source_functions': 0, 'source_code_bytes': 0, 'source_BSS_bytes': 0, 'source_relocations': 0}
EXPECTED={'schema': 'sly3-partial-iop-mcman-ecc-data-v1', 'module': 'disc/irx/module_02.irx', 'module_sha256': '1fe154231adbd587f9fb6ec1c7d4201c87c76ffcc91c8615474f24d26c05c7b0', 'functions': [], 'data_objects': [{'name': 'mcman_xor_table', 'kind': 'initialized_data', 'source': 'iop/src/mcman/mc_ecc_parity_table.c', 'source_sha256': '34587ac8ea00ae70f6c6c87bca49d5b69475ad6f0660ef013c724ba588ec45b2', 'module_offset': 73128, 'object_offset': 0, 'size': 256, 'section': '.data', 'native_flags': 3, 'native_alignment': 4, 'original_data_sha256': '4c942cad2423da5561ae3e0b35f2d9560ca66abe70da64dcbb2b8af9419e8bf9', 'source_identifier_kind': 'RECONSTRUCTED_C_NAME_NO_ORIGINAL_ELF_DATA_SYMBOL', 'mutable': True, 'profiles': ['legacy-scalar-leaf-114', 'legacy-scalar-leaf-136'], 'source_functions': 0, 'source_code_bytes': 0, 'source_BSS_bytes': 0, 'source_relocations': 0}], 'native_profiles': {'114': ['-Os', '-G0', '-mips1', '-mgp32', '-mfp32', '-mlong32', '-mcpu=r3000', '-malign-functions=2'], '136': ['-Os', '-G0', '-mips1', '-mgp32', '-mfp32', '-mlong32', '-mcpu=r3000', '-malign-functions=2']}, 'assembler_flags': ['-G0', '-mips1', '-mabi=32', '-O0'], 'source': 'iop/src/mcman/mc_ecc_parity_table.c', 'source_sha256': '34587ac8ea00ae70f6c6c87bca49d5b69475ad6f0660ef013c724ba588ec45b2', 'name': 'mcman_xor_table', 'source_initialized_section': '.data', 'source_initialized_data_bytes': 256, 'source_code_bytes': 0, 'source_functions': 0, 'source_BSS_bytes': 0, 'source_native_relocation_count': 0, 'license': 'iop/src/mcman/LICENSE.PS2SDK', 'license_sha256': '1ecee940922a6886baccddd9133d17f1ce677d32c5a954fac8e48224f2766fe8', 'pinned_dependencies': {'iop/src/mcman/mc_ecc_parity_table.c': '34587ac8ea00ae70f6c6c87bca49d5b69475ad6f0660ef013c724ba588ec45b2', 'iop/src/mcman/LICENSE.PS2SDK': '1ecee940922a6886baccddd9133d17f1ce677d32c5a954fac8e48224f2766fe8', 'build/iop_extra/primary_ps2sdk/iop/memorycard/mcman/src/main.c': 'd31c03143c40fcbb7fa55cbb5ed8711eaecf53deb2d0eecc654b125e20626ffb', 'build/iop_extra/primary_ps2sdk/iop/memorycard/mcman/include/mcman.h': '4a53cd27aa9ac2407c4f32752b288cc6467f6d5ba21f297c51f4b503a71a557e', 'build/iop_research/primary_ps2sdk/iop/system/loadcore/src/loadcore.c': '2eb29f11cce431de18f8d5f64c64e4eda22507bfca26487a57b53b63750e0d78', 'build/iop_research/interfaces.json': '5cc886e6bf8d83420f2aa0842f78e1fc48fe48423cd3d8dac2fa93e886dca25b', 'build/iop_extra/original_contract.py': 'b04df5ed4dc80abb8740dead0b81e16bb7664c3d82ba14f9afdbccfe051b5457', 'build/iop_extra/second_cohort/original_device_contract.py': 'ac9620593ff1849a4e2e61ebf7594823af3a08660094c4e906022f7ed5584233', 'build/reports/iop_extra_ecc_table_original_contract.json': 'a841e3d0217f8ad81cd2a9caac039149186427f36d2fa9dcb7046b4914c86441', 'build/reports/iop_extra_ecc_table_private_proposal.json': '807d094c6dd3c24a5ec13266263fb2d2dddf2485e9000a4997b5c37ff88515ef', 'build/reports/iop_extra_ecc_table_guard_validation.json': 'b051213e8e22422d87ecf9d1c078762a439c409db9823e80110391e55841797d', 'build/reports/iop_extra_ecc_table_frozen_frontier.json': 'cbafebef9afe117b03e3b817337ee717983d8c1d421b2e9350f92d067237ccfc', 'build/reports/hand_iop_extra_ecc_table_independent_review.json': 'f0c3df798faa539926d8dbe16e7eea75e7b870b16e68862dbe4757947584970d', 'build/reports/hand_iop_extra_ecc_table_independent_native_review.json': '26affb0dae7fd1af39e7a60df01062c271fb199a7165866ae13640fc46c1f4a7', 'build/reports/hand_iop_extra_ecc_table_independent_guard_review.json': 'aef944f7279d6fdfd56d583166a6e5c978c1b3b7ad9b32b440c79557ef3e184b', 'build/iop_extra/ecc_cohort/verify_ecc_table.py': '5d83dfacd2397229660e31e9f138b893b2801f530cf18f57fc06867d1ba81874', 'build/iop_extra/ecc_cohort/table_guard_validation.py': '87493a5081578ce26cf0c089d9bb5f16ee579b6b4a81d8f86558316736c45d07', 'tools/common.py': 'ea66a7d1022952de2eb5c1d0bbe8551fb0ef6a472d6153b1dde05d0bec42c2ce', 'tools/iop_build.py': 'aed6391f61893537776e417c0e6efd06171f941c4200fd94079f3a537fd89ea7', 'disc/irx/module_00.irx': '565ec77e75f174cfddf72c41ccc446c1c07a3d5fb0a2ccfefad337cb8a7d0728', 'disc/irx/module_01.irx': '78ca085ba4d0719b6753c271d9f911b37bcb8dd8ac910924e504b0e99c7f8816', 'disc/irx/module_02.irx': '1fe154231adbd587f9fb6ec1c7d4201c87c76ffcc91c8615474f24d26c05c7b0', 'disc/irx/module_03.irx': '9c9a7d8fff21ccd11eae79592842bef1c4d1ddb716f918b1facb9d2b03a76800', 'disc/irx/module_04.irx': 'd26a8dcd121ff4ded9c819b72864ea7f4e723932cc2eab1b4f0f1c93faad43ef', 'disc/irx/module_05.irx': 'c6b249bc32f021df08a572429ec47f56d3cd0e7da5364076557a4b806f0c0b13', 'disc/irx/module_06.irx': '5d0bfa40ad6e927efed0c8d5c3e6a6c9e3d05b7a7338196594f1c72ee3046a6d', 'disc/irx/module_07.irx': '9fa190ec393a60cbed1c04764c922e7b41d04ff0f41436cfae4cf198e1cdb6a5', 'disc/irx/module_08.irx': '9f761df401dfefda6f2122218fc6e2f53908c4def3ea59699c397f18f6e17201'}, 'admitted_source_component': 'MANDATORY_DATA_ONLY_NO_CHECKSUM_CODE', 'unmatched_checksum_code_counted': False, 'historical_compiler_identity': 'UNCONFIRMED', 'general_framed_O32_ABI': 'UNCONFIRMED'}
DEFAULT_MANIFEST=ROOT/'config/iop_mcman_ecc_partial.json';DEFAULT_OUTPUT=ROOT/'build/iop/mcman_ecc';REPORT_NAME='partial_iop_report.json'

def sha(b):return hashlib.sha256(b).hexdigest()

def parity_of_bit(index):return 0x80|(0x10 if index&1 else 1)|(0x20 if index&2 else 2)|(0x40 if index&4 else 4)

def parity_of_byte(value):
 result=0
 for index in range(8):
  if value&(1<<index):result^=parity_of_bit(index)
 return result

def inspect_object_bytes(data,original):
 e=Elf32(data);h=struct.unpack_from('<16sHHIIIIIHHHHHH',data)
 if(e.type,e.flags,e.entry,e.phnum,e.phoff,e.phentsize,e.shentsize,e.shnum,e.shstrndx)!=(1,MEASURED_OBJECT_FLAGS,0,0,0,0,40,9,6)or h[3]!=1 or h[8]!=52 or h[0]!=bytes.fromhex('7f454c46010101000000000000000000'):raise ValueError('Unmeasured complete native ELF identity')
 names=['','.text','.data','.bss','.reginfo','.mdebug','.shstrtab','.symtab','.strtab'];types=[0,1,1,8,0x70000006,0x70000005,3,2,3]
 if[x['name']for x in e.sections]!=names or[x['type']for x in e.sections]!=types:raise ValueError('Unknown/missing/duplicate/relocating native section')
 if any(s['addr']or s['flags']for s in e.sections if s['name']not in('.text','.data','.bss')):raise ValueError('Unknown allocation/address')
 ranges=[(0,52),(e.shoff,e.shoff+e.shnum*40)]+[(s['offset'],s['offset']+s['size'])for s in e.sections if s['size']and s['type']!=8]
 for i,a in enumerate(ranges):
  if a[0]<0 or a[1]>len(data):raise ValueError('Native range outside object')
  for b in ranges[i+1:]:
   if max(a[0],b[0])<min(a[1],b[1]):raise ValueError('Overlapping complete native file ownership')
 ordered=sorted(ranges)
 if max(z for a,z in ordered)!=len(data):raise ValueError('Unowned trailing native payload')
 if any(any(data[a[1]:b[0]])for a,b in zip(ordered,ordered[1:])):raise ValueError('Unowned nonzero native alignment payload')
 allocated=[s for s in e.sections if s['flags']&2]
 if[s['name']for s in allocated]!=['.text','.data','.bss']:raise ValueError('Unowned native initialized section')
 for name,expected in[('.text',(0,0,1,6,4,0,0,0)),('.data',(0,256,1,3,4,0,0,0)),('.bss',(0,0,8,3,1,0,0,0))]:
  s=e.section(name)
  if tuple(s[k]for k in('addr','size','type','flags','alignment','entsize','link','info'))!=expected:raise ValueError('Unowned code/BSS/data tail or whole-data extent')
 reg=e.section('.reginfo')
 if tuple(reg[k]for k in('size','alignment','entsize','link','info'))!=(24,4,1,0,0)or e.section_data(reg)!=bytes(24):raise ValueError('Native producer has unknown executable/register metadata')
 symtab=e.section('.symtab')
 if tuple(symtab[k]for k in('size','entsize','alignment','link','info'))!=(144,16,4,8,6):raise ValueError('Unknown native symbol table extent')
 sy=e.symbols();objects=[s for s in sy if s['type']==1]
 if len(sy)!=9 or any(s['type']==2 for s in sy)or any(s['binding']and s['shndx']==0 for s in sy):raise ValueError('Extra native function/unresolved symbol')
 if len(objects)!=1 or tuple(objects[0][k]for k in('name','value','size','shndx','binding','visibility'))!=(NAME,0,256,2,1,0):raise ValueError('Whole initialized table symbol ownership differs')
 for s in sy:
  if s['index']==0 and not s['name']and not s['shndx']and all(s[k]==0 for k in('value','size','type','binding','visibility')):continue
  if s['type']==3:
   if s['name']or s['value']or s['size']or s['binding']or s['visibility']or s['shndx']not in(1,2,3,4,5):raise ValueError('Malformed/unowned native section symbol')
   continue
  if s['name']in('gcc2_compiled.','__gnu_compiled_c'):
   if tuple(s[k]for k in('value','size','type','binding','visibility','shndx'))!=(0,0,0,0,0,1):raise ValueError('Unowned compiler marker')
   continue
  if s not in objects:raise ValueError('Unowned defined/external symbol')
 if sorted(s['shndx']for s in sy if s['type']==3)!=[1,2,3,4,5]:raise ValueError('Missing/duplicate section symbol')
 native=e.section_data(e.section('.data'));_,target=allocated_read(original,START,256)
 if native!=target or native!=bytes(parity_of_byte(i)for i in range(256)):raise ValueError('Entire emitted initialized data differs from original or independent parity generation')
 return {'status':'PASS_ENTIRE_NATIVE256_BYTE_INITIALIZED_DATA_AND_ALL_ALLOCATED_SECTIONS','source_functions':0,'source_code_bytes':0,'source_initialized_data_bytes':256,'source_BSS_bytes':0,'native_source_relocations':[],'native_symbol':objects[0],'all_allocated_sections':[{'section':s['name'],'size':s['size'],'type':s['type'],'flags':s['flags'],'alignment':s['alignment'],'sha256':sha(e.section_data(s))}for s in allocated],'whole_native_data_sha256':sha(native),'object_sha256':sha(data)}

def reference_ecc(data):
 # Independently accumulate parity of the24 complemented column/row address bits.
 columns=0;even=0;odd=0
 for index,value in enumerate(data):
  columns^=parity_of_byte(value)
  if value.bit_count()&1:even^=~index;odd^=index
 return bytes([~columns&0x77,~even&0x7f,~odd&0x7f])

def execute_original_kernel(body,table,data):
 words=list(struct.unpack('<29I',body));regs=[(i*0x13131313)&0xffffffff for i in range(32)];regs[0]=0;regs[4]=0x10000000;regs[5]=0x10002000;regs[31]=0xeada0000;before=regs[:]
 memory={0x10000000+i:b for i,b in enumerate(data)};memory.update({START+i:b for i,b in enumerate(table)});memory.update({0x10002000+i:0xa5 for i in range(3)});pc=0x3b14;pending_load=None;pending_transfer=None;inputreads=[];tablereads=[];stores=[];steps=0
 while True:
  if not 0x3b14<=pc<0x3b88 or pc%4:raise ValueError('Original kernel control outside whole function')
  w=words[(pc-0x3b14)//4];op=w>>26;rs=(w>>21)&31;rt=(w>>16)&31;rd=(w>>11)&31;oldload=pending_load;oldtransfer=pending_transfer;pending_load=None;pending_transfer=None;nextpc=pc+4
  if w==0:pass
  elif op==0 and w&63==33:regs[rd]=(regs[rs]+regs[rt])&0xffffffff
  elif op==0 and w&63==38:regs[rd]=regs[rs]^regs[rt]
  elif op==0 and w&63==39:regs[rd]=~(regs[rs]|regs[rt])&0xffffffff
  elif op==15:regs[rt]=(w&0xffff)<<16
  elif op==9:regs[rt]=(regs[rs]+((w&0x7fff)-(w&0x8000)))&0xffffffff
  elif op==12:regs[rt]=regs[rs]&(w&0xffff)
  elif op==10:regs[rt]=int((regs[rs]if regs[rs]<0x80000000 else regs[rs]-0x100000000)<((w&0x7fff)-(w&0x8000)))
  elif op==36:
   address=(regs[rs]+((w&0x7fff)-(w&0x8000)))&0xffffffff;pending_load=(rt,memory[address])
   if 0x10000000<=address<0x10000080:inputreads.append(address)
   elif START<=address<START+256:tablereads.append(address)
   else:raise ValueError('Original checksum input/table range changed')
  elif op==40:
   address=(regs[rs]+((w&0x7fff)-(w&0x8000)))&0xffffffff
   if address not in(0x10002000,0x10002001,0x10002002):raise ValueError('Original ECC output extent changed')
   memory[address]=regs[rt]&255;stores.append(address)
  elif op in(4,5):
   condition=regs[rs]==regs[rt];taken=condition if op==4 else not condition
   pending_transfer=pc+4+((w&0x7fff)-(w&0x8000))*4 if taken else pc+8
  elif w==0x03e00008:pending_transfer=regs[31]
  else:raise ValueError('Unreviewed original ECC opcode')
  if oldload:regs[oldload[0]]=oldload[1]
  regs[0]=0;steps+=1
  if steps>4096:raise ValueError('Original128-byte loop did not terminate')
  if oldtransfer is not None:
   if oldtransfer==before[31]:break
   nextpc=oldtransfer
  pc=nextpc
 if pending_load or pending_transfer or inputreads!=list(range(0x10000000,0x10000080))or len(tablereads)!=128 or stores!=[0x10002000,0x10002001,0x10002002]:raise ValueError('Original128input/128table/3output and delay contract changed')
 if any(regs[i]!=before[i]for i in range(32)if i not in(1,2,3,4,6,7,8)):raise ValueError('Original kernel unreviewed clobber')
 if bytes(memory[0x10000000+i]for i in range(128))!=data or bytes(memory[START+i]for i in range(256))!=table:raise ValueError('Original kernel writes input or table')
 return bytes(memory[0x10002000+i]for i in range(3))

def semantic_states(original,rows):
 _,body=allocated_read(original,0x3b14,116,True);tables=[]
 for row in rows:
  e=Elf32((ROOT/row['object']).read_bytes());tables.append(e.section_data(e.section('.data')))
 for table in tables:
  for byte in range(256):
   if table[byte]!=parity_of_byte(byte)or((table[byte]>>7)&1)!=(byte.bit_count()&1):raise ValueError('Byte/overall parity derivation differs')
   for bit in range(8):
    if table[byte^1<<bit]^table[byte]!=parity_of_bit(bit):raise ValueError('Single-bit ECC basis differs')
  for x in range(256):
   for y in range(256):
    if table[x^y]!=table[x]^table[y]:raise ValueError('Entire generated parity table is not GF2 linear')
 rng=random.Random(0x45434333);inputs=[bytes([x])*128 for x in range(256)]
 for bit in range(1024):
  data=bytearray(128);data[bit//8]=1<<(bit%8);inputs.append(bytes(data))
 inputs +=[bytes(rng.getrandbits(8)for _ in range(128))for _ in range(128)]
 for data in inputs:
  expected=reference_ecc(data)
  for table in tables:
   if execute_original_kernel(body,table,data)!=expected:raise ValueError('Original full kernel with entire native-generated table changes ECC semantics')
 return {'status':'PASS_GENERATED_WHOLE_TABLE_AND_ORIGINAL_KERNEL_SEMANTICS','all_input_byte_values':256,'basis_transition_cases_per_profile':2048,'GF2_linearity_cases_per_profile':65536,'original_kernel_input_chunks':len(inputs),'native_generated_table_kernel_replays':len(inputs)*len(tables),'single_bit_input_positions':1024,'all_constant_input_bytes':256,'random128byte_buffers':128,'each_original_kernel_replay_has128_input_loads128_table_loads3_output_stores':True,'R3000_load_and_branch_delays_modelled':True,'no_original_kernel_code_counted_as_decompiled_source':True}

def checked(path,scope):
 p=Path(path);p=p if p.is_absolute()else ROOT/p;p=p.resolve()
 if not p.is_relative_to((ROOT/scope).resolve()):raise ValueError('Path escapes maintained ECC component scope')
 return p

def dependency_hashes():
 paths={p:sha((ROOT/p).read_bytes())for p in PINNED}
 paths[Path(__file__).resolve().relative_to(ROOT).as_posix()]=sha(Path(__file__).read_bytes())
 return paths

def validate_manifest(m):
 if m!=EXPECTED:raise ValueError('Unknown/missing/extra whole ECC data source/profile/type/section/code/ownership/identity')
 for path,h in PINNED.items():
  if sha((ROOT/path).read_bytes())!=h:raise ValueError('Pinned actual source/primary/original/loader/proof/helper changed: '+path)
 text=(ROOT/SOURCE).read_text()
 if any(token in text for token in('__asm','asm(','volatile')):raise ValueError('Unreviewed source adapter/scheduling fence')
 if not re.search(r'unsigned\s+char\s+mcman_xor_table\[256\]\s*=',text):raise ValueError('Actual source no longer defines complete mutable byte table')
 peer=json.loads((ROOT/PEER).read_bytes())
 if peer['blockers']or peer['scope']['entire_initialized_data_bytes']!=256 or peer['scope']['source_functions']or peer['scope']['source_code_bytes']or peer['scope']['source_BSS_bytes']or peer['scope']['source_relocations']or peer['validation']['pure_rejection_guards']!=6507 or peer['validation']['original_kernel_native_generated_table_replays']!=2816:raise ValueError('Independent whole table/original-consumer/native/state/guard prerequisite absent')
 return True

def validate_original(raw):
 if sha(raw)!=MODULE_SHA:raise ValueError('Original entire module02 changed')
 e=Elf32(raw)
 if(e.type,e.flags,e.entry)!=(0xff80,1,0x178):raise ValueError('Unconfirmed original IRX header')
 owner,table=allocated_read(e,START,SIZE)
 if tuple(owner[k]for k in('name','type','flags','addr','offset','size','alignment'))!=('.data',1,3,0x11d60,0x11e00,512,16):raise ValueError('Original allocated domain/whole section metadata differs')
 if sha(table)!=TABLE_SHA or table!=bytes(parity_of_byte(x)for x in range(256)):raise ValueError('Entire original mutable parity table differs')
 sy=e.symbols()
 if len(sy)!=1 or any(s['name']or s['value']or s['size']or s['shndx']or s['binding']or s['type']for s in sy):raise ValueError('Original has an unreviewed named data symbol; reconstructed identifier qualification stale')
 return e

def original_contract():
 raw=(ROOT/MODULE).read_bytes();e=validate_original(raw);records=oc.records(e)
 if len(records)!=2699:raise ValueError('Complete original relocation records changed')
 peer=json.loads((ROOT/PEER_NATIVE).read_bytes())['independent_original_contract']
 kernel=peer['whole_kernel'];_,body=allocated_read(e,kernel['module_address'],kernel['size'],True)
 if(kernel['module_address'],kernel['size'],sha(body))!=(0x3b14,116,KERNEL_SHA)or [hex(w)for w in struct.unpack('<29I',body)]!=kernel['words']:raise ValueError('Complete actual original116-byte consumer changed')
 for caller in peer['complete_callers']:
  f=caller['complete_body'];_,b=allocated_read(e,f['module_address'],f['size'],True)
  if sha(b)!=f['original_code_sha256']or [hex(w)for w in struct.unpack('<'+str(f['size']//4)+'I',b)]!=f['words']:raise ValueError('Complete original kernel caller changed')
 export=[r for r in records if r['module_address']==100]
 if export!=[peer['kernel_export']]:raise ValueError('Actual export20 pointer/relocation changed')
 pairs=[]
 for i,hi in enumerate(records):
  if hi['type']!=5:continue
  if i+1>=len(records)or records[i+1]['type']!=6:raise ValueError('Original IRX HI/LO ordering/carry contract changed')
  lo=records[i+1];address=((hi['word']&0xffff)<<16)+((lo['word']&0x7fff)-(lo['word']&0x8000))
  if START<=address<START+SIZE:pairs.append({'hi':hi,'lo':lo,'address':address})
 if pairs!=peer['table_actual_pointer_operands']:raise ValueError('Sole real table HI/LO consumer field/addend changed')
 if any(START<=r['module_address']<START+SIZE or r['type']==2 and START<=r['word']<START+SIZE for r in records):raise ValueError('Table has unreviewed relocation/pointer ownership')
 meta=json.loads((ROOT/'build/iop_research/interfaces.json').read_bytes())['modules'];own=next(m for m in meta if m['module']=='module_02.irx')
 controls=[x for x in dc.controls(e,own)if 0x3b14<=x['target']<0x3b88]
 if controls!=peer['full_kernel_controls']or any(0x3b14<x['target']<0x3b88 and not 0x3b14<=x['pc']<0x3b88 for x in controls):raise ValueError('Original boundaries/incoming actual calls changed')
 for m in meta:
  original=validate_original(raw)if m['module']=='module_02.irx'else Elf32((ROOT/'disc/irx'/m['module']).read_bytes())
  for t in m['tables']:
   _,payload=allocated_read(original,t['header_address'],t['byte_length'],True)
   if sha(payload)!=t['sha256']:raise ValueError('Whole original IRX import/export table changed: '+m['module'])
   if t['kind']=='IMPORT'and t['library']=='mcman'and any(x['ordinal']==20 for x in t['entries']):raise ValueError('An unreviewed external checksum consumer appeared')
 primary=(ROOT/PRIMARY).read_text();literal=re.search(r'static\s+const\s+u8\s+mcman_xortable\[256\]\s*=\s*\{(.*?)\};',primary,re.S)
 if literal is None:raise ValueError('Primary complete parity table disappeared')
 if bytes(int(x,0)for x in re.findall(r'0x[0-9a-fA-F]+|\b\d+\b',literal.group(1)))!=allocated_read(e,START,SIZE)[1]:raise ValueError('Primary/reference parity semantics differ')
 carry=[]
 for base in [0,0x6250,0x6258,0x6260,0x10000,0x17ff0,0x80000000,0xa0000000,0xfff00000]:
  hi,lo=pairs[0]['hi'],pairs[0]['lo'];target=(START+base)&0xffffffff
  relocated_hi=((hi['word']&0xffff)<<16)+((lo['word']&0x7fff)-(lo['word']&0x8000))+base
  carry_hi=((relocated_hi>>15)+1)>>1
  low=(lo['word']+base)&0xffff
  resolved=((carry_hi&0xffff)<<16)+((low&0x7fff)-(low&0x8000))
  if resolved&0xffffffff!=target:raise ValueError('Actual original IRX loadercarry table placement differs')
  carry.append({'load_base':base,'target':target,'HI':carry_hi&0xffff,'LO':low})
 return {'whole_module_sha256':MODULE_SHA,'original_data_sha256':TABLE_SHA,'original_table_file_offset':0x11e48,'original_table_source_identifier':'RECONSTRUCTED_ONLY','original_allocated_section':{k:owner for k,owner in [(key,e.section('.data')[key])for key in('name','type','flags','addr','offset','size','alignment')]},'actual_table_HI_LO_pairs':pairs,'original_source_table_relocations':[],'actual_export20':export[0],'complete_original_kernel_sha256':KERNEL_SHA,'complete_original_caller_bodies':[{'start':f['complete_body']['module_address'],'size':f['complete_body']['size'],'sha256':f['complete_body']['original_code_sha256']}for f in peer['complete_callers']],'actual_inputs':peer['original_inputs'],'actual_caller_arguments':peer['caller_arguments'],'all_extracted_import_export_tables_verified':True,'external_checksum_ordinal20_imports':[],'original_loadercarry_cases':carry,'unmatched_original_consumer_source_code_count':0}


def native_compile(revision,output):
 compiler=ROOT/f'tools/third_party/ee-gcc2.95.3-{revision}/bin/ee-gcc.exe';lib=compiler.parent.parent/'lib/gcc-lib/ee/2.95.3';assembler=ROOT/'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe';source=ROOT/SOURCE
 output.mkdir(parents=True,exist_ok=True);assembly=output/f'mc_ecc_parity_table_{revision}.raw.s';obj=output/f'mc_ecc_parity_table_{revision}.o';inputs=native_inputs(revision)
 for cmd in [[str(compiler),'-S','-x','c',*FLAGS,'-B'+lib.as_posix()+'/',source.as_posix(),'-o',assembly.as_posix()],[str(assembler),*AS_FLAGS,'-o',obj.as_posix(),assembly.as_posix()]]:
  result=subprocess.run(cmd,cwd=ROOT,capture_output=True,text=True,timeout=60)
  if result.returncode:raise RuntimeError(json.dumps({'command':cmd,'stderr':result.stderr,'exit':result.returncode}))
 return {'revision':str(revision),'profile':f'legacy-scalar-leaf-{revision}','compiler_flags':FLAGS[:],'assembler_flags':AS_FLAGS[:],'native_input_hashes':inputs,'assembly':assembly.relative_to(ROOT).as_posix(),'assembly_sha256':sha(assembly.read_bytes()),'assembly_unchanged':True,'object':obj.relative_to(ROOT).as_posix(),'object_sha256':sha(obj.read_bytes())}

def semantic_receipt():
 return {'status':'PASS_GENERATED_WHOLE_TABLE_AND_ORIGINAL_KERNEL_SEMANTICS','all_input_byte_values':256,'basis_transition_cases_per_profile':2048,'GF2_linearity_cases_per_profile':65536,'original_kernel_input_chunks':1408,'native_generated_table_kernel_replays':2816,'single_bit_input_positions':1024,'all_constant_input_bytes':256,'random128byte_buffers':128,'each_original_kernel_replay_has128_input_loads128_table_loads3_output_stores':True,'R3000_load_and_branch_delays_modelled':True,'no_original_kernel_code_counted_as_decompiled_source':True}

def progress(raw,original):
 return {'verified_source_functions':0,'verified_source_code_bytes':0,'verified_source_initialized_data_bytes':256,'verified_source_BSS_bytes':0,'preserved_original_file_bytes_excluded_from_source':len(raw)-256,'original_file_size':len(raw),'original_text_bytes_including_tables_and_stubs':original.section('.text')['size']}

def run(manifest_path=None,output=None):
 manifest_path=checked(manifest_path or DEFAULT_MANIFEST,'config');output=checked(output or DEFAULT_OUTPUT,'build/iop');output.mkdir(parents=True,exist_ok=True);report_path=output/REPORT_NAME
 report_path.write_text(json.dumps({'status':'UNVERIFIED_CURRENT_BUILD','progress':{'verified_source_functions':0,'verified_source_code_bytes':0,'verified_source_initialized_data_bytes':0}},indent=2)+'\n')
 manifest_raw=manifest_path.read_bytes();validate_manifest(json.loads(manifest_raw));deps=dependency_hashes();contract=original_contract();raw=(ROOT/MODULE).read_bytes();original=validate_original(raw);profiles=[];tables=[]
 for revision in ['114','136']:
  row=native_compile(revision,output);proof=inspect_object_bytes((ROOT/row['object']).read_bytes(),original)
  if row['native_input_hashes']!=native_inputs(revision)or dependency_hashes()!=deps:raise ValueError('Source/dependency/native inputs changed during fresh compile')
  profiles.append({**row,'whole_object_proof':proof});e=Elf32((ROOT/row['object']).read_bytes());tables.append(e.section_data(e.section('.data')))
 if len(tables)!=2 or tables[0]!=tables[1]:raise ValueError('Two entire native initialized data sections differ')
 states=semantic_states(original,profiles)
 if states!=semantic_receipt():raise ValueError('Complete2816 semantic replay receipt changed')
 owner,target=allocated_read(original,START,SIZE);rebuilt=bytearray(raw);at=owner['offset']+START-owner['addr'];rebuilt[at:at+SIZE]=tables[0]
 if bytes(rebuilt)!=raw:raise ValueError('Entire source-native table placed at original address changes a byte')
 partial=output/'module_02.partial.irx';partial.write_bytes(rebuilt)
 report={'status':'PASS_MCMAN_COMPLETE_MUTABLE_ECC_INITIALIZED_DATA','manifest':manifest_path.relative_to(ROOT).as_posix(),'manifest_sha256':sha(manifest_raw),'report_path':report_path.relative_to(ROOT).as_posix(),'dependency_hashes':deps,'module':MODULE,'module_sha256':MODULE_SHA,'functions':[],'data_objects':[copy.deepcopy(CLAIM)],'data_native_profiles':profiles,'original_contract':contract,'semantic_states':states,'progress':progress(raw,original),'partial_module':partial.relative_to(ROOT).as_posix(),'partial_module_sha256':sha(partial.read_bytes()),'full_file_bytes_equal':True,'whole_module_source_ownership':False,'unmatched_checksum_and_correction_source_count':0,'all_unowned_bytes_and_metadata':'PRESERVATION_EXCLUDED_FROM_SOURCE','historical_iop_compiler_identity':'UNCONFIRMED','general_original_o32_abi':'UNCONFIRMED','public_mutations':False}
 report_path.write_text(json.dumps(report,indent=2)+'\n');current_report(manifest_path,report_path);return report

def current_report(manifest_path=None,report_path=None):
 manifest_path=checked(manifest_path or DEFAULT_MANIFEST,'config');report_path=checked(report_path or DEFAULT_OUTPUT/REPORT_NAME,'build/iop');manifest_raw=manifest_path.read_bytes();validate_manifest(json.loads(manifest_raw));raw=(ROOT/MODULE).read_bytes();original=validate_original(raw);contract=original_contract();report=json.loads(report_path.read_bytes())
 expected={'status':'PASS_MCMAN_COMPLETE_MUTABLE_ECC_INITIALIZED_DATA','manifest':manifest_path.relative_to(ROOT).as_posix(),'manifest_sha256':sha(manifest_raw),'report_path':report_path.relative_to(ROOT).as_posix(),'dependency_hashes':dependency_hashes(),'module':MODULE,'module_sha256':MODULE_SHA,'functions':[],'data_objects':[CLAIM],'original_contract':contract,'semantic_states':semantic_receipt(),'progress':progress(raw,original),'partial_module':(report_path.parent/'module_02.partial.irx').relative_to(ROOT).as_posix(),'partial_module_sha256':MODULE_SHA,'full_file_bytes_equal':True,'whole_module_source_ownership':False,'unmatched_checksum_and_correction_source_count':0,'all_unowned_bytes_and_metadata':'PRESERVATION_EXCLUDED_FROM_SOURCE','historical_iop_compiler_identity':'UNCONFIRMED','general_original_o32_abi':'UNCONFIRMED','public_mutations':False}
 if set(report)!=set(expected)|{'data_native_profiles'}or any(report.get(k)!=v for k,v in expected.items()):raise ValueError('Stale/false/omitted/foreign source/data/contract/state/ownership/dependency report')
 rows=report['data_native_profiles']
 if len(rows)!=2 or [p.get('revision')for p in rows]!=['114','136']:raise ValueError('Unknown/missing/reordered whole native data profiles')
 for row,revision in zip(rows,['114','136']):
  if set(row)!={'revision','profile','compiler_flags','assembler_flags','native_input_hashes','assembly','assembly_sha256','assembly_unchanged','object','object_sha256','whole_object_proof'}:raise ValueError('Unknown native source/profile/ownership fields')
  assembly=report_path.parent/f'mc_ecc_parity_table_{revision}.raw.s';obj=report_path.parent/f'mc_ecc_parity_table_{revision}.o'
  if row.get('profile')!=f'legacy-scalar-leaf-{revision}'or row.get('compiler_flags')!=FLAGS or row.get('assembler_flags')!=AS_FLAGS or row.get('native_input_hashes')!=native_inputs(revision)or row.get('assembly_unchanged')is not True:raise ValueError('Native profile/input provenance changed')
  if row.get('assembly')!=assembly.relative_to(ROOT).as_posix()or row.get('object')!=obj.relative_to(ROOT).as_posix()or row.get('assembly_sha256')!=sha(assembly.read_bytes())or row.get('object_sha256')!=sha(obj.read_bytes()):raise ValueError('Fresh actual assembly/object path/hash changed')
  proof=inspect_object_bytes(obj.read_bytes(),original)
  if proof!=row.get('whole_object_proof'):raise ValueError('Entire current native metadata/data/symbol/section proof changed')
 # Fresh build/tests execute2816 replays. Repeated reads prove identical complete
 # consumed kernel/table bytes, all256 entry values, real operands and native
 # ownership again; no cached unverified code/data or model input is accepted.
 words=json.loads((ROOT/PEER_NATIVE).read_bytes())['independent_original_contract']['whole_kernel']['words']
 if allocated_read(original,0x3b14,116,True)[1]!=struct.pack('<29I',*[int(w,16)for w in words]):raise ValueError('Consumed original kernel opcode identity changed')
 partial=report_path.parent/'module_02.partial.irx'
 if partial.read_bytes()!=raw:raise ValueError('Original unowned code/metadata preservation changed')
 return {**report,'freshness':'CURRENT_WHOLE_MUTABLE_ECC_DATA_BOTH_NATIVE_OBJECTS_COMPLETE_ORIGINAL_CONSUMED_BYTE_IDENTITY_VERIFIED'}

if __name__=='__main__':run()
