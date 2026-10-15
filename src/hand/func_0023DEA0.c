// Remove the original flag2 record from its second list after the first list cleanup. Both helpers receive every consumed pointer input explicitly, and all other flags are preserved.
// Reference algorithm: src/hand/func_0012E648.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R {char prefix[0x70];unsigned long flags;};
struct S { char unknown_0[0xDC]; struct R * record; };
extern char D_00479950[];
void func_0023DCF0(void *receiver);
void func_0011B028(void *list,void *record);
void func_0023DEA0(struct S *p){func_0023DCF0(p);if(p->record&&(p->record->flags&2)){p->record->flags&=~2UL;func_0011B028(D_00479950,p->record);}}
