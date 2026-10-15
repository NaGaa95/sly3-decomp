"""UNRUN whole particle/native/input/provenance and mandatory-nine-owner guards.
No registry mutation, publisher, tree copy, assembler or fixture.
Operational tests require a complete current canonical native component.
"""
import copy,json,struct,hashlib
from pathlib import Path
import vu_particle_build as particle
import vu_union_sources as union
H=lambda b:hashlib.sha256(b).hexdigest()

def rejected(call,etype,message):
    try:call()
    except Exception as err:
        if type(err).__name__!=etype or not(str(err).startswith(message)if message else str(err)==''):
            raise ValueError('Wrong intended guard: '+repr((etype,message,type(err).__name__,str(err))))from err
        return{'rejected':True,'actual_exception':type(err).__name__,'actual_reason':str(err),'intended_exception':etype,'intended_reason_prefix':message,'blank_reason_explicit':message==''}
    raise ValueError('Malformed component accepted')

def registry_guards(components):
    union.validate_registry(components);cases=[]
    for i in range(9):
        c=copy.deepcopy(components);c.pop(i);cases.append(('missing mandatory owner'+str(i),c))
    c=copy.deepcopy(components);c.append(copy.deepcopy(c[-1]));cases.append(('duplicate mandatory owner',c))
    for i in [4,5,6,7,8]:
        for key,value in [('functions',{4:37,5:30,6:22,7:3,8:10}[i]),('code_bytes',components[i]['chain_bytes']),('VIF_protocol_bytes',0),('chain_bytes',components[i]['chain_bytes']-8),('EE_chain_begin',0x2c4600),('original_function_count_complete',True),('aliases_count_as_additional_functions',True)]:
            c=copy.deepcopy(components);c[i][key]=value;cases.append(('unknown owner'+str(i)+' '+key,c))
    result=[]
    for name,c in cases:
        try:union.validate_registry(c)
        except (ValueError,KeyError) as err:result.append({'name':name,'rejected':True,'reason':str(err)})
        else:raise ValueError('Malformed registry accepted: '+name)
    return result

def manifest_guards(bundle=particle.DEFAULT_BUNDLE):
    m=json.loads(particle.renderer.contained(bundle,'config/vu_particle_sources.json').read_bytes());particle.validate_manifest(m);rows=[]
    for key,value,msg in[
      ('new_original_function_count',3,'Three authored partitions'),('existing_seven_owners_mandatory',False,'Three authored partitions'),
      ('initialized_data_bytes',4,'False EE/template/data'),('BSS_bytes',4,'False EE/template/data'),('EE_C_CPP_code_bytes_delta',3800,'False EE/template/data'),
      ('historical_original_compiler_identity_confirmed',True,'Unsupported compiler/hardware'),('live_hardware_observed',True,'Unsupported compiler/hardware'),
      ('universal_asset_or_predecessor_domain_claim',True,'Unsupported compiler/hardware'),('full_source_relink_complete',True,'Unsupported compiler/hardware')]:
        v=copy.deepcopy(m);v[key]=value;rows.append({'case':key,**rejected(lambda v=v:particle.validate_manifest(v),'ValueError',msg)})
    for key,value in[('functions',3),('code_bytes',3824),('chain_bytes',3800),('VIF_protocol_bytes',0),('nonallocated_overlay_R32_fields',0),('source_partition_count',4),('post_entry_VIF_command',0x17000000),('post_entry_VIF_command_name','MSCNT'),('dynamic_REFS_source_credit',16)]:
        v=copy.deepcopy(m);v['component'][key]=value;rows.append({'case':key,**rejected(lambda v=v:particle.validate_manifest(v),'ValueError','Wrong whole particle ownership')})
    return rows

