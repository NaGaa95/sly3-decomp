"""Validate the explicit SDK soft-double profile through production compilation."""
import hashlib,json,random,struct,subprocess,sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'tools'))
from common import Elf32,target_config
from asfix_sdk_softdf import canonical_call_slots,fix,lower_literal
from compiler import compile_source
from matchtool import compare,compare_object,functions,object_functions
from reference_evidence import relocation_evidence
from relocate import ObjectLinker,symbol_addresses

def assemble(source,output,assembler):
    source.write_text(source.read_text() if source.exists() else '')
    subprocess.run([str(assembler),'-G0','-O2','-mabi=eabi','-o',output.as_posix(),source.as_posix()],check=True,capture_output=True,text=True)
    return Elf32(output.read_bytes())

def numeric_crosscheck(directory):
    cases=[]
    for value in (-32768,-1,0,1,32767,32768,65535,0xFFFFFFFF):cases.append(('dli',str(value)))
    for width in range(33,65):
        for trailing in range(65-width):cases.append(('dli',hex(((1<<width)-1)<<trailing)))
    for exponent in range(-1022,1024):
        value=2.0**exponent
        try:lower_literal('li.d','$16,'+format(value,'.20e'))
        except ValueError:continue
        cases.append(('li.d',format(value,'.20e')))
    raw=['.text','.set noreorder'];lowered=['.text','.set noreorder']
    for index,(mn,value) in enumerate(cases):
        label=f'probe_{index}';raw.extend((f'.globl {label}',label+':',f'{mn} $16,{value}'))
        lowered.extend((f'.globl {label}',label+':',*lower_literal(mn,'$16,'+value)))
    for lines in (raw,lowered):lines.extend(('.globl probe_end','probe_end:'))
    rawfile=directory/'numeric_gnu.s';rawfile.write_text('\n'.join(raw)+'\n')
    lowerfile=directory/'numeric_lowered.s';lowerfile.write_text('\n'.join(lowered)+'\n')
    gnu=ROOT/'tools/third_party/ee-gcc2.95.3-136/lib/gcc-lib/ee/2.95.3/as.exe'
    original=assemble(rawfile,directory/'numeric_gnu.o',gnu)
    rebuilt=assemble(lowerfile,directory/'numeric_lowered.o',ROOT/target_config()['assembler'])
    def blocks(elf):
        symbols={entry['name']:entry['value'] for entry in elf.symbols()}
        payload=elf.section_data(elf.section('.text'))
        return [payload[symbols[f'probe_{i}']:symbols[f'probe_{i+1}'] if i+1<len(cases) else symbols['probe_end']] for i in range(len(cases))]
    a,b=blocks(original),blocks(rebuilt)
    bad=[{'instruction':cases[i],'gnu':a[i].hex(),'lowered':b[i].hex()} for i in range(len(cases)) if a[i]!=b[i]]
    print('GNU numeric cases',len(cases),'different',len(bad),bad[:5])
    return {'cases':len(cases),'differences':bad,'gnu_assembler_sha256':hashlib.sha256(gnu.read_bytes()).hexdigest()}

def call_moves_proof():
    randomizer=random.Random(0x2953)
    pairs=0
    for left in range(32):
        for right in range(32):
            if left in (4,5,31) or right in (4,5,31):continue
            lines=[f'move $4,${left}', '.set noreorder','.set nomacro','jal dpmul',f'move $5,${right}', '.set macro','.set reorder']
            changed,proof=canonical_call_slots(lines)
            assert len(proof)==1 and changed[0]==lines[4] and changed[4]==lines[0]
            for _ in range(4):
                initial=[randomizer.getrandbits(64) for _ in range(32)];initial[0]=0
                pc=randomizer.randrange(0x100000,0x2C0000,4)
                a=initial.copy();a[4]=a[left];a[31]=pc+8;a[5]=a[right]
                b=initial.copy();b[5]=b[right];b[31]=pc+8;b[4]=b[left]
                assert a==b
            pairs+=1
    counterexamples=[]
    for left,right in ((31,16),(2,31)):
        initial=list(range(32));initial[31]=0xABCD0000;pc=0x100010
        a=initial.copy();a[4]=a[left];a[31]=pc+8;a[5]=a[right]
        b=initial.copy();b[5]=b[right];b[31]=pc+8;b[4]=b[left]
        assert a!=b and (a[4],a[5])!=(b[4],b[5])
        counterexamples.append({'source_registers':[left,right],
                                'original_arguments':[a[4],a[5]],
                                'exchanged_arguments':[b[4],b[5]]})
    return {'independent_register_pairs':pairs,'random_64bit_states_per_pair':4,
            'jal_model':'RA=PC+8 before the delay slot; compare all 32 GPRs',
            'rejected_ra_counterexamples':counterexamples}

