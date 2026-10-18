// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"
#include "../P2/vector_intrinsics.h"
struct LiftFrame { qword row[4]; };
struct LiftSource {
    unsigned char opaque00[0xC];
    SCENE_VIRTUAL_ENTRY *vtable;
    unsigned char opaque10[0x100 - 0x10];
    qword point;
    unsigned char opaque110[0x16C - 0x110];
    SCENE_OBJECT *frameObject;
};
extern "C" int D_0036E6A0;
extern "C" qword func_001C9428(SCENE_OBJECT *source, SCENE_OBJECT *destination, qword position);
extern "C" void func_001A25E0(LiftSource *source, void *unused, qword *out)
{
    if (out) {
        if (D_0036E6A0) {
            SCENE_OBJECT *object = source->frameObject;
            SCENE_VIRTUAL_ENTRY *entry = &object->vtable[36];
            LiftFrame *frame = (LiftFrame *)entry->Query((char *)object + entry->delta);
            *out = frame->row[3];
            ((float *)out)[2] = ((float *)out)[2] + 50.0f;
        } else {
            SCENE_OBJECT *object;
            SCENE_VIRTUAL_ENTRY *entry;
            LiftFrame *frame;
            *out = func_001C9428((SCENE_OBJECT *)source, 0, source->point);
            object = source->frameObject;
            entry = &object->vtable[36];
            frame = (LiftFrame *)entry->Query((char *)object + entry->delta);
            ((float *)out)[2] = PackedVectorZ(frame->row[3]) + 50.0f;
        }
    }
}
