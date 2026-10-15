// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class LoopSequenceReference {
public:
    CRef value;
    LoopSequenceReference() { value.tag=-1; }
    LoopSequenceReference(const LoopSequenceReference &other) __asm__("func_0012AF00");
    LoopSequenceReference &operator=(const LoopSequenceReference &other) __asm__("func_0012B3B0");
    void InitTag(int tag) __asm__("func_0012BDD8");
    void Drop() __asm__("func_0012BC20");
    ~LoopSequenceReference() { Drop(); }
};
extern "C" LoopSequenceReference EvaluateLoopSequenceChild(ScriptNode *node,EvalFrame *frame) __asm__("func_001296F0");

extern "C" LoopSequenceReference func_00128EA0(ScriptNode *node,EvalFrame *frame)
{
    LoopSequenceReference result;
    ScriptNode *condition=((ScriptNode *)node->ref.payload.pointer)->next;
    ScriptNode *body=condition->next;
    for(;;) {
        result=EvaluateLoopSequenceChild(condition,frame);
        if(result.value.tag==0x15 && result.value.payload.integer==0)
            break;
        result=EvaluateLoopSequenceChild(body,frame);
    }
    result.Drop();
    result.InitTag(0x22);
    return result;
}

extern "C" LoopSequenceReference func_00129148(ScriptNode *node,EvalFrame *frame)
{
    LoopSequenceReference result;
    result.Drop();
    result.InitTag(0x22);
    for(ScriptNode *child=((ScriptNode *)node->ref.payload.pointer)->next;
        child;child=child->next)
        result=EvaluateLoopSequenceChild(child,frame);
    return result;
}
