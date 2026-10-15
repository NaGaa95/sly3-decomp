"""Maintained disjoint-range IOP registry freshness and ownership guards."""
import copy
import importlib.util
import json
import sys
from pathlib import Path
from unittest.mock import patch

ROOT=next(p for p in Path(__file__).resolve().parents if(p/'config/target.json').is_file())
sys.path.insert(0,str(ROOT/'tools'))


def load(name,file):
    spec=importlib.util.spec_from_file_location(name,file);module=importlib.util.module_from_spec(spec)
    sys.modules[name]=module;spec.loader.exec_module(module);return module


def main(result_path=None):
    stage=Path(__file__).resolve().parent
    import iop_nosplit_build as narrow
    import iop_sources as registry
    protected=[ROOT/p for p in ['tools/iop_build.py','tools/test_iop_build.py','tools/iop_libsd_build.py','tools/test_iop_libsd_build.py',
        'tools/iop_sources.py','tools/test_iop_sources.py','config/iop_partial.json','config/iop_libsd_partial.json']]
    before={p.relative_to(ROOT).as_posix():narrow.digest(p.read_bytes())for p in protected}
    core=registry.components()
    assert len(core)==9
    proposed=core[-1];core=core[:-1]
    definitions=core+[proposed];negative=[]
    def rejected(label,call):
        try:call()
        except (ValueError,OSError)as error:negative.append({'case':label,'status':'REJECTED','reason':str(error)})
        else:raise AssertionError('Guard accepted '+label)
    with patch.object(registry,'components',return_value=definitions):
        proofs=registry.current_components(require_all=True)
        totals=registry.summarize(proofs);modules=registry.current_modules(proofs)
        assert totals['verified_source_functions']==25 and totals['verified_source_code_bytes']==676 and totals['verified_source_initialized_data_bytes']==936
        assert totals['unique_original_module_count']==4 and len(modules)==4
        assert [r['progress']['verified_source_functions']for r in modules]==[16,4,2,3]
        assert [r['progress']['verified_source_code_bytes']for r in modules]==[300,160,40,176]
        assert [r['progress']['verified_source_initialized_data_bytes']for r in modules]==[0,256,680,0]
        module02=next(m for m in modules if m['module']=='disc/irx/module_02.irx')
        assert len(module02['source_claims'])==4 and len(module02['data_objects'])==1 and module02['data_objects'][0]['module_offset']==0x11da8 and module02['data_objects'][0]['size']==256
        module07=next(m for m in modules if m['module']=='disc/irx/module_07.irx')
        assert len(module07['source_claims'])==3 and not module07['data_objects'] and [(c['module_offset'],c['size'])for c in module07['source_claims']]==[(0xe490,76),(0x18c1c,32),(0x18c3c,68)]
        assert totals['original_file_size']==6641+95909+28661+178984
        assert totals['preserved_original_file_bytes_excluded_from_source']==6641+95909+28661+178984-676-936
        combined=registry.combine_components(proofs,ROOT/'build/iop/combined_private_review')
        assert len(combined['modules'])==4 and all(r['full_file_bytes_equal']for r in combined['modules'])
        for c in definitions:
            with patch.object(registry,'components',return_value=definitions+[c]):
                rejected('duplicate_'+c['library']+'_component_range_ownership',lambda:registry.current_components(require_all=True))
        for verifier in('iop_build','iop_libsd_build','iop_nosplit_build','iop_mcman_build','iop_mcman_device_build','iop_mcman_ecc_build','iop_snd989_build','iop_snd989_chain_build','iop_snd989_volume_build'):
            with patch(verifier+'.current_report',side_effect=ValueError('Stale entire component')):
                rejected(verifier+'_stale_current_proof_cannot_count_or_be_skipped',lambda:registry.current_components())
        missing={**proposed,'output':ROOT/'build/iop/missing_snd989_chain_review'}
        with patch.object(registry,'components',return_value=core+[missing]):
            rejected('required_missing_new_component',lambda:registry.current_components(require_all=True))
            rejected('default_missing_new_component_never_falls_back_to22',lambda:registry.current_components())
        original_is_file=Path.is_file
        before_combined={p.name:narrow.digest(p.read_bytes())for p in (ROOT/'build/iop/combined_private_review').iterdir()if p.is_file()}
        for c in definitions:
            for kind,path in [('manifest',Path(c['manifest'])),('report',Path(c['output'])/'partial_iop_report.json')]:
                absent=path.resolve()
                def missing_file(p,pinned=absent):return False if p.resolve()==pinned else original_is_file(p)
                with patch.object(Path,'is_file',missing_file):
                    for require_all in(False,True):
                        rejected(c['library']+'_missing_'+kind+'_required_'+str(require_all),lambda flag=require_all:registry.current_components(require_all=flag))
                    rejected(c['library']+'_missing_'+kind+'_cannot_write_combined_artifact',lambda:registry.combine_components(output=ROOT/'build/iop/combined_private_review'))
        assert before_combined=={p.name:narrow.digest(p.read_bytes())for p in (ROOT/'build/iop/combined_private_review').iterdir()if p.is_file()}
        # The wrapped getter remains independently mandatory; extending libsd
        # must retain every original manifest/report guard, including writes.
        base_getter=next(c for c in registry.base_components()if c['verifier']=='iop_libsd_build')
        for kind,path in [('manifest',Path(base_getter['manifest'])),('report',Path(base_getter['output'])/'partial_iop_report.json')]:
            absent=path.resolve()
            def missing_base_getter(p,pinned=absent):return False if p.resolve()==pinned else original_is_file(p)
            with patch.object(Path,'is_file',missing_base_getter):
                for require_all in(False,True):
                    rejected('original_getter_missing_'+kind+'_required_'+str(require_all),lambda flag=require_all:registry.current_components(require_all=flag))
                rejected('original_getter_missing_'+kind+'_cannot_write_aggregate',lambda:registry.run(ROOT/'build/iop/combined_private_review'))
        with patch('iop_mcman_build.current_report',side_effect=ValueError('Stale new whole module02 code')):
            rejected('module02_stale_cannot_fall_back_to18',registry.current_components)
        with patch('iop_mcman_device_build.current_report',side_effect=ValueError('Stale whole device128 source')):
            rejected('module02_device_stale_cannot_fall_back_to20',registry.current_components)
        with patch('iop_mcman_ecc_build.current_report',side_effect=ValueError('Stale whole ECC initialized section')):
            rejected('ECC_data_stale_cannot_fall_back_to680',registry.current_components)
        with patch('iop_snd989_build.current_report',side_effect=ValueError('Stale whole source initializer76')):
            rejected('snd989_source_stale_cannot_fall_back_to500',registry.current_components)
        with patch('iop_snd989_chain_build.current_report',side_effect=ValueError('Stale complete source chain32')):
            rejected('chain32_stale_cannot_fall_back_to576',registry.current_components)
        with patch('iop_libsd_data_build.current_report',side_effect=ValueError('Stale whole initialized section')):
            rejected('data_extension_stale_cannot_fall_back_to_zero_data',registry.current_components)
        assert before_combined=={p.name:narrow.digest(p.read_bytes())for p in (ROOT/'build/iop/combined_private_review').iterdir()if p.is_file()}
        rejected('incomplete_admitted_receipts_cannot_summarize',lambda:registry.summarize(proofs[:2]))
        rejected('incomplete_admitted_receipts_cannot_return_modules',lambda:registry.current_modules(proofs[:2]))
        rejected('incomplete_admitted_receipts_cannot_write_union',lambda:registry.combine_components(proofs[:2],ROOT/'build/iop/combined_private_review'))
        unknown={**proposed,'verifier':'unreviewed_loader'}
        with patch.object(registry,'components',return_value=core+[unknown]):
            rejected('unreviewed_verifier_is_not_source_owner',lambda:registry.current_components(require_all=True))
        unknown={**proposed,'manifest':ROOT.parent/'outside_manifest.json'}
        with patch.object(registry,'components',return_value=core+[unknown]):
            rejected('manifest_escapes_workspace',lambda:registry.current_components(require_all=True))
        tampered=copy.deepcopy(proofs);tampered[0]['report']['progress']['verified_source_code_bytes']+=4
        rejected('forged_component_receipt_cannot_inflate_source',lambda:registry.summarize(tampered))
        tampered=copy.deepcopy(proofs);tampered[2]['report']['functions'][0]['module_offset']=0x3EF8
        rejected('forged_getter_overlap_rejected_before_count',lambda:registry.summarize(tampered))
        tampered=copy.deepcopy(proofs);tampered[0]['report']['functions'][0]['size']+=4
        rejected('forged_function_tail_rejected_before_count',lambda:registry.summarize(tampered))
        tampered=copy.deepcopy(proofs);tampered[2]['report']['progress']['verified_source_initialized_data_bytes']=4
        rejected('unverified_initialized_data_not_counted',lambda:registry.summarize(tampered))
        tampered=copy.deepcopy(proofs);tampered[2]['report']['functions'][0]['module_sha256']='0'*64
        rejected('contradictory_original_identity_rejected',lambda:registry.summarize(tampered))
        for label,edit in [('device source owner omission',lambda r:r['report']['functions'].pop()),('device source owner duplication',lambda r:r['report']['functions'].append(copy.deepcopy(r['report']['functions'][0]))),('device source moved onto prior32',lambda r:r['report']['functions'][0].update(module_offset=0x2f8)),('device foreign original identity',lambda r:r['report']['functions'][0].update(module_sha256='0'*64))]:
            forged=copy.deepcopy(proofs);owner=next(r for r in forged if r['verifier']=='iop_mcman_device_build');edit(owner)
            rejected(label,lambda q=forged:registry.summarize(q))
        for label,edit in [('snd989 source omitted',lambda r:r['report']['functions'].pop()),('snd989 source duplicate',lambda r:r['report']['functions'].append(copy.deepcopy(r['report']['functions'][0]))),('snd989 source shortened',lambda r:r['report']['functions'][0].update(size=72)),('snd989 source foreign identity',lambda r:r['report'].update(module_sha256='0'*64)),('snd989 source false data',lambda r:r['report']['progress'].update(verified_source_initialized_data_bytes=4))]:
            forged=copy.deepcopy(proofs);owner=next(r for r in forged if r['verifier']=='iop_snd989_build');edit(owner)
            rejected(label,lambda q=forged:registry.summarize(q))
        for label,edit in [('chain source omitted',lambda r:r['report']['functions'].pop()),('chain source duplicate',lambda r:r['report']['functions'].append(copy.deepcopy(r['report']['functions'][0]))),('chain source shortened',lambda r:r['report']['functions'][0].update(size=28)),('chain source moved onto initializer76',lambda r:r['report']['functions'][0].update(module_offset=0xe490)),('chain source false data',lambda r:r['report']['progress'].update(verified_source_initialized_data_bytes=4))]:
            forged=copy.deepcopy(proofs);owner=next(r for r in forged if r['verifier']=='iop_snd989_chain_build');edit(owner)
            rejected(label,lambda q=forged:registry.summarize(q))
        for label,edit in [('volume source omitted',lambda r:r['report']['functions'].pop()),('volume source duplicate',lambda r:r['report']['functions'].append(copy.deepcopy(r['report']['functions'][0]))),('volume source truncated',lambda r:r['report']['functions'][0].update(size=64)),('volume source moved onto chain',lambda r:r['report']['functions'][0].update(module_offset=0x18c1c)),('volume source claims metadata as data',lambda r:r['report']['progress'].update(verified_source_initialized_data_bytes=24))]:
            forged=copy.deepcopy(proofs);owner=next(r for r in forged if r['verifier']=='iop_snd989_volume_build');edit(owner)
            rejected(label,lambda q=forged:registry.summarize(q))
        with patch('iop_snd989_volume_build.current_report',side_effect=ValueError('Stale entire volume68 source')):
            rejected('volume stale cannot fallback to24',registry.current_components)
        rejected('combined_output_escapes_IOP_tree',lambda:registry.combine_components(proofs,ROOT/'src/combined'))
        # With native component proofs held fixed, independently exercise the
        # cross-owner range algorithm against a hypothetical separately reviewed
        # overlapping cohort. Do not alter the real narrow verifier's contract.
        fabricated=copy.deepcopy(proofs)
        real_getter=fabricated[1]['report']['functions'][0]
        f=fabricated[2]['report']['functions'][0]
        f.update(name='distinct_name_same_existing_entry',module_offset=real_getter['module_offset'],size=real_getter['size'],original_code_sha256=real_getter['original_code_sha256'])
        fabricated[2]['report']['progress']['verified_source_code_bytes']=80
        actual_reread=registry.reread
        def selected_reread(item):
            if item['verifier']=='iop_nosplit_build':return narrow,item['report']
            return actual_reread(item)
        with patch.object(registry,'reread',side_effect=selected_reread):
            rejected('independently_claimed_nonidentical_names_still_overlap',lambda:registry.summarize(fabricated))
        # Original content cannot be silently accepted with an old hash/receipt.
        reader=Path.read_bytes;original_path=(ROOT/'disc/irx/module_00.irx').resolve()
        def changed_read(path):
            raw=reader(path)
            return raw[:-1]+bytes([raw[-1]^1])if path.resolve()==original_path else raw
        with patch.object(Path,'read_bytes',changed_read):
            rejected('unknown_preservation_mutation_cannot_pass_aggregate',lambda:registry.current_components(require_all=True))
    assert before=={p.relative_to(ROOT).as_posix():narrow.digest(p.read_bytes())for p in protected}
    result={'status':'PASS_PRIVATE_FINAL_SOURCE_AND_DISJOINT_IOP_REGISTRY_PROPOSAL','negative_guard_count':len(negative),'negative_guards':negative,
        'proposed_progress':totals,'module_source_counts':[{'module':r['module'],'progress':r['progress']}for r in modules],
        'combined_report':'build/iop/combined_private_review/combined_iop_report.json','protected_existing_files':before,
        'verified_IOP_progress':'25/676/936 across four original identities','registry_current':True,
        'registry_sha256':narrow.digest(Path(registry.__file__).read_bytes()),'test_sha256':narrow.digest(Path(__file__).read_bytes())}
    result_path=Path(result_path)if result_path is not None else ROOT/'build/iop/combined/registry_guard_results.json'
    if not result_path.resolve().is_relative_to(ROOT/'build/iop')and not result_path.resolve().is_relative_to(ROOT/'build/iop_research/publication'):
        raise ValueError('Registry test output escapes maintained/private IOP tree')
    result_path.parent.mkdir(parents=True,exist_ok=True)
    result_path.write_text(json.dumps(result,indent=2)+'\n')
    print(f'PASS IOP registry:25/676/936 across four unique original modules;{len(negative)} rejection guards;existing component verifiers unchanged.')


if __name__=='__main__':main()
