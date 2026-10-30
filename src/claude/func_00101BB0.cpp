// Splice wrapper (Sly 2 pattern): descriptor IDs recovered from 0x0031E690; void callee, returns the void tag.
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
extern "C" { void func_001313B8(void *p, int, int, int, float); CRef func_00101BB0(void *p, int c, void *aref); }
CRef func_00101BB0(void *p, int c, void *aref)
{
    int ak[4] = {0x14, 0x5, 0x5, 0x1};
    int v0;
    int v1;
    int v2;
    float v3;
    CRef ref = func_0024B2B8(4, aref, ak, &v0, &v1, &v2, &v3);
    ref.Decref();
    ref.InitTag(0x22);
    func_001313B8(p, v0, v1, v2, v3);
    return ref;
}
