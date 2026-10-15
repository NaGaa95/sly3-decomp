// Set the receiver state, allocate the original global record, replace its reference and update that record. Complete2BA9A8 reads no incoming GP argument;2BAA50 consumes both pointers;2BE530->2B4308 consumes only record A0.
// Reference algorithm: src/hand/func_001492B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { void * record; char unknown_4[0x3F40]; int state; };
void *func_002BA9A8(void);
void func_002BAA50(void *receiver,void *record);
void func_002BE530(void *record);
void func_00249980(struct S *p){void *record;p->state=1;record=func_002BA9A8();func_002BAA50(p,record);func_002BE530(p->record);}
