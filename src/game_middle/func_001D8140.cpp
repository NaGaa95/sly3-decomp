// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_ASFIX: engine-divfix1
// func_001D8140: curve follower step. Projects the actor onto its path (func_001EF2A8), steers toward a lead point
// on the path (spring/damper blend of velocity and position error), pushes away from and around nearby bodies of the
// actor's region, integrates the motion and clamps it against the region geometry (func_001ED460).
// Port of the matched Sly 2 follower step (references/sly2/src/hand/func_00177F78.cpp) to the Sly 3 layout: the path
// mode/reverse handling is gone, the curve and limit tables are local .rodata, and the tuning values are literals.
// Notes on the shapes that reproduce the original:
//  - The avoidance block owns an object whose out-of-line destructor (func_002BE720, called with in-charge flag 2) runs
//    after the body loop; declaring it in that block gives the original stack slot 0x50.
//  - `accel` is a VV class object: its address is taken when it is constructed, so its pseudo (and its spill slot 0x90)
//    precedes the projected separation (0xA0).
//  - The integration reads the stored position through a local `pos` first, which gives the original VU registers of
//    the position and the half-step-squared scalar.
typedef int qword __attribute__((mode(TI)));
union VEC
{
    qword qw;
    float f[4];
};
struct VTENT
{
    short delta, pad;
    void *pfn;
};
struct XFM
{
    qword mat[3];
    qword pos;
};
struct BODY;
struct REGION
{
    char pad[0x108];
    BODY *pbodyFirst;
};
struct OBJECT;
struct BODY
{
    OBJECT *pobj;
    float dz;
    float sRadius;
    float gMass;
    REGION *pregion;
    char pad14[0x4C];
    BODY *pbodyNext;
};
struct GROUP
{
    char pad[0xDC];
    BODY *pbody;
};
struct OID
{
    int id;
};
struct OBJECT
{
    char pad[0xC];
    VTENT *pvt;
    char pad10[4];
    OID *poid;
    char pad18[0xC0];
    GROUP *pgroup;
    char padDC[0xE4];
    qword axis;
};
struct PATH;
struct FOLLOWER
{
    char pad[0x10];
    OBJECT *pactor;
    char pad14[0x1C];
    PATH *ppath;
    float s;
    int fNoCollide;
    char pad3C[0x14];
    float sSeparation;
    char pad54[0xC];
    qword pos;
    qword v;
    int fInit;
    char pad84[0x1C];
    int fFree;
};
struct CLQ
{
    float g0, g1, g2;
};
struct LM
{
    float gMin, gMax;
};
struct CLOCK
{
    float t, dt;
};
static const CLQ D_00324330 __attribute__((aligned(16))) = {200.0f, -0.5f, 0.0f};
static const LM D_00324340 __attribute__((aligned(16))) = {0.0f, 150.0f};
static const CLQ D_00324350 __attribute__((aligned(16))) = {0.5f, -1.0f, 0.0f};
struct SCOPE;
extern "C" {
extern LM D_00341FF0;
extern CLOCK D_0036BB98;
extern qword D_00317530, D_00317550, D_00317560;
void func_001EF2A8(PATH *ppath, float s, qword pos, VEC *ppos, VEC *pdir, float *ps);
float func_001EF588(PATH *ppath);
int func_001D8AC0(FOLLOWER *pfollower);
void func_00120A00(qword pos, qword p0, qword p1, VEC *ppos, float *pt, float *pdist);
int func_001ED460(REGION *pregion, qword pos, VEC *ppos);
void func_002BE720(SCOPE *pscope, int flags);
}
struct SCOPE
{
    ~SCOPE() { func_002BE720(this, 2); } /* the out-of-line destructor g++ calls for this automatic object */
};
struct VU_FLOAT
{
    qword qw;
    VU_FLOAT(float g) { __asm__("qmtc2.ni %1, %0" : "=j"(qw) : "r"(g)); }
};
struct VV
{
    qword q;
    VV(const qword &v) { q = v; }
    operator qword() const { return q; }
};
struct VU_VECTOR
{
    qword q;
    VU_VECTOR(const qword &v) { q = v; }
};
static inline float GXOfQw(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw));
    return x;
}
static inline float GXOfQwJ(qword qw)
{
    float x;
    __asm__("mtc1 %1, %0" : "=f"(x) : "r"(qw), "j"(qw)); /* allocation-only "j"(qw): the vector stays in a VF register */
    return x;
}
static inline float GZOfQw(qword qw)
{
    float z;
    __asm__("pextuw %0, $zero, %1" : "=r"(z) : "r"(qw));
    return z;
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwDot(const qword &a, const qword &b)
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
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(qw));
    return r;
}
/* length of v whose vmul.xyz reads its input as two "j" operands (allocation only) */
static inline qword QwLength2(qword v)
{
    qword qw;
    qword vfOne;
    __asm__("vmul.xyz %0, %2, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z"
            : "=j"(qw), "=j"(vfOne) : "j"(v), "j"(v));
    qword r;
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(r) : "j"(qw));
    return r;
}
/* length of v; copy receives v itself (allocation-only tied output, never written); the "r"(v) operands load v through a GPR */
#define QW_LENGTH_COPY(len, copy, v) \
    { \
        qword qwSq_, vfOne_; \
        __asm__("vmul.xyz %0, %3, %3\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" \
                : "=j"(qwSq_), "=j"(vfOne_), "=j"(copy) : "2"(v), "r"(v), "r"(v)); \
        __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(len) : "j"(qwSq_)); \
    }
