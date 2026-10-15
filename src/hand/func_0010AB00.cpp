// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(int tagk) { InitTag(tagk); }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(void *pv);
    CRef &operator=(qword q);
    CRef &operator=(bool f);
    CRef &operator=(int n);
    CRef &operator=(float g);
};
extern "C" CRef func_0024B2B8(int c, void *aref, int *ak, ...);
extern "C" { void *func_00173E00(void *p, int a, qword q, int b); CRef func_0010AB00(void *p, int c, void *aref); }
CRef func_0010AB00(void *p, int c, void *aref)
{
    // Sly 3 descriptor IDs recovered from 0x0031E9A8.
    int ak[3] = {0x103D, 0x2, 0x2002};
    union { qword q; } u;
    int a, b;
    CRef ref = func_0024B2B8(3, aref, ak, &a, &u, &b);
    ref = func_00173E00(p, a, u.q, b);
    return ref;
}