def native_guards(bundle=particle.DEFAULT_BUNDLE,output=particle.DEFAULT_OUTPUT):
    _,_,expected,_,_=particle.checked_manifest(bundle);out=particle.output_path(output);base={k:(out/(k+'.o')).read_bytes()for k in['program','chain']};elfs={k:particle.Elf32(v)for k,v in base.items()};rows=[];accepted=[]
    def check(name,kind,raw,typ='AssertionError',message=''):
        rows.append({'case':name,'kind':kind,'base_sha256':H(base[kind]),'mutated_whole_object_sha256':H(raw),'mutated_whole_bytes':len(raw),**rejected(lambda:particle.strict_native(raw,kind,expected[kind],particle.ROLES),typ,message)})
    def field(kind,sec,at,value):
        e=elfs[kind];raw=bytearray(base[kind]);struct.pack_into('<I',raw,e.shoff+e.section(sec)['index']*40+at,value);return bytes(raw)
    for word in range(950):
        pc=word*4
        for kind in['program','chain']:
            e=elfs[kind];offset=pc if kind=='program'else pc+8 if pc<2048 else pc+16;offset+=e.section('.vutext')['offset'];raw=bytearray(base[kind]);raw[offset]^=1
            check('all_lower_upper_word'+str(word),kind,bytes(raw),message="('Whole allocated native mismatch'")
    for rel in[0,4,2056,2060,3816,3820]:
        off=elfs['chain'].section('.vutext')['offset']+rel
        for bit in range(32):
            raw=bytearray(base['chain']);w=struct.unpack_from('<I',raw,off)[0];struct.pack_into('<I',raw,off,w^(1<<bit));check('all_static_control_'+str(rel)+'_bit'+str(bit),'chain',bytes(raw),message="('Whole allocated native mismatch'")
    for kind in['program','chain']:
        e=elfs[kind]
        for at in range(16):
            raw=bytearray(base[kind]);raw[at]^=1;check('entireELFident'+str(at),kind,bytes(raw),'ValueError','Wrong native ELF ident/class/endian/version/OSABI/padding')
        for at,width in[(16,2),(18,2),(20,4),(24,4),(28,4),(36,4),(40,2),(42,2),(44,2),(46,2)]:
            raw=bytearray(base[kind]);fmt='<H'if width==2 else'<I';v=struct.unpack_from(fmt,raw,at)[0];struct.pack_into(fmt,raw,at,v^1);check('entireELFprofile'+str(at),kind,bytes(raw),'ValueError','Unsupported entire native ELF header profile')
        # Insert4 bytes before SHT, move SHT, then allocate one genuine new byte.
        # This shape reaches whole-data rejection without an earlier raw overlap.
        raw=bytearray(base[kind][:e.shoff]+bytes(4)+base[kind][e.shoff:]);struct.pack_into('<I',raw,32,e.shoff+4);h=e.shoff+4+e.section('.vudata')['index']*40;struct.pack_into('<I',raw,h+16,e.shoff);struct.pack_into('<I',raw,h+20,1)
        check('actual_nonoverlap_initialized_data',kind,bytes(raw),message='Unproved whole initialized data/BSS')
        check('new_BSS_byte',kind,field(kind,'.vubss',20,1),message='Unproved whole initialized data/BSS')
    for kind in['program','chain']:
        e=elfs[kind]
        for at in[48,50]:
            raw=bytearray(base[kind]);v=struct.unpack_from('<H',raw,at)[0];struct.pack_into('<H',raw,at,v^1);check('section_inventory_header'+str(at),kind,bytes(raw),'ValueError','Wrong complete native section/string index header')
        raw=bytearray(base[kind]);struct.pack_into('<I',raw,32,e.shoff+4);check('whole_SHT_bounds',kind,bytes(raw),'ValueError','Invalid whole native section table bounds')
        raw=bytearray(base[kind]);struct.pack_into('<I',raw,e.shoff,1);check('nonzero_null_header',kind,bytes(raw),'ValueError','Nonzero native null-section header')
        check('whole_code_raw_bounds',kind,field(kind,'.vutext',16,len(base[kind])+4),'ValueError','Native section raw data escapes complete object bounds')
        check('whole_raw_section_overlap',kind,field(kind,'.strtab',16,e.section('.vutext')['offset']),'ValueError','Overlapping whole native raw sections')
    e=elfs['program'];st=e.section('.symtab')
    for sym in[x for x in e.symbols()if x['type']==2]:
        raw=bytearray(base['program']);struct.pack_into('<I',raw,st['offset']+16*sym['index']+8,sym['size']-8);check('whole_partition_size_'+sym['name'],'program',bytes(raw),message='Incomplete authored native source partition symbols')
        raw=bytearray(base['program']);struct.pack_into('<H',raw,st['offset']+16*sym['index']+14,e.section('.vudata')['index']);check('whole_partition_section_'+sym['name'],'program',bytes(raw))
        raw=bytearray(base['program']);raw[st['offset']+16*sym['index']+13]=0;check('whole_partition_visibility_'+sym['name'],'program',bytes(raw))
    e=elfs['chain'];rel=e.section('.rel.DVP.ovlytab')
    for i in range(4):
        raw=bytearray(base['chain']);at=rel['offset']+8*i+4;v=struct.unpack_from('<I',raw,at)[0];struct.pack_into('<I',raw,at,(v&~255)|4);check('each_actual_R32_'+str(i),'chain',bytes(raw))
    shadows=[s for s in e.sections if s['name'].startswith('.DVP.overlay.')]
    if len(shadows)!=2:raise ValueError('Exact two whole sizing shadows required')
    for i,s in enumerate(shadows):
        for fill in[0,0x67,255]:
            raw=bytearray(base['chain']);raw[s['offset']:s['offset']+s['size']]=bytes([fill])*s['size'];proof=particle.strict_native(bytes(raw),'chain',expected['chain'],particle.ROLES)
            accepted.append({'case':'exact_uniform_NONALLOCfill','shadow':i,'fill':fill,'whole_mutated_object_sha256':H(raw),'entire_original_allocated_equal':proof['entire_native_original_equal'],'source_credit':0})
        raw=bytearray(base['chain']);raw[s['offset']+s['size']-1]^=1;check('whole_NONALLOC_nonuniform'+str(i),'chain',bytes(raw),message='Nonuniform nonallocated DVP sizing shadow')
        check('whole_NONALLOC_becameALLOC'+str(i),'chain',field('chain',s['name'],8,7),message='Unsupported allocated native section')
    if any((out/(k+'.o')).read_bytes()!=v for k,v in base.items()):raise ValueError('Read-only guard modified whole native object')
    return{'rejections':rows,'documented_uniform_acceptances_source0':accepted,'whole_original_objects_unchanged':True,'native_compiles':0}

