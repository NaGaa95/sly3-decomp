"""Mandatory complete mesh VU component. Existing four owners remain mandatory."""
import argparse,json,struct,subprocess,sys,os,uuid,copy,hashlib
from pathlib import Path
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve();ROOT=next(p for p in HERE.parents if (p/'disc/SCUS_974.64').is_file())
sys.path.insert(0,str(ROOT/'tools'))
import vu_build as renderer
from common import Elf32
from vu_mesh_native import strict_native
DEFAULT_BUNDLE=HERE.parents[1]
DEFAULT_OUTPUT=ROOT/'build/vu/mesh'
REPORT_NAME='vu_mesh_report.json'
EXPECTED_COMPONENT={'family': '376118843', 'processor': 'VU1', 'source': 'src/vu/mesh/mesh_program.vsm', 'chain_source': 'src/vu/mesh/mesh_upload.vif', 'source_sha256': 'd73651ddef6a1c2cf2753e09af483a3285108b1d672b0341b0e070d953c71032', 'chain_source_sha256': '9cc04b59f0bf6e54ffe417401c0cdef227648c4b07b48931b335cf3128017a64', 'code_bytes': 16344, 'chain_bytes': 16416, 'DMA_protocol_bytes': 0, 'VIF_protocol_bytes': 72, 'EE_chain_begin': 2903024, 'EE_chain_end': 2919440, 'program_sha256': '6f4ce804a09996de0d189ac0dfa32cd21c1a066ab1efa637df055e4487099e9e', 'chain_sha256': '6b2adce21f6b37e7529e34ecf9a21bd4fe3bf0521fc472914097f6bec1f3b41a', 'functions': None, 'original_function_count_complete': False, 'authored_source_partitions': [{'name': 'mesh_compose_transform', 'VU_byte_begin': 0, 'bytes': 832}, {'name': 'mesh_prepare_light_basis', 'VU_byte_begin': 832, 'bytes': 896}, {'name': 'mesh_restore_previous_packet', 'VU_byte_begin': 1728, 'bytes': 192}, {'name': 'mesh_project_vertices', 'VU_byte_begin': 1920, 'bytes': 1456}, {'name': 'mesh_classify_triangle', 'VU_byte_begin': 3376, 'bytes': 200}, {'name': 'mesh_adjust_uv', 'VU_byte_begin': 3576, 'bytes': 432}, {'name': 'mesh_add_matrix_channels', 'VU_byte_begin': 4008, 'bytes': 928}, {'name': 'mesh_toggle_adc', 'VU_byte_begin': 4936, 'bytes': 144}, {'name': 'mesh_shade_cubic', 'VU_byte_begin': 5080, 'bytes': 912}, {'name': 'mesh_shade_dynamic', 'VU_byte_begin': 5992, 'bytes': 912}, {'name': 'mesh_modulate_material', 'VU_byte_begin': 6904, 'bytes': 760}, {'name': 'mesh_skin_positions', 'VU_byte_begin': 7664, 'bytes': 680}, {'name': 'mesh_skin_normals_positions', 'VU_byte_begin': 8344, 'bytes': 984}, {'name': 'mesh_kick_packet_pair', 'VU_byte_begin': 9328, 'bytes': 184}, {'name': 'mesh_cull_polygon', 'VU_byte_begin': 9512, 'bytes': 192}, {'name': 'mesh_clip_polygon_plane', 'VU_byte_begin': 9704, 'bytes': 464}, {'name': 'mesh_collect_unique_xy', 'VU_byte_begin': 10168, 'bytes': 248}, {'name': 'mesh_clip_project_polygon', 'VU_byte_begin': 10416, 'bytes': 1008}, {'name': 'mesh_emit_clipped_triangles', 'VU_byte_begin': 11424, 'bytes': 728}, {'name': 'mesh_clip_outline_plane', 'VU_byte_begin': 12152, 'bytes': 328}, {'name': 'mesh_sort_clip_outline', 'VU_byte_begin': 12480, 'bytes': 928}, {'name': 'mesh_scale_packet_alpha', 'VU_byte_begin': 13408, 'bytes': 56}, {'name': 'mesh_dispatch_previous', 'VU_byte_begin': 13464, 'bytes': 152}, {'name': 'mesh_debug_acknowledge', 'VU_byte_begin': 13616, 'bytes': 80}, {'name': 'mesh_inverse_normal_matrix', 'VU_byte_begin': 13696, 'bytes': 184}, {'name': 'mesh_idle', 'VU_byte_begin': 13880, 'bytes': 16}, {'name': 'mesh_delay_and_kick', 'VU_byte_begin': 13896, 'bytes': 136}, {'name': 'mesh_draw_primary', 'VU_byte_begin': 14032, 'bytes': 1304}, {'name': 'mesh_draw_secondary', 'VU_byte_begin': 15336, 'bytes': 400}, {'name': 'mesh_resume_secondary_first', 'VU_byte_begin': 15736, 'bytes': 96}, {'name': 'mesh_resume_secondary_pair', 'VU_byte_begin': 15832, 'bytes': 120}, {'name': 'mesh_resume_secondary_clip', 'VU_byte_begin': 15952, 'bytes': 104}, {'name': 'mesh_draw_fast_transform', 'VU_byte_begin': 16056, 'bytes': 72}, {'name': 'mesh_draw_fast_restore', 'VU_byte_begin': 16128, 'bytes': 72}, {'name': 'mesh_draw_fast_ready', 'VU_byte_begin': 16200, 'bytes': 56}, {'name': 'mesh_draw_secondary_ready', 'VU_byte_begin': 16256, 'bytes': 16}, {'name': 'mesh_flush_pending', 'VU_byte_begin': 16272, 'bytes': 72}], 'additional_entries': {'2576': 'mesh_project_vertices_continue', '14168': 'mesh_draw_primary_restore', '14240': 'mesh_draw_primary_ready', '14280': 'mesh_draw_primary_after_transform'}, 'source_partition_count': 37, 'aliases_count_as_additional_functions': False, 'runtime_scope': 'Selected6755alarm/CID2F accepted initialized-frame predicate only, enabled16/14 palettes/camera0/visibility/stamps/validbuffers/queues/DMA/cache/null36B330 optionalclient; original startup4/4 mask0mode0 and mainflags8 finalmode0/cycle1/1, with no universal arbitrary packet or coldboot observation.', 'dynamic_REFS_source_credit': 0, 'initialized_data_bytes': 0, 'BSS_bytes': 0, 'allocated_relocations': 0, 'nonallocated_overlay_R32_fields': 16, 'full_source_relink_complete': False}
EXPECTED_EVIDENCE={'docs/evidence/vu_mesh_selected_main_launch.json': '5d1138450d0d90373b0d2f6b79e015aaed5c295601c206105300a7eeadd1fa2e', 'docs/evidence/vu_mesh_normal_state_predecessor.json': '8a04fd892a6659881cec984345355e766a2d4c83fa0a4bd314f46cc0bc59d036', 'docs/evidence/vu_mesh_accepted_frame_state.json': '03e9744bcfa085d1b0a81d9c64affea78a07f545fcaf00c30241b48296e8c3f0', 'docs/evidence/vu_mesh_source_peer_review.json': '155a355c8394c50187c3720b04ced1e60bea5243fa7971dbfea4e02c3acc5e01', 'docs/evidence/vu_mesh_parent_review.json': '994ddbac551fda7b5e8931ad48415f0827df8d1fadf19315e6d054dc680bb14e'}
ORIGINAL_SHA='ce817858306efd711f08bbc14f393455280119cb00b894bdc9fb1fa47bcbb338'
PROVENANCE_SHA='2199c34122dcb130521cbc1690a2a3f996cd9f59f1c4886055a88ed4354a1ea7'
ROLES={'functions':EXPECTED_COMPONENT['authored_source_partitions'],'genuine_additional_entries_not_duplicate_functions':EXPECTED_COMPONENT['additional_entries']}

