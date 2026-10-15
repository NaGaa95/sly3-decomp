"""Complete eighth particle source component; separate original-input scope.
Exact final parent and independent source/runtime evidence are mandatory.
Whole code3800 and staticVIF24 are separate; three source partitions are not
three recovered original functions. Dynamic buffers/templates remain input0.
"""
import argparse,json,struct,subprocess,sys,os,uuid,copy,hashlib
from pathlib import Path
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve();ROOT=next(p for p in HERE.parents if (p/'disc/SCUS_974.64').is_file())
sys.path.insert(0,str(ROOT/'tools'))
import vu_build as renderer
from common import Elf32
from vu_particle_native import strict_native
DEFAULT_BUNDLE=HERE.parents[1]
DEFAULT_OUTPUT=ROOT/'build/vu/particle'
REPORT_NAME='vu_particle_report.json'
EXPECTED_COMPONENT={'family': '376117691',
 'processor': 'VU1',
 'source': 'src/vu/particle/particle_program.vsm',
 'chain_source': 'src/vu/particle/particle_upload.vif',
 'source_sha256': '545a8bfd7ece41cbadaa9851d87b43676eed9f987d5dfc352282ac704bd7222c',
 'chain_source_sha256': 'e37ec04ad6d56165b71b52cb501091f51d1b68945e29a4915f32abdb0fd9cd5b',
 'code_bytes': 3800,
 'chain_bytes': 3824,
 'DMA_protocol_bytes': 0,
 'VIF_protocol_bytes': 24,
 'EE_chain_begin': 2884896,
 'EE_requested_end': 2888712,
 'EE_requested_bytes': 3816,
 'EE_chain_end': 2888720,
 'actual_REFS_qwords': 239,
 'program_sha256': '30694bb55c1d50b1c6121618106b5c19d5a83c474bf8f7ea7c82c3ce9ccabdae',
 'chain_sha256': '6370899a0bee58d58cdea638b6c5f1d7f9c41566bbb5b8494c70a5c499e39b26',
 'functions': None,
 'original_function_count_complete': False,
 'authored_source_partitions': [{'name': 'particle_billboard_batch',
                                 'VU_byte_begin': 0,
                                 'bytes': 920,
                                 'algorithm': 'Age-polynomial clipspacebillboards withframe/color '
                                              'interpolation andnativeADCclipmask.',
                                 'original_symbol_names_not_recovered': True},
                                {'name': 'particle_streak_batch',
                                 'VU_byte_begin': 920,
                                 'bytes': 1256,
                                 'algorithm': 'Direction-based EFUlength/cross-product streaks, separateQ '
                                              'endpoints andinheritedUV/color/framecache.',
                                 'original_symbol_names_not_recovered': True},
                                {'name': 'particle_rotated_batch',
                                 'VU_byte_begin': 2176,
                                 'bytes': 1624,
                                 'algorithm': 'NativeESIN/ESQRT quadrantrotation, agecurves '
                                              'andclipspacequads.',
                                 'original_symbol_names_not_recovered': True}],
 'additional_entries': {},
 'source_partition_count': 3,
 'aliases_count_as_additional_functions': False,
 'actual_direct_entries': {'0': 'particle_billboard_batch',
                           '398': 'particle_streak_batch',
                           '880': 'particle_rotated_batch'},
 'post_entry_VIF_command': 285212672,
 'post_entry_VIF_command_name': 'FLUSH',
 'post_entry_EE_sites': [1354608, 2103032],
 'runtime_scope': 'Bounded actual dynamicCID26/state11 first-emission frame; conditional originalmode0/1/2, '
                  'N1..43, positive nativealloc/camera, initializedboth840-bytebanks, '
                  'finiteage/material/frame/EFU/Q/clipinputs; C1..32,Tpowerof2in1/2/4/8/16,C+T<=33 '
                  'andsimplecolorflag0; normal acceptedframe, stable queuedbank/material '
                  'throughDMAcompletion, deferredretirement. State12/13 callback/secondprovider evidence '
                  'input-only; no separatefactory, stock/universal/concurrentlifetime/hardwareclaim.',
 'dynamic_REFS_source_credit': 0,
 'initialized_data_bytes': 0,
 'BSS_bytes': 0,
 'allocated_relocations': 0,
 'nonallocated_overlay_R32_fields': 4,
 'full_source_relink_complete': False}
