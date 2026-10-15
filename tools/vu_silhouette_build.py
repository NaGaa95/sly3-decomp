"""Ninth maintained silhouette component; qualified final parent eligibility, unknown original function count."""
import argparse,json,struct,subprocess,sys,os,uuid,copy,hashlib
from pathlib import Path
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve();ROOT=next(p for p in HERE.parents if (p/'disc/SCUS_974.64').is_file())
sys.path.insert(0,str(ROOT/'tools'))
import vu_build as renderer
from common import Elf32
from vu_silhouette_native import strict_native
DEFAULT_BUNDLE=HERE.parents[1]
DEFAULT_OUTPUT=ROOT/'build/vu/silhouette'
REPORT_NAME='vu_silhouette_report.json'
PARENT_REVIEW_SHA='d8c34a0cbc6b9b647db4d6c1fe3c9e6e66b952f97a424949b1c1e41e922ae278'
EXPECTED_COMPONENT={'family': '188058427', 'processor': 'VU1', 'source': 'src/vu/silhouette/silhouette_program.vsm', 'chain_source': 'src/vu/silhouette/silhouette_upload.vif', 'source_sha256': '532da52a1a99ba1f93d129b0bb8bfaf9b5297d565ead03bc39f4dbc18dae0ca3', 'chain_source_sha256': 'dfeb9643e6b063a6632f5ccfd07aba3ef2616e35241ac623a065e9090ad93958', 'code_bytes': 2336, 'chain_bytes': 2352, 'DMA_protocol_bytes': 0, 'VIF_protocol_bytes': 16, 'EE_chain_begin': 2891008, 'EE_chain_end': 2893360, 'program_sha256': 'e1d1b43db4cb71cb0f7c01d3628b3396107d0aaf4eedbfeced4916c9a1d8afa3', 'chain_sha256': '68628aa7782f554418326e4cba414bbf224beff8e0302eba74fdac344271589b', 'functions': None, 'original_function_count_complete': False, 'authored_source_partitions': [{'name': 'silhouette_idle', 'VU_byte_begin': 0, 'bytes': 16}, {'name': 'silhouette_debug_acknowledge', 'VU_byte_begin': 16, 'bytes': 80}, {'name': 'silhouette_prepare_depth', 'VU_byte_begin': 96, 'bytes': 192}, {'name': 'silhouette_copy_packet_bank', 'VU_byte_begin': 288, 'bytes': 192}, {'name': 'silhouette_skin_vertices', 'VU_byte_begin': 480, 'bytes': 480}, {'name': 'silhouette_project_vertices', 'VU_byte_begin': 960, 'bytes': 320}, {'name': 'silhouette_emit_edges', 'VU_byte_begin': 1280, 'bytes': 568}, {'name': 'silhouette_kick_packet', 'VU_byte_begin': 1848, 'bytes': 184}, {'name': 'silhouette_draw', 'VU_byte_begin': 2032, 'bytes': 120}, {'name': 'silhouette_compose_matrix', 'VU_byte_begin': 2152, 'bytes': 184}], 'additional_entries': {}, 'source_partition_count': 10, 'aliases_count_as_additional_functions': False, 'actual_direct_entries': {'0': 'silhouette_idle', '738': 'silhouette_kick_packet', '7f0': 'silhouette_draw'}, 'runtime_scope': 'Permitted normal unmasked VIF1 mode0 and equalcycle4/4 startup or1/1 predecessor; actualinitialized camera/scene/pose, validprojection/EFU operands, permittednull36B330optional-client route, successfulreal allocations, live retained geometry/frame storage through DMAwait, correctqueue/cache/IRQ/DMAC environment. Only actual enabled unskinned baseCID36 Bentley node56/cfg1/state8/15XYZ/28edgequads, additional disabled instance excluded; camera kind10 uses(2,2), both pages52/538. Finalq77 ambient/dead4ILW+4LQ and undefined inputW retained. No universal geometry, firstbank, class, arbitrary packet, all-readinitialized or live hardware theorem.', 'ambient_final_prefetch_not_source_initialized': True, 'dynamic_REFS_source_credit': 0, 'initialized_data_bytes': 0, 'BSS_bytes': 0, 'allocated_relocations': 0, 'nonallocated_overlay_R32_fields': 4, 'full_source_relink_complete': False}
EXPECTED_EVIDENCE={'docs/evidence/vu_silhouette_camera_original_addendum.json': '050c82fff78102e976412bc25398a267cdd14517b4205ee53f651e04b409de42', 'docs/evidence/vu_silhouette_cfg_selector_correction.json': 'd228b86cb2e5910b529ee2a54c5ffa252ec49df433b72f0a8ff3236c1ec3279d', 'docs/evidence/vu_silhouette_complete_original_inputs.json': '790e2825ff915157f128ab55b40cd0f113b7bde7d1c7321514abdf624edceecc', 'docs/evidence/vu_silhouette_original_runtime_review.json': 'a9e4061a771fad0178ec9ac185d962c106532906e016eb18578f5d51903631cf', 'docs/evidence/vu_silhouette_parent_review.json': 'd8c34a0cbc6b9b647db4d6c1fe3c9e6e66b952f97a424949b1c1e41e922ae278', 'docs/evidence/vu_silhouette_runtime_independent_peer.json': 'd294446f7108f7514b9c83725a7c7f86d2b0274bb7536673ac18251d31166af2', 'docs/evidence/vu_silhouette_source_native_peer.json': 'd779aa459eb6782862e9afd41ab1b7ef4e32dfbf293402a078d13593ad37d1ea', 'docs/evidence/vu_silhouette_source_qualification.json': 'ace0a31c11f4fac5c6d9bb2fbe776a609ca9f5d676d40d79feae7557c54a54f7'}
ORIGINAL_SHA='ce817858306efd711f08bbc14f393455280119cb00b894bdc9fb1fa47bcbb338'
PROVENANCE_SHA='2199c34122dcb130521cbc1690a2a3f996cd9f59f1c4886055a88ed4354a1ea7'
ROLES={'source_partitions':EXPECTED_COMPONENT['authored_source_partitions'],'native_loop_labels_not_new_functions':EXPECTED_COMPONENT['additional_entries']}

