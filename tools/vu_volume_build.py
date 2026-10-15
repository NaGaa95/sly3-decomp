"""Complete state6 volume VU component; all six earlier source owners stay mandatory."""
import argparse,json,struct,subprocess,sys,os,uuid,copy,hashlib
from pathlib import Path
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve();ROOT=next(p for p in HERE.parents if (p/'disc/SCUS_974.64').is_file())
sys.path.insert(0,str(ROOT/'tools'))
import vu_build as renderer
from common import Elf32
from vu_volume_native import strict_native
DEFAULT_BUNDLE=HERE.parents[1]
DEFAULT_OUTPUT=ROOT/'build/vu/volume'
REPORT_NAME='vu_volume_report.json'
EXPECTED_COMPONENT={'family': '188058715', 'processor': 'VU1', 'source': 'src/vu/volume/volume_program.vsm', 'chain_source': 'src/vu/volume/volume_upload.vif', 'source_sha256': '29d782d968f1feed5ffd7eb09a9630f66b0a396f42e4c1802f40a5edc58fc523', 'chain_source_sha256': '00d3c107e9e87032e8a9b2886505301b00a8480bdb99cf11b2341da14137e841', 'code_bytes': 8008, 'chain_bytes': 8048, 'DMA_protocol_bytes': 0, 'VIF_protocol_bytes': 40, 'EE_chain_begin': 2893376, 'EE_chain_end': 2901424, 'program_sha256': '3c2cf48127acda999a55db79fb68fb8b1fb6df21d2aeccc128524d18a73cd9c5', 'chain_sha256': 'f120da8a904409319b585452be0b93d14f732d137bca1407286331a7eeacc3b9', 'functions': None, 'original_function_count_complete': False, 'authored_source_partitions': [{'name': 'volume_idle', 'VU_byte_begin': 0, 'bytes': 16, 'algorithm': 'Realidle Eplusdelay, separateCPUgeometry idle0 provider.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_debug_acknowledge', 'VU_byte_begin': 16, 'bytes': 80, 'algorithm': 'Consume/clear absolute15.W debugrequest with originalDpair.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_prepare_transform', 'VU_byte_begin': 96, 'bytes': 576, 'algorithm': 'Flags1400 billboard selection; local/view/inverse affine transforms with actualnativeW andsavedlink.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_restore_previous_packet', 'VU_byte_begin': 672, 'bytes': 192, 'algorithm': 'Copyten oppositepage cacheqwords and boundedtail14..end.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_skin_positions', 'VU_byte_begin': 864, 'bytes': 448, 'algorithm': 'Four packetdirected matrices; integerweightsnormalized1/255; twoqword positions.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_project_edge_space', 'VU_byte_begin': 1312, 'bytes': 360, 'algorithm': 'Rollingthree-vector Qprojection XYZ/Z for edgepositions, realend/padding requirements.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_build_silhouette_sides', 'VU_byte_begin': 1672, 'bytes': 856, 'algorithm': 'Quadadjacency face-crossproduct Zsign transitions emit sixsidevertices; mantissabias indices andnative1.5extrusion.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_project_strip_body', 'VU_byte_begin': 2528, 'bytes': 1256, 'algorithm': 'Homogeneous twoqword stripprojection and alternating marker/Q/CLIP pipeline, completebody.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_classify_triangle', 'VU_byte_begin': 3784, 'bytes': 344, 'algorithm': 'NestedVI14 triangleCLIP/ADC classification, rollingAND/OR masks, native markerflags.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_project_strip_reject_tail', 'VU_byte_begin': 4128, 'bytes': 248, 'algorithm': 'Projectionbody livecommonplane reject continuation, not an originalfunction orfreshentry.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_kick_strip_packets', 'VU_byte_begin': 4376, 'bytes': 256, 'algorithm': 'Patch inheritedGIFtag andkickone/two actualmaterialstreams.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_clip_polygon_plane', 'VU_byte_begin': 4632, 'bytes': 336, 'algorithm': 'Sutherland-Hodgman position clipping with signedW distance andQinterpolation.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_clip_project_polygon', 'VU_byte_begin': 4968, 'bytes': 648, 'algorithm': 'Six originalCLIP-plane gates thenperspective map, trueemptyoutput andsavedlinkdelay.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_choose_winding_marker', 'VU_byte_begin': 5616, 'bytes': 208, 'algorithm': 'Signedfan area chooses originalwindingmarker andfills evenqword carriers.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_emit_clipped_triangles', 'VU_byte_begin': 5824, 'bytes': 776, 'algorithm': 'Inheritedpartiallyclipped triangles reconstructed tohomogeneousspace, clip/marker/materialkicks, alternatingwinding/scratchbanks.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_draw_primary', 'VU_byte_begin': 6600, 'bytes': 344, 'algorithm': 'Actual19C8 primaryentry: flags1/2/4 compose/restore/skin, adjacencyprojection/silhouette andstripkick.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_draw_secondary', 'VU_byte_begin': 6944, 'bytes': 56, 'algorithm': 'Actual1B20 secondaryentry: completeclip thenstripkick andE/delay.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_patch_command_stream', 'VU_byte_begin': 7000, 'bytes': 472, 'algorithm': 'Actual1B58 interpreter: signedU16operation/end records27→patch absoluteparameterbank components into TOPS-relativecommandstream36; realnegativeand>8termination.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_patch_teardown_entry', 'VU_byte_begin': 7472, 'bytes': 16, 'algorithm': 'Actual1D30 teardown branchinto1B58, noindependentE/reset ornewfunctioncount.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_compose_matrices', 'VU_byte_begin': 7488, 'bytes': 184, 'algorithm': 'Fourcolumn matrixcomposition with pipelinedstores andrealJRdelay.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_inverse_normal_matrix', 'VU_byte_begin': 7672, 'bytes': 184, 'algorithm': 'Actualwhole184byte3x3 cofactors/determinant/transpose/reciprocalQ; originalequivalence to376/150 proved.', 'names_are_source_identifiers_not_original_symbols': True}, {'name': 'volume_inverse_affine', 'VU_byte_begin': 7856, 'bytes': 152, 'algorithm': 'Affineinverse viaactualcofactorhelper thennegatedtranslation; Wchanges expressedasnativeops.', 'names_are_source_identifiers_not_original_symbols': True}], 'additional_entries': {'4128': 'strip_reject_common_plane', '7320': 'command_patch_0', '7336': 'command_patch_1', '7352': 'command_patch_2', '7368': 'command_patch_3', '7384': 'command_patch_4', '7400': 'command_patch_5', '7416': 'command_patch_6', '7432': 'command_patch_7', '7448': 'command_patch_8'}, 'source_partition_count': 22, 'aliases_count_as_additional_functions': False, 'actual_direct_entries': {'0': 'volume_idle', '19c8': 'volume_draw_primary', '1b20': 'volume_draw_secondary', '1b58': 'volume_patch_command_stream', '1d30': 'volume_patch_teardown_entry'}, 'runtime_scope': 'Actual mode0CID36Bentley/node7kind2/state6RendererID86, normal equalcycle4/4 or1/1 mode0/unmasked/validcamera/header/matrix/geometry/light/video+10divisor/surface/queue/cache/IRQ/DMAfreshstamp/alignedarena/nonnegative settings1C andacceptednonnull2C predicate. Zero1C/F20 clears/skips; negative/customcallback uninitializedmatrix alternative excluded. No state7separate witness, coldboot/asset/vtable/universal GS extent or livehardware claim.', 'dynamic_REFS_source_credit': 0, 'initialized_data_bytes': 0, 'BSS_bytes': 0, 'allocated_relocations': 0, 'nonallocated_overlay_R32_fields': 8, 'full_source_relink_complete': False}
EXPECTED_EVIDENCE={'docs/evidence/vu_volume_borrowed_packet_review.json': '79c6b037d7d9daa52317ba3da7d3312b67a40105864b1239c51cfbf94b69d1dd', 'docs/evidence/vu_volume_original_launch_frontier.json': '8fdfbe1395bd85108e0e4e1cb38c8616d208221ea9a2651f02a520bcf92aa8d1', 'docs/evidence/vu_volume_packet_original_support.json': 'e2ec315f3b8517160a80132c8bf703b508eb08b54c3180f08035208cdc94a5ff', 'docs/evidence/vu_volume_parent_review.json': '5b2e00f1699b9488f7f6522523d42f2231f231a3a759bfb57c7239f9672fba71', 'docs/evidence/vu_volume_runtime_edge_peer_review.json': '14a459e60a572e47801b097c91bc59e33fac687b55731c028f5a8167e87c07ce', 'docs/evidence/vu_volume_source_adjustment.json': '5156326e9bfab3faa73e9512cf6f376fba49635353ad4d2ba596e58da1ec09d9', 'docs/evidence/vu_volume_source_peer_review.json': '384c208409c4f060d319b99b778a27580924596102cac8abb072ce17a5301001'}
ORIGINAL_SHA='ce817858306efd711f08bbc14f393455280119cb00b894bdc9fb1fa47bcbb338'
PROVENANCE_SHA='2199c34122dcb130521cbc1690a2a3f996cd9f59f1c4886055a88ed4354a1ea7'
ROLES={'source_partitions':EXPECTED_COMPONENT['authored_source_partitions'],'native_loop_labels_not_new_functions':EXPECTED_COMPONENT['additional_entries']}

