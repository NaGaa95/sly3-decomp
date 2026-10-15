// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
#include "../P2/scene.h"

struct ControlSourcePath {
    unsigned char opaque00[8];
    float limit;
    unsigned char opaque0C[0x28 - 0xC];
};
struct ControlSourceMember {
    float duration;
    unsigned char opaque04[0x14 - 4];
    SCENE_VIRTUAL_ENTRY *vtable;
    void *next, *previous;
};
struct ControlSource {
    unsigned char opaque00[0x130];
    ControlSourcePath path;
    ControlSourceMember member;
    int state;
    unsigned char opaque17C[0x188 - 0x17C];
    int enabled;
};

extern "C" {
void func_0023AE08(void *receiver);
void func_001A0708(void *member);
void func_00240E58(void *receiver, unsigned int mask, int value);
void func_001FC968(void *receiver, void *owner);
void func_0011AF60(void *list, void *receiver);
void func_0011B028(void *list, void *receiver);
extern char D_00479B08[];
}

extern "C" void func_001A1730(void *receiver)
{
    ControlSource *source = (ControlSource *)receiver;
    func_0023AE08(receiver);
    func_001A0708(&source->path);
    ControlSourceMember *member = &source->member;
    SCENE_VIRTUAL_ENTRY *entry = &member->vtable[1];
    SCENE_OBJECT *scene = (SCENE_OBJECT *)entry->Query((char *)member + entry->delta);
    scene->flags.value |= 1UL << 60;
    source->state = 0;
    member->duration = 1250.0f;
    source->path.limit = 300.0f;
    source->enabled = 1;
    func_00240E58(receiver, 0x03FFFFFFu, 2);
    func_00240E58(receiver, 0x00D88001u, 0);
}

extern "C" void func_001A17D8(void *receiver, void *owner)
{
    func_001FC968(receiver, owner);
    ((ControlSource *)receiver)->state = 0;
}

extern "C" void func_001A1800(void *receiver)
{
    func_0011AF60(D_00479B08, receiver);
}

extern "C" void func_001A1828(void *receiver)
{
    func_0011B028(D_00479B08, receiver);
}
