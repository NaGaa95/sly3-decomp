// Construct the original inherited receiver, retain actual scalar identifier A1, install its actual interface table and set masked state1 before returning the receiver. Every base/state helper input is explicit.
// Reference algorithm: src/hand/func_001C3390.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x50]; int identifier; };
extern char D_00365CC0[];
void *func_00244BC8(void *receiver);
void func_00245320(void *receiver,int mask,int value);
struct S *func_00245A30(struct S *p,int identifier){func_00244BC8(p);p->identifier=identifier;p->vtable=D_00365CC0;func_00245320(p,1,1);return p;}
