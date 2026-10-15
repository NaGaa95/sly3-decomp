// Construct the inherited receiver, install its actual vtable and initialize all five original absent selections.
// Reference algorithm: src/hand/func_00179598.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0034EB20[];
struct S { char unknown_0[0xC]; void * vtable; char unknown_10[0x110]; int a; int b; int c; int d; int e; };
struct S *func_002606A0(struct S *p);
struct S *func_00260220(struct S *p){func_002606A0(p);p->vtable=D_0034EB20;p->a=-1;p->b=-1;p->c=-1;p->d=-1;p->e=-1;return p;}
