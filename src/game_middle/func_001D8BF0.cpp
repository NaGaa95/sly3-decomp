// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Allocation note: the duplicate "j"(v) input of QwLengthXY gives dpos the reference count that makes it a caller-saved vf pseudo (sqc2 in the call delay slot, lqc2 after) instead of a spill; the final moved test is written inline so it branches on c.lt.s directly.
// Steering toward the target point (same routine as Sly 2 func_00178EE0): after the base update, while mode 0, turns the
// ground-plane offset to the target into a speed (curve evaluated on its length, clamped) and hands it to the current
// movement choice (kind 0: speed + heading, kind 3: velocity vector in the actor frame); refreshes the progress timer.
typedef int qword __attribute__((mode(TI)));
struct MATRIX3 { float mat[3][4]; };
struct CLQ { float g0, g1, g2; };
struct LM { float gMin, gMax; };
struct VTE { short d; short pad; void *pfn; };
struct ACTOR { char pad[0xC]; VTE *vt; };
struct MODEL { char pad[0x10]; qword velocity; };
struct CONTROL { char pad[0x24]; void *animation; };
struct CHOICE { int kind; MODEL *model; CONTROL *control; };
struct DRIVER { char pad[0x40]; CHOICE *choice; };
struct P {
    char pad[0x10]; ACTOR *actor; int pad14; DRIVER *driver;
    char pad1C[0x3C - 0x1C]; unsigned int mode; char pad40[0x60 - 0x40]; qword target;
    char pad70[0xB4 - 0x70]; float rate; char padB8[8]; qword cached; float timeout;
};
struct CLOCK { float t, dt; };
struct VU_FLOAT { qword qw; VU_FLOAT() {} VU_FLOAT(float g) { __asm__("qmtc2 %1, %0" : "=j"(qw) : "r"(g)); } };
extern "C" {
extern CLQ D_00324360;
extern LM D_00341FF0;
extern CLOCK D_0036BB98;
extern qword D_00317550, D_00317560;
void func_001D89B0(P *);
void func_00138B68(void *, float);
void func_0024E8E8(ACTOR *, qword);
void func_00259678(CONTROL *, qword);
}
static inline float GFromVf(qword qw)
{
    float g;
    __asm__("qmfc2 %0, %1" : "=r"(g) : "j"(qw));
    return g;
}
static inline float GXOfQw(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw));
    return x;
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwDot(qword a, qword b)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(a), "j"(b));
    return qw;
}
static inline qword QwProjectOut(qword v, qword n)
{
    qword d = QwDot(v, n);
    qword al, ac;
    __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(al) : "j"(d), "j"(n));
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(ac) : "j"(v), "j"(al));
    return ac;
}
static inline qword QwLength(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline qword QwLengthXY(qword v)
{
    qword qw;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(qw) : "j"(v), "j"(v)); /* second "j"(v): allocation-only (one more reference to v: dpos is saved/restored around the call instead of being spilled) */
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline qword QwLengthUntied(qword v)
{
    qword qwSq;
    qword vfOne;
    qword qwLen;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qwSq), "=j"(vfOne) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qwLen) : "j"(qwSq));
    return qwLen;
}
static inline float GLength(qword v) { return GFromVf(QwLength(v)); }
static inline qword QwScaleX(qword qwVec, VU_FLOAT g)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(qwVec), "j"(g.qw));
    return qw;
}
static inline qword QwDotRowsMatP(MATRIX3 *pmat, qword qwV)
{
    qword qwLocal;
    qword qwTmp0, qwTmp1, qwTmp2, qwOnes;
    __asm__("vmul.xyzw %2, %5, %8\n\tvmaxw.xyzw %1, $vf0, $vf0w\n\tvmul.xyzw %3, %6, %8\n\tvmul.xyzw %4, %7, %8\n\tvadday.x $ACC, %2, %2y\n\tvmaddz.x %0, %1, %2z\n\tvaddax.y $ACC, %3, %3x\n\tvmaddz.y %0, %1, %3z\n\tvaddax.z $ACC, %4, %4x\n\tvmaddy.z %0, %1, %4y"
            : "=j"(qwLocal), "=&j"(qwOnes), "=&j"(qwTmp0), "=&j"(qwTmp1), "=&j"(qwTmp2)
            : "j"(*(qword *)pmat->mat[0]), "j"(*(qword *)pmat->mat[1]), "j"(*(qword *)pmat->mat[2]), "j"(qwV));
    return qwLocal;
}
static inline float GEvaluateClqLm(CLQ *pclq, LM *plm, float x)
{
    float g = pclq->g0 + x * (pclq->g1 + x * pclq->g2);
    float gMin = plm->gMin;
    float gMax = plm->gMax;
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
static inline qword ActorPosition(ACTOR *actor)
{
    VTE *e = &actor->vt[36];
    return ((qword *(*)(void *))e->pfn)((char *)actor + e->d)[3];
}
static inline MATRIX3 *ActorMatrix(ACTOR *actor)
{
    VTE *e = &actor->vt[36];
    return ((MATRIX3 *(*)(void *))e->pfn)((char *)actor + e->d);
}
extern "C" void func_001D8BF0(P *p)
{
    func_001D89B0(p);
    if (p->mode == 0)
    {
        qword pos = ActorPosition(p->actor);
        qword dpos = QwProjectOut(QwSub(p->target, pos), D_00317550);
        float g = GEvaluateClqLm(&D_00324360, &D_00341FF0, GXOfQw(QwLengthXY(dpos)));
        CHOICE *pchoice = p->driver->choice;
        switch (pchoice->kind)
        {
        case 0:
            func_00138B68(pchoice->control, p->rate * g);
            func_0024E8E8(p->actor, dpos);
            break;
        case 3:
        {
            qword qwLocal = QwDotRowsMatP(ActorMatrix(p->actor), dpos);
            qword qwFallback = D_00317560;
            float gSpeed = p->rate * g;
            gSpeed *= GXOfQw(QwLengthXY(pchoice->model->velocity));
            qword qwLen = QwLengthUntied(qwLocal);
            VU_FLOAT vuSpeed(gSpeed);
            qword qwDir;
            if (GXOfQw(qwLen) < 0.0001f)
            {
                qwDir = qwFallback;
            }
            else
            {
                __asm__("vdiv $Q, $vf0w, %0x\n\tvwaitq" : : "j"(qwLen));
                __asm__("vmulq.xyzw %0, %1, $Q" : "=j"(qwDir) : "j"(qwLocal));
            }
            func_00259678(pchoice->control, QwScaleX(qwDir, vuSpeed));
            func_00138B68(pchoice->control->animation, g);
            break;
        }
        }
        if (25.0f < GLength(QwSub(pos, p->cached)))
        {
            p->cached = pos;
            p->timeout = 1.5f;
        }
        else
        {
            p->timeout -= D_0036BB98.dt;
        }
    }
}
