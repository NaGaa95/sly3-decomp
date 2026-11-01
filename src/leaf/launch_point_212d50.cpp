// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Launch an object at a point: add it to the world, clear its motion, then give it a velocity along the line to the aim point
// (scaled by its launch speed for kinds 0x5B), a plain scalar launch speed (kind 0x5C) or the ballistic lob solution (all other kinds).
typedef int qword __attribute__((mode(TI)));
struct MATRIX3 { qword r[3]; };
struct MATRIX4 { qword r[4]; };
struct SO;
#define VF1(n) virtual void V##n();
struct LO {
    int hdr[3];
    VF1(1) VF1(2) VF1(3) VF1(4) VF1(5) VF1(6) VF1(7)
    virtual void Add();                                          // 8
    VF1(9) VF1(10) VF1(11) VF1(12) VF1(13) VF1(14) VF1(15) VF1(16) VF1(17) VF1(18) VF1(19) VF1(20)
    VF1(21) VF1(22) VF1(23) VF1(24) VF1(25) VF1(26) VF1(27) VF1(28) VF1(29) VF1(30) VF1(31) VF1(32)
    VF1(33) VF1(34)
    virtual void RotateToMat(MATRIX3 *pmat);                     // 35
    virtual MATRIX4 *PmatWorld();                                // 36
    VF1(37) VF1(38) VF1(39)
    virtual void SetVelocity(qword v);                           // 40
    virtual void SetAngularVelocity(qword w);                    // 41
    VF1(42) VF1(43) VF1(44) VF1(45) VF1(46) VF1(47) VF1(48) VF1(49) VF1(50) VF1(51) VF1(52) VF1(53) VF1(54) VF1(55) VF1(56)
    VF1(57) VF1(58) VF1(59) VF1(60) VF1(61) VF1(62) VF1(63) VF1(64) VF1(65) VF1(66) VF1(67) VF1(68) VF1(69) VF1(70) VF1(71) VF1(72)
    VF1(73) VF1(74) VF1(75) VF1(76) VF1(77) VF1(78) VF1(79) VF1(80) VF1(81)
    virtual void SetTarget(SO *psoSource, qword posTarget);      // 82
};
struct SO : LO {
    char pad10[0x240 - 0x10];
    float svLaunch;                                              // 0x240
};
extern qword D_00317530;        // default direction
extern qword D_00317560;        // zero vector
extern "C" {
void func_0023EBF8(SO *, void *);
void func_0023EC98(SO *, void *);
void func_001C7A00(SO *, int, int);
void func_0023D938(SO *, qword);
qword func_0023ED38(SO *);
qword func_00212480(float, qword, qword, qword);                 // CalculateLaunchVelocity
qword func_001C9428(int, SO *, qword);
void func_0011CBA0(MATRIX3 *, qword);
int func_0013B500(SO *, int);
}
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
struct VU_FLOAT {
    qword q;
    VU_FLOAT() {}
};
// a VU float straight from a float in memory (loaded as an integer word)
static inline VU_FLOAT VuFloatFromWord(const float &f) { VU_FLOAT g; __asm__("qmtc2.ni %1,%0" : "=j"(g.q) : "rV"(*(const int *)&f)); return g; }
struct VECTOR {
    qword q;
    VECTOR(float x, float y, float z)
    {
        qword t;
        __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0" : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    }
};
static inline float GFromVfBits(qword v)
{
    int n;
    float g;
    __asm__("qmfc2.ni %0,%1" : "=r"(n) : "j"(v));
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(n));
    return g;
}
static inline qword Length(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Div(qword v, qword l) { qword r; __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(l)); return r; }
// unit vector from posFrom to posTo, or the default direction when they are too close
static inline qword Normalize2(qword posTo, qword posFrom)
{
    qword v;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(v) : "j"(posTo), "j"(posFrom), "j"(posTo)); // posTo again: allocation only
    qword fallback = D_00317530;
    qword l = Length(v);
    if (GFromVfBits(l) < 0.0001f)
        l = fallback;
    else
        l = Div(v, l);
    return l;
}
static inline qword operator*(VU_FLOAT g, qword v) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(g.q)); return r; }
extern "C" void func_00212D50(SO *pso, SO *psoSource, qword posAim)
{
    qword posStart = pso->PmatWorld()->r[3];
    VV posCopy(posStart);
    pso->Add();
    VV posCopy2(posAim);
    func_0023EBF8(pso, 0);
    func_0023EC98(pso, 0);
    func_001C7A00(pso, 0, 3);
    pso->SetAngularVelocity(D_00317560);
    if (func_0013B500(pso, 0x5C)) {
        func_0023D938(pso, VECTOR(pso->svLaunch, 0.0f, 0.0f).q);
    } else if (func_0013B500(pso, 0x5B)) {
        qword v = VuFloatFromWord(pso->svLaunch) * Normalize2(posAim, posStart);
        pso->SetVelocity(v);
        MATRIX3 mat;
        func_0011CBA0(&mat, v);
        pso->RotateToMat(&mat);
    } else {
        qword vAccel = func_0023ED38(pso);
        qword v = func_00212480(0.5f, posCopy, posCopy2, vAccel);
        pso->SetVelocity(v);
    }
    if (func_0013B500(pso, 0x5A))
        pso->SetTarget(psoSource, func_001C9428(0, psoSource, posAim));
}
