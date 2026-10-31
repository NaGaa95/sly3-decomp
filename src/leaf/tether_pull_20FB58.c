// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Spring-like pull: when the follower is farther than the limit from the anchor, push the offset back with a distance-scaled impulse.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } UQ;
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct Body { unsigned char pad0[0xC]; struct VTE *vtable; };
struct Tether {
    unsigned char prefix0[0x1D8];
    struct Body *anchor;
    struct Body *follower;
    float limit;
    float stiffness;
    float damping;
};
void func_00244828(struct Tether *self, qword impulse);
static inline qword Position(struct Body *b)
{
    struct VTE *e = &b->vtable[36];
    return ((struct M4 *(*)(void *))e->pfn)((char *)b + e->d)->r[3];
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Length(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(d));
    return d;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline qword Qmtc2(float g)
{
    qword v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v) : "r"(g));
    return v;
}
static inline qword ScaleX(qword v, qword s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s));
    return r;
}
void func_0020FB58(struct Tether *self)
{
    qword followerPos, d;
    float len;
    UQ s;
    if (!self->anchor)
        return;
    if (!self->follower)
        return;
    followerPos = Position(self->follower);
    d = Sub(followerPos, Position(self->anchor));
    len = F(Length(d));
    if (len <= self->limit)
        return;
    s.q = Qmtc2(self->stiffness * (1.0f - self->limit / len) + self->damping / len);
    func_00244828(self, ScaleX(d, s.q));
}
