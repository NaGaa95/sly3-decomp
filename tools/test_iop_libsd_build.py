"""Native pair/code/data/freshness guards for the separately admitted libsd leaf."""
import copy
import json
import struct
from pathlib import Path
from unittest.mock import patch

import iop_libsd_build as b
from common import Elf32


def main():
    manifest_path=b.DEFAULT_MANIFEST
    manifest=json.loads(manifest_path.read_text())
    output=b.ROOT/'build/iop/module_04/tests/native'
    maintained_paths=[b.ROOT/'tools/iop_build.py',b.ROOT/'tools/test_iop_build.py',b.ROOT/'config/iop_partial.json']
    before={p:b.digest(p.read_bytes())for p in maintained_paths}
    report=b.run(manifest_path,output)
    fresh=b.current_report(manifest_path,output/b.REPORT_NAME)
    assert fresh['progress']['verified_source_functions']==1 and fresh['progress']['verified_source_code_bytes']==16
    assert fresh['progress']['verified_source_initialized_data_bytes']==0
    original=Elf32((b.ROOT/b.MODULE).read_bytes())
    object_path=b.ROOT/report['native_profiles'][1]['object']
    native=Elf32(object_path.read_bytes())
    code,proof=b.inspect_object(native,original)
    target,original_pair,_=b.validate_original(original)
    assert code==target and proof['actual_relocation_count']==2
    negatives=[]

    def rejected(name,callback):
        try:
            callback()
        except (ValueError,OSError)as error:
            negatives.append({'case':name,'status':'REJECTED','reason':str(error)})
        else:
            raise AssertionError('Guard accepted '+name)

    def bad_manifest(name,change):
        candidate=copy.deepcopy(manifest);change(candidate)
        rejected(name,lambda:b.validate_manifest(candidate))

    for name,change in [
        ('unknown_schema',lambda m:m.update(schema='other')),
        ('unclaimed_module00',lambda m:m.update(module='disc/irx/module_00.irx')),
        ('custom989snd_contract_not_admitted',lambda m:m.update(module='disc/irx/module_07.irx')),
        ('customspiop_contract_not_admitted',lambda m:m.update(module='disc/irx/module_08.irx')),
        ('unknown_profile',lambda m:m.update(profiles=['unknown'])),
        ('missing_native_profile',lambda m:m.update(profiles=m['profiles'][:1])),
        ('reversed_native_profiles',lambda m:m['profiles'].reverse()),
        ('duplicate_function_ownership',lambda m:m['functions'].append(copy.deepcopy(m['functions'][0]))),
        ('missing_function',lambda m:m.update(functions=[])),
        ('wrong_function_name',lambda m:m['functions'][0].update(name='other')),
        ('wrong_module_entry',lambda m:m['functions'][0].update(module_offset=b.START+4)),
        ('wrong_complete_boundary',lambda m:m['functions'][0].update(size=12)),
        ('object_gap',lambda m:m['functions'][0].update(object_offset=4)),
        ('wrong_export_ordinal',lambda m:m['functions'][0].update(export_ordinal=28)),
        ('invented_receiver_input',lambda m:m['functions'][0].update(input_registers=['a0: receiver','ra: return address'])),
        ('invented_integer_return',lambda m:m['functions'][0].update(signature='int sceSdGetSpu2IntrHandlerArgument(void)')),
        ('wrong_output_width',lambda m:m['functions'][0].update(output_registers=['v0: u8'])),
        ('wrong_original_code_identity',lambda m:m['functions'][0].update(original_code_sha256='0'*64)),
        ('wrong_native_source_hash',lambda m:m['functions'][0].update(source_sha256='0'*64)),
        ('source_outside_private_IOP_group',lambda m:m['functions'][0].update(source='src/hand/func_001A9478.c')),
        ('source_path_escape',lambda m:m['functions'][0].update(source='../outside.c')),
        ('wrong_actual_global',lambda m:m.update(symbol_bindings={'Spu2IntrData':b.GLOBAL+4})),
        ('extra_global_binding',lambda m:m['symbol_bindings'].update(invented=0)),
        ('wrong_original_module_identity',lambda m:m.update(module_sha256='0'*64)),
        ('stale_original_proof_hash',lambda m:m.update(original_boundary_proof_sha256='0'*64)),
        ('stale_independent_proof_hash',lambda m:m.update(independent_original_review_sha256='0'*64)),
        ('stale_primary_pointer_API_hash',lambda m:m.update(primary_header_sha256='0'*64)),
        ('unreviewed_manifest_field',lambda m:m.update(discard_unknown_data=True)),
    ]:bad_manifest(name,change)

    def changed_elf_word(elf,section_name,offset,word):
        result=copy.deepcopy(elf);section=result.section(section_name);data=bytearray(result.data)
        struct.pack_into('<I',data,section['offset']+offset,word);result.data=bytes(data)
        return result

    def bad_native(name,change):
        candidate=copy.deepcopy(native);change(candidate)
        rejected(name,lambda:b.inspect_object(candidate,original))

    def patched_symbols(elf,change):
        symbols=copy.deepcopy(elf.symbols());change(symbols);elf.symbols=lambda:symbols

    for name,change in [
        ('wrong_ELF_object_type',lambda e:setattr(e,'type',0xFF80)),
        ('unmeasured_object_flags',lambda e:setattr(e,'flags',1)),
        ('wrong_code_alignment',lambda e:e.section('.text').update(alignment=8)),
        ('wrong_code_address',lambda e:e.section('.text').update(addr=4)),
        ('unowned_code_tail',lambda e:e.section('.text').update(size=20)),
        ('truncated_code',lambda e:e.section('.text').update(size=12)),
        ('nonexecutable_code',lambda e:e.section('.text').update(flags=2)),
        ('initialized_reginfo_not_placed',lambda e:e.section('.reginfo').update(flags=2)),
        ('unknown_initialized_data',lambda e:e.section('.data').update(size=4)),
        ('unknown_BSS',lambda e:e.section('.bss').update(size=4)),
        ('empty_data_executable_permissions',lambda e:e.section('.data').update(flags=6)),
        ('empty_data_nonallocated_permissions',lambda e:e.section('.data').update(flags=0)),
        ('empty_data_RELA_type',lambda e:e.section('.data').update(type=4)),
        ('empty_data_NOBITS_type',lambda e:e.section('.data').update(type=8)),
        ('empty_data_nonzero_address',lambda e:e.section('.data').update(addr=4)),
        ('empty_data_unmeasured_alignment',lambda e:e.section('.data').update(alignment=4)),
        ('missing_measured_empty_data',lambda e:e.sections.remove(e.section('.data'))),
        ('duplicate_measured_empty_data',lambda e:e.sections.append(copy.deepcopy(e.section('.data')))),
        ('empty_BSS_executable_permissions',lambda e:e.section('.bss').update(flags=6)),
        ('empty_BSS_nonallocated_permissions',lambda e:e.section('.bss').update(flags=0)),
        ('empty_BSS_RELA_type',lambda e:e.section('.bss').update(type=4)),
        ('empty_BSS_PROGBITS_type',lambda e:e.section('.bss').update(type=1)),
        ('empty_BSS_nonzero_address',lambda e:e.section('.bss').update(addr=4)),
        ('empty_BSS_unmeasured_alignment',lambda e:e.section('.bss').update(alignment=4)),
        ('missing_measured_empty_BSS',lambda e:e.sections.remove(e.section('.bss'))),
        ('duplicate_measured_empty_BSS',lambda e:e.sections.append(copy.deepcopy(e.section('.bss')))),
        ('unknown_allocated_section_even_empty',lambda e:e.sections.append({'name':'.unknown','size':0,'flags':2,'type':1})),
        ('extra_allocated_code',lambda e:e.sections.append({'name':'.text.extra','size':4,'flags':6,'type':1})),
        ('extra_function_even_zero_size',lambda e:patched_symbols(e,lambda ss:ss.append({**next(s for s in ss if s['type']==2),'name':'hidden','size':0}))),
        ('wrong_function_section',lambda e:patched_symbols(e,lambda ss:next(s for s in ss if s['type']==2).update(shndx=e.section('.data')['index']))),
        ('wrong_function_extent',lambda e:patched_symbols(e,lambda ss:next(s for s in ss if s['type']==2).update(size=12))),
        ('wrong_function_object_offset',lambda e:patched_symbols(e,lambda ss:next(s for s in ss if s['type']==2).update(value=4))),
        ('weak_function_not_reviewed',lambda e:patched_symbols(e,lambda ss:next(s for s in ss if s['type']==2).update(binding=2))),
        ('missing_external_symbol',lambda e:patched_symbols(e,lambda ss:ss.pop())),
        ('wrong_external_symbol_name',lambda e:patched_symbols(e,lambda ss:next(s for s in ss if s['name']=='Spu2IntrData').update(name='OtherData'))),
        ('nonzero_symbol_addend',lambda e:patched_symbols(e,lambda ss:next(s for s in ss if s['name']=='Spu2IntrData').update(value=4))),
        ('weak_external_symbol_not_reviewed',lambda e:patched_symbols(e,lambda ss:next(s for s in ss if s['name']=='Spu2IntrData').update(binding=2))),
        ('defined_external_data',lambda e:patched_symbols(e,lambda ss:next(s for s in ss if s['name']=='Spu2IntrData').update(shndx=e.section('.data')['index']))),
        ('extra_external_symbol',lambda e:patched_symbols(e,lambda ss:ss.append({**ss[-1],'name':'OtherData','index':ss[-1]['index']+1}))),
        ('extra_unknown_defined_symbol',lambda e:patched_symbols(e,lambda ss:ss.append({**ss[-1],'name':'HiddenData','type':1,'shndx':e.section('.text')['index']}))),
        ('missing_native_relocation_section',lambda e:e.section('.rel.text').update(size=0)),
        ('missing_native_LO16',lambda e:e.section('.rel.text').update(size=8)),
        ('extra_native_relocation',lambda e:e.section('.rel.text').update(size=24)),
        ('native_RELA_not_admitted',lambda e:e.section('.rel.text').update(type=4)),
        ('wrong_native_relocation_owner',lambda e:e.section('.rel.text').update(info=e.section('.data')['index'])),
        ('wrong_native_symbol_table',lambda e:e.section('.rel.text').update(link=e.section('.strtab')['index'])),
        ('wrong_native_relocation_entry_size',lambda e:e.section('.rel.text').update(entsize=4)),
        ('extra_native_relocation_section',lambda e:e.sections.append({**e.section('.rel.text'),'name':'.rel.extra'})),
    ]:bad_native(name,change)

    reloc=native.section('.rel.text');records=list(struct.iter_unpack('<II',native.section_data(reloc)))
    high_info,low_info=records[0][1],records[1][1]
    def patched_relocations(values):
        e=copy.deepcopy(native);data=bytearray(e.data)
        for i,(off,info)in enumerate(values):struct.pack_into('<II',data,reloc['offset']+i*8,off,info)
        e.data=bytes(data);return e
    for name,values in [
        ('reordered_native_HI_LO',records[::-1]),('wrong_native_HI_type',[(0,(high_info&~255)|6),records[1]]),
        ('wrong_native_LO_type',[records[0],(4,(low_info&~255)|4)]),
        ('duplicate_native_field',[records[0],(0,low_info)]),('unaligned_native_field',[(1,high_info),records[1]]),
        ('native_field_outside_function',[records[0],(16,low_info)]),
        ('native_symbol_index_not_real_external',[(0,5),records[1]]),
        ('native_LO_uses_different_symbol',[records[0],(4,6)]),
    ]:rejected(name,lambda v=values:b.inspect_object(patched_relocations(v),original))
    for name,off,word in [
        ('wrong_LUI_opcode',0,0x34020000),('wrong_LUI_destination',0,0x3C030000),('nonzero_HI_addend',0,0x3C020001),
        ('wrong_load_opcode',4,0x8C430000),('wrong_load_base',4,0x8C620000),('nonzero_LO_addend',4,0x8C420004),
        ('changed_return_register',8,0x00400008),('extra_delay_slot_side_effect',12,0x24040001),
    ]:rejected(name,lambda off=off,w=word:b.inspect_object(changed_elf_word(native,'.text',off,w),original))

    # Actual original IRX addresses and raw relocation pair are checked too.
    orig_records=b.original_records(original)
    orig_rel=original.section('.rel.text')
    raw_orig=list(struct.iter_unpack('<II',original.section_data(orig_rel)))
    hi=next(i for i,(off,info)in enumerate(raw_orig)if off==b.START and (info&255)==5)
    lo=hi+1
    assert raw_orig[lo]==(b.START+4,6)
    def mutated_original_reloc(change):
        e=copy.deepcopy(original);rr=list(raw_orig);change(rr);data=bytearray(e.data)
        for i,(off,info)in enumerate(rr):struct.pack_into('<II',data,orig_rel['offset']+i*8,off,info)
        e.data=bytes(data);return e
    for name,change in [
        ('original_missing_HI',lambda rr:rr.__setitem__(hi,(b.START,2))),
        ('original_missing_LO',lambda rr:rr.__setitem__(lo,(b.START+4,2))),
        ('original_reordered_HI_LO',lambda rr:rr.__setitem__(slice(hi,lo+1),rr[hi:lo+1][::-1])),
        ('original_nonzero_symbol_index',lambda rr:rr.__setitem__(hi,(b.START,0x105))),
        ('original_duplicate_field',lambda rr:rr.__setitem__(lo,(b.START,6))),
        ('original_extra_body_relocation',lambda rr:rr.__setitem__(lo+1,(b.START+8,2))),
        ('original_export_lacks_R32',lambda rr:rr.__setitem__(next(i for i,(off,info)in enumerate(rr)if off==b.EXPORT_FIELD),(b.EXPORT_FIELD,4))),
    ]:rejected(name,lambda c=change:b.validate_original(mutated_original_reloc(c)))
    for name,addr,word in [('wrong_original_global_operand',b.START+4,0x8C425310),('wrong_original_export_pointer',b.EXPORT_FIELD,b.START+4),('wrong_original_export_magic',0,0x41E00000)]:
        rejected(name,lambda a=addr,w=word:b.validate_original(changed_elf_word(original,'.text',a,w)))
    metadata=copy.deepcopy(original);metadata.sections=[s for s in metadata.sections if not s['flags']&2]
    rejected('nonallocated_iopmod_overlap_cannot_supply_code',lambda:b.allocated_read(metadata,0,20,True))
    ambiguous=copy.deepcopy(original);ambiguous.sections.append(copy.deepcopy(ambiguous.section('.text')))
    rejected('ambiguous_allocated_original_domain',lambda:b.allocated_read(ambiguous,b.START,16,True))
    rejected('original_BSS_cannot_supply_initialized_word',lambda:b.allocated_read(original,original.section('.bss')['addr'],4))
    rejected('original_data_cannot_supply_code',lambda:b.allocated_read(original,b.GLOBAL,4,True))

    # A stale successful build must not survive a current failure.
    bad=copy.deepcopy(manifest);bad['module_sha256']='0'*64
    failed_manifest=output.parent/'bad_manifest.json';failed_manifest.write_text(json.dumps(bad))
    failed_output=output.parent/'failed';failed_output.mkdir(exist_ok=True)
    failed_report=failed_output/b.REPORT_NAME;failed_report.write_text(json.dumps(report))
    rejected('failed_current_build_invalidates_old_success',lambda:b.run(failed_manifest,failed_output))
    assert json.loads(failed_report.read_text())['status']=='UNVERIFIED_CURRENT_BUILD'
    assert json.loads(failed_report.read_text())['progress']['verified_source_code_bytes']==0
    rejected('stale_failed_report_never_supplies_counts',lambda:b.current_report(manifest_path,failed_report))

    stale_path=output.parent/'stale_report.json'
    def stale(name,change):
        candidate=copy.deepcopy(report);change(candidate);stale_path.write_text(json.dumps(candidate))
        rejected(name,lambda:b.current_report(manifest_path,stale_path))
    for name,change in [
        ('freshness_wrong_manifest_hash',lambda r:r.update(manifest_sha256='0'*64)),
        ('freshness_missing_manifest_provenance',lambda r:r.pop('manifest')),
        ('freshness_wrong_manifest_provenance',lambda r:r.update(manifest='config/iop_partial.json')),
        ('freshness_missing_original_ownership',lambda r:r.pop('original_source_ownership')),
        ('freshness_wrong_original_ownership',lambda r:r.update(original_source_ownership={'module_offset':0,'file_offset':0,'bytes':20,'section':'.data'})),
        ('freshness_wrong_original_module_offset',lambda r:r['original_source_ownership'].update(module_offset=0)),
        ('freshness_wrong_original_file_offset',lambda r:r['original_source_ownership'].update(file_offset=0)),
        ('freshness_wrong_original_section',lambda r:r['original_source_ownership'].update(section='.data')),
        ('freshness_wrong_original_span_size',lambda r:r['original_source_ownership'].update(bytes=20)),
        ('freshness_extra_original_ownership_field',lambda r:r['original_source_ownership'].update(preservation_counted=True)),
        ('freshness_missing_dependency_hashes',lambda r:r.update(dependency_hashes={})),
        ('freshness_changed_common_dependency',lambda r:r['dependency_hashes'].update({'tools/common.py':'0'*64})),
        ('freshness_wrong_module_hash',lambda r:r.update(module_sha256='0'*64)),
        ('freshness_wrong_source_hash',lambda r:r.update(source_sha256='0'*64)),
        ('freshness_wrong_function_inputs',lambda r:r['functions'][0].update(input_registers=['a0: invented'])),
        ('freshness_wrong_profile_cohort',lambda r:r['native_profiles'].reverse()),
        ('freshness_wrong_native_flags',lambda r:r['native_profiles'][0].update(compiler_flags=['-O0'])),
        ('freshness_wrong_assembler_flags',lambda r:r['native_profiles'][0].update(assembler_flags=['-O2'])),
        ('freshness_changed_native_inputs',lambda r:r['native_profiles'][0].update(native_input_hashes={})),
        ('freshness_changed_assembly_hash',lambda r:r['native_profiles'][0].update(assembly_sha256='0'*64)),
        ('freshness_changed_object_hash',lambda r:r['native_profiles'][0].update(object_sha256='0'*64)),
        ('freshness_changed_section_evidence',lambda r:r['native_profiles'][0]['whole_object_proof'].update(emitted_BSS=[{'size':4}])),
        ('freshness_wrong_relocation_evidence',lambda r:r['native_profiles'][0]['whole_object_proof'].update(actual_relocation_count=0)),
        ('freshness_missing_load_replay',lambda r:r['native_profiles'][0]['whole_object_proof'].update(IRX_load_base_cases=[])),
        ('freshness_partial_hash_changed',lambda r:r.update(partial_module_sha256='0'*64)),
        ('freshness_exaggerated_counts',lambda r:r['progress'].update(verified_source_code_bytes=20)),
    ]:stale(name,change)
    original_reader=Path.read_bytes
    for label,relative in [('source',b.SOURCE),('original_proof',b.PROOF),('independent_proof',b.INDEPENDENT),('primary_header',b.PRIMARY),('original_module',b.MODULE)]:
        def changed_read(path,pinned=(b.ROOT/relative).resolve()):
            result=original_reader(path)
            return bytes([result[0]^1])+result[1:] if path.resolve()==pinned else result
        with patch.object(Path,'read_bytes',changed_read):
            rejected('freshness_actual_'+label+'_changed',lambda:b.current_report(manifest_path,output/b.REPORT_NAME))
    altered=copy.deepcopy(native);rr=altered.section('.rel.text');bad_obj=changed_elf_word(altered,'.text',4,0x8C420004)
    bad_path=output.parent/'tampered_rehashed.o';bad_path.write_bytes(bad_obj.data)
    def use_rehashed(r):
        row=r['native_profiles'][1];row.update(object=bad_path.relative_to(b.ROOT).as_posix(),object_sha256=b.digest(bad_path.read_bytes()))
    stale('freshness_rehashed_object_still_requires_complete_relocation_proof',use_rehashed)
    invalid_partial=output.parent/'tampered_partial.irx';changed=bytearray((b.ROOT/report['partial_module']).read_bytes());changed[-1]^=1;invalid_partial.write_bytes(changed)
    stale('freshness_rehashed_partial_cannot_count_preservation_as_source',lambda r:r.update(partial_module=invalid_partial.relative_to(b.ROOT).as_posix(),partial_module_sha256=b.digest(invalid_partial.read_bytes())))

    # Pointer bit patterns and all load-base carry states keep every non-V0 GPR.
    values=sorted({0,0xFFFFFFFF,0x5314,0x475480,0xBF808268,0x12345678}|{1<<i for i in range(32)}|{0xFFFFFFFF^(1<<i)for i in range(32)})
    state_count=0
    for row in report['native_profiles']:
        elf=Elf32((b.ROOT/row['object']).read_bytes());raw=elf.section_data(elf.section('.text'))
        records=[{'offset':0,'type':5,'symbol':'Spu2IntrData'},{'offset':4,'type':6,'symbol':'Spu2IntrData'}]
        for base in b.BASES:
            words=struct.unpack('<4I',b.relocate_pair(raw,records,b.GLOBAL+base))
            for value in values:
                regs=[(i*0x13579BDF)&0xFFFFFFFF for i in range(32)];regs[0]=0;before_regs=list(regs)
                regs[2]=(words[0]&65535)<<16
                address=(regs[2]+((words[1]&0x7FFF)-(words[1]&0x8000)))&0xFFFFFFFF
                assert address==b.GLOBAL+base
                regs[2]=value
                assert words[2:]==(0x03E00008,0) and regs[2]==value
                assert all(regs[i]==before_regs[i]for i in range(32)if i!=2)
                state_count+=1
    # The existing module00 checker still refuses the libsd object's relocations.
    core_manifest=json.loads((b.ROOT/'config/iop_partial.json').read_text())
    published=b.iop_build.current_report()
    assert published['progress']['verified_source_functions']==12 and published['progress']['verified_source_code_bytes']==236
    core=[f for f in core_manifest['functions']if f['source']=='iop/src/sio2man/sio2_ctrl.c']
    original00=Elf32((b.ROOT/core_manifest['module']).read_bytes())
    core_target=b.iop_build.expected_object_text(original00,core)
    core_object=b.ROOT/published['native_groups'][0]['native_profiles'][0]['object']
    native00=Elf32(core_object.read_bytes());native00.sections.append({'name':'.rel.unproved','type':9,'size':8})
    rejected('published_module00_zero_relocation_guard_is_unchanged',lambda:b.iop_build.inspect_object(native00,core,core_target))
    assert {p:b.digest(p.read_bytes())for p in maintained_paths}==before
    summary={'status':'PASS_LIBSD_NATIVE_AND_FAIL_CLOSED_GUARDS','negative_guard_count':len(negatives),'negative_guards':negatives,
        'native_profiles':2,'complete_function_bytes':16,'actual_relocations':2,'initialized_source_data_bytes':0,
        'pointer_state_cases':state_count,'load_bases':b.BASES,'published_core_IOP_preserved':'12 functions/236bytes;54-guard test files and config unmodified',
        'shared_production_mutations':False,'native_report':(output/b.REPORT_NAME).relative_to(b.ROOT).as_posix()}
    (b.ROOT/'build/iop/module_04/tests/libsd_guard_results.json').write_text(json.dumps(summary,indent=2)+'\n')
    print(f'PASS separate libsd: {len(negatives)} rejection guards; {state_count} pointer/load-base/GPR states; two whole native16-byte objects and2actual relocations; published12/236 unchanged.')


if __name__=='__main__':main()