def need(condition,message):
    if not condition:raise ValueError(message)
def receipt(path):return renderer.file_receipt(Path(path).resolve(),ROOT)
def sha(data):return hashlib.sha256(data).hexdigest()
def output_path(output):
    p=Path(output).resolve();need(p==ROOT/'build/vu/silhouette','Silhouette output must be its exact canonical directory');return p
def validate_manifest(m):
    need(m.get('schema')==1 and m.get('kind')=='complete-readable-native-VU-silhouette-component','Missing complete silhouette source owner')
    need(m.get('component')==EXPECTED_COMPONENT,'Wrong whole silhouette ownership/code/control/unknown count')
    need(m.get('expected_prior_owner_count')==8 and m.get('existing_eight_owners_mandatory') is True and 'new_original_function_count' in m and m['new_original_function_count'] is None,'Authored10 partitions are not original functions; prior eight owners remain mandatory')
    need(m.get('prior_known_original_function_count')==19 and m.get('prior_unknown_original_function_count_programs')==['376118843','1504484043','188058715','376117691'],'Existing known19/four-unknown provenance changed')
    need(m.get('original_sha256')==ORIGINAL_SHA and m.get('original_unique_program_count')==9 and m.get('original_unique_program_code_bytes')==50032 and m.get('original_nonallocated_zero_shadow_count')==29,'Wrong original family/code/shadow denominator')
    need(m.get('evidence_hashes')==EXPECTED_EVIDENCE and m.get('portable_provenance_sha256')==PROVENANCE_SHA,'Missing closed source/input/tool evidence')
    need(all(m.get(k)==0 for k in ['initialized_data_bytes','BSS_bytes','EE_C_CPP_functions_delta','EE_C_CPP_code_bytes_delta']),'False EE/data source credit')
    need(all(m.get(k) is False for k in ['historical_original_compiler_identity_confirmed','live_hardware_observed','universal_asset_or_predecessor_domain_claim','full_source_relink_complete']),'Unsupported compiler/hardware/universal/relink claim')
def required_dependencies():
    return ['config/vu_silhouette_sources.json',EXPECTED_COMPONENT['source'],EXPECTED_COMPONENT['chain_source'],*EXPECTED_EVIDENCE,'tools/vu_silhouette_build.py','tools/vu_silhouette_native.py','tools/test_vu_silhouette.py']
