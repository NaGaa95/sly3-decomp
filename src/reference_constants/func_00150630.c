// Reference algorithm: src/hand/func_0013E368.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct E { int id; const unsigned short *pv; };
struct S { char pad[0x4E54]; int c; struct E *a; };
extern const unsigned short D_004BB210[];
const unsigned short *func_00150630(struct S *p, int id) {
    int i;
    if (id == -1) return D_004BB210;
    for (i = 0; i < p->c; i++) {
        if (p->a[i].id == id) return p->a[i].pv;
    }
    return D_004BB210;
}
