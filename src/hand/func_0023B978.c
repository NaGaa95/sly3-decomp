// Set record flag19 once and detach it through both explicit pointer inputs when receiver flag56 is set. Complete23B7E8 saves receiver/record A0/A1 and supplies all other arguments internally.
// Reference algorithm: src/hand/func_001F2AD0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0x18];unsigned long flags;};
struct S { char unknown_0[0x28]; unsigned long flags; };
void func_0023B7E8(void *receiver,struct Record *record);
void func_0023B978(struct S *p,struct Record *record){if(!(record->flags&0x80000)){record->flags|=0x80000;if((int)(p->flags>>56)&1)func_0023B7E8(p,record);}}
