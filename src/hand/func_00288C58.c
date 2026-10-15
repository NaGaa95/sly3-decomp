// Apply the selected controller mode, using the stored on/off event IDs and original Sly 3 virtual slots.
// Reference algorithm: src/hand/func_0022B090.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct O;
struct VTE { short d; short pad; void (*pfn)(); };
struct O { int x0, x4, x8; struct VTE *vt; };
struct S { int k; int x4; char a8[0x48]; struct O *po; int unknown; int off_id; int on_id; };
struct G;
extern struct G D_00475480;
void *func_00292034(void *p, int c, int n);
void func_0025AD70(struct G *pg, void *p);
void func_00288C58(struct S *p, int k)
{
    struct O *po;
    if (p->k == k) return;
    p->k = k;
    switch (k) {
    case 0:
        p->x4 = 0;
        func_00292034(p->a8, 0, 0x48);
        po = p->po;
        if (po) po->vt[54].pfn((char *)po + po->vt[54].d);
        break;
    case 1:
        p->po->vt[53].pfn((char *)p->po + p->po->vt[53].d, p->on_id);
        break;
    case 2:
        p->po->vt[53].pfn((char *)p->po + p->po->vt[53].d, p->off_id);
        break;
    case 3:
        func_0025AD70(&D_00475480, p->a8);
        p->x4 = 0;
        func_00292034(p->a8, 0, 0x48);
        break;
    }
}
