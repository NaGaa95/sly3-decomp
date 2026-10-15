"""Explicit scalar SDK ABI adapter; never reads original game words.

This is a distinct, explicitly selected SDK ABI: callee-save GPRs preserve 64
bits in compiler-reserved 16-byte slots. It is not a generic optimization.
Only scalar compiler output with the exact .mask slot convention is admitted.
The adapter also pins empty call slots and moves a division out of a direct
call's delay before adding the SDK's two pre-division interlock instructions.
"""
import re
from collections import deque
from asfix_fdlibm import fix as order
from asfix_sly2 import classify, reg, COND, JUMPY

GPRS={'move','li','lui','ori','andi','xori','or','and','xor','nor','addu','addiu','add','addi','daddu','daddiu','dsubu','subu','sub','sll','srl','sra','sllv','srlv','srav','dsll','dsrl','dsra','dsllv','dsrlv','dsrav','slt','sltu','slti','sltiu','mfc1','mflo','mfhi','lw','lwu','lh','lhu','lb','lbu','ld','movn','movz'}
STORES={'sd','sw','sh','sb','swc1','s.s'}
STORE_WIDTH={'sd':8,'sw':4,'sh':2,'sb':1,'swc1':4,'s.s':4,'sq':16}
LIKELY={'beql','bnel','beqzl','bnezl','bgezl','bgtzl','blezl','bltzl','bc1fl','bc1tl'}
FLOATS={'li.s','mov.s','neg.s','abs.s','add.s','sub.s','mul.s','div.s','sqrt.s','cvt.s.w','cvt.w.s','trunc.w.s','c.eq.s','c.lt.s','c.le.s','lwc1','l.s','mtc1'}
PRESERVED=set(range(16,24))|{30,31}

def operands(node):return [item.strip() for item in node[2].split(',')]

def isreg(value):
    if not value.startswith('$'):return False
    try:return 0<=reg(value)<32
    except (ValueError,KeyError):return False

def wrap_bare_controls(lines):
    """Expose every compiler delay as a pair before doing any transformation."""
    parsed=[classify(line) for line in lines];out=[];inside=False;block=False
    for index,line in enumerate(lines):
        node=parsed[index]
        if node[0]=='dir' and re.match(r'\.ent\b',node[1]):inside=True
        if inside and node[0]=='dir' and re.match(r'\.set\s+noreorder\s*$',node[1]):block=True
        if inside and node[0]=='dir' and re.match(r'\.set\s+reorder\s*$',node[1]):block=False
        if inside and node[0]=='insn' and JUMPY.match(node[1]) and not block:
            mn=node[1];args=operands(node)
            direct_call=mn=='jal' and len(args)==1 and re.fullmatch(r'[$\w.]+',args[0]) and not args[0].startswith('$')
            if not direct_call and mn not in COND and not (mn in ('j','jr') and len(args)==1 and isreg(args[0]) and reg(args[0])==31):
                raise ValueError('Unsupported bare control in SDK ABI')
            out.extend(('\t.set noreorder','\t.set nomacro',line,'\tnop','\t.set macro','\t.set reorder'))
        else:out.append(line)
        if node[0]=='dir' and re.match(r'\.end\b',node[1]):inside=False
    # The production fdlibm validator checks source directives, operand counts,
    # local labels, macro expansion and all explicit control/delay scaffolding.
    order('\n'.join(out)+'\n')
    return out

def divisions_before_calls(lines):
    parsed=[classify(line) for line in lines];changes={};insertions={};block=None
    for index,node in enumerate(parsed):
        if node[0]=='dir' and re.match(r'\.set\s+noreorder\s*$',node[1]):block={'start':index,'insns':[]}
        elif block is not None and node[0]=='insn':block['insns'].append(index)
        elif block is not None and node[0]=='dir' and re.match(r'\.set\s+reorder\s*$',node[1]):
            control,delay=block['insns'];cn,dn=parsed[control],parsed[delay]
            if dn[1]=='div.s':
                args=operands(cn)
                if cn[1]!='jal' or len(args)!=1 or not re.fullmatch(r'[\w.]+',args[0]):
                    raise ValueError('A delay-slot division is supported only for a direct call')
                insertions[block['start']]=lines[delay]
                changes[delay]='\tnop'
            block=None
    out=[]
    for index,line in enumerate(lines):
        if index in insertions:out.append(insertions[index])
        out.append(changes.get(index,line))
    return out

