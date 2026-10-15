// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
class BindingExpressionReference {
public:
    CRef value;
    BindingExpressionReference() { value.tag=-1; }
    BindingExpressionReference(const BindingExpressionReference &other) __asm__("func_0012AF00");
    BindingExpressionReference &operator=(const BindingExpressionReference &other) __asm__("func_0012B3B0");
    void Drop() __asm__("func_0012BC20");
    ~BindingExpressionReference() { Drop(); }
};
extern "C" BindingExpressionReference EvaluateBindingValue(ScriptNode *node,EvalFrame *frame) __asm__("func_001296F0");
extern "C" BindingExpressionReference InsertBindingValue(EvalFrame *frame,int key,const CRef *source) __asm__("func_001299C8");

extern "C" BindingExpressionReference func_001284D8(ScriptNode *node,EvalFrame *frame)
{
    BindingExpressionReference result;
    ScriptNode *key=((ScriptNode *)node->ref.payload.pointer)->next;
    result=EvaluateBindingValue(key->next,frame);
    result=InsertBindingValue(frame,key->ref.payload.integer,&result.value);
    return result;
}