def original_input_ranges(e,documents):
    records=[];counts=[];ck=['bytes','complete_original_bytes','entire_original_bytes','complete_bytes','whole_bytes','captured_bytes','input_window_bytes'];hk=['original_sha256','sha256','whole_sha256']
    hexkeys=['whole_original_hex_input_only','whole_original_hex','entire_original_hex','original_hex','original_bytes_hex']
    def walk(v,found):
        if isinstance(v,list):
            for x in v:walk(x,found)
        elif isinstance(v,dict):
            a=v.get('address',v.get('EE_begin'));ns=[v[k] for k in ck if k in v];hs=[v[k] for k in hk if k in v]
            if a is not None and ns and hs:
                need(all(type(n) is int and n>0 for n in ns) and len(set(ns))==1 and len(set(hs))==1,'Missing/ambiguous whole original range')
                a=int(a,0) if isinstance(a,str) else a;need(type(a) is int and a>=0,'Wrong complete original address');b=e.at_vram(a,ns[0]);need(sha(b)==hs[0],'Changed entire original support')
                for k in hexkeys:
                    if k in v:need(bytes.fromhex(v[k])==b,'Changed entire original capture hex')
                found.append((a,ns[0],sha(b)))
            for x in v.values():walk(x,found)
    for doc in documents:
        found=[];walk(doc,found);records+=found;counts.append(len(found))
    need(counts==[0,176,1,84,1,1,0],'Incomplete original source/runtime/correction inventory')
    return sorted(set(records))
