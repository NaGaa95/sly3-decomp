// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "recovered/splicewrap.h"
void func_0012B2F0(void *, s32);                 /* extern */
s32 func_001A2198(s32, s32);                        /* extern */

CRef *func_0010C3F8(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    OTYP aotyp[1];
    s32 arg0_v;
    aotyp[0] = 0x2002;
    func_0024B2B8(&ref, 1, aref, aotyp, &arg0_v);
    func_0012B2F0(&ref, func_001A2198(pbasic, arg0_v) != 0);
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