def function_scopes(lines):
    scopes=[];start=None
    for index,line in enumerate(lines):
        node=classify(line)
        if node[0]=='dir' and re.match(r'\.ent\b',node[1]):
            if start is not None:raise ValueError('Nested SDK function')
            start=index
        if node[0]=='dir' and re.match(r'\.end\b',node[1]):
            if start is None:raise ValueError('SDK end without function')
            scopes.append((start,index));start=None
    if start is not None:raise ValueError('Unterminated SDK function')
    return scopes

def stack_access(node):
    args=operands(node)
    if len(args)!=2 or not isreg(args[0]):raise ValueError('Ambiguous saved-register operands')
    match=re.fullmatch(r'(-?(?:0x[0-9A-Fa-f]+|\d+))\((\$\w+)\)',args[1])
    if not match or not isreg(match[2]) or reg(match[2])!=29:raise ValueError('Saved-register access is not stack relative')
    return reg(args[0]),int(match[1],0)

def stack_store_offset(node):
    """This restricted ABI cohort admits only literal SP-relative stores.

    A body store through a computed pointer could alias a reserved save slot.
    Until such aliases have a separate proof, reject them rather than infer
    safety from the C source or the original game bytes.
    """
    args=operands(node)
    if len(args)!=2:raise ValueError('Ambiguous SDK store operands')
    floating=node[1] in ('swc1','s.s')
    valid_source=re.fullmatch(r'\$f(?:[0-9]|[12][0-9]|3[01])',args[0]) if floating else isreg(args[0])
    if not valid_source:raise ValueError('Invalid SDK store source register')
    match=re.fullmatch(r'(-?(?:0x[0-9A-Fa-f]+|\d+))\((\$\w+)\)',args[1])
    if not match or not isreg(match[2]) or reg(match[2])!=29:
        raise ValueError('SDK body store may alias a reserved stack slot')
    return int(match[1],0)

def overlaps(offset,width,slots,slot_width):
    return any(offset<base+slot_width and base<offset+width for base in slots.values())

