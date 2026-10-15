// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
void func_002BA840(void *receiver, int flags);
}

// Same class declaration as the maintained script_closure.cpp caller.
struct ClosureNodeReference {
    ScriptNode *value;
    void operator=(ScriptNode *node) __asm__("func_002BA780");
};

void ClosureNodeReference::operator=(ScriptNode *node)
{
    if (node)
        node->ref.word2++;
    ScriptNode *previous = value;
    if (previous && --previous->ref.word2 == 0)
        func_002BA840(previous, 3);
    value = node;
}
