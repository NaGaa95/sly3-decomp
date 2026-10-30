// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; struct Matrix *(*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; unsigned char pad10[0x1C0 - 0x10]; qword dir; };
struct Self { qword pos; struct Object *target; int mode; };
extern qword D_00317560;
struct Object *func_001407B8(struct Self *self);
static inline struct Matrix *matrix_of(struct Object *object)
{
    struct Method *method = &object->methods[36];
    return method->call((unsigned char *)object + method->delta);
}
qword func_001407E8(struct Self *self)
{
    struct Object *o = func_001407B8(self);
    if (o)
        return matrix_of(o)->rows[3];
    switch (self->mode) {
    case 0: case 1:
        return self->pos;
    case -1: {
        qword base = matrix_of(self->target)->rows[3];
        U u;
        qword r;
        __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(125.0f));
        __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(base), "j"(self->target->dir), "j"(u.q));
        return r;
    }
    }
    return D_00317560;
}
