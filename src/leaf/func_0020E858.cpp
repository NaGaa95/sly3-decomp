// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Runs func_0020C470 with the anchor frame temporarily moved: the frame (basis rows + origin) is saved, expressed in the
// owner's world matrix (identity matrices when there is no world), checked against the anchor radius (too far from the
// first block's point -> func_0020E5F0), shifted by the first block's offset and, with three blocks, re-oriented by the
// basis built from the cross product of the two block edges; afterwards the saved frame is restored.
typedef int qword __attribute__((mode(TI)));
union UQ { qword q; float f[4]; };
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct VirtualEntry { short adjustment; short reserved; M4 *(*call)(void *); };
struct World { unsigned char pad0[0xC]; VirtualEntry *vtable; };
struct Owner { unsigned char pad0[0x60]; World *world; };
struct Anchors {
    unsigned char pad0[0x10];
    Owner *owner;
    unsigned char pad14[0x40 - 0x14];
    M3 basis;
    qword origin;
    unsigned char pad80[0xF0 - 0x80];
    void *handle;
    float radius;
    int count;
    void *blocks[3];
};
extern qword D_00317550;
extern qword D_00325AD0[2];
extern "C" {
void *func_00292034(void *pv, int n, int cb);
M4 func_0011D768(M4 *pm);
M3 func_0011CDC8(qword a, qword b);
void *func_002BC400(qword *out, void *source);
qword func_00289D68(void *handle, void *block);
void func_0020E5F0(Anchors *self);
void func_0020C470(Anchors *self, int a1, void *a2);
}
static inline qword XformPoint(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline qword XformVector(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %2x\n\tvmadday.xyz $ACC, %3, %2y\n\tvmaddz.xyz %0, %4, %2z"
            : "=j"(r) : "j"(m.r[0]), "j"(v), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Add(qword a, qword b)
{
    qword r;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float GetX(qword q)
{
    float g;
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q));
    return g;
}
// rows of the product a * b (rotation part of a applied to the rows of b)
static inline M3 operator*(const M4 &a, const M3 &b) return r
{
    qword a0 = a.r[0], a1 = a.r[1], a2 = a.r[2];
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[0]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[0]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[1]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[1]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[2]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[2]));
}
static inline M3 operator*(const M3 &a, const M4 &b) return r
{
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[0]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[0]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[1]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[1]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[2]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[2]));
}
static inline void Identity(M4 *m)
{
    float *f = (float *)m;
    func_00292034(m, 0, 0x40);
    f[0] = f[5] = f[10] = f[15] = 1.0f;
}
extern "C" void func_0020E858(Anchors *self, int a1, void *a2)
{
    M3 saved = self->basis;
    qword savedOrigin = self->origin;
    M4 m, inv;
    World *w = self->owner->world;
    if (w) {
        m = *w->vtable[36].call((char *)w + w->vtable[36].adjustment);
        inv = func_0011D768(&m);
    } else {
        Identity(&m);
        Identity(&inv);
    }
    if (self->radius >= 0.0f) {
        qword p = XformPoint(m, self->origin);
        UQ far;
        func_002BC400(&far.q, self->blocks[0]);
        qword d = Sub(p, far.q);
        float r2 = self->radius * self->radius;
        int outside = r2 < GetX(Dot(d, d));
        if (outside)
            func_0020E5F0(self);
    }
    if (self->handle) {
        qword q1 = func_00289D68(self->handle, self->blocks[0]);
        M4 *pinv = &inv;
        self->origin = Add(self->origin, XformVector(*pinv, q1));
        if (self->count == 3) {
            qword q2 = func_00289D68(self->handle, self->blocks[1]);
            qword q3 = func_00289D68(self->handle, self->blocks[2]);
            qword e2 = Add(Sub(q2, q1), D_00325AD0[0]);
            qword e3 = Add(Sub(q3, q1), D_00325AD0[1]);
            M3 b;
            b = func_0011CDC8(D_00317550, Cross(e2, e3));
            M4 *pm = &m;
            self->basis = (*pinv * b) * *pm;
        }
    }
    func_0020C470(self, a1, a2);
    self->origin = savedOrigin;
    self->basis = saved;
}
