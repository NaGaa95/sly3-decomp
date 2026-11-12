// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Spinner update: damp the spin vector, rotate the basis by |spin|*dt around the spin axis, then move the position by
// the transformed velocity. Rotate() writes each rotated column to the caller's matrix and to its own copy; the order
// of the two writes per column reproduces the original order of the dead stack stores.
typedef int qword __attribute__((mode(TI)));

union UQ { qword q; float f[4]; };
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct Clock { float t; float dt; };
struct Spinner {
    unsigned char pad0[0x40];
    M3 basis;
    qword position;
    qword lastPosition;
    qword velocity;
    qword turn;
    unsigned char padB0[0xD0 - 0xB0];
    qword spin;
    float damping;
};
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
};
struct VU_FLOATM {
    qword q;
    VU_FLOATM(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "rV"(*(int *)&f)); }
};
extern "C" {
extern Clock D_0036BB98;
int func_0020BF18(qword v);
int func_0020BED0(qword v);
int func_0020BF60(qword v);
M3 func_0011C8C0(qword axis, float angle);
M4 func_00179CC0(qword *turn);
}
static inline qword Scale(qword v, VU_FLOAT s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s.q), "j"(v));
    return r;
}
static inline qword Length(qword a)
{
    qword t, one, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
        : "=&j"(t), "=&j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(t));
    return r;
}
static inline qword DivQ(qword v, VU_FLOAT f)
{
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(f.q));
    return r;
}
static inline qword AddScaled(qword a, qword v, VU_FLOATM f)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(v), "j"(f.q));
    return r;
}
static inline qword MulM3(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %2x\n\tvmadday.xyz $ACC, %3, %2y\n\tvmaddz.xyz %0, %4, %2z"
        : "=j"(r) : "j"(m.r[0]), "j"(v), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
static inline qword XformPoint(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline void Rotate(M3 *out, const M3 &rot, const M3 &m)
{
    M3 r;
    out->r[0] = MulM3(rot, m.r[0]); r.r[0] = out->r[0];
    out->r[1] = MulM3(rot, m.r[1]); r.r[1] = out->r[1];
    r.r[2] = MulM3(rot, m.r[2]); out->r[2] = r.r[2];
}
extern "C" void func_0020BFA8(Spinner *self)
{
    if (!func_0020BF18(self->spin)) {
        float len;
        self->spin = Scale(self->spin, VU_FLOAT(self->damping * D_0036BB98.dt + 1.0f));
        len = F(Length(self->spin));
        if (0.0001f < len) {
            UQ axis;
            axis.q = DivQ(self->spin, VU_FLOAT(len));
            M3 t;
            Rotate(&t, func_0011C8C0(axis.q, len * D_0036BB98.dt), self->basis);
            self->basis = t;
        }
    }
    self->lastPosition = self->position;
    int moved = !func_0020BED0(self->velocity) || !func_0020BF60(self->turn);
    if (moved) {
        self->velocity = XformPoint(func_00179CC0(&self->turn), self->velocity);
        self->position = AddScaled(self->position, self->velocity, VU_FLOATM(D_0036BB98.dt));
    }
}
