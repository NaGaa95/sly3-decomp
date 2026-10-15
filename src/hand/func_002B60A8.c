// Construct the original inherited receiver and both embedded interface receivers, install all three actual interface tables, and return the receiver. Full base chain2B52F0->2B8670 and all embedded constructors consume only receiver A0; no unexpressed constructor input is relied upon.
// Reference algorithm: src/hand/func_00132238.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00354958[];
extern char D_00354998[];
extern char D_003549C0[];
struct S { char unknown_0[0xC]; void * interface2; char unknown_10[0x1FC]; void * interface0; char unknown_210[0x14]; void * interface1; };
struct S *func_002B5B18(struct S *receiver);
void *func_002B8848(void *receiver);
void *func_002B8718(void *receiver);
struct S *func_002B60A8(struct S *p){func_002B5B18(p);func_002B8848((char *)p+0x120);func_002B8718((char *)p+0x210);p->interface0=D_00354958;p->interface1=D_00354998;p->interface2=D_003549C0;return p;}
