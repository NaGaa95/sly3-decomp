"""Whole native VU renderer verification. Pure review functions never write files.

The two measured DVP language profiles reproduce original native instructions;
they do not establish the historical compiler/VCL version. EE counts are separate.
"""
import argparse
import hashlib
import json
import struct
import subprocess
import sys
from pathlib import Path

HERE = Path(__file__).resolve()
PROJECT = next(p for p in HERE.parents if (p / 'disc/SCUS_974.64').is_file())
sys.path.insert(0, str(PROJECT / 'tools'))
from common import Elf32
DEFAULT_BUNDLE = HERE.parents[1]
DEFAULT_OUTPUT = PROJECT / 'build/vu/renderer'
REPORT_NAME = 'vu_source_report.json'
ORIGINAL_SHA = 'ce817858306efd711f08bbc14f393455280119cb00b894bdc9fb1fa47bcbb338'
PROGRAM_SHA = '2691a079a57499b9c415e4f640cf6efcadd5dddc41e4dcb4b6c86eb5266b9d75'
UPLOAD_SHA = 'b950b0611dfcbe2d6bfcf36545caa572696fbdbe2c6ba06b1feefd35ca39f71f'
EXPECTED = [('render_template_27',0,48),('render_template_30',48,48),('render_template_34',96,48),('render_template_37',144,48),('render_frame_unmasked',192,64),('render_frame_masked',256,64),('render_vertex_batches',320,1296),('render_quad_packet',1616,624)]
EXPECTED_SOURCE_HASHES = {'src/vu/renderer_program.vsm':'f2d2cbf3022d8fbf7d5c1996e97a856118c326f0a4ef65f0242d08a001635faf','src/vu/renderer_upload.vif':'011f4483a3a594c285a885fda52191533c538befa7e10e31a251e54192e3d985'}
EXPECTED_EVIDENCE_HASHES = {'docs/evidence/vu_renderer_input_review.json':'0ffd8f7964a4ac1027b0dbaa8098df9c46f84274edfb7759da64480a878f5464','docs/evidence/vu_renderer_parent_review.json':'6b539e7d0404e02b2882fc844b7fc326fe47ff67eddf57e04be87c1e03886df9','config/vu_original_programs.json':'0ba30ac51d21b09c15dac9827cad1324c7fa93d6e1fddc490f355f3d6e581a64'}

def sha(data):
    return hashlib.sha256(data).hexdigest()

def contained(base, relative):
    base=Path(base).resolve(); p=(base/relative).resolve()
    if not p.is_relative_to(base) or p==base:
        raise ValueError('Path escapes the claimed source/tool/output ownership')
    return p

def file_receipt(path, base):
    p=Path(path).resolve()
    return {'path':p.relative_to(Path(base).resolve()).as_posix(),'bytes':p.stat().st_size,'sha256':sha(p.read_bytes())}

def checked_output(output, fresh=False):
    p=Path(output).resolve()
    allowed=[(PROJECT/'build/vu').resolve(),(PROJECT/'build/vu_matches').resolve()]
    if not any(p.is_relative_to(b) and p!=b for b in allowed):
        raise ValueError('VU output escapes its maintained or explicitly private build lane')
    if fresh and p.exists() and any(p.iterdir()):
        raise ValueError('Independent replay requires a new empty output directory')
    return p

