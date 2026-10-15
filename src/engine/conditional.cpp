// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class ConditionalReference {
public:
    CRef value;
    ConditionalReference() { value.tag=-1; }
    ConditionalReference(const ConditionalReference &other) __asm__("func_0012AF00");
    ConditionalReference &operator=(const ConditionalReference &other) __asm__("func_0012B3B0");
    void InitTag(int tag) __asm__("func_0012BDD8");
    void Drop() __asm__("func_0012BC20");
    ~ConditionalReference() { Drop(); }
};
extern "C" ConditionalReference EvaluateConditionalChild(ScriptNode *node,EvalFrame *frame) __asm__("func_001296F0");

extern "C" ConditionalReference func_001286A0(ScriptNode *node,EvalFrame *frame)
{
    ConditionalReference result;
    ScriptNode *condition=((ScriptNode *)node->ref.payload.pointer)->next;
    ScriptNode *whenTrue=condition->next;
    ScriptNode *whenFalse=whenTrue->next;
    result=EvaluateConditionalChild(condition,frame);
    if(result.value.payload.integer==1)
        result=EvaluateConditionalChild(whenTrue,frame);
    else if(whenFalse)
        result=EvaluateConditionalChild(whenFalse,frame);
    else {
        result.Drop();
        result.InitTag(0x22);
    }
    return result;
}
