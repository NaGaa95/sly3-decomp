"""Separate exact module04 libsd getter build and freshness verifier.

The sole ordinary C leaf owns 16 bytes and its actual HI16/LO16 pair. The
original IRX metadata, remaining code/data, loader relocations and BSS stay
preservation. This never broadens the published module00 zero-relocation tool.
Historical IOP compiler identity and general original O32 ABI are unconfirmed.
"""
import argparse
import json
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT/'tools'))
import common
import iop_build
from common import Elf32
from iop_build import allocated_read, digest, PROFILE_FLAGS, AS_FLAGS, PROFILE_REVISIONS, MEASURED_OBJECT_FLAGS, native_inputs

NAME = 'sceSdGetSpu2IntrHandlerArgument'
SOURCE = 'iop/src/libsd/spu2_argument.c'
SOURCE_SHA = '0b72b271ed4ec7933d6c13ded161d0515a53df5c5122f4db7957c0bc5295dec9'
MODULE = 'disc/irx/module_04.irx'
MODULE_SHA = 'd26a8dcd121ff4ded9c819b72864ea7f4e723932cc2eab1b4f0f1c93faad43ef'
CODE_SHA = '9148799bbaeeee5f462c95d8ea4b8493772e674b44df4340eff1b05ae91eafe5'
PROOF = 'build/iop_research/libsd_getter_proposal.json'
PROOF_SHA = '15371df2852e3b4cf307941a2f721bd3069deef00e5a95a4e3a57faa3d6af305'
PRIMARY = 'iop/references/ps2sdk/libsd/libsd-common.h'
PRIMARY_SHA = '7fbc2ac53a4f6663ecc487ac65ba38c3f2179ceae466dfa7b7f5511e5a127171'
INDEPENDENT = 'build/iop_research/libsd_getter_independent_review.json'
INDEPENDENT_SHA = 'bdffcf20c0767b7adbc6a84e9cf9b97e7171dd416c20c87ac4df4699cefb6f9c'
START, SIZE, GLOBAL, ORDINAL, EXPORT_FIELD = 0x3EF8, 16, 0x5314, 29, 0x88
BASES = [0, 0x1000, 0x3000, 0x17FF0, 0x27FF0, 0xCFFF0]
DEFAULT_MANIFEST = ROOT/'config/iop_libsd_partial.json'
DEFAULT_OUTPUT = ROOT/'build/iop/module_04'
REPORT_NAME = 'partial_iop_report.json'
EXPECTED_FUNCTION = {'name': NAME, 'source': SOURCE, 'source_sha256': SOURCE_SHA,
    'module_offset': START, 'object_offset': 0, 'size': SIZE, 'export_ordinal': ORDINAL,
    'signature': 'void *sceSdGetSpu2IntrHandlerArgument(void)', 'input_registers': ['ra: return address'],
    'output_registers': ['v0: unchanged32-bit opaque pointer'], 'original_code_sha256': CODE_SHA}


def checked_path(relative, prefix):
    path = (ROOT/relative).resolve()
    if not path.is_relative_to(ROOT) or not path.is_relative_to((ROOT/prefix).resolve()):
        raise ValueError('Path escapes the private IOP research domain: '+str(relative))
    return path


def dependency_hashes():
    paths = [Path(__file__).resolve(), Path(common.__file__).resolve(), Path(iop_build.__file__).resolve(),
             ROOT/PROOF, ROOT/INDEPENDENT, ROOT/PRIMARY, ROOT/'iop/references/ps2sdk/libsd/provenance.json',
             ROOT/'iop/licenses/PS2SDK.MIT']
    return {p.relative_to(ROOT).as_posix(): digest(p.read_bytes()) for p in paths}


