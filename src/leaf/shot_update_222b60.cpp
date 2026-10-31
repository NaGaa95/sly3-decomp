// Per-frame update of a homing shot: expire it at its end time, otherwise ease its offset towards the target position.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
struct VEntry { short delta; short pad; M4 *(*method)(void *); };
struct Target { char pad0[0xC]; VEntry *table; };
struct Shot {
    char pad00[0x30];
    void *owner;
    float started;
    float expires;
    char pad3C[4];
    Target *target;
    char pad44[0xC];
    qword position;
    qword offset;
};
struct Clock { float now, step; };
extern Clock D_0036BB98;
extern "C" void func_0021DD20(Shot *shot);
extern "C" void func_00222CD8(Shot *shot);
extern "C" qword func_00222890(Shot *shot, qword position);
extern "C" void func_00222AD8(Shot *shot);

union Factor { qword q; float f[4]; };
static inline qword Scalar(float value)
{
    qword scalar;
    asm("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}
static inline qword Add(qword a, qword b)
{
    qword r;
    asm("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Blend(qword a, qword as, qword b, qword bs)
{
    qword r;
    asm("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x" : "=j"(r) : "j"(a), "j"(as), "j"(b), "j"(bs));
    return r;
}
static inline M4 *Matrix(Target *object)
{
    VEntry *entry = &object->table[36];
    return entry->method((char *)object + entry->delta);
}

extern "C" void func_00222B60(Shot *shot)
{
    Factor factor;
    func_0021DD20(shot);
    if (!shot->target) return;
    if (shot->expires <= D_0036BB98.now) {
        func_00222CD8(shot);
        return;
    }
    {
        qword goal = func_00222890(shot, Add(Matrix(shot->target)->r[3], shot->position));
        float t = D_0036BB98.step / (shot->expires - D_0036BB98.now);
        t = t <? 1.0f;
        factor.q = Scalar(1.0f - t);
        qword rest = factor.q;
        factor.q = Scalar(t);
        qword tq = factor.q;
        shot->offset = Blend(shot->offset, rest, goal, tq);
    }
    func_00222AD8(shot);
}
