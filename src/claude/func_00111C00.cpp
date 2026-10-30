// Splice wrapper (Sly 2 pattern): descriptor IDs recovered from 0x0031EC98; void callee, returns the void tag.
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
extern "C" { void func_001A0480(void *p, int, int, int); CRef func_00111C00(void *p, int c, void *aref); }
CRef func_00111C00(void *p, int c, void *aref)
{
    int ak[3] = {0x5, 0x108b, 0x5};
    int v0;
    int v1;
    int v2;
    CRef ref = func_0024B2B8(3, aref, ak, &v0, &v1, &v2);
    ref.Decref();
    ref.InitTag(0x22);
    func_001A0480(p, v0, v1, v2);
    return ref;
}
