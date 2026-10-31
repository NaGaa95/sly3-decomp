// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00166690: port of Sly 2 BuildFrustrum (src/hand/BuildFrustrum.cpp): 4 side-plane normals.
// NormalizeP (used by the planes whose normal is Cross's second operand) has the one register pin.
typedef int qword __attribute__((mode(TI)));
struct MATRIX3 { qword r[3]; };
extern "C" void func_00166690(MATRIX3 *pmat, float gx, float gy, qword *anormal);
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VU_VECTOR { qword q; VU_VECTOR(const qword &v) { q = v; } };

static inline qword AddScaled(VU_VECTOR a, VU_VECTOR b, VU_FLOAT s)
{
    qword r;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(r) : "j"(a.q), "j"(b.q), "j"(s.q));
    return r;
}
static inline qword Normalize(qword v)
{
    qword t, one, r;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=&j"(t), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(t));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(t), "j"(v));
    return r;
}
static inline qword Cross(qword a, qword b)
{
    qword r;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(r) : "j"(a), "j"(b));
    return r;
}

static inline qword NormalizeP(qword v)
{
    register qword t __asm__("vf2"); /* register pin: length temp in vf2 like the target */
    qword r;
    qword one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=&j"(t), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "+j"(t));
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(r) : "j"(t), "j"(v));
    return r;
}

void func_00166690(MATRIX3 *pmat, float gx, float gy, qword *anormal)
{
    anormal[0] = Cross(pmat->r[2], NormalizeP(AddScaled(pmat->r[0], pmat->r[1], VU_FLOAT(gx))));
    anormal[1] = Cross(Normalize(AddScaled(pmat->r[0], pmat->r[1], VU_FLOAT(-gx))), pmat->r[2]);
    anormal[2] = Cross(Normalize(AddScaled(pmat->r[0], pmat->r[2], VU_FLOAT(gy))), pmat->r[1]);
    anormal[3] = Cross(pmat->r[1], NormalizeP(AddScaled(pmat->r[0], pmat->r[2], VU_FLOAT(-gy))));
}
