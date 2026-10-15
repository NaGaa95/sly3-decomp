"""Mandatory nine-program VU union. Known19 routines and five unknown counts stay distinct."""
import argparse,json,struct,sys
from pathlib import Path
sys.dont_write_bytecode=True
from vu_extra_build import ROOT,DEFAULT_BUNDLE,DEFAULT_OUTPUT,EXPECTED_COMPONENTS,ORIGINAL_SHA,Elf32,receipt,sha,renderer,current_report as extras_current,run as extras_build,checked_manifest
DEFAULT_UNION=ROOT/'build/vu/combined'
REPORT_NAME='vu_union_report.json'
import vu_lighting_build as lighting
import vu_mesh_build as mesh
import vu_mesh_alt_build as mesh_alt
import vu_volume_build as volume
import vu_particle_build as particle
import vu_silhouette_build as silhouette

def totals():
    return {'original_unique_program_count':9,'original_unique_VU_code_bytes':50032,'original_unique_program_code_bytes':50032,'verified_source_programs':9,'verified_source_functions':19,'verified_source_known_original_functions':19,'verified_source_original_function_count_complete':False,'unknown_original_function_count_programs':['376118843','1504484043','188058715','376117691','188058427'],'verified_source_VU_code_bytes':50032,'verified_source_code_bytes':50032,'VU_code_percent':50032/50032*100,'verified_source_VIF_control_bytes':320,'VIF_protocol_bytes':320,'DMA_protocol_bytes':32,'verified_source_protocol_bytes':352,'verified_whole_runtime_upload_bytes':50384,'verified_source_initialized_data_bytes':0,'unrecovered_VU_code_bytes':0,'EE_C_CPP_functions_delta':0,'EE_C_CPP_code_bytes_delta':0,'preserved_original_zero_shadow_bytes_added':0,'full_game_source_relink_complete':False,'actual_resolved_nonallocated_metadata_relocations':58,'dynamic_REFS_source_credit':0}

def output_path(output):
    p=Path(output).resolve()
    if not(p.is_relative_to(ROOT/'build/vu/combined')or p.is_relative_to(ROOT/'build/vu/extra/testing')or p.is_relative_to(ROOT/'build/vu_matches/union_stage')or p.is_relative_to(ROOT/'build/vu_matches/program_752237851_integration_20261014')):raise ValueError('VU union output escapes owned build tree')
    return p

def current_components(bundle=DEFAULT_BUNDLE,extra_output=DEFAULT_OUTPUT,lighting_output=lighting.DEFAULT_OUTPUT,mesh_output=mesh.DEFAULT_OUTPUT,mesh_alt_output=mesh_alt.DEFAULT_OUTPUT,volume_output=volume.DEFAULT_OUTPUT,particle_output=particle.DEFAULT_OUTPUT,silhouette_output=silhouette.DEFAULT_OUTPUT):
    legacy=renderer.current_report(ROOT,renderer.DEFAULT_OUTPUT);extra=extras_current(bundle,extra_output)
    result=[{'family':'188059931','processor':'VU1','code_bytes':2240,'chain_bytes':2256,'DMA_protocol_bytes':0,'VIF_protocol_bytes':16,'EE_chain_begin':0x2c1420,'chain_path':receipt(renderer.DEFAULT_OUTPUT/'renderer_upload.bin')['path'],'source':'src/vu/renderer_program.vsm','chain_source':'src/vu/renderer_upload.vif','functions':8,'renderer_evidence':receipt(renderer.DEFAULT_OUTPUT/renderer.REPORT_NAME)}]
    for c in EXPECTED_COMPONENTS:
        result.append({**c,'chain_path':extra['native_components'][c['family']]['files']['chain.bin']['path'],'functions':7 if c['processor']=='VU0'else 1,'extra_evidence':receipt(Path(extra_output)/'vu_extra_report.json')})
    light=lighting.current_report(bundle,lighting_output)
    result.append({'family':'752237851','processor':'VU1','code_bytes':1488,'chain_bytes':1504,'DMA_protocol_bytes':0,'VIF_protocol_bytes':16,'EE_chain_begin':0x2c4600,'EE_payload_begin':0x2c4608,'chain_path':light['native_components']['chain']['files']['chain.bin']['path'],'source':'src/vu/lighting/lighting_program_v2.vsm','chain_source':'src/vu/lighting/lighting_upload_v2.vif','functions':3,'lighting_evidence':receipt(Path(lighting_output)/lighting.REPORT_NAME)})
    mr=mesh.current_report(bundle,mesh_output)
    result.append({**mesh.EXPECTED_COMPONENT,'chain_path':mr['native_components']['chain']['files']['chain.bin']['path'],'mesh_evidence':receipt(Path(mesh_output)/mesh.REPORT_NAME)})
    ar=mesh_alt.current_report(bundle,mesh_alt_output)
    result.append({**mesh_alt.EXPECTED_COMPONENT,'chain_path':ar['native_components']['chain']['files']['chain.bin']['path'],'mesh_alt_evidence':receipt(Path(mesh_alt_output)/mesh_alt.REPORT_NAME)})
    vr=volume.current_report(bundle,volume_output)
    result.append({**volume.EXPECTED_COMPONENT,'chain_path':vr['native_components']['chain']['files']['chain.bin']['path'],'volume_evidence':receipt(Path(volume_output)/volume.REPORT_NAME)})
    pr=particle.current_report(bundle,particle_output)
    result.append({**particle.EXPECTED_COMPONENT,'chain_path':pr['native_components']['chain']['files']['chain.bin']['path'],'particle_evidence':receipt(Path(particle_output)/particle.REPORT_NAME)})
    sr=silhouette.current_report(bundle,silhouette_output)
    result.append({**silhouette.EXPECTED_COMPONENT,'chain_path':sr['native_components']['chain']['files']['chain.bin']['path'],'silhouette_evidence':receipt(Path(silhouette_output)/silhouette.REPORT_NAME)})
    validate_registry(result)
    return result

