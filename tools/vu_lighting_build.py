"""Mandatory whole fourth VU lighting program; EE source counts stay separate.
Pure APIs re-read all original/input/source/compiler/native dependencies.
"""
import argparse,hashlib,json,struct,subprocess,sys
from pathlib import Path
sys.dont_write_bytecode=True
HERE=Path(__file__).resolve();ROOT=next(p for p in HERE.parents if(p/'disc/SCUS_974.64').is_file())
sys.path.insert(0,str(ROOT/'tools'))
from common import Elf32
import vu_build as renderer
from vu_lighting_native import strict_native,ENTRIES
from vu_lighting_inputs import checked_inputs,same
DEFAULT_BUNDLE=HERE.parents[1]
DEFAULT_OUTPUT=ROOT/'build/vu/lighting'
REPORT_NAME='vu_lighting_report.json'
ORIGINAL_SHA='ce817858306efd711f08bbc14f393455280119cb00b894bdc9fb1fa47bcbb338'
PROGRAM_SHA='e464ebda93326068bb753a26839b888196eb35fd27698d6463778fc085ab4739'
CHAIN_SHA='1ba060cbe09341fa8c6be9ed41a791f44172a5e28818ee33deedb6a08b793b6d'
PROVENANCE_SHA='2199c34122dcb130521cbc1690a2a3f996cd9f59f1c4886055a88ed4354a1ea7'
EXPECTED_COMPONENT={'family': '752237851', 'processor': 'VU1', 'source_language': 'readable-native-VSM-VIF', 'source': 'src/vu/lighting/lighting_program_v2.vsm', 'upload_source': 'src/vu/lighting/lighting_upload_v2.vif', 'source_sha256': '167ec6d32d634ff113c37c88e707d684a6e125334713ea70b0630d1c5b7abcd8', 'upload_source_sha256': '82a8fa1991690db7ce6c7fb6c319d68d6960cd676ee9d578371b1898c95dc0f6', 'program_sha256': 'e464ebda93326068bb753a26839b888196eb35fd27698d6463778fc085ab4739', 'upload_sha256': '1ba060cbe09341fa8c6be9ed41a791f44172a5e28818ee33deedb6a08b793b6d', 'original_EE_upload_begin': 2901504, 'original_EE_payload_begin': 2901512, 'original_EE_upload_end': 2903008, 'VU_code_bytes': 1488, 'entire_static_upload_bytes': 1504, 'VIF_static_control_bytes': 16, 'DMA_static_control_bytes': 0, 'routines': [{'name': 'light_idle', 'VU_byte_begin': 0, 'code_bytes': 16}, {'name': 'light_batch', 'VU_byte_begin': 16, 'code_bytes': 1344}, {'name': 'light_inverse_normal_matrix', 'VU_byte_begin': 1360, 'code_bytes': 128}], 'initialized_data_bytes': 0, 'BSS_bytes': 0, 'allocated_code_relocations': 0, 'nonallocated_overlay_R32_fields': 2, 'dynamic_REFS_control_bytes_evidence_only': 16, 'dynamic_REFS_source_credit': 0, 'runtime_binding_evidence': {'path': 'docs/evidence/vu_lighting_runtime_parent_review.json', 'sha256': '8d1518fe41dbb40b2d497fa930902360dd4864860a72b62eea56e77b9660de42'}, 'runtime_scope': 'Only loaded v_alarm_light/CID2F node0/surface1type1 with captured lifetime/visibility/queue/DMA/nullclient predicates; no universal class or live hardware claim.', 'actual_MSCAL_instruction_immediate': 2, 'corresponding_VU_byte_entry': 16, 'same_local_byteaddress_in_other_programs_is_not_family_alias': True, 'full_game_source_metadata_relink_complete': False}
EXPECTED_EVIDENCE_HASHES={'docs/evidence/vu_lighting_frame_submission_review.json': '4937d41bbc42de43d8119555e16a44a8bbcb43b58b002e625d694f7bed187f9d', 'docs/evidence/vu_lighting_runtime_binding_review.json': '32c8c69102837da0ecb9cdaff60dc7342453a00de06a18478f43fd5968a51c3e', 'docs/evidence/vu_lighting_runtime_parent_review.json': '8d1518fe41dbb40b2d497fa930902360dd4864860a72b62eea56e77b9660de42', 'docs/evidence/vu_lighting_runtime_refs_control.vif': '6d8c0c4ad36a7bb2fe592197004f2112af8f2f270019877e5d23610ca022f008'}

