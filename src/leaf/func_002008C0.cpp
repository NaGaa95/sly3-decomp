// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sets up the runtime of a particle program: the polynomial coefficients of the speed curve (peak value over [0, g]),
// the basis vectors and, when the owner changed, its sound handle; finishes with func_001FF010.
typedef int qword __attribute__((mode(TI)));
struct Phase { int pad0, count; };
struct Program {
    unsigned char pad0[0x10]; int soundId; unsigned char pad14[8]; float duration; Phase *phase; int pad24;
    int fixed; unsigned char pad2C[2]; unsigned short pending;
};
struct Shape {
    qword origin; qword axis; float v20[4]; float v30[4];
    unsigned char pad40[0x68 - 0x40]; float f68; unsigned char pad6C[4]; float f70; unsigned char pad74[4]; float g;
    unsigned char pad7C[6]; unsigned short enabled;
};
struct Owner { unsigned char pad0[0x10]; int id; };
struct Type { unsigned char pad0[0x14]; Shape *shape; unsigned char pad18[4]; Program *program; };
struct Emitter {
    Owner *owner; Type *type; unsigned char pad8[0x60 - 8]; int sound; unsigned char pad64[0x70 - 0x64];
    float c0, c1, c2; unsigned char pad7C[4]; float peak; unsigned char pad84[0x90 - 0x84];
    float velocity[4]; unsigned char padA0[4]; float ratio; unsigned char padA8[0xB0 - 0xA8];
    float axis[4]; qword origin; qword direction; float spin0, spin1;
};
extern "C" {
extern qword D_00317550;
extern char D_00475480[];
void func_0011EAD0(const float *in, float scale, float z, float *out);
void func_001FF010(Emitter *, int);
int func_0017E1B8(void *, int, int, int);
}
static inline qword Length(qword v)
{
    qword d, one, len;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(len) : "j"(d));
    return len;
}
static inline float X(qword q) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(q)); return f; }
static inline qword Unit(qword v, qword len)
{
    qword r;
    __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(len));
    return r;
}
static inline qword Normalize(qword v, qword fallback)
{
    qword len = Length(v);
    if (X(len) < 0.0001f)
        return fallback;
    return Unit(v, len);
}
extern "C" void func_002008C0(Emitter *self, int flag)
{
    Type *type = self->type;
    Program *prog = type->program;
    Shape *shape = type->shape;
    Phase *phase = prog->phase;
    if (!flag || shape->enabled) {
        if (phase->count >= 2 && prog->duration == 0.0f)
            self->ratio = (float)phase->count / shape->g;
        float *coef = &self->c0;
        func_0011EAD0(shape->v30, 1.0f / shape->g, 0.0f, self->velocity);
        func_0011EAD0(shape->v20, 1.0f / shape->g, 0.0f, coef);
        float peak;
        if (self->c1 == 0.0f && self->c2 == 0.0f) {
            peak = __builtin_fabsf(self->c0);
            self->peak = peak;
        } else {
            float v[3];
            v[0] = self->c0;
            v[1] = 0.0f;
            v[2] = self->c0 + shape->g * (coef[1] + shape->g * coef[2]);
            if (self->c2 != v[1]) {
                float t = -self->c1 / (self->c2 + self->c2);
                if (v[1] < t && t < shape->g)
                    v[1] = self->c0 + t * (coef[1] + t * coef[2]);
            }
            float a = __builtin_fabsf(v[0]);
            float b = __builtin_fabsf(v[1]);
            float c = __builtin_fabsf(v[2]);
            if (b < a && c < a)
                peak = a;
            else if (c < b)
                peak = b;
            else
                peak = c;
            self->peak = peak;
        }
        float *axis = self->axis;
        float inv = 1.0f / shape->g;
        axis[0] = 0.0f;
        axis[2] = 0.0f;
        axis[1] = inv;
        if (!prog->fixed) {
            self->origin = shape->origin;
            qword *dir = &self->direction;
            *dir = Normalize(shape->axis, D_00317550);
            self->spin0 = shape->f70;
            self->spin1 = shape->f68;
        }
    }
    func_001FF010(self, flag);
    if (!flag || prog->pending) {
        int ownerId = self->owner->id;
        if (prog->soundId != -1)
            self->sound = func_0017E1B8(D_00475480, 4, prog->soundId, ownerId);
        if (phase->count >= 2 && 0.0f < prog->duration)
            self->ratio = (float)phase->count / prog->duration;
        prog->pending = 0;
    }
}
