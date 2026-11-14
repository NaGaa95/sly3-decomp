// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0011CDC8: rotation matrix taking direction a onto b. Port of the matched Sly 2
// func_0011BA08 (src/hand/func_0011BA08.cpp in the Sly 2 decomp), adapted:
//  - -Os (as the neighbouring Sly 3 math functions) fixes the second Len() VU registers.
//  - G() reads a VU float via an explicit qmfc2 + mtc1 (no register pin). Using it for the lb test adds one
//    RTL insn while a is live, which breaks the a/axis global-alloc priority tie the right way.
//  - H(): "r,j" alternatives keep la/lb VU-class (the j alternative is never selected).
//  - sn reuses one variable for cos^2 and sqrt so the sqrt result lands in $f0; the sqrt asm is volatile to
//    keep the original schedule.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct VU_FLOAT {
    qword q;
    VU_FLOAT() {}
    VU_FLOAT(float f) { __asm__("mfc1 %0, %1" : "=r"(q) : "f"(f)); }
    float F() const { float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(q)); return g; }
    /* "r,j": the j alternative is allocation-only (never selected), see header */
    float H() const { float g; __asm__("mtc1 %1, %0" : "=f,f"(g) : "r,j"(q)); return g; }
    float G() const { qword t; __asm__("qmfc2.ni %0, %1" : "=r"(t) : "j"(q)); float g; __asm__("mtc1 %1, %0" : "=f"(g) : "r"(t)); return g; }
};
extern "C" {
void *func_00292034(void *pv, int n, int cb);
void *func_00291E8C(void *pvDst, const void *pvSrc, int cb);
qword func_0011FF60(qword v);
float func_0011E560(float g, float gMax);
M3 func_0011C840(VU_FLOAT s, VU_FLOAT c, qword axis);
}
static inline qword Len(qword a)
{
    qword l;
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Dot(qword a, qword b)
{
    qword d;
    qword one;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
struct MAT3 { float m[3][4]; };
extern "C" M3 *func_0011CDC8(M3 *pm, qword a, qword b);
M3 *func_0011CDC8(M3 *pm, qword a, qword b)
{
    VU_FLOAT la, lb;
    la.q = Len(a);
    lb.q = Len(b);
    if (la.H() < 1e-4f || lb.G() < 1e-4f) {
        MAT3 *p = (MAT3 *)pm;
        func_00292034(pm, 0, 0x30);
        p->m[0][0] = p->m[1][1] = p->m[2][2] = 1.0f;
    } else {
        qword axis;
        __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(axis) : "j"(a), "j"(b));
        VU_FLOAT l;
        l.q = Len(axis);
        if (l.F() > 1e-8f) {
            __asm__("vdiv $Q, $vf0w, %2x\n\tvwaitq\n\tvmulq.xyzw %0, %1, $Q" : "=j"(axis) : "j"(axis), "j"(l.q));
        } else {
            axis = func_0011FF60(a);
        }
        VU_FLOAT d;
        d.q = Dot(a, b);
        VU_FLOAT c = func_0011E560(VU_FLOAT(d.G() / (la.H() * lb.H())).F(), 1.0f);
        float sn = c.F();
        sn = sn * sn;
        __asm__ __volatile__("sqrt.s %0, %1" : "=f"(sn) : "f"(1.0f - sn));
        M3 m = func_0011C840(VU_FLOAT(sn), c, axis);
        func_00291E8C(pm, &m, sizeof(M3));
    }
    return pm;
}
