// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_00167DA0): grow a bounding sphere (radius in w) to include a transformed point.
typedef int qword __attribute__((mode(TI)));
struct M4 { qword r[4]; };
extern "C" const qword D_00345030;
static inline qword Transform(const M4 *m, qword p)
{
    qword r;
    __asm__("vmulax.xyz ACC,%1,%3x\n\tvmadday.xyz ACC,%2,%3y\n\tvmaddaz.xyz ACC,%4,%3z\n\tvmaddw.xyz %0,%5,$vf0w"
            : "=j"(r) : "j"(m->r[0]), "j"(m->r[1]), "j"(p), "j"(m->r[2]), "j"(m->r[3]));
    return r;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float Length(qword v)
{
    qword d, one; float f;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,Q" : "=j"(d) : "j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(d));
    return f;
}
static inline float GetX(qword v) { float f; __asm__("mtc1 %1,%0" : "=f"(f) : "r"(v)); return f; }
static inline float GetY(qword v) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(v)); return f; }
static inline float GetZ(qword v) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(v)); return f; }
static inline float GetW(qword v) { float f; __asm__("pextuw %0,$0,%1\n\tpextuw %0,$0,%0" : "=r"(f) : "r"(v)); return f; }
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); } };
static inline qword MAdd(qword p, qword v, VU_FLOAT k) { qword r; __asm__("vadda.xyzw ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(p), "j"(v), "j"(k.q)); return r; }
struct VU_FLOATR { qword q; VU_FLOATR(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); } };
union U { qword q; float f[4]; };
static inline qword Pack(float x, float y, float z, float w)
{
    U u; qword q, t, s;
    __asm__("mfc1 %0,%3\n\tmfc1 %1,%4\n\tpextlw %0,%1,%0\n\tmfc1 %1,%5\n\tmfc1 %2,%6\n\tpextlw %1,%2,%1\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t), "=&r"(s) : "f"(x), "f"(y), "f"(z), "f"(w));
    u.q = q;
    return u.q;
}
static inline qword Copy(qword v) { qword r; __asm__("vmax.xyzw %0,%1,%1" : "=j"(r) : "j"(v)); return r; }
extern "C" qword func_0018DC58(const M4 *m, qword p)
{
    qword s = Copy(p);
    float r = GetW(p);
    qword d = Sub(Transform(m, D_00345030), s);
    float len = Length(d);
    if (r < len) {
        float ratio = (len - r) * 0.5f / len;
        float nr = (len + r) * 0.5f;
        qword c = MAdd(s, d, VU_FLOAT(ratio));
        p = Pack(GetX(c), GetY(c), GetZ(c), GetX(VU_FLOATR(nr).q));
    }
    return p;
}
