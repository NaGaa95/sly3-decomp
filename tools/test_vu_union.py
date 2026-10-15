"""Meaningful VU union/native/fingerprint guards; only exact dependencies are copied."""
import argparse,copy,json,struct,tempfile
from pathlib import Path
from vu_extra_build import *
import vu_union_sources as union
import vu_lighting_build as lighting
import test_vu_lighting as lighting_tests
import vu_mesh_build as mesh
import test_vu_mesh as mesh_tests
import vu_mesh_alt_build as mesh_alt
import test_vu_mesh_alt as mesh_alt_tests
import vu_volume_build as volume
import test_vu_volume as volume_tests
import vu_particle_build as particle
import test_vu_particle as particle_tests
import vu_silhouette_build as silhouette
import test_vu_silhouette as silhouette_tests
def math_guards(program_object,chain_object,program,chain):
    candidates=[];pe=Elf32(program_object);ce=Elf32(chain_object);pt=pe.section('.vutext');ct=ce.section('.vutext');symbols=pe.section('.symtab')
    def word(raw,label,at,value,kind):
        b=bytearray(raw);struct.pack_into('<I',b,at,value);candidates.append((kind,label,bytes(b)))
    def sh(e,s,field):return e.shoff+e.shentsize*s['index']+field
    for name,begin,size in EXPECTED_MATH:
        word(program_object,'wrong native operand '+name,pt['offset']+begin,struct.unpack_from('<I',program_object,pt['offset']+begin)[0]^1,'program')
        sym=next(s for s in pe.symbols()if s['name']==name)
        word(program_object,'partial declared routine '+name,symbols['offset']+sym['index']*16+8,size-8,'program')
        word(program_object,'EE address aliases VU '+name,symbols['offset']+sym['index']*16+4,0x2c0260+begin,'program')
    for name in['.vudata','.vubss']:
        s=pe.section(name);word(program_object,'unowned allocated '+name,sh(pe,s,20),16,'program')
    word(program_object,'incomplete allocated native program',sh(pe,pt,20),664,'program')
    for at,label in[(0x1c0,'LOI400'),(0x230,'MAC read'),(0x260,'status read'),(0x240,'first branch'),(0x248,'branch-delay upper subtraction'),(0x298,'final delay')]:
        word(program_object,'changed native '+label,pt['offset']+at,struct.unpack_from('<I',program_object,pt['offset']+at)[0]^1,'program')
    word(chain_object,'wrong DMA QWC43',ct['offset'],0x1000002a,'chain')
    word(chain_object,'wrong packed MPG84',ct['offset']+12,0x4a530000,'chain')
    word(chain_object,'wrong startup idle entry',ct['offset']+688,0x14000001,'chain')
    word(chain_object,'wrong terminal DMA END',ct['offset']+704,0x60000000,'chain')
    word(chain_object,'truncated whole native chain',sh(ce,ct,20),704,'chain')
    rel=ce.section('.rel.DVP.ovlytab');tab=ce.section('.DVP.ovlytab');shadow=next(s for s in ce.sections if s['name'].startswith('.DVP.overlay.'))
    word(chain_object,'missing actual metadata relocation',sh(ce,rel,20),8,'chain')
    word(chain_object,'wrong actual metadata relocation type',rel['offset']+4,struct.unpack_from('<I',chain_object,rel['offset']+4)[0]&~255|5,'chain')
    word(chain_object,'wrong original payload load offset',tab['offset']+4,8,'chain')
    word(chain_object,'wrong original local VU destination',tab['offset']+8,8,'chain')
    word(chain_object,'metadata incorrectly allocated',sh(ce,tab,8),3,'chain')
    word(chain_object,'shadow incorrectly allocated',sh(ce,shadow,8),7,'chain')
    word(chain_object,'nonzero preserved shadow counted',shadow['offset'],1,'chain')
    tests=[]
    for kind,label,data in candidates:
        try:(math_program if kind=='program'else math_chain)(data,program if kind=='program'else chain)
        except (ValueError,KeyError,IndexError,StopIteration,struct.error)as ex:tests.append({'mode':kind,'mutation':label,'rejected':True,'actual_exception':type(ex).__name__,'actual_reason':str(ex)})
        else:raise ValueError('Malformed native admission: '+label)
    return tests
