"""Separate five-function no-split source verifier, never an entire-module owner.

Only the pinned source claims are counted. Existing module00/module04 source
ranges remain reserved to the public packages; all original metadata and other
bytes remain preservation. Both native revisions use a legitimate extra
-mno-split-addresses option, untouched GNU assembly and complete real HI/LO
proof. Historical compiler identity and the general original O32 ABI remain
unconfirmed. This verifier never broadens either pre-existing IOP verifier or the EE compiler.
"""
import argparse
import json
import struct
import subprocess
import sys
from pathlib import Path

ROOT=next(p for p in Path(__file__).resolve().parents if (p/'config/target.json').is_file())
sys.path.insert(0,str(ROOT/'tools'))
import common
import iop_build
from common import Elf32
from iop_build import allocated_read,digest,native_inputs

PROPOSAL='build/iop_research/publication/final_source_proof.json'
PROPOSAL_SHA='9f3cce19e4ca45f685b696542b0065184de974e191d3c255215101cb099594ad'
INDEPENDENT='build/iop_research/scalar_no_split_independent_review.json'
INDEPENDENT_SHA='f0e6861062c41ef86deb2ac9cab33802162dbbec81fc0ea6fa493f8ccd993a26'
PUBLIC_MANIFESTS=['config/iop_partial.json','config/iop_libsd_partial.json']
BASE_FLAGS=['-Os','-G0','-mips1','-mgp32','-mfp32','-mlong32','-mcpu=r3000','-malign-functions=2']
FLAGS=BASE_FLAGS+['-mno-split-addresses']
AS_FLAGS=['-G0','-mips1','-mabi=32','-O0']
PROFILES={'legacy-scalar-nosplit-114':'114','legacy-scalar-nosplit-136':'136'}
BASES=[0,0x1000,0x3000,0x17FF0,0x27FF0,0xCFFF0]
ROOT_OUTPUT=ROOT/'build/iop/nosplit'
DEFAULT_MANIFEST=ROOT/'config/iop_nosplit_partial.json'
DEFAULT_OUTPUT=ROOT_OUTPUT
REPORT='partial_iop_report.json'
EXPECTED_IDENTITY=[('module_04.irx','sceSdGetTransIntrHandlerArgument',0x3E98,24,28),
    ('module_00.irx','sio2_mtap_change_slot_set',0xB14,16,53),
    ('module_00.irx','sio2_mtap_get_slot_max_set',0xB24,16,54),
    ('module_00.irx','sio2_mtap_get_slot_max2_set',0xB34,16,55),
    ('module_00.irx','sio2_mtap_update_slots_set',0xB44,16,56)]


def checked_path(relative,prefix):
    path=(ROOT/relative).resolve()
    if not path.is_relative_to(ROOT)or not path.is_relative_to((ROOT/prefix).resolve()):
        raise ValueError('Path escapes private no-split ownership: '+str(relative))
    return path


def proposal_records():
    raw=(ROOT/PROPOSAL).read_bytes()
    if digest(raw)!=PROPOSAL_SHA:
        raise ValueError('Pinned five-function source/entry/input proposal has changed')
    proposal=json.loads(raw)
    functions=proposal.get('functions',[])
    if [(f['module'],f['name'],f['start'],f['size'],f['ordinal'])for f in functions]!=EXPECTED_IDENTITY:
        raise ValueError('Proposal is not the narrowly reviewed five-function cohort')
    return functions


def expected_claims():
    return [{'name':f['name'],'module':'disc/irx/'+f['module'],'module_sha256':f['module_sha256'],
        'source':f['source'],'source_sha256':f['source_sha256'],'module_offset':f['start'],'object_offset':0,
        'size':f['size'],'export_ordinal':f['ordinal'],'original_code_sha256':f['original_code_sha256'],
        'symbol_bindings':f['binding'],'GP_inputs':f['GP_inputs'],'GP_outputs':f['GP_outputs'],'FPR_inputs':[],'stack_bytes':0}
        for f in proposal_records()]


