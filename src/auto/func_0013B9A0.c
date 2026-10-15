// PRIVATE unchanged-byte API repair: real8-byteCRef temporary and explicit pointer inputs.
#include "eval_dispatch_api.h"

void func_0013B9A0(void *unused_receiver, ScriptNode *node, EvalFrame *frame, CRef *destination)
{
    CRef temporary;
    func_001296F0(&temporary, node, frame);
    if (destination)
        func_0012B3B0(destination, &temporary);
    func_0012BC20(&temporary);
}
