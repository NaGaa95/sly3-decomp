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
extern "C" { void * func_001ED290(void *p, qword, int); CRef func_0010EB28(void *p, int c, void *aref); }
CRef func_0010EB28(void *p, int c, void *aref)
{
    // Sly 3 descriptor IDs recovered from 0x0031EB80.
    int ak[2] = {0x2, 0x0};
    union { qword q; } v0;
    int v1;
    CRef ref = func_0024B2B8(2, aref, ak, &v0, &v1);
    ref = func_001ED290(p, v0.q, v1);
    return ref;
}
