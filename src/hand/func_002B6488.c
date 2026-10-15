// Construct the inherited receiver, install its two actual interface tables and clear both derived state words.
// Reference algorithm: src/hand/func_00179A58.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00353CC0[],D_0035BC10[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x304]; void * interface; char unknown_318[0x1BDC]; int first; int second; };
struct S *func_002B88B0(struct S *p);
struct S *func_002B6488(struct S *p){func_002B88B0(p);p->interface=D_00353CC0;p->vtable=D_0035BC10;p->first=0;p->second=0;return p;}