def validate_registry(components):
    wanted={'188059931':(2240,0,16,2256,8,0x2c1420),'11753275':(672,16,32,720,7,0x2c0250),'376118779':(16,16,32,64,1,0x2c45c0),'752237851':(1488,0,16,1504,3,0x2c4600),'376118843':(16344,0,72,16416,None,0x2c4bf0),'1504484043':(15128,0,72,15200,None,0x2c8c20),'188058715':(8008,0,40,8048,None,0x2c2640),'376117691':(3800,0,24,3824,None,0x2c0520),'188058427':(2336,0,16,2352,None,0x2c1d00)}
    if len(components)!=9 or {c['family'] for c in components}!=set(wanted):raise ValueError('Missing/duplicate mandatory complete VU owner')
    for c in components:
        actual=tuple(c[k] for k in ['code_bytes','DMA_protocol_bytes','VIF_protocol_bytes','chain_bytes','functions','EE_chain_begin'])
        if actual!=wanted[c['family']]:raise ValueError('Wrong VU owner code/control/boundary/function count')
        if c['functions'] is not None and type(c['functions']) is not int:raise ValueError('Known VU function count must be integer')
        if c['family'] in ['376118843','1504484043','188058715','376117691','188058427'] and (c.get('original_function_count_complete') is not False or c.get('source_partition_count')!={'376118843':37,'1504484043':30,'188058715':22,'376117691':3,'188058427':10}[c['family']] or c.get('aliases_count_as_additional_functions') is not False):raise ValueError('Mesh authored partitions/aliases cannot recover original function count')

