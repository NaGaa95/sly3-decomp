// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"

struct SceneDeferredNode { void *payload; SceneDeferredNode *next; };
struct SceneDeferredBinding {
    char prefix[0x64];
    SceneDeferredNode *head;
    int unknown68;
    void *pending;
};
struct SceneDeferredState {
    char prefix[0xDC];
    SceneDeferredBinding *binding;
    char padE0[0x120 - 0xE0];
    unsigned long flags;
};
struct SceneDeferredGlobals;
typedef void (SCENE_OBJECT::*SceneDeferredMember)(void *);
extern "C" SceneDeferredGlobals D_00475480;
extern "C" SceneDeferredMember D_00326E90;
extern "C" void func_0015DCD0(SceneDeferredGlobals *, SceneDeferredState *,
                             SceneDeferredMember, void *);
typedef char CheckDeferredMember8[sizeof(SceneDeferredMember) == 8 ? 1 : -1];
typedef char CheckDeferredBinding70[sizeof(SceneDeferredBinding) == 0x70 ? 1 : -1];
typedef char CheckDeferredState128[sizeof(SceneDeferredState) == 0x128 ? 1 : -1];

extern "C" void func_0023E068(SceneDeferredState *object)
{
    SceneDeferredBinding *binding = object->binding;
    if (binding->pending) {
        func_0015DCD0(&D_00475480, object, D_00326E90, 0);
    } else if (object->flags & (3UL << 56)) {
        for (SceneDeferredNode *node = binding->head; node; node = node->next) {
            if (node->payload) {
                func_0015DCD0(&D_00475480, object, D_00326E90, 0);
                break;
            }
        }
    }
}
