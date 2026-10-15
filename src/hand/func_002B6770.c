// Construct the original inherited receiver and both embedded interface receivers, install all three actual interface tables, and return the receiver. Full base chain2B52F0->2B8670 and all embedded constructors consume only receiver A0; no unexpressed constructor input is relied upon.
// Reference algorithm: src/hand/func_00132238.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0035AB80[];
extern char D_0035ABC0[];
extern char D_0035ABE8[];
struct S { char unknown_0[0xC]; void * interface2; char unknown_10[0x144]; void * interface0; char unknown_158[0x14]; void * interface1; };
struct S *func_002B56A0(struct S *receiver);
void *func_002B8898(void *receiver);
void *func_002B8700(void *receiver);
struct S *func_002B6770(struct S *p){func_002B56A0(p);func_002B8898((char *)p+0x130);func_002B8700((char *)p+0x158);p->interface0=D_0035AB80;p->interface1=D_0035ABC0;p->interface2=D_0035ABE8;return p;}