EXPECTED_EVIDENCE={'docs/evidence/vu_particle_original_owner_reservation.json': '581d94d6be4f2128b40c1b8c880c142db4af9f54d880d43c3240218a323e99f4',
 'docs/evidence/vu_particle_source_owner_review.json': '0cc2c869c7e90659abb144ec5a437f1f57a60cca7204857337bfb3d68aa0d512',
 'docs/evidence/vu_particle_source_peer_review.json': '927624d9ba0136e56caf68658aed57eef45342d8cf33781489a4fab334442821',
 'docs/evidence/vu_particle_runtime_input_review.json': 'f324d097b856474b7afac0a51b5777cfba10b95aa6d9f73ab72b5f4bfc8f7006',
 'docs/evidence/vu_particle_runtime_input_support.json': 'dfcc52f8c566510c999a6e56b926d070b9791702a6822a8aa94364339d768559',
 'docs/evidence/vu_particle_shadow_primary_classification.json': '1941f297209d1b4660130b72a5aafd8ce1114b42f12b9996dfdf01f2d5bbb9a6',
 'docs/evidence/vu_particle_protocol_label_correction.json': 'a1012f3c1237e5bbc0c2d96a3731a8da047deb5c0662d726402a0ce192e303ac'}
EXPECTED_EVIDENCE['docs/evidence/vu_particle_runtime_peer_review.json']='63b58750084ac4213178d0ab0363ffae0000d07ef56a3f9dcb56dbd7b80ba0fe'
EXPECTED_EVIDENCE['docs/evidence/vu_particle_parent_review.json']='1b534af9e73f01b27bb0b1feac35f708bf54a4c0101634a85db8ccddf7e3d9cc'
PENDING_REQUIRED_EVIDENCE=[]
PREPARATION_ONLY_UNRUN=False
ORIGINAL_SHA='ce817858306efd711f08bbc14f393455280119cb00b894bdc9fb1fa47bcbb338'
PROVENANCE_SHA='2199c34122dcb130521cbc1690a2a3f996cd9f59f1c4886055a88ed4354a1ea7'
ROLES={'source_partitions':EXPECTED_COMPONENT['authored_source_partitions'],'native_loop_labels_not_new_functions':{}}

def need(condition,message):
    if not condition:raise ValueError(message)

def receipt(path):return renderer.file_receipt(Path(path).resolve(),ROOT)
def sha(data):return hashlib.sha256(data).hexdigest()
def output_path(output):
    p=Path(output).resolve();need(p==ROOT/'build/vu/particle','Particle native output must be its exact canonical directory');return p

def validate_manifest(m):
    need(m.get('schema')==1 and m.get('kind')=='mandatory-eighth-complete-readable-native-VU-particle-component','Missing mandatory complete particle owner')
    need(m.get('component')==EXPECTED_COMPONENT,'Wrong whole particle ownership/code/control/FLUSH/NULLfunctioncount')
    need(m.get('known_original_function_count_from_existing_seven')==19 and 'new_original_function_count'in m and m['new_original_function_count']is None and m.get('existing_seven_owners_mandatory')is True,'Three authored partitions are not recovered functions; all seven earlier owners mandatory')
    need(m.get('original_sha256')==ORIGINAL_SHA and m.get('original_unique_program_count')==9 and m.get('original_unique_program_code_bytes')==50032 and m.get('original_nonallocated_zero_shadow_count')==29,'Wrong original family/code/shadow denominator')
    need(m.get('evidence_hashes')==EXPECTED_EVIDENCE and m.get('portable_provenance_sha256')==PROVENANCE_SHA,'Missing closed source/runtime/tool evidence')
    need(m.get('pending_required_reviews')==PENDING_REQUIRED_EVIDENCE and m.get('preparation_only_unrun')is PREPARATION_ONLY_UNRUN,'Pending final eligibility gate changed without a new reviewed payload')
    need(all(m.get(k)==0 for k in['initialized_data_bytes','BSS_bytes','EE_C_CPP_functions_delta','EE_C_CPP_code_bytes_delta']),'False EE/template/data source credit')
    need(all(m.get(k)is False for k in['historical_original_compiler_identity_confirmed','live_hardware_observed','universal_asset_or_predecessor_domain_claim','full_source_relink_complete']),'Unsupported compiler/hardware/universal/relink claim')

def required_dependencies():
    return['config/vu_particle_sources.json',EXPECTED_COMPONENT['source'],EXPECTED_COMPONENT['chain_source'],*EXPECTED_EVIDENCE,'tools/vu_particle_build.py','tools/vu_particle_native.py','tools/test_vu_particle.py']

