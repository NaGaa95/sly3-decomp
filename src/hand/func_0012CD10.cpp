// Sly 2 reference: src/hand/func_0012B0E8.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref() __asm__("func_0012BC20");
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r) __asm__("func_0012B3B0");
};
struct W;
extern char D_004520D0[];
extern "C" {
void func_0011CD98(void *pheap, void *pv);
void func_00255438(void *pv);
W *func_002BAE00() __asm__("func_002BAE00");
CRef func_0012B928(CRef *pref, void *a, void *b) __asm__("func_0012B928");
}
struct SPM {
    W *p;
    ~SPM();
    SPM &operator=(W *pw) __asm__("func_002BAED0");
};
struct W {
    ~W();
    int cref;
    int x4;
    int x8;
    CRef ref;
    SPM pnext;
    void SetNext(W *pw) { pnext = pw; }
    void operator delete(void *pv) { func_00255438(pv); func_0011CD98(D_004520D0, pv); }
};
struct SPW {
    W *p;
    void Set(W *pw) __asm__("func_002BAEB0");
    SPW() {}
    SPW(W *pw) { Set(pw); }
    SPW(const SPW &);
    ~SPW() { W *pw = p; if (pw && --pw->cref == 0) delete pw; }
    W *operator->() { return p; }
};
extern "C" SPW func_0012CD10(W *src, void *a, void *b) __asm__("func_0012CD10");
SPW func_0012CD10(W *src, void *a, void *b)
{
    SPW sp;
    sp.Set(func_002BAE00());
    sp->x8 = src->x8;
    sp->ref = func_0012B928(&src->ref, a, b);
    if (src->pnext.p)
        sp->SetNext(func_0012CD10(src->pnext.p, a, b).p);
    return SPW(sp.p);
}
