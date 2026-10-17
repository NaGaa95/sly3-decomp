// SLY3_CFLAGS: -Os -G0
typedef struct DL {
    void *head;
    void *tail;
    int ibDle;
} DL;
typedef struct DLI {
    DL *m_pdl;
    void **m_ppv;
    int m_ibDle;
    struct DLI *m_pdliNext;
} DLI;
extern DLI *D_0036AE94;
struct VTE {
    short d;
    short pad;
    void (*pf)();
};
struct Item {
    unsigned char prefix[0xE8];
    struct VTE *vt;
};
struct Owner {
    unsigned char prefix[0x50];
    DL dl;
};
void func_001FF098(void *);
void func_002BEA80(void *, int);
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
void func_002028B8(struct Owner *owner)
{
    DLI dli;
    struct Item *item;
    func_001FF098(owner);
    InitDli(&dli, &owner->dl);
    while ((item = (struct Item *)PvNextDli(&dli)) != 0)
        ((void (*)(void *))item->vt[6].pf)((char *)item + item->vt[6].d);
    if (owner)
        func_002BEA80(owner, 3);
    D_0036AE94 = dli.m_pdliNext;
}
