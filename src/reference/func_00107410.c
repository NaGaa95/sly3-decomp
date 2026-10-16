#include "recovered/splicewrap.h"
struct O;
CRef *func_0012B768(CRef *, struct O *);
void *func_001FE950(void *, s32);

CRef *func_00107410(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    OTYP aotyp[1];
    s32 arg0_v;
    aotyp[0] = 6;
    func_0024B2B8(&ref, 1, aref, aotyp, &arg0_v);
    func_0012B768(&ref, (struct O *)func_001FE950(pbasic, arg0_v));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
