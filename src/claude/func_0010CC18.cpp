// Splice wrapper (Sly 2 pattern): one CRef argument (descriptor 0x8010); void callee, returns the void tag.
struct CRef {
    short m_tagk; short m_pad; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
};
extern "C" CRef func_0024B2B8(int c, void *aref, int *ak, ...);
extern "C" { void func_00260D78(void *p, CRef *pref); CRef func_0010CC18(void *p, int c, void *aref); }
CRef func_0010CC18(void *p, int c, void *aref)
{
    int ak[1] = {0x8010};
    CRef v0;
    CRef ref = func_0024B2B8(1, aref, ak, &v0);
    ref.Decref();
    ref.InitTag(0x22);
    func_00260D78(p, &v0);
    return ref;
}
