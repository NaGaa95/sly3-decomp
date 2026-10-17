// SLY3_CFLAGS: -Os -G0
typedef struct DL { void *head; void *tail; int ibDle; } DL;
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *D_0036AE94;
struct EnginePendingGame { unsigned char prefix[0x3E50]; DL pending; };
void func_0015B780(struct EnginePendingGame *game);
void func_0015B580(struct EnginePendingGame *game,void *node);
static __inline__ void InitDli(DLI *pdli,DL *pdl)
{
    pdli->m_pdl=pdl;
    pdli->m_ppv=(void **)pdl;
    pdli->m_ibDle=pdl->ibDle;
    pdli->m_pdliNext=D_0036AE94;
    D_0036AE94=pdli;
}
static __inline__ void *PvNextDli(DLI *pdli)
{
    void *pv=*pdli->m_ppv;
    pdli->m_ppv=(void **)((char *)pv+pdli->m_ibDle);
    return pv;
}
void func_0015B790(struct EnginePendingGame *game)
{
    DLI dli;
    void *node;
    func_0015B780(game);
    InitDli(&dli,&game->pending);
    while((node=PvNextDli(&dli))!=0) func_0015B580(game,node);
    D_0036AE94=dli.m_pdliNext;
}
