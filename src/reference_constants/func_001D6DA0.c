// Reference algorithm: src/hand/func_001B1F40.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct Q { char pad[0x18]; int x18; };
struct S { char pad[0x218]; int c238; int a23C[4]; int c24C; int a250[4]; };
int func_0014D188(struct S *p, struct Q *q);
int func_0013CD00(int r, int n);
int func_0013B500(struct Q *q, int k);
int func_001D6DA0(struct S *p, struct Q *q)
{
    int i, j;
    int r = func_0014D188(p, q);
    for (i = 0; i < p->c238; i++)
        if (p->a23C[i] == q->x18) r = func_0013CD00(r, 1);
    for (j = 0; j < p->c24C; j++)
        if (func_0013B500(q, p->a250[j])) r = func_0013CD00(r, 1);
    return r;
}
