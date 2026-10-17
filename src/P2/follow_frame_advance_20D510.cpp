// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "rotation_matrix_intrinsics.h"
#include "state_position_ops.h"
struct AdvanceSource { unsigned char prefix[0x50]; void *node; };
struct AdvanceObject {
    unsigned char prefix00[0x14];
    float time;
    float period;
    AdvanceSource *source;
    unsigned char gap20[0x20];
    ROTATION_MATRIX rotation;
    qword position, previous, velocity, offset;
    unsigned char gapB0[0x40];
    qword axis;
    float rate;
};
union AdvanceFactor { qword q; float f[4]; };
struct AdvanceClock { float now, step; };
extern AdvanceClock D_0036BB98;
extern "C" {
void func_0028F680(void *a, void *b, float *m, float *n, float f);
void func_00118558(float lower, float step, float one, qword position, qword velocity, qword target, qword blended,
                   qword *position_out, qword *velocity_out, qword *extra_out);
MATRIX3 *func_0011C8C0(MATRIX3 *matrix, float angle, qword axis);
}
static inline qword AdvanceScalar(float value)
{
    qword scalar;
    asm("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}
static inline qword AdvanceScale(qword vector, qword scalar)
{
    qword result;
    asm("vmulx.xyzw %0,%1,%2x" : "=j"(result) : "j"(vector), "j"(scalar));
    return result;
}
static inline qword AdvanceBlend(qword first, qword first_scale, qword second, qword second_scale, qword third,
                                 qword third_scale)
{
    qword result;
    asm("vmulax.xyzw $ACC,%1,%2x\n\tvmaddax.xyzw $ACC,%3,%4x\n\tvmaddx.xyzw %0,%5,%6x"
        : "=j"(result) : "j"(first), "j"(first_scale), "j"(second), "j"(second_scale), "j"(third),
          "j"(third_scale));
    return result;
}
extern "C" void func_0020D510(AdvanceObject *self)
{
    float matrix[16] __attribute__((aligned(16)));
    AdvanceFactor factor;
    ROTATION_MATRIX turn;
    ROTATION_MATRIX rotated;
    float lower;
    if (D_0036BB98.now < self->time)
        return;
    self->previous = self->position;
    lower = self->time + self->period - D_0036BB98.now;
    lower = D_0036BB98.step >? lower;
    func_0028F680(self->source->node, 0, matrix, 0, lower);
    {
        qword first, second, third, fourth;
        qword target = *(qword *)&matrix[12];
        qword difference, scaled, blended;
        factor.q = AdvanceScalar(1.5f / lower);
        first = factor.q;
        factor.q = AdvanceScalar(-0.5f);
        second = factor.q;
        factor.q = AdvanceScalar(0.25f);
        third = factor.q;
        factor.q = AdvanceScalar(lower);
        fourth = factor.q;
        difference = PackedDifference(target, self->position);
        scaled = AdvanceScale(self->offset, fourth);
        blended = AdvanceBlend(difference, first, self->velocity, second, scaled, third);
        func_00118558(lower, D_0036BB98.step, 1.0f, self->position, self->velocity, target, blended,
                      &self->position, &self->velocity, 0);
    }
    func_0011C8C0((MATRIX3 *)&turn, self->rate * lower / self->period, self->axis);
    MultiplyRotation(&rotated, &turn, (ROTATION_MATRIX *)matrix);
    self->rotation = rotated;
}
