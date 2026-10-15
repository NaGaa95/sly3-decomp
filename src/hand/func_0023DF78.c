// Detach both sides of each linked resource, release global references, clear the handles, and release the owner's final attached resource.
// Reference algorithm: src/hand/func_001F4E28.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct VTE { short d; short p; void (*pfn)(void *, void *); };
struct VT { struct VTE a[59]; };
struct X { char pad[0xC]; struct VT *pvt; };
struct N { void *pv0; struct N *next; int *pn8; struct X *px; };
struct E { char pad[0x60]; struct X *p60; struct N *pn; void *p68; };
struct P { char pad[0xC]; struct VT *pvt; char pad2[0xDC - 0x10]; struct E *pe; };
struct G;
extern struct G D_00475480;
void func_0023DD40(struct P *);
void func_001CBAA0(struct G *, void *);
#define VF(q, n, a) (q)->pvt->a[n].pfn((char *)(q) + (q)->pvt->a[n].d, a)
void func_0023DF78(struct P *p)
{
    struct N *pn;
    if (!p->pe) return;
    func_0023DD40(p);
    for (pn = p->pe->pn; pn; pn = pn->next) {
        struct X *q = p->pe->p60;
        q->pvt->a[58].pfn((char *)q + q->pvt->a[58].d, pn->px);
        pn->px->pvt->a[58].pfn((char *)pn->px + pn->px->pvt->a[58].d, p->pe->p60);
        func_001CBAA0(&D_00475480, pn->pv0);
        *pn->pn8 = 0;
        pn->pv0 = 0;
    }
    p->pvt->a[58].pfn((char *)p + p->pvt->a[58].d, 0);
    func_001CBAA0(&D_00475480, p->pe->p68);
    p->pe->p68 = 0;
}
