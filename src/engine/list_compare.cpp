// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
struct CompareContext {
    ScriptNode *expression;
    EvalFrame *frame;
    CRef *left;
    CRef *right;
};
extern CompareContext D_0036B128;
struct ResultReference {
    CRef value;
    ~ResultReference() { func_0012BC20(&value); }
};
extern "C" int func_00123868(ScriptNode *const *left, ScriptNode *const *right) {
    func_0012B3B0(D_0036B128.left, &(*left)->ref);
    func_0012B3B0(D_0036B128.right, &(*right)->ref);
    ResultReference result;
    func_001296F0(&result.value, D_0036B128.expression, D_0036B128.frame);
    if (result.value.payload.integer)
        return -1;
    return 1;
}
