#include "recovered/splicewrap.h"
CRef *func_0012B768(CRef *, void *);
void *func_0023FB68(void *, s32);

CRef *func_001015F0(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    OTYP aotyp[1];
    s32 arg0_v;
    aotyp[0] = 6;
    func_0024B2B8(&ref, 1, aref, aotyp, &arg0_v);
    func_0012B768(&ref, func_0023FB68(pbasic, arg0_v));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
