// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "bis.h"
#include "heap.h"
extern "C" {
#include "eval_dispatch_api.h"
}
class ResultReference {
public:
    CRef value;
    ResultReference() { value.tag = -1; }
    ResultReference(const ResultReference &) __asm__("func_0012AF00");
    ResultReference &operator=(const ResultReference &) __asm__("func_0012B3B0");
    void Drop() __asm__("func_0012BC20");
    ~ResultReference() { Drop(); }
};
extern "C" void func_002BA840(void *, int);
class NodeHandle {
public:
    ScriptNode *value;
    NodeHandle(const NodeHandle &);
    ~NodeHandle()
    {
        ScriptNode *node = value;
        if (node && --node->ref.word2 == 0)
            func_002BA840(node, 3);
    }
};
struct FrameSlot {
    EvalFrame *value;
    void operator=(EvalFrame *frame) __asm__("func_002BAA50");
};
struct FrameView { unsigned char prefix[0x14]; int flag; };
struct FrameList {
    int key;
    int count;
    FrameSlot *slots;
    FrameList *previous;
};
struct ListOwner {
    unsigned char prefix[0x3F18];
    FrameList *current;
    FrameList *head;
};
extern "C" {
extern int D_0047A488;
extern char D_0036B138[];
EvalFrame *func_002BA9A8();
void func_002BE530(EvalFrame *);
void func_00119830(CBinaryInputStream *);
void func_00129E20(void *);
void *func_001D2538(ALLOCREQ *);
}
extern "C" NodeHandle func_0012C108(CBinaryInputStream *) ;
extern "C" ResultReference EvaluateNode(ScriptNode *, EvalFrame *) __asm__("func_001296F0");
extern "C" void func_002499F0(ListOwner *owner, int key, CBinaryInputStream *stream)
{
    int count = stream->U32Read();
    if (count) {
        FrameList *list;
        {
            ALLOCREQ request;
            request.cb = 16;
            request.cbAlign = 16;
            list = (FrameList *)func_001D2538(&request);
            list->key = key;
            owner->current = list;
            list->previous = owner->head;
            owner->head = list;
            list->count = count;
            request.cb = count * 4;
            request.cbAlign = 16;
            list->slots = (FrameSlot *)func_001D2538(&request);
        }
        for (int i = 0; i < count; ++i) {
            FrameSlot *slot = &list->slots[i];
            NodeHandle node = func_0012C108(stream);
            if (D_0047A488) {
                func_00119830(stream);
                func_00119830(stream);
                func_00119830(stream);
            }
            *slot = func_002BA9A8();
            func_002BE530(slot->value);
            ((FrameView *)slot->value)->flag = 1;
            EvaluateNode(node.value, slot->value);
        }
        func_00129E20(D_0036B138);
    }
}
