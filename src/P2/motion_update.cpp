// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "vector_intrinsics.h"
struct MotionRuntimeView {
    unsigned char prefix[0x80];
    qword vector;
    unsigned char toParameters[0x20];
    unsigned char parameters[0x10];
    int mode;
};
struct MotionUpdateView {
    unsigned char prefix[0x48];
    void *owner;
    unsigned char toRuntime[0xD8 - 0x4C];
    MotionRuntimeView *runtime;
    unsigned char toRecords[0x110 - 0xDC];
    void *records;
};
extern qword D_00317560;
extern "C" int func_0011E9F0(float, float, float);
extern "C" qword func_00244418(void *, void *, qword);
extern "C" void func_00244828(void *, qword);
extern "C" void func_00281250(void *);
static inline int MotionNear(qword first, qword second)
{
    return func_0011E9F0(PackedVectorX(first), PackedVectorX(second), 0.0001f) &&
           func_0011E9F0(PackedVectorY(first), PackedVectorY(second), 0.0001f) &&
           func_0011E9F0(PackedVectorZ(first), PackedVectorZ(second), 0.0001f);
}
extern "C" void func_00243738(void *receiver)
{
    MotionUpdateView *state = (MotionUpdateView *)receiver;
    int update = 0;
    int near = MotionNear(D_00317560, state->runtime->vector);
    if (!near)
        update = state->runtime->mode != 3;
    if (update)
        func_00244828(state, func_00244418(state->runtime->parameters,
                                        state->owner, state->runtime->vector));
    if (state->records)
        func_00281250(state);
}
