// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/scene.h"

struct RecentRemoveRecord {
    char prefix[0x18];
    unsigned long flags;
};

struct RecentRemoveQueue {
    char prefix[0x410];
    RecentRemoveQueue *next;
};

extern "C" RecentRemoveQueue *D_00479BC8;
extern "C" void func_001C10A0(void *queue, SCENE_OBJECT *object, RecentRemoveRecord *record);
extern "C" void func_002BE508(void *unused_token, int flags);

extern "C" void func_001C1128(void *unused_game, SCENE_OBJECT *object, RecentRemoveRecord *record)
{
    char token;
    for (RecentRemoveQueue *queue = D_00479BC8; queue; queue = queue->next)
        func_001C10A0(queue, object, record);
    if (object)
        object->flags.value &= ~(1UL << 55);
    if (record)
        record->flags &= ~(1UL << 20);
    func_002BE508(&token, 2);
}
