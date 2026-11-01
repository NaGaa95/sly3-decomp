// Sample one billboard item of a particle effect at normalised time t: transform its offset by the item matrix, face the camera, spin by the animated angle and scale size/alpha by curves of t and of the camera distance.
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
struct VTE { short delta, pad; void *fn; };
struct World { char pad0[0xC]; VTE *vt; };
union U { qword q; float f[4]; };
extern LM D_00341FF0, D_00325A60, D_00325A80;
extern CLQ D_00325A50, D_00325A70, D_00325A90;
extern qword D_00317550, D_00317530;
extern unsigned char D_00475480[];
extern "C" {
World *func_00165B28(void *);
M3 func_0011CBF0(qword a, qword b);
M3 func_0011C8C0(qword axis, float angle);
}
static inline qword Point(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline M3 Mul(const M3 &a, const M3 &b) return r {
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[0]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[0]));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[1]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[1]));
    __asm__("vmulax.xyz $ACC,%1,%4x\n\tvmadday.xyz $ACC,%2,%4y\n\tvmaddz.xyz %0,%3,%4z" : "=j"(r.r[2]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[2]));
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Length(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%2
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%0,%0y
	vmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v), "j"(v));
    __asm__("vsqrt $Q,%0x
	vwaitq
	vaddq.x %0,$vf0,$Q" : "+j"(d));
    return d;
}
static inline float X(qword v) { int t; float f; __asm__("qmfc2.ni %1,%2
	mtc1 %1,%0" : "=f"(f), "=&r"(t) : "j"(v)); return f; }

static inline float Curve(const CLQ &c, float t) { return c.g0 + t * (c.g1 + t * c.g2); }
static inline float Clamp(float g, const LM &lm) { float gMin = lm.gMin, gMax = lm.gMax; if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
extern "C" void func_0020D7E8(Self *self, M4 *item, Sample *out, float t) 
{
    World *world = func_00165B28(D_00475480);
    qword pos = Point(*item, self->pos);
    VTE *e = &world->vt[36];
    qword cam = ((M4 *(*)(void *))e->fn)((char *)world + e->delta)->r[3];
    qword d = Sub(cam, pos);
    qword up = D_00317550;
    float dist = X(Length(d)) * 0.001f;
    M3 look = func_0011CBF0(d, up);
    M3 spin = func_0011C8C0(D_00317530, Curve(D_00325A90, t));
    out->pos = pos;
    out->m = Mul(look, spin);
    out->g40 = Clamp(Curve(self->clqB, t), D_00341FF0) * Clamp(Curve(D_00325A70, dist), D_00325A80);
    out->g44 = Curve(self->clqA, t) * Clamp(Curve(D_00325A50, dist), D_00325A60);
}
