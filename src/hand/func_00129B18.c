// PRIVATE unchanged-byte API repair: key/flag integers and actualCRef lookup/copy pointers.
#include "eval_dispatch_api.h"

int func_00129B18(EvalFrame *frame, int key, int searchParents, CRef *output)
{
    CRef *value = func_00129B58(frame, key, searchParents);
    if (value) {
        if (output)
            func_0012B3B0(output, value);
        return 1;
    }
    return 0;
}
