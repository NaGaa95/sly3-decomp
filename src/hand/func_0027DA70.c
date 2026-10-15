// Run pre-update callbacks for matching entries, traverse the mutation-safe linked list to update flagged resources, and run post-update callbacks with the live iteration index exposed to the owner.
// Reference algorithm: src/hand/func_002267C0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct DL { void *head; void *tail; int ibDle; } DL;
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *D_0036AE94;     /* g_pdliFirst */
struct VTE { short d; short pad; void (*pfn)(); };
struct O { char pad[0xC]; struct VTE *vt; };
struct E { int grf; struct O *po; };
struct Q { char pad[0x3C]; unsigned int x40; };
struct A { char pad[0x14]; struct Q *pq; };
struct S { char pad[0x4514]; DL dl; char pad2[0x4648 - 0x4520]; int c; int x3F18; int *pi; struct E *ae; };
void func_00137900(struct A *);
static inline void InitDli(DLI *pdli, DL *pdl)
{
    pdli->m_pdl = pdl;
    pdli->m_ppv = (void **)pdl;
    pdli->m_ibDle = pdl->ibDle;
    pdli->m_pdliNext = D_0036AE94;
    D_0036AE94 = pdli;
}
static inline void *PvNextDli(DLI *pdli)
{
    void *pv = *pdli->m_ppv;
    pdli->m_ppv = (void **)((char *)pv + pdli->m_ibDle);
    return pv;
}
static __inline__ unsigned int GrfQ(struct Q *pq) { unsigned int x = pq->x40; return ((x ^ 1) & 1) ? *(unsigned int *)x : x; }
void func_0027DA70(struct S *p)
{
    DLI dli;
    int i;
    struct A *pa;
    p->pi = &i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if ((pe->grf & 0x202) == 0x202) {
            struct O *po = pe->po;
            ((void (*)(void *))po->vt[18].pfn)((char *)po + po->vt[18].d);
        }
    }
    p->pi = 0;
    InitDli(&dli, &p->dl);
    while ((pa = PvNextDli(&dli)) != 0) {
        if (GrfQ(pa->pq) & 0x200)
            func_00137900(pa);
    }
    p->pi = &i;
    for (i = 0; i < p->c; i++) {
        struct E *pe = &p->ae[i];
        if ((pe->grf & 0x244) == 0x204) {
            struct O *po = pe->po;
            ((void (*)(void *))po->vt[19].pfn)((char *)po + po->vt[19].d);
        }
    }
    p->pi = 0;
    D_0036AE94 = dli.m_pdliNext;
}
