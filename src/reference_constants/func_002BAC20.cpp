// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "runtime_closure_release_access.h"

void ClosureStorage::Destroy(int flags)
{
    ScriptNode *node = body.value;
    if (node && --node->ref.word2 == 0)
        func_002BA840(node, 3);
    node = parameters.value;
    if (node && --node->ref.word2 == 0)
        func_002BA840(node, 3);
    EvalFrame *frame = parent.value;
    if (frame && --((RuntimeFrameCountView *)frame)->references == 0)
        func_002BABA8(frame, 3);
    func_002B46C8((struct S *)this);
    if (flags & 1)
        func_0011E1F0(D_004D2D60, this);
}
