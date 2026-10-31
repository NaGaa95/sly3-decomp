// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00129208 (agent A20b): script call evaluation (Sly 2 func_001272E0 port, from the laneB6 Sly 2 match):
// Sly 3 CRef (short tag/refcount, tags 2 lower: bif 0x17, lambda 0x1E, method 0x20, param 0x12), NODE pnext at
// +0xC, node delete func_002BA840(pn, 3), METHOD gains a field (pv 0xC, pfn 0x10, cargMin 0x14), FRAME init
// func_002BAA50 on frame+8, SPF::Set func_002BAB88, frame delete func_002BABA8(pf, 3).
// As in the Sly 2 match, `int dummy[2]` after spf reproduces the lambda-case frame layout.
struct NODE;
struct CRef {
    short m_tagk; short m_cref; union { int n; float g; void *pv; NODE *pnode; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    void SetNil() { Decref(); InitTag(0); }
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(NODE *pn) __asm__("func_0012B6C8");
};
extern "C" {
NODE *func_002BA6B8();
void func_002BA840(NODE *, int);
}
struct SPM {
    NODE *p;
    void operator=(NODE *pn) __asm__("func_002BA780");
};
struct NODE {
    CRef ref;
    int x8;
    SPM pnext;
};
struct SPN {
    NODE *p;
    void Set(NODE *pn) __asm__("func_002BA760");
    SPN() { p = 0; }
    SPN(NODE *pn) { Set(pn); }
    ~SPN() { NODE *pn = p; if (pn && --pn->ref.m_cref == 0) func_002BA840(pn, 3); }
    void Assign(NODE *pn) __asm__("func_002BA780");
    SPN &operator=(NODE *pn) { Assign(pn); return *this; }
    NODE *operator->() { return p; }
    int pad;
};
struct FRAME;
extern "C" void func_002BABA8(FRAME *, int);
struct FRAMEX { void Init(FRAME *pframeParent) __asm__("func_002BAA50"); };
struct FRAME {
    int cref;
    int x4;
    FRAMEX x8;
};
struct SPF {
    FRAME *p;
    int pad;
    void Set(FRAME *pf) __asm__("func_002BAB88");
    SPF(FRAME *pf) { Set(pf); }
    ~SPF() { FRAME *pf = p; if (pf && --pf->cref == 0) func_002BABA8(pf, 3); }
};
struct BIF {
    CRef (*pfn)(int c, CRef *aref, FRAME *pframe);
    int cargMin;
    int fRest;
};
struct METHOD {
    int x0, x4, x8;
    void *pv;
    CRef (*pfn)(void *pv, int c, CRef *aref);
    int cargMin;
};
struct LAMBDA {
    int x0, x4;
    FRAME *pframe;
    int cargMin;
    int fRest;
    NODE *pparams;
    NODE *pbody;
};
extern BIF D_00342030[];
extern "C" {
FRAME *func_002BA9A8();
CRef func_001296F0(NODE *p, FRAME *pframe);
CRef func_001299C8(FRAME *pframe, int sym, CRef *pref);
CRef func_001290B0(LAMBDA *plambda, FRAME *pframe);
CRef func_00129208(NODE *p, FRAME *pframe);
}

CRef func_00129208(NODE *p, FRAME *pframe)
{
    CRef ref;
    BIF *pbif = 0;
    LAMBDA *plambda = 0;
    METHOD *pmeth = 0;
    NODE *pnFn = p->ref.u.pnode;
    CRef refOp = func_001296F0(pnFn, pframe);
    int cargMin, fRest;
    if (refOp.m_tagk == 0x17) {
        pbif = &D_00342030[refOp.u.n];
        cargMin = pbif->cargMin;
        fRest = pbif->fRest;
    } else if (refOp.m_tagk == 0x20) {
        pmeth = (METHOD *)refOp.u.pv;
        fRest = 0;
        cargMin = pmeth->cargMin;
    } else {
        plambda = (LAMBDA *)refOp.u.pv;
        cargMin = plambda->cargMin;
        fRest = plambda->fRest;
    }
    int carg = cargMin + (fRest != 0);
    CRef aref[32];
    NODE *pn = pnFn->pnext.p;
    int c = cargMin;
    int i;
    for (i = 0; i < c; i++) {
        ref = func_001296F0(pn, pframe);
        aref[i] = ref;
        pn = pn->pnext.p;
    }
    if (fRest) {
        SPN spCur(pn);
        SPN spLast;
        SPN spList;
        while (spCur.p) {
            SPN spNew(func_002BA6B8());
            spNew->ref = func_001296F0(spCur.p, pframe);
            if (spLast.p) {
                spLast->pnext = spNew.p;
                spLast = spNew.p;
            } else {
                spLast = spNew.p;
                spList = spLast.p;
            }
            c++;
            spCur = spCur->pnext.p;
        }
        if (spList.p) {
            aref[i] = spList.p;
        } else {
            aref[i].SetNil();
        }
    }
    switch (refOp.m_tagk) {
    case 0x17:
        ref = pbif->pfn(c, aref, pframe);
        break;
    case 0x1E: {
        SPF spf(func_002BA9A8());
        int dummy[2];
        spf.p->x8.Init(plambda->pframe);
        NODE *pparam = plambda->pparams;
        for (i = 0; i < carg; i++) {
            if (pparam->ref.m_tagk == 0x12)
                pparam = pparam->pnext.p;
            CRef r = func_001299C8(spf.p, pparam->ref.u.n, &aref[i]);
            pparam = pparam->pnext.p;
        }
        ref = func_001290B0(plambda, spf.p);
        break;
    }
    case 0x20:
        ref = pmeth->pfn(pmeth->pv, c, aref);
        break;
    }
    return ref;
}
