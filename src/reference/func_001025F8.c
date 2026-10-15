// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "recovered/splicewrap.h"
void func_0012B2B0(void *, f32);
/* extern */ f32 func_00246E40(void *, s32);
/* extern */ CRef *func_001025F8(CRef *ret, void *pbasic, s32 cref, CRef *aref) {
    CRef ref;
    OTYP aotyp[1];
    s32 arg0_v;
    aotyp[0] = 0x10;
    func_0024B2B8(&ref, 1, aref, aotyp, &arg0_v);
    func_0012B2B0(&ref, func_00246E40(pbasic, arg0_v));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