def validate_manifest(manifest):
    expected = {'schema': 'sly3-iop-libsd-partial-v1', 'module': MODULE, 'module_sha256': MODULE_SHA,
        'profiles': ['legacy-scalar-leaf-114', 'legacy-scalar-leaf-136'],
        'functions': [EXPECTED_FUNCTION], 'symbol_bindings': {'Spu2IntrData': GLOBAL},
        'original_boundary_proof': PROOF, 'original_boundary_proof_sha256': PROOF_SHA,
        'primary_header': PRIMARY, 'primary_header_sha256': PRIMARY_SHA,
        'independent_original_review': INDEPENDENT, 'independent_original_review_sha256': INDEPENDENT_SHA}
    if manifest != expected:
        raise ValueError('Unknown libsd manifest entry, profile, source, bounds, inputs, symbol, proof or ownership')
    source = checked_path(SOURCE, 'iop/src')
    if digest(source.read_bytes()) != SOURCE_SHA:
        raise ValueError('Current source differs from the sole reviewed ordinary C leaf')
    if digest((ROOT/PROOF).read_bytes()) != PROOF_SHA:
        raise ValueError('Original boundary/input proposal proof has changed')
    if digest((ROOT/PRIMARY).read_bytes()) != PRIMARY_SHA:
        raise ValueError('Pinned primary pointer API evidence has changed')
    if digest((ROOT/INDEPENDENT).read_bytes()) != INDEPENDENT_SHA:
        raise ValueError('Independent original/code/input review has changed')
    proof = json.loads((ROOT/PROOF).read_text())
    if (proof.get('status') != 'PASS_PRIVATE_COMPLETE_SOURCE_PROPOSAL_PENDING_PARENT_REVIEW'
        or proof.get('module_sha256') != MODULE_SHA or proof.get('source_sha256') != SOURCE_SHA
        or proof.get('function') != NAME or proof.get('export_ordinal') != ORDINAL
        or proof.get('proposal', {}).get('code_bytes') != SIZE):
        raise ValueError('Proof does not cover the current complete original entry/source/API')
    return source


def original_records(original):
    records = []
    for section in original.sections:
        if section['type'] == 4 and section['size']:
            raise ValueError('Original RELA is unsupported')
        if section['type'] != 9:
            continue
        if section['entsize'] not in (0,8) or section['size']%8 or not 0 <= section['info'] < len(original.sections):
            raise ValueError('Invalid original IRX relocation ownership/format')
        owner = original.sections[section['info']]
        for place, info in struct.iter_unpack('<II', original.section_data(section)):
            if info>>8 or place%4:
                raise ValueError('Original relocation symbol/address domain is not regular IRX')
            resolved_owner,raw = allocated_read(original, place, 4, executable=bool(owner['flags']&4))
            if resolved_owner['index'] != owner['index']:
                raise ValueError('Original relocation field is outside its actual allocated owner')
            records.append({'section':owner['name'], 'module_offset':place, 'type':info&255,
                            'symbol_index':0,'original_word':struct.unpack('<I',raw)[0]})
    return records


def validate_original(original):
    if original.type != 0xFF80 or original.flags != 1 or original.entry != 0xB0:
        raise ValueError('Unknown original regular libsd IRX header cohort')
    owner,body = allocated_read(original,START,SIZE,executable=True)
    if owner['name'] != '.text' or owner['addr'] != 0 or digest(body) != CODE_SHA:
        raise ValueError('Original executable extent/code identity differs')
    if struct.unpack('<4I',body) != (0x3C020000,0x8C425314,0x03E00008,0):
        raise ValueError('Original code does not encode the complete reviewed no-argument pointer getter')
    _,header = allocated_read(original,0,20,executable=True)
    if struct.unpack_from('<I',header)[0] != 0x41C00000 or header[12:20].rstrip(b'\0') != b'libsd':
        raise ValueError('Original export ownership is not libsd')
    _,field = allocated_read(original,EXPORT_FIELD,4,executable=True)
    if struct.unpack('<I',field)[0] != START or EXPORT_FIELD != 20+ORDINAL*4:
        raise ValueError('Original export29 pointer does not name the function entry')
    records = original_records(original)
    functions = [r for r in records if START <= r['module_offset'] < START+SIZE]
    expected = [{'section':'.text','module_offset':START,'type':5,'symbol_index':0,'original_word':0x3C020000},
                {'section':'.text','module_offset':START+4,'type':6,'symbol_index':0,'original_word':0x8C425314}]
    if functions != expected:
        raise ValueError('Missing/extra/reordered original getter HI16/LO16, opcode or addend')
    exports = [r for r in records if r['module_offset'] == EXPORT_FIELD]
    if exports != [{'section':'.text','module_offset':EXPORT_FIELD,'type':2,'symbol_index':0,'original_word':START}]:
        raise ValueError('Original export pointer lacks its genuine R_MIPS32')
    global_owner,global_bytes = allocated_read(original,GLOBAL,4)
    if global_owner['name'] != '.data' or global_owner['flags'] != 3 or global_bytes != bytes(4):
        raise ValueError('Original opaque pointer storage is not the reviewed initialized word')
    return body, functions, exports


