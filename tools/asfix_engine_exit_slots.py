"""Explicit engine-exit-slots profile: expose guaranteed-empty exit delay slots.

The existing engine min6 padding algorithm already counts explicit conditional
exits. A compiler forward exit still in reorder mode prevents that count. This
prepass materializes its proven NOP slot without moving any instruction, then
uses the existing engine policy unchanged. No original ELF or target words are
read. Only short linear scalar loops with an explicit ordinary backedge are admitted.

The source precondition is a single scalar writer immediately before an ordinary
forward exit, writing a physical GPR read by that exit. Native SN/GNU fixtures
confirm this prevents assembler delay filling. Materializing only its NOP lets
the unchanged engine min6 policy count the nonexit path. No instruction moves,
original ELF reads, game words, ABI changes or function-specific padding occur.

This opt-in reconstruction profile establishes the measured search-loop cohort,
not a global historical assembler policy. Inline assembly, ambiguous joins,
branch-likely exits, expanded pseudos and unsupported scalar input fail closed.
"""
import re
import asfix_sly2
from asfix_sly2 import classify,reg,multi,COND

BRANCH={'beq','bne','beqz','bnez'}
LIKELY={'beql','bnel','beqzl','bnezl','blezl','bgtzl','bltzl','bgezl','bc1tl','bc1fl'}
OPS3={'addu','daddu','addiu','daddiu','and','or','xor','nor','andi','ori','xori','slt','sltu','slti','sltiu','sll','srl','sra','dsll','dsrl','dsra'}
LOADS={'lb','lbu','lh','lhu','lw','lwu','ld'}
STORES={'sb','sh','sw','sd'}
ZERO={'nop'}
PAIR={'move'}
VALID=OPS3|LOADS|STORES|ZERO|PAIR|{'lui','li'}

def operands(mn,text):
 parts=[s.strip()for s in text.split(',')]
 wanted=1 if mn=='nop'else 2 if mn in LOADS|STORES|PAIR|{'lui','li'}else 3
 if len(parts)!=wanted:raise ValueError('Invalid scalar operand count')
 if mn=='nop':
  if parts!=['']:raise ValueError('NOP has operands')
  return parts
 def gpr(item):
  if not item.startswith('$'):raise ValueError('Expected physical GPR')
  try:value=reg(item)
  except (ValueError,KeyError):raise ValueError('Invalid physical GPR')
  if not 0<=value<32:raise ValueError('Physical GPR outside0..31')
  return value
 if mn not in VALID:raise ValueError('Unsupported loop instruction')
 gpr(parts[0])
 if mn in LOADS|STORES:
  match=re.fullmatch(r'([^()]+)\((\$[\w]+)\)',parts[1])
  if not match:raise ValueError('Loop memory operand must use one GPR base')
  gpr(match[2]);offset=int(match[1],0)
  if not -32768<=offset<=32767:raise ValueError('Memory offset may expand')
 elif mn=='move':gpr(parts[1])
 elif mn in{'lui','li'}:
  int(parts[1],0)
 elif mn in OPS3:
  gpr(parts[1])
  if mn in{'addiu','daddiu','andi','ori','xori','slti','sltiu','sll','srl','sra','dsll','dsrl','dsra'} or mn in{'addu','daddu'}and not parts[2].startswith('$'):
   value=int(parts[2],0)
   if mn in{'sll','srl','sra'}:
    if not 0<=value<=31:raise ValueError('Invalid word shift')
   elif mn in{'dsll','dsrl','dsra'}:
    if not 0<=value<=63:raise ValueError('Invalid doubleword shift')
   elif mn in{'andi','ori','xori'}:
    if not 0<=value<=65535:raise ValueError('Invalid bitwise immediate')
   elif not -32768<=value<=32767:raise ValueError('Immediate may expand')
  else:gpr(parts[2])
 if multi(mn,text):raise ValueError('Multi-instruction pseudo inside loop')
 return parts

def branch_parts(mn,text):
 parts=[s.strip()for s in text.split(',')];needed=3 if mn in('beq','bne')else 2
 if mn not in BRANCH or len(parts)!=needed:raise ValueError('Unsupported branch or operand count')
 reads=set()
 for item in parts[:-1]:
  if not item.startswith('$'):raise ValueError('Branch condition is not a physical GPR')
  try:value=reg(item)
  except (ValueError,KeyError):raise ValueError('Invalid branch register')
  if not 0<=value<32:raise ValueError('Invalid branch register')
  reads.add(value)
 return parts,reads