def original_mapping():
    raw=(PROJECT/'disc/SCUS_974.64').read_bytes()
    if sha(raw)!=ORIGINAL_SHA:raise ValueError('Original USA executable identity mismatch')
    e=Elf32(raw);tab=e.section('.DVP.ovlytab');strings=e.section_data(e.section('.DVP.ovlystrtab'));text=e.section('.vutext')
    if tab['type']!=0x7ffff420 or tab['flags']&2 or tab['size']!=29*12:
        raise ValueError('Original complete DVP table ownership differs')
    groups={};rows=[];covered=[]
    for off in range(0,tab['size'],12):
        no,lma,vma=struct.unpack_from('<III',e.section_data(tab),off)
        name=strings[no:].split(b'\0',1)[0].decode('ascii');s=e.section(name)
        if s['type']!=0x7ffff421 or s['flags']!=5 or any(e.section_data(s)):
            raise ValueError('Original shadow is not the proved nonallocated zero metadata')
        word=struct.unpack('<I',e.at_vram(lma-4,4))[0];count=((word>>16)&255) or 256
        if word&0x7f000000!=0x4a000000 or (word&65535)*8!=vma or s['size']!=count*8:
            raise ValueError('Original native MPG destination/count does not own its shadow')
        if not(text['addr']<=lma and lma+s['size']<=text['addr']+text['size']):
            raise ValueError('Native payload lies outside allocated original VU upload text')
        span=(lma,lma+s['size'])
        if any(span[0]<b and a<span[1]for a,b in covered):raise ValueError('Original native payload source ownership overlap')
        covered.append(span);family=name.split('.')[5];body=e.at_vram(lma,s['size'])
        row={'family':family,'VU_byte_begin':vma,'EE_payload_begin':lma,'code_bytes':s['size'],'code_sha256':sha(body),'original_zero_nonallocated_shadow':name}
        rows.append(row);groups.setdefault(family,[]).append((vma,body,row))
    programs=[]
    for family,chunks in groups.items():
        cursor=0;body=b'';ordered=[]
        for vma,data,row in sorted(chunks,key=lambda c:c[0]):
            if vma!=cursor:raise ValueError('Original whole native program has a gap/duplicate range')
            body+=data;cursor+=len(data);ordered.append(row)
        programs.append({'family_file_name_hash':family,'VU_byte_begin':0,'VU_bytes':cursor,'entire_program_sha256':sha(body),'chunks':ordered})
    if len(programs)!=9 or len(rows)!=29 or sum(p['VU_bytes']for p in programs)!=50032:
        raise ValueError('Wrong original nine-program denominator or duplicated shadow count')
    upload=e.at_vram(0x2c1420,2256);program=upload[8:2056]+upload[2064:2256]
    if sha(upload)!=UPLOAD_SHA or sha(program)!=PROGRAM_SHA or len(program)!=2240:
        raise ValueError('Complete original renderer/upload mapping differs')
    if struct.unpack_from('<II',upload,0)!=(0,0x4a000000) or struct.unpack_from('<II',upload,2056)!=(0,0x4a180100):
        raise ValueError('Original whole VIF framing differs')
    return e,program,upload,programs

def allocated(e,size,expected):
 if e.data[4:6]!=bytes([1,1]):raise ValueError('wrong ELF class/endian')
 a=[s for s in e.sections if s['flags']&2]
 if len(a)!=3 or {s['name'] for s in a}!={'.vutext','.vudata','.vubss'}:raise ValueError('extra/absent allocated section')
 t=next(s for s in a if s['name']=='.vutext')
 if t['type']!=1 or t['flags']!=6 or t['size']!=size or e.section_data(t)!=expected:raise ValueError('incomplete/different entire native code')
 if any(s['size'] for s in a if s['name']!='.vutext'):raise ValueError('unmapped initialized data or BSS')
 if {(s['name'],s['type'],s['flags']) for s in a if s['name']!='.vutext'}!={('.vudata',1,3),('.vubss',8,3)}:raise ValueError('wrong empty native data/BSS section types')
 if e.type!=1 or e.phnum:raise ValueError('native proof must be a relocatable object with no hidden load segments')
 return a,t

def validate_program(data,expected):
 e=Elf32(data);a,t=allocated(e,2240,expected)
 if any(s['type'] in [4,9] and s['size'] for s in e.sections):raise ValueError('unexpected relocation in native program')
 funcs=[s for s in e.symbols() if s['type']==2]
 if sorted((s['name'],s['value'],s['size']) for s in funcs)!=sorted(EXPECTED):raise ValueError('incomplete/overlapping function ownership')
 if any(s['shndx']!=t['index'] or s['visibility']!=0xeb for s in funcs):raise ValueError('wrong VU function address space')
 cursor=0
 for name,begin,size in EXPECTED:
  if begin!=cursor:raise ValueError('native gap')
  code=e.section_data(t)[begin:begin+size];pairs=list(struct.iter_unpack('<II',code))
  if [i*8 for i,(lo,hi) in enumerate(pairs) if hi&0x40000000]!=[size-16]:raise ValueError('invalid E/delay termination')
  cursor+=size
 if cursor!=2240:raise ValueError('unowned native text')
 return e,a,t

