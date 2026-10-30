// Splice wrapper (Sly 2 pattern): descriptor IDs recovered from 0x0031E8D8; void callee.
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
extern "C" { void func_001973B8(void *p, int, int, int, int, int); CRef func_001081B8(void *p, int c, void *aref); }
CRef func_001081B8(void *p, int c, void *aref)
{
    int ak[5] = {0x6, 0x0, 0x6, 0x6, 0x0};
    int v0;
    int v1;
    int v2;
    int v3;
    int v4;
    CRef ref = func_0024B2B8(5, aref, ak, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(0x22);
    func_001973B8(p, v0, v1, v2, v3, v4);
    return ref;
}
