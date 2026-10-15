// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "runtime_closure_release_access.h"

extern "C" void func_002BABA8(EvalFrame *frame, int flags)
{
    RuntimeEvalFrameReleaseView *view = (RuntimeEvalFrameReleaseView *)frame;
    RuntimeFrameCountView *bindings = view->bindings;
    if (bindings && --bindings->references == 0)
        func_002BACE0(bindings, 3);
    func_002BAD40((int **)&view->parent, 2);
    func_002B4308((struct S *)frame);
    if (flags & 1)
        func_0011E1F0(D_004D2C88, frame);
}
