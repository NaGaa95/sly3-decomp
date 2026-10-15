// Store the explicit mask and clear/update the original receiver when its attached record mask intersects it; helper inputs are receiver and literal option0.
// Reference algorithm: src/hand/func_002108E8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0x10];unsigned int mask;};
struct S { char unknown_0[0x30]; void * resource; char unknown_34[0xC]; struct Record * record; char unknown_44[0x4]; unsigned int mask; };
void func_00239F58(void *receiver);
void func_0023A428(void *receiver,int option);
void func_0023A9F0(struct S *p,unsigned int mask){p->mask=mask;if(p->resource && (p->record->mask&mask)){func_00239F58(p);func_0023A428(p,0);}}
