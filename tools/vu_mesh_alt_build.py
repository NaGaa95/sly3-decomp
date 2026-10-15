"""Mandatory complete alternate mesh VU component. Existing five owners remain mandatory."""
import argparse,json,struct,subprocess,sys,os,uuid,copy,hashlib
from pathlib import Path
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve();ROOT=next(p for p in HERE.parents if (p/'disc/SCUS_974.64').is_file())
sys.path.insert(0,str(ROOT/'tools'))
import vu_build as renderer
from common import Elf32
from vu_mesh_alt_native import strict_native
DEFAULT_BUNDLE=HERE.parents[1]
DEFAULT_OUTPUT=ROOT/'build/vu/mesh_alt'
REPORT_NAME='vu_mesh_alt_report.json'
EXPECTED_COMPONENT={'family': '1504484043', 'processor': 'VU1', 'source': 'src/vu/mesh_alt/mesh_program.vsm', 'chain_source': 'src/vu/mesh_alt/mesh_upload.vif', 'source_sha256': 'fda759b27aaccacb42d0b2a8ccce89ecf8d9decc5cfd48b0e07d943facf1f37a', 'chain_source_sha256': '39983bf0dc4cab3582dc8e7b70fddd5237d51f9db5b661e7560a4f78d1d71429', 'code_bytes': 15128, 'chain_bytes': 15200, 'DMA_protocol_bytes': 0, 'VIF_protocol_bytes': 72, 'EE_chain_begin': 2919456, 'EE_chain_end': 2934656, 'program_sha256': 'e6327c2dd8e47b976474cc5c0d2135f1262a4f14264b527fa3ff5e4d41360d89', 'chain_sha256': '9d42e58f049c7b406c5da89bfb9cb1b370df6eac153b569c384e12b42bf0e931', 'functions': None, 'original_function_count_complete': False, 'authored_source_partitions': [{'name': 'mesh_compose_transform', 'VU_byte_begin': 0, 'bytes': 832}, {'name': 'mesh_prepare_light_basis', 'VU_byte_begin': 832, 'bytes': 896}, {'name': 'mesh_restore_previous_packet', 'VU_byte_begin': 1728, 'bytes': 192}, {'name': 'mesh_project_vertices', 'VU_byte_begin': 1920, 'bytes': 1456}, {'name': 'mesh_classify_triangle', 'VU_byte_begin': 3376, 'bytes': 200}, {'name': 'mesh_adjust_uv', 'VU_byte_begin': 3576, 'bytes': 432}, {'name': 'mesh_add_matrix_channels', 'VU_byte_begin': 4008, 'bytes': 928}, {'name': 'mesh_toggle_adc', 'VU_byte_begin': 4936, 'bytes': 144}, {'name': 'mesh_shade_cubic', 'VU_byte_begin': 5080, 'bytes': 912}, {'name': 'mesh_shade_dynamic', 'VU_byte_begin': 5992, 'bytes': 912}, {'name': 'mesh_modulate_material', 'VU_byte_begin': 6904, 'bytes': 760}, {'name': 'mesh_skin_positions', 'VU_byte_begin': 7664, 'bytes': 680}, {'name': 'mesh_skin_normals_positions', 'VU_byte_begin': 8344, 'bytes': 984}, {'name': 'mesh_kick_packet_pair', 'VU_byte_begin': 9328, 'bytes': 184}, {'name': 'mesh_cull_polygon', 'VU_byte_begin': 9512, 'bytes': 192}, {'name': 'mesh_clip_polygon_plane', 'VU_byte_begin': 9704, 'bytes': 464}, {'name': 'mesh_collect_unique_xy', 'VU_byte_begin': 10168, 'bytes': 248}, {'name': 'mesh_clip_project_polygon', 'VU_byte_begin': 10416, 'bytes': 1008}, {'name': 'mesh_emit_clipped_triangles', 'VU_byte_begin': 11424, 'bytes': 728}, {'name': 'mesh_clip_outline_plane', 'VU_byte_begin': 12152, 'bytes': 328}, {'name': 'mesh_sort_clip_outline', 'VU_byte_begin': 12480, 'bytes': 928}, {'name': 'mesh_scale_packet_alpha', 'VU_byte_begin': 13408, 'bytes': 56}, {'name': 'mesh_dispatch_previous', 'VU_byte_begin': 13464, 'bytes': 152}, {'name': 'mesh_debug_acknowledge', 'VU_byte_begin': 13616, 'bytes': 80}, {'name': 'mesh_inverse_normal_matrix', 'VU_byte_begin': 13696, 'bytes': 184}, {'name': 'mesh_idle', 'VU_byte_begin': 13880, 'bytes': 16}, {'name': 'mesh_alt_draw_primary', 'VU_byte_begin': 13896, 'bytes': 384}, {'name': 'mesh_alt_draw_secondary', 'VU_byte_begin': 14280, 'bytes': 432}, {'name': 'mesh_alt_resume_alpha', 'VU_byte_begin': 14712, 'bytes': 344}, {'name': 'mesh_alt_flush_pending', 'VU_byte_begin': 15056, 'bytes': 72}], 'additional_entries': {'2576': 'mesh_project_vertices_continue'}, 'source_partition_count': 30, 'aliases_count_as_additional_functions': False, 'actual_direct_entries': {'3638': 'mesh_idle', '3648': 'mesh_alt_draw_primary', '37c8': 'mesh_alt_draw_secondary', '3ad0': 'mesh_alt_flush_pending'}, 'runtime_scope': 'Only actual mode0 CID2F/state10 node0 laser_beam_render_red witness, accepted initialized frame/visibility/camera0/12+7 palettes/normal startup4/4 or completed1/1/mode0/header/page/queue/cache/IRQ/DMA/null36B330 lifetime predicates. No state14 witness, arbitrary packet, coldboot, class universality or livehardware execution.', 'dynamic_REFS_source_credit': 0, 'initialized_data_bytes': 0, 'BSS_bytes': 0, 'allocated_relocations': 0, 'nonallocated_overlay_R32_fields': 16, 'full_source_relink_complete': False}
EXPECTED_EVIDENCE={'docs/evidence/vu_mesh_alt_selected_launch.json': '439eeccb388a848499e144c175ff7d538373aaf454c80f5d750dc0917fe2c4ca', 'docs/evidence/vu_mesh_alt_parent_review.json': '17f1f137432184b8fb329de11239740e6183eb92d2b8b04c8146f2869753f8a0', 'docs/evidence/vu_mesh_alt_source_peer_review.json': '4688f39be0875c50f0804fa5e0344aa3130be3ada12ac4dc93f2a26ca71561a3', 'docs/evidence/vu_mesh_alt_launch_driver_source.py.txt': '3a8be18a68b986e52db0cfdfd9e2badd674bfdce11c9c64aed71de3c00e58806', 'docs/evidence/vu_mesh_alt_source_adjustment.json': '18e05b6d9aa04b1f8d060a3dba92c04e47ac1c72107de6b026bbdaa9c3c42bbd'}
ORIGINAL_SHA='ce817858306efd711f08bbc14f393455280119cb00b894bdc9fb1fa47bcbb338'
PROVENANCE_SHA='2199c34122dcb130521cbc1690a2a3f996cd9f59f1c4886055a88ed4354a1ea7'
ROLES={'source_partitions':EXPECTED_COMPONENT['authored_source_partitions'],'native_loop_labels_not_new_functions':EXPECTED_COMPONENT['additional_entries']}

