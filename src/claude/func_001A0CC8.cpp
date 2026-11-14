// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// func_001A0CC8: allocation-only operands instead of a vf1 pin; one GPR pin for the -1.0 VU_FLOAT.
typedef int qword __attribute__((mode(TI)));
struct VU_FLOAT { qword q; VU_FLOAT(const float &f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)&f)); } };
struct VU_FLOATC { qword q; VU_FLOATC(float f) { register int t __asm__("$3"); /* register pin: target moves the -1.0 bits through v1 */ __asm__("mfc1 %0, %1" : "=r"(t) : "f"(f)); __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(t)); } };
struct V4 { float f[4]; } __attribute__((aligned(16)));
struct Obj { unsigned char pad0[0x260]; qword origin; unsigned char pad270[0x1148 - 0x270]; float reach; int flip; };
extern "C" {
extern qword D_00317550;
extern qword D_00317530;
void func_0022E330(void *self, qword *pos, qword *dir);
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
/* Normal: the three allocation-only "j"(one) operands keep the vaddw temp out of vf1 so the result takes vf1 (no pin) */
static inline qword Normal(qword a, qword fallback) { qword d; qword one; float len; __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=&j"(d), "=&j"(one) : "j"(a)); __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(d) : "j"(d)); __asm__("qmfc2.ni %0,%1" : "=r"(len) : "j"(d)); if (len < 0.0001f) { d = fallback; } else { __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(d) : "j"(d), "j"(a), "j"(one), "j"(one), "j"(one)); } return d; }
static inline qword QwMadd(qword a, qword b, const VU_FLOAT &s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q), "j"(s.q), "j"(s.q), "j"(s.q));
    return r;
}
static inline qword QwScale(qword a, const VU_FLOATC &s)
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
extern "C" void func_001A0CC8(void *self, Obj *obj, qword *outPos, float *outAngle)
{
    V4 pos, dir;
    func_0022E330(self, (qword *)&pos, (qword *)&dir);
    qword n = Normal(Cross3(*(qword *)&dir, D_00317550), D_00317530);
    if (outPos)
        *outPos = QwSub(QwMadd(*(qword *)&pos, n, VU_FLOAT(obj->reach)), obj->origin);
    if (outAngle) {
        if (obj->flip == 1)
            n = QwScale(n, VU_FLOATC(-1.0f));
        *outAngle = func_001205C8(n);
    }
}
