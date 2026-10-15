// Traverse timed resources with a registered mutation-safe iterator; retain and release each expired object around its virtual callback, then advance the group state.
// Reference algorithm: src/hand/FUN_0019e420.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef struct DL { void *head; void *tail; int ibDle; } DL;
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *D_0036AE94;
struct CLOCK { float t, dt; };
extern struct CLOCK D_0036BB98;
struct VTE { short d; short pad; void (*pf)(); };
struct RIP { char pad[0x14]; float tStart; char p1[0xE8 - 0x18]; struct VTE *vt; };
struct RIPG { char pad[0xC]; struct VTE *vt; char p1[0x134 - 0x10]; DL dl; };
void func_0020BDB0(struct RIP *prip);
void func_0020BDC0(struct RIP *prip);
int func_001C8610(struct RIPG *p);
int func_0011B0F0(DL *pdl);
void func_0020B578(struct RIPG *p);
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
void func_0020B468(struct RIPG *pripg)
{
    DLI dli;
    struct RIP *prip;
    InitDli(&dli, &pripg->dl);
    while ((prip = (struct RIP *)PvNextDli(&dli)) != 0) {
        if (D_0036BB98.t <= prip->tStart) continue;
        func_0020BDB0(prip);
        ((void (*)(void *))prip->vt[4].pf)((char *)prip + prip->vt[4].d);
        func_0020BDC0(prip);
    }
    if (!func_001C8610(pripg) || func_0011B0F0(&pripg->dl))
        ((void (*)(void *))pripg->vt[9].pf)((char *)pripg + pripg->vt[9].d);
    else
        func_0020B578(pripg);
    D_0036AE94 = dli.m_pdliNext;
}