static inline qword QwLengthXY(qword v)
{
    qword qw;
    __asm__("vmul.xy %0, %1, %1\n\tvaddy.x %0, %0, %0y" : "=j"(qw) : "j"(v));
    __asm__("vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(qw) : "0"(qw));
    return qw;
}
static inline qword QwDivLength(qword v, qword qwLen)
{
    qword qw;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(qw) : "j"(qwLen), "j"(v));
    return qw;
}
static inline qword QwScaleX(qword v, const VU_FLOAT &g)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(v), "j"(g.qw));
    return qw;
}
static inline qword QwAddScaled(qword a, qword b, const VU_FLOAT &g)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(a), "j"(b), "j"(g.qw));
    return qw;
}
static inline qword QwIntegrate(qword pos, qword v, const VU_FLOAT &g1, qword a, const VU_FLOAT &g2)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddax.xyzw $ACC, %2, %3x\n\tvmaddx.xyzw %0, %4, %5x"
            : "=j"(qw) : "j"(pos), "j"(v), "j"(g1.qw), "j"(a), "j"(g2.qw));
    return qw;
}
static inline qword QwCross(qword a, qword b)
{
    qword qw;
    __asm__("vopmula.xyz $ACC, %1, %2\n\tvopmsub.xyz %0, %2, %1" : "=j"(qw) : "j"(a), "j"(b));
    return qw;
}
static inline qword VecCombo(VU_FLOAT f1, VU_VECTOR v1, VU_FLOAT f2, VU_VECTOR v2)
{
    qword r;
    __asm__("vmulax.xyzw $ACC, %2, %1x\n\tvmaddx.xyzw %0, %4, %3x" : "=j"(r) : "j"(f1.qw), "j"(v1.q), "j"(f2.qw), "j"(v2.q));
    return r;
}
static inline VV VSub(VV a, VV b) { return QwSub(a, b); }
static inline VV VAddScaled(VV a, VV b, const VU_FLOAT &g) { return QwAddScaled(a, b, g); }
static inline VV VProjectOut(VV v, VV n) { return QwProjectOut(v, n); }
static inline VV VCross(VV a, VV b) { return QwCross(a, b); }
static inline VV VDot(VV a, VV b) { return QwDot(a.q, b.q); }
static inline VV VLength2(VV v) { return QwLength2(v); }
static inline VV DivSafe(VV v, VV len, VV fallback)
{
    if (GXOfQw(len) < 0.0001f)
        return fallback;
    return QwDivLength(v, len);
}
static inline float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (gMax < g)
        return gMax;
    return g;
}
static inline float GEvaluateClqLm(const CLQ *pclq, const LM *plm, float x)
{
    return GClamp(pclq->g0 + x * (pclq->g1 + x * pclq->g2), plm->gMin, plm->gMax);
}
static inline float GMax(float a, float b)
{
    return a < b ? b : a;
}
/* position row of the object's transform (virtual slot 36) */
static inline qword QwPosObj(OBJECT *pobj)
{
    VTENT *pvte = &pobj->pvt[36];
    return ((XFM * (*)(void *)) pvte->pfn)((char *)pobj + pvte->delta)->pos;
}
/* object velocity (virtual slot 38) */
static inline qword QwVelocity(OBJECT *pobj)
{
    VTENT *pvte = &pobj->pvt[38];
    return ((qword(*)(void *))pvte->pfn)((char *)pobj + pvte->delta);
}
extern "C" void func_001D8140(FOLLOWER *p)
{
    VEC point, dir, next, nextDir;
    qword posActor = QwPosObj(p->pactor);

    BODY *pbody = 0;
    if (p->pactor->pgroup)
        pbody = p->pactor->pgroup->pbody;
    REGION *pregion = 0;
    if (pbody)
        pregion = pbody->pregion;
    func_001EF2A8(p->ppath, p->s + 100.0f, posActor, &point, &dir, &p->s);
    p->sSeparation = GXOfQw(QwLengthXY(QwSub(point.qw, posActor)));
    float ds = GEvaluateClqLm(&D_00324330, &D_00324340, p->sSeparation);
    float gSpeed;
    if (!p->fFree && func_001D8AC0(p))
    {
        gSpeed = 0.0f;
        nextDir.qw = D_00317530;
        next.qw = posActor;
    }
    else
    {
        gSpeed = 500.0f;
        float dsClamp = ds;
        if (!p->fFree)
        {
            float sMin = -p->s;
            float sMax = func_001EF588(p->ppath) - p->s;
            dsClamp = GClamp(dsClamp, sMin, sMax);
            if (ds != dsClamp)
                gSpeed = 0.0f;
        }
        next.qw = QwAddScaled(point.qw, dir.qw, VU_FLOAT(dsClamp));
        nextDir.qw = dir.qw;
    }
    qword vGoal = QwScaleX(nextDir.qw, VU_FLOAT(gSpeed));
    qword vGoalCopy;
    __asm__("qmfc2.ni %0, %1" : "=r"(vGoalCopy) : "j"(vGoal)); /* GPR copy of vGoal */

    if (p->fInit)
    {
        p->v = vGoalCopy;
        p->pos = next.qw;
        p->fInit = 0;
    }
    VV accel = VecCombo(VU_FLOAT(7.5f), QwSub(vGoal, p->v), VU_FLOAT(30.0f), QwSub(next.qw, p->pos));
    if (!p->fNoCollide)
    {
        SCOPE scope;
        BODY *pbodySelf = p->pactor->pgroup->pbody;
        for (BODY *pbodyOther = pregion->pbodyFirst; pbodyOther; pbodyOther = pbodyOther->pbodyNext)
        {
            if (pbodyOther->sRadius == 0.0f)
                continue;
            if (pbodyOther->gMass == 0.0f)
                continue;
            OBJECT *pobj = pbodyOther->pobj;
            if (pobj->poid->id == p->pactor->poid->id)
                continue;
            VEC posOther;
            posOther.qw = QwPosObj(pobj);
            posOther.f[2] += pbodyOther->dz;
            qword dpos = QwSub(posActor, posOther.qw);
            if (__builtin_fabsf(GZOfQw(dpos)) > 250.0f)
                continue;
            qword vOther = QwVelocity(pobj);
            qword posPredict = VAddScaled(posOther.qw, vOther, VU_FLOAT(0.5f));
            dpos = VProjectOut(dpos, D_00317550);
            qword dposLater = VProjectOut(VSub(p->pos, posPredict), D_00317550);

            VEC normal;
            func_00120A00(D_00317560, dpos, dposLater, &normal, 0, 0);
            const qword *pqwZeroHere = &D_00317530;
            qword normalCopy;
            qword qwLen;
            QW_LENGTH_COPY(qwLen, normalCopy, normal.qw);
            if (GXOfQw(qwLen) < 0.0001f)
                normal.qw = *pqwZeroHere;
            else
                normal.qw = QwDivLength(normalCopy, qwLen);
            float sGap = GXOfQwJ(qwLen);
            sGap = GMax(0.0f, sGap - pbodyOther->sRadius - pbodySelf->sRadius);
            float gMass = pbodyOther->gMass / (pbodyOther->gMass + pbodySelf->gMass);
            if (sGap < 200.0f)
                accel = VAddScaled(accel, normal.qw, VU_FLOAT(gMass * (1.0f - sGap / 200.0f) * 10000.0f));
            if (sGap < 350.0f)
            {
                float g = 1.0f - sGap / 350.0f;
                qword dirNow = DivSafe(dpos, VLength2(dpos), D_00317530);
                g *= GEvaluateClqLm(&D_00324350, &D_00341FF0, GXOfQw(VDot(dirNow, p->pactor->axis)));
                if (g == 0.0f)
                    continue;
                accel = VAddScaled(accel, VCross(normal.qw, D_00317550), VU_FLOAT(gMass * g * 6000.0f));
            }
        }
    }
    float half = 0.5f;
    float dt = D_0036BB98.dt;
    accel = QwProjectOut(accel, D_00317550);
    qword pos = p->pos;
    qword posNext = QwIntegrate(pos, p->v, VU_FLOAT(dt), accel, VU_FLOAT(dt * (dt * half)));
    qword vNew = QwAddScaled(p->v, accel, VU_FLOAT(dt));
    qword vNext = vNew;
    if (!p->fNoCollide)
    {
        VEC posHit;
        if (func_001ED460(pregion, posNext, &posHit))
        {
            VEC normal;
            const qword *pqwZero = &D_00317530;
            normal.qw = QwProjectOut(QwSub(posHit.qw, posNext), D_00317550);
            qword qwLen = QwLength(normal.qw);
            if (GXOfQw(qwLen) < 0.0001f)
                normal.qw = *pqwZero;
            else
                normal.qw = QwDivLength(normal.qw, qwLen);
            if (1.0f < GXOfQwJ(qwLen))
            {
                float gClose = GXOfQwJ(QwDot(vNew, normal.qw));
                posNext = posHit.qw;
                if (gClose < 0.0f)
                    vNext = QwAddScaled(vNew, normal.qw, VU_FLOAT(-gClose));
            }
        }
    }
    p->pos = posNext;
    p->v = vNext;
}
