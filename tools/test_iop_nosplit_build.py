"""PRIVATE native no-split guard suite; published files are read-only."""
import copy
import json
import struct
from pathlib import Path
from unittest.mock import patch

import iop_nosplit_build as b
from common import Elf32


def word_changed(elf,section,offset,word):
    e=copy.deepcopy(elf);s=e.section(section);raw=bytearray(e.data)
    struct.pack_into('<I',raw,s['offset']+offset,word);e.data=bytes(raw)
    return e


def symbols_changed(elf,change):
    symbols=copy.deepcopy(elf.symbols());change(symbols);elf.symbols=lambda:symbols


def records_changed(elf,section,change):
    e=copy.deepcopy(elf);s=e.section(section)
    rr=list(struct.iter_unpack('<II',e.section_data(s)));change(rr);raw=bytearray(e.data)
    for i,(off,info)in enumerate(rr):struct.pack_into('<II',raw,s['offset']+i*8,off,info)
    e.data=bytes(raw);return e


def execute(words,registers,memory):
    """Small independent MIPS1 scalar interpreter, including JR's delay NOP."""
    regs=list(registers);mem=dict(memory);writes=[];returned=None
    for index,w in enumerate(words):
        op=w>>26;rs=(w>>21)&31;rt=(w>>16)&31;rd=(w>>11)&31;fun=w&63
        immediate=(w&0x7FFF)-(w&0x8000)
        if w==0:pass
        elif op==15:regs[rt]=(w&65535)<<16
        elif op==0 and fun==0:regs[rd]=(regs[rt]<<((w>>6)&31))&0xFFFFFFFF
        elif op==0 and fun==33:regs[rd]=(regs[rs]+regs[rt])&0xFFFFFFFF
        elif op==35:regs[rt]=mem[(regs[rs]+immediate)&0xFFFFFFFF]
        elif op==43:
            address=(regs[rs]+immediate)&0xFFFFFFFF;mem[address]=regs[rt];writes.append(address)
        elif op==0 and fun==8:
            assert index==len(words)-2 and words[-1]==0
            returned=regs[rs]
        else:raise AssertionError('Unexpected instruction in isolated scalar interpreter')
        regs[0]=0
    assert returned is not None
    return regs,mem,writes,returned