def need(condition,message):
    if not condition:raise ValueError(message)
def receipt(path):return renderer.file_receipt(Path(path).resolve(),ROOT)
def sha(data):return hashlib.sha256(data).hexdigest()
def output_path(output):
    p=Path(output).resolve()
    need(p==ROOT/'build/vu/volume','Volume native output must be its exact canonical directory')
    return p
def validate_manifest(m):
    need(m.get('schema')==1 and m.get('kind')=='mandatory-seventh-complete-readable-native-VU-volume-component','Missing mandatory complete volume owner')
    need(m.get('component')==EXPECTED_COMPONENT,'Wrong whole volume ownership, code/control or unknown function count')
    need(m.get('known_original_function_count_from_existing_six')==19 and 'new_original_function_count' in m and m['new_original_function_count'] is None and m.get('existing_six_owners_mandatory') is True,'Authored22 partitions are not original functions; all six earlier owners remain mandatory')
    need(m.get('original_sha256')==ORIGINAL_SHA and m.get('original_unique_program_count')==9 and m.get('original_unique_program_code_bytes')==50032 and m.get('original_nonallocated_zero_shadow_count')==29,'Wrong original family/code/shadow denominator')
    need(m.get('evidence_hashes')==EXPECTED_EVIDENCE and m.get('portable_provenance_sha256')==PROVENANCE_SHA,'Missing closed source/input/tool evidence')
    need(all(m.get(k)==0 for k in ['initialized_data_bytes','BSS_bytes','EE_C_CPP_functions_delta','EE_C_CPP_code_bytes_delta']),'False EE/data source credit')
    need(all(m.get(k) is False for k in ['historical_original_compiler_identity_confirmed','live_hardware_observed','universal_asset_or_predecessor_domain_claim','full_source_relink_complete']),'Unsupported compiler/hardware/universal/relink claim')
