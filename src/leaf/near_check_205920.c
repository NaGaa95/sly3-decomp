// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } UQ;
struct VirtualEntry { short adjustment; short reserved; qword (*call)(void *); };
struct Probe {
    unsigned char pad0[0xC];
    struct VirtualEntry *vtable;
    unsigned char pad10[0x33C - 0x10];
    float weight;
};
int func_002058D8(struct Probe *self);
int func_00205888(struct Probe *self);
int func_00205A38(struct Probe *self);
static inline qword Length(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    return d;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
// True when the object is close (50 units) and either its weight-limited counter is below 4 or its second offset vector stays within 6 units on x and y.
int func_00205920(struct Probe *self)
{
    UQ v;
    if (func_002058D8(self))
        return 0;
    if (50.0f < F(Length(self->vtable[38].call((char *)self + self->vtable[38].adjustment))))
        return 0;
    if (func_00205888(self)) {
        if (self->weight != 0.0f && func_00205A38(self) < 4)
            return 1;
    } else {
        v.q = self->vtable[39].call((char *)self + self->vtable[39].adjustment);
        if (__builtin_fabsf(v.f[0]) < 6.0f && __builtin_fabsf(v.f[1]) < 6.0f)
            return 1;
    }
    return 0;
}