def input_guards(bundle=particle.DEFAULT_BUNDLE):
    _,e,_,_,_=particle.checked_manifest(bundle);docs={rel.rsplit('/',1)[1]:json.loads(particle.renderer.contained(bundle,rel).read_bytes())for rel in particle.EXPECTED_EVIDENCE};rows=[]
    def change(name,fn,msg):
        v=copy.deepcopy(docs);fn(v);rows.append({'case':name,**rejected(lambda:particle.verify_original_inputs(e,v),'ValueError',msg)})
    support='vu_particle_runtime_input_support.json';runtime='vu_particle_runtime_input_review.json';correction='vu_particle_protocol_label_correction.json'
    change('missing whole runtime range',lambda v:v[runtime]['whole_original_ranges_rechecked'].pop(),'Missing96 complete original range occurrences')
    change('wrong whole runtime hash',lambda v:v[runtime]['whole_original_ranges_rechecked'][0].__setitem__(2,'0'*64),'Changed entire original runtime input range')
    change('wrong actual anchor',lambda v:v[support]['EE_anchor_words'][0].__setitem__('word','00000000'),'Changed actual original runtime operand anchor')
    change('missing distinct anchor',lambda v:v[support]['EE_anchor_words'].pop(),'Missing139 distinct actual original operand anchors')
    change('missing full new input body',lambda v:v[support]['whole_new_original_functions'].pop(),'Missing complete new runtime body windows')
    change('bad body original hex',lambda v:v[support]['whole_new_original_functions'][0].__setitem__('entire_original_hex','00'),'Changed complete new runtime input body')
    change('runtimeBSS falselysource',lambda v:v[support].__setitem__('source_credit',192),'Runtime BSS/shader/pool/CPU inputs cannot become source-data claims')
    change('incorrect67 capacity',lambda v:v[runtime]['capacity_and_VU_inputs'].__setitem__('N_domain',[1,67]),'Wrong actual43-decimal particle range/read/store bounds')
    change('outofbounds bankstore',lambda v:v[runtime]['capacity_and_VU_inputs']['TOP_pages'][1].__setitem__('end_exclusive',1030),'Out-of-VU-memory second-bank/wholeqword range')
    change('wrongCIDfactory',lambda v:v[runtime]['actual_receiver'].__setitem__('CID',27),'Wrong genuine dynamic receiver dispatch')
    change('incorrect historicalMSCNT',lambda v:v[correction].__setitem__('actual_emitted_VIF_command',0x17000000),'Historical MSCNT wording must remain withdrawn')
    change('changed FLUSH helper',lambda v:v[correction]['actual_helper'].__setitem__('whole_original_hex_input_only','00'),'Changed entire post-entry FLUSH helper')
    change('confused VUbyte/immediate',lambda v:v[correction].__setitem__('actual_MSCAL_entries_VU_bytes',[0,0x73,0x110]),'Confused actual VU byte address and VIF instruction immediate')
    change('forged codecommentdiff',lambda v:v[correction].__setitem__('canonical_source_all_bytes_identical',False),'Unreviewed source/protocol/comment changes')
    return rows

