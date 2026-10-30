// Splice wrapper (Sly 2 pattern): descriptor IDs recovered from 0x0031E870; void callee, returns the void tag.
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
};
extern "C" CRef func_0024B2B8(int c, void *aref, int *ak, ...);
extern "C" { void func_00189E60(void *p, int, int); CRef func_0010DFE8(void *p, int c, void *aref); }
CRef func_0010DFE8(void *p, int c, void *aref)
{
    int ak[2] = {0x6, 0x6};
    int a, b;
    CRef ref = func_0024B2B8(2, aref, ak, &a, &b);
    ref.Decref();
    ref.InitTag(0x22);
    func_00189E60(p, a, b);
    return ref;
}