def validate_upload(data,expected):
 e=Elf32(data);a,t=allocated(e,2256,expected)
 rel=[s for s in e.sections if s['type'] in [4,9] and s['size']]
 if len(rel)!=1 or rel[0]['type']!=9 or rel[0]['name']!='.rel.DVP.ovlytab':raise ValueError('unreviewed relocation section')
 tab=next(s for s in e.sections if s['name']=='.DVP.ovlytab');strings=next(s for s in e.sections if s['name']=='.DVP.ovlystrtab')
 if tab['flags']!=1 or tab['size']!=24 or tab['type']!=0x7ffff420:raise ValueError('wrong nonallocated DVP table')
 if strings['flags']!=1 or strings['type']!=3:raise ValueError('allocated DVP names')
 if rel[0]['info']!=tab['index'] or rel[0]['size']!=32 or rel[0]['flags']!=0x40 or rel[0]['entsize']!=8:raise ValueError('wrong metadata relocation ownership')
 syms=e.symbols();byname={s['name']:s for s in syms};rfields=[]
 if len([s for s in e.sections if s['type']==2])!=1 or rel[0]['link']!=next(s['index'] for s in e.sections if s['type']==2):raise ValueError('wrong metadata relocation symbol-table domain')
 if len([s['name'] for s in syms if s['name']])!=len({s['name'] for s in syms if s['name']}):raise ValueError('ambiguous native named symbol')
 for offset,info in struct.iter_unpack('<II',e.section_data(rel[0])):
  symbol=syms[info>>8];kind=info&255;addend=struct.unpack_from('<I',e.section_data(tab),offset)[0]
  if kind!=2 or offset not in [0,4,12,16]:raise ValueError('unsupported DVP metadata relocation')
  want=t if offset in [4,16] else strings
  if symbol['shndx']!=want['index'] or symbol['type']!=3 or symbol['value']!=0:raise ValueError('wrong metadata section reference')
  rfields.append({'offset':offset,'type':kind,'symbol':symbol['name'],'symbol_section_index':symbol['shndx'],'original_native_addend':addend,'resolved_value':addend+(0x2c1420 if offset in [4,16] else 0),'resolved_domain':'EE payload address' if offset in [4,16] else 'DVP string-table relative offset'})
 if {r['offset'] for r in rfields}!={0,4,12,16}:raise ValueError('missing or duplicate metadata relocation')
 chunks=[];shadow_indices=[]
 for off,vma,want_lma,size in [(0,0,8,2048),(12,2048,2064,192)]:
  no,lma,address=struct.unpack_from('<III',e.section_data(tab),off)
  if lma!=want_lma or address!=vma:raise ValueError('wrong native overlay/load mapping')
  name=e.section_data(strings)[no:].split(b'\0')[0].decode('ascii');shadow=next((s for s in e.sections if s['name']==name),None)
  if shadow is None or shadow['type']!=0x7ffff421 or shadow['flags']!=5 or shadow['size']!=size or any(e.section_data(shadow)):raise ValueError('wrong native zero shadow')
  shadow_indices.append(shadow['index']);chunks.append({'name':name,'native_shadow_section':shadow['index'],'VU_byte_begin':vma,'EE_payload_begin':0x2c1420+lma,'payload_bytes':size,'native_file_payload_sha256':sha(e.section_data(t)[lma:lma+size]),'nonallocated_shadow_not_additional_code':True})
 if len([s for s in e.sections if s['name'].startswith('.DVP.overlay.')])!=2:raise ValueError('extra shadow')
 for name,begin,size in EXPECTED:
  f=byname.get(name);mips=byname.get('_$'+name)
  if f is None or mips is None or f['value']!=begin or f['visibility']!=0xeb or f['shndx']!=shadow_indices[0 if begin<2048 else 1]:raise ValueError('VU label domain/mapping')
  file_off=begin+(8 if begin<2048 else 16)
  if mips['shndx']!=t['index'] or mips['value']!=file_off or mips['visibility']!=0xeb:raise ValueError('wrong separate stored-label mapping')
 if byname['render_upload_begin']['value']!=0 or byname['render_upload_end']['value']!=2256:raise ValueError('upload endpoint mismatch')
 return e,a,t,rfields,chunks

