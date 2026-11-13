// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Follows the selected path and computes the steering heading in local coordinates.
typedef int qword __attribute__((mode(TI)));
union U { qword q; float f[4]; };
struct VEntry { short delta; short pad; qword *(*call)(void *); };
struct CLQ { float g0, g1, g2; };
struct LM { float gMin, gMax; };
struct Follower {
    unsigned char pad00[0xC];
    VEntry *table;
    unsigned char pad10[0x220 - 0x10];
    float radius;
    unsigned char pad224[0x25C - 0x224];
    float cursor;
};
extern "C" {
void func_0022EEA0(void *path, qword position, void *unused, qword *point, qword *tangent, float *out, float *cursor, float start);
float func_001205C8(qword v);
float func_002A3EE8(float y, float x);
float func_0011E3B8(float angle);
}
static inline qword *Matrix(Follower *self)
{
    VEntry *entry = &self->table[36];
    return entry->call((char *)self + entry->delta);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
static inline qword Scale(qword a, VU_FLOAT s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q));
    return r;
}
static inline float Dist2D(qword a, qword b)
{
    qword d;
    float f;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a), "j"(b));
    __asm__("vmul.xy %0, %0, %0
	vaddy.x %0, %0, %0y" : "+j"(d));
    __asm__("vsqrt $Q, %0x
	vwaitq
	vaddq.x %0, $vf0, $Q" : "+j"(d));
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(d));
    return f;
}
static inline float GClamp(float g, const LM &lm) { if (g < lm.gMin) return lm.gMin; if (lm.gMax < g) return lm.gMax; return g; }
static inline float Curve(const CLQ &c, float t) { return c.g0 + t * (c.g1 + t * c.g2); }
static inline qword AddScaled(qword a, qword b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float F(qword q) { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
static inline qword NormalizeOr(qword v, qword fallback)
{
    qword d, one, len;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(len) : "j"(d));
    if (F(len) < 0.0001f) {
        __asm__ volatile(""); /* Keep fallback selection inside this branch; emits no instruction. */
        return fallback;
    }
    qword r;
    __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(r) : "j"(v), "j"(len));
    return r;
}
extern "C" float func_00217470(Follower *self, void *path, int forward)
{
    U point, tangent;
    qword dir;
    qword position = Matrix(self)[3];
    func_0022EEA0(path, position, 0, &point.q, &tangent.q, 0, &self->cursor, self->cursor);
    if (!forward)
        tangent.q = Scale(tangent.q, VU_FLOAT(-1.0f));
    {
        qword p = point.q;
        float dist = Dist2D(position, p);
        CLQ curve;
        LM range;
        float limit = self->radius * 1.5f;
        range.gMin = 0.0f;
        range.gMax = limit;
        curve.g0 = limit;
        curve.g1 = -1.0f;
        curve.g2 = 0.0f;
        float g = GClamp(Curve(curve, dist), range);
        dir = NormalizeOr(Sub(AddScaled(p, tangent.q, VU_FLOAT(g)), position), tangent.q);
    }
    float heading = func_001205C8(dir);
    qword *m = Matrix(self);
    return func_0011E3B8(heading - func_002A3EE8(((float *)m)[1], ((float *)m)[0]));
}

