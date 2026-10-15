// Replace only original record flag21 and notify the actual stored owner pointer.23DD40 consumes owner A0 only; no extra receiver argument is relied upon.
// Reference algorithm: src/hand/func_001B0808.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0x18];unsigned long flags;};
struct S {char prefix[0x20];void *owner;struct Record *record;};
void func_0023DD40(void *owner);
void func_002B5750(struct S *p,unsigned int enabled){p->record->flags=(p->record->flags&~(1UL<<21))|((unsigned long)(enabled&1)<<21);func_0023DD40(p->owner);}
