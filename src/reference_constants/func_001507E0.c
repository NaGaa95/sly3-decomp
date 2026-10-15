// Reference algorithm: src/hand/func_0013E510.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void *(*pfn)(); };
struct O { int pad[3]; struct VTE *vt; int pad2[2]; int f18; };
struct R { int f0; int f4; };
struct O *func_00150690(int, int, int, int);
struct O *func_001507E0(struct O *po, int a) {
    struct R *pr;
    struct O *pn;
    if (!po) return 0;
    pr = (struct R *)((void *(*)(void *))po->vt[6].pfn)((char *)po + po->vt[6].d);
    pn = func_00150690(pr->f4, a, po->f18, -1);
    ((void (*)(void *, struct O *))pn->vt[44].pfn)((char *)pn + pn->vt[44].d, po);
    return pn;
}
