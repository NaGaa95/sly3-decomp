// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00276510: CheckFocusVisible - Sly 3 form of Sly 2 CheckFocusVisible__FP8CPFOLLOW (0x2236E8), no pins.
// Sly 3: the sample offsets come from the focus (count +0x58, table +0x5C, up to 8 -> aqw[14]), the camera is
// pcmpart->pcm (positions via vtable slot 36 +0x30), CTX scope, both loops index aqw[3 + i] (strength-reduced).
// New data symbol D_00349FA0.
typedef int qword __attribute__((mode(TI)));
struct SO;
struct SOPART;
struct SW;
struct VTE { short delta, pad; void *(*fn)(void *); };
struct OBJ { char pad[0xC]; VTE *vt; };
struct CM { char pad[0xC]; VTE *vt; char pad10[0x144 - 0x10]; float sNearClip; char pad148[0x2F4 - 0x148]; int nCut; };
struct TN { char pad[0x140]; int fNoCamClip; };
struct CMPART { CM *pcm; char pad4[0x1C]; TN *ptn; char pad24[4]; OBJ *pvHero; char pad2C[0x110 - 0x2C]; float tLastSeen; float tLastCheck; };
struct FOCUS { char pad[0x58]; int cpos; qword *apos; };
struct VECTOR4 { float x, y, z, w; };
struct CLOCK { float t; float dt; };
extern CLOCK g_clock;
extern SW D_00475480;
extern int D_00349FA0;
extern qword D_00317550;
extern qword D_00317530;
extern "C" {
int func_001A9478(SW *psw, int n);
void func_00166548(CM *pcm);
int func_00167578(void *pv, SO *pso);
void func_0025CF18(SW *psw, qword posMin, qword posMax, int (*pfnFilter)(void *, SO *), int nUnk, int *pcpso, SOPART ***papso);
qword ConvertCmWorldToScreen(CM *pcm, qword pos) asm("func_001678C8");
qword ConvertCmScreenToWorld(CM *pcm, qword ndc) asm("func_00167838");
int FFindCmClearInterval(int cpsopart, SOPART **apsopart, qword posFrom, qword posTo, float duMin, float *puEnter, float *puExit) asm("func_00166F08");
}
struct CTX { int a; CTX(); ~CTX(); };
static inline qword Pos(OBJ *o) { VTE *v = &o->vt[36]; return *(qword *)((char *)v->fn((char *)o + v->delta) + 0x30); }
static inline qword PosCm(CM *o) { VTE *v = &o->vt[36]; return *(qword *)((char *)v->fn((char *)o + v->delta) + 0x30); }
static inline qword QwSub(qword qw0, qword qw1) { qword qw; __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1)); return qw; }
static inline qword QwAdd(qword qw0, qword qw1) { qword qw; __asm__("vadd.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1)); return qw; }
static inline float GFromVf(qword qw) { float g; __asm__("qmfc2.ni %0, %1" : "=r"(g) : "j"(qw)); return g; }
static inline qword QwLengthUntied(qword v)
{
    qword qwSq, vfOne, qwLen;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(qwSq), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qwLen) : "j"(qwSq));
    return qwLen;
}
static inline qword QwCross(qword a, qword b) { qword qw; __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(qw) : "j"(a), "j"(b)); return qw; }
static inline qword QwScaleByInverse(qword v, qword qwLen)
{
    qword qw;
    __asm__("vdiv $Q, $vf0w, %0x\n\tvwaitq" : : "j"(qwLen));
    __asm__("vmulq.xyzw %0, %1, $Q" : "=j"(qw) : "j"(v));
    return qw;
}
static inline qword QwMiniXyz(qword qw0, qword qw1) { qword qw; __asm__("vmini.xyz %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1)); return qw; }
static inline qword QwMaxXyz(qword qw0, qword qw1) { qword qw; __asm__("vmax.xyz %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1)); return qw; }
static inline qword QwAxesXyz(qword qwV, qword qwBack, qword qwSide, qword qwUp)
{
    qword qw;
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z" : "=j"(qw) : "j"(qwV), "j"(qwBack), "j"(qwSide), "j"(qwUp));
    return qw;
}
extern "C" void func_00276510(CMPART *pcmpart, FOCUS *pfocus)
{
    OBJ *plo = pcmpart->pvHero;
    if (func_001A9478(&D_00475480, -1) || pcmpart->pcm->nCut) {
        float t = g_clock.t;
        pcmpart->tLastCheck = t;
        pcmpart->tLastSeen = t;
        return;
    }
    if (pcmpart->ptn != 0 && pcmpart->ptn->fNoCamClip != 0)
        return;
    if (D_00349FA0 != 0)
        return;
    if (0.5f < g_clock.t - pcmpart->tLastCheck) {
        func_00166548(pcmpart->pcm);
        return;
    }
    if (g_clock.t - pcmpart->tLastSeen < 0.5f)
        return;
    qword aqw[14];
    int i;
    aqw[0] = aqw[1] = PosCm(pcmpart->pcm);
    qword qwUp = D_00317550;
    aqw[13] = qwUp;
    qword qwToHero = QwSub(Pos(plo), PosCm(pcmpart->pcm));
    qword qwCross = QwCross(qwUp, qwToHero);
    qword qwFallback = D_00317530;
    qword qwLen = QwLengthUntied(qwCross);
    qword qwSide;
    if (GFromVf(qwLen) < 0.0001f)
        qwSide = qwFallback;
    else
        qwSide = QwScaleByInverse(qwCross, qwLen);
    aqw[12] = qwSide;
    aqw[11] = QwCross(aqw[13], qwSide);
    for (i = 0; i < pfocus->cpos; i++) {
        qword pos = QwAdd(Pos(plo), QwAxesXyz(pfocus->apos[i], aqw[11], aqw[12], aqw[13]));
        aqw[0] = QwMiniXyz(aqw[0], pos);
        aqw[1] = QwMaxXyz(aqw[0], pos);
        aqw[3 + i] = pos;
    }
    CTX scope;
    int cpso;
    SOPART **apso;
    func_0025CF18(&D_00475480, aqw[0], aqw[1], func_00167578, 0, &cpso, &apso);
    for (i = 0; i < pfocus->cpos; i++) {
        aqw[2] = ConvertCmWorldToScreen(pcmpart->pcm, aqw[3 + i]);
        ((VECTOR4 *)&aqw[2])->z = pcmpart->pcm->sNearClip;
        aqw[2] = ConvertCmScreenToWorld(pcmpart->pcm, aqw[2]);
        float uExit;
        if (FFindCmClearInterval(cpso, apso, aqw[3 + i], aqw[2], 0.0f, 0, &uExit) && 1.0f <= uExit) {
            pcmpart->tLastSeen = g_clock.t;
            break;
        }
    }
    if (g_clock.t - pcmpart->tLastSeen > 1.5f)
        func_00166548(pcmpart->pcm);
}
