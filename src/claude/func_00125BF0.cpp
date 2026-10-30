// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Script builtin (Sly 2 func_00123BD8 evolved): builds the list (obj [ (0x10 . item) ... ]) and schedules it at
// g_clock.t + aref[0]; returns the handle id as an int CRef (Sly 3 int tag 0x13, CRef with short tag/refcount).
struct NODE;
struct OBJ;
struct AOBJ;
struct CRef {
    short m_tagk; short m_cref; union { int n; float g; void *pv; NODE *pnode; } u;
    CRef() { m_tagk = -1; }
    CRef(int n, int tagk) { m_tagk = tagk; u.n = n; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(int n);
    CRef &operator=(NODE *p) __asm__("func_0012B6C8");
    CRef &operator=(AOBJ *p) __asm__("func_0012B718");
    CRef &operator=(OBJ *p) __asm__("func_0012B7C8");
    void SetTag(int tagk) { Decref(); InitTag(tagk); }
};
struct G;
extern G D_00475480;
extern struct CLOCK { float t; float dt; } g_clock;
struct R { char pad[0xC]; int n; };
extern "C" {
NODE *func_002BA6B8();
void func_002BA840(NODE *, int);
CRef func_0012BAE8(CRef *pref);
R *func_0013B9E0(G *pg, int n, NODE *pnode, float t);
}
struct SPM {
    NODE *p;
    void operator=(NODE *pn) __asm__("func_002BA780");
};
struct NODE {
    CRef ref;
    int x8;
    SPM pnext;
    void SetNext(NODE *pn) { pnext = pn; }
};
struct SPN {
    NODE *p;
    void Set(NODE *pn) __asm__("func_002BA760");
    ~SPN() { NODE *pn = p; if (pn && --pn->ref.m_cref == 0) func_002BA840(pn, 3); }
    NODE *operator->() { return p; }
};
extern "C" CRef func_00125BF0(int c, CRef *aref);
CRef func_00125BF0(int c, CRef *aref)
{
    CRef res(-1, 0x13);
    SPN sp;
    NODE *pnNew = func_002BA6B8();
    sp.Set(pnNew);
    sp->ref = func_002BA6B8();
    NODE *pn = sp->ref.u.pnode;
    if (aref[1].m_tagk == 0x1E)
        pn->ref = (AOBJ *)aref[1].u.pv;
    else
        pn->ref = (OBJ *)aref[1].u.pv;
    if (c >= 3) {
        NODE *pnT = pn;
        for (NODE *pw = aref[2].u.pnode; pw; pw = pw->pnext.p) {
            pnT->SetNext(func_002BA6B8());
            pnT = pnT->pnext.p;
            CRef *pref = &pnT->ref;
            *pref = func_002BA6B8();
            NODE *pc = pref->u.pnode;
            pc->ref.SetTag(0x10);
            pc->SetNext(func_002BA6B8());
            pc->pnext.p->ref = pw->ref;
        }
    }
    G *pg = &D_00475480;
    float t = g_clock.t;
    R *pr = func_0013B9E0(pg, 0, sp.p, t + func_0012BAE8(aref).u.g);
    res = pr->n;
    return res;
}
