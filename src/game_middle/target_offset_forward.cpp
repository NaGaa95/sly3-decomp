// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/state_position_ops.h"
struct OffsetRecord { char prefix[0x30]; qword value; };
struct OffsetMethod { short delta, reserved; OffsetRecord *(*get)(void *receiver); };
struct OffsetObject { char prefix[12]; OffsetMethod *methods; };
struct OffsetEntry { char prefix[0x190]; int active; };
struct OffsetActor {
    char prefix[12];
    OffsetMethod *methods;
    char gap10[0x1540 - 0x10];
    OffsetEntry *entry;
    char gap1544[0x1568 - 0x1544];
    OffsetObject *target;
};
extern "C" void func_001DE690(void *actor, int state);
extern "C" void func_0024E8E8(void *owner, qword difference);
extern "C" void func_001E0380(OffsetActor *actor, OffsetObject *target)
{
    if (actor->entry) {
        if (actor->entry->active) {
            func_001DE690(actor, 7);
            if (target) {
                actor->target = target;
                OffsetMethod *targetMethod = &target->methods[36];
                qword targetPosition = targetMethod->get((char *)target + targetMethod->delta)->value;
                OffsetMethod *actorMethod = &actor->methods[36];
                qword actorPosition = actorMethod->get((char *)actor + actorMethod->delta)->value;
                func_0024E8E8(actor, PackedDifference(targetPosition, actorPosition));
            }
        }
    }
}
