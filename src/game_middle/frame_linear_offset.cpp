// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"
#include "../P2/state_position_ops.h"

struct LinearOffsetSource {
    unsigned char opaque00[0xC];
    SCENE_VIRTUAL_ENTRY *vtable;
    unsigned char opaque10[0x11C - 0x10];
    int suppress_offset;
};
struct LinearOffsetFrame { qword row[4]; };
union LinearOffsetFactor { qword q; float f[4]; };
struct LinearOffsetContext {
    unsigned char opaque00[0x260];
    qword position;
    unsigned char opaque270[0x1148 - 0x270];
    float offset;
    int reverse;
};

extern "C" float func_001205C8(qword vector);

static inline qword LinearOffsetScalar(float value)
{
    qword scalar;
    asm("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}

static inline qword AddLinearOffset(qword delta, qword direction, qword scalar)
{
    qword result;
    asm("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
        : "=j"(result) : "j"(delta), "j"(direction), "j"(scalar));
    return result;
}

extern "C" void func_001A1640(void *receiver, LinearOffsetContext *context,
                             qword *position, float *heading_out)
{
    LinearOffsetSource *source = (LinearOffsetSource *)receiver;
    float offset = 0.0f;
    if (!source->suppress_offset)
        offset = context->offset;
    SCENE_VIRTUAL_ENTRY *entry = &source->vtable[36];
    LinearOffsetFrame *frame = (LinearOffsetFrame *)entry->Query((char *)source + entry->delta);
    qword direction = frame->row[0];
    if (position) {
        entry = &source->vtable[36];
        frame = (LinearOffsetFrame *)entry->Query((char *)source + entry->delta);
        qword delta = PackedDifference(frame->row[3], context->position);
        LinearOffsetFactor scalar;
        scalar.q = LinearOffsetScalar(offset);
        *position = AddLinearOffset(delta, direction, scalar.q);
    }
    if (heading_out) {
        float heading = func_001205C8(direction);
        if (context->reverse == 1)
            heading += 3.14159265f;
        *heading_out = heading;
    }
}