def relocate_pair(payload,records,address):
    """Resolve the actual zero-addend pair; never use target instruction words."""
    if not 0 <= address <= 0xFFFFFFFF:
        raise ValueError('Relocated pointer address exceeds the proved32-bit domain')
    if [(r['offset'],r['type'],r['symbol'])for r in records] != [(0,5,'Spu2IntrData'),(4,6,'Spu2IntrData')]:
        raise ValueError('Unknown native relocation pair ownership')
    if len(payload) != SIZE:
        raise ValueError('Unowned native code gap or tail')
    hi,lo = struct.unpack_from('<II',payload)
    if hi != 0x3C020000 or lo != 0x8C420000:
        raise ValueError('Native HI/LO opcode/register or zero addend differs')
    linked = bytearray(payload)
    struct.pack_into('<I',linked,0,(hi&0xFFFF0000)|(((address+0x8000)>>16)&0xFFFF))
    struct.pack_into('<I',linked,4,(lo&0xFFFF0000)|(address&0xFFFF))
    return bytes(linked)


def replay_original_pair(body,records,base):
    """Independent loader arithmetic from both complete original operands."""
    if [(r['module_offset'],r['type'],r['symbol_index'])for r in records] != [(START,5,0),(START+4,6,0)]:
        raise ValueError('Original pair ownership changed')
    hi,lo = struct.unpack_from('<II',body)
    if hi>>26 != 15 or lo>>26 != 35 or ((hi>>16)&31) != 2 or ((lo>>21)&31) != 2 or ((lo>>16)&31) != 2:
        raise ValueError('Original source address opcodes/registers are unsupported')
    signed_low=(lo&0x7FFF)-(lo&0x8000)
    address=((hi&0xFFFF)<<16)+signed_low+base
    if address != GLOBAL+base:
        raise ValueError('Original address pair does not point to actual argument storage')
    result=bytearray(body)
    struct.pack_into('<I',result,0,(hi&0xFFFF0000)|(((address+0x8000)>>16)&0xFFFF))
    struct.pack_into('<I',result,4,(lo&0xFFFF0000)|((lo+base)&0xFFFF))
    return bytes(result)


