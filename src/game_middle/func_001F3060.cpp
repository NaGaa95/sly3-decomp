// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Source lifecycle: initialise a control source (scene flags on its member object), then register / unregister it
// in the global source list. Same shape as linear_source_lifecycle.cpp.
#include "../P2/scene.h"

typedef int qword __attribute__((mode(TI)));

struct SourceMember {
    float duration;
    unsigned char opaque04[0x14 - 4];
    SCENE_VIRTUAL_ENTRY *vtable;
    int selection;
};
struct Source {
    unsigned char opaque00[0x180];
    unsigned char resource[0x20];
    int enabled;
    unsigned char opaque1A4[4];
    SourceMember member;
    unsigned char opaque1C4[0x1D0 - 0x1C4];
    qword direction;
    int mode;
    int kind;
    float scale;
};

extern "C" {
void func_0022D708(void *receiver);
void func_001A0708(void *member);
void func_001C9118(void *receiver, int state);
void func_0011AF60(void *list, void *receiver);
void func_0011B028(void *list, void *receiver);
extern char D_00479AE4[];
extern qword D_00317530;
}

extern "C" void func_001F3060(void *receiver)
{
    Source *source = (Source *)receiver;
    func_0022D708(receiver);
    func_001A0708(source->resource);
    func_001C9118(receiver, 2);
    source->direction = D_00317530;
    source->kind = 9;
    source->scale = 1.0f;
    source->mode = 8;
    source->enabled = 1;
    SourceMember *member = &source->member;
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

extern "C" void func_001F3160(void *receiver)
{
    func_0011AF60(D_00479AE4, receiver);
}

extern "C" void func_001F3188(void *receiver)
{
    func_0011B028(D_00479AE4, receiver);
}
