// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/vector_intrinsics.h"
struct InterceptCoefficient {
    char unaccessed[0x88];
    float coefficient;
};
struct InterceptOwner {
    char unaccessed[0xD8];
    InterceptCoefficient *coefficient;
};
struct InterceptContext { InterceptOwner *owner; };
extern "C" {
int func_0011EA28(float a, float b, float c, float *roots);
int func_001BB188(InterceptContext *context, qword first, qword velocity,
    qword second, qword second_velocity, float *output)
{
    float roots[2];
    int count = func_0011EA28(context->owner->coefficient->coefficient * 0.5f,
        PackedVectorZ(velocity) - PackedVectorZ(second_velocity),
        PackedVectorZ(first) - PackedVectorZ(second), roots);
    if (count <= 0) return 0;
    {
        float root = roots[count - 1];
        if (root <= 0.0f) return 0;
        *output = root;
    }
    return 1;
}
}
