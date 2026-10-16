// SLY3_CFLAGS: -Os -G0
#include "animation_ensure_api.h"
#include "resource_attachment_api.h"

struct AnimationRecordResource {
    unsigned char beforeAnimation[0x40];
    struct ASEG *animation;
};

struct AttachedAnimationRecord {
    unsigned char base[0x20];
    struct ALO *owner;
    struct ASEGA *animation;
    struct AnimationRecordResource *resource;
    struct ASEG **resourceAnimation;
    int flags;
    unsigned char tail[0x40 - 0x34];
};

typedef char CheckAttachedRecord40[sizeof(struct AttachedAnimationRecord) == 0x40 ? 1 : -1];
void *func_00292034(void *, int, unsigned int);
void *func_002B5958(void *);
void func_00137588(struct ASEG *, struct ALO *, float, float, int, struct ASEGA **);

void func_002594E0(void *input, void *owner, int flags, void *output)
{
    struct AnimationRecordResource *resource = input;
    struct AttachedAnimationRecord *record = output;
    func_00292034(record, 0, sizeof(*record));
    func_00292034(record, 0, sizeof(*record));
    func_002B5958(record);
    record->resource = resource;
    record->owner = owner;
    record->flags = flags;
    func_00137588(resource->animation, owner, 0.0f, 1.0f, flags, &record->animation);
    func_0013BD00(record->animation, (int)record);
    record->resourceAnimation = &resource->animation;
}
