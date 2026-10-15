// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
#include "activation_selector_api.h"
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
extern "C" CRef func_001055E8(void *p, int c, void *aref);
CRef func_001055E8(void *p, int c, void *aref)
{
    // Sly 3 descriptor IDs recovered from 0x0031E7F0.
    int ak[3] = {0x202F, 0x6, 0x100B};
    void *receiver;
    int b, d;
    CRef ref = func_0024B2B8(3, aref, ak, &receiver, &b, &d);
    ref = func_002399C8(p, receiver, b, d);
    return ref;
}
