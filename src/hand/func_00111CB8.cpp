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
    CRef &operator=(void *pv) __asm__("func_0012B270");
    CRef &operator=(qword q);
    CRef &operator=(bool f);
    CRef &operator=(int n);
    CRef &operator=(float g);
};
extern "C" CRef func_0024B2B8(int c, void *aref, int *ak, ...);
extern "C" { void *func_001A04E0(void *p, int a, int b, int c); CRef func_00111CB8(void *p, int c, void *aref); }
CRef func_00111CB8(void *p, int c, void *aref)
{
    // Sly 3 descriptor IDs recovered from 0x0031ECA8.
    int ak[3] = {0x5, 0x108B, 0x0};
    int a, b, d;
    CRef ref = func_0024B2B8(3, aref, ak, &a, &b, &d);
    ref = func_001A04E0(p, a, b, d);
    return ref;
}
