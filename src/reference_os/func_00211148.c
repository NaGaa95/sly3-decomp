// Sly 2 reference: src/hand/func_001D57E0.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct S { int c; int a[0x100]; };
int func_00211148(struct S *p) {
    if (p->c == 0) return 0;
    return p->a[--p->c];
}
