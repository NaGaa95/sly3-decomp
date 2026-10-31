// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 port (A16) of the matched Sly 2 func_00120FB0 (list shuffle builtin): Sly 3 CRef/NODE layout, list tag 0x1D.
struct NODE;
struct CRef {
    short m_tagk; short m_cref; union { int n; float g; void *pv; NODE *pnode; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    CRef(NODE *p) __asm__("func_0012B1D8");
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
extern "C" {
NODE *func_002BA6B8();
void func_002BA840(NODE *, int);
extern "C" int func_0011E8F0(int nLo, int nHi);
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
    ~SPN() { NODE *pn = p; if (pn && --pn->ref.m_cref == 0) func_002BA840(pn, 3); }
    void operator=(NODE *pn) __asm__("func_002BA780");
    NODE *operator->() { return p; }
    int pad[3];
};
extern "C" CRef func_00122BD0(void *pbasic, CRef *aref);
static inline void SetSpn(SPN *psp, NODE *pn) { *psp = pn; }
static inline void InsertAfter(SPM *psp, SPN &sp) { sp->pnext = psp->p; *psp = sp.p; }
CRef func_00122BD0(void *pbasic, CRef *aref)
{
    if (aref[0].m_tagk == 0) return CRef(0);
    if (aref[0].m_tagk != 0x1D) return CRef(0);
    CRef *apref[128];
    int c = 0;
    int iNil = -1;
    SPN spRes;
    NODE *pn;
    for (pn = aref[0].u.pnode; pn; pn = pn->pnext.p) {
        if (pn->ref.m_tagk == 0) iNil = c;
        else apref[c++] = &pn->ref;
    }
    int fShuffle = c >= 2 && iNil < 1;
    if (fShuffle) {
        CRef *prefFirst = apref[0];
        int i;
        for (i = 0; i < c; i++) {
            int j = func_0011E8F0(0, c - 1);
            CRef *pref = apref[j];
            apref[j] = apref[i];
            apref[i] = pref;
        }
        if (apref[0] == prefFirst) {
            apref[0] = apref[c - 1];
            apref[c - 1] = prefFirst;
        }
        iNil = c;
    }
    spRes.p = 0;
    NODE *pnLast = 0;
    SPM *psp = (SPM *)&spRes;
    int i;
    for (i = 0; i < c; i++) {
        *psp = func_002BA6B8();
        NODE *pnNew = psp->p;
        pnNew->ref = *apref[i];
        psp = &pnNew->pnext;
        if (i == iNil - 1) pnLast = pnNew;
    }
    if (pnLast && pnLast != spRes.p) {
        if (!fShuffle) {
            SPN sp;
            sp.Set(spRes.p);
            SetSpn(&spRes, spRes->pnext.p);
            InsertAfter(&pnLast->pnext, sp);
        }
        if (spRes.p != pnLast) {
            SPN sp;
            NODE *pnNew = func_002BA6B8();
            sp.Set(pnNew);
            sp->ref = CRef(0);
            InsertAfter(&pnLast->pnext, sp);
        }
    }
    return CRef(spRes.p);
}
