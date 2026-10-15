#include "eval_dispatch_api.h"
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
struct S;
struct RuntimeSceneCounterView { unsigned int references; };
struct RuntimeSceneOwnerReferences {
    struct RuntimeSceneCounterView *actor;
    struct RuntimeSceneCounterView *script;
};
void func_002BB8B8(struct S *script, int flags);
void func_002BABA8(EvalFrame *actor, int flags);
void func_001D2818(void *storage);

void func_002BC7F0(void *storage, int flags)
{
    struct RuntimeSceneOwnerReferences *owner = storage;
    struct RuntimeSceneCounterView *script = owner->script;
    struct RuntimeSceneCounterView *actor;
    if (script && --script->references == 0)
        func_002BB8B8((struct S *)script, 3);
    actor = owner->actor;
    if (actor && --actor->references == 0)
        func_002BABA8((EvalFrame *)actor, 3);
    if (flags & 1)
        func_001D2818(owner);
}