def verify_original_inputs(e,docs):
    """Pure whole input recheck. Preserve96 occurrences;94 unique, source0."""
    owner=docs['vu_particle_original_owner_reservation.json'];runtime=docs['vu_particle_runtime_input_review.json'];support=docs['vu_particle_runtime_input_support.json'];peer=docs['vu_particle_source_peer_review.json'];correction=docs['vu_particle_protocol_label_correction.json']
    need(owner['family']=='376117691'and owner['original_function_count']is None,'Wrong whole original family/boundaries')
    functions=owner['whole_original_EE_supports'];need(len(functions)==21,'Missing21 complete original source-input supports')
    for x in functions:
        raw=e.at_vram(x['address'],x['bytes']);need(sha(raw)==x['sha256']and raw==bytes.fromhex(x['whole_original_hex_input_only']),'Changed entire original source-input body')
    rows=runtime['whole_original_ranges_rechecked'];need(runtime['whole_original_recheck_count']==96 and len(rows)==96,'Missing96 complete original range occurrences')
    occurrences=[]
    for a,n,h in rows:
        a=int(a,0)if isinstance(a,str)else a;need(type(a)is int and type(n)is int and n>0 and sha(e.at_vram(a,n))==h,'Changed entire original runtime input range');occurrences.append((a,n,h))
    need(len(set(occurrences))==94,'Runtime96 occurrences must retain94 unique ranges, no duplicate source credit')
    need(set((x['address'],x['bytes'],x['sha256'])for x in functions).issubset(set(occurrences)),'Owner input body missing from full runtime union')
    need(len(support['whole_new_original_functions'])==48,'Missing complete new runtime body windows')
    for x in support['whole_new_original_functions']:
        a=int(x['address'],0);n=x['input_window_bytes'];raw=e.at_vram(a,n);need(raw==bytes.fromhex(x['entire_original_hex'])and sha(raw)==x['sha256']and int(x['end_exclusive'],0)==a+n,'Changed complete new runtime input body')
    anchors=support['EE_anchor_words'];need(len(anchors)==len({x['address']for x in anchors})==139,'Missing139 distinct actual original operand anchors')
    for x in anchors:
        a=int(x['address'],0);need(struct.unpack('<I',e.at_vram(a,4))[0]==int(x['word'],16),'Changed actual original runtime operand anchor')
    need(len(support['new_initialized_input_tables'])==3,'Missing entire runtime input table')
    for x in support['new_initialized_input_tables']:
        raw=e.at_vram(int(x['address'],0),x['bytes']);need(raw==bytes.fromhex(x['entire_original_hex'])and sha(raw)==x['sha256'],'Changed whole initialized runtime input table')
    need(support['BSS_template_destinations_not_static_original_data']==['0x36b260','0x36b2a0','0x36b2e0']and support['source_credit']==0,'Runtime BSS/shader/pool/CPU inputs cannot become source-data claims')
    need(runtime['status']=='CLOSED_BOUNDED_ORIGINAL_RUNTIME_INPUT_PASS_WITH_EXPLICIT_ACCEPTED_FRAME_PREDICATES'and runtime['family']==376117691 and runtime['original_function_count']is None,'Missing bounded actual dynamicCID26/runtime predicate')
    need(runtime['actual_receiver']['CID']==26 and runtime['actual_receiver']['real_slot21']['target']=='0x14a6d0','Wrong genuine dynamic receiver dispatch')
    domain=runtime['capacity_and_VU_inputs'];need(domain['N_domain']==[1,43]and domain['header_start_decimal']==52 and domain['header_stride_qwords']==10 and domain['relative_largest_read']==475 and domain['relative_largest_write']==481 and domain['relative_end_exclusive']==482,'Wrong actual43-decimal particle range/read/store bounds')
    need([x['end_exclusive']for x in domain['TOP_pages']]==[534,1020],'Out-of-VU-memory second-bank/wholeqword range')
    need(peer['status']=='PASS_COMPLETE_SOURCE_NATIVE_WITH_ADDITIVE_FLUSH_LABEL_QUALIFICATION_RUNTIME_NOT_REVIEWED'and peer['runtime_eligible_claim']is False,'Source/native peer must remain separate from original runtime eligibility')
    parent=docs['vu_particle_parent_review.json']
    need(parent['parent_review_status']=='PASS_COMPLETE_SOURCE_NATIVE_AND_BOUNDED_ACTUAL_STATE11_RUNTIME_ELIGIBLE_FOR_MAINTAINED_INTEGRATION'and parent['whole_code_bytes']==3800 and parent['whole_runtime_upload_bytes']==3824 and parent['VIF_control_bytes_separate']==24 and parent['actual_nonallocated_R32']==4 and parent['entire_initialized_data_BSS']==0 and parent['original_function_count']is None and parent['authored_source_partitions_not_original_functions']==3 and parent['whole_original_range_occurrences']==96 and parent['unique_whole_original_spans']==94 and parent['EE_anchor_count']==139 and parent['whole_VU_pairs']==475,'Missing exact final parent source/native/original runtime eligibility')
    need(parent['mandatory_additive_correction']['emitted_command']=='0x11000000'and parent['mandatory_additive_correction']['historical_MSCNT_label_is_wrong']is True and parent['mandatory_additive_correction']['no_microprogram_continuation_inferred']is True,'Final parent FLUSH correction is mandatory')
    runtime_peer=docs['vu_particle_runtime_peer_review.json']
    need(runtime_peer['status']=='PASS_INDEPENDENT_BOUNDED_ORIGINAL_RUNTIME_INPUT_LIFETIME_WITH_EXPLICIT_PREDICATES'and runtime_peer['family']==376117691 and runtime_peer['whole_original_range_occurrence_count']==96 and runtime_peer['unique_whole_original_spans']==94 and runtime_peer['EE_anchor_count']==139 and runtime_peer['original_VU_pair_count']==475 and runtime_peer['original_function_count']is None and runtime_peer['authored_partitions_are_original_functions']is False,'Missing independent actual runtime-input/lifetime peer')
    need(correction['actual_emitted_VIF_command']==0x11000000 and correction['actual_VIF_opcode']==0x11 and correction['actual_VIF_name']=='FLUSH'and correction['excluded_MSCNT_opcode']==0x17 and correction['no_MSCNT_or_inferred_cross_partition_resume']is True,'Historical MSCNT wording must remain withdrawn')
    helper=correction['actual_helper'];raw=e.at_vram(0x27e290,24);need(helper['address']==0x27e290 and helper['bytes']==24 and raw==bytes.fromhex(helper['whole_original_hex_input_only'])and sha(raw)==helper['sha256'],'Changed entire post-entry FLUSH helper')
    need(struct.unpack('<I',e.at_vram(0x27e294,4))[0]==correction['actual_27E294_LUI_A1_word']==0x3c051100 and struct.unpack('<I',e.at_vram(0x27e2a4,4))[0]==correction['actual_27E2A4_real_SW_delay_word'],'Changed actual FLUSH construction/SWdelay')
    need(correction['actual_EE_call_sites']==[0x14ab70,0x2016f8]and correction['actual_MSCAL_entries_VU_bytes']==[0,0x398,0x880]and correction['actual_MSCAL_instruction_immediates']==[0,0x73,0x110],'Confused actual VU byte address and VIF instruction immediate')
    need(correction['canonical_source_all_bytes_identical']is True and correction['canonical_VIF_all_bytes_identical']is True and correction['canonical_source_comment_changes']==[],'Unreviewed source/protocol/comment changes')
    need(len(support['whole_original_VU_pairs_input_only'])==475,'Missing original entire VU pair input capture')
    return occurrences

