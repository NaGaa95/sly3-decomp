// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
typedef int qword __attribute__((mode(TI)));
typedef unsigned int uint;
typedef int DI __attribute__((mode(DI)));
union U { qword q; float f[4]; int bits[4]; };
struct M4 { U r[4]; };
struct M3 { U r[3]; };
struct VECTOR4 { float x, y, z, w; };
struct BSP { BSP *pbspNeg, *pbspPos; void *psurf; };
struct LSG { qword apos[2]; qword anormal[2]; float au[2]; int lsgk; void *apsurf[2]; void *pedge; int iiposSwap; LSG *plsgNext; };
struct ALLOCREQ { int cb; int cbAlign; int pad; };
struct CTX { int a, b, c, d; };
extern "C" void *__3CTX(CTX *);
extern "C" void _$_3CTX(CTX *, int);
struct SOVT { char pad0[0xA4]; int stamp; };
struct SO { SOVT *pvt; char pad4[0x18 - 4]; DI grf; char pad20[0x7C - 0x20]; int cbsp; char pad80[4]; BSP *pbsp; char pad88[0xC0 - 0x88]; int stamp; };
struct VTE { short delta, pad; M4 *(*pfn)(void *); };
struct OBJ { char pad0[0xC]; VTE *vt; char pad10[0x30 - 0x10]; float bottom, top; char pad38[0xDC - 0x38]; void *filter; char padE0[0x1BC - 0xE0]; float angle; M3 mat; };
struct GAME;
extern GAME D_00475480;
extern const qword D_00317550;
extern "C" {
M3 func_0011C8C0(float g, qword axis);
qword *func_002BA818(qword *, qword);
void *memset(void *, int, uint);
void func_0018B1E0(SO *);
void *PvAllocSlot(ALLOCREQ *) asm("PvAllocSlot__FP8ALLOCREQ");
int func_00119C20(BSP *, BSP *, qword, float, int *, BSP **);
int func_00119BE8(BSP *, BSP *, qword, qword, int, LSG *);
int func_0024FC50(void *, SO *);
void func_0025D0D8(GAME *, qword, int (*)(void *, SO *), void *, float, int *, SO ***);
M3 func_0011CDC8(qword, qword);
void DecomposeRotateMatrixRad(M3 *, float *, qword *) asm("DecomposeRotateMatrixRad__FP7MATRIX3PfP6VECTOR");
}
static inline M4 *GetMatrix(OBJ *p) { return p->vt[36].pfn((char *)p + p->vt[36].delta); }
static inline void *PvAllocStack(int cb) { ALLOCREQ req; req.cb = cb; req.cbAlign = 0x10; return PvAllocSlot(&req); }
static inline float Length(qword v)
{
    qword d, one, l;
    float f;
    __asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "0"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    __asm__("qmfc2.ni %0,%1" : "=r"(f) : "j"(l));
    return f;
}
static inline float Max(float a, float b) { return a > b ? a : b; }
static inline qword Transform(const M4 &m, qword v)
{
    qword r;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(r) : "j"(m.r[0].q), "j"(m.r[1].q), "j"(m.r[2].q), "j"(m.r[3].q), "j"(v));
    return r;
}
struct VU_FLOAT { qword q; VU_FLOAT(const float &g) { __asm__("qmtc2.ni %1,%0" : "=j,!r"(q) : "r,m"(g)); } };
static inline qword AddScaled(qword a, qword b, const VU_FLOAT &s)
{
    qword r;
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(a), "j"(b), "j"(s.q));
    return r;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Cross(qword a, qword b) { qword r; __asm__("vopmula.xyz $ACC,%1,%2\n\tvopmsub.xyz %0,%2,%1" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword VLength(qword v)
{
    qword d, one, l;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    return l;
}
static inline float GFromVf(qword v)
{
    float g;
    __asm__("qmfc2.ni %0,%1" : "=r"(g) : "j"(v));
    return g;
}
static inline qword Div(qword v, qword l) { qword r; __asm__("vdiv $Q,$vf0w,%2x\n\tvwaitq\n\tvmulq.xyzw %0,%1,$Q" : "=j"(r) : "j"(v), "j"(l)); return r; }
static inline qword Normalize(qword v)
{
    qword fallback = D_00317550;
    qword l = VLength(v);
    if (GFromVf(l) < 0.0001f)
        return fallback;
    return Div(v, l);
}
struct VU_VECTOR4 { qword qw; };
inline M3 operator*(const M3 &matL, const M3 &matR) return mat
{
    qword qwL0 = matL.r[0].q;
    qword qwL1 = matL.r[1].q;
    qword qwL2 = matL.r[2].q;
    VU_VECTOR4 v0, v1, v2;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v0.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[0].q));
    *(VU_VECTOR4 *)&mat.r[0] = v0;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v1.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[1].q));
    *(VU_VECTOR4 *)&mat.r[1] = v1;
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(v2.qw) : "j"(qwL0), "j"(qwL1), "j"(qwL2), "j"(matR.r[2].q));
    *(VU_VECTOR4 *)&mat.r[2] = v2;
}
static inline void SetRot(M4 *pm, M3 m)
{
    pm->r[0].q = m.r[0].q;
    pm->r[1].q = m.r[1].q;
    pm->r[2].q = m.r[2].q;
    pm->r[2].bits[3] = 0;
    pm->r[1].bits[3] = 0;
    pm->r[0].bits[3] = 0;
}