def expected_manifest():
    return {'schema':'sly3-iop-nosplit-v1','profiles':list(PROFILES),
        'proposal':PROPOSAL,'proposal_sha256':PROPOSAL_SHA,'functions':expected_claims(),
        'independent_original_review':INDEPENDENT,'independent_original_review_sha256':INDEPENDENT_SHA,
        'public_reservation_manifests':PUBLIC_MANIFESTS}


def public_reservations():
    rows=[]
    for relative in PUBLIC_MANIFESTS:
        path=ROOT/relative;manifest=json.loads(path.read_text())
        module=manifest['module'];module_hash=manifest['module_sha256']
        if digest((ROOT/module).read_bytes())!=module_hash:
            raise ValueError('Published reservation original identity differs')
        for f in manifest['functions']:
            rows.append({'owner_manifest':relative,'module':module,'module_sha256':module_hash,
                'name':f['name'],'module_offset':f['module_offset'],'size':f['size']})
    if len(rows)!=13 or sum(r['size']for r in rows)!=252:
        raise ValueError('Published reservation baseline changed; requires new independent integration review')
    return rows


def validate_nonoverlap(claims,reserved):
    identities=set()
    for f in claims:
        key=(f['module'],f['name'])
        if key in identities:raise ValueError('Duplicate source function ownership')
        identities.add(key)
        a,n=f['module_offset'],f['size']
        if a<0 or a%4 or n<=0 or n%4 or a+n>0x100000000:
            raise ValueError('Invalid source code span')
    all_ranges=[(f,'new')for f in claims]+[(f,'public')for f in reserved]
    for i,(f,owner)in enumerate(all_ranges):
        for g,other in all_ranges[i+1:]:
            if f['module']!=g['module']:continue
            if f['module_sha256']!=g['module_sha256']:
                raise ValueError('Same module path has inconsistent original identities')
            if f['module_offset']<g['module_offset']+g['size']and g['module_offset']<f['module_offset']+f['size']:
                raise ValueError('Code source ownership overlaps within an original module')


def validate_manifest(manifest):
    if manifest!=expected_manifest():
        raise ValueError('Unknown source/input/return/symbol/module/entry/bounds/profile/proof/manifest contract')
    if iop_build.PROFILE_FLAGS!=BASE_FLAGS or iop_build.AS_FLAGS!=AS_FLAGS:
        raise ValueError('Existing scalar profile changed; no implicit broadening is permitted')
    review=(ROOT/INDEPENDENT).read_bytes()
    if digest(review)!=INDEPENDENT_SHA or json.loads(review).get('status')!='PASS_PRIVATE_FIVE_88_BYTE_SCALAR_NO_SPLIT_SOURCE_AND_ORIGINAL_CONTRACTS':
        raise ValueError('Independent original entry/input/boundary review changed')
    functions=manifest['functions'];reserved=public_reservations()
    validate_nonoverlap(functions,reserved)
    for f in functions:
        path=checked_path(f['source'],'iop/src')
        if path.suffix!='.c'or digest(path.read_bytes())!=f['source_sha256']:
            raise ValueError('Source differs from the exact pinned ordinary C function')
    return functions,reserved


def dependencies():
    paths=[Path(__file__).resolve(),Path(common.__file__).resolve(),Path(iop_build.__file__).resolve(),ROOT/PROPOSAL,ROOT/INDEPENDENT,
        *(ROOT/p for p in PUBLIC_MANIFESTS),ROOT/'tools/iop_libsd_build.py',
        ROOT/'iop/references/ps2sdk/libsd/libsd-common.h',
        ROOT/'iop/references/ps2sdk/sio2man/rsio2man.h',
        ROOT/'iop/references/ps2sdk/sio2man/xsio2man.h',
        ROOT/'iop/references/ps2sdk/LICENSE']
    return {p.relative_to(ROOT).as_posix():digest(p.read_bytes())for p in paths}