def checked_manifest(bundle=DEFAULT_BUNDLE):
    bundle=Path(bundle).resolve();m=json.loads(contained(bundle,'config/vu_sources.json').read_text())
    if m.get('schema')!=1 or m.get('source_language')!='readable-native-VSM-VIF' or m.get('EE_C_CPP_source_count_delta')!=0:
        raise ValueError('Unsupported VU admission/source-language schema')
    expected={'family_file_name_hash':'188059931','whole_program_code_bytes':2240,'whole_upload_bytes':2256,'VIF_protocol_bytes':16,'original_EE_upload_address':0x2c1420,'program_sha256':PROGRAM_SHA,'upload_sha256':UPLOAD_SHA,'source':'src/vu/renderer_program.vsm','upload_source':'src/vu/renderer_upload.vif','routines':[{'name':n,'VU_byte_begin':a,'code_bytes':s}for n,a,s in EXPECTED]}
    if m.get('components')!=[expected] or m.get('original_sha256')!=ORIGINAL_SHA or m.get('original_unique_VU_code_bytes')!=50032 or m.get('original_program_count')!=9 or m.get('original_nonallocated_zero_shadow_count')!=29:
        raise ValueError('Only one complete, disjoint, independently reviewed full renderer component is admitted')
    if m.get('historical_original_compiler_identity_confirmed')is not False or m.get('full_game_source_relink_complete')is not False:
        raise ValueError('Unsupported historical compiler/full-source claim')
    e,program,upload,programs=original_mapping()
    pinned={**EXPECTED_SOURCE_HASHES,**EXPECTED_EVIDENCE_HASHES}
    receipts=[]
    for rel,want in pinned.items():
        p=contained(bundle,rel);r=file_receipt(p,bundle)
        if r['sha256']!=want:raise ValueError('Reviewed source/input/parent evidence changed: '+rel)
        receipts.append(r)
    for rel in EXPECTED_SOURCE_HASHES:
        text=contained(bundle,rel).read_text().lower()
        if any(token in text for token in ['.word','.byte','.long','.quad','.incbin','.org','.space']):raise ValueError('Raw original instruction/data preservation cannot be source')
    src=contained(bundle,'src/vu/renderer_program.vsm').read_text()
    wrapper=contained(bundle,'src/vu/renderer_upload.vif').read_text()
    if '.include' in src.lower() or wrapper.count('.include "renderer_program.vsm"')!=1:raise ValueError('Unowned source include')
    evidence=json.loads(contained(bundle,'docs/evidence/vu_renderer_input_review.json').read_text())
    parent=json.loads(contained(bundle,'docs/evidence/vu_renderer_parent_review.json').read_text())
    if parent['status']!='PASS_PARENT_INDEPENDENT_COMPLETE2240_VU_2256_NATIVE_UPLOAD' or parent['blockers'] or parent['production_mutations'] or parent['new_source_programs_pending_publication']!=1 or parent['new_VU_functions_pending_publication']!=8 or parent['new_VU_code_bytes_pending_publication']!=2240:
        raise ValueError('Missing complete independent parent boundary/input/native review')
    for body in evidence['original_complete_EE_support_bodies']:
        actual=e.at_vram(body['address'],body['size'])
        if actual.hex()!=body['original_bytes'] or sha(actual)!=body['sha256']:
            raise ValueError('Original complete CPU entry/input/header/packet proof has changed')
    if len(evidence['original_complete_EE_support_bodies'])!=34:raise ValueError('Incomplete original CPU protocol proof set')
    original_inv=json.loads(contained(bundle,'config/vu_original_programs.json').read_text())
    if {(p['family_file_name_hash'],p['VU_bytes'],p['entire_program_sha256'])for p in programs}!={(p['family_file_name_hash'],p['VU_bytes'],p['entire_program_sha256'])for p in original_inv['programs']}:
        raise ValueError('Original program denominator evidence does not agree with native metadata')
    toolpath=contained(bundle,'tools/third_party/dvp/provenance.json');provenance=json.loads(toolpath.read_text())
    if sha(toolpath.read_bytes())!='2199c34122dcb130521cbc1690a2a3f996cd9f59f1c4886055a88ed4354a1ea7' or sha(toolpath.read_bytes())!=m['portable_provenance_sha256'] or provenance['system_installation']or provenance['environment_changes']or provenance['target']!='dvp' or provenance['version']!='GNU Binutils 2.45.1':
        raise ValueError('Wrong portable/native DVP provenance')
    receipts.append(file_receipt(toolpath,bundle))
    if sorted(p.name for p in contained(bundle,'tools/third_party/dvp/bin').iterdir())!=['dvp-as.exe','dvp-objdump.exe','libgcc_s_dw2-1.dll','libwinpthread-1.dll','libzstd.dll']:
        raise ValueError('Missing or unsupported portable executable runtime')
    for row in provenance['files']:
        p=contained(bundle,row['path']);r=file_receipt(p,bundle)
        if r['sha256']!=row['sha256']or r['bytes']!=row['bytes']:raise ValueError('Portable tool/runtime/license changed: '+row['path'])
        if p.suffix in ['.exe','.dll']:
            b=p.read_bytes()
            if b[:2]!=b'MZ' or struct.unpack_from('<H',b,struct.unpack_from('<I',b,60)[0]+4)[0]!=0x14c:raise ValueError('Unsupported native DVP PE runtime architecture')
        receipts.append(r)
    for rel in ['config/vu_sources.json','tools/vu_build.py','tools/vu_sources.py','tools/test_vu_sources.py']:
        receipts.append(file_receipt(contained(bundle,rel),bundle))
    receipts.append({'project_shared_reader':file_receipt(PROJECT/'tools/common.py',PROJECT)})
    return m,e,program,upload,programs,receipts,evidence