def need(condition,message):
    if not condition:raise ValueError(message)
def receipt(path):return renderer.file_receipt(Path(path).resolve(),ROOT)
def sha(data):return hashlib.sha256(data).hexdigest()
def output_path(output):
    p=Path(output).resolve()
    need(any(p==a or p.is_relative_to(a) for a in [ROOT/'build/vu/mesh',ROOT/'build/vu/extra/testing',ROOT/'build/game_middle/vu376118843_integration_prep_20261015']),'Mesh output escapes its maintained or granted private tree')
    return p
def validate_manifest(m):
    need(m.get('schema')==1 and m.get('kind')=='mandatory-fifth-complete-readable-native-VU-mesh-component','Missing mandatory complete mesh owner')
    need(m.get('component')==EXPECTED_COMPONENT,'Wrong whole mesh ownership, code/control or unknown function-count marker')
    need(m.get('known_original_function_count_from_existing_four')==19 and 'new_original_function_count' in m and m['new_original_function_count'] is None,'Authored37 partitions cannot become an original function count')
    need(m.get('existing_four_owners_mandatory') is True,'Missing prior four mandatory source owners')
    need(m.get('original_sha256')==ORIGINAL_SHA and m.get('original_unique_program_count')==9 and m.get('original_unique_program_code_bytes')==50032 and m.get('original_nonallocated_zero_shadow_count')==29,'Wrong original family denominator or shadow domain')
    need(m.get('evidence_hashes')==EXPECTED_EVIDENCE and m.get('portable_provenance_sha256')==PROVENANCE_SHA,'Missing closed source/input/tool evidence')
    need(all(m.get(k)==0 for k in ['initialized_data_bytes','BSS_bytes','EE_C_CPP_functions_delta','EE_C_CPP_code_bytes_delta']),'False EE/data source credit')
    need(all(m.get(k) is False for k in ['historical_original_compiler_identity_confirmed','live_hardware_observed','universal_asset_or_predecessor_domain_claim','full_source_relink_complete']),'Unsupported universal runtime/compiler/relink claim')
