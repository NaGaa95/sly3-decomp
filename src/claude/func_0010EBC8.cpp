// Splice wrapper (Sly 2 pattern): descriptor IDs recovered from 0x0031EB80; bool callee.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(bool f);
    CRef &operator=(int n);
    CRef &operator=(float g);
    CRef &operator=(void *pv);
};
extern "C" CRef func_0024B2B8(int c, void *aref, int *ak, ...);
extern "C" { int func_001ED320(void *p, qword, int); CRef func_0010EBC8(void *p, int c, void *aref); }
CRef func_0010EBC8(void *p, int c, void *aref)
{
    int ak[2] = {0x2, 0x0};
    union { qword q; } v0;
    int v1;
    CRef ref = func_0024B2B8(2, aref, ak, &v0, &v1);
    ref = func_001ED320(p, v0.q, v1) != 0;
    return ref;
}
