// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "recovered/splicewrap.h"
M2C_UNK func_0012B270(void *, s32);                 /* extern */
s32 func_00240E10(s32, s32);                        /* extern */

CRef *func_001010D0(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    OTYP aotyp[1];
    s32 arg0_v;
    aotyp[0] = 0x1011;
    func_0024B2B8(&ref, 1, aref, aotyp, &arg0_v);
    func_0012B270(&ref, func_00240E10(pbasic, arg0_v));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