def required_dependencies():
    return ['config/vu_mesh_sources.json',EXPECTED_COMPONENT['source'],EXPECTED_COMPONENT['chain_source'],*EXPECTED_EVIDENCE,'tools/vu_mesh_build.py','tools/vu_mesh_native.py','tools/test_vu_mesh.py']
def original_input_ranges(e,documents):
    records=[];occurrences=[]
    count_keys=['bytes','complete_original_bytes','entire_original_bytes','complete_bytes','whole_bytes']
    hash_keys=['original_sha256','sha256','whole_sha256']
    hex_keys=['original_bytes_hex','raw_original_hex','original_hex','original_bytes_hex_input_only','whole_original_hex_input_only']
    def visit(v,found):
        if isinstance(v,list):
            for x in v:visit(x,found)
        elif isinstance(v,dict):
            address=v.get('address',v.get('EE_begin'))
            sizes=[v[k] for k in count_keys if k in v]
            if address is not None and sizes:
                need(all(type(n) is int and n>0 for n in sizes) and len(set(sizes))==1,'Missing/ambiguous complete original input size')
                n=sizes[0];a=int(address,0) if isinstance(address,str) else address
                need(type(a) is int and a>=0,'Missing complete original input address')
                hashes=[v[k] for k in hash_keys if k in v]
                need(bool(hashes) and len(set(hashes))==1,'Missing/ambiguous full original input fingerprint')
                data=e.at_vram(a,n);h=sha(data)
                need(h==hashes[0],'Original selected frame/body/table input changed')
                for k in hex_keys:
                    if k in v:need(bytes.fromhex(v[k])==data,'Original complete input hex/size changed')
                found.append((a,n,h))
            for x in v.values():visit(x,found)
    for d in documents:
        found=[];visit(d,found);occurrences.append(len(found));records+=found
    need(occurrences==[77,17,30,0,29],'Incomplete whole original selected launch/state/parent support inventory')
    need(bool(records),'Missing full original selected input support')
    return sorted(set(records))
