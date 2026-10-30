// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Adapted from the Sly 2 decomp (func_00189C40, RebuildJtXmg).
typedef int qword __attribute__((mode(TI)));
struct MATRIX4 { float mat[4][4]; } __attribute__((aligned(16)));
struct VU_FLOAT {
    qword qw;
    VU_FLOAT(float f) { __asm__("qmtc2 %1, %0" : "=j"(qw) : "r"(f)); }
};
struct ASEG;
struct XF;
struct ASEGA { unsigned char pad0[0x14]; ASEG *paseg; };
struct SMA { unsigned char pad0[0x30]; ASEGA *pasegaCur; };
struct EA { float tLocal; };
struct IKREC { XF *pxfGoal; unsigned char pad4[0x20 - 0x4]; qword qwPosIkh; unsigned char pad30[4]; float sUpper; float sLower; };
struct ALO { unsigned char pad0[0xA8]; IKREC *pikrec; };
struct JT {
    unsigned char pad0[0x50]; XF *pxfRoot;
    unsigned char pad54[0x10E8 - 0x54]; ASEGA *pasegaJanim;
    unsigned char pad10EC[0x113C - 0x10EC]; ASEGA *pasega113C; SMA *psma1140;
    unsigned char pad1144[0x19E0 - 0x1144]; int jts;
};
struct XMG {
    ASEG *paseg;
    int fValid;
    float sSphere;
    int unk_0x0c;
    qword posExtrem;
    qword posSphere;
    qword posUp;
    qword posDown;
    qword posSphereLow;
};
struct LSG {
    qword apos[2];
    qword anormal[2];
    float au[2];
    int lsgk;
    void *apsurf[2];
    void *pedge;
    int iiposSwap;
    LSG *plsgNext;
};
struct ACT5;
extern "C" {
extern qword D_00317550;
EA *func_00136880(ASEG *paseg, int oid);
void func_00137070(ASEG *paseg, JT *pso, float tLocal, float svt, XF *pxfEffect, XF *pxfRef, MATRIX4 *pmatOut, int f);
int func_00164B08(qword posSphere, float sRadius, qword pos0, qword pos1, int clsgMax, LSG *alsg);
void func_001AB308(JT *pjt, ALO *paloExtrem, float sRadius, ALO *paloHip, ACT5 *pact5, XMG *pxmg);
}
static inline qword QwTransformPos(MATRIX4 *pmat, qword qwPos)
{
    qword qwResult;
    __asm__("vmulax.xyz $ACC, %1, %5x\n\tvmadday.xyz $ACC, %2, %5y\n\tvmaddaz.xyz $ACC, %3, %5z\n\tvmaddw.xyz %0, %4, $vf0w"
            : "=j"(qwResult)
            : "j"(*(qword *)pmat->mat[0]), "j"(*(qword *)pmat->mat[1]), "j"(*(qword *)pmat->mat[2]), "j"(*(qword *)pmat->mat[3]),
              "j"(qwPos));
    return qwResult;
}
static inline qword QwSub(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwAdd(qword qw0, qword qw1)
{
    qword qw;
    __asm__("vadd.xyzw %0, %1, %2" : "=j"(qw) : "j"(qw0), "j"(qw1));
    return qw;
}
static inline qword QwAddScaled(qword qwBase, qword qwVec, VU_FLOAT gScale)
{
    qword qw;
    __asm__("vadda.xyzw $ACC, %1, $vf0\n\tvmaddx.xyzw %0, %2, %3x" : "=j"(qw) : "j"(qwBase), "j"(qwVec), "j"(gScale.qw));
    return qw;
}

void func_001AB308(JT *pjt, ALO *paloExtrem, float sRadius, ALO *paloHip, ACT5 *pact5, XMG *pxmg)
{
    ASEGA *pasega;
    if (pjt->jts == 0x17)
        pasega = pjt->pasegaJanim;
    else if (pjt->psma1140 != 0)
        pasega = pjt->psma1140->pasegaCur;
    else
        pasega = pjt->pasega113C;
    if (pasega->paseg != pxmg->paseg)
    {
        pxmg->paseg = pasega->paseg;
        float tLocal = 0.0f;
        EA *pea = func_00136880(pasega->paseg, 0x188);
        if (pea != 0)
        {
            tLocal = pea->tLocal;
        }
        MATRIX4 matExtrem;
        func_00137070(pasega->paseg, pjt, tLocal, 0.0f, (XF *)paloExtrem, pjt->pxfRoot, &matExtrem, 0);
        qword posExtrem = QwAddScaled(*(qword *)matExtrem.mat[3], D_00317550, VU_FLOAT(-sRadius));
        MATRIX4 matHip;
        func_00137070(pasega->paseg, pjt, tLocal, 0.0f, (XF *)paloHip, pjt->pxfRoot, &matHip, 0);
        MATRIX4 matIkh;
        func_00137070(pasega->paseg, pjt, tLocal, 0.0f, paloHip->pikrec->pxfGoal, pjt->pxfRoot, &matIkh, 0);
        qword posIkh = QwTransformPos(&matIkh, paloHip->pikrec->qwPosIkh);
        qword posSphereCenter = QwAdd(*(qword *)matHip.mat[3], QwSub(posExtrem, posIkh));
        pxmg->posSphere = posSphereCenter;
        pxmg->sSphere = paloHip->pikrec->sUpper + paloHip->pikrec->sLower + 10.0f;
        VU_FLOAT vfUp = VU_FLOAT(50.0f);
        VU_FLOAT vfDown = VU_FLOAT(-50.0f);
        LSG lsgClip;
        qword posLineUp = QwAddScaled(posExtrem, D_00317550, vfUp);
        qword posLineDown = QwAddScaled(posExtrem, D_00317550, vfDown);
        pxmg->fValid = func_00164B08(posSphereCenter, pxmg->sSphere, posLineUp, posLineDown, 1, &lsgClip) > 0;
        pxmg->posExtrem = posExtrem;
        pxmg->posUp = lsgClip.apos[0];
        pxmg->posDown = lsgClip.apos[1];
        pxmg->posSphereLow = QwAddScaled(pxmg->posSphere, D_00317550, VU_FLOAT(-pxmg->sSphere));
    }
}