def audit_restore_paths(lines,start,end,mask,slots,frame):
    parsed=[classify(line) for line in lines];instructions=[];labels={};label_pending=[]
    for index in range(start,end+1):
        node=parsed[index]
        if node[0]=='label':label_pending.append(node[1])
        elif node[0]=='insn':
            for label in label_pending:labels[label]=len(instructions)
            label_pending=[];instructions.append((index,node))
    for label in label_pending:labels[label]=len(instructions)
    for position,(_,node) in enumerate(instructions):
        if node[1] in GPRS:
            args=operands(node)
            if args and isreg(args[0]) and reg(args[0])==29:
                if len(args)!=3 or not isreg(args[1]) or reg(args[1])!=29:
                    raise ValueError('SDK body modifies the stack pointer ambiguously')
                try:amount=int(args[2],0)
                except ValueError:raise ValueError('SDK stack change is not a frame constant')
                allocation=position==0 and node[1] in ('subu','dsubu') and amount==frame
                allocation=allocation or position==0 and node[1] in ('addiu','daddiu') and amount==-frame
                previous=instructions[position-1][1] if position else None
                returning=previous and previous[1] in ('j','jr') and len(operands(previous))==1 and isreg(operands(previous)[0]) and reg(operands(previous)[0])==31
                deallocation=returning and node[1] in ('addu','addiu','daddu','daddiu') and amount==frame
                if not (allocation or deallocation):raise ValueError('SDK body changes a reserved stack frame')
    if frame:
        first=instructions[0][1];args=operands(first)
        if first[1] not in ('subu','dsubu','addiu','daddiu') or len(args)!=3 or not isreg(args[0]) or reg(args[0])!=29:
            raise ValueError('SDK frame allocation is not the first instruction')
    work=deque([(0,0,0)]);seen=set();returns=0
    def step(position,saved,restored):
        index,node=instructions[position];mn=node[1]
        if mn in ('sq','lq','sd','ld'):
            args=operands(node)
            if isreg(args[0]) and reg(args[0]) in slots:
                number,offset=stack_access(node)
                if offset!=slots[number]:raise ValueError('A save or restore changes its reserved slot')
                bit=1<<number
                if mn in ('sq','sd'):
                    if saved&bit:raise ValueError('Saved GPR is stored more than once on a path')
                    saved|=bit;restored&=~bit
                else:
                    if not saved&bit:raise ValueError('Restore lacks a dominating save')
                    restored|=bit
                return saved,restored
        if mn in GPRS:
            args=operands(node)
            if args and isreg(args[0]) and reg(args[0]) in slots:
                bit=1<<reg(args[0])
                if not saved&bit:raise ValueError('Saved GPR is written before its save')
                restored&=~bit
        if mn=='jal':
            if 31 in slots:
                if not saved&(1<<31):raise ValueError('Call precedes return-address save')
                restored&=~(1<<31)
        return saved,restored
    while work:
        position,saved,restored=work.popleft()
        state=(position,saved,restored)
        if state in seen:continue
        seen.add(state)
        if len(seen)>10000:raise ValueError('SDK restore-path analysis is ambiguous')
        if position>=len(instructions):raise ValueError('SDK function falls through without a return')
        index,node=instructions[position];mn=node[1];saved,restored=step(position,saved,restored)
        if JUMPY.match(mn):
            if position+1>=len(instructions):raise ValueError('Control lacks its checked delay')
            ds,dr=step(position+1,saved,restored);args=operands(node)
            if mn in ('j','jr') and len(args)==1 and isreg(args[0]) and reg(args[0])==31:
                if ds&mask!=mask or dr&mask!=mask:raise ValueError('A return path omits a saved GPR restore')
                delay=instructions[position+1][1];delay_args=operands(delay)
                if frame and not (delay[1] in ('addu','addiu','daddu','daddiu') and len(delay_args)==3 and isreg(delay_args[0]) and reg(delay_args[0])==29 and isreg(delay_args[1]) and reg(delay_args[1])==29 and int(delay_args[2],0)==frame):
                    raise ValueError('SDK return omits its frame deallocation')
                returns+=1;continue
            if mn=='jal':work.append((position+2,ds,dr));continue
            if mn=='b':
                if args[-1] not in labels:raise ValueError('SDK jump leaves its function')
                work.append((labels[args[-1]],ds,dr));continue
            if mn in COND:
                if args[-1] not in labels:raise ValueError('SDK conditional leaves its function')
                work.append((labels[args[-1]],ds,dr))
                # A likely branch annuls its delay on the untaken path.
                likely=mn in LIKELY
                work.append((position+2,saved if likely else ds,restored if likely else dr));continue
            raise ValueError('Unsupported control in SDK restore-path analysis')
        work.append((position+1,saved,restored))
    if not returns:raise ValueError('SDK function has no checked return')

