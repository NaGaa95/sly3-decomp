// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(void *pv);
};
extern "C" {
CRef func_0024B2B8(int c, void *aref, int *ak, void *an);
void *func_0022F2E0(void *p, qword q);
CRef func_0010D5D8(void *p, int c, void *aref);
}
extern "C" CRef func_0010D5D8(void *p, int c, void *aref)
{
    union { qword q; } u;
    int k = 2;
    CRef ref = func_0024B2B8(1, aref, &k, &u);
    ref = func_0022F2E0(p, u.q);
    return ref;
}
