// Construct the original inherited receiver, install the actual derived vtable and clear its seven derived integer words; return receiver.
// Reference algorithm: src/hand/func_001885B8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_003689B0[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x3D4]; int value0; int value1; int value2; int value3; int value4; int value5; int value6; };
struct S *func_002B5898(struct S *p);
struct S *func_002B7820(struct S *p){func_002B5898(p);p->vtable=D_003689B0;p->value0=0;p->value1=0;p->value2=0;p->value3=0;p->value4=0;p->value5=0;p->value6=0;return p;}
