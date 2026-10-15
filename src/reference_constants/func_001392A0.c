// Reference algorithm: src/hand/func_00132140.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x130]; int c150; int a154[4]; int c164; int a168[4]; int f178; };
int func_001C8768(void *, int);
int func_0013B500(void *, int);
int func_0023E178(struct S *, void *);
int func_001392A0(struct S *p, void *pv) {
    int i, j;
    int f;
    i = 0;
    f = 0;
    for (; i < p->c150; i++) {
        if (func_001C8768(pv, p->a154[i])) f = 1;
    }
    for (j = 0; j < p->c164; j++) {
        if (func_0013B500(pv, p->a168[j])) f = 1;
    }
    {
        int r;
        if (p->f178) {
            if (f) r = 3;
            else r = func_0023E178(p, pv);
        } else r = f ? 2 : 1;
        return r;
    }
}
