#include "actor_resource_lookup_api.h"
// Recovered using the Sly 2 source; Sly 3 calls and globals resolved from original operands.
#include "recovered/splicewrap.h"
void func_0012B768(void *, s32);
/* extern */ CRef *func_0010D2B8(CRef *ret, void *pbasic, s32 cref, CRef *aref) {
    CRef ref;
    func_0024B2B8(&ref, 0, aref, NULL);
    func_0012B768(&ref, (s32)func_001FBE30(pbasic, 0));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
