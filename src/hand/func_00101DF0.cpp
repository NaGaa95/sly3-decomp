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
extern "C" { void * func_00137568(void *p, int, int, float, float, int); CRef func_00101DF0(void *p, int c, void *aref); }
CRef func_00101DF0(void *p, int c, void *aref)
{
    // Sly 3 descriptor IDs recovered from 0x0031E6C0.
    int ak[5] = {0x202F, 0x100C, 0x1, 0x1, 0x100B};
    int v0;
    int v1;
    float v2;
    float v3;
    int v4;
    CRef ref = func_0024B2B8(5, aref, ak, &v0, &v1, &v2, &v3, &v4);
    ref = func_00137568(p, v0, v1, v2, v3, v4);
    return ref;
}
