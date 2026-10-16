// SLY3_CFLAGS: -Os -G0
#include "notify_dispatch_api.h"

typedef struct NotifyReceiver { EvalFrame *frame; } NotifyReceiver;
typedef struct NotifyClock { float time; } NotifyClock;
extern NotifyClock D_0036BB98;
extern unsigned char D_00475480[];
extern const int D_002EDDC0[];
extern const int D_002EDCE4[];

CRef *func_0024AD90(CRef *output, int count, const int *specifications,
                   void *const *argumentAddresses);
ScriptNode **func_0013B8A0(ScriptNode **output, void *receiver,
                          int event, const CRef *arguments);
void *func_0013B9E0(void *game, NotifyReceiver *receiver, ScriptNode *node,
                    float time);
void func_0013B9A0(void *receiver, ScriptNode *node, EvalFrame *frame,
                   CRef *destination);
void func_002BA840(ScriptNode *node, int flags);

void func_0013BB58(void *opaqueReceiver, int event, int scheduleWord,
                   int count, void *const *argumentAddresses, CRef *destination)
{
    NotifyReceiver *receiver = (NotifyReceiver *)opaqueReceiver;
    if (receiver->frame && func_00129B58(receiver->frame, event, 1)) {
        CRef arguments;
        ScriptNode *node;
        func_0024AD90(&arguments, count,
                       &D_002EDCE4[D_002EDDC0[event]], argumentAddresses);
        func_0013B8A0(&node, receiver, event, &arguments);
        if (scheduleWord)
            func_0013B9E0(D_00475480, receiver, node, D_0036BB98.time);
        else
            func_0013B9A0(receiver, node, receiver->frame, destination);
        {
            ScriptNode *owned = node;
            if (owned && --owned->ref.word2 == 0)
                func_002BA840(owned, 3);
        }
        func_0012BC20(&arguments);
    }
}
