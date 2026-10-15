// Clear the original state, increment the current count, apply receiver update and publish its actual integer result to the stored record. Both helpers consume only receiver before internally supplied call inputs.
// Reference algorithm: src/hand/func_00175090.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0xBC];int value;};
struct S { char unknown_0[0x50]; struct Record * record; char unknown_54[0x224]; int count; int state; };
void func_002793F0(void *receiver);
int func_00279660(void *receiver);
void func_002793A0(struct S *p){p->state=0;++p->count;func_002793F0(p);if(p->record)p->record->value=func_00279660(p);}
