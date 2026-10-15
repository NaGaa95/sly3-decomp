// Sly 2 reference: src/hand/func_0012AB78.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct BINDING;
extern char D_004520D0[];
extern char D_00452148[];
extern "C" {
void func_0011CD98(void *pheap, void *pv);
void func_00255438(void *pv);
void func_00255DE8(void *pv);
}
struct CRef { int m_tagk; int m_tag; void Decref(); ~CRef() { Decref(); } };
struct SPM {
    BINDING *p;
    ~SPM();
};
struct BINDING {
    ~BINDING();
    int cref;
    int x4;
    int sym;
    CRef ref;
    SPM pnext;
    void operator delete(void *pv) { func_00255438(pv); func_0011CD98(D_004520D0, pv); }
};
struct SPB {
    BINDING *p;
    SPB() {}
    SPB(const SPB &);
    ~SPB() { BINDING *pb = p; if (pb && --pb->cref == 0) delete pb; }
    void operator=(BINDING *pb) __asm__("func_002BAED0");
};
struct SB {
    ~SB();
    int cref;
    int x4;
    SPB pbinding;
    void SetBinding(BINDING *pb) { pbinding = pb; }
    void operator delete(void *pv) { func_00255DE8(pv); func_0011CD98(D_00452148, pv); }
};
struct SPS {
    SB *p;
    void Set(SB *psb) __asm__("func_002BB898");
    SPS() {}
    SPS(SB *psb) { Set(psb); }
    SPS(const SPS &);
    ~SPS() { SB *psb = p; if (psb && --psb->cref == 0) delete psb; }
    SB *operator->() { return p; }
};
extern "C" {
SB *func_002BB7F0() __asm__("func_002BB7F0");
SPB func_0012CD10(BINDING *pb, void *p, void *q) __asm__("func_0012CD10");
SPS func_0012C820(SB *psbSrc, void *q) __asm__("func_0012C820");
}
SPS func_0012C820(SB *psbSrc, void *q)
{
    SPS sp;
    sp.Set(func_002BB7F0());
    if (psbSrc->pbinding.p)
        sp->SetBinding(func_0012CD10(psbSrc->pbinding.p, 0, q).p);
    return SPS(sp.p);
}