def record_guards(bundle=particle.DEFAULT_BUNDLE,output=particle.DEFAULT_OUTPUT):
    bundle=Path(bundle).resolve();out=particle.output_path(output);_,_,expected,inputs,deps=particle.checked_manifest(bundle);r=particle.current_report(bundle,out);rows=[]
    def change(name,fn,message):
        v=copy.deepcopy(r);fn(v);rows.append({'case':name,**rejected(lambda:particle.validate_report(v,bundle,out,expected,inputs,deps),'ValueError',message)})
    for k in['program','chain']:
        change(k+'sourcehash',lambda v,k=k:v['native_components'][k].__setitem__('source_sha256','0'*64),'Stale/foreign actual native source signature')
        change(k+'argv',lambda v,k=k:v['native_components'][k]['actual_native_command']['argv'].append('--defsym=FORGED=1'),'False/stale native argv/cwd/profile/exit/stdout/stderr/TEMP identity')
        change(k+'cwd',lambda v,k=k:v['native_components'][k]['actual_native_command'].__setitem__('cwd',str(particle.ROOT)),'False/stale native argv/cwd/profile/exit/stdout/stderr/TEMP identity')
    for key,value in[('exit_code',1),('stdout','forged'),('stderr','warning'),('TEMP',str(particle.ROOT)),('TMP',str(particle.ROOT)),('TMPDIR',str(particle.ROOT))]:
        change('command'+key,lambda v,key=key,value=value:v['native_components']['program']['actual_native_command'].__setitem__(key,value),'False/stale native argv/cwd/profile/exit/stdout/stderr/TEMP identity')
    change('stale source input dependency',lambda v:v['dependency_hashes'].__setitem__('tools/vu_particle_native.py','0'*64),'Stale source/native/input report')
    change('missing whole input range',lambda v:v['complete_original_input_ranges'].pop(),'Stale source/native/input report')
    change('forged3functions',lambda v:v.__setitem__('verified_original_function_count',3),'False routine/data/dynamic-input source count')
    change('dynamicREFS sourcecredit',lambda v:v.__setitem__('dynamic_REFS_source_credit',16),'False routine/data/dynamic-input source count')
    change('postentryMSCNT',lambda v:v.__setitem__('post_entry_actual_VIF_name','MSCNT'),'False FLUSH/range/anchor predicate')
    change('wronguniquerangecount',lambda v:v.__setitem__('unique_original_input_ranges',96),'False FLUSH/range/anchor predicate')
    change('universalborrowedstability',lambda v:v.__setitem__('unknown_predecessor_or_universal_asset_domain_claim',True),'False compiler/universal/runtime/relink claim')
    return rows

def run_tests(bundle=particle.DEFAULT_BUNDLE,output=particle.DEFAULT_OUTPUT):
    current=particle.current_report(bundle,output);registry=registry_guards(union.current_components(bundle,particle_output=output));manifest=manifest_guards(bundle);native=native_guards(bundle,output);inputs=input_guards(bundle);records=record_guards(bundle,output)
    return{'status':'PASS','kind':'component-only-no-registry-or-publisher','registry_guards':registry,'manifest_guards':manifest,'whole_native_guards':native,'actual_original_input_guards':inputs,'source_command_freshness_guards':records,'three_partitions_not_original_functions':True,'known_previous19_count_unchanged':True,'96occurrences94unique139anchors':True,'FLUSH11000000_neverMSCNT':True,'original_and_borrowed_CPU_inputs_source0':True,'native_or_compiler_or_fixture_execution':False,'current_component_report':particle.receipt(particle.output_path(output)/particle.REPORT_NAME)}

if __name__=='__main__':print(json.dumps(run_tests()))
