// Construct the original inherited receiver and both embedded interface receivers, install all three actual interface tables, and return the receiver. Full base chain2B52F0->2B8670 and all embedded constructors consume only receiver A0; no unexpressed constructor input is relied upon.
// Reference algorithm: src/hand/func_00132238.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0035B548[];
extern char D_0035B570[];
extern char D_0035B5B0[];
struct S { char unknown_0[0xC]; void * interface2; char unknown_10[0xD4]; void * interface0; char unknown_E8[0x28]; void * interface1; };
struct S *func_002B5328(struct S *receiver);
void *func_002B8718(void *receiver);
void *func_002B8898(void *receiver);
struct S *func_002B64D0(struct S *p){func_002B5328(p);func_002B8718((char *)p+0xD0);func_002B8898((char *)p+0xEC);p->interface0=D_0035B548;p->interface1=D_0035B570;p->interface2=D_0035B5B0;return p;}