def main(output=None,result_path=None):
    manifest_path=b.DEFAULT_MANIFEST;manifest=json.loads(manifest_path.read_text())
    protected=[p for p in (b.ROOT/'iop/src').rglob('*')if p.is_file()]
    protected += [b.ROOT/p for p in ['tools/iop_build.py','tools/test_iop_build.py','tools/iop_libsd_build.py',
        'tools/test_iop_libsd_build.py','tools/iop_sources.py','tools/test_iop_sources.py','config/iop_partial.json','config/iop_libsd_partial.json']]
    protected=[p for p in protected if p.exists()]
    before={p.relative_to(b.ROOT).as_posix():b.digest(p.read_bytes())for p in protected}
    output=Path(output)if output is not None else b.ROOT_OUTPUT/'tests/native'
    result_path=Path(result_path)if result_path is not None else b.ROOT_OUTPUT/'nosplit_guard_results.json'
    if not result_path.resolve().is_relative_to(b.ROOT_OUTPUT.resolve())and not result_path.resolve().is_relative_to((b.ROOT/'build/iop_research').resolve()):
        raise ValueError('Private guard report output escapes research ownership')
    report=b.run(manifest_path,output)
    fresh=b.current_report(manifest_path,output/b.REPORT)
    assert fresh['progress']==b.expected_progress(manifest['functions'])
    assert len(fresh['module_artifacts_are_identity_observations_not_owners'])==2
    functions=manifest['functions'];modules=b.load_modules(functions)
    native=[Elf32((b.ROOT/g['profiles'][1]['object']).read_bytes())for g in report['native_objects']]
    rejected_cases=[]

    def rejected(name,callback):
        try:callback()
        except (ValueError,OSError)as error:
            rejected_cases.append({'case':name,'status':'REJECTED','reason':str(error)})
        else:raise AssertionError('Guard accepted '+name)

    def bad_manifest(name,change):
        m=copy.deepcopy(manifest);change(m);rejected(name,lambda:b.validate_manifest(m))

    for name,change in [
        ('unknown_schema',lambda m:m.update(schema='other')),
        ('unknown_profile',lambda m:m.update(profiles=['unknown'])),
        ('unreviewed_base_profile',lambda m:m.update(profiles=['legacy-scalar-114','legacy-scalar-136'])),
        ('missing_profile',lambda m:m['profiles'].pop()),
        ('reversed_profiles',lambda m:m['profiles'].reverse()),
        ('duplicate_profile',lambda m:m['profiles'].append(m['profiles'][0])),
        ('stale_proposal_hash',lambda m:m.update(proposal_sha256='0'*64)),
        ('wrong_proposal_path',lambda m:m.update(proposal='other.json')),
        ('wrong_independent_review_path',lambda m:m.update(independent_original_review='other.json')),
        ('wrong_independent_review_hash',lambda m:m.update(independent_original_review_sha256='0'*64)),
        ('missing_function',lambda m:m['functions'].pop()),
        ('duplicate_function',lambda m:m['functions'].append(copy.deepcopy(m['functions'][0]))),
        ('reordered_functions',lambda m:m['functions'].reverse()),
        ('wrong_module',lambda m:m['functions'][0].update(module='disc/irx/module_07.irx')),
        ('wrong_original_module_hash',lambda m:m['functions'][0].update(module_sha256='0'*64)),
        ('wrong_entry',lambda m:m['functions'][0].update(module_offset=0x3E9C)),
        ('truncated_boundary',lambda m:m['functions'][0].update(size=20)),
        ('unowned_tail',lambda m:m['functions'][0].update(size=28)),
        ('object_gap',lambda m:m['functions'][0].update(object_offset=4)),
        ('wrong_export_ordinal',lambda m:m['functions'][0].update(export_ordinal=29)),
        ('source_path_escape',lambda m:m['functions'][0].update(source='../outside.c')),
        ('EE_source_outside_group',lambda m:m['functions'][0].update(source='src/P2/input.cpp')),
        ('stale_source_hash',lambda m:m['functions'][0].update(source_sha256='0'*64)),
        ('wrong_original_code_hash',lambda m:m['functions'][0].update(original_code_sha256='0'*64)),
        ('invented_receiver',lambda m:m['functions'][0].update(GP_inputs=['A0 receiver'])),
        ('incorrect_index_width',lambda m:m['functions'][0].update(GP_inputs=['A0 u8 channel'])),
        ('incorrect_integer_return',lambda m:m['functions'][0].update(GP_outputs=['V0 int'])),
        ('invented_fpr_input',lambda m:m['functions'][0].update(FPR_inputs=['F12'])),
        ('invented_stack',lambda m:m['functions'][0].update(stack_bytes=8)),
        ('wrong_record_base_plus4',lambda m:m['functions'][0].update(symbol_bindings={'TransferRecords':0x532C})),
        ('extra_global',lambda m:m['functions'][0]['symbol_bindings'].update(Other=0)),
        ('wrong_callback_storage',lambda m:m['functions'][1].update(symbol_bindings={'Data':0xFE0})),
        ('unreviewed_manifest_field',lambda m:m.update(ignore_unknown_data=True)),
        ('missing_public_reservation',lambda m:m.update(public_reservation_manifests=[])),
    ]:bad_manifest(name,change)

    # Generic range checks operate on real module identities, not object offsets.
    def overlap_case(name,change):
        claims=copy.deepcopy(functions);reserved=copy.deepcopy(report['published_reservations']);change(claims,reserved)
        rejected(name,lambda:b.validate_nonoverlap(claims,reserved))
    for name,change in [
        ('duplicate_claim_name',lambda c,r:c.append(copy.deepcopy(c[0]))),
        ('negative_source_offset',lambda c,r:c[0].update(module_offset=-4)),
        ('unaligned_source_offset',lambda c,r:c[0].update(module_offset=0x3E99)),
        ('zero_source_size',lambda c,r:c[0].update(size=0)),
        ('unaligned_source_size',lambda c,r:c[0].update(size=23)),
        ('source_range_overflows_module_domain',lambda c,r:c[0].update(module_offset=0xFFFFFFFC)),
        ('overlapping_new_ranges',lambda c,r:c[2].update(module_offset=c[1]['module_offset']+4)),
        ('contradictory_module_identity',lambda c,r:c[2].update(module_sha256='0'*64)),
        ('overlap_existing_public_getter',lambda c,r:c[0].update(module_offset=0x3EF8)),
        ('duplicate_public_source_reservation',lambda c,r:r.append(copy.deepcopy(r[0]))),
    ]:overlap_case(name,change)
    assert b.validate_nonoverlap(functions,report['published_reservations'])is None

    for fi in (0,1):
        f=functions[fi];n=native[fi];original=modules[f['module']][1];s=b.shape(f);prefix=f['name']+': '
        def bad_native(name,change):
            e=copy.deepcopy(n);change(e);rejected(prefix+name,lambda:b.inspect_object(e,f,original))
        def external(ss):return next(sym for sym in ss if sym['name']==s['symbol'])
        def function(ss):return next(sym for sym in ss if sym['type']==2)
        for name,change in [
            ('wrong_ELF_type',lambda e:setattr(e,'type',0xFF80)),
            ('wrong_native_flags',lambda e:setattr(e,'flags',1)),
            ('nonzero_object_entry',lambda e:setattr(e,'entry',4)),
            ('unmeasured_program_header',lambda e:setattr(e,'phnum',1)),
            ('wrong_text_type',lambda e:e.section('.text').update(type=8)),
            ('nonexecuting_text',lambda e:e.section('.text').update(flags=2)),
            ('wrong_text_addr',lambda e:e.section('.text').update(addr=4)),
            ('wrong_text_align',lambda e:e.section('.text').update(alignment=8)),
            ('truncated_text',lambda e:e.section('.text').update(size=f['size']-4)),
            ('unknown_text_tail',lambda e:e.section('.text').update(size=f['size']+4)),
            ('missing_text',lambda e:e.sections.remove(e.section('.text'))),
            ('duplicate_text',lambda e:e.sections.append(copy.deepcopy(e.section('.text')))),
            ('unknown_ALLOC_even_empty',lambda e:e.sections.append({'name':'.other','flags':2,'size':0,'type':1})),
            ('initialized_reginfo',lambda e:e.section('.reginfo').update(flags=2)),
            ('extra_ALLOC_code',lambda e:e.sections.append({'name':'.text.more','flags':6,'size':4,'type':1})),
            ('extra_zero_sized_function',lambda e:symbols_changed(e,lambda ss:ss.append({**function(ss),'name':'hidden','size':0}))),
            ('wrong_function_section',lambda e:symbols_changed(e,lambda ss:function(ss).update(shndx=e.section('.data')['index']))),
            ('wrong_function_size',lambda e:symbols_changed(e,lambda ss:function(ss).update(size=f['size']-4))),
            ('wrong_function_offset',lambda e:symbols_changed(e,lambda ss:function(ss).update(value=4))),
            ('weak_function',lambda e:symbols_changed(e,lambda ss:function(ss).update(binding=2))),
            ('hidden_function',lambda e:symbols_changed(e,lambda ss:function(ss).update(visibility=2))),
            ('wrong_external_name',lambda e:symbols_changed(e,lambda ss:external(ss).update(name='Other'))),
            ('wrong_external_value',lambda e:symbols_changed(e,lambda ss:external(ss).update(value=4))),
            ('wrong_external_type',lambda e:symbols_changed(e,lambda ss:external(ss).update(type=1))),
            ('weak_external',lambda e:symbols_changed(e,lambda ss:external(ss).update(binding=2))),
            ('defined_external',lambda e:symbols_changed(e,lambda ss:external(ss).update(shndx=e.section('.data')['index']))),
            ('extra_external',lambda e:symbols_changed(e,lambda ss:ss.append({**external(ss),'name':'Other','index':100}))),
            ('extra_defined_data',lambda e:symbols_changed(e,lambda ss:ss.append({**function(ss),'name':'Other','type':1}))),
            ('compiler_marker_global_binding',lambda e:symbols_changed(e,lambda ss:next(sym for sym in ss if sym['name']=='gcc2_compiled.').update(binding=1))),
            ('compiler_marker_data_definition',lambda e:symbols_changed(e,lambda ss:next(sym for sym in ss if sym['name']=='__gnu_compiled_c').update(shndx=e.section('.data')['index']))),
            ('compiler_marker_nonzero_span',lambda e:symbols_changed(e,lambda ss:next(sym for sym in ss if sym['name']=='gcc2_compiled.').update(value=4,size=4))),
            ('missing_relocations',lambda e:e.section('.rel.text').update(size=0)),
            ('missing_LO',lambda e:e.section('.rel.text').update(size=8)),
            ('extra_relocation',lambda e:e.section('.rel.text').update(size=24)),
            ('RELA_not_admitted',lambda e:e.section('.rel.text').update(type=4)),
            ('wrong_relocation_owner',lambda e:e.section('.rel.text').update(info=e.section('.data')['index'])),
            ('wrong_relocation_symbols',lambda e:e.section('.rel.text').update(link=e.section('.strtab')['index'])),
            ('wrong_relocation_entsize',lambda e:e.section('.rel.text').update(entsize=4)),
            ('wrong_relocation_flags',lambda e:e.section('.rel.text').update(flags=4)),
            ('wrong_relocation_address',lambda e:e.section('.rel.text').update(addr=4)),
            ('wrong_relocation_alignment',lambda e:e.section('.rel.text').update(alignment=8)),
            ('extra_relocation_section',lambda e:e.sections.append({**e.section('.rel.text'),'name':'.rel.other'})),
        ]:bad_native(name,change)
        for section,kind in(('.data',1),('.bss',8)):
            for label,change in [
                ('nonempty',lambda e,sec=section:e.section(sec).update(size=4)),
                ('execute_permissions',lambda e,sec=section:e.section(sec).update(flags=6)),
                ('nonallocated',lambda e,sec=section:e.section(sec).update(flags=0)),
                ('RELA_type',lambda e,sec=section:e.section(sec).update(type=4)),
                ('wrong_storage_type',lambda e,sec=section,k=kind:e.section(sec).update(type=8 if k==1 else 1)),
                ('nonzero_address',lambda e,sec=section:e.section(sec).update(addr=4)),
                ('wrong_alignment',lambda e,sec=section:e.section(sec).update(alignment=4)),
                ('missing',lambda e,sec=section:e.sections.remove(e.section(sec))),
                ('duplicate',lambda e,sec=section:e.sections.append(copy.deepcopy(e.section(sec)))),
            ]:bad_native(section+': '+label,change)
        rr=list(struct.iter_unpack('<II',n.section_data(n.section('.rel.text'))));hi,lo=rr
        for name,change in [
            ('reordered_HI_LO',lambda r:r.reverse()),
            ('HI_wrong_type',lambda r:r.__setitem__(0,(hi[0],(hi[1]&~255)|6))),
            ('LO_wrong_type',lambda r:r.__setitem__(1,(lo[0],(lo[1]&~255)|4))),
            ('duplicate_field',lambda r:r.__setitem__(1,(hi[0],lo[1]))),
            ('unaligned_field',lambda r:r.__setitem__(0,(hi[0]+1,hi[1]))),
            ('out_of_function_field',lambda r:r.__setitem__(1,(f['size'],lo[1]))),
            ('HI_wrong_symbol',lambda r:r.__setitem__(0,(hi[0],5))),
            ('LO_wrong_symbol',lambda r:r.__setitem__(1,(lo[0],6))),
        ]:rejected(prefix+name,lambda change=change:b.inspect_object(records_changed(n,'.rel.text',change),f,original))
        for name,offset,word in [
            ('wrong_LUI_opcode',s['high'],s['hi_word']^0x08000000),
            ('wrong_LUI_register',s['high'],s['hi_word']^0x10000),
            ('nonzero_HI_addend',s['high'],s['hi_word']+1),
            ('wrong_LO_opcode',s['low'],s['lo_word']^0x04000000),
            ('wrong_LO_base',s['low'],s['lo_word']^0x200000),
            ('wrong_LO_value_register',s['low'],s['lo_word']^0x10000),
            ('wrong_LO_addend',s['low'],s['lo_word']^4),
            ('negative_unproved_LO_addend',s['low'],(s['lo_word']&~65535)|0xFFFF),
            ('wrong_return_register',f['size']-8,0x00400008),
            ('delay_slot_side_effect',f['size']-4,0x24040001),
        ]:rejected(prefix+name,lambda off=offset,w=word:b.inspect_object(word_changed(n,'.text',off,w),f,original))
        if fi==0:
            for name,off,w in [('index_scale4_not8',0,0x00042080),('changed_ADDU_register',8,0x00441021^0x10000)]:
                rejected(prefix+name,lambda off=off,w=w:b.inspect_object(word_changed(n,'.text',off,w),f,original))

        # Each original full body, export R32, actual symbol0 pair and storage is audited.
        ori_rr=list(struct.iter_unpack('<II',original.section_data(original.section('.rel.text'))))
        hi_index=next(i for i,r in enumerate(ori_rr)if r==(f['module_offset']+s['high'],5))
        lo_index=next(i for i,r in enumerate(ori_rr)if r==(f['module_offset']+s['low'],6))
        export_index=next(i for i,r in enumerate(ori_rr)if r==(s['export_field'],2))
        for name,change in [
            ('original_HI_wrong_type',lambda r:r.__setitem__(hi_index,(r[hi_index][0],2))),
            ('original_LO_wrong_type',lambda r:r.__setitem__(lo_index,(r[lo_index][0],2))),
            ('original_nonzero_symbol',lambda r:r.__setitem__(hi_index,(r[hi_index][0],0x105))),
            ('original_reordered_pair',lambda r:r.__setitem__(slice(hi_index,lo_index+1),r[hi_index:lo_index+1][::-1])),
            ('original_duplicate_field',lambda r:r.__setitem__(lo_index,(r[hi_index][0],6))),
            ('original_extra_code_relocation',lambda r:r.__setitem__(lo_index+1,(f['module_offset']+f['size']-8,2))),
            ('original_export_not_R32',lambda r:r.__setitem__(export_index,(r[export_index][0],4))),
            ('original_wrong_relocation_owner',lambda r:r.__setitem__(hi_index,(0xFFFFFFFC,5))),
        ]:rejected(prefix+name,lambda change=change:b.validate_original(records_changed(original,'.rel.text',change),f))
        for name,address,word in [
            ('original_wrong_global',f['module_offset']+s['low'],(s['lo_word']&~65535)|(s['global_address']+s['addend']+4)),
            ('original_export_not_entry',s['export_field'],f['module_offset']+4),
            ('original_wrong_export_magic',s['export_header'],0x41E00000),
        ]:rejected(prefix+name,lambda a=address,w=word:b.validate_original(word_changed(original,'.text',a,w),f))
        if fi==0:
            rejected('original_transfer_core1_not_initialized',lambda:b.validate_original(word_changed(original,'.data',0x5328-original.section('.data')['addr']+8,0),f))
        else:
            e=copy.deepcopy(original);e.section('.bss').update(type=1)
            rejected('callback_storage_cannot_be_unknown_initialized_data',lambda:b.validate_original(e,f))
        e=copy.deepcopy(original);e.sections=[sec for sec in e.sections if not sec['flags']&2]
        rejected(prefix+'iopmod_overlap_is_not_allocated_code',lambda:b.allocated_read(e,0,16,True))
        e=copy.deepcopy(original);e.sections.append(copy.deepcopy(e.section('.text')))
        rejected(prefix+'ambiguous_original_allocated_domain',lambda:b.allocated_read(e,f['module_offset'],f['size'],True))
        rejected(prefix+'BSS_cannot_supply_initialized_bytes',lambda:b.allocated_read(original,original.section('.bss')['addr'],4))

    # Read-only freshness checks reject forged ownership and rehashed artifacts too.
    stale_path=output.parent/'stale_report.json'
    def stale(name,change):
        candidate=copy.deepcopy(report);change(candidate);stale_path.write_text(json.dumps(candidate))
        rejected(name,lambda:b.current_report(manifest_path,stale_path))
    def profile(r):return r['native_objects'][0]['profiles'][0]
    def proof(r):return profile(r)['complete_proof']
    def ownership(r):return proof(r)['original_source_ownership']
    def component(r):return r['module_artifacts_are_identity_observations_not_owners'][0]
    for name,change in [
        ('fresh_status_unverified',lambda r:r.update(status='UNVERIFIED_CURRENT_BUILD')),
        ('fresh_manifest_hash',lambda r:r.update(manifest_sha256='0'*64)),
        ('fresh_manifest_provenance_missing',lambda r:r.pop('manifest')),
        ('fresh_manifest_provenance_wrong',lambda r:r.update(manifest='config/iop_partial.json')),
        ('fresh_dependencies_missing',lambda r:r.update(dependency_hashes={})),
        ('fresh_historical_compiler_overclaimed',lambda r:r.update(historical_original_compiler='CONFIRMED')),
        ('fresh_general_O32_ABI_overclaimed',lambda r:r.update(general_original_O32_ABI='CONFIRMED')),
        ('fresh_EE_native_header_observation_hidden',lambda r:r.pop('native_header_note')),
        ('fresh_custom_IRX_contract_overclaimed',lambda r:r.update(custom989snd_spiop_contracts='RESOLVED')),
        ('fresh_public_mutation_lie',lambda r:r.update(public_source_manifests_profiles_guards_and_registry_changed=True)),
        ('fresh_common_dependency',lambda r:r['dependency_hashes'].update({'tools/common.py':'0'*64})),
        ('fresh_claims_missing',lambda r:r.update(functions=[])),
        ('fresh_public_reservations_missing',lambda r:r.update(published_reservations=[])),
        ('fresh_native_group_missing',lambda r:r['native_objects'].pop()),
        ('fresh_native_group_duplicate',lambda r:r['native_objects'].append(copy.deepcopy(r['native_objects'][0]))),
        ('fresh_group_false_claim',lambda r:r['native_objects'][0]['claim'].update(module_offset=0)),
        ('fresh_profile_missing',lambda r:r['native_objects'][0]['profiles'].pop()),
        ('fresh_profiles_reversed',lambda r:r['native_objects'][0]['profiles'].reverse()),
        ('fresh_compiler_flags',lambda r:profile(r).update(compiler_flags=b.BASE_FLAGS)),
        ('fresh_assembler_flags',lambda r:profile(r).update(assembler_flags=['-O2'])),
        ('fresh_native_inputs',lambda r:profile(r).update(native_input_hashes={})),
        ('fresh_assembly_transformed',lambda r:profile(r).update(assembly_untouched=False)),
        ('fresh_assembly_hash',lambda r:profile(r).update(assembly_sha256='0'*64)),
        ('fresh_object_hash',lambda r:profile(r).update(object_sha256='0'*64)),
        ('fresh_object_path_escape',lambda r:profile(r).update(object='../outside.o')),
        ('fresh_assembly_path_escape',lambda r:profile(r).update(assembly='src/auto/other.s')),
        ('fresh_missing_original_ownership',lambda r:proof(r).pop('original_source_ownership')),
        ('fresh_false_original_offset',lambda r:ownership(r).update(module_offset=0)),
        ('fresh_false_original_file_offset',lambda r:ownership(r).update(file_offset=0)),
        ('fresh_false_original_section',lambda r:ownership(r).update(section='.data')),
        ('fresh_false_original_size',lambda r:ownership(r).update(size=20)),
        ('fresh_extra_original_ownership',lambda r:ownership(r).update(preservation_counted=True)),
        ('fresh_missing_replays',lambda r:proof(r).update(signed_carry_replays=[])),
        ('fresh_false_initialized_data',lambda r:proof(r).update(initialized_nonexecutable_sections=[{'size':4}])),
        ('fresh_false_BSS',lambda r:proof(r).update(emitted_BSS=[{'size':4}])),
        ('fresh_false_relocation_count',lambda r:proof(r).update(actual_relocation_count=0)),
        ('fresh_false_source_addend',lambda r:proof(r)['raw_actual_operands'][0].update(source_addend=0)),
        ('fresh_module_identity_missing',lambda r:r['module_artifacts_are_identity_observations_not_owners'].pop()),
        ('fresh_module_identity_duplicate',lambda r:r['module_artifacts_are_identity_observations_not_owners'].append(copy.deepcopy(component(r)))),
        ('fresh_module_hash',lambda r:component(r).update(original_sha256='0'*64)),
        ('fresh_whole_module_ownership',lambda r:component(r).update(whole_module_owned=True)),
        ('fresh_original_metadata_counted',lambda r:component(r).update(original_metadata_and_all_other_bytes='SOURCE')),
        ('fresh_public_reservation_removed',lambda r:component(r).update(existing_public_source_ranges_reserved_not_counted=[])),
        ('fresh_module_code_count',lambda r:component(r).update(new_code_bytes=100)),
        ('fresh_module_source_spans',lambda r:component(r)['source_claims'][0].update(size=100)),
        ('fresh_module_original_file_size',lambda r:component(r).update(original_file_bytes=0)),
        ('fresh_partial_hash',lambda r:component(r).update(partial_sha256='0'*64)),
        ('fresh_progress_function_count',lambda r:r['progress'].update(verified_source_functions=18)),
        ('fresh_progress_byte_count',lambda r:r['progress'].update(verified_source_code_bytes=340)),
        ('fresh_progress_data_count',lambda r:r['progress'].update(verified_source_initialized_data_bytes=4)),
        ('fresh_progress_whole_module_count',lambda r:r['progress'].update(whole_module_ownership_claims=2)),
        ('fresh_progress_private_flag',lambda r:r['progress'].update(component_source_claims_only=False)),
    ]:stale(name,change)
    original_reader=Path.read_bytes
    relatives=[('source',f['source'])for f in functions]+[
        ('proposal',b.PROPOSAL),('independent_review',b.INDEPENDENT),
        ('module00','disc/irx/module_00.irx'),('module04','disc/irx/module_04.irx'),
        ('primary_libsd','iop/references/ps2sdk/libsd/libsd-common.h'),
        ('primary_rsio2','iop/references/ps2sdk/sio2man/rsio2man.h'),
        ('primary_xsio2','iop/references/ps2sdk/sio2man/xsio2man.h'),
        ('primary_license','iop/references/ps2sdk/LICENSE'),
        ('common','tools/common.py'),('public_core_manifest','config/iop_partial.json'),
        ('public_libsd_manifest','config/iop_libsd_partial.json'),
        ('native_cc1','tools/third_party/ee-gcc2.95.3-114/lib/gcc-lib/ee/2.95.3/cc1.exe')]
    for label,relative in relatives:
        def changed_read(path,pinned=(b.ROOT/relative).resolve()):
            result=original_reader(path)
            return bytes([result[0]^1])+result[1:]if path.resolve()==pinned else result
        with patch.object(Path,'read_bytes',changed_read):
            rejected('fresh_actual_'+label+'_'+Path(relative).stem,lambda:b.current_report(manifest_path,output/b.REPORT))
    rehashed=output.parent/'rehashed.o';altered=word_changed(native[0],'.text',12,0x8C420000)
    rehashed.write_bytes(altered.data)
    stale('fresh_rehashed_object_requires_real_plus4',lambda r:profile(r).update(object=rehashed.relative_to(b.ROOT).as_posix(),object_sha256=b.digest(rehashed.read_bytes())))
    altered_assembly=output.parent/'changed.raw.s';altered_assembly.write_bytes((b.ROOT/profile(report)['assembly']).read_bytes()+b'\n# forged receipt\n')
    stale('fresh_rehashed_assembly_requires_frozen_untouched_output',lambda r:profile(r).update(assembly=altered_assembly.relative_to(b.ROOT).as_posix(),assembly_sha256=b.digest(altered_assembly.read_bytes())))
    partial=output.parent/'changed.partial.irx';changed=bytearray((b.ROOT/component(report)['partial_module']).read_bytes());changed[-1]^=1;partial.write_bytes(changed)
    stale('fresh_rehashed_partial_requires_every_preserved_byte',lambda r:component(r).update(partial_module=partial.relative_to(b.ROOT).as_posix(),partial_sha256=b.digest(partial.read_bytes())))
    bad=copy.deepcopy(manifest);bad['functions'][0]['size']=20
    failed_manifest=output.parent/'failed_manifest.json';failed_manifest.write_text(json.dumps(bad));failed_output=output.parent/'failed';failed_output.mkdir(exist_ok=True)
    failed_report=failed_output/b.REPORT;failed_report.write_text(json.dumps(report))
    rejected('failed_build_invalidates_prior_success',lambda:b.run(failed_manifest,failed_output))
    assert json.loads(failed_report.read_text())['status']=='UNVERIFIED_CURRENT_BUILD'
    assert json.loads(failed_report.read_text())['progress']['verified_source_code_bytes']==0
    rejected('failed_current_build_never_supplies_counts',lambda:b.current_report(manifest_path,failed_report))

    # Full original/native machine-state comparison: real legal indices0/1,
    # opaque pointer/function-pointer bit patterns including NULL, varied bases.
    values=sorted({0,0xFFFFFFFF,0x532C,0x475480,0xBF808268,0x12345678}|{1<<i for i in range(32)}|{0xFFFFFFFF^(1<<i)for i in range(32)})
    states=0;carry_states=0
    for fi,f in enumerate(functions):
        s=b.shape(f);target,orig_records,_=b.validate_original(modules[f['module']][1],f)
        bases=b.BASES+[0x8000-s['global_address']-s['addend']-1,0x8000-s['global_address']-s['addend'],0x8000-s['global_address']-s['addend']+1]
        for profile_row in report['native_objects'][fi]['profiles']:
            e=Elf32((b.ROOT/profile_row['object']).read_bytes());payload=e.section_data(e.section('.text'));records=b.native_records(e,f)
            for base in bases:
                generated=b.relocate_native(payload,f,records,base);original_code=b.replay_original(target,orig_records,f,base)
                assert generated==original_code
                words=struct.unpack('<'+str(f['size']//4)+'I',generated);original_words=struct.unpack('<'+str(f['size']//4)+'I',original_code)
                address=s['global_address']+s['addend']+base
                high=words[s['high']//4]&65535;low=words[s['low']//4]&65535
                assert (high<<16)+((low&0x7FFF)-(low&0x8000))==address
                carry_states+=1
                for value in values:
                    for channel in([0,1]if fi==0 else[None]):
                        regs=[(i*0x13579BDF)&0xFFFFFFFF for i in range(32)];regs[0]=0;regs[4]=channel if fi==0 else value
                        effective=address+(8*channel if fi==0 else 0)
                        memory={effective-4:0x12345678,effective:value if fi==0 else 0xABCDEF00,effective+4:0x98765432}
                        actual=execute(words,regs,memory);expected=execute(original_words,regs,memory)
                        assert actual==expected and actual[3]==regs[31]
                        if fi==0:
                            assert actual[0][2]==value and actual[0][4]==channel*8 and actual[1]==memory and actual[2]==[]
                            assert all(actual[0][i]==regs[i]for i in range(32)if i not in(2,4))
                        else:
                            assert actual[2]==[effective]and actual[1][effective]==value
                            assert actual[1][effective-4]==memory[effective-4]and actual[1][effective+4]==memory[effective+4]
                            assert all(actual[0][i]==regs[i]for i in range(32)if i!=1)
                        states+=1
        rejected(f['name']+': negative_load_base',lambda:b.relocate_native(payload,f,records,-s['global_address']-s['addend']-1))
        rejected(f['name']+': negative_base_even_positive_result',lambda:b.relocate_native(payload,f,records,-1))
        rejected(f['name']+': overflowing_load_base',lambda:b.relocate_native(payload,f,records,0x100000000))
        rejected(f['name']+': noninteger_load_base',lambda:b.relocate_native(payload,f,records,0.5))
        rejected(f['name']+': original_negative_load_base',lambda:b.replay_original(target,orig_records,f,-1))
        rejected(f['name']+': original_overflowing_pointer',lambda:b.replay_original(target,orig_records,f,0xFFFFFFFF))
        rejected(f['name']+': original_truncated_replay',lambda:b.replay_original(target[:-4],orig_records,f,0))
        false_records=copy.deepcopy(orig_records);false_records[1]['word']^=4
        rejected(f['name']+': original_replay_false_recorded_operand',lambda:b.replay_original(target,false_records,f,0))
        false_records=copy.deepcopy(orig_records);false_records[1]['section']='.iopmod'
        rejected(f['name']+': original_replay_nonallocated_recorded_section',lambda:b.replay_original(target,false_records,f,0))

    # Published checkers retain their original, separately guarded admission scope.
    core=b.iop_build.current_report();assert core['progress']['verified_source_functions']==12 and core['progress']['verified_source_code_bytes']==236
    import iop_libsd_build as published_libsd
    libsd=published_libsd.current_report();assert libsd['progress']['verified_source_functions']==1 and libsd['progress']['verified_source_code_bytes']==16
    core_manifest=json.loads((b.ROOT/'config/iop_partial.json').read_text());ctrl=[f for f in core_manifest['functions']if f['source']=='iop/src/sio2man/sio2_ctrl.c']
    original00=Elf32((b.ROOT/core_manifest['module']).read_bytes());ctrl_target=b.iop_build.expected_object_text(original00,ctrl)
    ctrl_obj=Elf32((b.ROOT/core['native_groups'][0]['native_profiles'][0]['object']).read_bytes());ctrl_obj.sections.append({'name':'.rel.unproved','type':9,'size':8})
    rejected('published_module00_still_rejects_any_relocations',lambda:b.iop_build.inspect_object(ctrl_obj,ctrl,ctrl_target))
    rejected('published_libsd_single_getter_does_not_admit_indexed_getter',lambda:published_libsd.inspect_object(native[0],modules[functions[0]['module']][1]))
    assert before=={p.relative_to(b.ROOT).as_posix():b.digest(p.read_bytes())for p in protected}
    summary={'status':'PASS_PRIVATE_NOSPLIT_NATIVE_AND_FAIL_CLOSED_GUARDS','negative_guard_count':len(rejected_cases),'negative_guards':rejected_cases,
        'suite_path':Path(__file__).resolve().relative_to(b.ROOT).as_posix(),'suite_sha256':b.digest(Path(__file__).read_bytes()),
        'build_verifier_sha256':b.digest(Path(b.__file__).read_bytes()),'manifest_sha256':b.digest(manifest_path.read_bytes()),
        'fresh_native_objects':10,'functions':5,'code_bytes':88,'actual_relocations':10,'initialized_source_data_bytes':0,
        'complete_machine_state_cases':states,'complete_signed_carry_replays':carry_states,
        'machine_state_scope':'Only legal TransferRecords indices0/1; opaque pointer bits/NULL and callback stores; all unchanged GPRs, no FPR instructions, JR+NOP',
        'protected_published_files_sha256':before,'existing_protected_IOP_baseline_unchanged':'13functions/252bytes; core12/236 and libsd1/16',
        'unique_original_module_identities':2,'whole_module_ownership_claims':0,'source_progress_counted':False,
        'private_native_report':(output/b.REPORT).relative_to(b.ROOT).as_posix()}
    result_path.write_text(json.dumps(summary,indent=2)+'\n')
    print(f'PASS PRIVATE no-split: {len(rejected_cases)} rejection guards; {states} complete scalar states; {carry_states} carry replays;10objects/5functions/88bytes; existing protected13/252 components unchanged.')


if __name__=='__main__':main()
