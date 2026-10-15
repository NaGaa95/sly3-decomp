// SLY3_CFLAGS: -Os -G0 -fno-exceptions
extern "C" {
#include "eval_dispatch_api.h"
ScriptNode *func_002BA6B8();
void func_002BA760(ScriptNode **slot,ScriptNode *node);
void func_002BA780(ScriptNode **slot,ScriptNode *node);
void func_002BA840(void *node,int flags);
CRef *func_0012B1D8(CRef *result,ScriptNode *node);
}
class OwnedListNode {
public:
    ScriptNode *value;
    void Set(ScriptNode *node) { func_002BA760(&value,node); }
    ~OwnedListNode() {
        ScriptNode *node=value;
        if(node && --node->ref.word2==0)
            func_002BA840(node,3);
    }
};
extern "C" CRef *func_00122768(CRef *result,int unused_count,CRef *arguments,EvalFrame *unused_frame)
{
    OwnedListNode node;
    node.Set(func_002BA6B8());
    func_0012B3B0(&node.value->ref,&arguments[0]);
    CRef *tail=&arguments[1];
    if(tail->tag==0x1D)
        func_002BA780(&node.value->next,(ScriptNode *)tail->payload.pointer);
    func_0012B1D8(result,node.value);
    return result;
}
extern "C" CRef *func_00123AE8(CRef *result,int unused_count,CRef *arguments,EvalFrame *frame)
{
    OwnedListNode node;
    node.Set(func_002BA6B8());
    func_0012B3B0(&node.value->ref,&arguments[0]);
    func_001296F0(result,node.value,frame);
    return result;
}
