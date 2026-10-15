// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "recovered/splicewrap.h"
void func_0012B2B0(void *, f32);                 /* extern */
f32 func_002483D8(s32);                             /* extern */

CRef *func_00102960(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    func_0024B2B8(&ref, 0, aref, NULL);
    func_0012B2B0(&ref, func_002483D8(pbasic));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
