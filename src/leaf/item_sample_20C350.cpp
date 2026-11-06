// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct M4 { qword r[4]; };
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
struct Sample { qword pos; M3 m; float g40, g44; char pad48[8]; };
struct Self {
    char pad0[0x20]; CLQ clqA; CLQ clqB; M3 rot; qword pos;
};
extern LM D_00341FF0;
static inline qword Point(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline M3 Rotate(const M4 &m, const M3 &a) return r {
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[0]) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(a.r[0]));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[1]) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(a.r[1]));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[2]) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(a.r[2]));
}
static inline float Curve(const CLQ &c, float t) { return c.g0 + t * (c.g1 + t * c.g2); }
static inline float Clamp(float g, const LM &lm) { float gMin = lm.gMin, gMax = lm.gMax; if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
extern "C" void func_0020C350(Self *self, M4 *item, float t, Sample *out)
{
    out->pos = Point(*item, self->pos);
    out->m = Rotate(*item, self->rot);
    out->g40 = Clamp(Curve(self->clqB, t), D_00341FF0);
    out->g44 = Curve(self->clqA, t);
}
