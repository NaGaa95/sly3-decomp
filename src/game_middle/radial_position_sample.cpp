// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"

typedef int RadialVector __attribute__((mode(TI)));
struct RadialSource {
    unsigned char opaque00[0xC];
    SCENE_VIRTUAL_ENTRY *vtable;
    unsigned char opaque10[0x11C - 0x10];
    float radius;
};
struct RadialFrame {
    RadialVector row[4];
};

extern "C" {
float func_0011E940(float low, float high);
RadialVector func_0011FD70(float heading, float radius, float height);
extern RadialVector D_00317550;
}

static inline RadialVector AddRadialVectors(RadialVector a, RadialVector b)
{
    RadialVector sum;
    asm("vadd.xyzw %0,%1,%2" : "=j"(sum) : "j"(a), "j"(b));
    return sum;
}

extern "C" void func_001A1308(void *receiver, RadialVector *position,
                             RadialVector *direction)
{
    RadialSource *source = (RadialSource *)receiver;
    float heading = func_0011E940(-3.14159265f, 3.14159265f);
    float radius = func_0011E940(0.0f, 50.0f) + source->radius;
    SCENE_VIRTUAL_ENTRY *entry = &source->vtable[36];
    RadialFrame *frame = (RadialFrame *)entry->Query((char *)source + entry->delta);
    RadialVector origin = frame->row[3];
    *position = AddRadialVectors(origin, func_0011FD70(heading, radius, 0.0f));
    *direction = D_00317550;
}
