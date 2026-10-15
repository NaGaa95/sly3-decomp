// Construct the inherited receiver, install its actual vtable and initialize all five original absent selections.
// Reference algorithm: src/hand/func_00179598.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00350960[];
struct S { char unknown_0[0xC]; void * vtable; int a; char unknown_14[0x20]; int b; char unknown_38[0x7C90]; int c; int d; int e; };
struct S *func_002B8670(struct S *p);
struct S *func_00283740(struct S *p){func_002B8670(p);p->vtable=D_00350960;p->a=-1;p->b=-1;p->c=-1;p->d=-1;p->e=-1;return p;}
