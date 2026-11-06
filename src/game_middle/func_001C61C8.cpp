// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Does the sphere (pos, radius in w) touch a chain of spheres? Every sphere of the chain is tested on its own, then the
// capsule-like hull between each adjacent pair: the common tangent line of the two circles (normal n = u * s + perp *
// sqrt(1 - s*s), u the unit axis, s = (r0 - r1) / |axis|) gives the tangent points A and B; the point touches when its
// distance to the tangent is below the radius and its projection onto AB falls inside the segment.
typedef int qword __attribute__((mode(TI)));
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct SPHERE { qword pos; };

static inline VV Copy(qword v) { qword r; __asm__("vmax.xyzw %0,%1,%1" : "=j"(r) : "j"(v)); return r; }
static inline VV Sub(VV a, VV b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float GFromVf(VV v) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(v)); return g; }
static inline float GFromQw(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline float GetW(qword v) { float f; __asm__("pextuw %0,$0,%1\n\tpextuw %0,$0,%0" : "=r"(f) : "r"(v)); return f; }
static inline VV Sqrt(VV v) { qword r; __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(v)); return r; }
static inline VV Dot(VV a, VV b)
{
    qword r, one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(r), "=j"(one) : "j"(a), "j"(b));
    return r;
}
static inline VV Length(VV v) { return Sqrt(Dot(v, v)); }
static inline VV DivideQ(VV v, VV l) { qword r; __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(l), "j"(v)); return r; }
static inline VV Divide(VV v, VU_FLOAT g) { qword r; __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(g.q), "j"(v)); return r; }
static inline VV Normalize(VV v) { return DivideQ(v, Length(v)); }
static inline VV Cross(VV a, VV b) { qword r; __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b)); return r; }
// f1 * v1 + f2 * v2
static inline VV VecCombo(VU_FLOAT f1, VV v1, VU_FLOAT f2, VV v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1), "j"(f2.q), "j"(v2));
    return r;
}
// base + v * g
static inline VV AddScaled(VV base, VU_FLOAT g, VV v)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %3, %2x" : "=j"(r) : "j"(base), "j"(g.q), "j"(v));
    return r;
}
static inline float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(g)); return r; }

extern "C" int func_00120EE0(qword a, qword b);
extern "C" int func_001C61C8(qword pos, int csphere, SPHERE *asphere)
{
    int i;
    for (i = 0; i < csphere; i++)
    {
        if (func_00120EE0(pos, asphere[i].pos))
            return 1;
    }
    for (i = 1; i < csphere; i++)
    {
        SPHERE *ps0 = &asphere[i - 1];
        SPHERE *ps1 = &asphere[i];
        VV p = Copy(pos);
        VV a0 = Copy(ps0->pos);
        VV a1 = Copy(ps1->pos);
        float r0 = GetW(ps0->pos);
        float r1 = GetW(ps1->pos);
        VV axis = Sub(a1, a0);
        VV len = Length(axis);
        VV dpos = Sub(p, a0);
        VV c1 = Cross(dpos, axis);
        float sLen = GFromVf(len);
        VV u = Divide(axis, VU_FLOAT(sLen));
        float s = (r0 - r1) / sLen;
        VV perp = Normalize(Cross(u, c1));
        float root = SqrtF(1.0f - s * s);
        VV n = VecCombo(VU_FLOAT(s), u, VU_FLOAT(root), perp);
        VV posA = AddScaled(a0, VU_FLOAT(r0), n);
        VV pa = Sub(p, posA);
        VV posB = AddScaled(a1, VU_FLOAT(r1), n);
        VV ba = Sub(posB, posA);
        VV num = Dot(pa, ba);
        VV den = Dot(ba, ba);
        float sDist = GFromQw(Dot(pa, n));
        float t = GFromQw(num) / GFromVf(den);
        if (sDist < GetW(pos) && t >= 0.0f && t <= 1.0f)
            return 1;
    }
    return 0;
}