def required_dependencies():
    return ['config/vu_volume_sources.json',EXPECTED_COMPONENT['source'],EXPECTED_COMPONENT['chain_source'],*EXPECTED_EVIDENCE,'tools/vu_volume_build.py','tools/vu_volume_native.py','tools/test_vu_volume.py']
def original_input_ranges(e,documents):
    records=[];counts=[]
    count_keys=['bytes','complete_original_bytes','entire_original_bytes','complete_bytes','whole_bytes'];hash_keys=['original_sha256','sha256','whole_sha256']
    hex_keys=['original_bytes_hex','raw_original_hex','original_hex','original_bytes_hex_input_only','whole_original_hex_input_only','entire_original_hex']
    def visit(v,found):
        if isinstance(v,list):
            for x in v:visit(x,found)
        elif isinstance(v,dict):
            address=v.get('address',v.get('EE_begin'));sizes=[v[k] for k in count_keys if k in v];hashes=[v[k] for k in hash_keys if k in v]
            # Four-byte word anchors are verified separately below; they are
            # never counted as complete original function/range captures.
            if address is not None and sizes and hashes:
                need(all(type(n) is int and n>0 for n in sizes) and len(set(sizes))==1,'Missing/ambiguous complete original size')
                n=sizes[0];a=int(address,0) if isinstance(address,str) else address
                need(type(a) is int and a>=0 and len(set(hashes))==1,'Missing/ambiguous complete original address/hash')
                raw=e.at_vram(a,n);h=sha(raw);need(h==hashes[0],'Changed entire original input')
                for k in hex_keys:
                    if k in v:need(bytes.fromhex(v[k])==raw,'Changed complete original input hex')
                found.append((a,n,h))
            for x in v.values():visit(x,found)
    for d in documents:
        found=[];visit(d,found);counts.append(len(found));records+=found
    need(counts==[0,10,78,18,106,0,0],'Incomplete original input document/range inventory')
    need(len(records)==212,'Incomplete complete-range occurrences')
    return sorted(set(records))
