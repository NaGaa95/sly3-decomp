// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/scene.h"

struct TaggedPeriodMember {
    float period;
    unsigned char opaque04[0x14 - 4];
    SCENE_VIRTUAL_ENTRY *table;
    int identifier;
};
struct TaggedPeriodSource {
    unsigned char opaque00[0x148];
    TaggedPeriodMember member;
};
struct RegisteredPeriodMember {
    float period;
    unsigned char opaque04[0x14 - 4];
    SCENE_VIRTUAL_ENTRY *table;
};
struct RegisteredPeriodSource {
    unsigned char opaque00[0x14C];
    int word14C;
    unsigned char opaque150[8];
    RegisteredPeriodMember member;
};

extern "C" {
void func_0028FD70(void *receiver);
void func_0023AE08(void *receiver);
void func_001A0708(void *member);
void func_0011AF60(void *head, void *receiver);
void func_0011B028(void *head, void *receiver);
extern char D_00479BA4[];
}

extern "C" void func_001A2338(void *receiver)
{
    TaggedPeriodSource *source = (TaggedPeriodSource *)receiver;
    func_0028FD70(receiver);
    func_001A0708((char *)receiver + 0x120);
    TaggedPeriodMember *member = &source->member;
    SCENE_VIRTUAL_ENTRY *entry = &member->table[1];
    SCENE_OBJECT *marked_scene = (SCENE_OBJECT *)entry->Query((char *)member + entry->delta);
    marked_scene->flags.value |= 1UL << 60;
    member->period = 1250.0f;
    member->identifier = -1;
    entry = &member->table[1];
    SCENE_OBJECT *scene = (SCENE_OBJECT *)entry->Query((char *)member + entry->delta);
    int tagged = scene->field3C;
    if ((tagged ^ 1) & 1)
        *(int *)tagged &= ~0x40;
    else
        scene->field3C = tagged & ~0x40;
}

extern "C" void func_001A2768(void *receiver)
{
    RegisteredPeriodSource *source = (RegisteredPeriodSource *)receiver;
    func_0023AE08(receiver);
    func_001A0708((char *)receiver + 0x130);
    RegisteredPeriodMember *member = &source->member;
    SCENE_VIRTUAL_ENTRY *entry = &member->table[1];
    SCENE_OBJECT *scene = (SCENE_OBJECT *)entry->Query((char *)member + entry->delta);
    scene->flags.value |= 1UL << 60;
    member->period = 1250.0f;
    source->word14C = 0;
}

extern "C" void func_001A27D8(void *receiver)
{
    func_0011AF60(D_00479BA4, receiver);
}

extern "C" void func_001A2800(void *receiver)
{
    func_0011B028(D_00479BA4, receiver);
}
