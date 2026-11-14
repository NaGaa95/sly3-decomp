// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00147410: spring integrator acc=(pg-pos)*k0+(vg-vel)*k1; vel+=acc*dt; pos+=(vel+vel')*dt/2. One allocation-only "j"(s.q) operand in AddScaled2 (h gets vf1, dt vf5).
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };
static inline qword Sub(VU_VECTOR a, VU_VECTOR b) { qword d; __asm__("vsub.xyzw %0, %1, %2" : "=j"(d) : "j"(a.q), "j"(b.q)); return d; }
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.q), "j"(v1.q), "j"(f2.q), "j"(v2.q));
    return r;
}
static inline qword AddScaled(VU_VECTOR a, VU_VECTOR b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(s.q));
    return r;
}
static inline qword AddScaled2(VU_VECTOR a, VU_VECTOR b, VU_VECTOR c, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %4x\n\tvmaddx.xyzw %0, %3, %4x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(c.q), "j"(s.q), "j"(s.q));
    return r;
}
extern "C" void func_00147410(qword posGoal, qword velGoal, qword *ppos, qword *pvel, float k1, float k0, float dt)
{
    qword acc = VecCombo(VU_FLOAT(k0), Sub(posGoal, *ppos), VU_FLOAT(k1), Sub(velGoal, *pvel));
    qword v = AddScaled(*pvel, acc, VU_FLOAT(dt));
    *ppos = AddScaled2(*ppos, *pvel, v, VU_FLOAT(dt * 0.5f));
    *pvel = v;
}
