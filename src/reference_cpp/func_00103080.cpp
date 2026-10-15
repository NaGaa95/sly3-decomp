// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(qword q);
};
extern "C" {
CRef func_0024B2B8(int c, void *aref, int *ak, void *an);
qword func_001678C8(void *p, qword q);
CRef func_00103080(void *p, int c, void *aref);
}
CRef func_00103080(void *p, int c, void *aref)
{
    union { qword q; } u;
    int k = 2;
    CRef ref = func_0024B2B8(1, aref, &k, &u);
    ref = func_001678C8(p, u.q);
    return ref;
}
