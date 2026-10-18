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

extern "C" ConditionalReference func_00128948(ScriptNode *node,EvalFrame *frame)
{
    ConditionalReference value;
    ConditionalReference test;
    ScriptNode *clause;
    ScriptNode *head;
    value.Drop();
    value.InitTag(0x22);
    clause=((ScriptNode *)node->ref.payload.pointer)->next;
    while(clause) {
        int taken;
        head=(ScriptNode *)clause->ref.payload.pointer;
        if(head->ref.tag==0xA) {
            taken=1;
        } else {
            test=EvaluateConditionalChild(head,frame);
            taken=0;
            if(test.value.tag!=0x15 || test.value.payload.integer!=0) taken=1;
            if(taken && !head->next) value=test;
        }
        if(taken) {
            for(head=head->next;head;head=head->next)
                value=EvaluateConditionalChild(head,frame);
            clause=0;
        } else clause=clause->next;
    }
    return value;
}