def checked_manifest(bundle=DEFAULT_BUNDLE):
    bundle=Path(bundle).resolve();mp=renderer.contained(bundle,'config/vu_mesh_sources.json');m=json.loads(mp.read_bytes());validate_manifest(m)
    e,_,_,programs=renderer.original_mapping();original=next(p for p in programs if p['family_file_name_hash']=='376118843')
    program=b''.join(e.at_vram(c['EE_payload_begin'],c['code_bytes']) for c in original['chunks']);chain=e.at_vram(0x2c4bf0,16416)
    need(original['VU_bytes']==16344 and sha(program)==EXPECTED_COMPONENT['program_sha256'] and sha(chain)==EXPECTED_COMPONENT['chain_sha256'],'Wrong whole eight-chunk original program/upload')
    deps={};docs=[]
    for rel in required_dependencies():
        p=renderer.contained(bundle,rel);deps[p.relative_to(ROOT).as_posix()]=sha(p.read_bytes())
        if rel in EXPECTED_EVIDENCE:need(sha(p.read_bytes())==EXPECTED_EVIDENCE[rel],'Closed qualified input/source packet changed');docs.append(json.loads(p.read_bytes()))
    for key,pin in [('source','source_sha256'),('chain_source','chain_source_sha256')]:
        p=renderer.contained(bundle,EXPECTED_COMPONENT[key]);need(sha(p.read_bytes())==EXPECTED_COMPONENT[pin],'Complete readable mesh source changed')
        need(not any(t in p.read_text().lower() for t in ['.word','.byte','.long','.quad','.incbin','.org','.space']),'Raw original preservation cannot be source')
    source=renderer.contained(bundle,EXPECTED_COMPONENT['source']).read_text();wrapper=renderer.contained(bundle,EXPECTED_COMPONENT['chain_source']).read_text()
    need('.include' not in source and wrapper.count('.include "mesh_program.vsm"')==1 and wrapper.count('mpg 0,*')==1 and wrapper.count('vifnop')==2,'Incomplete whole native mesh algorithm/upload recipe')
    accepted=next(d for d in docs if d.get('status','').startswith('PASS_QUALIFIED_ORIGINAL_SELECTED_ACCEPTED_FRAME_STATE_CLOSURE'))
    need(type(accepted['scoped_input_blockers']) is list and accepted['scoped_input_blockers']==[] and accepted['startup_literal_cycle']=='4/4' and accepted['later_selected_packet_cycle']=='1/1' and accepted['selected_packet_end_mode']==0,'Open/false selected accepted-frame state scope')
    need(accepted['universal_arbitrary_packet_exclusion_claim'] is False and accepted['universal_CID_asset_or_lifetime_claim'] is False and accepted['live_hardware_or_EE_VU_execution'] is False,'Unqualified original hardware/asset domain')
    original_inputs=original_input_ranges(e,docs)
    provenance=ROOT/'tools/third_party/dvp/provenance.json';need(sha(provenance.read_bytes())==PROVENANCE_SHA,'Changed installed native tool profile')
    deps[provenance.relative_to(ROOT).as_posix()]=PROVENANCE_SHA
    for r in json.loads(provenance.read_bytes())['files']:
        p=renderer.contained(ROOT,r['path']);need(p.stat().st_size==r['bytes'] and sha(p.read_bytes())==r['sha256'],'Pinned native tool/runtime changed');deps[r['path']]=r['sha256']
    for rel in ['tools/common.py','tools/vu_build.py','config/vu_original_programs.json']:
        p=renderer.contained(ROOT,rel);deps[rel]=sha(p.read_bytes())
    return m,e,{'program':program,'chain':chain},original_inputs,dict(sorted(deps.items()))
def native_profile():
    return {'target':'dvp','version':'GNU Binutils 2.45.1','provenance':receipt(ROOT/'tools/third_party/dvp/provenance.json'),'assembler':receipt(ROOT/'tools/third_party/dvp/bin/dvp-as.exe'),'historical_original_compiler_identity_confirmed':False}

