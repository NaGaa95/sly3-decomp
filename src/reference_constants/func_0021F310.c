// Reference algorithm: src/hand/func_001DAE20.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int id; int a[7]; };
struct S { char pad[0x5C]; int c; struct E *ae; };
struct E *func_0021F310(struct S *p, int id) {
    int i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if (pe->id == id) return pe;
    }
    return 0;
}
