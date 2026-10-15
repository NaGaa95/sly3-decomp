// Sly 2 reference: src/hand/func_00131738.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int pad[3]; struct VTE *vt; int pad2[2]; struct O *f18; };
struct G { struct O *po; };
void func_0013BE38(struct O *, int, int);
void func_00138898(struct O *p, int a, int b) {
    struct G volatile g;
    g.po = p;
    ((void (*)(void *))p->vt[1].pfn)((char *)p + p->vt[1].d);
    if (p->f18) ((void (*)(void *, int, int))p->f18->vt[5].pfn)((char *)p->f18 + p->f18->vt[5].d, a, b);
    func_0013BE38(p, a, b);
    { struct O *po = g.po; ((void (*)(void *))po->vt[2].pfn)((char *)po + po->vt[2].d); }
}
