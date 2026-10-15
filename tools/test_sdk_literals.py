"""Full original proof and fail-closed guards for the literal-only SDK profile."""
import hashlib,json,struct,subprocess,sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'tools'))
from common import Elf32,target_config
from compiler import compile_source
from matchtool import functions,object_functions,compare,compare_object
from reference_evidence import relocation_evidence
from relocate import ObjectLinker,symbol_addresses
from asfix_sly2 import classify
from asfix_sdk_literals import fix
from test_sdk_softdf import numeric_crosscheck

def replace_once(raw,before,after):
    assert before in raw,repr(before)
    return raw.replace(before,after,1)

def main():
    directory=ROOT/'build/tests/sdk_literals';directory.mkdir(parents=True,exist_ok=True)
    numeric=numeric_crosscheck(directory);assert numeric['differences']==[]
    source=ROOT/'src/lib/gcc_agent/fixunsdfdi.c'
    rawobj=directory/'fixunsdfdi_runner.o';rawobj.unlink(missing_ok=True);compile_source(source,rawobj)
    raw=rawobj.with_suffix('.raw.s').read_text();fixed,proof=fix(raw)
    assembly=directory/'fixunsdfdi.s';assembly.write_text(fixed);obj=directory/'fixunsdfdi.o'
    subprocess.run([str(ROOT/target_config()['assembler']),'-G0','-O2','-mabi=eabi','-o',str(obj),str(assembly)],check=True,capture_output=True,text=True)
    target=Elf32((ROOT/'disc/SCUS_974.64').read_bytes());known=functions();assert known['func_0029AB68']==(0x29AB68,236)
    code,rel=object_functions(obj)['func_0029AB68'];shape=compare('func_0029AB68',code,rel,target,known)
    rawrel=relocation_evidence(obj,'func_0029AB68',shape);assert len(rawrel)==11
    addresses=symbol_addresses()
    for entry in rawrel:addresses[entry['symbol']]=int(entry['expected_address'],16)
    strict=compare_object('func_0029AB68',obj,target,known,ObjectLinker(obj,addresses=addresses,target=target))
    assert strict['status']=='LINKED_MATCH'and strict['instructions']==59
    linked=struct.pack('<59I',*strict['compiled']);assert linked==target.at_vram(0x29AB68,236)
    assert not[s for s in Elf32(obj.read_bytes()).sections if s['flags']&2 and s['name']!='.text'and s['size']]
    def call_order(text):
        return[(n[1],n[2])for line in text.splitlines()if(n:=classify(line))[0]=='insn'and n[1]in('move','jal','j','jr')]
    assert call_order(raw)==call_order(fixed)
    assert object_functions(rawobj)==object_functions(obj)
    # The dependent A1=A0 double-add pair is valid because it is preserved.
    # Exchanging those moves would read the incoming A0 rather than the result.
    before=['move $4,$2','jal dpadd','move $5,$4']
    for result in (0,1,0xffffffffffffffff,0x123456789abcdef0):
        old=[0]*32;old[2]=result;old[4]=0x654321;old[31]=0x100010
        unchanged=old.copy();unchanged[4]=unchanged[2];unchanged[31]=0x100018;unchanged[5]=unchanged[4]
        swapped=old.copy();swapped[5]=swapped[4];swapped[31]=0x100018;swapped[4]=swapped[2]
        assert (unchanged[4],unchanged[5])==(result,result)
        assert (swapped[4],swapped[5])!=(result,result)
    literal=next(row['original']for row in proof['literals']if'li.d'in row['original'])
    fixture_node=classify(literal);destination=fixture_node[2].split(',')[0]
    cases={
        'not_power_of_two':replace_once(raw,literal,'li.d '+destination+',0.3'),
        'negative_literal':replace_once(raw,literal,'li.d '+destination+',-1.0'),
        'zero_literal':replace_once(raw,literal,'li.d '+destination+',0.0'),
        'infinite_literal':replace_once(raw,literal,'li.d '+destination+',1.0e999'),
        'subnormal_literal':replace_once(raw,literal,'li.d '+destination+',4.9406564584124654e-324'),
        'symbolic_literal':replace_once(raw,literal,'li.d '+destination+',data_label'),
        'invalid_gpr':replace_once(raw,literal,'li.d $32,1.0'),
        'zero_gpr':replace_once(raw,literal,'li.d $0,1.0'),
        'fpr_destination':replace_once(raw,literal,'li.d $f0,1.0'),
        'integer_overflow':replace_once(raw,literal,'dli '+destination+',0x10000000000000000'),
        'non_mask_integer':replace_once(raw,literal,'dli '+destination+',0x123456789ABCDEF'),
        'inline_assembly':replace_once(raw,'gcc2_compiled.:','gcc2_compiled.:\n#APP\nnop\n#NO_APP'),
        'non_compiler_directive':replace_once(raw,literal,'.word 0\n'+literal),
        'missing_ra_restore':replace_once(raw,'lq $31,48($sp)','nop'),
        'overlapping_saved_slot':replace_once(raw,'sq $17,16($sp)','sq $17,0($sp)'),
        'body_overwrites_saved_slot':replace_once(raw,literal,'sw $2,8($sp)\n'+literal),
        'body_computed_pointer_store':replace_once(raw,literal,'sw $2,0($4)\n'+literal),
        'quad_body_operation':replace_once(raw,literal,'por $2,$2,$2\n'+literal),
        'literal_multistep_call_delay':replace_once(raw,'jal\tdpmul\n\tmove\t$4,$17','jal\tdpmul\n\tli.d $4,1.0'),
    }
    rejected=[]
    for label,text in cases.items():
        try:fix(text)
        except ValueError as error:rejected.append({'case':label,'reason':str(error)})
        else:raise AssertionError('Unsafe fixture admitted: '+label)
    result={'status':'PRODUCTION_SDK_LITERALS_VERIFIED','positive_full_original_bytes':236,
        'strict':{k:v for k,v in strict.items()if k not in('compiled','target')},'relocation_evidence':rawrel,
        'unchanged_call_move_sequence':call_order(raw),'dependent_argument_pairs_tested':4,
        'numeric_crosscheck':numeric,'cache_dependencies':cache_dependency_proof(source),'negative_cases':rejected,'adapter_proof':proof,
        'linked_sha256':hashlib.sha256(linked).hexdigest()}
    (ROOT/'build/reports/sdk_literals_validation.json').write_text(json.dumps(result,indent=2)+'\n')
    print('SDK literals:236LINKED,11actualrelocs,no data,',len(rejected),'negativeguards, unchangedcalls')
def cache_dependency_proof(source):
    from unittest.mock import patch
    import compiler
    cc=ROOT/'tools/third_party/ee-gcc2.95.3-114'
    assembler=ROOT/target_config()['assembler']
    kwargs={'source':source,'compiler':cc,'assembler':assembler,'flags':['-x','c','-O2','-G0'],
            'apply_filter':True,'include_dirs':[],'filter_mode':'sdk-literals'}
    baseline=compiler.source_signature(**kwargs)
    real=compiler.file_hash
    dependencies=[ROOT/'tools'/name for name in ('compiler.py','asfix_sly2.py','asfix_fdlibm.py',
                    'asfix_sdk_gp64.py','asfix_sdk_softdf.py','asfix_sdk_literals.py')]
    for dependency in dependencies:
        def changed_hash(path):
            return 'independent-test-mutation' if Path(path).resolve()==dependency.resolve() else real(path)
        with patch.object(compiler,'file_hash',side_effect=changed_hash):
            assert compiler.source_signature(**kwargs)!=baseline,dependency
    return [path.relative_to(ROOT).as_posix() for path in dependencies]

if __name__=='__main__':main()
