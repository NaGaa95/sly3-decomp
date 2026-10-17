// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
typedef int qword __attribute__((mode(TI)));
struct OrientEntry {
    short delta, pad;
    union { void *(*Query)(void *); qword (*Quad)(void *); void (*Apply)(void *, qword); };
};
struct OrientPath { unsigned char prefix[0x64]; float value; };
struct OrientState { unsigned char prefix[0x14]; OrientPath *path; unsigned char gap18[4]; float limit; };
struct OrientActor {
    unsigned char prefix[0xC];
    OrientEntry *vtable;
    unsigned char gap10[0x112C];
    OrientState *state;
};
struct OrientFollower {
    OrientActor *actor;
    int mode;
    int pad08;
    void *path;
    float parameter;
    int pad14;
    int reverse;
};
struct OrientRows { qword row[3]; };
union OrientFactor { qword q; float f[4]; };
extern float D_0036BB9C;
extern qword D_00317560;
extern "C" {
void func_001F32E8(void *path, float parameter, int reverse, void *output_frame);
void func_00118740(float lower, float step, float one, void *frame, qword quad, OrientRows *output, qword table,
                   OrientRows *rows, int zero);
void func_0011CFC0(OrientRows *output, void *frame, OrientRows *rows);
void func_0011D0B8(OrientRows *matrix, float *angle, qword *axis);
}
static inline qword OrientScalar(float value)
{
    qword scalar;
    asm("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}
static inline qword OrientScale(qword scalar, qword vector)
{
    qword result;
    asm("vmulx.xyzw %0,%2,%1x" : "=j"(result) : "j"(scalar), "j"(vector));
    return result;
}
static inline float OrientMax(float first, float second)
{
    float result;
    asm("max.s %0,%1,%2" : "=f"(result) : "f"(first), "f"(second));
    return result;
}
static inline void *ActorFrame(OrientActor *actor)
{
    OrientEntry *entry = &actor->vtable[36];
    return entry->Query((char *)actor + entry->delta);
}
extern "C" void func_001BEF88(OrientFollower *self)
{
    OrientRows frame;
    OrientRows rows;
    OrientRows matrix;
    qword axis[1];
    union { OrientRows basis; OrientFactor factor; } scratch;
    float angle;
    func_001F32E8(self->path, self->parameter, self->reverse == 0, &frame);
    if (self->mode == 0 || self->mode == 4) {
        OrientActor *actor = self->actor;
        float step = D_0036BB9C;
        float lower = actor->state->path->value - actor->state->limit;
        void *source;
        OrientEntry *entry;
        lower = step >? lower;
        source = ActorFrame(actor);
        entry = &self->actor->vtable[39];
        func_00118740(lower, step, 1.0f, source, entry->Quad((char *)self->actor + entry->delta), &frame, D_00317560,
                      &rows, 0);
    } else {
        rows = frame;
    }
    func_0011CFC0(&scratch.basis, ActorFrame(self->actor), &rows);
    matrix = scratch.basis;
    func_0011D0B8(&matrix, &angle, axis);
    {
        OrientEntry *entry = &self->actor->vtable[41];
        void (*apply)(void *, qword) = entry->Apply;
        void *target = (char *)self->actor + entry->delta;
        qword direction = axis[0];
        scratch.factor.q = OrientScalar(angle / D_0036BB9C);
        apply(target, OrientScale(scratch.factor.q, direction));
    }
}