def sha(data):return hashlib.sha256(data).hexdigest()
def need(condition,message):
    if not condition:raise ValueError(message)
def receipt(path):return renderer.file_receipt(Path(path).resolve(),ROOT)
def output_path(output):
    p=Path(output).resolve();allowed=[ROOT/'build/vu/lighting',ROOT/'build/vu/extra/testing',ROOT/'build/vu_matches/program_752237851_integration_20261014',ROOT/'build/vu_matches/union_stage']
    need(any(p==a or p.is_relative_to(a)for a in allowed),'Lighting output escapes explicit maintained/private owner')
    return p

def checked_manifest(bundle=DEFAULT_BUNDLE):
    bundle=Path(bundle).resolve();manifest_path=renderer.contained(bundle,'config/vu_lighting_sources.json');m=json.loads(manifest_path.read_text())
    need(m.get('schema')==1 and m.get('kind')=='mandatory-fourth-complete-readable-native-VU-lighting-component' and m.get('component')==EXPECTED_COMPONENT,'Missing/duplicate/incomplete lighting source owner')
    need(m.get('original_sha256')==ORIGINAL_SHA and m.get('original_unique_program_count')==9 and m.get('original_unique_program_code_bytes')==50032 and m.get('original_nonallocated_zero_shadow_count')==29,'Wrong unique original program denominator')
    need(m.get('initialized_data_bytes')==m.get('BSS_bytes')==m.get('EE_C_CPP_functions_delta')==m.get('EE_C_CPP_code_bytes_delta')==m.get('dynamic_REFS_source_credit')==0,'False data/BSS/EE or dynamicREFS source count')
    need(m.get('existing_three_program_owners_mandatory')is True and m.get('old_Bentley_type0_entry_and_part8_population_withdrawn')is True,'Foreign owner or historical false witness')
    need(m.get('historical_original_compiler_identity_confirmed')is False and m.get('full_source_relink_complete')is False and m.get('live_runtime_execution_observed')is False and m.get('universal_class_or_asset_domain_claim')is False,'Unsupported full-relink/compiler/runtime scope')
    need(m.get('evidence_hashes')==EXPECTED_EVIDENCE_HASHES and m.get('portable_provenance_sha256')==PROVENANCE_SHA,'Missing original input/parent/tool provenance')
    e,_,_,programs=renderer.original_mapping();program=e.at_vram(0x2c4608,1488);chain=e.at_vram(0x2c4600,1504)
    original=next(p for p in programs if p['family_file_name_hash']=='752237851')
    need(original['VU_bytes']==1488 and original['entire_program_sha256']==PROGRAM_SHA and sha(program)==PROGRAM_SHA and sha(chain)==CHAIN_SHA,'Whole original family/payload/transfer mapping changed')
    deps={manifest_path.relative_to(ROOT).as_posix():receipt(manifest_path)['sha256']}
    for key,want in [('source','source_sha256'),('upload_source','upload_source_sha256')]:
        p=renderer.contained(bundle,EXPECTED_COMPONENT[key]);need(sha(p.read_bytes())==EXPECTED_COMPONENT[want],'Readable complete native source changed');deps[p.relative_to(ROOT).as_posix()]=sha(p.read_bytes())
        need(not any(t in p.read_text().lower()for t in ['.word','.byte','.long','.quad','.incbin','.org','.space']),'Raw original instruction/data preservation cannot be source')
    source=renderer.contained(bundle,EXPECTED_COMPONENT['source']).read_text();wrapper=renderer.contained(bundle,EXPECTED_COMPONENT['upload_source']).read_text()
    need('.include'not in source.lower() and 'angular_weight'in source and 'begin_internal_routine light_inverse_normal_matrix'in source,'Incomplete readable whole algorithm/internal helper')
    need(wrapper.count('.include "lighting_program_v2.vsm"')==1 and wrapper.count('vifnop')==2,'Unowned include or missing whole extraVIFNOPs')
    for rel,want in EXPECTED_EVIDENCE_HASHES.items():
        p=renderer.contained(bundle,rel);need(sha(p.read_bytes())==want,'Corrected runtime/parent/control evidence changed');deps[p.relative_to(ROOT).as_posix()]=want
    dyn=m['dynamic_REFS_evidence_source'];need(dyn=='docs/evidence/vu_lighting_runtime_refs_control.vif'and m['dynamic_REFS_evidence_source_sha256']==EXPECTED_EVIDENCE_HASHES[dyn],'DynamicREFS source-evidence identity changed')
    need('dmarefs 94,original_light_upload_EE_address'in renderer.contained(bundle,dyn).read_text(),'Runtime REFS evidence must be meaningful control source')
    provenance=ROOT/'tools/third_party/dvp/provenance.json';need(sha(provenance.read_bytes())==PROVENANCE_SHA,'Portable official release provenance changed');p=json.loads(provenance.read_text());deps[provenance.relative_to(ROOT).as_posix()]=PROVENANCE_SHA
    need(p['system_installation']is False and p['environment_changes']is False and p['version']=='GNU Binutils 2.45.1','Unreviewed compiler profile/environment')
    for row in p['files']:
        tool=renderer.contained(ROOT,row['path']);need(tool.stat().st_size==row['bytes']and sha(tool.read_bytes())==row['sha256'],'Pinned compiler/runtime/license dependency changed');deps[row['path']]=row['sha256']
    for rel in ['tools/common.py','tools/vu_build.py','tools/vu_lighting_build.py','tools/vu_lighting_native.py','tools/vu_lighting_inputs.py','tools/test_vu_lighting.py','config/vu_original_programs.json','build/asset_catalog/level_tag_05.decoded.bin']:
        p=renderer.contained(bundle,rel);deps[p.relative_to(ROOT).as_posix()]=sha(p.read_bytes())
    actual=checked_inputs(e,bundle,m)
    return m,e,{'program':program,'chain':chain,'runtime_REFS':struct.pack('<4I',0x4000005e,0x2c4600,0,0)},actual,dict(sorted(deps.items()))

