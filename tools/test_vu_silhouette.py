"""Component-only whole silhouette code/header/R4/data/provenance guard recipes."""
import copy,json,struct
from pathlib import Path
import vu_silhouette_build as mesh
import vu_union_sources as union
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

def manifest_guards(bundle=mesh.DEFAULT_BUNDLE):
    m=json.loads(mesh.renderer.contained(bundle,'config/vu_silhouette_sources.json').read_bytes());cases=[]
    for key,value in [('new_original_function_count',10),('existing_eight_owners_mandatory',False),('initialized_data_bytes',4),('historical_original_compiler_identity_confirmed',True),('live_hardware_observed',True),('universal_asset_or_predecessor_domain_claim',True),('full_source_relink_complete',True)]:
        c=copy.deepcopy(m);c[key]=value;cases.append((key,c))
    for key,value in [('functions',10),('code_bytes',2352),('chain_bytes',2336),('VIF_protocol_bytes',0),('nonallocated_overlay_R32_fields',16),('source_partition_count',11),('aliases_count_as_additional_functions',True)]:
        c=copy.deepcopy(m);c['component'][key]=value;cases.append((key,c))
    result=[]
    for label,c in cases:
        try:mesh.validate_manifest(c)
        except (ValueError,KeyError,AssertionError) as err:result.append({'name':label,'rejected':True,'reason':str(err)})
        else:raise ValueError('Malformed silhouette manifest accepted: '+label)
    if len(result)!=14:raise ValueError('Incomplete manifest count/data/scope guards')
    return result

def native_guards(bundle=mesh.DEFAULT_BUNDLE,output=mesh.DEFAULT_OUTPUT):
    _,_,expected,_,_=mesh.checked_manifest(bundle);out=mesh.output_path(output);base={k:(out/(k+'.o')).read_bytes() for k in ['program','chain']};cases=[]
    for kind in base:
        e=mesh.Elf32(base[kind]);t=e.section('.vutext')
        for at in [0,t['size']-4]:
            b=bytearray(base[kind]);b[t['offset']+at]^=1;cases.append((kind,'whole native code/control'+str(at),bytes(b)))
        for sec in ['.vudata','.vubss']:
            s=e.section(sec);b=bytearray(base[kind]);struct.pack_into('<I',b,e.shoff+e.shentsize*s['index']+20,4);cases.append((kind,'unowned full '+sec,bytes(b)))
    e=mesh.Elf32(base['chain']);rel=e.section('.rel.DVP.ovlytab')
    for i in [0,3]:
        b=bytearray(base['chain']);at=rel['offset']+8*i+4;info=struct.unpack_from('<I',b,at)[0];struct.pack_into('<I',b,at,(info&~255)|3);cases.append(('chain','realR32 type'+str(i),bytes(b)))
    for kind in base:
        e=mesh.Elf32(base[kind])
        for at in range(16):
            b=bytearray(base[kind]);b[at]^=1;cases.append((kind,'whole ELF ident byte'+str(at),bytes(b)))
        for at,width,label in [(16,2,'type'),(18,2,'machine'),(20,4,'version'),(24,4,'entry'),(28,4,'phoff'),(36,4,'flags'),(40,2,'ehsize'),(42,2,'phentsize'),(44,2,'phnum'),(46,2,'shentsize'),(48,2,'shnum'),(50,2,'shstrndx')]:
            b=bytearray(base[kind]);fmt='<H' if width==2 else '<I';value=struct.unpack_from(fmt,b,at)[0];struct.pack_into(fmt,b,at,value^1);cases.append((kind,'whole ELF header '+label,bytes(b)))
        b=bytearray(base[kind]);struct.pack_into('<I',b,32,e.shoff+4);cases.append((kind,'whole section table raw bounds',bytes(b)))
        t=e.section('.vutext');b=bytearray(base[kind]);struct.pack_into('<I',b,e.shoff+e.shentsize*t['index']+16,len(b)+4);cases.append((kind,'full code section raw bounds',bytes(b)))
        data=e.section('.vudata');b=bytearray(base[kind]);struct.pack_into('<I',b,e.shoff+e.shentsize*data['index'],struct.unpack_from('<I',b,e.shoff+e.shentsize*t['index'])[0]);cases.append((kind,'duplicate entire section name',bytes(b)))
        b=bytearray(base[kind]);struct.pack_into('<I',b,e.shoff+8,2);cases.append((kind,'nonzero native null header',bytes(b)))
    result=[]
    for kind,name,b in cases:
        try:mesh.strict_native(b,kind,expected[kind],mesh.ROLES)
        except (ValueError,AssertionError,KeyError,IndexError,StopIteration,struct.error) as err:result.append({'name':name,'rejected':True,'reason':str(err)})
        else:raise ValueError('Malformed native accepted: '+name)
    return result

