// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } UQ;
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct VirtualEntry { short adjustment; short reserved; struct M4 *(*call)(void *); };
struct World { unsigned char pad0[0xC]; struct VirtualEntry *vtable; };
struct Curve { float c0, c1, c2, unused; };
struct FrameSource {
    unsigned char pad0[0x20];
    struct Curve curveB;
    struct Curve curveA;
    unsigned char pad40[0x70 - 0x40];
    qword position;
    unsigned char pad80[0x90 - 0x80];
    qword direction;
    unsigned char padA0[0xF4 - 0xA0];
    int flipUp;
};
struct FrameOut {
    qword position;
    struct M3 basis;
    float valueA;
    float valueB;
};
struct LM { float gMin, gMax; };
extern struct LM D_00341FF0;
extern qword D_00317550;
extern char D_00475480[];
struct World *func_00165B28(void *pg);
struct M3 func_0011CBF0(qword forward, qword up);
static inline float Eval(const struct Curve *c, float t) { return c->c0 + t * (c->c1 + t * c->c2); }
static inline float GClamp(float g, float lo, float hi)
{
    float r;
    if (g < lo)
        r = lo;
    else if (hi < g)
        r = hi;
    else
        r = g;
    return r;
}
static inline qword XformPoint(const struct M4 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(r) : "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(m->r[3]), "j"(v));
    return r;
}
static inline qword XformDir(const struct M4 *m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r) : "j"(m->r[0]), "j"(m->r[1]), "j"(m->r[2]), "j"(v));
    return r;
}
static inline qword ScaleX(qword v, qword s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s));
    return r;
}
static __inline__ qword Qmtc2(float g)
{
    qword v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v) : "r"(g));
    return v;
}
// Build the render frame for a source: transformed position, an orthonormal basis from its transformed direction and an up vector (optionally flipped),
// plus a limited and an unlimited curve value at time t.
void func_0020C760(struct FrameSource *self, struct M4 *m, float t, struct FrameOut *out)
{
    struct World *world = func_00165B28(D_00475480);
    qword up;
    if (self->flipUp) {
        UQ s;
        qword row = world->vtable[36].call((char *)world + world->vtable[36].adjustment)->r[0];
        s.q = Qmtc2(-1.0f);
        up = ScaleX(row, s.q);
    } else {
        up = D_00317550;
    }
    out->position = XformPoint(m, self->position);
    out->basis = func_0011CBF0(XformDir(m, self->direction), up);
    out->valueA = GClamp(Eval(&self->curveA, t), D_00341FF0.gMin, D_00341FF0.gMax);
    out->valueB = Eval(&self->curveB, t);
}