def checked_manifest(bundle=DEFAULT_BUNDLE):
    bundle=Path(bundle).resolve();m=json.loads(renderer.contained(bundle,'config/vu_volume_sources.json').read_bytes());validate_manifest(m)
    e,_,_,programs=renderer.original_mapping();original=next(p for p in programs if p['family_file_name_hash']=='188058715')
    program=b''.join(e.at_vram(c['EE_payload_begin'],c['code_bytes']) for c in original['chunks']);chain=e.at_vram(0x2c2640,8048)
    need(original['VU_bytes']==8008 and sha(program)==EXPECTED_COMPONENT['program_sha256'] and sha(chain)==EXPECTED_COMPONENT['chain_sha256'],'Wrong entire four-chunk8008/8048 program/upload')
    deps={};docs={}
    for rel in required_dependencies():
        p=renderer.contained(bundle,rel);deps[p.relative_to(ROOT).as_posix()]=sha(p.read_bytes())
        if rel in EXPECTED_EVIDENCE:
            need(sha(p.read_bytes())==EXPECTED_EVIDENCE[rel],'Closed source/runtime/original packet changed');docs[rel.rsplit('/',1)[1]]=json.loads(p.read_bytes())
    for key,pin in [('source','source_sha256'),('chain_source','chain_source_sha256')]:
        p=renderer.contained(bundle,EXPECTED_COMPONENT[key]);need(sha(p.read_bytes())==EXPECTED_COMPONENT[pin],'Complete readable volume source changed')
        need(not any(t in p.read_text().lower() for t in ['.word','.byte','.long','.quad','.incbin','.org','.space']),'Raw original preservation is not readable source')
    text=renderer.contained(bundle,EXPECTED_COMPONENT['source']).read_text();wrapper=renderer.contained(bundle,EXPECTED_COMPONENT['chain_source']).read_text()
    need('.include' not in text and wrapper.count('.include "volume_program.vsm"')==1 and wrapper.count('mpg 0,*')==1 and wrapper.count('vifnop')==2,'Incomplete volume source/upload recipe')
    parent=docs['vu_volume_parent_review.json'];runtime=docs['vu_volume_runtime_edge_peer_review.json'];borrowed=docs['vu_volume_borrowed_packet_review.json'];frontier=docs['vu_volume_original_launch_frontier.json'];adjust=docs['vu_volume_source_adjustment.json']
    need(parent['parent_review_status']=='PASS_COMPLETE_SOURCE_NATIVE_AND_BOUNDED_ACTUAL_STATE6_RUNTIME_ELIGIBLE_FOR_MAINTAINED_INTEGRATION' and parent['original_function_count'] is None,'Missing bounded final parent acceptance')
    need(runtime['status']=='PASS_QUALIFIED_BORROWED_PACKET_ORIGINAL_RUNTIME_EDGE_WITH_MANDATORY_ADDITIVE_FLAG_CORRECTION' and runtime['verification']['whole_original_range_rows']==106 and len(runtime['whole_original_ranges'])==106,'Missing exact borrowed runtime edge review')
    need(borrowed['status']=='CLOSED_PASS_BOUNDED_ORDINARY_BORROWED_REFS_CONTENT_AND_SAME_FRAME_LIFETIME','Missing ordinary generated packet/lifetime closure')
    correction=runtime['mandatory_additive_flag_correction'];need(correction==parent['mandatory_additive_flag_correction'] and correction['final_lane']=='Final payload row18.X is raw integer flag0 or1, not universalzero and not float1.0.','Missing mandatory final raw flag0OR1 correction')
    need(len(correction['anchors'])==14,'Incomplete flag initialization/override/copy anchors')
    for a in correction['anchors']:
        raw=e.at_vram(int(a['address'],0),4);need(raw==bytes.fromhex(a['bytes']) and struct.unpack('<I',raw)[0]==int(a['word'],0),'Changed actual flag0OR1 anchor')
    packet=runtime['retained_packet'];need(len(packet['both_pages'])==2 and packet['command_decode']['word']=='0x6c05c00e' and packet['command_decode']['NUM']==5 and packet['command_decode']['destination']==14,'Wrong whole80-byte retained packet/page contract')
    need([p['live_TOPS_qword'] for p in packet['both_pages']]==[52,538] and all(p['payload_bytes']==80 and p['changes_BASE_OFFSET_cycle_mode_mask_or_program'] is False for p in packet['both_pages']),'Wrong borrowed page/lifetime/state predicate')
    need(adjust['all_noncomment_source_bytes_identical'] is True and adjust['entire_VIF_unchanged'] is True and len(adjust['changes'])==1 and adjust['changes'][0]['line']==51 and adjust['final_source_sha256']==EXPECTED_COMPONENT['source_sha256'],'Unproved canonical comment correction')
    stock=frontier['actual_stock_receiver'];fr=stock['factory_record'];raw=(ROOT/'build/asset_catalog/level_tag_05.decoded.bin').read_bytes();body=raw[fr['body_range'][0]:fr['body_range'][1]]
    need(len(body)==665464 and sha(body)==fr['original_sha256']==stock['whole_body_sha256'],'Changed entire selected CID36 stock body')
    node=stock['selected_node7'];a,z=stock['selected_node_absolute_range'];need(raw[a:z]==bytes.fromhex(stock['selected_node_original_hex']) and node['index']==7 and node['kind']==2 and node['flag']==6 and node['geometry']['segments'][0]['vertex_count']==6,'Changed actual selected state6 node7 geometry')
    # Only exact ROOT-contained actual evidence is a live build dependency.
    # Four Sly2 sources in the frozen peer packet are reference-only attribution.
    for row in runtime['all_pins']:
        if Path(row['path']).is_absolute():
            need(row['path'].startswith('C:/Users/PC/Documents/GitHub/sly2-decomp/src/hand/'),'Unexpected external reference provenance');continue
        p=renderer.contained(ROOT,row['path']);need(p.stat().st_size==row['bytes'] and sha(p.read_bytes())==row['sha256'],'Changed frozen actual runtime/packet/input support');deps[row['path']]=row['sha256']
    order=['vu_volume_parent_review.json','vu_volume_borrowed_packet_review.json','vu_volume_original_launch_frontier.json','vu_volume_packet_original_support.json','vu_volume_runtime_edge_peer_review.json','vu_volume_source_adjustment.json','vu_volume_source_peer_review.json']
    inputs=original_input_ranges(e,[docs[n] for n in order])
    provenance=ROOT/'tools/third_party/dvp/provenance.json';need(sha(provenance.read_bytes())==PROVENANCE_SHA,'Changed installed native profile');deps[provenance.relative_to(ROOT).as_posix()]=PROVENANCE_SHA
    for row in json.loads(provenance.read_bytes())['files']:
        p=renderer.contained(ROOT,row['path']);need(p.stat().st_size==row['bytes'] and sha(p.read_bytes())==row['sha256'],'Changed pinned native tool/runtime');deps[row['path']]=row['sha256']
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
    need(r.get('kind')=='complete-seventh-readable-native-VU-volume-source-component' and r.get('bundle_root')==bundle.relative_to(ROOT).as_posix() and r.get('component')==EXPECTED_COMPONENT,'Foreign/missing volume current report')
    need(r.get('dependency_hashes')==deps and r.get('complete_original_input_ranges')==[list(x) for x in inputs],'Stale source/native/input report')
    need(set(r['native_components'])=={'program','chain'},'Missing/extra native volume component')
    job=r.get('native_job')
    for kind in ['program','chain']:
        item=r['native_components'][kind];validate_native_record(item,kind,bundle,out,job)
        need(set(item['files'])=={kind+'.o',kind+'.bin'},'Missing/extra complete native file')
        for n in [kind+'.o',kind+'.bin']:need(item['files'][n]==receipt(out/n),'Whole current native output fingerprint changed')
        proof=strict_native((out/(kind+'.o')).read_bytes(),kind,expected[kind],ROLES)
        need(item['native_proof']==proof and (out/(kind+'.bin')).read_bytes()==expected[kind],'False whole native/initialized-section/relocation proof')
    log={'native_job':job,'commands':[{'kind':k,'source':r['native_components'][k]['source'],'source_sha256':r['native_components'][k]['source_sha256'],'actual_native_command':r['native_components'][k]['actual_native_command']} for k in ['program','chain']]}
    need(r.get('native_command_log')==receipt(out/'actual_native_commands.json') and json.loads((out/'actual_native_commands.json').read_bytes())==log,'Missing/forged actual native command log')
    need(r.get('verified_original_function_count','missing') is None and r.get('source_partitions_not_original_functions')==22 and r.get('initialized_data_bytes')==r.get('BSS_bytes')==r.get('dynamic_REFS_source_credit')==0,'False routine/data/dynamic-input source count')
    need(all(r.get(k) is False for k in ['historical_original_compiler_identity_confirmed','full_source_relink_complete','live_runtime_execution_observed','unknown_predecessor_or_universal_asset_domain_claim']),'False compiler/universal/runtime/relink claim')