def inspect_object(elf,original):
    body,original_pair,_ = validate_original(original)
    if elf.type != 1 or elf.flags != MEASURED_OBJECT_FLAGS:
        raise ValueError('Unmeasured native ELF type/ABI flags')
    text = elf.section('.text')
    if text['type'] != 1 or text['flags'] != 6 or text['addr'] != 0 or text['alignment'] != 4 or text['size'] != SIZE:
        raise ValueError('Code section ownership, bounds, address/alignment or permissions differ')
    # Both fresh legacy profiles retain these empty, non-executable sections.
    # Their zero payload does not permit an unmeasured type or permissions.
    for name,kind in (('.data',1),('.bss',8)):
        matches=[s for s in elf.sections if s['name']==name]
        if len(matches)!=1 or tuple(matches[0][key]for key in ('addr','size','type','flags','alignment'))!=(0,0,kind,3,1):
            raise ValueError('Measured empty '+name+' section contract differs')
    for section in elf.sections:
        if section['flags']&2 and (section['name'] not in ('.text','.data','.bss') or (section['name'] != '.text' and section['size'])):
            raise ValueError('Unexpected allocated executable, initialized data or BSS payload')
    payload = elf.section_data(text)
    symbols = elf.symbols()
    functions = [s for s in symbols if s['type'] == 2]
    if len(functions) != 1 or (functions[0]['name'],functions[0]['value'],functions[0]['size'],functions[0]['shndx'],functions[0]['binding'],functions[0]['visibility']) != (NAME,0,SIZE,text['index'],1,0):
        raise ValueError('Every native function must have the sole complete reviewed ownership')
    undefined = [s for s in symbols if s['binding'] and s['shndx'] == 0]
    if len(undefined) != 1 or (undefined[0]['name'],undefined[0]['value'],undefined[0]['size'],undefined[0]['type'],undefined[0]['binding'],undefined[0]['visibility']) != ('Spu2IntrData',0,0,0,1,0):
        raise ValueError('Unowned/extra/defined or incompatible native external symbol')
    for s in symbols:
        if s['shndx'] and s['type'] != 3 and s['name'] not in (NAME,'gcc2_compiled.','__gnu_compiled_c'):
            raise ValueError('Unknown defined code/data symbol')
    by_index={(s['table'],s['index']):s for s in symbols}
    relocation_sections=[s for s in elf.sections if s['type'] in (4,9) and s['size']]
    if len(relocation_sections) != 1:
        raise ValueError('Missing/extra native relocation sections')
    section=relocation_sections[0]
    if section['type'] != 9 or section['name'] != '.rel.text' or section['info'] != text['index'] or section['link'] != undefined[0]['table'] or section['entsize'] != 8 or section['size'] != 16:
        raise ValueError('Unsupported native relocation format/section/symbol table ownership')
    records=[]
    for off,info in struct.iter_unpack('<II',elf.section_data(section)):
        symbol=by_index.get((section['link'],info>>8))
        if symbol != undefined[0]:
            raise ValueError('Native address relocation is not the actual opaque pointer symbol')
        records.append({'offset':off,'type':info&255,'symbol':symbol['name']})
    code=relocate_pair(payload,records,GLOBAL)
    if code != body:
        raise ValueError('Whole native16-byte function differs after actual relocation')
    cases=[]
    for base in BASES:
        native=relocate_pair(payload,records,GLOBAL+base)
        original_bytes=replay_original_pair(body,original_pair,base)
        if native != original_bytes:
            raise ValueError('Native whole relocation and original IRX loader replay disagree')
        cases.append({'base':base,'full_bytes_sha256':digest(native),'whole16_bytes_equal':True})
    operands=[{**r,'module_offset':START+r['offset'],'expected_module_symbol':GLOBAL,
        'object_word':f'0x{struct.unpack_from("<I",payload,r["offset"])[0]:08X}',
        'original_word':f'0x{struct.unpack_from("<I",body,r["offset"])[0]:08X}'}for r in records]
    return code, {'every_allocated_section_verified':True,
        'allocated_sections':[{'name':'.text','type':1,'flags':6,'size':SIZE,'linked_sha256':digest(code)}],
        'initialized_nonexecutable_sections':[],'emitted_BSS':[],'owned_function':NAME,
        'actual_relocation_count':2,'raw_relocation_operands':operands,'IRX_load_base_cases':cases}


def load_original():
    raw=(ROOT/MODULE).read_bytes()
    if digest(raw) != MODULE_SHA:
        raise ValueError('Original complete module identity changed')
    original=Elf32(raw)
    validate_original(original)
    return raw,original


def progress(raw,original):
    return {'verified_source_functions':1,'verified_source_code_bytes':SIZE,'verified_source_initialized_data_bytes':0,
        'preserved_original_file_bytes_excluded_from_source':len(raw)-SIZE,'original_file_size':len(raw),
        'original_text_bytes_including_tables_and_stubs':original.section('.text')['size']}


