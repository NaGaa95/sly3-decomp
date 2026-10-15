// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(bool f);
};
extern "C" {
CRef func_0024B2B8(int c, void *aref, int *ak, void *a0, void *a1);
int func_0027F390(void *p, qword q, float g);
CRef func_00105548(void *p, int c, void *aref);
}
extern "C" CRef func_00105548(void *p, int c, void *aref)
{
    // Sly 3 descriptor IDs recovered from 0x0031E720.
    int ak[2] = {0x2, 0x1};
    union { qword q; } u;
    float g;
    CRef ref = func_0024B2B8(2, aref, ak, &u, &g);
    ref = func_0027F390(p, u.q, g) != 0;
    return ref;
}
