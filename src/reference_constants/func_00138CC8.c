// Reference algorithm: src/hand/func_00131B60.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct P { int a; int b; };
struct E { char pad[0x94]; int f94; int f98; int f9c; char pad2[0x100 - 0xa0]; };
struct S { char pad[0x40]; int c; struct E *ae; };
void func_00138C70(void *, struct S *, struct E *);
void func_00138CC8(void *pv, struct S *p, int cp, struct P *ap) {
    int i, j;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        for (j = 0; j < cp; j++) {
            struct P *pp = &ap[j];
            if ((pe->f9c == pp->a || pp->a == -1) && (pe->f94 == pp->b || pp->b == -1)) {
                func_00138C70(pv, p, pe);
                break;
            }
        }
    }
}