def union_proof(bundle=DEFAULT_BUNDLE,extra_output=DEFAULT_OUTPUT,lighting_output=lighting.DEFAULT_OUTPUT,mesh_output=mesh.DEFAULT_OUTPUT,mesh_alt_output=mesh_alt.DEFAULT_OUTPUT,volume_output=volume.DEFAULT_OUTPUT,particle_output=particle.DEFAULT_OUTPUT,silhouette_output=silhouette.DEFAULT_OUTPUT):
    """Read-only; re-derive every source/data/control ownership byte."""
    m,e,proofs,legacy,extra_deps,hashes=checked_manifest(bundle);extra=extras_current(bundle,extra_output);light=lighting.current_report(bundle,lighting_output);mr=mesh.current_report(bundle,mesh_output);ar=mesh_alt.current_report(bundle,mesh_alt_output);vr=volume.current_report(bundle,volume_output);pr=particle.current_report(bundle,particle_output);sr=silhouette.current_report(bundle,silhouette_output);components=current_components(bundle,extra_output,lighting_output,mesh_output,mesh_alt_output,volume_output,particle_output,silhouette_output)
    spans=[];payload_spans=[];code=0;DMA=0;VIF=0;all_native=0;routines=0;unknown_counts=[];rewritten=bytearray(e.data);text=e.section('.vutext');ownership=[]
    for c in components:
        begin=c['EE_chain_begin'];size=c['chain_bytes'];end=begin+size
        if any(begin<b and a<end for a,b in spans):raise ValueError('Overlapping original source chains, including control bytes')
        spans.append((begin,end));data=(ROOT/c['chain_path']).read_bytes()
        if len(data)!=size or data!=e.at_vram(begin,size):raise ValueError('Current source-derived entire native chain differs')
        offset=text['offset']+begin-text['addr'];rewritten[offset:offset+size]=data
        payload=next(p for p in legacy['original_programs']if p['family_file_name_hash']==c['family'])
        native_code=b''
        for chunk in payload['chunks']:
            a=chunk['EE_payload_begin'];n=chunk['code_bytes'];b=a+n
            if any(a<y and x<b for x,y in payload_spans):raise ValueError('Duplicate original physical VU instruction ownership')
            payload_spans.append((a,b));native_code+=e.at_vram(a,n)
            if not(begin<=a and b<=end):raise ValueError('Whole original code payload is outside its source chain')
        if len(native_code)!=c['code_bytes']or sha(native_code)!=payload['entire_program_sha256']:raise ValueError('Wrong scoped original program code coverage')
        if c['code_bytes']+c['DMA_protocol_bytes']+c['VIF_protocol_bytes']!=size:raise ValueError('DMA/VIF protocol counted as extra code or whole upload duplicated')
        code+=c['code_bytes'];DMA+=c['DMA_protocol_bytes'];VIF+=c['VIF_protocol_bytes'];all_native+=size
        if c['functions'] is None:unknown_counts.append(c['family'])
        else:routines+=c['functions']
        ownership.append({'family':c['family'],'processor':c['processor'],'EE_chain_begin':begin,'file_offset':offset,'whole_native_chain_bytes':size,'VU_instruction_bytes':c['code_bytes'],'DMA_control_bytes':c['DMA_protocol_bytes'],'VIF_control_bytes':c['VIF_protocol_bytes'],'whole_native_chain_sha256':sha(data),'native_source_binary':c['chain_path'],'original_metadata_preserved_unadmitted':True})
    if(code,DMA,VIF,all_native,routines)!=(50032,32,320,50384,19)or unknown_counts!=['376118843','1504484043','188058715','376117691','188058427']or sha(rewritten)!=ORIGINAL_SHA:raise ValueError('False original union/source/protocol totals or rebuilt bytes')
    all_native_fields=len(legacy['native_proof']['all_actual_nonallocated_overlay_relocations'])+sum(len(v['native_proof']['actual_resolved_nonallocated_metadata_relocations'])for v in extra['native_components'].values())
    all_native_fields+=len(light['native_components']['chain']['native_proof']['actual_nonallocated_metadata_relocations'])
    all_native_fields+=len(mr['native_components']['chain']['native_proof']['actual_resolved_nonallocated_R32_metadata_fields'])
    all_native_fields+=len(ar['native_components']['chain']['native_proof']['actual_resolved_nonallocated_R32_metadata_fields'])
    all_native_fields+=len(vr['native_components']['chain']['native_proof']['actual_resolved_nonallocated_R32_metadata_fields'])
    all_native_fields+=len(pr['native_components']['chain']['native_proof']['actual_resolved_nonallocated_R32_metadata_fields'])
    all_native_fields+=len(sr['native_components']['chain']['native_proof']['actual_resolved_nonallocated_R32_metadata_fields'])
    if all_native_fields!=58:raise ValueError('Missing actual native metadata relocation evidence')
    hashes.update(sr['dependency_hashes'])
    for row in [receipt(Path(silhouette_output)/silhouette.REPORT_NAME),sr['native_command_log'],*[r for v in sr['native_components'].values() for r in v['files'].values()]]:hashes[row['path']]=row['sha256']
    hashes.update(pr['dependency_hashes'])
    for row in [receipt(Path(particle_output)/particle.REPORT_NAME),pr['native_command_log'],*[r for v in pr['native_components'].values() for r in v['files'].values()]]:hashes[row['path']]=row['sha256']
    hashes.update(vr['dependency_hashes'])
    for row in [receipt(Path(volume_output)/volume.REPORT_NAME),vr['native_command_log'],*[r for v in vr['native_components'].values() for r in v['files'].values()]]:hashes[row['path']]=row['sha256']
    hashes.update(ar['dependency_hashes'])
    for row in [receipt(Path(mesh_alt_output)/mesh_alt.REPORT_NAME),ar['native_command_log'],*[r for v in ar['native_components'].values() for r in v['files'].values()]]:hashes[row['path']]=row['sha256']
    hashes[mr['native_command_log']['path']]=mr['native_command_log']['sha256']
    hashes.update(mr['dependency_hashes'])
    hashes[receipt(Path(mesh_output)/mesh.REPORT_NAME)['path']]=receipt(Path(mesh_output)/mesh.REPORT_NAME)['sha256']
    for item in mr['native_components'].values():
        for row in item['files'].values():hashes[row['path']]=row['sha256']
    hashes.update(light['dependency_hashes'])
    hashes[receipt(Path(lighting_output)/lighting.REPORT_NAME)['path']]=receipt(Path(lighting_output)/lighting.REPORT_NAME)['sha256']
    for item in light['native_components'].values():
        for row in item['files'].values():hashes[row['path']]=row['sha256']
    for r in [receipt(Path(extra_output)/'vu_extra_report.json'),receipt(renderer.DEFAULT_OUTPUT/renderer.REPORT_NAME),*legacy['objects'].values(),legacy['source_derived_upload_binary'],legacy['partial_source_elf']]:hashes[r['path']]=r['sha256']
    for item in extra['native_components'].values():
        for r in item['files'].values():hashes[r['path']]=r['sha256']
    hashes['tools/vu_build.py']=receipt(ROOT/'tools/vu_build.py')['sha256']
    return {'components':components,'progress':totals(),'dependency_hashes':dict(sorted(hashes.items())),'native_source_ownership':ownership,'actual_resolved_nonallocated_metadata_relocations':58,'native_initialized_data_bytes':0,'native_BSS_bytes':0,'unsupported_allocated_sections':0,'original_unique_programs':legacy['original_programs'],'original_nonallocated_zero_shadow_records_excluded':29,'historical_original_compiler_identity_confirmed':False,'unconfirmed_dynamic_VU0_entry_1C0':True,'EE_source_build_preserved_other_bytes_is_separate_accounting':True,'full_source_relink_complete':False},bytes(rewritten)

