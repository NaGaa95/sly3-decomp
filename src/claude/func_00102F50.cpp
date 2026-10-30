// Splice wrapper (Sly 2 pattern): descriptor IDs recovered from 0x0031E720 (vector, float); bool-returning callee.
typedef int qword __attribute__((mode(TI)));
struct CRef {
    int m_tagk; union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(bool f);
};
union U { qword q; int n; };
extern "C" CRef func_0024B2B8(int c, void *aref, int *ak, ...);
extern "C" { int func_00167F60(void *p, qword v, qword g); CRef func_00102F50(void *p, int c, void *aref); }
CRef func_00102F50(void *p, int c, void *aref)
{
    int ak[2] = {0x2, 0x1};
    union { qword q; } v0;
    int v1;
    CRef ref = func_0024B2B8(2, aref, ak, &v0, &v1);
    qword q;
    __asm__("" : "=r"(q) : "0"(v1) : "$4"); /* empty asm: float bits to a qword argument; the "$4" clobber (a0 is not live here) is scheduling-only, putting the p argument copy after it as in the target */
    U u;
    u.q = q;
    ref = func_00167F60(p, v0.q, u.q) != 0;
    return ref;
}
