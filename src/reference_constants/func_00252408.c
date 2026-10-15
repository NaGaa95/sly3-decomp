// Reference algorithm: src/hand/func_00207598.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x180]; int a; char pad2[0x1D8]; int b; };
int func_002533C0(struct S *p, int n);
int func_00252408(struct S *p) { if (p->b || p->a) return 1; return func_002533C0(p, 0x3B) != 0; }
