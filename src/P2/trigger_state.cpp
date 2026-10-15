// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct TriggerStatePair { int key, value; };
struct TriggerTransitionView {
    char prefix[12]; SCENE_VIRTUAL_ENTRY *table;
    char pad10[0x124 - 0x10];
    int cancel, state;
    float stateStart;
    char pad130[0x180 - 0x130];
    float deadline, timeout, delay;
    int notificationCount;
    TriggerStatePair notifications[4];
};
struct TriggerStateClock { float current, delta; };
struct TriggerStateGame { char prefix[0x4424]; TriggerTransitionView *current; };
typedef char CheckTriggerView1B0[sizeof(TriggerTransitionView) == 0x1B0 ? 1 : -1];
extern "C" {
extern TriggerStateClock D_0036BB98;
extern TriggerStateGame D_00475480;
extern char D_0036C700[];
void func_001C9118(void *, int);
void func_001A93C8(void *unused, int selection, unsigned int flags);
void func_001A9420(void *unused, int selection, unsigned int flags);
void func_00185908(void *, int, TriggerStatePair *, void *);
TriggerTransitionView *func_0027F990(void *unused);
}
extern "C" void func_0027FC08(TriggerTransitionView *object, int state)
{
    int previous = object->state;
    if (state == previous) return;
    if (previous < 6) {
        if (previous >= 4) {
            func_001C9118(object, 0);
            func_001A9420(&D_00475480, -1, 3);
            D_00475480.current = 0;
        }
    }
    if (state < 6) {
        if (state >= 4) {
            func_001C9118(object, 1);
            func_001A93C8(&D_00475480, -1, 3);
            D_00475480.current = object;
        }
    }
    object->state = state;
    object->stateStart = D_0036BB98.current;
}
extern "C" void func_0027FCC8(TriggerTransitionView *object)
{
    if (object->state != 3) return;
    if (object->cancel) {
        func_0027FC08(object, 0);
        TriggerTransitionView *selected = func_0027F990(&D_00475480);
        if (selected) func_0027FCC8(selected);
        return;
    }
    func_00185908(D_0036C700, object->notificationCount, object->notifications, object);
    func_0027FC08(object, 4);
    object->deadline = D_0036BB98.current + object->delay;
    SCENE_VIRTUAL_ENTRY *entry = &object->table[3];
    ((void (*)(void *, int, int, int, void *, int))entry->Simple)(
        reinterpret_cast<char *>(object) + entry->delta, 5, 0, 0, 0, 0);
}