def narrow_saved_gprs(lines):
    changes={};evidence=[]
    for start,end in function_scopes(lines):
        frame=None;mask=None;top=None;fmask=None;ftop=None
        for index in range(start,end+1):
            node=classify(lines[index])
            if node[0]=='dir' and node[1].startswith('.frame'):
                match=re.fullmatch(r'\.frame\s+\$sp,(\d+),\$31',node[1])
                if not match or frame is not None:raise ValueError('Unsupported SDK stack frame')
                frame=int(match[1])
            elif node[0]=='dir' and node[1].startswith('.mask'):
                match=re.fullmatch(r'\.mask\s+(0x[0-9a-fA-F]+),(-?\d+)',node[1])
                if not match or mask is not None:raise ValueError('Unsupported SDK GPR mask')
                mask=int(match[1],16);top=int(match[2])
            elif node[0]=='dir' and node[1].startswith('.fmask'):
                match=re.fullmatch(r'\.fmask\s+(0x[0-9a-fA-F]+),(-?\d+)',node[1])
                if not match or fmask is not None:raise ValueError('Unsupported SDK FPR mask')
                fmask=int(match[1],16);ftop=int(match[2])
        if frame is None or mask is None or fmask is None or frame%16:raise ValueError('SDK frame/masks are absent or unaligned')
        if mask>>32 or fmask>>32:raise ValueError('SDK register mask exceeds physical registers')
        registers=[number for number in range(32) if mask&(1<<number)]
        if any(number not in PRESERVED for number in registers):raise ValueError('SDK mask saves an unsupported GPR')
        slots={number:frame+top-16*rank for rank,number in enumerate(sorted(registers,reverse=True))}
        if any(offset<0 or offset+16>frame or offset%16 for offset in slots.values()):raise ValueError('SDK save slots leave the reserved stack frame')
        # This profile is explicitly scalar single-precision. Double/FPR-pair
        # operations are outside its instruction whitelist. Validate both the
        # compiler FPR metadata and its actual scalar accesses before changing
        # any GPR save width.
        fregisters=[number for number in range(32) if fmask&(1<<number)]
        # GCC114 reserves eight bytes per FPR even when the actual scalar save
        # and restore are s.s/l.s. Protect the complete reserved slot as for
        # GPRs; the unused upper half must not conceal a body overwrite.
        fslots={number:frame+ftop-8*rank for rank,number in enumerate(sorted(fregisters,reverse=True))}
        if any(offset<0 or offset+8>frame or offset%8 for offset in fslots.values()):raise ValueError('SDK FPR save slots leave the stack frame')
        if any(overlaps(offset,8,slots,16) for offset in fslots.values()):raise ValueError('SDK FPR mask overlaps a reserved GPR slot')
        stores={number:0 for number in registers};loads={number:0 for number in registers}
        fstores={number:0 for number in fregisters};floads={number:0 for number in fregisters}
        for index in range(start,end+1):
            node=classify(lines[index])
            if node[0]!='insn':continue
            mn=node[1]
            if mn in ('sq','lq') or mn in ('sd','ld') and operands(node) and isreg(operands(node)[0]) and reg(operands(node)[0]) in slots:
                number,offset=stack_access(node)
                if number not in slots or slots[number]!=offset:raise ValueError('128-bit body operation or non-SDK save slot')
                if mn in ('sq','sd'):stores[number]+=1
                else:loads[number]+=1
                if mn in ('sq','lq'):changes[index]=re.sub(r'\b'+mn+r'\b','sd' if mn=='sq' else 'ld',lines[index],count=1)
            elif mn not in GPRS|STORES|FLOATS|set(COND)|{'nop','j','jr','jal'}:
                raise ValueError('Instruction is outside scalar SDK ABI: '+mn)
            else:
                if mn in STORES:
                    offset=stack_store_offset(node)
                    if overlaps(offset,STORE_WIDTH[mn],slots,16):raise ValueError('SDK body store overlaps a reserved GPR slot')
                    if overlaps(offset,STORE_WIDTH[mn],fslots,8):
                        args=operands(node)
                        if mn not in ('swc1','s.s') or not re.fullmatch(r'\$f(?:[0-9]|[12][0-9]|3[01])',args[0]):raise ValueError('SDK body store overlaps a reserved FPR slot')
                        number=int(args[0][2:])
                        if fslots.get(number)!=offset:raise ValueError('SDK store overwrites another saved FPR')
                        fstores[number]+=1
                if mn in ('l.s','lwc1'):
                    args=operands(node)
                    if args and re.fullmatch(r'\$f(?:[0-9]|[12][0-9]|3[01])',args[0]):
                        number=int(args[0][2:])
                        if number in fslots:
                            # A masked FPR load is a restore only at its exact
                            # metadata slot. Other uses remain unsupported.
                            fake=('insn','lw','$0,'+','.join(args[1:]))
                            _,offset=stack_access(fake)
                            if fslots[number]!=offset:raise ValueError('SDK FPR restore changes its reserved slot')
                            floads[number]+=1
        if any(stores[number]!=1 or loads[number]<1 for number in registers):raise ValueError('SDK saved-register accesses are incomplete')
        if any(fstores[number]!=1 or floads[number]<1 for number in fregisters):raise ValueError('SDK saved-FPR accesses are incomplete')
        audit_restore_paths(lines,start,end,mask,slots,frame)
        evidence.append({'frame':frame,'mask':f'0x{mask:08X}','slots':slots,'fmask':f'0x{fmask:08X}','fslots':fslots})
    return [changes.get(index,line) for index,line in enumerate(lines)],evidence

def fix(text):
    lines=wrap_bare_controls(text.splitlines())
    lines=divisions_before_calls(lines)
    # Validate the rewritten compiler scaffold before interpreting any frames.
    order('\n'.join(lines)+'\n')
    lines,evidence=narrow_saved_gprs(lines)
    expanded=[]
    for line in lines:
        node=classify(line)
        if node[0]=='insn' and node[1]=='div.s':expanded.extend(('\tnop','\tnop'))
        expanded.append(line)
    fixed,count=order('\n'.join(expanded)+'\n')
    return fixed,{'interlocks':count,'abi':'gp64 saves in gp128 slots','functions':evidence}