def main():
    directory=ROOT/'build/tests/sdk_softdf';directory.mkdir(parents=True,exist_ok=True)
    numeric=numeric_crosscheck(directory)
    # Compile the production source afresh through the real runner and selected
    # profile; every negative fixture is then derived from that actual assembly.
    source=ROOT/'src/lib/gcc_agent/floatdisf.c';obj=directory/'floatdisf.o'
    if obj.exists():obj.unlink()
    compile_source(source,obj)
    target=Elf32((ROOT/'disc/SCUS_974.64').read_bytes());known=functions()
    addresses=symbol_addresses()
    bindings={'litodp':0x29CA00,'dpmul':0x29C488,'dpadd':0x29C3C8,'dptofp':0x29CC20}
    addresses.update(bindings)
    strict=compare_object('func_0029ACF8',obj,target,known,ObjectLinker(obj,addresses=addresses,target=target))
    assert strict['status']=='LINKED_MATCH' and strict['instructions']==56 and strict['relocations']==7,strict
    linked=struct.pack('<%dI'%len(strict['compiled']),*strict['compiled'])
    assert linked==target.at_vram(0x29ACF8,224) and len(linked)==224
    assert strict.get('constant_sections',[])==[]
    code,rel=object_functions(obj)['func_0029ACF8']
    shape=compare('func_0029ACF8',code,rel,target,known)
    raw_evidence=relocation_evidence(obj,'func_0029ACF8',shape)
    assert len(raw_evidence)==7
    for entry in raw_evidence:assert int(entry['expected_address'],16)==bindings[entry['symbol']],entry
    raw=obj.with_suffix('.raw.s').read_text()
    cases={
      'integer_expression':raw.replace('dli\t$3,0x1fffffffffffff','dli\t$3,symbol+1'),
      'integer_overflow':raw.replace('dli\t$3,0x1fffffffffffff','dli\t$3,0x10000000000000000'),
      'integer_non_mask':raw.replace('dli\t$3,0x1fffffffffffff','dli\t$3,0x123456789ABCDEF'),
      'double_not_power_two':raw.replace('6.55360000000000000000e4','6.55370000000000000000e4'),
      'double_infinity':raw.replace('6.55360000000000000000e4','1.0e999'),
      'double_zero':raw.replace('6.55360000000000000000e4','0.0'),
      'double_subnormal':raw.replace('6.55360000000000000000e4','4.9406564584124654e-324'),
      'double_negative':raw.replace('6.55360000000000000000e4','-65536.0'),
      'double_fpr_destination':raw.replace('li.d\t$16','li.d\t$f0'),
      'literal_zero_destination':raw.replace('dli\t$3,','dli\t$0,'),
      'literal_high_register':raw.replace('dli\t$3,','dli\t$32,'),
      'literal_expands_in_delay':raw.replace('dli\t$2,0x800','dli\t$2,0x1fffffffffffff'),
      'call_dependency_on_a1':raw.replace('move\t$4,$2\n\t.set\tnoreorder','move\t$4,$5\n\t.set\tnoreorder',1),
      'call_dependency_on_a0':raw.replace('jal\tdpmul\n\tmove\t$5,$16','jal\tdpmul\n\tmove\t$5,$4',1),
      'before_call_reads_ra':raw.replace('move\t$4,$2\n\t.set\tnoreorder','move\t$4,$31\n\t.set\tnoreorder',1),
      'delay_slot_reads_ra':raw.replace('jal\tdpmul\n\tmove\t$5,$16','jal\tdpmul\n\tmove\t$5,$31',1),
      'call_argument_register32':raw.replace('move\t$4,$2\n\t.set\tnoreorder','move\t$4,$32\n\t.set\tnoreorder',1),
      'inline_assembly':raw.replace('gcc2_compiled.:','gcc2_compiled.:\n#APP\nnop\n#NO_APP'),
      'frame_slot_overlap':raw.replace('sq $17,16($sp)','sq $17,0($sp)'),
      'quad_body':raw.replace('or\t$17,$17,$2','por\t$17,$17,$2'),
      'missing_ra_restore':raw.replace('lq $31,48($sp)','nop'),
      'body_stack_store':raw.replace('or\t$17,$17,$2','sw $2,8($sp)\n\tor\t$17,$17,$2'),
      'non_compiler_directive':raw.replace('or\t$17,$17,$2','.word 0\n\tor\t$17,$17,$2'),
    }
    rejected=[]
    for label,text in cases.items():
        assert text!=raw,label
        try:fix(text)
        except ValueError as error:rejected.append({'case':label,'reason':str(error)})
        else:raise AssertionError('Unsafe candidate was accepted: '+label)
    fixed,proof=fix(raw);assert len(proof['call_slots'])==1
    unchanged=0
    for lines in (
      ['move $4,$2','.set noreorder','.set nomacro','jal unknown','move $5,$16','.set macro','.set reorder'],
      ['move $4,$2','join:','.set noreorder','.set nomacro','jal dpmul','move $5,$16','.set macro','.set reorder'],
      ['move $5,$16','.set noreorder','.set nomacro','jal dpmul','move $4,$2','.set macro','.set reorder']):
        result,evidence=canonical_call_slots(lines);assert result==lines and evidence==[];unchanged+=1
    result={'numeric_crosscheck':numeric,'call_moves_proof':call_moves_proof(),
            'negative_guards':rejected,'non_candidates_unchanged':unchanged,
            'positive_fixture':proof,'strict_positive':{k:v for k,v in strict.items() if k not in ('compiled','target')},'raw_relocation_evidence':raw_evidence}
    (ROOT/'build/reports/sdk_softdf_validation.json').write_text(json.dumps(result,indent=2)+'\n')
    assert numeric['differences']==[],numeric['differences'][:10]
    print('Rejected',len(rejected),'negative cases; preserved',unchanged,'non-candidates; proved',result['call_moves_proof'])

if __name__=='__main__':main()