def current_report(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT):
    bundle=Path(bundle).resolve();out=output_path(output);m,e,expected,inputs,deps=checked_manifest(bundle);r=json.loads((out/REPORT_NAME).read_bytes())
    validate_report(r,bundle,out,expected,inputs,deps)
    return {**r,'freshness':'CURRENT_WHOLE8008_VOLUME_AND8048_CHAIN_QUALIFIED_STATE6_ACCEPTED_FRAME_VERIFIED'}

def run(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT,fresh=False):
    bundle=Path(bundle).resolve();out=output_path(output)
    if out.exists() and any(out.iterdir()):
        need(not fresh,'Fresh native volume proof needs empty output')
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
        need(actual==native_command(kind,bundle,out,tmp),'Pinned native volume assembly failed or emitted unexpected diagnostics')
        proof=strict_native((out/(kind+'.o')).read_bytes(),kind,expected[kind],ROLES);elf=Elf32((out/(kind+'.o')).read_bytes());(out/(kind+'.bin')).write_bytes(elf.section_data(elf.section('.vutext')))
        native[kind]={'files':{n:receipt(out/n) for n in [kind+'.o',kind+'.bin']},'native_proof':proof,'actual_native_command':actual,'source_sha256':sha(p.read_bytes()),'source':receipt(p),'native_job':job}
    r={'kind':'complete-seventh-readable-native-VU-volume-source-component','bundle_root':bundle.relative_to(ROOT).as_posix(),'component':EXPECTED_COMPONENT,'dependency_hashes':deps,'complete_original_input_ranges':inputs,'native_components':native,'native_job':job,'native_command_log':receipt(out/'actual_native_commands.json'),'verified_original_function_count':None,'source_partitions_not_original_functions':22,'initialized_data_bytes':0,'BSS_bytes':0,'dynamic_REFS_source_credit':0,'historical_original_compiler_identity_confirmed':False,'full_source_relink_complete':False,'live_runtime_execution_observed':False,'unknown_predecessor_or_universal_asset_domain_claim':False}
    (out/REPORT_NAME).write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    return current_report(bundle,out)
def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--fresh',action='store_true');p.add_argument('--check',action='store_true');a=p.parse_args();r=current_report(a.bundle_root,a.output) if a.check else run(a.bundle_root,a.output,a.fresh);print(json.dumps({'status':'PASS','component':r['component'],'freshness':r['freshness'],'original_function_count':None}))
if __name__=='__main__':main()