def original_relocations(elf):
    records=[]
    for s in elf.sections:
        if s['type']==4 and s['size']:raise ValueError('Original RELA is not regular IRX')
        if s['type']!=9:continue
        if s['size']%8 or s['entsize']not in(0,8)or not 0<=s['info']<len(elf.sections):
            raise ValueError('Original IRX relocation section/format differs')
        owner=elf.sections[s['info']]
        for address,info in struct.iter_unpack('<II',elf.section_data(s)):
            if address%4 or info>>8:raise ValueError('Original relocation is not module-relative with symbol0')
            actual,raw=allocated_read(elf,address,4,executable=bool(owner['flags']&4))
            if actual['index']!=owner['index']:raise ValueError('Original relocation has wrong allocated owner')
            records.append({'module_offset':address,'section':owner['name'],'type':info&255,'symbol_index':0,
                'word':struct.unpack('<I',raw)[0]})
    return records


def shape(f):
    if f['module'].endswith('module_04.irx'):
        return {'high':4,'low':12,'symbol':'TransferRecords','addend':4,'hi_word':0x3C020000,'lo_word':0x8C420004,
            'global_address':0x5328,'export_field':0x84,'library':b'libsd','export_header':0}
    ordinal=f['export_ordinal']
    return {'high':0,'low':4,'symbol':'Data','addend':0,'hi_word':0x3C010000,'lo_word':0xAC240000,
        'global_address':0xFDC+(ordinal-53)*4,'export_field':0xC60+20+ordinal*4,'library':b'sio2man','export_header':0xC60}


def validate_original(elf,f):
    if elf.type!=0xFF80 or elf.flags!=1:raise ValueError('Original is not the pinned regular IRX cohort')
    a,n=f['module_offset'],f['size'];owner,code=allocated_read(elf,a,n,True);s=shape(f)
    if owner['name']!='.text'or owner['addr']!=0 or digest(code)!=f['original_code_sha256']:
        raise ValueError('Original full function span/hash differs')
    if struct.unpack_from('<II',code,n-8)!=(0x03E00008,0):
        raise ValueError('Original entry is not the complete zero-frame scalar leaf')
    records=original_relocations(elf)
    actual=[r for r in records if a<=r['module_offset']<a+n]
    expected=[{'module_offset':a+s['high'],'section':'.text','type':5,'symbol_index':0,
        'word':s['hi_word']}, {'module_offset':a+s['low'],'section':'.text','type':6,'symbol_index':0,
        'word':(s['lo_word']&0xFFFF0000)|(s['global_address']+s['addend'])}]
    if actual!=expected:raise ValueError('Original HI/LO pair, order, field, opcode/register or addend differs')
    _,header=allocated_read(elf,s['export_header'],20,True)
    if struct.unpack_from('<I',header)[0]!=0x41C00000 or header[12:20].rstrip(b'\0')!=s['library']:
        raise ValueError('Original export library/header ownership differs')
    _,pointer=allocated_read(elf,s['export_field'],4,True)
    if struct.unpack('<I',pointer)[0]!=a:raise ValueError('Original export points outside the exact entry')
    export=[r for r in records if r['module_offset']==s['export_field']]
    if export!=[{'module_offset':s['export_field'],'section':'.text','type':2,'symbol_index':0,'word':a}]:
        raise ValueError('Original export lacks its real R_MIPS32')
    if f['symbol_bindings']!={s['symbol']:s['global_address']}:
        raise ValueError('Symbol does not denote the original actual storage')
    if s['symbol']=='TransferRecords':
        storage,data=allocated_read(elf,s['global_address'],16)
        if storage['name']!='.data' or storage['flags']!=3 or struct.unpack('<4I',data)!=(0,0,1,0):
            raise ValueError('Original transfer records are not the actual preserved initialized storage')
    else:
        storage=[sec for sec in elf.sections if sec['flags']&2 and sec['type']==8 and sec['addr']<=s['global_address'] and s['global_address']+4<=sec['addr']+sec['size']]
        if len(storage)!=1 or storage[0]['name']!='.bss' or storage[0]['flags']!=3:
            raise ValueError('Callback symbol is not the actual original BSS word')
    ownership={'module_offset':a,'file_offset':owner['offset']+a-owner['addr'],'size':n,'section':'.text'}
    return code,actual,ownership


