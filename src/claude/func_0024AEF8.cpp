// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0024AEF8 (agents A71/A73): build a list of c option values (cf. Sly 2 src/hand/func_00200F58.cpp; Sly 3 CRef/NODE helpers).
// 'list = 0' goes through an inline Clear(SPN &) so &list is rematerialised (addiu) instead of CSE'd into an s-reg.
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
void *func_00292034(void *, int, int);
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
    SPN() { p = 0; }
    SPN(NODE *pn) { Set(pn); }
    void Set(NODE *pn) __asm__("func_002BA760");
    ~SPN() { NODE *pn = p; if (pn && --pn->ref.m_cref == 0) func_002BA840(pn, 3); }
    void operator=(NODE *pn) __asm__("func_002BA780");
    int pad[3];
};
struct PRM { int a; int k; int rest[8]; };
extern "C" CRef func_00249D98(void *pb, PRM *prm);
extern "C" CRef func_0024AEF8(int c, int x, void *pb);
static inline void Clear(SPN &l) { l = 0; }
CRef func_0024AEF8(int c, int x, void *pb)
{
    if (c == 0)
        return CRef(0);
    PRM prm;
    SPN list;
    func_00292034(&prm, 0, sizeof(prm));
    prm.a = x;
    prm.k = 2;
    Clear(list);
    SPM *ppTail = (SPM *)&list;
    for (int i = 0; i < c; i++) {
        prm.rest[0] = i * 4;
        SPN nw(func_002BA6B8());
        CRef *pr = &nw.p->ref;
        *pr = func_00249D98(pb, &prm);
        *ppTail = nw.p;
        ppTail = &nw.p->pnext;
    }
    return CRef(list.p);
}
