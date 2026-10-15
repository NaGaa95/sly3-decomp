// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"

typedef int TravelVector __attribute__((mode(TI)));
struct TravelSource {
    unsigned char opaque00[0xC];
    SCENE_VIRTUAL_ENTRY *vtable;
    unsigned char opaque10[0x11C - 0x10];
    float radius;
};
struct TravelFrame { TravelVector row[4]; };

extern "C" {
TravelVector func_00250600(void *context);
float func_001205C8(TravelVector direction);
}

static inline TravelVector SubtractTravelVectors(TravelVector a, TravelVector b)
{
    TravelVector difference;
    asm("vsub.xyzw %0,%1,%2" : "=j"(difference) : "j"(a), "j"(b));
    return difference;
}

extern "C" void func_001A11C8(void *receiver, void *context, float *travel)
{
    TravelSource *source = (TravelSource *)receiver;
    TravelVector point = func_00250600(context);
    SCENE_VIRTUAL_ENTRY *entry = &source->vtable[36];
    TravelFrame *frame = (TravelFrame *)entry->Query((char *)source + entry->delta);
    TravelVector direction = SubtractTravelVectors(point, frame->row[3]);
    *travel = func_001205C8(direction) * source->radius;
}