def native_records(elf,f):
    s=shape(f);text=elf.section('.text');symbols=elf.symbols()
    funcs=[sym for sym in symbols if sym['type']==2]
    if len(funcs)!=1 or tuple(funcs[0][k]for k in('name','value','size','shndx','binding','visibility'))!=(f['name'],0,f['size'],text['index'],1,0):
        raise ValueError('Native function has hidden/extra/incomplete ownership')
    extern=[sym for sym in symbols if sym['binding']and sym['shndx']==0]
    if len(extern)!=1 or tuple(extern[0][k]for k in('name','value','size','type','binding','visibility'))!=(s['symbol'],0,0,0,1,0):
        raise ValueError('Native external symbol ownership differs')
    for sym in symbols:
        if sym['shndx']and sym['type']!=3 and sym['name']not in(f['name'],'gcc2_compiled.','__gnu_compiled_c'):
            raise ValueError('Unowned defined code/data symbol')
        if sym['name']in('gcc2_compiled.','__gnu_compiled_c')and tuple(sym[k]for k in('value','size','type','binding','visibility','shndx'))!=(0,0,0,0,0,text['index']):
            raise ValueError('Compiler marker is not the measured local zero-sized text label')
    rel=[sec for sec in elf.sections if sec['type']in(4,9)and sec['size']]
    if len(rel)!=1:raise ValueError('Missing or extra native relocation section')
    rel=rel[0]
    if tuple(rel[k]for k in('name','type','flags','addr','alignment','size','entsize','info','link'))!=('.rel.text',9,0,0,4,16,8,text['index'],extern[0]['table']):
        raise ValueError('Native relocation format/code/symbol table ownership differs')
    by_index={(sym['table'],sym['index']):sym for sym in symbols};records=[]
    for offset,info in struct.iter_unpack('<II',elf.section_data(rel)):
        if by_index.get((rel['link'],info>>8))!=extern[0]:raise ValueError('Relocation references an unowned source symbol')
        records.append({'offset':offset,'type':info&255,'symbol':s['symbol']})
    if records!=[{'offset':s['high'],'type':5,'symbol':s['symbol']},{'offset':s['low'],'type':6,'symbol':s['symbol']}]:
        raise ValueError('Native HI/LO pair field/type/order differs')
    return records


def relocate_native(payload,f,records,base):
    s=shape(f)
    if not isinstance(base,int)or not 0<=base<=0xFFFFFFFF:raise ValueError('Invalid32-bit module load base')
    expected=[{'offset':s['high'],'type':5,'symbol':s['symbol']},{'offset':s['low'],'type':6,'symbol':s['symbol']}]
    if records!=expected or len(payload)!=f['size']:raise ValueError('Unknown native pair or code range')
    hi=struct.unpack_from('<I',payload,s['high'])[0];lo=struct.unpack_from('<I',payload,s['low'])[0]
    if hi!=s['hi_word']or lo!=s['lo_word']:raise ValueError('Native actual opcode/register or source addend differs')
    addend=((hi&65535)<<16)+((lo&0x7FFF)-(lo&0x8000))
    if addend!=s['addend']:raise ValueError('Native source addend is not independently proved')
    address=s['global_address']+base+addend
    if not 0<=address<=0xFFFFFFFF:raise ValueError('Pointer is outside32-bit module address domain')
    out=bytearray(payload)
    struct.pack_into('<I',out,s['high'],(hi&0xFFFF0000)|(((address+0x8000)>>16)&65535))
    struct.pack_into('<I',out,s['low'],(lo&0xFFFF0000)|(address&65535))
    return bytes(out)


