// SLY3_CFLAGS: -Os -G0
#include "eval_dispatch_api.h"

ScriptNode *func_002BA6B8(void);
void func_002BA760(ScriptNode **slot, ScriptNode *node);
void func_002BA780(ScriptNode **slot, ScriptNode *node);
void func_002BA840(ScriptNode *node, int flags);
CRef *func_0012B6C8(CRef *reference, ScriptNode *node);
CRef *func_0012B330(CRef *reference, int value);
CRef *func_0012B768(CRef *reference, void *object);

ScriptNode **func_0013B8A0(ScriptNode **output, void *receiver, int event,
                           const CRef *arguments)
{
    ScriptNode *owned;
    ScriptNode *tail;
    func_002BA760(&owned, func_002BA6B8());
    {
        CRef *head = &owned->ref;
        func_0012B6C8(head, func_002BA6B8());
    }
    tail = (ScriptNode *)owned->ref.payload.pointer;
    func_0012B330(&tail->ref, event);
    {
        ScriptNode *node = func_002BA6B8();
        func_002BA780(&tail->next, node);
    }
    tail = tail->next;
    func_0012B768(&tail->ref, receiver);
    if (arguments && arguments->tag)
        func_002BA780(&tail->next, (ScriptNode *)arguments->payload.pointer);
    func_002BA760(output, owned);
    {
        ScriptNode *node = owned;
        if (node && --node->ref.word2 == 0)
            func_002BA840(node, 3);
    }
    return output;
}