def idle_guards(program_object,chain_object,code,chain):
    pe=Elf32(program_object);ce=Elf32(chain_object);pt=pe.section('.vutext');ct=ce.section('.vutext');ps=pe.section('.symtab');f=next(s for s in pe.symbols()if s['name']=='vu1_startup_idle');tests=[]
    def reject(raw,label,pos,value,kind):
        b=bytearray(raw);struct.pack_into('<I',b,pos,value)
        try:(idle_program if kind=='program'else idle_chain)(bytes(b),code if kind=='program'else chain)
        except (ValueError,KeyError,IndexError,StopIteration,struct.error)as ex:tests.append({'mode':kind,'mutation':label,'rejected':True,'actual_exception':type(ex).__name__,'actual_reason':str(ex)})
        else:raise ValueError('Malformed native idle/chain admission: '+label)
    for off,value,label in[(0,0x10010001,'new VI side effect'),(4,0x2ff,'missing E'),(8,0x10010001,'changed required final delay')]:reject(program_object,label,pt['offset']+off,value,'program')
    reject(program_object,'partial function',ps['offset']+16*f['index']+8,8,'program')
    reject(program_object,'EE alias used as VU address',ps['offset']+16*f['index']+4,0x2c45d0,'program')
    for name in['.vudata','.vubss']:
        s=pe.section(name);reject(program_object,'unowned'+name,pe.shoff+pe.shentsize*s['index']+20,4,'program')
    for off,value,label in[(0,0x10000001,'wrong DMA count'),(12,0x4a010000,'wrong MPG count'),(32,0x14000001,'wrong idle entry'),(48,0x60000000,'wrong END')]:reject(chain_object,label,ct['offset']+off,value,'chain')
    tab=ce.section('.DVP.ovlytab');rel=ce.section('.rel.DVP.ovlytab');shadow=next(s for s in ce.sections if s['name'].startswith('.DVP.overlay.'))
    reject(chain_object,'missing metadata relocation',ce.shoff+ce.shentsize*rel['index']+20,8,'chain')
    reject(chain_object,'wrong metadata relocation type',rel['offset']+4,struct.unpack_from('<I',chain_object,rel['offset']+4)[0]&~255|5,'chain')
    reject(chain_object,'wrong EE load offset',tab['offset']+4,8,'chain')
    reject(chain_object,'shadow made allocated',ce.shoff+ce.shentsize*shadow['index']+8,7,'chain')
    reject(chain_object,'shadow nonzero',shadow['offset'],1,'chain')
    return tests

def clone_dependencies(bundle,dest):
    _,_,_,_,deps,_=checked_manifest(bundle)
    if len(deps)!=11:raise ValueError('Only exact eleven extra-source dependencies may be cloned')
    for rel,row in deps.items():
        source=renderer.contained(bundle,rel);target=renderer.contained(dest,rel);data=source.read_bytes()
        if len(data)!=row['bytes']or sha(data)!=row['sha256']:raise ValueError('Dependency changed before isolated fixture copy')
        target.parent.mkdir(parents=True,exist_ok=True)
        with target.open('xb')as f:f.write(data)
    lighting_deps=set(lighting_tests.DEPS)
    for rel in sorted(lighting_deps-set(deps)):
        source=renderer.contained(bundle,rel);target=renderer.contained(dest,rel);target.parent.mkdir(parents=True,exist_ok=True)
        with target.open('xb')as f:f.write(source.read_bytes())
    if {p.relative_to(dest).as_posix()for p in dest.rglob('*')if p.is_file()}!=set(deps)|lighting_deps:raise ValueError('Foreign project data cloned into fixture')
    return {'files':len(set(deps)|lighting_deps),'bytes':sum(p.stat().st_size for p in dest.rglob('*')if p.is_file()),'enclosing_project_build_disc_references_IOP_environment_never_copied':True}

def clone_native(output,dest):
    dest.mkdir(parents=True)
    for rel in ['vu_extra_report.json',*[c['family']+'/'+n for c in EXPECTED_COMPONENTS for n in ['program.o','chain.o','chain.bin']]]:
        target=renderer.contained(dest,rel);target.parent.mkdir(parents=True,exist_ok=True)
        with target.open('xb')as f:f.write(renderer.contained(output,rel).read_bytes())