def replay_original(code,records,f,base):
    s=shape(f);a=f['module_offset']
    if not isinstance(base,int)or not 0<=base<=0xFFFFFFFF or len(code)!=f['size']:
        raise ValueError('Invalid original loader base or complete code extent')
    if [(r['module_offset'],r['type'],r['symbol_index'])for r in records]!=[(a+s['high'],5,0),(a+s['low'],6,0)]:
        raise ValueError('Original pair order/address/symbol domain differs')
    hi=struct.unpack_from('<I',code,s['high'])[0];lo=struct.unpack_from('<I',code,s['low'])[0]
    if [r.get('word')for r in records]!=[hi,lo]or any(r.get('section')!='.text'for r in records):
        raise ValueError('Original pair receipt does not describe actual allocated instruction operands')
    before=((hi&65535)<<16)+((lo&0x7FFF)-(lo&0x8000))
    if before!=s['global_address']+s['addend']or(hi&0xFFFF0000)!=(s['hi_word']&0xFFFF0000)or(lo&0xFFFF0000)!=(s['lo_word']&0xFFFF0000):
        raise ValueError('Original actual address/operand differs')
    address=before+base
    if not 0<=address<=0xFFFFFFFF:raise ValueError('Original pointer outside32-bit module domain')
    out=bytearray(code)
    struct.pack_into('<I',out,s['high'],(hi&0xFFFF0000)|(((address+0x8000)>>16)&65535))
    struct.pack_into('<I',out,s['low'],(lo&0xFFFF0000)|((lo+base)&65535))
    return bytes(out)


def inspect_object(elf,f,original):
    if elf.type!=1 or elf.flags!=0x20921000 or elf.entry!=0 or elf.phnum!=0:raise ValueError('Object is not the measured native scalar profile')
    code,orig_records,ownership=validate_original(original,f)
    texts=[sec for sec in elf.sections if sec['name']=='.text']
    if len(texts)!=1:raise ValueError('Missing or duplicate complete native code ownership')
    text=texts[0]
    if tuple(text[k]for k in('type','flags','addr','alignment','size'))!=(1,6,0,4,f['size']):
        raise ValueError('Native full code section has wrong extent/permissions/alignment/address')
    for name,kind in(('.data',1),('.bss',8)):
        secs=[sec for sec in elf.sections if sec['name']==name]
        if len(secs)!=1 or tuple(secs[0][k]for k in('addr','size','type','flags','alignment'))!=(0,0,kind,3,1):
            raise ValueError('Measured empty '+name+' contract differs')
    if any(sec['flags']&2 and(sec['name']not in('.text','.data','.bss')or(sec['name']!='.text'and sec['size']))for sec in elf.sections):
        raise ValueError('Unknown allocated code, initialized data or BSS section')
    records=native_records(elf,f);payload=elf.section_data(text)
    linked=relocate_native(payload,f,records,0)
    if linked!=code:raise ValueError('Every native instruction byte must match after actual relocation')
    cases=[]
    for base in BASES:
        native=relocate_native(payload,f,records,base);expected=replay_original(code,orig_records,f,base)
        if native!=expected:raise ValueError('Full native and original IRX signed-carry replay disagree')
        cases.append({'base':base,'whole_code_sha256':digest(native),'whole_code_matches_original_loader':True})
    s=shape(f);operands=[{**r,'object_word':f'0x{struct.unpack_from("<I",payload,r["offset"])[0]:08X}',
        'original_word':f'0x{struct.unpack_from("<I",code,r["offset"])[0]:08X}',
        'actual_symbol_address':s['global_address'],'source_addend':s['addend']}for r in records]
    proof={'status':'WHOLE_NATIVE_CODE_AND_EVERY_ALLOCATED_SECTION_VERIFIED','code_bytes':f['size'],
        'function':f['name'],'allocated_sections':[{'name':'.text','type':1,'flags':6,'bytes':f['size'],'linked_sha256':digest(linked)}],
        'initialized_nonexecutable_sections':[],'emitted_BSS':[],'actual_relocation_count':2,
        'raw_actual_operands':operands,'original_source_ownership':ownership,'signed_carry_replays':cases}
    return linked,proof


