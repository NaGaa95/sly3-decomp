// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001A6B78 (A28/A32 wip 6b78_d + A34: XY length split [vmul,vaddy]|[vsqrt] with untied input, limit added at the compare, if/return 1/return 0).
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[4]; } M4;
typedef struct VirtualEntry { short adjustment; short reserved; M4 *(*call)(); } VirtualEntry;
struct Obj {
    unsigned char opaque0[12]; VirtualEntry *vtable;
    unsigned char pad10[0x1014 - 0x10]; struct Obj *target; int mode;
    unsigned char pad101C[0x1144 - 0x101C]; int flags;
};
struct Self { unsigned char pad0[0x10]; struct Obj *owner; };
qword func_001A6CA8(struct Self *self);
static inline M4 *Matrix(struct Obj *object)
{
    VirtualEntry *entry = &object->vtable[36];
    return ((M4 *(*)(void *))entry->call)((char *)object + entry->adjustment);
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Sub2(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%2,%1" : "=j"(r) : "j"(b), "j"(a)); return r; }
static inline qword LengthXY(qword v)
{
    qword r;
    qword s;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(s) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(r) : "j"(s));
    return r;
}
static inline qword ToVf(qword v) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(v)); return r; }
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
int func_001A6B78(struct Self *self)
{
    struct Obj *owner = self->owner;
    struct Obj *target;
    float dist;
    if (!(owner->flags & 2) || owner->mode == 2) return 1;
    target = owner->target;
    if (!target) return 0;
    {
        qword pos = Matrix(target)->r[3];
        dist = GetX(LengthXY(Sub(pos, Matrix(self->owner)->r[3])));
    }
    {
        qword pos = ToVf(func_001A6CA8(self));
        float g = GetX(LengthXY(Sub(pos, Matrix(self->owner)->r[3])));
        if (g < dist + 50.0f) return 1;
        return 0;
    }
}
