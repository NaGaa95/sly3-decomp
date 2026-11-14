// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// func_001A0DF8: SafeNormalize-style NormalTo stores through *pn in both arms;
// zero-instruction identity asm on the fallback keeps its lq in the dot block; vdiv's "0"(one) tie + two allocation-only
// "j"(one) operands give the target VF numbering; one GPR pin for pdv.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&f)); } };
struct V4 { float f[4]; } __attribute__((aligned(16)));
struct Obj { unsigned char pad0[0x260]; qword origin; unsigned char pad270[0x1148 - 0x270]; float reach; int flip; };
extern "C" {
extern qword D_00317550;
extern qword D_00317530;
void func_0022E330(void *self, float t, qword *pos, qword *dir);
float func_0022FC20(void *self, float g, float h);
float func_0011E940(float lo, float hi);
float func_001205C8(qword dir);
}
static inline qword Cross3(qword a, qword b)
{
    qword result;
    __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(result) : "j"(a), "j"(b));
    return result;
}
static inline qword Dot3(qword a, qword b)
{
    qword product, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
        : "=j"(product), "=&j"(one) : "j"(a), "j"(b));
    return product;
}
static inline qword SqrtX(qword value)
{
    qword root;
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(root) : "j"(value));
    return root;
}
static inline qword DivideByX(qword value, qword divisor)
{
    qword result;
    __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(result) : "j"(divisor), "j"(value));
    return result;
}
static inline float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static inline float GFromVf(qword q) { float x; __asm__("qmfc2.ni %0,%1" : "=r"(x) : "j"(q)); return x; }
/* zero-insn asm: identity copy of the fallback (keeps its load before the branch); "0"/"j"(one): allocation-only */
static inline void NormalTo(qword *pn, qword a, qword fallback) { qword d; qword one; float len; __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(one) : "j"(a)); __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d)); __asm__("qmfc2.ni %0,%1" : "=r"(len) : "j"(d)); qword k; __asm__("" : "=r"(k) : "0"(fallback)); if (len < 0.0001f) { *pn = k; } else { qword r; __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(r) : "j"(d), "j"(a), "0"(one), "j"(one), "j"(one)); *pn = r; } }
static inline qword QwMadd(qword a, qword b, const VU_FLOAT &s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword QwScale(qword a, const VU_FLOAT &s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(a), "j"(s.q));
    return r;
}
static inline qword QwSub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
extern "C" void func_001A0DF8(void *self, float g, qword *pv, qword *pdv)
{
    register qword *pd __asm__("$18") = pdv; /* register pin: pdv in s2, the D_00317550 high part in s3 */
    V4 pos, dir;
    qword n;
    func_0022E330(self, func_0022FC20(self, g, 150.0f), (qword *)&pos, (qword *)&dir);
    NormalTo(&n, Cross3(*(qword *)&dir, D_00317550), D_00317530);
    qword a = *(qword *)&pos;
    *pv = QwMadd(a, n, VU_FLOAT(func_0011E940(0.0f, 50.0f)));
    *pd = D_00317550;
}
