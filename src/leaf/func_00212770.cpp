// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union MATRIX4 { qword r[4]; float m[4][4]; };
struct MATRIX3 { qword r[3]; };
struct XF { MATRIX4 mat; MATRIX4 matWorld; };
struct CLQ { float g0, g1, g2, gUnused; };
struct LM { float gMin, gMax; };
struct VECTOR4 { qword q; VECTOR4(const qword &v) { q = v; } VECTOR4(const VECTOR4 &v) { q = v.q; } };
struct SO;
#define VF1(n) virtual void V##n();
#define VF4(n) VF1(n) VF1(n+1) VF1(n+2) VF1(n+3)
struct LO {
    int hdr[3];
    VF1(1) VF1(2) VF1(3) VF1(4) VF1(5) VF1(6) VF1(7)
    virtual void Add();                                          // 8
    VF1(9) VF1(10) VF1(11) VF1(12) VF1(13) VF1(14) VF1(15) VF1(16) VF1(17) VF1(18) VF1(19) VF1(20)
    VF1(21) VF1(22) VF1(23) VF1(24) VF1(25) VF1(26) VF1(27) VF1(28) VF1(29) VF1(30) VF1(31) VF1(32)
    VF1(33) VF1(34)
    virtual void RotateToMat(MATRIX3 *pmat);                     // 35
    virtual MATRIX4 *PmatWorld();                                // 36
    virtual XF *PxfLocal(MATRIX4 *pmatLocal);                    // 37
    VF1(38) VF1(39)
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
struct LAUNCH {
    char pad0[0x40];
    qword posTarget;            // 0x40
    SO *psoSource;              // 0x50
    char pad54[0xC];
    CLQ clqPredict;             // 0x60
    LM lmPredict;               // 0x70
    char pad78[8];
    CLQ clqOffset;              // 0x80
    LM lmOffset;                // 0x90
    LM lmSpin;                  // 0x98
    float pitch;                // 0xA0
};
extern XF D_0034A160;           // identity frame
extern qword D_00317530;        // default direction
extern "C" {
MATRIX4 *func_0011D558(MATRIX4 *, MATRIX4 *, MATRIX4 *);
void *func_00292034(void *, int, int);                           // memset
void func_0028F680(XF *, int, MATRIX4 *, MATRIX4 *, float);
int func_0013B500(SO *, int);                                    // FIsBasicDerivedFrom
void func_0014D1F0(SO *, LAUNCH *);
void func_0023EBF8(SO *, void *);
void func_0023EC98(SO *, void *);
void func_001C7A00(SO *, int, int);
void func_0023D938(SO *, qword);
qword func_0023ED38(SO *);
qword func_00212480(float, qword, qword, qword);                 // CalculateLaunchVelocity
void func_0011CBA0(MATRIX3 *, qword);
float func_0011E940(float, float);                               // GRandInRange
}
static inline float GRandInRange(const LM &lm) { return func_0011E940(lm.gMin, lm.gMax); }
struct VV { qword q; VV() {} VV(const qword &v) { q = v; } operator qword() const { return q; } };
struct VU_FLOAT {
    qword q;
    VU_FLOAT() {}
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1,%0" : "=j"(q) : "r"(f)); }
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
static inline qword QwToVf(qword v) { qword r; __asm__("qmtc2.ni %1,%0" : "=j"(r) : "r"(v)); return r; }
static inline qword QwFromVf(qword v) { qword r; __asm__("qmfc2.ni %0,%1" : "=r"(r) : "j"(v)); return r; }
static inline float GFromVf(qword v) { float g; __asm__("mtc1 %1,%0" : "=f"(g) : "r"(v)); return g; }
static inline float GFromVfBits(qword v)
{
    register int n __asm__("$3"); // pin: the length bits live in v1 so the fallback load can use v0
    float g;
    __asm__("qmfc2.ni %0,%1" : "=r"(n) : "j"(v));
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(n));
    return g;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Point(const MATRIX4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]), "j"(m.r[3]), "j"(v));
    return r;
}
static inline qword Length(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline qword Div(qword v, qword l) { qword r; __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(l)); return r; }
// unit vector along v (computed in place of its length), or the default direction when v is too short
static inline qword Normalize(qword v)
{
    qword fallback = D_00317530;
    qword l = Length(v);
    if (GFromVf(l) < 0.0001f)
        l = fallback;
    else
        l = Div(v, l);
    return l;
}
// unit vector from posFrom to posTo
static inline qword Normalize2(qword posTo, qword posFrom)
{
    qword fallback = D_00317530;
    qword v;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(v) : "j"(posTo), "j"(posFrom), "j"(posTo)); // posTo again: allocation only
    qword l = Length(v);
    if (GFromVfBits(l) < 0.0001f)
        l = fallback;
    else
        l = Div(v, l);
    return l;
}

