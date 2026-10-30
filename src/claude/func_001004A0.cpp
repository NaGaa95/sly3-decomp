// Splice wrapper (Sly 2 pattern): descriptor IDs recovered from 0x0031E608; void callee, returns the void tag.
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
extern "C" { void func_0013B690(void *p, int, void *); CRef func_001004A0(void *p, int c, void *aref); }
CRef func_001004A0(void *p, int c, void *aref)
{
    int ak[2] = {0x15, 0x9};
    int v0;
    union { qword q; } v1;
    CRef ref = func_0024B2B8(2, aref, ak, &v0, &v1);
    ref.Decref();
    ref.InitTag(0x22);
    func_0013B690(p, v0, &v1);
    return ref;
}
