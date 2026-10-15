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
extern "C" { void * func_00137428(void *p, int, float, float, int); CRef func_00101C78(void *p, int c, void *aref); }
CRef func_00101C78(void *p, int c, void *aref)
{
    // Sly 3 descriptor IDs recovered from 0x0031E6A0.
    int ak[4] = {0x202F, 0x1, 0x1, 0x100B};
    int v0;
    float v1;
    float v2;
    int v3;
    CRef ref = func_0024B2B8(4, aref, ak, &v0, &v1, &v2, &v3);
    ref = func_00137428(p, v0, v1, v2, v3);
    return ref;
}
