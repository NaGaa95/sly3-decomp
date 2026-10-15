// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "recovered/splicewrap.h"
void func_0012B768(void *, s32);                 /* extern */
s32 func_001FBF08(s32);                             /* extern */

CRef *func_0010D328(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    func_0024B2B8(&ref, 0, aref, NULL);
    func_0012B768(&ref, func_001FBF08(pbasic));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
