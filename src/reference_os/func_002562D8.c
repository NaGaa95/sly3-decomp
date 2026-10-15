// Sly 2 reference: src/hand/func_0020A658.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x28]; int c; int a[1]; };
int func_002562D8(struct S *p, int n) { int i; for (i = 0; i < p->c; i++) if (n == p->a[i]) return i; return -1; }
