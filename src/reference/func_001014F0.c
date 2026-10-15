// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "recovered/splicewrap.h"
void func_0012B768(void *, s32);                 /* extern */
s32 func_002419F0(s32, s32);                        /* extern */

CRef *func_001014F0(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    OTYP aotyp[1];
    s32 arg0_v;
    aotyp[0] = 6;
    func_0024B2B8(&ref, 1, aref, aotyp, &arg0_v);
    func_0012B768(&ref, func_002419F0(pbasic, arg0_v));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
