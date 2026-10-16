// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/scene.h"

struct FrameLimitMember {
    float period;
    unsigned char opaque04[0x14 - 4];
    SCENE_VIRTUAL_ENTRY *table;
    int identifier;
};
struct FrameLimitSource {
    unsigned char opaque00[0xE0];
    int enabled;
    unsigned char opaqueE4[12];
    int state;
    unsigned char opaqueF4[4];
    FrameLimitMember member;
    unsigned char opaque114[12];
    float limit;
};

extern "C" void func_0028FD70(void *receiver);
extern "C" void func_001A0708(void *member);
extern "C" void func_001C9118(void *receiver, int state);

extern "C" void func_001A1D70(void *receiver)
{
    FrameLimitSource *source = (FrameLimitSource *)receiver;
    func_0028FD70(receiver);
    func_001A0708((char *)receiver + 0xD0);
    func_001C9118(receiver, 2);
    source->enabled = 1;
    source->limit = 200.0f;
    source->state = 0;
    FrameLimitMember *member = &source->member;
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