def inspect_native(program_object, upload_object, expected_program, expected_upload):
    pe,pa,pt=validate_program(program_object,expected_program)
    ue,ua,ut,relocations,chunks=validate_upload(upload_object,expected_upload)
    def sections(e,allocated):
        return [{**s,'whole_native_sha256':sha(e.section_data(s))}for s in allocated]
    return {'program_allocated_sections':sections(pe,pa),'upload_allocated_sections':sections(ue,ua),'all_actual_nonallocated_overlay_relocations':relocations,'native_upload_chunks':chunks,'native_VU_code_sha256':sha(pe.section_data(pt)),'whole_VIF_upload_sha256':sha(ue.section_data(ut)),'all_allocated_native_code_bytes_complete':True,'emitted_initialized_data_bytes':0,'BSS_bytes':0,'unsupported_allocated_sections':0,'native_nonallocated_zero_shadow_bytes_excluded':2240,'original_nonallocated_zero_shadows_excluded':29}

def current_report(bundle=DEFAULT_BUNDLE, output=DEFAULT_OUTPUT):
    """Reread every current source/tool/input/native byte. This API never writes."""
    bundle=Path(bundle).resolve();out=checked_output(output)
    m,e,program,upload,programs,freshness,evidence=checked_manifest(bundle)
    report=json.loads((out/REPORT_NAME).read_text())
    if report['bundle_root']!=bundle.relative_to(PROJECT).as_posix() or report['freshness_inputs']!=freshness:
        raise ValueError('Stale/foreign source, native tool, verifier, or original input proof')
    section=e.section('.vutext');offset=section['offset']+0x2c1420-section['addr']
    want_owner={'EE_upload_address':0x2c1420,'file_offset':offset,'bytes':2256,'VU_instructions':2240,'VIF_protocol':16,'all_original_metadata_preserved_unadmitted':True}
    if report.get('consumed_native_upload')!=want_owner:raise ValueError('False native upload/partial ELF ownership')
    if report.get('dependency_hashes')!=dependency_hashes(bundle,freshness):raise ValueError('Stale/false source dependency map')
    if report.get('original_sha256')!=ORIGINAL_SHA or report.get('kind')!='partial-readable-native-VU-assembly-source-build' or report.get('original_programs')!=programs or report.get('complete_original_CPU_protocol_body_count')!=34 or report.get('original_VU_entry_input_protocol')!=evidence['all_real_VU_entry_inputs'] or report.get('original_lane_and_arithmetic_semantics')!=evidence['lane_and_arithmetic_semantics'] or report.get('historical_original_compiler_identity_confirmed')is not False or report.get('full_source_relink_complete')is not False:raise ValueError('False original/compiler/native-input/source-ownership report')
    if set(report['objects'])!={'program','upload'}:raise ValueError('Incomplete whole native profile receipts')
    objects={}
    for mode,row in report['objects'].items():
        p=out/(mode+'.o')
        if row!=file_receipt(p,PROJECT):raise ValueError('Changed/missing current entire native object: '+mode)
        objects[mode]=p.read_bytes()
    proof=inspect_native(objects['program'],objects['upload'],program,upload)
    if report['native_proof']!=proof or report['progress']!=source_totals() or report['compiler_profiles']!=profiles():
        raise ValueError('False/stale native section, relocation, source-count, or profile receipt')
    binary=out/'renderer_upload.bin'
    if report.get('source_derived_upload_binary')!=file_receipt(binary,PROJECT)or binary.read_bytes()!=upload:raise ValueError('Source-derived full VIF upload binary is incomplete or stale')
    partial=out/'SCUS_974.64.vu-source.elf'
    if file_receipt(partial,PROJECT)!=report['partial_source_elf'] or sha(partial.read_bytes())!=ORIGINAL_SHA:
        raise ValueError('Partial VU source executable no longer equals the original USA file')
    return {**report,'freshness':'CURRENT_COMPLETE_VU_PROGRAM_AND_WHOLE_NATIVE_UPLOAD_VERIFIED'}