def checked_manifest(bundle=DEFAULT_BUNDLE):
    need(PARENT_REVIEW_SHA is not None and EXPECTED_EVIDENCE.get('docs/evidence/vu_silhouette_parent_review.json')==PARENT_REVIEW_SHA,'Missing exact final bounded root eligibility')
    bundle=Path(bundle).resolve();m=json.loads(renderer.contained(bundle,'config/vu_silhouette_sources.json').read_bytes());validate_manifest(m)
    e,_,_,programs=renderer.original_mapping();o=next(p for p in programs if p['family_file_name_hash']=='188058427');program=b''.join(e.at_vram(c['EE_payload_begin'],c['code_bytes']) for c in o['chunks']);chain=e.at_vram(0x2c1d00,2352)
    need(o['VU_bytes']==2336 and sha(program)==EXPECTED_COMPONENT['program_sha256'] and sha(chain)==EXPECTED_COMPONENT['chain_sha256'],'Wrong complete2336/two-MPG2352 original upload')
    deps={};docs={}
    for rel in required_dependencies():
        p=renderer.contained(bundle,rel);deps[p.relative_to(ROOT).as_posix()]=sha(p.read_bytes())
        if rel in EXPECTED_EVIDENCE:
            need(sha(p.read_bytes())==EXPECTED_EVIDENCE[rel],'Changed frozen silhouette source/runtime evidence');docs[rel.rsplit('/',1)[1]]=json.loads(p.read_bytes())
    for key,pin in [('source','source_sha256'),('chain_source','chain_source_sha256')]:
        p=renderer.contained(bundle,EXPECTED_COMPONENT[key]);need(sha(p.read_bytes())==EXPECTED_COMPONENT[pin],'Whole unchanged readable source/VIF changed');need(not any(x in p.read_text().lower() for x in ['.word','.byte','.long','.quad','.incbin','.org','.space','.fill','.dword','.hword']),'Raw binary preservation cannot be source')
    text=renderer.contained(bundle,EXPECTED_COMPONENT['source']).read_text();wrapper=renderer.contained(bundle,EXPECTED_COMPONENT['chain_source']).read_text()
    need('.include' not in text and wrapper.count('.include "silhouette_program.vsm"')==1 and wrapper.count('mpg 0,*')==1 and 'vifnop' not in wrapper,'Whole silhouette source/two-header upload recipe')
    parent=docs['vu_silhouette_parent_review.json']
    need(parent.get('parent_review_status')=='PASS_COMPLETE_SOURCE_NATIVE_AND_BOUNDED_ACTUAL_STATE8_RUNTIME_ELIGIBLE_FOR_MAINTAINED_INTEGRATION' and parent.get('family')=='188058427' and parent.get('remaining_scoped_original_runtime_blockers')==[],'Missing final qualified source/native/runtime parent PASS')
    need(tuple(parent[k] for k in ['whole_code_bytes','VIF_control_bytes_separate','whole_runtime_upload_bytes','actual_nonallocated_R32_fields','entire_initialized_data_bytes','entire_BSS_bytes','original_function_count','authored_source_partitions_not_original_functions'])==(2336,16,2352,4,0,0,None,10),'Parent whole-program/count/data contract changed')
    asset=docs['vu_silhouette_runtime_independent_peer.json'];rt=docs['vu_silhouette_original_runtime_review.json'];correction=docs['vu_silhouette_cfg_selector_correction.json'];peer=docs['vu_silhouette_source_native_peer.json'];q=docs['vu_silhouette_source_qualification.json']
    need(asset['status']=='CLOSED_QUALIFIED_RUNTIME_PASS_MANDATORY_ADDITIVE_KIND10_CAMERA_A2_CORRECTION' and asset['remaining_scoped_original_runtime_blockers']==[],'Missing superseding bounded runtime PASS')
    need('A1=2,A2=2' in asset['mandatory_corrections']['camera'] and struct.unpack('<I',e.at_vram(0x175224,4))[0]==0x24050002 and struct.unpack('<I',e.at_vram(0x17522c,4))[0]==0x24060002,'Wrong actual kind10 camera(2,2); old050c82ff A2=1 is superseded')
    need(correction['status']=='PASS_ADDITIVE_ORIGINAL_PROSE_CORRECTION_ONLY' and correction['all256_byte_selectors_checked'] is True and correction['four_explicit_routes'][1]['target']==0x194558 and correction['four_explicit_routes'][2]['target']==0x192bb0,'Missing cfg1/194558 and cfg2/192BB0 correction')
    need(peer['original_function_count'] is None and peer['whole_code_bytes']==2336 and peer['real_nonallocated_R32_fields']==4,'Missing independently closed whole source/native peer')
    need(q['source_all_bytes_identical'] is True and q['VIF_all_bytes_identical'] is True and q['comment_changes']==[],'Unproved source/VIF mutation')
    bounds=asset['page_and_initialized_input_findings']['both_page_bounds'];need([(x['TOP'],x['vertex_begin'],x['vertex_end_exclusive'],x['edge_begin'],x['edge_end_exclusive'],x['ambient_last_prefetch']) for x in bounds]==[(52,86,101,101,129,129),(538,572,587,587,615,615)],'Wrong exact two-page selected ranges')
    look=asset['lookahead_and_last_edge'];need('q77' in look['final_ambient_prefetch'] and 'NO zero/sentinel' in look['final_ambient_prefetch'] and EXPECTED_COMPONENT['ambient_final_prefetch_not_source_initialized'] is True,'Invented initialized final sentinel or removed ambient reads')
    stock=rt['selected_serialized_original_witness'];fr=stock['factory_record'];raw=(ROOT/'build/asset_catalog/level_tag_05.decoded.bin').read_bytes();body=raw[fr['body_range'][0]:fr['body_range'][1]];a,z=stock['geometry_absolute_range']
    need(len(body)==665464 and sha(body)==fr['original_sha256'] and raw[a:z]==bytes.fromhex(stock['whole_geometry300_hex_input_only']) and z-a==300,'Changed entire actual stock/permanent-copy geometry input')
    node=stock['node'];seg=node['geometry']['segments'][0];need(node['index']==56 and node['kind']==1 and node['flag']==8 and node['sub_count']==0 and seg['vertex_count']==15 and seg['tail_count']==28,'Wrong actual selected unskinned base geometry')
    for row in asset['independent_direct_reverification']['deduplicated_pins']:
        p=Path(row['path']).resolve();need(p.is_relative_to(ROOT),'Actual frozen runtime input escapes workspace');p=renderer.contained(ROOT,p.relative_to(ROOT));need(p.stat().st_size==row['bytes'] and sha(p.read_bytes())==row['sha256'],'Changed exact actual source/runtime/architecture input');deps[p.relative_to(ROOT).as_posix()]=row['sha256']
    order=['vu_silhouette_original_runtime_review.json','vu_silhouette_complete_original_inputs.json','vu_silhouette_camera_original_addendum.json','vu_silhouette_runtime_independent_peer.json','vu_silhouette_source_native_peer.json','vu_silhouette_cfg_selector_correction.json','vu_silhouette_source_qualification.json'];inputs=original_input_ranges(e,[docs[x] for x in order])
    provenance=ROOT/'tools/third_party/dvp/provenance.json';need(sha(provenance.read_bytes())==PROVENANCE_SHA,'Changed native tool provenance');deps[provenance.relative_to(ROOT).as_posix()]=PROVENANCE_SHA
    for row in json.loads(provenance.read_bytes())['files']:
        p=renderer.contained(ROOT,row['path']);need(p.stat().st_size==row['bytes'] and sha(p.read_bytes())==row['sha256'],'Changed actual native compiler/runtime');deps[row['path']]=row['sha256']
    for row in [{'path': 'build/root_reviews/vu1504484043_20261015/primary_shadow_metadata_review.json', 'bytes': 4126, 'sha256': '3e42cb7dd79ec2cd24fe8652a3e32d630882e41c2cecb33dd6363213b63cbd32'}, {'path': 'build/compiler_profile/vu1504484043_shadow_primary_classification_peer_20261015/INDEPENDENT_PRIMARY_SHADOW_FILL_CLASSIFICATION.json', 'bytes': 20017, 'sha256': '1941f297209d1b4660130b72a5aafd8ce1114b42f12b9996dfdf01f2d5bbb9a6'}, {'path': 'build/root_reviews/dvp2451_primary_fragment_20261015/gas/config/tc-dvp.c', 'bytes': 101890, 'sha256': '1ad962e9d78cda8241939a2ff784cf31bfb9671e8609c137bef8858554b6a657'}, {'path': 'build/root_reviews/dvp2451_primary_fragment_20261015/gas/frags.c', 'bytes': 16155, 'sha256': 'b8293596bc993a63803bf09cf97dfc893fa383c70fc05b0e6157f4850e048aca'}, {'path': 'build/root_reviews/dvp2451_primary_fragment_20261015/gas/read.c', 'bytes': 169748, 'sha256': '19dd84b24ff3ea28e9ae260d1d61285cbd0a74d1ebed3295747f4c0d3b0d1435'}, {'path': 'build/root_reviews/dvp2451_primary_fragment_20261015/gas/write.c', 'bytes': 89360, 'sha256': '95be14bf0f2a61e4ae17f792e48c8a60c53ac3f2eb59e44fc13bee81b3d6324b'}, {'path': 'build/root_reviews/dvp2451_primary_fragment_20261015/gas/frags.h', 'bytes': 5261, 'sha256': 'b903728e36bbc7d2109c72d2cd855878ccec62e3b476059d92d382b3afbae383'}, {'path': 'build/root_reviews/dvp2451_primary_fragment_20261015/gas/config/tc-dvp.h', 'bytes': 3409, 'sha256': '109cb57fda3a3e8404922c1a256fc0cfe2d19fdb7fdb8db1edb5ffe849ea1a71'}, {'path': 'build/root_reviews/dvp2451_primary_fragment_20261015/include/obstack.h', 'bytes': 22405, 'sha256': 'ab4004dde55fff6c2d404781843bed538abf526ff0d8019e99999390c747d518'}]:
        p=renderer.contained(ROOT,row['path']);need(p.stat().st_size==row['bytes'] and sha(p.read_bytes())==row['sha256'],'Changed exact primary nonallocated sizing-shadow classification');deps[row['path']]=row['sha256']
    for rel in ['tools/common.py','tools/vu_build.py','config/vu_original_programs.json']:
        p=renderer.contained(ROOT,rel);deps[rel]=sha(p.read_bytes())
    return m,e,{'program':program,'chain':chain},inputs,dict(sorted(deps.items()))
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
    need(r.get('kind')=='complete-readable-native-VU-silhouette-source-component' and r.get('bundle_root')==bundle.relative_to(ROOT).as_posix() and r.get('component')==EXPECTED_COMPONENT,'Foreign/missing silhouette current report')
    need(r.get('dependency_hashes')==deps and r.get('complete_original_input_ranges')==[list(x) for x in inputs],'Stale source/native/input report')
    need(set(r['native_components'])=={'program','chain'},'Missing/extra native silhouette component')
    job=r.get('native_job')
    for kind in ['program','chain']:
        item=r['native_components'][kind];validate_native_record(item,kind,bundle,out,job)
        need(set(item['files'])=={kind+'.o',kind+'.bin'},'Missing/extra complete native file')
        for n in [kind+'.o',kind+'.bin']:need(item['files'][n]==receipt(out/n),'Whole current native output fingerprint changed')
        proof=strict_native((out/(kind+'.o')).read_bytes(),kind,expected[kind],ROLES)
        need(item['native_proof']==proof and (out/(kind+'.bin')).read_bytes()==expected[kind],'False whole native/initialized-section/relocation proof')
    log={'native_job':job,'commands':[{'kind':k,'source':r['native_components'][k]['source'],'source_sha256':r['native_components'][k]['source_sha256'],'actual_native_command':r['native_components'][k]['actual_native_command']} for k in ['program','chain']]}
    need(r.get('native_command_log')==receipt(out/'actual_native_commands.json') and json.loads((out/'actual_native_commands.json').read_bytes())==log,'Missing/forged actual native command log')
    need(r.get('verified_original_function_count','missing') is None and r.get('source_partitions_not_original_functions')==10 and r.get('initialized_data_bytes')==r.get('BSS_bytes')==r.get('dynamic_REFS_source_credit')==0,'False routine/data/dynamic-input source count')
    need(all(r.get(k) is False for k in ['historical_original_compiler_identity_confirmed','full_source_relink_complete','live_runtime_execution_observed','unknown_predecessor_or_universal_asset_domain_claim']),'False compiler/universal/runtime/relink claim')

