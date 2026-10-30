// Splice wrapper (Sly 2 pattern): descriptor IDs recovered from 0x0031EC68; void callee, returns the void tag.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
};
extern "C" CRef func_0024B2B8(int c, void *aref, int *ak, ...);
extern "C" { void func_00219448(void *p, int, int, float, int); CRef func_00111488(void *p, int c, void *aref); }
CRef func_00111488(void *p, int c, void *aref)
{
    int ak[4] = {0x6, 0x6, 0x1, 0x100d};
    int v0;
    int v1;
    float v2;
    int v3;
    CRef ref = func_0024B2B8(4, aref, ak, &v0, &v1, &v2, &v3);
    ref.Decref();
    ref.InitTag(0x22);
    func_00219448(p, v0, v1, v2, v3);
    return ref;
}
