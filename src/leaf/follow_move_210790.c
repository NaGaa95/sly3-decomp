// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Follower update: turn the heading toward the owner's facing, project the owner origin along the heading by its horizontal speed and move the follower to it.
typedef int qword __attribute__((mode(TI)));
struct VirtualEntry { short adjustment; short reserved; void *call; };
struct Smoother { float state[3]; };
struct Owner {
    unsigned char pad0[0xC];
    struct VirtualEntry *vtable;
    unsigned char pad10[0x290 - 0x10];
    qword origin;
    union { qword q; float f[4]; } velocity;
    float turnRate;
    struct Smoother smoother;
};
struct World { unsigned char pad0[0x11C]; float turnRate; };
struct Self {
    struct World *world;
    unsigned char pad4[0x20 - 4];
    struct Owner *owner;
    float heading;
    unsigned char pad28[0x30 - 0x28];
    qword position;
};
struct CLOCK { float t; float dt; };
extern struct CLOCK D_0036BB98;
void func_00169E78(struct Self *self);
qword func_0011D3C0(void *matrix);
float func_0011E840(float current, float target, float dt, struct Smoother *smoother, float *rate);
qword func_001C9428(void *object, int zero, qword v);
qword func_0011FD70(float a, float b, float c);
qword func_00167660(struct World *world, qword from, qword to, int flags);
void func_00166E48(struct World *world, qword position, qword origin, float a, float b);
#define MATRIX(object) (((void *(*)(void *))(object)->vtable[36].call)((char *)(object) + (object)->vtable[36].adjustment))
static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword LenXY(qword v)
{
    qword d, l;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(d) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
void func_00210790(struct Self *self)
{
    qword origin;
    qword target;
    func_00169E78(self);
    self->world->turnRate = self->owner->turnRate;
    self->heading = func_0011E840(self->heading, GetZ(func_0011D3C0(MATRIX(self->owner))) + 3.14159265f, D_0036BB98.dt, &self->owner->smoother, 0);
    origin = func_001C9428(self->owner, 0, self->owner->origin);
    target = Add(origin, func_0011FD70(self->heading, F(LenXY(self->owner->velocity.q)), self->owner->velocity.f[2]));
    self->position = func_00167660(self->world, self->position, target, 0);
    func_00166E48(self->world, self->position, origin, 0.0f, 0.0f);
}
