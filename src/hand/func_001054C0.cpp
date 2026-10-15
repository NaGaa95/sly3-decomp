// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(bool f);
};
extern "C" {
CRef func_0024B2B8(int c, void *aref, int *ak, void *a0);
int func_0027F258(void *p, qword q);
CRef func_001054C0(void *p, int c, void *aref);
}
extern "C" CRef func_001054C0(void *p, int c, void *aref)
{
    int ak[1] = {2};
    union { qword q; } u;
    CRef ref = func_0024B2B8(1, aref, ak, &u);
    ref = func_0027F258(p, u.q) != 0;
    return ref;
}
