// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class OptionalEvaluationReference {
public:
    CRef value;
    OptionalEvaluationReference() { value.tag=-1; }
    OptionalEvaluationReference(const OptionalEvaluationReference &other) __asm__("func_0012AF00");
    OptionalEvaluationReference &operator=(const OptionalEvaluationReference &other) __asm__("func_0012B3B0");
    void InitTag(int tag) __asm__("func_0012BDD8");
    void Drop() __asm__("func_0012BC20");
    ~OptionalEvaluationReference() { Drop(); }
};
extern "C" OptionalEvaluationReference EvaluateOptionalChild(ScriptNode *node,EvalFrame *frame) __asm__("func_001296F0");

extern "C" OptionalEvaluationReference func_00128610(ScriptNode *node,EvalFrame *frame)
{
    OptionalEvaluationReference result;
    ScriptNode *child=((ScriptNode *)node->ref.payload.pointer)->next;
    if(child)
        result=EvaluateOptionalChild(child,frame);
    else {
        result.Drop();
        result.InitTag(0x22);
    }
    return result;
}
