// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "common.h"
#include "scene.h"

struct CALLBACK_KIND_INFO { int amount, stringId, unknown; };
struct RewardKind { int unknown, index; };
struct RewardTransition {
    char prefix[0xC]; SCENE_VIRTUAL_ENTRY *table;
    char reserved10[0x130 - 0x10]; int mode;
    char reserved134[0x16C - 0x134]; SCENE_OBJECT *observer;
    char reserved170[0x194 - 0x170]; void *property;
    char reserved198[0x1A0 - 0x198]; float lowDelay, highDelay, delay;
    char reserved1AC[8]; RewardKind *kind;
};
typedef char CheckKindInfo12[sizeof(CALLBACK_KIND_INFO) == 12 ? 1 : -1];
typedef char CheckTransition1B8[sizeof(RewardTransition) == 0x1B8 ? 1 : -1];
extern "C" {
extern CALLBACK_KIND_INFO D_00349070[];
extern unsigned char D_0036C700[];
float func_0011E940(float low, float high);
int func_001852E0(void *context);
void func_00185328(void *context, int value);
void *func_001FE728(void *property, int flags);
void func_001F7588(void *receiver, int mode);
}

extern "C" void func_001F8E70(void *receiver, int mode)
{
    RewardTransition *object = (RewardTransition *)receiver;
    if (object->mode == mode)
        return;
    switch (mode) {
    case 0:
        object->delay = func_0011E940(object->lowDelay, object->highDelay);
        break;
    case 1: {
        SCENE_OBJECT *observer = object->observer;
        if (observer) {
            SCENE_VIRTUAL_ENTRY *entry = &observer->vtable[88];
            ((void (*)(void *, void *))entry->Simple)
                ((char *)observer + entry->delta, receiver);
        }
        int reward = D_00349070[object->kind->index].amount;
        if (reward > 0) {
            void *counter = D_0036C700;
            int previous = func_001852E0(counter);
            func_00185328(counter, (int)((uint)previous + (uint)reward));
        }
        void *property = object->property;
        if (property)
            func_001FE728(property, 1);
        SCENE_VIRTUAL_ENTRY *entry = &object->table[3];
        ((void (*)(void *, int, void *, int, void *, void *))entry->Simple)
            ((char *)receiver + entry->delta, 5, 0, 0, 0, 0);
        entry = &object->table[80];
        ((void (*)(void *, int))entry->Simple)
            ((char *)receiver + entry->delta, -1);
        return;
    }
    }
    func_001F7588(receiver, mode);
}
