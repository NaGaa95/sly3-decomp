// Reference algorithm: src/hand/func_001B1030.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short pad; void (*pfn)(); };
struct V3 { int x, y, z; };
struct X { char pad[0xF0]; struct V3 v; };
struct S { int a, b, c; struct VTE *vt; char pad[0x48 - 0x10]; struct X *px58; struct X *px5c; char pad2[0x200 - 0x50]; int n; };
void func_0023C970(struct S *p);
static __inline__ void ClearV(struct V3 *pv) { pv->z = 0; pv->y = 0; pv->x = 0; }
void func_001D5E08(struct S *p)
{
    int n = p->n;
    if (n < 4) if (n >= 2) {
        struct VTE *e;
        ClearV(&p->px58->v);
        ClearV(&p->px5c->v);
        e = &p->vt[74];
        ((void (*)(void *))e->pfn)((char *)p + e->d);
    }
    func_0023C970(p);
}