def dependency_hashes(bundle,freshness):
    result={}
    for r in freshness:
        if 'project_shared_reader' in r:
            q=r['project_shared_reader'];result[q['path']]=q['sha256']
        else:
            key=(Path(bundle)/r['path']).resolve().relative_to(PROJECT).as_posix();result[key]=r['sha256']
    result['disc/SCUS_974.64']=ORIGINAL_SHA
    return dict(sorted(result.items()))

def source_totals():
    return {'original_unique_program_count':9,'original_unique_VU_code_bytes':50032,'original_unique_program_code_bytes':50032,'verified_source_programs':1,'verified_source_functions':8,'verified_source_VU_code_bytes':2240,'verified_source_code_bytes':2240,'VU_code_percent':2240/50032*100,'verified_source_VIF_control_bytes':16,'VIF_protocol_bytes':16,'verified_whole_runtime_upload_bytes':2256,'verified_source_initialized_data_bytes':0,'unrecovered_VU_code_bytes':50032-2240,'EE_C_CPP_functions_delta':0,'EE_C_CPP_code_bytes_delta':0,'preserved_original_zero_shadow_bytes_added':0,'full_game_source_relink_complete':False}

def profiles():
    return [{'mode':'program','flags':['--defsym','VU_NATIVE_STANDALONE=1'],'whole_native_code_bytes':2240},{'mode':'upload','flags':['-I','<canonical-source-directory>'],'whole_native_upload_bytes':2256}]