def pinned_native(f,revision):
    proposal=next(p for p in proposal_records()if p['name']==f['name'])
    return next(p for p in proposal['native_profiles']if p['revision']==revision)


def validate_native_receipt(f,revision,assembly,obj,inputs):
    pinned=pinned_native(f,revision)
    if inputs!=pinned['native_input_hashes'] or digest(assembly)!=pinned['raw_assembly_sha256'] or digest(obj)!=pinned['object_sha256']:
        raise ValueError('Native inputs, untouched compiler assembly or complete object differ from independent frozen cohort')


def load_modules(functions):
    result={}
    for f in functions:
        relative=f['module']
        if relative in result:continue
        path=checked_path(relative,'disc/irx');raw=path.read_bytes()
        if digest(raw)!=f['module_sha256']:raise ValueError('Original module hash differs')
        result[relative]=(raw,Elf32(raw))
    return result


def expected_progress(functions):
    return {'verified_source_functions':len(functions),'verified_source_code_bytes':sum(f['size']for f in functions),
        'verified_source_initialized_data_bytes':0,'whole_module_ownership_claims':0,'component_source_claims_only':True}


def expected_limitations():
    return {'historical_original_compiler':'UNCONFIRMED','general_original_O32_ABI':'UNCONFIRMED',
        'native_header_note':'Measured native flags0x20921000 retain an EE tag; only exact MIPS1 scalar bodies are proved. All original IRX headers are preservation.',
        'custom989snd_spiop_contracts':'UNRESOLVED_AND_NOT_ADMITTED','public_source_manifests_profiles_guards_and_registry_changed':False}


