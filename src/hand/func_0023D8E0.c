// Return the original complete default vector for unsupported record kinds, otherwise transform all128 record vector bits through the actual object/context helpers. Signed kind and all three transform inputs are explicit.
// Reference algorithm: src/hand/func_0017DDE8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Record {char prefix[0x98];short kind;char unknown[6];void *object;char unknown2[12];QWORD value;};
struct S { char unknown_0[0x4C]; struct Record * record; void * context; };
extern QWORD D_00317560;
int func_0028EFD8(int kind);
QWORD func_0028E990(void *object,void *context,QWORD value);
QWORD func_0023D8E0(struct S *p){if(func_0028EFD8(p->record->kind))return func_0028E990(p->record->object,p->context,p->record->value);return D_00317560;}
