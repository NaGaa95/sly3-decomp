// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
typedef struct { qword r[3]; } M3;
typedef struct { qword r[4]; } M4;
typedef struct VirtualEntry { short adjustment; short reserved; M4 *(*call)(); } VirtualEntry;
struct Obj { unsigned char opaque0[12]; VirtualEntry *vtable; };
struct Self {
    unsigned char opaque0[12]; VirtualEntry *vtable;
    unsigned char pad10[0x1A0 - 0x10]; qword push; unsigned char pad1B0[0x10]; unsigned char frame[0x11B4 - 0x1C0];
    struct Obj *target;
};
struct Spring { float max; int pad; float damping; int pad2; };
struct Clock { float t; float dt; };
extern struct Clock g_clock;
extern qword D_00317530;
void func_0024E8E8(struct Self *self, qword dir);
void func_0011E598(const struct Spring *spring, int *out, float x, float range, float dt);
void func_0011C6F8(M3 *out, void *frame);
static inline M4 *Matrix(void *object)
{
    VirtualEntry *entry = &((struct Obj *)object)->vtable[36];
    return ((M4 *(*)(void *))entry->call)((char *)object + entry->adjustment);
}
static inline qword Dot3(qword a, qword b)
{
    qword product, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        : "=j"(product), "=&j"(one) : "j"(a), "j"(b));
    return product;
}
static inline qword SqrtX(qword value)
{
    qword root;
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(root) : "j"(value));
    return root;
}
static __inline__ float GetLength(qword q) { float x; __asm__("qmfc2.ni %0,%1" : "=r"(x) : "j"(q)); return x; }
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
void func_001AFF00(struct Self *self)
{
    static const struct Spring spring = { 1000.0f, 0, 0.5f, 0 };
    U n;
    M3 scaled;
    M3 m;
    U s;
    int k; /* float result, moved to VU as raw bits */
    qword pos, d, length;
    float dist;
    const qword *fallback;
    pos = Matrix(self->target)->r[3];
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(d) : "j"(pos), "j"(Matrix(self)->r[3]));
    fallback = &D_00317530;
    n.q = d;
    length = SqrtX(Dot3(d, d));
    if (GetX(length) < 1.0e-4f) {
        n.q = *fallback;
    } else {
        __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(n.q) : "j"(length), "j"(n.q));
    }
    dist = GetLength(length);
    func_0024E8E8(self, n.q);
    func_0011E598(&spring, &k, dist, 200.0f, g_clock.dt * 0.5f);
    func_0011C6F8(&m, self->frame);
    { register int kk __asm__("$3") = k; /* the one register pin */ __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(kk)); }
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(scaled.r[0]) : "j"(m.r[0]), "j"(s.q));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(scaled.r[1]) : "j"(m.r[1]), "j"(s.q));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(scaled.r[2]) : "j"(m.r[2]), "j"(s.q));
    __asm__("vmulax.xyz $ACC,%2,%1x\n\tvmadday.xyz $ACC,%3,%1y\n\tvmaddz.xyz %0,%4,%1z"
        : "=j"(self->push) : "j"(n.q), "j"(scaled.r[0]), "j"(scaled.r[1]), "j"(scaled.r[2]));
}