def checked_manifest(bundle=DEFAULT_BUNDLE):
    bundle=Path(bundle).resolve();m=json.loads(renderer.contained(bundle,'config/vu_particle_sources.json').read_bytes());validate_manifest(m)
    # Final root and independent eligibility receipts are mandatory. Any
    # unresolved preparation flag prevents native assembly or report acceptance.
    need(not PREPARATION_ONLY_UNRUN and not PENDING_REQUIRED_EVIDENCE,'UNRUN component preparation: final parent/runtime-peer eligibility pins and schema are still pending')
    e,_,_,programs=renderer.original_mapping();original=next(p for p in programs if p['family_file_name_hash']=='376117691')
    program=b''.join(e.at_vram(c['EE_payload_begin'],c['code_bytes'])for c in original['chunks']);chain=e.at_vram(0x2c0520,3824)
    need(original['VU_bytes']==3800 and len(original['chunks'])==2 and sha(program)==EXPECTED_COMPONENT['program_sha256']and sha(chain)==EXPECTED_COMPONENT['chain_sha256'],'Wrong complete3800 program or3824 consumed transfer')
    need([c['code_bytes']for c in original['chunks']]==[2048,1752]and[c['EE_payload_begin']for c in original['chunks']]==[0x2c0528,0x2c0d30],'Wrong whole MPG/chunk/address boundaries')
    for a,n,vu in[(0x2c0520,2048,0),(0x2c0d28,1752,2048)]:
        z,w=struct.unpack('<II',e.at_vram(a,8));need(z==0 and w>>24==0x4a and(w&65535)*8==vu and((w>>16&255)or 256)*8==n,'Wrong original full MPG header/count')
    need(chain[3816:]==bytes(8),'Missing two actual consumed static VIFNOPs')
    deps={};docs={}
    for rel in required_dependencies():
        p=renderer.contained(bundle,rel);deps[p.relative_to(ROOT).as_posix()]=sha(p.read_bytes())
        if rel in EXPECTED_EVIDENCE:
            need(sha(p.read_bytes())==EXPECTED_EVIDENCE[rel],'Closed original/source/peer/protocol evidence changed');docs[rel.rsplit('/',1)[1]]=json.loads(p.read_bytes())
    for key,pin in[('source','source_sha256'),('chain_source','chain_source_sha256')]:
        p=renderer.contained(bundle,EXPECTED_COMPONENT[key]);need(sha(p.read_bytes())==EXPECTED_COMPONENT[pin],'Complete readable particle source changed');need(not any(t in p.read_text().lower()for t in['.word','.byte','.long','.quad','.incbin','.org','.space','.fill']),'Original binary preservation is not decompiled VU source')
    source=renderer.contained(bundle,EXPECTED_COMPONENT['source']).read_text();vif=renderer.contained(bundle,EXPECTED_COMPONENT['chain_source']).read_text();semantic=[x.split(';',1)[0].strip()for x in vif.splitlines()if x.split(';',1)[0].strip()]
    need('.include'not in source and semantic==['.global particle_upload_begin','.global particle_upload_end','particle_upload_begin:','mpg 0,*','.include "particle_program.vsm"','.endmpg','vifnop','vifnop','particle_upload_end:'],'Incomplete whole particle source/upload recipe')
    inputs=verify_original_inputs(e,docs)
    primary=docs['vu_particle_shadow_primary_classification.json'];need(primary['all7_primary_files_pinned']and len(primary['all7_primary_files_pinned'])==7,'Missing exact uniform-shadow allocation/emission primary proof')
    for row in primary['all7_primary_files_pinned']:
        p=renderer.contained(ROOT,row['path']);need(sha(p.read_bytes())==row['sha256'],'Changed exact DVP shadow allocation/emission primary source');deps[row['path']]=row['sha256']
    for row in docs['vu_particle_runtime_input_review.json']['immutable_input_pins']:
        p=Path(row['path']).resolve()
        if not p.is_relative_to(ROOT):
            need(p.is_relative_to(Path('C:/Users/PC/Documents/GitHub/sly2-decomp'))or p.is_relative_to(Path('C:/Users/PC/Documents/GitHub/ProjectCane')),'Unexpected external attribution path');continue
        need(p.stat().st_size==row['bytes']and sha(p.read_bytes())==row['sha256'],'Changed frozen original/runtime/source input pin');deps[p.relative_to(ROOT).as_posix()]=row['sha256']
    provenance=ROOT/'tools/third_party/dvp/provenance.json';need(sha(provenance.read_bytes())==PROVENANCE_SHA,'Changed installed original portable native profile');deps[provenance.relative_to(ROOT).as_posix()]=PROVENANCE_SHA
    for row in json.loads(provenance.read_bytes())['files']:
        p=renderer.contained(ROOT,row['path']);need(p.stat().st_size==row['bytes']and sha(p.read_bytes())==row['sha256'],'Changed pinned native tool/runtime/license');deps[row['path']]=row['sha256']
    for rel in['tools/common.py','tools/vu_build.py','config/vu_original_programs.json']:
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
    need(r.get('kind')=='complete-eighth-readable-native-VU-particle-source-component' and r.get('bundle_root')==bundle.relative_to(ROOT).as_posix() and r.get('component')==EXPECTED_COMPONENT,'Foreign/missing particle current report')
    need(r.get('dependency_hashes')==deps and r.get('complete_original_input_ranges')==[list(x) for x in inputs],'Stale source/native/input report')
    need(set(r['native_components'])=={'program','chain'},'Missing/extra native particle component')
    job=r.get('native_job')
    for kind in ['program','chain']:
        item=r['native_components'][kind];validate_native_record(item,kind,bundle,out,job)
        need(set(item['files'])=={kind+'.o',kind+'.bin'},'Missing/extra complete native file')
        for n in [kind+'.o',kind+'.bin']:need(item['files'][n]==receipt(out/n),'Whole current native output fingerprint changed')
        proof=strict_native((out/(kind+'.o')).read_bytes(),kind,expected[kind],ROLES)
        need(item['native_proof']==proof and (out/(kind+'.bin')).read_bytes()==expected[kind],'False whole native/initialized-section/relocation proof')
    log={'native_job':job,'commands':[{'kind':k,'source':r['native_components'][k]['source'],'source_sha256':r['native_components'][k]['source_sha256'],'actual_native_command':r['native_components'][k]['actual_native_command']} for k in ['program','chain']]}
    need(r.get('native_command_log')==receipt(out/'actual_native_commands.json') and json.loads((out/'actual_native_commands.json').read_bytes())==log,'Missing/forged actual native command log')
    need(r.get('verified_original_function_count','missing') is None and r.get('source_partitions_not_original_functions')==3 and r.get('initialized_data_bytes')==r.get('BSS_bytes')==r.get('dynamic_REFS_source_credit')==0,'False routine/data/dynamic-input source count')
    need(r.get('post_entry_actual_VIF_command')==0x11000000 and r.get('post_entry_actual_VIF_name')=='FLUSH' and r.get('whole_original_input_range_occurrences')==96 and r.get('unique_original_input_ranges')==94 and r.get('distinct_original_operand_anchors')==139,'False FLUSH/range/anchor predicate')
    need(all(r.get(k) is False for k in ['historical_original_compiler_identity_confirmed','full_source_relink_complete','live_runtime_execution_observed','unknown_predecessor_or_universal_asset_domain_claim']),'False compiler/universal/runtime/relink claim')

