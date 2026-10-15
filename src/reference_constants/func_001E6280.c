// Reference algorithm: src/hand/func_001BC0D0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct ALLOCREQ { int cb; int nKind; };
struct T8 { int a, b; };
struct P { char pad[0xD8]; int cE8; char pad1[0x1C0 - 0xDC]; struct T8 t1D0; int pad2[2]; struct T8 t1E0; int pad3; void *pv1EC; };
void func_0022D740(struct P *p, void *source);
void *func_001D2538(struct ALLOCREQ *preq);
static __inline__ void *PvAllocA(struct ALLOCREQ *preq, int cb, int nKind)
{
    preq->cb = cb;
    preq->nKind = nKind;
    return func_001D2538(preq);
}
void func_001E6280(struct P *p, void *source)
{
    struct T8 a = p->t1D0;
    struct T8 b = p->t1E0;
    struct ALLOCREQ req;
    func_0022D740(p, source);
    p->t1D0 = a;
    p->t1E0 = b;
    p->pv1EC = PvAllocA(&req, p->cE8 * 16 - 16, 0x10);
}

