import json,sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'tools'))
from asfix_sdk_gp64 import fix
from compiler import compile_source
from common import Elf32
from matchtool import compare_object
from relocate import ObjectLinker
raw=''

def replaced(before,after):
 if before not in raw:raise ValueError('Fixture does not contain '+repr(before))
 return raw.replace(before,after,1)

def annulled_restore(branch):
 return '''gcc2_compiled.:
\t.text
\t.ent fixture
fixture:
\t.frame $sp,32,$31
\t.mask 0x80010000,-16
\t.fmask 0x00000000,0
\tsubu $sp,$sp,32
\tsq $31,16($sp)
\tsq $16,0($sp)
\tlq $31,16($sp)
\t.set noreorder
\t.set nomacro
\t'''+branch+''' $2,$Lreturn
\tlq $16,0($sp)
\t.set macro
\t.set reorder
$Lreturn:
\t.set noreorder
\t.set nomacro
\tjr $31
\taddu $sp,$sp,32
\t.set macro
\t.set reorder
\t.end fixture
'''

def disjoint_fpr():
 return annulled_restore('beqz').replace('.frame $sp,32,$31','.frame $sp,48,$31').replace('.mask 0x80010000,-16','.mask 0x80010000,-32').replace('.fmask 0x00000000,0','.fmask 0x00100000,-16').replace('subu $sp,$sp,32','subu $sp,$sp,48').replace('addu $sp,$sp,32','addu $sp,$sp,48').replace('\tlq $31,16($sp)','\ts.s $f20,32($sp)\n\tl.s $f20,32($sp)\n\tlq $31,16($sp)')

def multiple_disjoint_fprs():
 return disjoint_fpr().replace('.frame $sp,48,$31','.frame $sp,80,$31').replace('.mask 0x80010000,-32','.mask 0x80010000,-64').replace('.fmask 0x00100000,-16','.fmask 0x00700000,-16').replace('subu $sp,$sp,48','subu $sp,$sp,80').replace('addu $sp,$sp,48','addu $sp,$sp,80').replace('\ts.s $f20,32($sp)\n\tl.s $f20,32($sp)','\ts.s $f22,64($sp)\n\ts.s $f21,56($sp)\n\ts.s $f20,48($sp)\n\tl.s $f20,48($sp)\n\tl.s $f21,56($sp)\n\tl.s $f22,64($sp)')

