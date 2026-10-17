// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "state_position_ops.h"
struct FollowEntry {
    short delta, pad;
    union { void (*Simple)(void *); void *(*Query)(void *); };
};
struct FollowOwner { unsigned char prefix[0xC]; FollowEntry *vtable; };
struct FollowFrame { qword row[4]; };
struct FollowSource { unsigned char prefix[0x50]; void *node; };
struct FollowObject {
    unsigned char prefix00[0x18];
    float scale;
    FollowSource *source;
    unsigned char gap20[0x20];
    qword row0, row1, row2, position;
    unsigned char gap80[0x10];
    qword delta, offset;
    unsigned char gapB0[0x40];
    qword axis;
    float angle;
    FollowOwner *owner;
};
union FollowFactor { qword q; float f[4]; };
struct FollowBasis { qword row[3]; };
extern "C" {
void func_0028F680(void *a, void *b, float *m, float *n, float f);
void func_0011CFC0(FollowBasis *out, float *matrix, qword *rows);
void func_0011D0B8(FollowBasis *matrix, float *angle, qword *axis);
}
static inline qword FollowScalar(float value)
{
    qword scalar;
    asm("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}
static inline qword FollowBlend(qword base, qword first, qword add, qword second)
{
    qword result;
    asm("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x"
        : "=j"(result) : "j"(base), "j"(first), "j"(add), "j"(second));
    return result;
}
static inline FollowFrame *OwnerFrame(FollowOwner *owner)
{
    FollowEntry *entry = &owner->vtable[36];
    return (FollowFrame *)entry->Query((char *)owner + entry->delta);
}
extern "C" void func_0020D3A0(FollowObject *self)
{
    float matrix[16] __attribute__((aligned(16)));
    FollowFactor factor;
    FollowBasis basis;
    self->position = OwnerFrame(self->owner)->row[3];
    {
        FollowFrame *frame = OwnerFrame(self->owner);
        self->row0 = frame->row[0];
        self->row1 = frame->row[1];
        self->row2 = frame->row[2];
    }
    func_0028F680(self->source->node, 0, matrix, 0, self->scale);
    {
        qword difference = PackedDifference(*(qword *)&matrix[12], self->position);
        qword first, second;
        factor.q = FollowScalar(1.0f / self->scale);
        first = factor.q;
        factor.q = FollowScalar(self->scale * -0.5f);
        second = factor.q;
        self->delta = FollowBlend(difference, first, self->offset, second);
    }
    func_0011CFC0(&basis, matrix, &self->row0);
    func_0011D0B8(&basis, &self->angle, &self->axis);
    if (self->angle > 0.0f)
        self->angle = self->angle + 6.2831855f;
    else
        self->angle = self->angle - 6.2831855f;
    {
        FollowEntry *entry = &self->owner->vtable[9];
        entry->Simple((char *)self->owner + entry->delta);
    }
    self->owner = 0;
}