def record_guards(bundle=mesh.DEFAULT_BUNDLE,output=mesh.DEFAULT_OUTPUT):
    bundle=Path(bundle).resolve();out=mesh.output_path(output);_,_,expected,inputs,deps=mesh.checked_manifest(bundle);r=mesh.current_report(bundle,out);cases=[]
    def change(label,fn):
        v=copy.deepcopy(r);fn(v);cases.append((label,v))
    for k in ['program','chain']:
        change(k+' false source sha',lambda v,k=k:v['native_components'][k].__setitem__('source_sha256','0'*64))
        change(k+' false source receipt',lambda v,k=k:v['native_components'][k]['source'].__setitem__('path','src/vu/renderer_program.vsm'))
        change(k+' foreign argv',lambda v,k=k:v['native_components'][k]['actual_native_command']['argv'].append('--defsym=FORGED=1'))
        change(k+' foreign cwd',lambda v,k=k:v['native_components'][k]['actual_native_command'].__setitem__('cwd',str(mesh.ROOT)))
        change(k+' wrong compiler',lambda v,k=k:v['native_components'][k]['actual_native_command']['profile']['assembler'].__setitem__('sha256','0'*64))
    for key,value in [('exit_code',1),('stdout','forged'),('stderr','warning'),('TEMP',str(mesh.ROOT)),('TMP',str(mesh.ROOT)),('TMPDIR',str(mesh.ROOT))]:
        change('native command '+key,lambda v,key=key,value=value:v['native_components']['program']['actual_native_command'].__setitem__(key,value))
    change('foreign component job',lambda v:v['native_components']['chain'].__setitem__('native_job','00000000-0000-0000-0000-000000000000'))
    change('missing native log',lambda v:v.pop('native_command_log'))
    change('stale dependency',lambda v:v['dependency_hashes'].__setitem__('tools/vu_mesh_alt_build.py','0'*64))
    change('omitted complete original body',lambda v:v['complete_original_input_ranges'].pop())
    change('fabricated10 original functions',lambda v:v.__setitem__('verified_original_function_count',10))
    change('invented initialized data',lambda v:v.__setitem__('initialized_data_bytes',4))
    change('invented universal runtime',lambda v:v.__setitem__('unknown_predecessor_or_universal_asset_domain_claim',True))
    result=[]
    for label,v in cases:
        try:mesh.validate_report(v,bundle,out,expected,inputs,deps)
        except (ValueError,KeyError,AssertionError,TypeError) as err:result.append({'name':label,'rejected':True,'reason':str(err)})
        else:raise ValueError('Forged/stale native provenance accepted: '+label)
    if len(result)!=23:raise ValueError('Incomplete actual native source/command/freshness guards')
    return result

def shadow_guards(bundle=mesh.DEFAULT_BUNDLE,output=mesh.DEFAULT_OUTPUT):
    _,_,expected,_,_=mesh.checked_manifest(bundle);out=mesh.output_path(output)
    raw=(out/'chain.o').read_bytes();e=mesh.Elf32(raw);cases=[]
    shadows=[s for s in e.sections if s['name'].startswith('.DVP.overlay.')]
    if len(shadows)!=2:raise ValueError('Wrong exact nonallocated sizing-shadow domain')
    for i,s in enumerate(shadows):
        b=bytearray(raw);b[s['offset']+s['size']-1]^=1;cases.append(('shadow'+str(i)+' nonuniform entire fill',bytes(b)))
        for field,value,label in [(8,s['flags']|2,'unexpected ALLOC'),(4,s['type']^1,'wrong exact type'),(20,s['size']+1,'wrong entire size')]:
            b=bytearray(raw);struct.pack_into('<I',b,e.shoff+e.shentsize*s['index']+field,value);cases.append(('shadow'+str(i)+' '+label,bytes(b)))
    result=[]
    for name,b in cases:
        try:mesh.strict_native(b,'chain',expected['chain'],mesh.ROLES)
        except (ValueError,AssertionError,KeyError,IndexError,StopIteration,struct.error) as err:result.append({'name':name,'rejected':True,'reason':str(err)})
        else:raise ValueError('Malformed nonallocated sizing shadow accepted: '+name)
    if len(result)!=8:raise ValueError('Incomplete per-shadow uniform/ALLOC/type/size guards')
    return result

def run_tests(bundle=mesh.DEFAULT_BUNDLE,output=mesh.DEFAULT_OUTPUT,components=None):
    r=mesh.current_report(bundle,output);components=components or union.current_components(bundle,silhouette_output=output);rg=registry_guards(components);mg=manifest_guards(bundle);ng=native_guards(bundle,output);pg=record_guards(bundle,output);sg=shadow_guards(bundle,output)
    if len(rg)!=45 or len(mg)!=14 or len(ng)!=74 or len(pg)!=23 or len(sg)!=8:raise ValueError('Incomplete whole silhouette component guards')
    return {'status':'PASS','registry_guards':rg,'manifest_guards':mg,'native_guards':ng,'source_command_freshness_guards':pg,'nonallocated_shadow_guards':sg,'native_or_compiler_execution':False,'new_original_function_count':None,'current_report':mesh.receipt(mesh.output_path(output)/mesh.REPORT_NAME)}
if __name__=='__main__':print(json.dumps(run_tests()))
