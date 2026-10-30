// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the matched Sly 2 source src/hand/func_001248B0.cpp (Sly 3: short tag, int tag 0x13, CTX helper).
typedef int qword __attribute__((mode(TI)));
struct CRef {
    short m_tagk; short m_pad; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(float g);
};
struct CTX { int a[4]; CTX(); ~CTX(); };
extern char D_00475480[];
extern "C" {
void func_0025D0D8(void *pg, qword a, void *p3, void *p4, float g, int *pc, void **pap);
void func_0025D240(int c, void *ap, int *pc, void **pap);
CRef func_00126060(int c, void *ap);
CRef func_001268E0(void *pbasic, CRef *aref);
}
CRef func_001268E0(void *pbasic, CRef *aref)
{
    CRef ref;
    float g;
    if (aref[1].m_tagk == 0x13)
        g = (float)aref[1].u.n;
    else
        g = aref[1].u.g;
    CTX obj;
    int c0;
    void *ap0;
    int c1;
    void *ap1;
    func_0025D0D8(D_00475480, *(qword *)aref[0].u.pv, 0, 0, g, &c0, &ap0);
    func_0025D240(c0, ap0, &c1, &ap1);
    ref = func_00126060(c1, ap1);
    return ref;
}
