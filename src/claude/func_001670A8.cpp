// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Port of Sly 2 src/hand/func_001670A8.cpp (same body, Sly 3 addresses).
typedef int qword __attribute__((mode(TI)));
/* rodata at 0x00320DD0 (not in symbol_addrs): ring counts per tilt step */
extern "C" const int D_00320DD0[9] = { 1, 5, 10, 12, 15, 12, 10, 5, 1 };
extern "C" {
qword func_0011FDD8(float pan, float tilt, float s);
int func_00166F08(void *p, void *x, qword a, qword b, float *pt, float *pu, float g);
qword func_001670A8(void *p, void *x, qword pos, float g);
}
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };

static inline qword AddScaled(VU_VECTOR a, VU_VECTOR b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(s.q));
    return r;
}

static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2, VU_FLOAT f3, VU_VECTOR v3)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %1, %4x\n\tvmaddax.xyzw $ACC, %2, %5x\n\tvmaddx.xyzw %0, %3, %6x"
            : "=j"(r) : "j"(v1.q), "j"(v2.q), "j"(v3.q), "j"(f1.q), "j"(f2.q), "j"(f3.q));
    return r;
}

qword func_001670A8(void *p, void *x, qword pos, float g)
{
    float t, u;
    qword best;
    float dg = 5.0f / g;
    float gBest = 3.40282346638528859812e+38f;
    int i, j;

    best = pos;
    for (i = 0; i < 9; i++) {
        float tilt = (float)(i - 4) * 0.3926991f;
        int c = D_00320DD0[i];
        for (j = 0; j < c; j++) {
            qword dir = func_0011FDD8((float)j * 3.1415927f / (float)c, tilt, 1.0f);
            qword test = AddScaled(pos, dir, VU_FLOAT(g));
            if (func_00166F08(p, x, pos, test, &t, &u, dg + dg)) {
                if (0.0f < t)
                    t += dg;
                if (t < gBest) {
                    gBest = t;
                    best = VecCombo(VU_FLOAT(1.0f - gBest), pos, VU_FLOAT(gBest), test, VU_FLOAT(-1.0f), dir);
                }
            }
        }
    }
    return best;
}
/* Next .rodata item of the original unit (a float literal read by a later function); it follows FLT_MAX. */
extern "C" const float D_00320DF8 = 2500.0f;
