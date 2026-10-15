// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/scene.h"

struct LinearLifecycleMember {
    float duration;
    unsigned char opaque04[0x14 - 4];
    SCENE_VIRTUAL_ENTRY *vtable;
    int selection;
};
struct LinearLifecycleSource {
    unsigned char opaque00[0xD0];
    void *resource;
    unsigned char opaqueD4[0xF8 - 0xD4];
    LinearLifecycleMember member;
    unsigned char opaque114[8];
    int suppress_offset;
};

extern "C" {
void func_0028FD70(void *receiver);
void func_001A0708(void *member);
void func_001C9118(void *receiver, int state);
void func_001C7DC8(void *receiver);
void func_00273E48(void *receiver, void *first, void *second, int mode);
void func_0011AF60(void *list, void *receiver);
void func_0011B028(void *list, void *receiver);
extern char D_00479B2C[];
}

extern "C" void func_001A13E0(void *receiver)
{
    LinearLifecycleSource *source = (LinearLifecycleSource *)receiver;
    func_0028FD70(receiver);
    func_001A0708(&source->resource);
    func_001C9118(receiver, 2);
    LinearLifecycleMember *member = &source->member;
    SCENE_VIRTUAL_ENTRY *entry = &member->vtable[1];
    SCENE_OBJECT *marked_scene = (SCENE_OBJECT *)entry->Query((char *)member + entry->delta);
    marked_scene->flags.value |= 1UL << 60;
    member->duration = 1250.0f;
    member->selection = -1;
    entry = &member->vtable[1];
    SCENE_OBJECT *scene = (SCENE_OBJECT *)entry->Query((char *)member + entry->delta);
    int tagged = scene->field3C;
    if ((tagged ^ 1) & 1)
        *(int *)tagged &= ~0x40;
    else
        scene->field3C = tagged & ~0x40;
}

extern "C" void func_001A14B0(void *receiver)
{
    func_0011AF60(D_00479B2C, receiver);
}

extern "C" void func_001A14D8(void *receiver)
{
    func_0011B028(D_00479B2C, receiver);
}

extern "C" void func_001A1500(void *receiver)
{
    LinearLifecycleSource *source = (LinearLifecycleSource *)receiver;
    func_001C7DC8(receiver);
    if (source->resource)
        func_00273E48(source->resource, 0, 0, 0);
    int default_duration = 1;
    if (source->member.duration != 1250.0f)
        default_duration = 0;
    if (default_duration)
        source->member.duration = 1250.0f;
}
