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
struct ScheduleNode {
    void *source;
    void *other;
};
struct ScheduleOwner {
    unsigned char prefix[0x494C];
    unsigned char pool[0x18];
    DL list;
};
void func_0011B028(void *list, void *node);
void func_0011E1F0(void *pool, void *node);
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
void func_0025DEF8(struct ScheduleOwner *owner, void *source)
{
    DLI dli;
    struct ScheduleNode *node;
    InitDli(&dli, &owner->list);
    while ((node = (struct ScheduleNode *)PvNextDli(&dli)) != 0) {
        if (node->other == source) {
            func_0011B028(&owner->list, node);
            func_0011E1F0(owner->pool, node);
        }
    }
    D_0036AE94 = dli.m_pdliNext;
}
