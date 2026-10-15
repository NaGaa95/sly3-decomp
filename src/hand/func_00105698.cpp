#include "activation_retained_api.h"
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
extern "C" CRef func_00105698(void *p, int c, void *aref);
CRef func_00105698(void *p, int c, void *aref)
{
    // Sly 3 descriptor IDs recovered from 0x0031E800.
    int ak[4] = {0x202F, 0x6, 0x100B, 0x104D};
    void *receiver;
    int v1;
    int v2;
    int v3;
    CRef ref = func_0024B2B8(4, aref, ak, &receiver, &v1, &v2, &v3);
    ref = func_002399F0(p, receiver, v1, v2, v3);
    return ref;
}
