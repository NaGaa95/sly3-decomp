// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class ShortCircuitReference {
public:
    CRef value;
    ShortCircuitReference() { value.tag=-1; }
    ShortCircuitReference(const ShortCircuitReference &other) __asm__("func_0012AF00");
    ShortCircuitReference &operator=(const ShortCircuitReference &other) __asm__("func_0012B3B0");
    ShortCircuitReference &operator=(bool value) __asm__("func_0012B2F0");
    void Drop() __asm__("func_0012BC20");
    ~ShortCircuitReference() { Drop(); }
};
extern "C" ShortCircuitReference EvaluateShortCircuitChild(ScriptNode *node,EvalFrame *frame) __asm__("func_001296F0");

extern "C" ShortCircuitReference func_00128788(ScriptNode *node,EvalFrame *frame)
{
    ShortCircuitReference result;
    for(ScriptNode *child=((ScriptNode *)node->ref.payload.pointer)->next;
        child;child=child->next) {
        result=EvaluateShortCircuitChild(child,frame);
        if(result.value.tag!=0x15 || result.value.payload.integer!=0)
            return result;
    }
    result=false;
    return result;
}

extern "C" ShortCircuitReference func_00128860(ScriptNode *node,EvalFrame *frame)
{
    ShortCircuitReference result;
    result=true;
    for(ScriptNode *child=((ScriptNode *)node->ref.payload.pointer)->next;
        child;child=child->next) {
        result=EvaluateShortCircuitChild(child,frame);
        if(result.value.tag==0x15 && result.value.payload.integer==0)
            return result;
    }
    return result;
}