def run(manifest_path,output):
    manifest_path=Path(manifest_path);output=Path(output).resolve()
    if not output.is_relative_to((ROOT/'build/iop/module_04').resolve()):
        raise ValueError('Libsd private outputs must stay below build/iop/module_04')
    output.mkdir(parents=True,exist_ok=True)
    report_path=output/REPORT_NAME
    report_path.write_text(json.dumps({'status':'UNVERIFIED_CURRENT_BUILD','progress':{'verified_source_functions':0,'verified_source_code_bytes':0},'previous_success_must_not_count':True},indent=2)+'\n')
    manifest_raw=manifest_path.read_bytes();manifest=json.loads(manifest_raw)
    source=validate_manifest(manifest)
    deps=dependency_hashes()
    original_raw,original=load_original()
    native=[];code=None
    assembler=ROOT/'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe'
    for profile in manifest['profiles']:
        revision=PROFILE_REVISIONS[profile]
        directory=ROOT/f'tools/third_party/ee-gcc2.95.3-{revision}'
        library=directory/'lib/gcc-lib/ee/2.95.3'
        compiler=directory/'bin/ee-gcc.exe'
        raw=output/f'spu2_argument_{revision}.raw.s';obj=output/f'spu2_argument_{revision}.o'
        inputs=native_inputs(revision)
        commands=[[str(compiler),'-S','-x','c',*PROFILE_FLAGS,'-B'+library.as_posix()+'/',source.as_posix(),'-o',raw.as_posix()],
                  [str(assembler),*AS_FLAGS,'-o',obj.as_posix(),raw.as_posix()]]
        for command in commands:
            completed=subprocess.run(command,cwd=ROOT,capture_output=True,text=True,timeout=60)
            if completed.returncode:
                raise RuntimeError(json.dumps({'command':command,'exit':completed.returncode,'stdout':completed.stdout,'stderr':completed.stderr}))
        payload,proof=inspect_object(Elf32(obj.read_bytes()),original)
        if code is not None and payload != code:
            raise ValueError('The two unchanged native scalar profiles disagree')
        if inputs != native_inputs(revision) or digest(source.read_bytes()) != SOURCE_SHA or deps != dependency_hashes():
            raise ValueError('Source/tool/compiler/dependency changed during compilation')
        code=payload
        native.append({'profile':profile,'compiler_flags':PROFILE_FLAGS,'assembler_flags':AS_FLAGS,
            'native_input_hashes':inputs,'assembly':raw.relative_to(ROOT).as_posix(),'assembly_sha256':digest(raw.read_bytes()),
            'assembly_unchanged':True,'object':obj.relative_to(ROOT).as_posix(),'object_sha256':digest(obj.read_bytes()),'whole_object_proof':proof})
    owner,_=allocated_read(original,START,SIZE,executable=True)
    file_offset=owner['offset']+START-owner['addr'];rebuilt=bytearray(original_raw)
    rebuilt[file_offset:file_offset+SIZE]=code
    rebuilt=bytes(rebuilt)
    if rebuilt != original_raw:
        raise ValueError('Full private partial module differs from original')
    partial=output/'module_04.partial.irx';partial.write_bytes(rebuilt)
    report={'status':'PASS_SEPARATE_LIBSD_PARTIAL_SOURCE_BUILD','manifest':manifest_path.resolve().relative_to(ROOT).as_posix(),
        'manifest_sha256':digest(manifest_raw),'dependency_hashes':deps,'source':SOURCE,'source_sha256':SOURCE_SHA,
        'module':MODULE,'module_sha256':digest(original_raw),'partial_module':partial.relative_to(ROOT).as_posix(),
        'partial_module_sha256':digest(rebuilt),'full_file_bytes_equal':True,
        'functions':[{**EXPECTED_FUNCTION,'status':'LINKED_EXACT','source_code_bytes':SIZE,'actual_relocations':2,'initialized_data_bytes':0}],
        'native_profiles':native,'progress':progress(original_raw,original),
        'original_source_ownership':{'module_offset':START,'file_offset':file_offset,'bytes':SIZE,'section':owner['name']},
        'all_other_original_bytes':'PRESERVATION_EXCLUDED_FROM_SOURCE_PROGRESS',
        'original_metadata_exports_imports_relocations_and_BSS':'PRESERVED_ORIGINAL_NOT_RECONSTRUCTED',
        'historical_iop_compiler_identity':'UNCONFIRMED','general_original_o32_abi':'UNCONFIRMED',
        'native_object_header_limitation':'Native GNU output retains EE/R5900 flags0x20921000; only complete MIPS1-compatible zero-frame pointer code and its pair are proved. Original IRX header is preservation.',
        'custom_989snd_spiop_contracts':'UNRESOLVED_AND_EXCLUDED','main_ee_source_index_compiler_and_progress_changed':False}
    report_path.write_text(json.dumps(report,indent=2)+'\n')
    print('PASS separate libsd getter: 1 function /16 code bytes /2 actual relocations /0 initialized data; original remaining28645 file bytes are preservation.')
    return report


