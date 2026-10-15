// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CRef {
    short m_tagk;
    short padding;
    union {
        int n;
        float g;
        void *pv;
    } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
typedef char CheckReferenceSize[(sizeof(CRef) == 8) ? 1 : -1];
struct EvalFrame;
struct NODE {
    CRef ref;
    int padding8;
    NODE *pnext;
};
struct P {
    char pad[4];
    struct {
        char pad[0xC];
        NODE *pargs;
    } *pv;
};
typedef char CheckNodeSize[(sizeof(NODE) == 16) ? 1 : -1];
extern "C" {
CRef func_001296F0(NODE *p, EvalFrame *penv);
CRef func_001221B8(int carg, CRef *aref, EvalFrame *penv);
CRef func_00128AD0(P *p, EvalFrame *penv);
}
CRef func_00128AD0(P *p, EvalFrame *penv)
{
    CRef ref;
    CRef arefT[2];
    CRef test;
    NODE *pkey;
    NODE *pcl;
    ref.Decref();
    ref.InitTag(0x22);
    pkey = p->pv->pargs;
    arefT[0] = func_001296F0(pkey, penv);
    pcl = pkey->pnext;
    while (pcl) {
        NODE *pc = (NODE *)pcl->ref.u.pv;
        int f;
        if (pc->ref.m_tagk == 0xA) {
            f = 1;
        } else {
            NODE *pk;
            f = 0;
            pk = (NODE *)pc->ref.u.pv;
            while (pk) {
                arefT[1] = pk->ref;
                test = func_001221B8(2, arefT, penv);
                if (test.m_tagk == 0x15 && test.u.n) {
                    f = 1;
                    pk = 0;
                } else {
                    pk = pk->pnext;
                }
            }
        }
        if (f) {
            for (pc = pc->pnext; pc; pc = pc->pnext)
                ref = func_001296F0(pc, penv);
            pcl = 0;
        } else {
            pcl = pcl->pnext;
        }
    }
    return ref;
}
