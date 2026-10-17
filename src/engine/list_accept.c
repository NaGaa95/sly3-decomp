// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
typedef struct DL { void *head; void *tail; int ibDle; } DL;
typedef struct DLI { DL *m_pdl; void **m_ppv; int m_ibDle; struct DLI *m_pdliNext; } DLI;
extern DLI *D_0036AE94;
extern DL D_00479B8C;
static __inline__ void ExitDli(DLI *pdli) { D_0036AE94=pdli->m_pdliNext; }
struct AcceptEntry { short delta,padding; char *(*fn)(void *); };
struct AcceptHolder { unsigned char prefix[0xC]; struct AcceptEntry *table; };
struct AcceptSelf { unsigned char prefix[0x10]; struct AcceptHolder *holder; };
struct AcceptNode { unsigned char prefix[0x120]; struct AcceptNode *next; };
int func_0027F258(void *node,Qword position);
int func_001612D0(struct AcceptSelf *self)
{
    Qword position=*(Qword *)(self->holder->table[36].fn((char *)self->holder+self->holder->table[36].delta)+0x30);
    DLI dli;
    struct AcceptNode *node;
    dli.m_pdl=&D_00479B8C;
    dli.m_ppv=(void **)&D_00479B8C;
    dli.m_ibDle=D_00479B8C.ibDle;
    dli.m_pdliNext=D_0036AE94;
    D_0036AE94=&dli;
    for(node=(struct AcceptNode *)D_00479B8C.head;node;node=node->next) {
        if(func_0027F258(node,position)) { ExitDli(&dli); return 1; }
    }
    ExitDli(&dli);
    return 0;
}
