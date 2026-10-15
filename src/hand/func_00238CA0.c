// Apply inherited activation, set the original tagged flag through its direct/indirect representation, and clear flag3 in the64-bit receiver word. Complete23C580 inherited chain consumes only receiver before internally supplied call inputs.
// Reference algorithm: src/hand/func_001EF850.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0x3C]; unsigned int tagged_flags; char unknown_40[0xE8]; unsigned long flags; };
void func_0023C580(void *receiver);
void func_001C9118(void *receiver,int active);
void func_00238CA0(struct S *p){unsigned int value;func_0023C580(p);func_001C9118(p,1);value=p->tagged_flags;if((value^1)&1)*(unsigned int *)value|=2;else p->tagged_flags=value|2;p->flags&=~8UL;}
