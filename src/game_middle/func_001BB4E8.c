// SLY3_AS: gnu-2.9
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Minimum reach required for a move of the given kind: fixed distances, a quadratic in the vertical velocity,
// or the owner's reach function; the result raises the vertical velocity component and the vector is returned.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Params { unsigned char pad0[0x88]; float coefficient; };
struct Other { unsigned char pad0[0x80]; float height; };
struct Owner {
    unsigned char pad0[0xC]; struct Method *table;
    unsigned char pad10[0xD8 - 0x10]; struct Params *params;
    unsigned char padDC[0x10DC - 0xDC]; struct Other *other;
};
struct Self { struct Owner *owner; unsigned char pad4[0x28 - 4]; int index; };
struct Poly { float c0, c1, c2; };
struct Range { float min, max; };
typedef union { qword q; float f[4]; } Vector;
struct Motion { qword position; Vector velocity; };
extern const struct Poly D_00323240;
extern const struct Range D_00323250;
extern const float D_00323258[];
extern float D_003457A8;
float func_00250418(struct Owner *owner, float offset, float gravity);
float func_002504B0(struct Owner *owner, float a, float b, float c);
static inline float maxf(float a, float b) { return a > b ? a : b; }
static inline float GLimit(float g, float gMin, float gMax)
{
    float r;
    if (g < gMin)
        r = gMin;
    else if (gMax < g)
        r = gMax;
    else
        r = g;
    return r;
}
qword func_001BB4E8(struct Self *self, int kind)
{
    struct Motion motion;
    float required;
    float coefficient;
    {
        struct Method *method = &self->owner->table[36];
        motion.position = ((qword *(*)(void *))method->function)((char *)self->owner + method->adjustment)[3];
    }
    {
        struct Method *method = &self->owner->table[38];
        motion.velocity.q = ((qword (*)(void *))method->function)((char *)self->owner + method->adjustment);
    }
    coefficient = self->owner->params->coefficient;
    switch (kind) {
    case 2:
        required = 700.0f;
        break;
    case 3:
        required = 800.0f;
        break;
    case 1: case 7: case 9: case 13: case 14: case 16: case 17: case 18: {
        float offset;
        switch (kind) {
        case 9: offset = 1200.0f; break;
        case 13: offset = 250.0f; break;
        case 16: case 17: offset = 150.0f; break;
        case 18: offset = self->owner->other->height; break;
        default: offset = D_003457A8; break;
        }
        required = func_00250418(self->owner, offset, coefficient);
        break;
    }
    case 4: {
        float z = motion.velocity.f[2];
        required = D_00323240.c0 + z * (D_00323240.c1 + z * D_00323240.c2);
        required = GLimit(required, D_00323250.min, D_00323250.max);
        break;
    }
    case 6:
        required = func_002504B0(self->owner, D_003457A8, D_00323258[self->index], self->owner->params->coefficient);
        break;
    default:
        required = motion.velocity.f[2];
        break;
    }
    motion.velocity.f[2] = maxf(motion.velocity.f[2], required);
    return motion.velocity.q;
}
