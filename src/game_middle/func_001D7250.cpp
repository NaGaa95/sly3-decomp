// Position of an attached object: its local point is carried through the frame
// of its anchor and then through the anchor frame sampled at the given time.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"
#include "../P2/mat.h"

union AttachedPoint {
    qword packed;
    float lane[4];
};
struct AttachedObject {
    char opaque000[0x1F0];
    SCENE_OBJECT *anchor;
    char opaque1F4[0x200 - 0x1F4];
    qword local;
};

extern "C" void func_0028F680(void *from, void *to, MATRIX4 *matrix, MATRIX4 *inverse, float time);

static inline qword TransformPoint(const MATRIX4 *matrix, qword point)
{
    const qword *columns = (const qword *)matrix;
    qword result;
    __asm__("vmulax.xyz $ACC, %1, %2x\n\tvmadday.xyz $ACC, %3, %2y\n\tvmaddaz.xyz $ACC, %4, %2z\n\tvmaddw.xyz %0, %5, $vf0w"
            : "=j"(result) : "j"(columns[0]), "j"(point), "j"(columns[1]), "j"(columns[2]), "j"(columns[3]));
    return result;
}

extern "C" AttachedPoint func_001D7250(AttachedObject *object, float time)
{
    AttachedPoint result;
    SCENE_OBJECT *anchor = object->anchor;
    if (anchor) {
        MATRIX4 frame, sampled;
        SCENE_VIRTUAL_ENTRY *entry = &anchor->vtable[37];
        void *node = ((void *(*)(void *, MATRIX4 *))entry->Simple)((char *)anchor + entry->delta, &frame);
        func_0028F680(node, 0, &sampled, 0, time);
        result.packed = TransformPoint(&sampled, TransformPoint(&frame, object->local));
    } else {
        result.packed = object->local;
    }
    return result;
}
