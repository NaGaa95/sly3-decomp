// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "scene.h"

struct AssetRequestStateOwnerView {
    char prefix[0xC];
    SCENE_VIRTUAL_ENTRY *primary;
    void *subject;
};

struct AssetRequestStateRecordView {
    char opaque[8];
    int state;
    float changedAt;
    float enteredFromZeroAt;
};

struct AssetRequestStateArguments {
    AssetRequestStateRecordView *record;
    int *state;
    int *requested;
};

typedef void (*AssetRequestStateNotify)(void *, int, void *, int,
                                       AssetRequestStateArguments *, int);

struct AssetRequestStateClock { float t; float dt; };

extern "C" {
extern AssetRequestStateClock D_0036BB98;
extern char D_0036C700[];
int func_0013B500(char *, int);
void func_001854C8(void *, int, void *);
}

extern "C" void func_00170410(void *receiver, void *rawRecord, int requested)
{
    AssetRequestStateOwnerView *owner =
        static_cast<AssetRequestStateOwnerView *>(receiver);
    AssetRequestStateRecordView *record =
        static_cast<AssetRequestStateRecordView *>(rawRecord);
    AssetRequestStateArguments arguments;

    if (!record || requested == record->state)
        return;
    if (record->state == 0)
        record->enteredFromZeroAt = D_0036BB98.t;

    arguments.record = record;
    arguments.state = &record->state;
    arguments.requested = &requested;
    SCENE_VIRTUAL_ENTRY *entry = &owner->primary[3];
    reinterpret_cast<AssetRequestStateNotify>(entry->Simple)(
        reinterpret_cast<char *>(owner) + entry->delta,
        0x1F, 0, 3, &arguments, 0);

    record->state = requested;
    record->changedAt = D_0036BB98.t;
    if (owner->subject &&
        func_0013B500(static_cast<char *>(owner->subject), 0x32)) {
        if (requested == 1)
            func_001854C8(D_0036C700, 0x12, owner->subject);
        else
            func_001854C8(D_0036C700, 0x13, owner->subject);
    }
}