def materialize(text):
 if re.search(r'^\s*#\s*(?:APP|NO_APP)\b',text,re.M):raise ValueError('Opaque inline assembly is outside this compiler cohort')
 lines=text.splitlines();labels={};states=[];macros=[];owners=[];state=False;macro=True;owner=None
 for i,line in enumerate(lines):
  c=classify(line)
  if c[0]=='label+':raise ValueError('Combined label/instruction is unsupported')
  if c[0]=='label':
   if c[1]in labels:raise ValueError('Duplicate compiler label')
   labels[c[1]]=i
  if c[0]=='dir':
   ent=re.fullmatch(r'\.ent\s+([\w.$]+)',c[1]);end=re.fullmatch(r'\.end\s+([\w.$]+)',c[1])
   if ent:
    if owner is not None:raise ValueError('Nested compiler function')
    owner=ent[1]
   if owner is not None and not re.fullmatch(r'\.(?:ent|end|frame|mask|fmask|globl|align|p2align|type)\b.*|\.set\s+(?:noreorder|reorder|nomacro|macro)',c[1]):raise ValueError('Unknown in-function directive')
   if re.fullmatch(r'\.set\s+noreorder',c[1]):state=True
   elif re.fullmatch(r'\.set\s+reorder',c[1]):state=False
   elif re.fullmatch(r'\.set\s+nomacro',c[1]):macro=False
   elif re.fullmatch(r'\.set\s+macro',c[1]):macro=True
   if end:
    if owner!=end[1]:raise ValueError('Mismatched compiler function end')
    owner=None
  states.append(state);macros.append(macro);owners.append(owner)
 rewrites={};records=[];claimed=set()
 for i,line in enumerate(lines):
  c=classify(line)
  if c[0]!='insn'or c[1]not in BRANCH or not states[i]:continue
  parts,reads=branch_parts(c[1],c[2]);target=parts[-1]
  if target not in labels or labels[target]>=i:continue
  head=labels[target]
  if owners[i] is None or owners[head]!=owners[i]:raise ValueError('Backedge is outside one compiler function')
  if i+1>=len(lines):raise ValueError('Backedge delay absent')
  delay=classify(lines[i+1])
  if delay[0]!='insn'or delay[1]not in VALID:raise ValueError('Unsupported explicit backedge delay')
  operands(delay[1],delay[2])
  exits=[];count=0;previous=None
  for j in range(head+1,i):
   item=classify(lines[j])
   if item[0]=='blank':continue
   if item[0]=='label':raise ValueError('Interior labels/joins make loop path ambiguous')
   if item[0]=='dir':
    if re.fullmatch(r'\.set\s+(noreorder|reorder|nomacro|macro)',item[1]):continue
    if re.fullmatch(r'\.(p2align|align)\s+2',item[1]):continue
    raise ValueError('Unknown/count-changing directive inside loop')
   if item[0]!='insn':raise ValueError('Unknown loop input')
   mn,ops=item[1],item[2]
   if mn in LIKELY:raise ValueError('Annulled branch-likely exit is unsupported')
   if mn in BRANCH:
    ep,er=branch_parts(mn,ops);label=ep[-1]
    if label not in labels or labels[label]<=i+1:raise ValueError('Exit does not leave the complete loop/backedge delay')
    if owners[labels[label]]!=owners[i]:raise ValueError('Exit crosses compiler function boundary')
    if states[j]:raise ValueError('Already explicit forward exits use the existing profile directly')
    if not macros[j]:raise ValueError('Reorder exit is inside an unsupported nomacro scope')
    if previous is None:raise ValueError('No preceding exit-condition producer')
    before=classify(lines[previous]);args=operands(before[1],before[2])
    if before[1]in STORES|ZERO:raise ValueError('Predecessor does not write a branch-condition register')
    destination=reg(args[0])
    if destination==0 or destination not in er:raise ValueError('Assembler could move the preceding instruction into the exit slot')
    # No instruction moves: the existing backend's previous-condition-write
    # rule guarantees that this reorder branch receives an empty NOP slot.
    exits.append((j,mn,ops,previous));count+=2;previous=None
   else:
    if mn not in VALID:raise ValueError('Opaque control/pseudo inside loop')
    operands(mn,ops);count+=1;previous=j
  if not exits:continue
  length=count+2
  if length>asfix_sly2.LOOP_LEN:continue
  if any(j in claimed for j,_,_,_ in exits):raise ValueError('Overlapping eligible loops')
  for j,mn,ops,producer in exits:
   claimed.add(j);indent=re.match(r'^\s*',lines[j])[0]or'\t'
   rewrites[j]=[indent+'.set noreorder',indent+'.set nomacro',lines[j],indent+'nop',indent+'.set macro',indent+'.set reorder']
  records.append({'loop_label':target,'backedge_line':i+1,'unpad_loop_path_words':length,'min_loop_words':asfix_sly2.LOOP_LEN,'materialized_exit_slots':[{'line':j+1,'branch':lines[j].strip(),'producer':lines[p].strip()}for j,_,_,p in exits]})
 if owner is not None:raise ValueError('Unclosed compiler function')
 out=[]
 for i,line in enumerate(lines):out.extend(rewrites.get(i,[line]))
 return'\n'.join(out)+'\n',records

def fix(text):
 explicit,records=materialize(text);out,count=asfix_sly2.fix(explicit)
 return out,{'materialized_exit_slots':records,'engine_padded_loops':count}
