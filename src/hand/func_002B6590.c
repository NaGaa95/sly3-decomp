// Construct the original inherited receiver and both embedded interface receivers, install all three actual interface tables, and return the receiver. Full base chain2B52F0->2B8670 and all embedded constructors consume only receiver A0; no unexpressed constructor input is relied upon.
// Reference algorithm: src/hand/func_00132238.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00361638[];
extern char D_00361678[];
extern char D_003616A0[];
struct S { char unknown_0[0xC]; void * interface2; char unknown_10[0x194]; void * interface0; char unknown_1A8[0x14]; void * interface1; };
struct S *func_002B5990(struct S *receiver);
void *func_002B8898(void *receiver);
void *func_002B8718(void *receiver);
struct S *func_002B6590(struct S *p){func_002B5990(p);func_002B8898((char *)p+0x180);func_002B8718((char *)p+0x1A8);p->interface0=D_00361638;p->interface1=D_00361678;p->interface2=D_003616A0;return p;}
