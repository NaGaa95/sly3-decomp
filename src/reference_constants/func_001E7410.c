// Reference algorithm: src/hand/func_001BD218.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
typedef struct DL { void *head; void *tail; int ibDle; } DL;
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *D_0036AE94;
struct VE { short d; short pad; void (*pfn)(); };
struct S { char pad[0xC]; struct VE *vt; char pad1[0x1B4 - 0x10]; DL dl; char pad2[0x1D8 - 0x1D0]; int x1D8; };
extern char D_0047A26C[], D_0047A260[];
void func_0011B028(DL *pdl, struct S *pv);
int func_0011B0C0(void *pdl, struct S *pv);
void func_0011AF60(void *pdl, struct S *pv);
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
void func_001E7410(struct S *p)
{
    DLI dli;
    struct S *pv;
    InitDli(&dli, &p->dl);
    while ((pv = PvNextDli(&dli)) != 0) {
        func_0011B028(&p->dl, pv);
        pv->x1D8 = 0;
        if (!func_0011B0C0(D_0047A26C, pv)) func_0011AF60(D_0047A26C, pv);
    }
    ((void (*)(void *))p->vt[9].pfn)((char *)p + p->vt[9].d);
    func_0011AF60(D_0047A260, p);
    D_0036AE94 = dli.m_pdliNext;
}