def run_tests(bundle=DEFAULT_BUNDLE,extra_output=DEFAULT_OUTPUT,union_output=union.DEFAULT_UNION,temp_root=None,lighting_output=lighting.DEFAULT_OUTPUT):
    bundle=Path(bundle).resolve();extra_output=Path(extra_output).resolve();m,e,proofs,legacy,deps,hashes=checked_manifest(bundle)
    fifth=mesh_tests.run_tests(bundle,mesh.DEFAULT_OUTPUT);sixth=mesh_alt_tests.run_tests(bundle,mesh_alt.DEFAULT_OUTPUT);seventh=volume_tests.run_tests(bundle,volume.DEFAULT_OUTPUT);eighth=particle_tests.run_tests(bundle,particle.DEFAULT_OUTPUT);ninth=silhouette_tests.run_tests(bundle,silhouette.DEFAULT_OUTPUT)
    original_renderer=receipt(renderer.DEFAULT_OUTPUT/renderer.REPORT_NAME);native=[]
    for c in EXPECTED_COMPONENTS:
        folder=extra_output/c['family'];native+= (math_guards if c['processor']=='VU0'else idle_guards)((folder/'program.o').read_bytes(),(folder/'chain.o').read_bytes(),proofs[c['family']]['program'],proofs[c['family']]['chain'])
    if len(native)!=58:raise ValueError('Incomplete math/bootstrap native guards')
    extras_current=current_report(bundle,extra_output);union.current_report(bundle,extra_output,union_output,lighting_output=lighting_output)
    temp_root=Path(temp_root or(ROOT/'build/vu/extra/testing')).resolve()
    if not(temp_root.is_relative_to(ROOT/'build/vu/extra/testing')or temp_root.is_relative_to(ROOT/'build/vu_matches/union_stage')):raise ValueError('Tests escape extra VU ownership')
    temp_root.mkdir(parents=True,exist_ok=True);source_guards=[];receipt_guards=[]
    with tempfile.TemporaryDirectory(dir=temp_root,prefix='exact_dependencies_')as temp:
        temp=Path(temp);cloned=temp/'bundle';copyproof=clone_dependencies(bundle,cloned)
        mutations=[(rel,lambda b:b+b' ')for rel in [c['source']for c in EXPECTED_COMPONENTS]+[c['chain_source']for c in EXPECTED_COMPONENTS]+[c['evidence']for c in EXPECTED_COMPONENTS]+['docs/evidence/vu_math_bootstrap_parent_review.json']]
        mutations += [('config/vu_extra_sources.json',lambda b:change_manifest(b,'duplicate')),('config/vu_extra_sources.json',lambda b:change_manifest(b,'overlap')),('config/vu_extra_sources.json',lambda b:change_manifest(b,'protocol_as_code')),('config/vu_extra_sources.json',lambda b:change_manifest(b,'hide_unknown_entry'))]
        for rel,fn in mutations:
            target=cloned/rel;old=target.read_bytes();target.write_bytes(fn(old))
            try:checked_manifest(cloned)
            except(ValueError,KeyError,IndexError)as ex:source_guards.append({'mutation':rel,'rejected':True,'actual_exception':type(ex).__name__,'actual_reason':str(ex)})
            else:raise ValueError('False source/protocol/ownership acceptance')
            finally:target.write_bytes(old)
        fixture=temp/'native';clone_native(extra_output,fixture);base=json.loads((fixture/REPORT_NAME).read_text());base['bundle_root']=cloned.relative_to(ROOT).as_posix();base['dependency_hashes']=checked_manifest(cloned)[5]
        for c in EXPECTED_COMPONENTS:
            item=base['native_components'][c['family']];item['files']={n:receipt(fixture/c['family']/n)for n in ['program.o','chain.o','chain.bin']}
        (fixture/REPORT_NAME).write_text(json.dumps(base),encoding='utf-8');current_report(cloned,fixture)
        changes=[('missing native program',lambda r:r['native_components'].pop('11753275')),('duplicate/missing source owner',lambda r:r['components'].pop()),('false initialized data',lambda r:r.__setitem__('initialized_data_bytes',16)),('hide dynamic1C0 unknown',lambda r:r.__setitem__('unconfirmed_dynamic_VU0_entry_1C0',False)),('missing real metadata relocation',lambda r:r['native_components']['11753275']['native_proof']['actual_resolved_nonallocated_metadata_relocations'].pop()),('false source fingerprint',lambda r:r['dependency_hashes'].__setitem__('disc/SCUS_974.64','0'*64))]
        for label,fn in changes:
            altered=copy.deepcopy(base);fn(altered);(fixture/REPORT_NAME).write_text(json.dumps(altered),encoding='utf-8')
            try:current_report(cloned,fixture)
            except(ValueError,KeyError,IndexError)as ex:receipt_guards.append({'mutation':label,'rejected':True,'actual_exception':type(ex).__name__,'actual_reason':str(ex)})
            else:raise ValueError('False extra native report acceptance')
        lf=temp/'lighting_native';lighting_tests.clone_native(lighting_output,lf);lighting_tests.rebase_report(cloned,lf)
        # Retain every legacy union receipt guard against the exact fresh
        # nine-owner expected fields through the maintained current_report gate.
        baseline=union.current_report(bundle,extra_output,union_output,lighting_output=lighting_output)
        expected,_=union.union_proof(bundle,extra_output,lighting_output)
        union_changes=[('duplicate idle/source owner',lambda r:r['components'].append(copy.deepcopy(r['components'][1]))),('protocol counted as code',lambda r:r['progress'].__setitem__('verified_source_code_bytes',4544)),('zero shadows counted',lambda r:r['progress'].__setitem__('verified_source_code_bytes',8832))]
        # Each guard changes actual admitted receipt fields, not a display-only label.
        union_changes+=[('wrong original denominator',lambda r:r['progress'].__setitem__('original_unique_program_code_bytes',50048)),('missing real metadata fields',lambda r:r.__setitem__('actual_resolved_nonallocated_metadata_relocations',4)),('false data source bytes',lambda r:r.__setitem__('native_initialized_data_bytes',40)),('invented dynamic1C0 caller',lambda r:r.__setitem__('unconfirmed_dynamic_VU0_entry_1C0',False)),('missing renderer owner',lambda r:r['components'].pop(0)),('missing mandatory fourth owner',lambda r:r['components'].pop(3)),('dynamicREFS counted',lambda r:r['progress'].__setitem__('dynamic_REFS_source_credit',16)),('wrong code/control balance',lambda r:r['components'][-1].__setitem__('VIF_protocol_bytes',32)),('overlapping full original transfer',lambda r:r['components'][-1].__setitem__('EE_chain_begin',0x2c45c0))]
        for label,fn in union_changes:
            altered=copy.deepcopy(baseline);fn(altered)
            try:union.report_fields_current(altered,expected)
            except(ValueError,KeyError,IndexError)as ex:receipt_guards.append({'mutation':label,'rejected':True,'actual_exception':type(ex).__name__,'actual_reason':str(ex)})
            else:raise ValueError('False nine-owner union/source accounting acceptance')
    if receipt(renderer.DEFAULT_OUTPUT/renderer.REPORT_NAME)!=original_renderer:raise ValueError('Legacy renderer proof changed during tests')
    return {'status':'PASS','native_guards':native,'native_guard_count':58,'source_fingerprint_guards':source_guards,'source_guard_count':len(source_guards),'receipt_and_union_guards':receipt_guards,'receipt_guard_count':len(receipt_guards),'exact_component_fixture_copy':copyproof,'old_renderer_proof_unchanged':original_renderer,'progress':union.totals(),'mesh_fifth_owner_guards':fifth,'mesh_alt_sixth_owner_guards':sixth,'volume_seventh_owner_guards':seventh,'particle_eighth_owner_guards':eighth,'silhouette_ninth_owner_guards':ninth}

