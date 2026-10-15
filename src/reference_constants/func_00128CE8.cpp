// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CRef {
    short m_tagk;
    short padding;
    union {
        int n;
        float g;
        void *pv;
    }
    u;
    CRef() {
        m_tagk = -1;
    }
    CRef(int tagk) {
        InitTag(tagk);
    }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() {
        Decref();
    }
    CRef &operator=(const CRef &r);
};
struct NODE {
    CRef ref;
    int pad8;
    NODE *pnext;
};
struct P {
    char pad[4];
    struct {
        char pad[0xC];
        NODE *pargs;
    }
    *pv;
};
struct EvalFrame {
    int cref;
    int pad4;
    EvalFrame *parent;
    ~EvalFrame();
};
struct EvalFrameRef {
    EvalFrame *p;
    EvalFrameRef() {
        p = 0;
    }
    ~EvalFrameRef() {
        EvalFrame *pf = p;
        if (pf && --pf->cref == 0) delete pf;
    }
    void operator=(EvalFrame *pf);
};
extern "C" {
    EvalFrame *func_002BA9A8();
    CRef func_001296F0(NODE *p, EvalFrame *pframe);
    CRef func_001299C8(EvalFrame *pframe, int sym, CRef *pref);
    void func_002BAA50(EvalFrameRef *parent, EvalFrame *pframeParent);
    CRef func_00128CE8(P *p, EvalFrame *pframe);
}
CRef func_00128CE8(P *p, EvalFrame *pframe) {
    CRef ref;
    CRef refVal;
    CRef refT;
    EvalFrameRef spf;
    NODE *pargs = p->pv->pargs;
    NODE *pn;
    if (pargs->ref.m_tagk == 0x1D) {
        EvalFrame *pfNew = func_002BA9A8();
        spf = pfNew;
        for (pn = (NODE *)pargs->ref.u.pv; pn; pn = pn->pnext) {
            NODE *pb = (NODE *)pn->ref.u.pv;
            refVal = func_001296F0(pb->pnext, pframe);
            refT = func_001299C8(spf.p, pb->ref.u.n, &refVal);
        }
        func_002BAA50((EvalFrameRef *)&spf.p->parent, pframe);
    }
    else {
        spf = pframe;
    }
    NODE *pq;
    for (pq = pargs->pnext; pq; pq = pq->pnext) ref = func_001296F0(pq, spf.p);
    return ref;
}
