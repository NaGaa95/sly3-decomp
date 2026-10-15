// Reference algorithm: src/hand/func_001645D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x44]; int n; char pad2[0x5C - 0x48]; int f6c; };
struct S { char pad[0x84]; int c; struct X **apx; };
int func_00189008(struct S *p)
{
    int f = 1;
    int i;
    for (i = 0; f && i < p->c; i++) {
        struct X *px = p->apx[i];
        f = 0;
        if (px->n >= 2 || (px->n == 1 && px->f6c))
            f = 1;
    }
    return f;
}