def need(condition,message):
    if not condition:raise ValueError(message)
def receipt(path):return renderer.file_receipt(Path(path).resolve(),ROOT)
def sha(data):return hashlib.sha256(data).hexdigest()
def output_path(output):
    p=Path(output).resolve()
    need(any(p==a or p.is_relative_to(a) for a in [ROOT/'build/vu/mesh_alt',ROOT/'build/vu/extra/testing',ROOT/'build/game_middle/vu1504484043_integration_prep_20261015']),'Mesh output escapes its maintained or granted private tree')
    return p
def validate_manifest(m):
    need(m.get('schema')==1 and m.get('kind')=='mandatory-sixth-complete-readable-native-VU-mesh-alt-component','Missing mandatory complete mesh owner')
    need(m.get('component')==EXPECTED_COMPONENT,'Wrong whole mesh ownership, code/control or unknown function-count marker')
    need(m.get('known_original_function_count_from_existing_five')==19 and 'new_original_function_count' in m and m['new_original_function_count'] is None,'Authored30 partitions cannot become an original function count')
    need(m.get('existing_five_owners_mandatory') is True,'Missing prior five mandatory source owners')
    need(m.get('original_sha256')==ORIGINAL_SHA and m.get('original_unique_program_count')==9 and m.get('original_unique_program_code_bytes')==50032 and m.get('original_nonallocated_zero_shadow_count')==29,'Wrong original family denominator or shadow domain')
    need(m.get('evidence_hashes')==EXPECTED_EVIDENCE and m.get('portable_provenance_sha256')==PROVENANCE_SHA,'Missing closed source/input/tool evidence')
    need(all(m.get(k)==0 for k in ['initialized_data_bytes','BSS_bytes','EE_C_CPP_functions_delta','EE_C_CPP_code_bytes_delta']),'False EE/data source credit')
    need(all(m.get(k) is False for k in ['historical_original_compiler_identity_confirmed','live_hardware_observed','universal_asset_or_predecessor_domain_claim','full_source_relink_complete']),'Unsupported universal runtime/compiler/relink claim')
