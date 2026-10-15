// Initialize both base object words and install its original vtable, returning the receiver.
// Reference algorithm: src/hand/func_001477B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_003521A0[];
struct S { int first; int second; char unknown_8[0x4]; void * vtable; };
struct S *func_002B8670(struct S *p){p->first=0;p->vtable=D_003521A0;p->second=0;return p;}
