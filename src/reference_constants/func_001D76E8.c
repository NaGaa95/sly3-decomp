// Reference algorithm: src/hand/func_0017D360.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct T { char pad[0x28]; int n28; };
struct G { char pad[0x45CC]; struct T *p45CC; };
extern struct G D_00475CB0;
struct S { char pad[0x30]; int n30; int pad2; int n38; char pad3[0x44]; float gA0; int nA4; };
void func_00238970(struct S *p);
void func_001D76E8(struct S *p) { func_00238970(p); p->n30 = -1; p->n38 = -1; p->gA0 = -3.40282346638528859812e+38f; p->nA4 = D_00475CB0.p45CC->n28; }
