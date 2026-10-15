// Mark the stored record registered and append it to the original global list only once, with explicit list and node inputs.
// Reference algorithm: src/hand/func_001F4BA8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0x70];unsigned long flags;};
struct S { char unknown_0[0xDC]; struct Record * record; };
extern char D_00479944[];
void func_0011AF60(void *list,void *node);
void func_0023DCA0(struct S *p){struct Record *record=p->record;if(record && !(record->flags&1)){record->flags|=1;func_0011AF60(D_00479944,p->record);}}