def current_report(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT):
    bundle=Path(bundle).resolve();out=output_path(output);m,e,expected,inputs,deps=checked_manifest(bundle);r=json.loads((out/REPORT_NAME).read_text())
    need(r.get('kind')=='complete-fourth-readable-native-VU-lighting-source-component'and r.get('bundle_root')==bundle.relative_to(ROOT).as_posix()and r.get('component')==EXPECTED_COMPONENT,'Foreign/incomplete current lighting report')
    need(r.get('dependency_hashes')==deps,'Stale lighting source/compiler/evidence dependencies')
    need(same(r.get('complete_original_input_review'),inputs),'False current whole original input/body/gate proof')
    need(set(r['native_components'])=={'program','chain','runtime_REFS'},'Missing/extra whole native source/control proof')
    for kind in ['program','chain','runtime_REFS']:
        item=r['native_components'][kind];names={'program':['program.o','program.bin'],'chain':['chain.o','chain.bin'],'runtime_REFS':['runtime_REFS.o','runtime_REFS.bin']}[kind]
        for name in names:need(item['files'][name]==receipt(out/name),'Current whole native output fingerprint changed')
        proof=strict_native((out/names[0]).read_bytes(),'upload'if kind=='chain'else kind,expected[kind])
        need(same(item['native_proof'],proof)and(out/names[1]).read_bytes()==expected[kind],'False incomplete initialized/native/control proof')
    need(r.get('initialized_data_bytes')==r.get('BSS_bytes')==r.get('dynamic_REFS_source_credit')==0 and r.get('historical_original_compiler_identity_confirmed')is False and r.get('full_source_relink_complete')is False,'False source data/compiler/relink claim')
    need(r['old_Bentley_type0_entry_and_part8_claims_withdrawn']is True and r['actual_MSCAL_immediate']==2 and r['actual_VU_byte_entry']==16,'Stale entry polarity/address domain')
    return {**r,'freshness':'CURRENT_COMPLETE_FOURTH_VU_PROGRAM_FULL1504_UPLOAD_CORRECTED_REAL_TYPE1_INPUTS_VERIFIED'}

