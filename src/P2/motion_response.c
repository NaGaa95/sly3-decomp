// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "common.h"

typedef union { qword q; float f; } U;
struct MotionResponsePair { qword linear, angular; };
struct MotionResponseItem {
    unsigned char beforePoint[0x10];
    qword point;
    unsigned char tail[0x20];
};
struct MotionResponseWork {
    struct MotionResponsePair responses[2];
    qword impulse;
    struct MotionResponseItem *items;
};
struct MotionResponseRuntime {
    unsigned char beforeAngularMode[0xA0];
    int angularMode;
    unsigned char beforeLinearMode[0xC0 - 0xA4];
    int linearMode;
};
struct MotionResponseOwner {
    unsigned char beforeRuntime[0xD8];
    struct MotionResponseRuntime *runtime;
};

qword func_002445E8(void *, qword);
qword func_00244630(void *, qword, qword);

static inline qword Mulx(qword a, float g)
{
    U s;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(g));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q));
    return r;
}

void func_002448F8(struct MotionResponseOwner *owner, int unusedFirst,
    struct MotionResponseWork *work, int unusedSecond, int side)
{
    struct MotionResponseRuntime *runtime = owner->runtime;
    qword impulse;
    struct MotionResponsePair *response;
    if (!runtime) return;
    impulse = work->impulse;
    if (side) impulse = Mulx(impulse, -1.0f);
    response = &work->responses[side];
    if (runtime->linearMode != 3)
        response->linear = func_002445E8(owner, impulse);
    if (runtime->angularMode != 3)
        response->angular = func_00244630(owner, work->items[side].point, impulse);
}