def report_fields_current(report,expected):
    if {k:report[k] for k in expected}!=expected:raise ValueError('False/stale/incomplete VU union receipt')

def current_report(bundle=DEFAULT_BUNDLE,extra_output=DEFAULT_OUTPUT,output=DEFAULT_UNION,lighting_output=lighting.DEFAULT_OUTPUT,mesh_output=mesh.DEFAULT_OUTPUT,mesh_alt_output=mesh_alt.DEFAULT_OUTPUT,volume_output=volume.DEFAULT_OUTPUT,particle_output=particle.DEFAULT_OUTPUT,silhouette_output=silhouette.DEFAULT_OUTPUT):
    out=output_path(output);expected,rebuilt=union_proof(bundle,extra_output,lighting_output,mesh_output,mesh_alt_output,volume_output,particle_output,silhouette_output);r=json.loads((out/REPORT_NAME).read_text())
    report_fields_current(r,expected)
    p=out/'SCUS_974.64.vu-union-source.elf'
    if receipt(p)!=r['partial_source_elf']or p.read_bytes()!=rebuilt:raise ValueError('Partial union ELF was not derived from all nine current native chains')
    return {**r,'freshness':'CURRENT_NINE_DISJOINT_WHOLE_VU_PROGRAMS_KNOWN19_FIVE_UNKNOWN_FUNCTION_COUNTS_VERIFIED'}

def summarize(supplied=None):
    current=current_components()
    if supplied is not None and supplied!=current:raise ValueError('Foreign/incomplete VU source owner set')
    current_report();return totals()