def change_manifest(data,kind):
    m=json.loads(data)
    if kind=='duplicate':m['components'].append(copy.deepcopy(m['components'][0]))
    elif kind=='overlap':m['components'][1]['EE_chain_begin']=m['components'][0]['EE_chain_begin']
    elif kind=='protocol_as_code':m['components'][0]['code_bytes']=720
    else:m['unconfirmed_dynamic_VU0_entry_1C0']=False
    return json.dumps(m).encode()

def main():
    p=argparse.ArgumentParser();p.add_argument('--bundle-root',type=Path,default=DEFAULT_BUNDLE);p.add_argument('--extra-output',type=Path,default=DEFAULT_OUTPUT);p.add_argument('--union-output',type=Path,default=union.DEFAULT_UNION);p.add_argument('--lighting-output',type=Path,default=lighting.DEFAULT_OUTPUT);p.add_argument('--temp-root',type=Path);p.add_argument('--report',type=Path);a=p.parse_args();r=run_tests(a.bundle_root,a.extra_output,a.union_output,a.temp_root,a.lighting_output)
    if a.report:
        dest=Path(a.report).resolve()
        if dest.exists()or not(dest.is_relative_to(ROOT/'build/vu')or dest.is_relative_to(ROOT/'build/vu_matches/union_stage')):raise ValueError('New scoped test report required')
        dest.write_text(json.dumps(r,indent=2)+'\n',encoding='utf-8')
    print(json.dumps({'status':r['status'],'native_guards':58,'source_guards':r['source_guard_count'],'receipt_guards':r['receipt_guard_count'],'fixture_copy':r['exact_component_fixture_copy']}))
if __name__=='__main__':main()
