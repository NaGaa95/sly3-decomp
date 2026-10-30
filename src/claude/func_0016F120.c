// SLY3_CFLAGS: -Os -G0
struct DL { void *head; void *tail; int ibDle; };
struct DLI { struct DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; };
struct VTE { short d; short pad; void (*pfn)(void *, int); };
struct OBJ { char pad[0xC]; struct VTE *vt; };
struct ITEM { char pad[0x14]; void *owner; };
struct ENT { int kind; struct OBJ *pobj; int arg; };
struct GRP { char pad[0x44]; int iEnd; };
struct S0 { char pad[0x44]; struct GRP *agrp; char pad1[0x4C - 0x48]; struct ENT *aent; char x50[0x698 - 0x50]; int igrp; };
extern struct DL D_00479D98;
extern struct DLI *g_psliFirst;
void func_0011AE28(struct DL *pdl, void *pv);
void func_00117E88(void *p);
static inline void InitDli(struct DLI *pdli, struct DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = g_psliFirst;
    g_psliFirst = pdli;
}
static inline void *PvNextDli(struct DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
#define VCALL(o, i, a) ((o)->vt[i].pfn((char *)(o) + (o)->vt[i].d, a))
void func_0016F120(struct S0 *p)
{
    struct DLI dli;
    struct ITEM *pitem;
    int i;
    if (p->igrp < 0) return;
    InitDli(&dli, &D_00479D98);
    while ((pitem = PvNextDli(&dli)) != 0) {
        if (pitem->owner == p->x50)
            func_0011AE28(&D_00479D98, pitem);
    }
    i = 0;
    if (p->igrp > 0) i = p->agrp[p->igrp - 1].iEnd;
    for (; i < p->agrp[p->igrp].iEnd; i++) {
        struct ENT *pent = &p->aent[i];
        switch (pent->kind) {
        case 0:
            if (pent->pobj) VCALL(pent->pobj, 16, -1);
            break;
        case 1:
            if (pent->pobj) VCALL(pent->pobj, 16, pent->arg);
            break;
        }
    }
    func_00117E88(p->x50);
    p->igrp = -1;
    g_psliFirst = dli.m_pdliNext;
}