def native_command(kind,bundle,out,temp):
    need(kind in ['program','chain'],'Foreign native component')
    rel=EXPECTED_COMPONENT['source' if kind=='program' else 'chain_source']
    p=renderer.contained(bundle,rel);flags=['--defsym','VU_NATIVE_STANDALONE=1'] if kind=='program' else []
    return {'argv':[str(ROOT/'tools/third_party/dvp/bin/dvp-as.exe'),'-I',str(p.parent),*flags,'-o',str(out/(kind+'.o')),str(p)],
            'cwd':str(p.parent),'TEMP':str(temp),'TMP':str(temp),'TMPDIR':str(temp),
            'profile':native_profile(),'exit_code':0,'stdout':'','stderr':''}

def validate_native_record(item,kind,bundle,out,job):
    need(type(job) is str and str(uuid.UUID(job))==job,'Invalid unique native job identity')
    temp=out/('temp_'+job)
    need(temp.is_dir() and temp.resolve().parent==out,'Missing/outside native temporary job directory')
    rel=EXPECTED_COMPONENT['source' if kind=='program' else 'chain_source'];p=renderer.contained(bundle,rel)
    expected_sha=EXPECTED_COMPONENT['source_sha256' if kind=='program' else 'chain_source_sha256']
    need(item.get('source_sha256')==expected_sha==sha(p.read_bytes()) and item.get('source')==receipt(p),'Stale/foreign actual native source signature')
    need(item.get('actual_native_command')==native_command(kind,bundle,out,temp),'False/stale native argv/cwd/profile/exit/stdout/stderr/TEMP identity')
    need(item.get('native_job')==job,'Mismatched native component job identity')

def validate_report(r,bundle,out,expected,inputs,deps):
    need(r.get('kind')=='complete-fifth-readable-native-VU-mesh-source-component' and r.get('bundle_root')==bundle.relative_to(ROOT).as_posix() and r.get('component')==EXPECTED_COMPONENT,'Foreign/missing mesh current report')
    need(r.get('dependency_hashes')==deps and r.get('complete_original_input_ranges')==[list(x) for x in inputs],'Stale source/native/input report')
    need(set(r['native_components'])=={'program','chain'},'Missing/extra native mesh component')
    job=r.get('native_job')
    for kind in ['program','chain']:
        item=r['native_components'][kind];validate_native_record(item,kind,bundle,out,job)
        need(set(item['files'])=={kind+'.o',kind+'.bin'},'Missing/extra complete native file')
        for n in [kind+'.o',kind+'.bin']:need(item['files'][n]==receipt(out/n),'Whole current native output fingerprint changed')
        proof=strict_native((out/(kind+'.o')).read_bytes(),kind,expected[kind],ROLES)
        need(item['native_proof']==proof and (out/(kind+'.bin')).read_bytes()==expected[kind],'False whole native/initialized-section/relocation proof')
    log={'native_job':job,'commands':[{'kind':k,'source':r['native_components'][k]['source'],'source_sha256':r['native_components'][k]['source_sha256'],'actual_native_command':r['native_components'][k]['actual_native_command']} for k in ['program','chain']]}
    need(r.get('native_command_log')==receipt(out/'actual_native_commands.json') and json.loads((out/'actual_native_commands.json').read_bytes())==log,'Missing/forged actual native command log')
    need(r.get('verified_original_function_count','missing') is None and r.get('source_partitions_not_original_functions')==37 and r.get('initialized_data_bytes')==r.get('BSS_bytes')==r.get('dynamic_REFS_source_credit')==0,'False routine/data/dynamic-input source count')
    need(all(r.get(k) is False for k in ['historical_original_compiler_identity_confirmed','full_source_relink_complete','live_runtime_execution_observed','unknown_predecessor_or_universal_asset_domain_claim']),'False compiler/universal/runtime/relink claim')

