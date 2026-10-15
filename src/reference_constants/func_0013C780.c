// Reference algorithm: src/hand/func_00133E30.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int pad[3]; struct VTE *vt; };
struct Q { char pad[0x60]; struct O *po; };
struct S { char pad[0x44C4]; struct Q *pq; };
void func_0013C780(struct S *p) {
    struct Q *pq;
    while ((pq = p->pq) != 0) {
        struct O *po = pq->po; struct VTE *vt = po->vt;
        ((void (*)(void *))vt[54].pfn)((char *)po + vt[54].d);
    }
}
