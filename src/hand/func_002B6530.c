// Construct the original inherited receiver and both embedded interface receivers, install all three actual interface tables, and return the receiver. Full base chain2B52F0->2B8670 and all embedded constructors consume only receiver A0; no unexpressed constructor input is relied upon.
// Reference algorithm: src/hand/func_00132238.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00365DE0[];
extern char D_00365E20[];
extern char D_00365E48[];
struct S { char unknown_0[0xC]; void * interface2; char unknown_10[0xE4]; void * interface0; char unknown_F8[0x14]; void * interface1; };
struct S *func_002B5328(struct S *receiver);
void *func_002B8898(void *receiver);
void *func_002B8718(void *receiver);
struct S *func_002B6530(struct S *p){func_002B5328(p);func_002B8898((char *)p+0xD0);func_002B8718((char *)p+0xF8);p->interface0=D_00365DE0;p->interface1=D_00365E20;p->interface2=D_00365E48;return p;}
