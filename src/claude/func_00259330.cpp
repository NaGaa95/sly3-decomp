// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_00259330: one-time setup of four animated legs: segment, root velocity and speed (cf. Sly 2 func_0020C908).
typedef unsigned int uint;
typedef int qword __attribute__((mode(TI)));

struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));

struct XF;
struct KEY
{
    virtual void Load(void *pbis);
};
struct VECKEY : public KEY
{
    virtual void CacheSeg(XF *pxf);
    virtual void GetValue(float t, float svt, qword *ppos, qword *pv);
};
struct BLEND
{
    void *vtbl;
    void *pasegbl;
    void *amrsgc;
};
struct CHN
{
    int oid : 20;
    int ixf : 10;
    uint fStripped : 1;
    uint fScalar : 1;
    KEY *pkey;
};
struct MRSGC { int ib; int cmrsg; void *amrsg; };
struct ASEG
{
    char pad0[0x4C];
    int cchn;
    CHN *achn;
    char pad54[0x10];
    float tMax;
};
struct ASEGBL
{
    char pad0[0x4C];
    int cchn;
    CHN *achn;
    char pad54[0x50];
    int fUnkA4;
    char padA8[0x18];
    MRSGC *amrsgc;
};
struct XFX { char pad[0x9C]; int oid; };
struct BLGAIT
{
    float gWeight;
    ASEG *paseg;
    char ab08[8];
    qword vRoot;
    char ab20[0x20];
};
struct GAIT
{
    void *pstepplayer;
    ASEGBL *pasegbl;
    char ab08[8];
    BLGAIT abl[2];
    char ab90[0x14];
    int fLoaded;
};
struct VU_FLOAT { qword qw; };
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwDivVu(qword qw, VU_FLOAT g)
{
    qword qwRet;
    __asm__("vdiv $Q, $vf0w, %1x\n\tvwaitq\n\tvmulq.xyzw %0, %2, $Q" : "=j"(qwRet) : "j"(g.qw), "j"(qw));
    return qwRet;
}
struct E { ASEG *paseg; int pad[3]; qword v; float s; char ab24[8]; char ab2C[0x14]; };
struct S { E ae[4]; int fInit; };
extern "C" {
extern char D_00475480[];
ASEG *func_0017E1B8(void *psw, int n, ASEG *paseg, void *p);
CHN *func_00136EE0(ASEG *paseg, void *palo, int xfk, int fStripped);
void func_002592A8(void *pv, ASEG *paseg, int oid0, int oid1);
}
static inline qword QwSpeed(qword v)
{
    qword d, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=&j"(d), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(d) : "0"(d));
    return d;
}
// store the x lane of a VU register to memory (lane helper: qmfc2 + sw)
static inline void StoreX(float *pg, qword q)
{
    int n;
    __asm__("qmfc2.ni %0, %2\n\tsw %0, %1" : "=&r"(n), "=m"(*pg) : "j"(q));
}
extern "C" void func_00259330(S *p, void *pv)
{
    if (p->fInit)
        return;
    for (uint i = 0; i < 4; i++)
    {
        E *pe = &p->ae[i];
        ASEG *paseg = func_0017E1B8(D_00475480, 4, pe->paseg, pv);
        pe->paseg = paseg;
        if (!paseg)
            continue;
        CHN *pchn = func_00136EE0(paseg, pv, 1, 1);
        VECTOR4 vStart, vEnd;
        ((VECKEY *)pchn->pkey)->GetValue(0.0f, 1.0f, (qword *)&vStart, 0);
        ((VECKEY *)pchn->pkey)->GetValue(paseg->tMax, 1.0f, (qword *)&vEnd, 0);
        register qword qwE asm("vf1") = *(qword *)&vEnd; /* pin: end point in vf1 */
        qword qwDiff;
        __asm__("vsub.xyzw %0, %1, %2" : "=j"(qwDiff) : "0"(qwE), "j"(*(qword *)&vStart));
        VU_FLOAT vuT;
        __asm__("qmtc2 %1, %0" : "=j"(vuT.qw) : "rV"(*(int *)&paseg->tMax));
        qword v = QwDivVu(qwDiff, vuT);
        pe->v = v;
        StoreX(&pe->s, QwSpeed(v));
        func_002592A8(pe->ab24, paseg, 0x19B, 0x19C);
        func_002592A8(pe->ab2C, paseg, 0x19D, 0x19E);
    }
    p->fInit = 1;
}
