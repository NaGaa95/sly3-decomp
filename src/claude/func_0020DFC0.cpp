// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0020DFC0 (agent A92): MoveRipFlutter - Sly 3 form of Sly 2 MoveRipFlutter__FP4RIPN (0x1D09A0, src/hand/func_001D09A0.cpp).
// Sly 3 blends the along-length toward 200 with (1 - dt); the second length readout uses a whitespace-different mtc1 helper
// so cse does not merge it with the first. One pin (as in Sly 2): the vector to normalise read into $v0.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
struct P { char pad0[0x40]; M3 matrix; char pad70[0x20]; qword vel; char padA0[0x24]; float drag; };
struct CLOCK { float time, dt; };
extern "C" {
extern CLOCK g_clock;
extern float D_00325AA0[3], D_00325AB0[2];
extern qword D_00317530;
M3 BuildRotateMatrixAxis(qword, float) asm("func_0011C8C0");
float GSplitVector(qword, qword, qword *, qword *) asm("func_0011FE60");
void MoveRip(P *) asm("func_0020BFA8");
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
/* f1*v1 + f2*v2 */
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return r;
}
static inline float GClamp(float g, const float *lim)
{
    float gMin = lim[0], gMax = lim[1];
    if (g < gMin) return gMin;
    if (gMax < g) return gMax;
    return g;
}
static inline float Dot(qword a, qword b)
{
    qword d, one;
    float g;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(d), "=&j"(one) : "j"(a), "j"(b));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(d));
    return g;
}
/* m * v for a 3x3 matrix stored as rows */
static inline qword Rotate(const M3 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(v), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    return r;
}
/* a*b for 3x3 matrices; g++ named return value (its two dead stack copies are in the target) */
static inline M3 Multiply(const M3 &a, const M3 &b) return r
{
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r.r[0]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[0]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r.r[1]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[1]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z" : "=j"(r.r[2]) : "j"(a.r[0]), "j"(a.r[1]), "j"(a.r[2]), "j"(b.r[2]));
}
/* length of the xyz part, left in a VF register (x) */
static inline qword Length(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Divide(qword v, qword l)
{
    qword r;
    __asm__("vdiv Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, Q" : "=j"(r) : "j"(v), "j"(l), "j"(l)); /* allocation-only second "j"(l): keeps the length in a VF register */
    return r;
}
static inline float GetX2(qword q) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(q)); return g; }
static inline float GetX(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
/* *pv /= |*pv|, or *pv = *pfallback when the length is below 1e-4; returns the length */
static inline qword NormalizeSafe(qword *pv, const qword *pfallback)
{
    register qword g asm("$2") = *(volatile qword *)pv; /* the one register pin: the target reads the vector into $v0, then qmtc2 */
    qword v = g;
    qword len = Length(v);
    if (GetX(len) < 0.0001f) *pv = *pfallback;
    else *pv = Divide(v, len);
    return len;
}
// name: SafeHouse port (MoveRipFlutter)
extern "C" void func_0020DFC0(P *p)
{
    qword row0 = p->matrix.r[0];
    qword axis = p->matrix.r[1];
    float g = Dot(p->vel, row0);
    float t = GClamp(D_00325AA0[0] + g * (D_00325AA0[1] + g * D_00325AA0[2]), D_00325AB0);
    M3 rot = BuildRotateMatrixAxis(axis, t * g_clock.dt);
    p->vel = Rotate(rot, p->vel);
    p->matrix = Multiply(rot, p->matrix);
    float drag = p->drag;
    p->drag = 0.0f;
    struct { qword along, across; } w;
    GSplitVector(p->vel, row0, &w.along, &w.across);
    qword len = NormalizeSafe(&w.along, &D_00317530);
    float dt = g_clock.dt;
    g = GetX2(len);
    float gAlong = 200.0f + (1.0f - dt) * (g - 200.0f);
    float gAcross = drag * dt + 1.0f;
    p->vel = VecCombo(VU_FLOAT(gAlong), VU_VECTOR(w.along), VU_FLOAT(gAcross), VU_VECTOR(w.across));
    MoveRip(p);
    p->drag = drag;
}