def run(manifest_path=None,output=None):
    manifest_path=Path(manifest_path)if manifest_path is not None else DEFAULT_MANIFEST
    output=(Path(output)if output is not None else DEFAULT_OUTPUT).resolve()
    if not output.is_relative_to(ROOT_OUTPUT.resolve()):raise ValueError('Outputs escape private no-split build tree')
    output.mkdir(parents=True,exist_ok=True);rp=output/REPORT
    rp.write_text(json.dumps({'status':'UNVERIFIED_CURRENT_BUILD','progress':{'verified_source_functions':0,'verified_source_code_bytes':0}},indent=2)+'\n')
    manifest_raw=manifest_path.read_bytes();manifest=json.loads(manifest_raw);functions,reserved=validate_manifest(manifest)
    dep=dependencies();modules=load_modules(functions);rebuilt={name:bytearray(raw)for name,(raw,elf)in modules.items()}
    native=[];assembler=ROOT/'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe'
    for fi,f in enumerate(functions):
        source=ROOT/f['source'];original=modules[f['module']][1];profiles=[];code=None
        for profile,revision in PROFILES.items():
            directory=ROOT/f'tools/third_party/ee-gcc2.95.3-{revision}';library=directory/'lib/gcc-lib/ee/2.95.3';compiler=directory/'bin/ee-gcc.exe'
            raw=output/f'{fi}_{revision}.raw.s';obj=output/f'{fi}_{revision}.o';inputs=native_inputs(revision)
            commands=[[str(compiler),'-S','-x','c',*FLAGS,'-B'+library.as_posix()+'/',source.as_posix(),'-o',raw.as_posix()],
                [str(assembler),*AS_FLAGS,'-o',obj.as_posix(),raw.as_posix()]]
            for command in commands:
                completed=subprocess.run(command,cwd=ROOT,capture_output=True,text=True,timeout=60)
                if completed.returncode:raise RuntimeError(json.dumps({'command':command,'stdout':completed.stdout,'stderr':completed.stderr}))
            actual,proof=inspect_object(Elf32(obj.read_bytes()),f,original)
            validate_native_receipt(f,revision,raw.read_bytes(),obj.read_bytes(),inputs)
            if code is not None and code!=actual:raise ValueError('Independent compiler revisions disagree')
            if inputs!=native_inputs(revision)or dep!=dependencies()or digest(source.read_bytes())!=f['source_sha256']:
                raise ValueError('Source/dependencies/native inputs changed during compilation')
            code=actual
            profiles.append({'profile':profile,'compiler_flags':FLAGS,'assembler_flags':AS_FLAGS,'native_input_hashes':inputs,
                'assembly':raw.relative_to(ROOT).as_posix(),'assembly_sha256':digest(raw.read_bytes()),'assembly_untouched':True,
                'object':obj.relative_to(ROOT).as_posix(),'object_sha256':digest(obj.read_bytes()),'complete_proof':proof})
        _,_,ownership=validate_original(original,f);offset=ownership['file_offset']
        rebuilt[f['module']][offset:offset+f['size']]=code
        native.append({'claim':f,'profiles':profiles})
    components=[]
    for relative,(original_raw,elf)in modules.items():
        partial=bytes(rebuilt[relative])
        if partial!=original_raw:raise ValueError('Combined new disjoint ranges change the original partial module')
        path=output/(Path(relative).stem+'.partial.irx');path.write_bytes(partial)
        owned=[f for f in functions if f['module']==relative];public=[r for r in reserved if r['module']==relative]
        components.append({'module':relative,'original_sha256':digest(original_raw),'partial_module':path.relative_to(ROOT).as_posix(),
            'partial_sha256':digest(partial),'source_claims':[{'name':f['name'],'module_offset':f['module_offset'],'size':f['size']}for f in owned],
            'new_code_bytes':sum(f['size']for f in owned),'existing_public_source_ranges_reserved_not_counted':public,
            'whole_module_owned':False,'original_metadata_and_all_other_bytes':'PRESERVATION_NOT_SOURCE',
            'original_file_bytes':len(original_raw),'original_file_bytes_outside_new_claims':len(original_raw)-sum(f['size']for f in owned)})
    if manifest_path.read_bytes()!=manifest_raw or dependencies()!=dep:
        raise ValueError('Manifest/source dependencies changed during final partial-module assembly')
    report={'status':'PASS_SEPARATE_NOSPLIT_FUNCTION_SOURCE_CLAIMS','manifest':manifest_path.resolve().relative_to(ROOT).as_posix(),
        'manifest_sha256':digest(manifest_raw),'dependency_hashes':dep,'functions':functions,'native_objects':native,
        'module_artifacts_are_identity_observations_not_owners':components,'published_reservations':reserved,
        'progress':expected_progress(functions),**expected_limitations()}
    rp.write_text(json.dumps(report,indent=2)+'\n')
    print('PASS PRIVATE no-split: five disjoint source claims /88 code bytes /10actual relocations /zero initialized data; no duplicate whole-module ownership.')
    return report


