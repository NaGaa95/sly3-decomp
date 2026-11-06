// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ENT { int pos; int x4; };
struct S {
    unsigned short *pbase; unsigned short *pch; char pad8[0x84 - 8]; float f84; char pad88[0x90 - 0x88];
    float f90; int n94; struct ENT a[1];
};
void func_00264B18(struct S *p, int);
unsigned short func_00264BB0(struct S *p);
void func_00264D00(struct S *p, int n)
{
    struct ENT *pe, *pend;
    int i;
    func_00264B18(p, 0);
    pe = &p->a[1];
    pend = &p->a[p->n94];
    for (i = 0; i < n && func_00264BB0(p); i++) {
        int idx = p->pch - p->pbase - 1;
        if (pe < pend && pe->pos <= idx)
            pe++;
    }
    p->n94 = pe - p->a;
    p->f90 = p->n94 * p->f84;
    *p->pch = 0;
}
