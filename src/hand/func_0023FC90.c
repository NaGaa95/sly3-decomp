// Replace only record flag2 from the explicit input bit, then update the receiver. Complete23DF78 consumes receiver A0 only before internally setting notification arguments.
// Reference algorithm: src/hand/func_001FB018.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0x70];unsigned long flags;};
struct S { char unknown_0[0xDC]; struct Record * record; };
void func_0023DF78(void *receiver);
void func_0023FC90(struct S *p,unsigned int enabled){struct Record *record=p->record;if(record){record->flags=(record->flags&~4UL)|((unsigned long)(enabled&1)<<2);func_0023DF78(p);}}
