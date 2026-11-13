// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001AFBE8: Sly hanging from a hook, each frame (cf. Sly 2 UpdateSlyHangFollow, func_0018DF60).
typedef int qword __attribute__((mode(TI)));
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
struct MATRIX3 { qword r[3]; };
struct M4 { qword r[4]; };
struct VTE { short d; short pad; void *pfn; };
struct VT { char pad[0x120]; VTE eMat; char pad128[0x148 - 0x128]; VTE eAngVel; };
struct LO { char pad[0xC]; VT *pvt; };
struct CLQ { float g0, g1, g2; };
struct LM { float gMin, gMax; };
struct HOOK : LO { char pad10[0x130 - 0x10]; CLQ clq; };
struct PADCTL { float x, y, uJoy; };
struct BL { float gWeight; int pad[2]; };
struct ASEGBL;
struct SMP;
struct SLY : LO {
    char pad10[0x134 - 0x10];
    PADCTL *ppadctl;    /* 0x134 */
    char pad138[0x1C0 - 0x138];
    MATRIX3 matHeading; /* 0x1C0 */
    char pad1F0[0x19F4 - 0x1F0];
    HOOK *phook;        /* 0x19F4 */
    char pad19F8[0x1E20 - 0x19F8];
    BL abl[4];          /* 0x1E20 */
    ASEGBL *pasegbl;    /* 0x1E50 */
    float gHangAmount;  /* 0x1E54 */
    float gHangWeight;  /* 0x1E58 */
};
struct CLOCK { float t; float dt; };
extern "C" {
extern CLOCK g_clock;
extern qword D_00317550;
extern SMP D_00322B10;
extern LM D_00341FF8;
void func_0011C798(MATRIX3 *pmat);
void func_0011DDA8(M4 *pmatCur, MATRIX3 *pmatTarget, SMP *psmp, void *pv, float dt, qword *pw);
LO *func_001F4A80(LO *plo);
qword func_001C94E8(void *pxf, HOOK *phook, qword vec);
void func_00148938(ASEGBL *pasegbl);
void func_001AFBE8(SLY *p);
}
static inline M4 *Matrix(LO *p) { VTE *e = &p->pvt->eMat; return ((M4 *(*)(void *))e->pfn)((char *)p + e->d); }
static inline void SetAngVelocity(LO *p, qword v) { VTE *e = &p->pvt->eAngVel; ((void (*)(void *, qword))e->pfn)((char *)p + e->d, v); }
struct VU_FLOAT { qword q; VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); } };
struct VECTOR3 {
    qword q;
    VECTOR3(float gX, float gY, float gZ)
    {
        int iTmp;
        __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
                : "=&r"(q), "=&r"(iTmp) : "f"(gX), "f"(gY), "f"(gZ));
    }
};
static inline qword MulM3V(M4 *pm, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r) : "j"(pm->r[0]), "j"(pm->r[1]), "j"(pm->r[2]), "j"(v));
    return r;
}
static inline qword QwScale(qword v, VU_FLOAT s)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
static inline qword QwLength(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    qword qwLen;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qwLen) : "j"(qw));
    return qwLen;
}
static inline float GFromVf(qword qw) { float g; __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw)); return g; }
static inline qword Normalize(qword a, qword fallback)
{
    qword qwLen = QwLength(a);
    qword d = fallback;
    if (GFromVf(qwLen) < 0.0001f) {} else
        __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(d) : "j"(qwLen), "j"(a));
    return d;
}
static __inline__ float GetY(qword q) { register qword t __asm__("$3"); /* pin: phook pointer takes v0 */ __asm__ __volatile__("qmfc2.ni %0,%1" : "=r"(t) : "j"(q)); float y; __asm__("prot3w %0,%1" : "=&r"(y) : "r"(t)); return y; }
static inline float GEvaluateClq(CLQ *pclq, float x) { return pclq->g0 + x * (pclq->g1 + x * pclq->g2); }
static inline float GLimitLm(LM *plm, float g)
{
    float gMin = plm->gMin, gMax = plm->gMax;
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
static inline float GMaxOf(float a, float b) { return (a > b) ? a : b; }
extern "C" void func_001AFBE8(SLY *p)
{
    VECTOR4 vecAngular;
    M4 *pm = Matrix(p->phook);
    p->matHeading.r[0] = pm->r[0];
    p->matHeading.r[1] = pm->r[1];
    p->matHeading.r[2] = pm->r[2];
    func_0011C798(&p->matHeading);
    func_0011DDA8(Matrix(p), &p->matHeading, &D_00322B10, 0, g_clock.dt * 0.5f, (qword *)&vecAngular);
    SetAngVelocity(p, *(qword *)&vecAngular);
    LO *pcm = func_001F4A80(p);
    PADCTL *pc = p->ppadctl;
    qword vec; __asm__("qmtc2.ni %1, %0" : "=j"(vec) : "r"(VECTOR3(0.0f, -pc->x, pc->y).q));
    vec = MulM3V(Matrix(pcm), vec);
    vec = func_001C94E8(0, p->phook, vec);
    qword vecN = Normalize(vec, QwScale(D_00317550, VU_FLOAT(-1.0f)));
    float g = GLimitLm(&D_00341FF8, GEvaluateClq(&p->phook->clq, GetY(vecN)));
    p->gHangAmount = g;
    float gZero = 0.0f;
    float gOne = 1.0f;
    float gRight = GMaxOf(gZero, g);
    float gLeft = GMaxOf(gZero, -g);
    float gMiddle = gOne - gRight - gLeft;
    float w = p->ppadctl->uJoy;
    p->gHangWeight = w;
    p->abl[0].gWeight = gOne - w;
    p->abl[3].gWeight = gRight * w;
    p->abl[2].gWeight = gMiddle * w;
    p->abl[1].gWeight = gLeft * w;
    func_00148938(p->pasegbl);
}
