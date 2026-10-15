// Sly 2 reference: src/hand/func_00194640.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct S { int a, b, k, c; };
static __inline__ int FX(struct S *p) { return p->c == 9 || p->c == 10; }
int func_001B5DD8(struct S *p) {
    switch (p->k) {
    case 8: if (FX(p)) goto one; break; case 0xC: one: return 1;
    }
    return 0;
}