def run(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT,fresh=False):
    """Compile from current readable source; writes only the explicit VU output."""
    bundle=Path(bundle).resolve();out=checked_output(output,fresh)
    m,e,program,upload,programs,freshness,evidence=checked_manifest(bundle)
    assembler=contained(bundle,'tools/third_party/dvp/bin/dvp-as.exe')
    version=subprocess.run([str(assembler),'--version'],capture_output=True,timeout=30)
    if version.returncode or b'2.45.1'not in version.stdout or b"target of `dvp'"not in version.stdout:raise ValueError('Pinned DVP native profile unavailable')
    out.mkdir(parents=True,exist_ok=True);objects={};commands=[]
    for mode,relative,args in [('program','src/vu/renderer_program.vsm',['--defsym','VU_NATIVE_STANDALONE=1']),('upload','src/vu/renderer_upload.vif',['-I',str(contained(bundle,'src/vu'))])]:
        obj=out/(mode+'.o');cmd=[str(assembler),*args,'-o',str(obj),str(contained(bundle,relative))]
        p=subprocess.run(cmd,capture_output=True,timeout=30,cwd=contained(bundle,'src/vu'))
        if p.returncode:raise ValueError('Native DVP assembly failed: '+p.stderr.decode(errors='replace'))
        objects[mode]=file_receipt(obj,PROJECT);commands.append({'mode':mode,'command':cmd})
    proof=inspect_native((out/'program.o').read_bytes(),(out/'upload.o').read_bytes(),program,upload)
    rebuilt=bytearray(e.data);section=e.section('.vutext');offset=section['offset']+0x2c1420-section['addr']
    native=Elf32((out/'upload.o').read_bytes());payload=native.section_data(native.section('.vutext'))
    rebuilt[offset:offset+2256]=payload
    if sha(rebuilt)!=ORIGINAL_SHA:raise ValueError('Whole native upload changes the USA executable')
    binary=out/'renderer_upload.bin';binary.write_bytes(payload)
    partial=out/'SCUS_974.64.vu-source.elf';partial.write_bytes(rebuilt)
    report={'kind':'partial-readable-native-VU-assembly-source-build','bundle_root':bundle.relative_to(PROJECT).as_posix(),'original_sha256':ORIGINAL_SHA,'freshness_inputs':freshness,'dependency_hashes':dependency_hashes(bundle,freshness),'objects':objects,'compiler_profiles':profiles(),'actual_native_commands':commands,'native_proof':proof,'progress':source_totals(),'original_programs':programs,'complete_original_CPU_protocol_body_count':len(evidence['original_complete_EE_support_bodies']),'original_VU_entry_input_protocol':evidence['all_real_VU_entry_inputs'],'original_lane_and_arithmetic_semantics':evidence['lane_and_arithmetic_semantics'],'native_compiler_version_stdout':version.stdout.decode(),'source_derived_upload_binary':file_receipt(binary,PROJECT),'consumed_native_upload':{'EE_upload_address':0x2c1420,'file_offset':offset,'bytes':2256,'VU_instructions':2240,'VIF_protocol':16,'all_original_metadata_preserved_unadmitted':True},'EE_source_build_ledger_is_separate':'source_build.json preserved_other_bytes is EE-only accounting; this VU-source partial ELF consumes the separate VU2240/protocol16 native payload','partial_source_elf':file_receipt(partial,PROJECT),'native_debug_file_and_line_names_match_original':False,'original_nonallocated_debug_metadata_preserved':True,'historical_original_compiler_identity_confirmed':False,'full_source_relink_complete':False}
    (out/REPORT_NAME).write_text(json.dumps(report,indent=2)+'\n',encoding='utf-8')
    return current_report(bundle,out)

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--fresh',action='store_true');p.add_argument('--check',action='store_true')
    a=p.parse_args();r=current_report(a.bundle_root,a.output)if a.check else run(a.bundle_root,a.output,a.fresh)
    print(json.dumps({'status':'PASS','progress':r['progress'],'freshness':r['freshness'],'report':file_receipt(checked_output(a.output)/REPORT_NAME,PROJECT)}))

if __name__=='__main__':main()
