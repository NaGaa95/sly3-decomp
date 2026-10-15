// Reference algorithm: src/hand/func_0013C278.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct A { int n; };
struct M { char pad[0x14]; struct A *pa; };
struct S { char pad[0x164]; int st; };
int func_0013B500(int, int);
int func_0023E178(struct S *, struct M *);
int func_0014D9A8(struct S *p, struct M *pm) {
    if (p->st == 5 && func_0013B500(pm->pa->n, 0x33)) return 3;
    return func_0023E178(p, pm);
}