def current_report(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT):
    bundle=Path(bundle).resolve();out=output_path(output);m,e,expected,inputs,deps=checked_manifest(bundle);r=json.loads((out/REPORT_NAME).read_bytes())
    validate_report(r,bundle,out,expected,inputs,deps)
    return {**r,'freshness':'CURRENT_WHOLE2336_SILHOUETTE_AND2352_CHAIN_QUALIFIED_STATE8_ACCEPTED_FRAME_VERIFIED'}

def run(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT,fresh=False):
    bundle=Path(bundle).resolve();out=output_path(output)
    if out.exists() and any(out.iterdir()):
        need(not fresh,'Fresh native silhouette proof needs empty output')
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
        need(actual==native_command(kind,bundle,out,tmp),'Pinned native silhouette assembly failed or emitted unexpected diagnostics')
        proof=strict_native((out/(kind+'.o')).read_bytes(),kind,expected[kind],ROLES);elf=Elf32((out/(kind+'.o')).read_bytes());(out/(kind+'.bin')).write_bytes(elf.section_data(elf.section('.vutext')))
        native[kind]={'files':{n:receipt(out/n) for n in [kind+'.o',kind+'.bin']},'native_proof':proof,'actual_native_command':actual,'source_sha256':sha(p.read_bytes()),'source':receipt(p),'native_job':job}
    r={'kind':'complete-readable-native-VU-silhouette-source-component','bundle_root':bundle.relative_to(ROOT).as_posix(),'component':EXPECTED_COMPONENT,'dependency_hashes':deps,'complete_original_input_ranges':inputs,'native_components':native,'native_job':job,'native_command_log':receipt(out/'actual_native_commands.json'),'verified_original_function_count':None,'source_partitions_not_original_functions':10,'initialized_data_bytes':0,'BSS_bytes':0,'dynamic_REFS_source_credit':0,'historical_original_compiler_identity_confirmed':False,'full_source_relink_complete':False,'live_runtime_execution_observed':False,'unknown_predecessor_or_universal_asset_domain_claim':False}
    (out/REPORT_NAME).write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    return current_report(bundle,out)
def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--fresh',action='store_true');p.add_argument('--check',action='store_true');a=p.parse_args();r=current_report(a.bundle_root,a.output) if a.check else run(a.bundle_root,a.output,a.fresh);print(json.dumps({'status':'PASS','component':r['component'],'freshness':r['freshness'],'original_function_count':None}))
if __name__=='__main__':main()
