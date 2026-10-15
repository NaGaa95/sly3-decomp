// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
}
struct ClosureFrameReference {
    EvalFrame *value;
    void operator=(EvalFrame *frame) __asm__("func_002BAA50");
};
struct ClosureNodeReference {
    ScriptNode *value;
    void operator=(ScriptNode *node) __asm__("func_002BA780");
};
struct ClosureStorage {
    int references;
    unsigned int word4;
    ClosureFrameReference parent;
    int parameterCount;
    int hasRestParameter;
    ClosureNodeReference parameters;
    ClosureNodeReference body;
    void Destroy(int flags) __asm__("func_002BAC20");
};
class ClosureOwner {
public:
    ClosureStorage *value;
    void Set(ClosureStorage *storage) __asm__("func_002BAB68");
    ClosureOwner(ClosureStorage *storage) { Set(storage); }
    ~ClosureOwner() {
        ClosureStorage *storage=value;
        if(storage && --storage->references==0)
            storage->Destroy(3);
    }
};
class ClosureReference {
public:
    CRef value;
    ClosureReference(ClosureStorage *storage) __asm__("func_0012B1F8");
    void Drop() __asm__("func_0012BC20");
    ~ClosureReference() { Drop(); }
};
extern "C" ClosureStorage *func_002BAAB8();

extern "C" ClosureReference func_00128F90(ScriptNode *node,EvalFrame *frame)
{
    ScriptNode *parameterExpression=((ScriptNode *)node->ref.payload.pointer)->next;
    ScriptNode *body=parameterExpression->next;
    ClosureOwner owner(func_002BAAB8());
    owner.value->parent=frame;
    if(parameterExpression->ref.tag==0)
        owner.value->parameters=0;
    else
        owner.value->parameters=(ScriptNode *)parameterExpression->ref.payload.pointer;
    owner.value->body=body;
    int hasRest=0;
    int count=0;
    for(ScriptNode *parameter=owner.value->parameters.value;parameter;) {
        if(parameter->ref.tag==0x12) {
            hasRest=1;
            parameter=0;
        } else {
            parameter=parameter->next;
            count++;
        }
    }
    owner.value->parameterCount=count;
    owner.value->hasRestParameter=hasRest;
    return ClosureReference(owner.value);
}
