// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/state_position_ops.h"
struct SideRecord { char prefix[0x30]; qword value; };
struct SideMethod { short delta, reserved; SideRecord *(*get)(void *receiver); };
struct SideObject { char prefix[12]; SideMethod *methods; };
struct SideEntry { char prefix[0x14]; int slot; };
struct SideActor {
    char prefix[12];
    SideMethod *methods;
    char gap10[0x11B4 - 0x10];
    SideObject *object;
    char gap11B8[0x187C - 0x11B8];
    int leftSlot;
    char gap1880[0x1884 - 0x1880];
    int rightSlot;
    char gap1888[0x18DC - 0x1888];
    SideEntry *entry;
};
extern "C" void func_001DE690(void *actor, int state);
extern "C" qword func_001C94E8(void *source, void *destination, qword direction);
extern "C" void func_001E1018(void *actor, int side);
extern "C" void func_001E0F38(SideActor *actor)
{
    int side;
    func_001DE690(actor, 0xC);
    if (actor->entry) {
        int slot = actor->entry->slot;
        if (slot == actor->leftSlot || slot == actor->rightSlot)
            side = 3;
        else
            side = 2;
    } else if (actor->object) {
        SideObject *object = actor->object;
        SideMethod *objectMethod = &object->methods[36];
        qword objectPosition = objectMethod->get((char *)object + objectMethod->delta)->value;
        SideMethod *actorMethod = &actor->methods[36];
        qword actorPosition = actorMethod->get((char *)actor + actorMethod->delta)->value;
        qword local = func_001C94E8(0, actor, PackedDifference(objectPosition, actorPosition));
        side = 0.0f < PackedVectorY(local) ? 2 : 3;
    } else {
        side = 3;
    }
    func_001E1018(actor, side);
}
