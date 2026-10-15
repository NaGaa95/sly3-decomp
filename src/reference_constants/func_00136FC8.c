// Reference algorithm: src/hand/func_00130010.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; int (*pfn)(); };
struct O { int pad[3]; struct VTE *vt; };
struct A { int f0; int f4; };
extern char D_00475480[];
struct O *func_0017E1B8(void *, int, int, void *);
void func_00136FC8(void *p, void *q, struct A *pa, struct O **ppo, int *pn) {
    if (q) *ppo = func_0017E1B8(D_00475480, 1, pa->f4, q);
    else *ppo = func_0017E1B8(D_00475480, 4, pa->f4, p);
    if (!*ppo) *pn = 0;
    else { struct O *po = *ppo; *pn = ((int (*)(void *, int))po->vt[47].pfn)((char *)po + po->vt[47].d, pa->f0); }
}