def current_report(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT):
    bundle=Path(bundle).resolve();out=output_path(output);m,e,expected,inputs,deps=checked_manifest(bundle);r=json.loads((out/REPORT_NAME).read_bytes())
    validate_report(r,bundle,out,expected,inputs,deps)
    return {**r,'freshness':'CURRENT_WHOLE16344_MESH_AND16416_CHAIN_QUALIFIED_ACCEPTED_FRAME_VERIFIED'}

def run(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT,fresh=False):
    bundle=Path(bundle).resolve();out=output_path(output)
    if out.exists() and any(out.iterdir()):
        need(not fresh,'Fresh native mesh proof needs empty output')
        return current_report(bundle,out)
    m,e,expected,inputs,deps=checked_manifest(bundle);out.mkdir(parents=True,exist_ok=True);job=str(uuid.uuid4());tmp=out/('temp_'+job);tmp.mkdir();env=os.environ.copy()
    for key in ['TEMP','TMP','TMPDIR']:env[key]=str(tmp)
    native={};log={'native_job':job,'commands':[]}
    for kind in ['program','chain']:
        rel=EXPECTED_COMPONENT['source' if kind=='program' else 'chain_source'];p=renderer.contained(bundle,rel);actual=native_command(kind,bundle,out,tmp)
        try:
            result=subprocess.run(actual['argv'],cwd=actual['cwd'],env=env,capture_output=True,text=True,timeout=30)
            actual.update(exit_code=result.returncode,stdout=result.stdout,stderr=result.stderr)
        except Exception as err:
            diagnostics={k:({'raw_bytes_hex':getattr(err,k).hex()} if isinstance(getattr(err,k,None),bytes) else getattr(err,k,None)) for k in ['stdout','stderr']}
            actual.update(exit_code=None,**diagnostics,exception={'type':type(err).__name__,'message':str(err)})
            log['commands'].append({'kind':kind,'source':receipt(p),'source_sha256':sha(p.read_bytes()),'actual_native_command':actual})
            (out/'actual_native_commands.json').write_text(json.dumps(log,indent=2)+'\n',encoding='utf-8')
            raise
        log['commands'].append({'kind':kind,'source':receipt(p),'source_sha256':sha(p.read_bytes()),'actual_native_command':actual})
        (out/'actual_native_commands.json').write_text(json.dumps(log,indent=2)+'\n',encoding='utf-8')
        need(actual==native_command(kind,bundle,out,tmp),'Pinned native mesh assembly failed or emitted unexpected diagnostics')
        proof=strict_native((out/(kind+'.o')).read_bytes(),kind,expected[kind],ROLES);elf=Elf32((out/(kind+'.o')).read_bytes());(out/(kind+'.bin')).write_bytes(elf.section_data(elf.section('.vutext')))
        native[kind]={'files':{n:receipt(out/n) for n in [kind+'.o',kind+'.bin']},'native_proof':proof,'actual_native_command':actual,'source_sha256':sha(p.read_bytes()),'source':receipt(p),'native_job':job}
    r={'kind':'complete-fifth-readable-native-VU-mesh-source-component','bundle_root':bundle.relative_to(ROOT).as_posix(),'component':EXPECTED_COMPONENT,'dependency_hashes':deps,'complete_original_input_ranges':inputs,'native_components':native,'native_job':job,'native_command_log':receipt(out/'actual_native_commands.json'),'verified_original_function_count':None,'source_partitions_not_original_functions':37,'initialized_data_bytes':0,'BSS_bytes':0,'dynamic_REFS_source_credit':0,'historical_original_compiler_identity_confirmed':False,'full_source_relink_complete':False,'live_runtime_execution_observed':False,'unknown_predecessor_or_universal_asset_domain_claim':False}
    (out/REPORT_NAME).write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    return current_report(bundle,out)
def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--fresh',action='store_true');p.add_argument('--check',action='store_true');a=p.parse_args();r=current_report(a.bundle_root,a.output) if a.check else run(a.bundle_root,a.output,a.fresh);print(json.dumps({'status':'PASS','component':r['component'],'freshness':r['freshness'],'original_function_count':None}))
if __name__=='__main__':main()