def current_report(manifest_path=None,report_path=None):
    """Read-only reinspection; rejects stale source/proof/object/report metadata."""
    manifest_path=Path(manifest_path)if manifest_path is not None else DEFAULT_MANIFEST
    report_path=Path(report_path)if report_path is not None else DEFAULT_OUTPUT/REPORT
    manifest_raw=manifest_path.read_bytes();manifest=json.loads(manifest_raw);functions,reserved=validate_manifest(manifest)
    report=json.loads(report_path.read_text())
    if report.get('status')!='PASS_SEPARATE_NOSPLIT_FUNCTION_SOURCE_CLAIMS' or report.get('manifest')!=manifest_path.resolve().relative_to(ROOT).as_posix()or report.get('manifest_sha256')!=digest(manifest_raw)or report.get('dependency_hashes')!=dependencies():
        raise ValueError('Current no-split report is unverified or stale for manifest/dependencies')
    if report.get('functions')!=functions or report.get('published_reservations')!=reserved:
        raise ValueError('Current source claims or external ownership reservations changed')
    if {k:report.get(k)for k in expected_limitations()}!=expected_limitations():
        raise ValueError('Report invents historical compiler/ABI/scope or publication claims')
    modules=load_modules(functions);objects=report.get('native_objects',[])
    if len(objects)!=len(functions):raise ValueError('Missing/extra native object ownership')
    for group,f in zip(objects,functions):
        if group.get('claim')!=f:raise ValueError('Native group has false input/source/module ownership')
        profiles=group.get('profiles',[])
        if [p.get('profile')for p in profiles]!=list(PROFILES):raise ValueError('Unknown/missing/duplicate native profile')
        for p in profiles:
            revision=PROFILES[p['profile']]
            if p.get('compiler_flags')!=FLAGS or p.get('assembler_flags')!=AS_FLAGS or p.get('native_input_hashes')!=native_inputs(revision)or p.get('assembly_untouched')is not True:
                raise ValueError('Native compiler/assembler/options/source assembly changed')
            raw=checked_path(p['assembly'],'build/iop/nosplit');obj=checked_path(p['object'],'build/iop/nosplit')
            if digest(raw.read_bytes())!=p.get('assembly_sha256')or digest(obj.read_bytes())!=p.get('object_sha256'):
                raise ValueError('Current raw assembly or native object is stale')
            validate_native_receipt(f,revision,raw.read_bytes(),obj.read_bytes(),p['native_input_hashes'])
            _,proof=inspect_object(Elf32(obj.read_bytes()),f,modules[f['module']][1])
            if p.get('complete_proof')!=proof:raise ValueError('Complete native ownership/pair/addend/section/replay proof changed')
    components=report.get('module_artifacts_are_identity_observations_not_owners',[])
    if len(components)!=len(modules):raise ValueError('Missing/extra original module identity observations')
    for c,(relative,(raw,elf))in zip(components,modules.items()):
        owned=[f for f in functions if f['module']==relative];public=[r for r in reserved if r['module']==relative]
        expected={'module':relative,'original_sha256':digest(raw),'source_claims':[{'name':f['name'],'module_offset':f['module_offset'],'size':f['size']}for f in owned],
            'new_code_bytes':sum(f['size']for f in owned),'existing_public_source_ranges_reserved_not_counted':public,
            'whole_module_owned':False,'original_metadata_and_all_other_bytes':'PRESERVATION_NOT_SOURCE',
            'original_file_bytes':len(raw),'original_file_bytes_outside_new_claims':len(raw)-sum(f['size']for f in owned)}
        if {k:c.get(k)for k in expected}!=expected:raise ValueError('False module/range/preservation ownership or duplicate-module claim')
        partial=checked_path(c['partial_module'],'build/iop/nosplit').read_bytes()
        if partial!=raw or digest(partial)!=c.get('partial_sha256'):
            raise ValueError('Partial module is stale or unknown bytes changed')
    if report.get('progress')!=expected_progress(functions):raise ValueError('Counts exceed unique disjoint source function ownership')
    return {**report,'freshness':'CURRENT_PRIVATE_SOURCE_CLAIMS_MODULES_DEPENDENCIES_AND_WHOLE_NATIVE_CODE_DATA_VERIFIED'}


def main():
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--manifest',type=Path,default=DEFAULT_MANIFEST);parser.add_argument('--output',type=Path,default=DEFAULT_OUTPUT)
    args=parser.parse_args();run(args.manifest,args.output)


if __name__=='__main__':main()
