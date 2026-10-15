#include "pool_reset_api.h"
#include "eval_dispatch_api.h"

struct ClosureFrameReference;
void func_002BAA50(struct ClosureFrameReference *reference, EvalFrame *frame);

void func_002499C8(int reference, int unused)
{
    func_002BAA50((struct ClosureFrameReference *)reference, 0);
    func_0012CA50();
}