def run(bundle=DEFAULT_BUNDLE,output=DEFAULT_OUTPUT,fresh=False):
    bundle=Path(bundle).resolve();out=output_path(output)
    need(not(fresh and out.exists()and any(out.iterdir())),'Fresh lighting replay needs a new empty output')
    m,e,expected,inputs,deps=checked_manifest(bundle);out.mkdir(parents=True,exist_ok=True);native={};exe=ROOT/'tools/third_party/dvp/bin/dvp-as.exe'
    jobs=[('program',EXPECTED_COMPONENT['source'],['--defsym','VU_NATIVE_STANDALONE=1']),('chain',EXPECTED_COMPONENT['upload_source'],[]),('runtime_REFS',m['dynamic_REFS_evidence_source'],[])]
    for kind,rel,flags in jobs:
        p=renderer.contained(bundle,rel);cmd=[str(exe),'-I',str(renderer.contained(bundle,EXPECTED_COMPONENT['source']).parent),*flags,'-o',str(out/(kind+'.o')),str(p)]
        completed=subprocess.run(cmd,cwd=p.parent,capture_output=True,text=True,timeout=30)
        need(completed.returncode==0 and not completed.stderr,'Pinned native lighting assembly failed: '+completed.stderr)
        proof=strict_native((out/(kind+'.o')).read_bytes(),'upload'if kind=='chain'else kind,expected[kind])
        parsed=Elf32((out/(kind+'.o')).read_bytes());(out/(kind+'.bin')).write_bytes(parsed.section_data(parsed.section('.vutext')))
        native[kind]={'source':renderer.file_receipt(p,bundle),'files':{name:receipt(out/name)for name in[kind+'.o',kind+'.bin']},'actual_native_command':cmd,'native_proof':proof,'source_code_credit':0 if kind=='runtime_REFS'else(1488 if kind=='program'else 0),'static_control_credit':16 if kind=='chain'else 0}
    r={'kind':'complete-fourth-readable-native-VU-lighting-source-component','bundle_root':bundle.relative_to(ROOT).as_posix(),'component':EXPECTED_COMPONENT,'dependency_hashes':deps,'complete_original_input_review':inputs,'native_components':native,'initialized_data_bytes':0,'BSS_bytes':0,'dynamic_REFS_source_credit':0,'old_Bentley_type0_entry_and_part8_claims_withdrawn':True,'actual_MSCAL_immediate':2,'actual_VU_byte_entry':16,'historical_original_compiler_identity_confirmed':False,'full_source_relink_complete':False,'live_runtime_observed':False,'original_debug_names_and_zero_shadows_source_credit':0}
    (out/REPORT_NAME).write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8');return current_report(bundle,out)

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--fresh',action='store_true');p.add_argument('--check',action='store_true');a=p.parse_args()
    r=current_report(a.bundle_root,a.output)if a.check else run(a.bundle_root,a.output,a.fresh)
    print(json.dumps({'status':'PASS','component':r['component'],'report':receipt(output_path(a.output)/REPORT_NAME),'freshness':r['freshness'],'dynamic_REFS_source_credit':0}))
if __name__=='__main__':main()
