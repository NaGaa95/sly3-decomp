// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"
CRef *func_00129A90(CRef *ret, EvalFrame *a, int b, CRef *pref)
{
    CRef ref;
    CRef *p;
    ref.tag = -1;
    p = func_00129B58(a, b, 1);
    if (p)
        func_0012B3B0(p, pref);
    func_0012BC20(&ref);
    func_0012BDD8(&ref, 0x22);
    func_0012AF00(ret, &ref);
    func_0012BC20(&ref);
    return ret;
}