def required_dependencies():
    return ['config/vu_mesh_alt_sources.json',EXPECTED_COMPONENT['source'],EXPECTED_COMPONENT['chain_source'],*EXPECTED_EVIDENCE,'tools/vu_mesh_alt_build.py','tools/vu_mesh_alt_native.py','tools/test_vu_mesh_alt.py']
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
    need(occurrences==[69,19,0,0],'Incomplete whole original selected launch/state/parent support inventory')
    need(bool(records),'Missing full original selected input support')
    return sorted(set(records))
def checked_manifest(bundle=DEFAULT_BUNDLE):
    bundle=Path(bundle).resolve();mp=renderer.contained(bundle,'config/vu_mesh_alt_sources.json');m=json.loads(mp.read_bytes());validate_manifest(m)
    e,_,_,programs=renderer.original_mapping();original=next(p for p in programs if p['family_file_name_hash']=='1504484043')
    program=b''.join(e.at_vram(c['EE_payload_begin'],c['code_bytes']) for c in original['chunks']);chain=e.at_vram(0x2c8c20,15200)
    need(original['VU_bytes']==15128 and sha(program)==EXPECTED_COMPONENT['program_sha256'] and sha(chain)==EXPECTED_COMPONENT['chain_sha256'],'Wrong whole eight-chunk original program/upload')
    deps={};docs=[]
    for rel in required_dependencies():
        p=renderer.contained(bundle,rel);deps[p.relative_to(ROOT).as_posix()]=sha(p.read_bytes())
        if rel in EXPECTED_EVIDENCE:
            need(sha(p.read_bytes())==EXPECTED_EVIDENCE[rel],'Closed qualified input/source/driver packet changed')
            if rel.endswith('.json'):docs.append(json.loads(p.read_bytes()))
    for key,pin in [('source','source_sha256'),('chain_source','chain_source_sha256')]:
        p=renderer.contained(bundle,EXPECTED_COMPONENT[key]);need(sha(p.read_bytes())==EXPECTED_COMPONENT[pin],'Complete readable mesh source changed')
        need(not any(t in p.read_text().lower() for t in ['.word','.byte','.long','.quad','.incbin','.org','.space']),'Raw original preservation cannot be source')
    source=renderer.contained(bundle,EXPECTED_COMPONENT['source']).read_text();wrapper=renderer.contained(bundle,EXPECTED_COMPONENT['chain_source']).read_text()
    need('.include' not in source and wrapper.count('.include "mesh_program.vsm"')==1 and wrapper.count('mpg 0,*')==1 and wrapper.count('vifnop')==2,'Incomplete whole native mesh algorithm/upload recipe')
    accepted=docs[0];parent=docs[1];adjustment=docs[3]
    need(accepted['status']=='PASS_QUALIFIED_COMPLETE_ORIGINAL_STOCK_STATE10_LAUNCH_PAGE_AND_TRANSPORT_PARENT_REVIEW_REQUIRED' and len(accepted['complete_original_support_reverified_by_reference'])==67,'Wrong/open bounded stock state10 original input proof')
    need(parent['parent_review_status']=='PASS_COMPLETE_SOURCE_NATIVE_AND_BOUNDED_ACTUAL_STATE10_RUNTIME_ELIGIBLE_FOR_MAINTAINED_INTEGRATION' and parent['original_function_count'] is None,'Missing final qualified root source/native/runtime acceptance')
    need(adjustment['final_source_sha256']==EXPECTED_COMPONENT['source_sha256'] and adjustment['all_noncomment_source_bytes_identical'] is True and len(adjustment['changes'])==2,'Unproved final readable source comment adjustment')
    # Rehash actual frozen packet/parser/driver inputs, not a mutable public VU map.
    for row in accepted['compact_frozen_inputs']:
        p=renderer.contained(ROOT,row['path']);need(p.stat().st_size==row['bytes'] and sha(p.read_bytes())==row['sha256'],'Frozen actual stock packet/driver/source input changed');deps[row['path']]=row['sha256']
    stock=accepted['actual_stock'];body=bytes.fromhex(stock['whole1594_body_original_hex']);fr=stock['factory_record'];raw=ROOT/'build/asset_catalog/level_tag_05.decoded.bin'
    need(len(body)==1594 and sha(body)==fr['original_sha256'] and raw.read_bytes()[fr['body_range'][0]:fr['body_range'][1]]==body,'Entire concrete actual stock body changed')
    need(len(accepted['two_actual_page_control_topologies'])==2 and len(accepted['accepted_live_predicates'])==6 and stock['selected_full_reader_geometry']['geometry']['nodes'][0]['flag']==10,'Unsupported actual page/state10/accepted-lifetime domain')
    need(accepted['original_VU_control_qualification']['unique_nonzero_callback_producer']['target_bytePC']==0x3978 and accepted['original_VU_control_qualification']['clear_bytePC']==0x3aa0 and accepted['original_VU_control_qualification']['teardown_three_dispatches_are_one_callback_then_two_zero_reads'] is True,'Invented alternate callback protocol')
    original_inputs=original_input_ranges(e,docs)
    provenance=ROOT/'tools/third_party/dvp/provenance.json';need(sha(provenance.read_bytes())==PROVENANCE_SHA,'Changed installed native tool profile')
    deps[provenance.relative_to(ROOT).as_posix()]=PROVENANCE_SHA
    for r in json.loads(provenance.read_bytes())['files']:
        p=renderer.contained(ROOT,r['path']);need(p.stat().st_size==r['bytes'] and sha(p.read_bytes())==r['sha256'],'Pinned native tool/runtime changed');deps[r['path']]=r['sha256']
    for rel in ['tools/common.py','tools/vu_build.py','config/vu_original_programs.json','tools/vu_mesh_native.py']:
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
    need(r.get('kind')=='complete-sixth-readable-native-VU-mesh-alt-source-component' and r.get('bundle_root')==bundle.relative_to(ROOT).as_posix() and r.get('component')==EXPECTED_COMPONENT,'Foreign/missing mesh current report')
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
    need(r.get('verified_original_function_count','missing') is None and r.get('source_partitions_not_original_functions')==30 and r.get('initialized_data_bytes')==r.get('BSS_bytes')==r.get('dynamic_REFS_source_credit')==0,'False routine/data/dynamic-input source count')
    need(all(r.get(k) is False for k in ['historical_original_compiler_identity_confirmed','full_source_relink_complete','live_runtime_execution_observed','unknown_predecessor_or_universal_asset_domain_claim']),'False compiler/universal/runtime/relink claim')

