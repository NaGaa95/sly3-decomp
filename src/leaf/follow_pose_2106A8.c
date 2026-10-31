// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VirtualEntry { short adjustment; short reserved; void *call; };
struct Owner {
    unsigned char pad0[0xC];
    struct VirtualEntry *vtable;
    unsigned char pad10[0x290 - 0x10];
    qword origin;
    union { qword q; float f[4]; } velocity;
};
struct Self {
    unsigned char pad0[0x20];
    struct Owner *owner;
    float heading;
    unsigned char pad28[0x30 - 0x28];
    qword position;
};
void func_00169E28(struct Self *self);
qword func_0011D3C0(void *matrix);
qword func_001C9428(void *object, int zero, qword v);
qword func_0011FD70(float a, float b, float c);
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
void func_002106A8(struct Self *self)
{
    qword base;
    func_00169E28(self);
    self->heading = GetZ(func_0011D3C0(MATRIX(self->owner))) + 3.14159265f;
    base = func_001C9428(self->owner, 0, self->owner->origin);
    self->position = Add(base, func_0011FD70(self->heading, F(LenXY(self->owner->velocity.q)), self->owner->velocity.f[2]));
}