def current_programs():
    r=current_report();owners={c['family']:c for c in r['components']};result=[]
    for original in r['original_unique_programs']:
        c=owners.get(original['family_file_name_hash'])
        result.append({**original,'decompilation_status':'complete-native-VU-source-code-and-runtime-chain'if c else'preserved-not-decompiled','verified_source_routines':c['functions']if c else 0,'verified_source_VU_code_bytes':c['code_bytes']if c else 0,'verified_source_DMA_control_bytes':c['DMA_protocol_bytes']if c else 0,'verified_source_VIF_control_bytes':c['VIF_protocol_bytes']if c else 0,'verified_source_initialized_data_bytes':0,'source_language':'readable-native-VSM-VIF-DMA'if c else None,'full_program_source_metadata_relink_complete':False,**({'source':c['source'],'chain_source':c['chain_source'],'processor':c['processor']}if c else{})})
    if len(result)!=9 or sum(p['verified_source_VU_code_bytes']for p in result)!=50032:raise ValueError('Missing/duplicate original union program')
    return result

def combine(bundle=DEFAULT_BUNDLE,extra_output=DEFAULT_OUTPUT,output=DEFAULT_UNION,fresh=False,lighting_output=lighting.DEFAULT_OUTPUT,mesh_output=mesh.DEFAULT_OUTPUT,mesh_alt_output=mesh_alt.DEFAULT_OUTPUT,volume_output=volume.DEFAULT_OUTPUT,particle_output=particle.DEFAULT_OUTPUT,silhouette_output=silhouette.DEFAULT_OUTPUT):
    out=output_path(output)
    if fresh and out.exists()and any(out.iterdir()):raise ValueError('Independent union proof needs new empty output')
    r,rebuilt=union_proof(bundle,extra_output,lighting_output,mesh_output,mesh_alt_output,volume_output,particle_output,silhouette_output);out.mkdir(parents=True,exist_ok=True);p=out/'SCUS_974.64.vu-union-source.elf';p.write_bytes(rebuilt);r['partial_source_elf']=receipt(p);(out/REPORT_NAME).write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8');return current_report(bundle,extra_output,out,lighting_output,mesh_output,mesh_alt_output,volume_output,particle_output,silhouette_output)

def build_components():
    # Existing renderer source/module/test/config remain byte-identical. Its
    # fresh native default build is already part of the authorized whole build.
    from vu_sources import build_components as legacy_build
    legacy_build();extras_build();lighting.run();mesh.run();mesh_alt.run();volume.run();particle.run();silhouette.run();combine();print('PASS VU union:19 known original routines plus five unknown-count VU programs /50032 code bytes; DMA32 + VIF320 separately; dynamicREFS credit0')
    return current_components()

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--extra-output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--lighting-output',type=Path,default=lighting.DEFAULT_OUTPUT);p.add_argument('--mesh-output',type=Path,default=mesh.DEFAULT_OUTPUT);p.add_argument('--mesh-alt-output',type=Path,default=mesh_alt.DEFAULT_OUTPUT);p.add_argument('--volume-output',type=Path,default=volume.DEFAULT_OUTPUT);p.add_argument('--particle-output',type=Path,default=particle.DEFAULT_OUTPUT);p.add_argument('--silhouette-output',type=Path,default=silhouette.DEFAULT_OUTPUT);p.add_argument('--output',type=Path,default=DEFAULT_UNION);p.add_argument('--fresh',action='store_true');p.add_argument('--check',action='store_true');p.add_argument('--compile-extra',action='store_true');a=p.parse_args()
    if a.compile_extra:
        extras_build(a.bundle_root,a.extra_output,a.fresh);lighting.run(a.bundle_root,a.lighting_output,a.fresh);mesh.run(a.bundle_root,a.mesh_output,a.fresh);mesh_alt.run(a.bundle_root,a.mesh_alt_output,a.fresh);volume.run(a.bundle_root,a.volume_output,a.fresh);particle.run(a.bundle_root,a.particle_output,a.fresh);silhouette.run(a.bundle_root,a.silhouette_output,a.fresh)
    r=current_report(a.bundle_root,a.extra_output,a.output,a.lighting_output,a.mesh_output,a.mesh_alt_output,a.volume_output,a.particle_output,a.silhouette_output)if a.check else combine(a.bundle_root,a.extra_output,a.output,a.fresh,a.lighting_output,a.mesh_output,a.mesh_alt_output,a.volume_output,a.particle_output,a.silhouette_output);print(json.dumps({'status':'PASS','progress':r['progress'],'report':receipt(output_path(a.output)/REPORT_NAME),'freshness':r['freshness']}))
if __name__=='__main__':main()