def main():
 global raw
 name='func_002A6270'
 source=ROOT/'src/lib/math'/f'{name}.c'
 output=ROOT/'build/tests/math_sdk_gp64'/f'{name}.o'
 output.parent.mkdir(parents=True,exist_ok=True)
 if output.exists():output.unlink()
 compile_source(source,output)
 target=Elf32((ROOT/'disc/SCUS_974.64').read_bytes())
 strict=compare_object(name,output,elf=target,linker=ObjectLinker(output,target=target))
 strict={key:value for key,value in strict.items() if key not in ('compiled','target')}
 assert strict['status']=='LINKED_MATCH',strict
 assert strict['instructions']==186 and strict['relocations']==5,strict
 assert strict['constant_sections']==[{'section':'.rodata','address':0x32BD4C,'size':28}],strict
 raw=output.with_suffix('.raw.s').read_text()
 cases={
  '128bit_mmi_body':replaced('\tmfc1\t$8,$f13','\tpor\t$16,$16,$16\n\tmfc1\t$8,$f13'),
  'non_save_quad_load':replaced('\tmfc1\t$8,$f13','\tlq $2,0($sp)\n\tmfc1\t$8,$f13'),
  'wrong_save_slot':replaced('\tsq $16,0($sp)','\tsq $16,16($sp)'),
  'wrong_restore_slot':replaced('\tlq $16,0($sp)','\tlq $16,16($sp)'),
  'missing_ra_restore_one_path':replaced('\tlq $31,16($sp)','\tnop'),
  'body_stack_adjustment':replaced('\tmfc1\t$8,$f13','\taddiu $sp,$sp,16\n\tmfc1\t$8,$f13'),
  'saved_register_write_after_restore':replaced('\tlq $16,0($sp)','\tlq $16,0($sp)\n\tmove $16,$0'),
  'restored_s0_write_before_return':replaced('$L73:', '$L73:\n\tmove $16,$0'),
  'frame_mask_missing_register':replaced('.mask\t0x80010000,-16','.mask\t0x80000000,-16'),
  'conditional_division_delay':replaced('\tjal\tfunc_002A34F0\n\tdiv.s','\tbeq $2,$0,$L50\n\tdiv.s'),
  'inline_assembly':replaced('gcc2_compiled.:','gcc2_compiled.:\n#APP\nnop\n#NO_APP'),
  'bare_indirect_call':replaced('\tmfc1\t$8,$f13','\tjalr $2\n\tmfc1\t$8,$f13'),
  'return_missing_stack_deallocation':replaced('\taddu\t$sp,$sp,32','\tnop'),
  'unrecognized_source_directive':replaced('\tmfc1\t$8,$f13','\t.word 0\n\tmfc1\t$8,$f13'),
  'beqzl_annuls_required_restore':annulled_restore('beqzl'),
  'bnezl_annuls_required_restore':annulled_restore('bnezl'),
  'non_save_quad_store':replaced('\tmfc1\t$8,$f13','\tsq $2,0($sp)\n\tmfc1\t$8,$f13'),
  'body_store_ambiguous_base':replaced('\tmfc1\t$8,$f13','\tsw $2,0($4)\n\tmfc1\t$8,$f13'),
  'fmask_overlaps_gpr_slot':replaced('.fmask\t0x00000000,0','.fmask\t0x00100000,-32'),
  'fmask_outside_frame':replaced('.fmask\t0x00000000,0','.fmask\t0x00100000,0'),
  'fmask_missing_accesses':disjoint_fpr().replace('\ts.s $f20,32($sp)\n\tl.s $f20,32($sp)\n',''),
  'body_store_overlaps_fpr_slot':disjoint_fpr().replace('\ts.s $f20,32($sp)','\tsw $2,32($sp)\n\ts.s $f20,32($sp)'),
  'different_fpr_overwrites_slot':disjoint_fpr().replace('\ts.s $f20,32($sp)','\ts.s $f21,32($sp)'),
  'fpr_restore_wrong_slot':disjoint_fpr().replace('\tl.s $f20,32($sp)','\tl.s $f20,36($sp)'),
  'body_store_overlaps_fpr_upper_half':disjoint_fpr().replace('\ts.s $f20,32($sp)','\tsw $2,36($sp)\n\ts.s $f20,32($sp)'),
  'multi_fpr_mask_overlaps_gpr_slot':multiple_disjoint_fprs().replace('.mask 0x80010000,-64','.mask 0x80010000,-32').replace('sq $31,16($sp)','sq $31,48($sp)').replace('sq $16,0($sp)','sq $16,32($sp)').replace('lq $31,16($sp)','lq $31,48($sp)').replace('lq $16,0($sp)','lq $16,32($sp)'),
 }
 for mnemonic,operand in [('sd','$2'),('sw','$2'),('sh','$2'),('sb','$2'),('swc1','$f0'),('s.s','$f0')]:
  # Offset 8 occupies the unused upper half after a 16-byte SQ becomes SD.
  # The entire original reserved slot, not just the narrowed save, is protected.
  cases['body_'+mnemonic.replace('.','_')+'_overlaps_reserved_upper_half']=replaced('\tmfc1\t$8,$f13','\t'+mnemonic+' '+operand+',8($sp)\n\tmfc1\t$8,$f13')
 cases['body_sd_crosses_reserved_boundary']=replaced('\tmfc1\t$8,$f13','\tsd $2,-4($sp)\n\tmfc1\t$8,$f13')
 results=[]
 for label,text in cases.items():
  try:fix(text)
  except ValueError as error:results.append({'case':label,'status':'REJECTED','reason':str(error)});print(label,'REJECTED',str(error))
  else:raise AssertionError('Unsafe SDK ABI fixture was accepted: '+label)
 # These positive counterparts ensure the fences distinguish normal branches
 # and disjoint scalar FPR slots rather than rejecting all such compiler forms.
 positive=[]
 for label,text in [('beqz_delay_restore',annulled_restore('beqz')),('bnez_delay_restore',annulled_restore('bnez')),('disjoint_fpr_mask_and_slots',disjoint_fpr()),('three_disjoint_fpr_slots',multiple_disjoint_fprs())]:
  fixed,evidence=fix(text);positive.append({'case':label,'status':'ACCEPTED','abi_evidence':evidence})
 (ROOT/'build/reports/math_sdk_gp64_production.json').write_text(json.dumps({'strict':strict,'cases':results,'positive_controls':positive},indent=2)+'\n')
 print(len(results),'negative fixtures rejected')
 return {'strict':strict,'negative_cases':len(results),'positive_controls':len(positive)}

if __name__=='__main__':
 print(main())