def current_report(manifest_path=None,report_path=None):
    """Read-only freshness plus complete native reinspection; no compilation."""
    manifest_path=Path(manifest_path)if manifest_path is not None else DEFAULT_MANIFEST
    report_path=Path(report_path)if report_path is not None else DEFAULT_OUTPUT/REPORT_NAME
    manifest_raw=manifest_path.read_bytes();manifest=json.loads(manifest_raw)
    validate_manifest(manifest)
    report=json.loads(report_path.read_text())
    if report.get('status') != 'PASS_SEPARATE_LIBSD_PARTIAL_SOURCE_BUILD' or report.get('manifest_sha256') != digest(manifest_raw) or report.get('dependency_hashes') != dependency_hashes():
        raise ValueError('Libsd source proof is unverified or stale for current manifest/dependencies')
    original_raw,original=load_original()
    if report.get('module') != MODULE or report.get('module_sha256') != MODULE_SHA or report.get('source') != SOURCE or report.get('source_sha256') != SOURCE_SHA:
        raise ValueError('Source/original module report ownership or hash is stale')
    if report.get('manifest')!=manifest_path.resolve().relative_to(ROOT).as_posix():
        raise ValueError('Recorded manifest provenance differs from the actual resolved manifest')
    owner,_=allocated_read(original,START,SIZE,executable=True)
    expected_ownership={'module_offset':START,'file_offset':owner['offset']+START-owner['addr'],'bytes':SIZE,'section':owner['name']}
    if report.get('original_source_ownership')!=expected_ownership:
        raise ValueError('Recorded original ownership differs from the complete actual allocated span')
    expected_function={**EXPECTED_FUNCTION,'status':'LINKED_EXACT','source_code_bytes':SIZE,'actual_relocations':2,'initialized_data_bytes':0}
    if report.get('functions') != [expected_function]:
        raise ValueError('Report function/input/symbol/boundary ownership changed')
    profiles=report.get('native_profiles',[])
    if [r.get('profile')for r in profiles] != manifest['profiles']:
        raise ValueError('Native complete profile cohort is missing, duplicated or unknown')
    for row in profiles:
        revision=PROFILE_REVISIONS[row['profile']]
        if row.get('compiler_flags') != PROFILE_FLAGS or row.get('assembler_flags') != AS_FLAGS or row.get('native_input_hashes') != native_inputs(revision) or row.get('assembly_unchanged') is not True:
            raise ValueError('Native compiler/assembler/options/source assembly contract changed')
        raw=checked_path(row['assembly'],'build/iop/module_04');obj=checked_path(row['object'],'build/iop/module_04')
        raw_bytes=raw.read_bytes();obj_bytes=obj.read_bytes()
        if digest(raw_bytes) != row.get('assembly_sha256') or digest(obj_bytes) != row.get('object_sha256'):
            raise ValueError('Raw assembly or native object is stale')
        _,proof=inspect_object(Elf32(obj_bytes),original)
        if proof != row.get('whole_object_proof'):
            raise ValueError('Current whole native code/data/relocation proof differs')
    partial=checked_path(report['partial_module'],'build/iop/module_04').read_bytes()
    if partial != original_raw or digest(partial) != report.get('partial_module_sha256') or report.get('full_file_bytes_equal') is not True:
        raise ValueError('Partial module bytes are stale or altered')
    if report.get('progress') != progress(original_raw,original):
        raise ValueError('Report counts exceed the complete verified private source ownership')
    return {**report,'freshness':'CURRENT_MANIFEST_SOURCE_PROOF_MODULE_NATIVE_OBJECTS_AND_ALL_SECTIONS_VERIFIED'}


def main():
    parser=argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--manifest',type=Path,default=DEFAULT_MANIFEST)
    parser.add_argument('--output',type=Path,default=DEFAULT_OUTPUT)
    args=parser.parse_args()
    run(args.manifest,args.output)


if __name__=='__main__':main()
