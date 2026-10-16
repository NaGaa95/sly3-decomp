#include "recovered/splicewrap.h"
CRef *func_0012B768(CRef *, void *);
#include "resource_selected_child_pointer_api.h"

CRef *func_0010D328(CRef *ret, void *pbasic, s32 cref, CRef *aref)
{
    CRef ref;
    func_0024B2B8(&ref, 0, aref, NULL);
    func_0012B768(&ref, func_001FBF08(pbasic));
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
