// Reference algorithm: src/hand/func_00163B48.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(void *); };
struct O { char pad[0xC]; struct VTE *vt; };
struct S { char pad[0x44]; int n; float t; char pad2[0x64 - 0x4C]; float dt; char pad3[8]; struct O *po; };
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
extern int D_004794C4;
void func_001C8168(struct S *p);
void func_00189DA0(struct S *p, int n);
void func_00188460(struct S *p)
{
    struct O *po;
    func_001C8168(p);
    if (p->n == 1 && p->dt > 0.0f) {
        float dt = D_0036BB98.t - p->t;
        if (dt < p->dt && p->dt + D_0036BB98.dt <= dt)
            func_00189DA0(p, 0);
    }
    po = p->po;
    if (po) {
        int f = p->n == 1; if (D_004794C4) f = 0;
        if (f) {
            struct VTE *e = &po->vt[8];
            e->pfn((char *)po + e->d);
        } else {
            struct VTE *e = &po->vt[9];
            e->pfn((char *)po + e->d);
        }
    }
}
