// PRIVATE unchanged-byte API repair: destination8/node/environment are real inputs.
// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"

CRef *func_00128588(CRef *destination, ScriptNode *node, EvalFrame *frame)
{
    CRef temporary, converted;
    temporary.tag = -1;
    func_001296F0(&converted, ((ScriptNode *)node->ref.payload.pointer)->next, frame);
    func_0012B3B0(&temporary, &converted);
    func_0012BC20(&converted);
    func_0012BC20(&temporary);
    func_0012BDD8(&temporary, 0x22);
    func_0012AF00(destination, &temporary);
    func_0012BC20(&temporary);
    return destination;
}
