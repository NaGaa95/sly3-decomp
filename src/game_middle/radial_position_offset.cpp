// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"

typedef int OffsetVector __attribute__((mode(TI)));
struct OffsetSource {
    unsigned char opaque00[0xC];
    SCENE_VIRTUAL_ENTRY *vtable;
    unsigned char opaque10[0x11C - 0x10];
    float radius;
};
struct OffsetFrame { OffsetVector row[4]; };
struct OffsetContext {
    unsigned char opaque00[0x260];
    OffsetVector position;
    unsigned char opaque270[0x1148 - 0x270];
    float radial_offset;
    int reversed;
};

extern "C" OffsetVector func_0011FD70(float heading, float radius, float height);

static inline OffsetVector AddOffsetVectors(OffsetVector a, OffsetVector b)
{
    OffsetVector sum;
    asm("vadd.xyzw %0,%1,%2" : "=j"(sum) : "j"(a), "j"(b));
    return sum;
}
static inline OffsetVector SubtractOffsetVectors(OffsetVector a, OffsetVector b)
{
    OffsetVector difference;
    asm("vsub.xyzw %0,%1,%2" : "=j"(difference) : "j"(a), "j"(b));
    return difference;
}

extern "C" void func_001A1238(void *receiver, OffsetContext *context,
                             OffsetVector *position, float *heading_out,
                             float travel)
{
    OffsetSource *source = (OffsetSource *)receiver;
    float heading = travel / source->radius;
    float radius = source->radius + context->radial_offset;
    if (position) {
        SCENE_VIRTUAL_ENTRY *entry = &source->vtable[36];
        OffsetFrame *frame = (OffsetFrame *)entry->Query((char *)source + entry->delta);
        OffsetVector origin = frame->row[3];
        *position = SubtractOffsetVectors(
            AddOffsetVectors(origin, func_0011FD70(heading, radius, 0.0f)),
            context->position);
    }
    if (heading_out) {
        if (context->reversed == 1)
            heading += 3.14159265f;
        *heading_out = heading;
    }
}