def current_report(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT):
    bundle=Path(bundle).resolve();out=output_path(output);m,e,expected,inputs,deps=checked_manifest(bundle);r=json.loads((out/REPORT_NAME).read_bytes())
    validate_report(r,bundle,out,expected,inputs,deps)
    return {**r,'freshness':'CURRENT_WHOLE15128_MESH_ALT_AND15200_CHAIN_QUALIFIED_STATE10_ACCEPTED_FRAME_VERIFIED'}

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
    r={'kind':'complete-sixth-readable-native-VU-mesh-alt-source-component','bundle_root':bundle.relative_to(ROOT).as_posix(),'component':EXPECTED_COMPONENT,'dependency_hashes':deps,'complete_original_input_ranges':inputs,'native_components':native,'native_job':job,'native_command_log':receipt(out/'actual_native_commands.json'),'verified_original_function_count':None,'source_partitions_not_original_functions':30,'initialized_data_bytes':0,'BSS_bytes':0,'dynamic_REFS_source_credit':0,'historical_original_compiler_identity_confirmed':False,'full_source_relink_complete':False,'live_runtime_execution_observed':False,'unknown_predecessor_or_universal_asset_domain_claim':False}
    (out/REPORT_NAME).write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    return current_report(bundle,out)
def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--fresh',action='store_true');p.add_argument('--check',action='store_true');a=p.parse_args();r=current_report(a.bundle_root,a.output) if a.check else run(a.bundle_root,a.output,a.fresh);print(json.dumps({'status':'PASS','component':r['component'],'freshness':r['freshness'],'original_function_count':None}))
if __name__=='__main__':main()