static inline qword NormalizeTo(qword v)
{
    qword fallback = D_00317530;
    qword l = Length(v);
    if (GFromVf(l) < 0.0001f)
        goto tiny;
    return Div(v, l);
tiny:
    return fallback;
}
// base + v * g
static inline qword AddScaled(VV base, VU_FLOAT g, qword v)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base.q), "j"(v), "j"(g.q));
    return r;
}
static inline qword operator*(qword v, VU_FLOAT g) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(g.q)); return r; }
static inline qword operator*(VU_FLOAT g, qword v) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(g.q)); return r; }
static inline float GFromClq(const CLQ &clq, float g) { return clq.g0 + g * (clq.g1 + g * clq.g2); }
static inline float GClamp(float g, float gMin, float gMax) { if (g < gMin) g = gMin; else if (gMax < g) g = gMax; return g; }
static inline float GClampR(float g, float gMin, float gMax) { if (g < gMin) return gMin; if (gMax < g) return gMax; return g; }
static inline void LoadIdentity(MATRIX4 *pm) { func_00292034(pm, 0, sizeof(*pm)); pm->m[0][0] = pm->m[1][1] = pm->m[2][2] = pm->m[3][3] = 1.0f; }

extern "C" void func_00212770(LAUNCH *plaunch, SO *pso)
{
    MATRIX4 matParent;
    qword posStart = pso->PmatWorld()->r[3];
    VV posOrigin(posStart);
    SO *psoSource = plaunch->psoSource;
    XF *pxf;
    if (psoSource)
        pxf = psoSource->PxfLocal(&matParent);
    else {
        pxf = &D_0034A160;
        LoadIdentity(&matParent);
    }
    qword dpos;
    float dist;
    {
        MATRIX4 mat;
        func_0011D558(&mat, &pxf->matWorld, &matParent);
        dpos = Sub(Point(mat, plaunch->posTarget), posStart);
        dist = GFromVf(Length(dpos));
        float t = GClamp(GFromClq(plaunch->clqPredict, dist), plaunch->lmPredict.gMin, plaunch->lmPredict.gMax);
        if (t != 0.0f) {
            MATRIX4 matPredict;
            func_0028F680(pxf, 0, &mat, 0, t);
            func_0011D558(&matPredict, &mat, &matParent);
            dpos = Sub(Point(matPredict, plaunch->posTarget), posStart);
        }
    }
    dist = GFromVf(Length(dpos));
    float offset = GClampR(GFromClq(plaunch->clqOffset, dist), plaunch->lmOffset.gMin, plaunch->lmOffset.gMax);
    qword posAim;
    qword posLaunch = AddScaled(posOrigin, VU_FLOAT(offset), Normalize(dpos));
    posAim = QwFromVf(posLaunch);
    if (func_0013B500(pso, 0x59)) {
        func_0014D1F0(pso, plaunch);
    }
    pso->Add();
    func_0023EBF8(pso, 0);
    func_0023EC98(pso, 0);
    func_001C7A00(pso, 0, 3);
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
        qword v = func_00212480(plaunch->pitch, posStart, posLaunch, vAccel);
        pso->SetVelocity(v);
    }
    if (plaunch->lmSpin.gMax > 0.0f) {
        float g = GRandInRange(plaunch->lmSpin);
        float x = func_0011E940(-1.0f, 1.0f);
        float y = func_0011E940(-1.0f, 1.0f);
        float z = func_0011E940(-1.0f, 1.0f);
        qword w = NormalizeTo(QwToVf(VECTOR(x, y, z).q)) * VU_FLOAT(g);
        pso->SetAngularVelocity(w);
    }
    if (func_0013B500(pso, 0x5A))
        pso->SetTarget(plaunch->psoSource, plaunch->posTarget);
}