static inline void BuildFrame(M4 *pm, const M3 &m, M4 *pmat)
{
    func_002BA818(&pm->r[3].q, pmat->r[3].q);
    pm->r[0].q = m.r[0].q;
    pm->r[1].q = m.r[1].q;
    pm->r[2].q = m.r[2].q;
    pm->r[3].f[3] = 1.0f;
    pm->r[2].bits[3] = 0;
    pm->r[1].bits[3] = 0;
    pm->r[0].bits[3] = 0;
}
struct WHL { qword apos[3]; float bottom, top; };
static inline void SetPoint2(qword *pdst, const LSG &best, qword world)
{
    qword pt;
    if (best.au[0] != 0.0f && ((VECTOR4 *)&best.anormal[0])->z >= 0.7f)
        pt = best.apos[0];
    else {
        pt = world;
        __asm__("" : : "r"(pt));
    }
    *pdst = pt;
}
extern "C" void func_0024FCA0(OBJ *obj, WHL *pwhl)
{
    qword *apos = pwhl->apos;
    M4 frame;
    BuildFrame(&frame, func_0011C8C0(obj->angle, D_00317550), GetMatrix(obj));
    struct { M4 orig; CTX ctx; } w;
    w.orig = frame;
    float radius = -3.402823466e+38f;
    for (uint i = 0; i < 3; i++)
        radius = Max(radius, Length(apos[i]));
    __3CTX(&w.ctx);
    int cso;
    SO **aso;
    func_0025D0D8(&D_00475480, frame.r[3].q, func_0024FC50, obj->filter, radius, &cso, &aso);
    int cbsp = 0;
    int i;
    for (i = 0; i < cso; i++)
        cbsp += aso[i]->cbsp;
    {
        int lim = 0x2AAA;
        if (cbsp > lim - 1)
            cbsp = lim;
    }
    int cbspLeft;
    BSP *pbsp;
    pbsp = (BSP *)PvAllocStack(cbsp * sizeof(BSP));
    cbspLeft = cbsp;
    BSP **aroot = (BSP **)PvAllocStack(cso * sizeof(BSP *));
    int croot = 0;
    for (i = 0; i < cso; i++) {
        SO *so = aso[i];
        if (so->grf & 0x20000)
            continue;
        if (so->stamp != so->pvt->stamp)
            func_0018B1E0(so);
        if (func_00119C20(so->pbsp, (BSP *)0x7FFFFFFF, frame.r[3].q, radius, &cbspLeft, &pbsp) == 2)
            aroot[croot++] = pbsp - 1;
    }
    for (int pass = 0; pass < 2; pass++) {
        qword apt[3];
        uint j = 0;
        qword *ppos;
        do {
            ppos = apos + j;
            qword world = Transform(frame, *ppos);
            // volatile read: this load must issue after the spill store of world (sched2 order)
            qword up = *(volatile const qword *)&D_00317550;
            qword top = AddScaled(world, up, VU_FLOAT(pwhl->top));
            qword bottom = AddScaled(world, up, VU_FLOAT(pwhl->bottom));
            LSG best;
            memset(&best, 0, sizeof(best));
            float u = 3.402823466e+38f;
            for (int k = 0; k < croot; k++) {
                LSG alsg[2];
                int clsg = func_00119BE8(aroot[k], (BSP *)0x7FFFFFFF, top, bottom, 2, alsg);
                int j = 0;
                if (clsg > 0 && alsg[0].au[0] == 0.0f)
                    j = 1;
                if (j < clsg && alsg[j].au[0] < u) {
                    u = alsg[j].au[0];
                    best = alsg[j];
                }
            }
            SetPoint2(apt + j, best, world);
            j++;
        } while (ppos + 1 < apos + 3);
        qword normal = Normalize(Cross(Sub(apt[1], apt[0]), Sub(apt[2], apt[0])));
        M4 *porig = &w.orig;
        M3 rot = func_0011CDC8(w.orig.r[2].q, normal);
        float angle;
        VECTOR4 axis;
        DecomposeRotateMatrixRad(&rot, &angle, (qword *)&axis);
        if (0.6f < angle)
            rot = func_0011C8C0(0.6f, *(qword *)&axis);
        SetRot(&frame, rot * *(M3 *)porig);
    }
    obj->mat = *(M3 *)&frame;
    _$_3CTX(&w.ctx, 2);
}
