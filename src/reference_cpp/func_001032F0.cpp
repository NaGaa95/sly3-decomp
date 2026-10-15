// Recovered using Sly 2 CRef wrappers; Sly 3 argument tags and call targets verified separately.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
    CRef &operator=(int n);
};
extern "C" {
CRef func_0024B2B8(int c, void *aref, int *ak, void *a0, void *a1);
int func_00273F68(void *p, int a, int b);
CRef func_001032F0(void *p, int c, void *aref);
}
CRef func_001032F0(void *p, int c, void *aref)
{
    int ak[2] = {0x2005, 0x2031};
    int a, b;
    CRef ref = func_0024B2B8(2, aref, ak, &a, &b);
    ref = func_00273F68(p, a, b);
    return ref;
}
