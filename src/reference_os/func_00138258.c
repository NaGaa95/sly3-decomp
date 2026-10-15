// Sly 2 reference: src/hand/func_00131270.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct S { int pad[5]; int a14; int a18; };
int func_00138258(struct S *p) { if (p->a18) return p->a18; return p->a14; }
