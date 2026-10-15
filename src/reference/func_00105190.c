#include "recovered/splicewrap.h"
void func_0012B270(void *, s32);
struct Holder;
s32 func_00170500(struct Holder *, void *);

CRef *func_00105190(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    OTYP aotyp[1];
    s32 arg0_v;
    aotyp[0] = 0x2002;
    func_0024B2B8(&ref, 1, aref, aotyp, &arg0_v);
    func_0012B270(&ref, func_00170500((struct Holder *)pbasic, (void *)arg0_v));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
