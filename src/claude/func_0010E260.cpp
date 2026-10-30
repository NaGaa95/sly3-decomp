// Splice wrapper (Sly 2 pattern): descriptor IDs recovered from 0x0031EAF0; void callee.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    short m_tagk; short m_pad; union { int n; float g; void *pv; } u;
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
extern "C" { void func_00188118(void *p, int, CRef *, int, int, int); CRef func_0010E260(void *p, int c, void *aref); }
CRef func_0010E260(void *p, int c, void *aref)
{
    int ak[5] = {0x6, 0x9047, 0x6, 0xf, 0x0};
    int v0;
    CRef v1;
    int v2;
    int v3;
    int v4;
    CRef ref = func_0024B2B8(5, aref, ak, &v0, &v1, &v2, &v3, &v4);
    ref.Decref();
    ref.InitTag(0x22);
    func_00188118(p, v0, &v1, v2, v3, v4);
    return ref;
}