def current_report(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT):
    bundle=Path(bundle).resolve();out=output_path(output);m,e,expected,inputs,deps=checked_manifest(bundle);r=json.loads((out/REPORT_NAME).read_bytes())
    validate_report(r,bundle,out,expected,inputs,deps)
    return {**r,'freshness':'CURRENT_WHOLE3800_PARTICLE_AND3824_CHAIN_QUALIFIED_DYNAMIC_CID26_STATE11_FRAME_VERIFIED'}

def run(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT,fresh=False):
    bundle=Path(bundle).resolve();out=output_path(output)
    if out.exists() and any(out.iterdir()):
        need(not fresh,'Fresh native particle proof needs empty output')
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
        need(actual==native_command(kind,bundle,out,tmp),'Pinned native particle assembly failed or emitted unexpected diagnostics')
        proof=strict_native((out/(kind+'.o')).read_bytes(),kind,expected[kind],ROLES);elf=Elf32((out/(kind+'.o')).read_bytes());(out/(kind+'.bin')).write_bytes(elf.section_data(elf.section('.vutext')))
        native[kind]={'files':{n:receipt(out/n) for n in [kind+'.o',kind+'.bin']},'native_proof':proof,'actual_native_command':actual,'source_sha256':sha(p.read_bytes()),'source':receipt(p),'native_job':job}
    r={'kind':'complete-eighth-readable-native-VU-particle-source-component','bundle_root':bundle.relative_to(ROOT).as_posix(),'component':EXPECTED_COMPONENT,'dependency_hashes':deps,'complete_original_input_ranges':inputs,'native_components':native,'native_job':job,'native_command_log':receipt(out/'actual_native_commands.json'),'post_entry_actual_VIF_command':0x11000000,'post_entry_actual_VIF_name':'FLUSH','whole_original_input_range_occurrences':96,'unique_original_input_ranges':94,'distinct_original_operand_anchors':139,'verified_original_function_count':None,'source_partitions_not_original_functions':3,'initialized_data_bytes':0,'BSS_bytes':0,'dynamic_REFS_source_credit':0,'historical_original_compiler_identity_confirmed':False,'full_source_relink_complete':False,'live_runtime_execution_observed':False,'unknown_predecessor_or_universal_asset_domain_claim':False}
    (out/REPORT_NAME).write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    return current_report(bundle,out)

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--fresh',action='store_true');p.add_argument('--check',action='store_true');a=p.parse_args();r=current_report(a.bundle_root,a.output) if a.check else run(a.bundle_root,a.output,a.fresh);print(json.dumps({'status':'PASS','component':r['component'],'freshness':r['freshness'],'original_function_count':None}))
if __name__=='__main__':main()
