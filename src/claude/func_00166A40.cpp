// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 3 UpdateCmMat4 (Sly 2 func_0014DC58 in src/hand): jolt shake of the eye matrix, then one frustum and its transposed copy.
typedef int qword __attribute__((mode(TI)));
struct M3 { qword r[3]; };
union M4 { struct { qword r[4]; } q; M3 m3; float af[4][4]; };
struct CLQ { float g0, g1, g2, pad; };
struct LM { float gMin, gMax; };
struct CLOCK { float t; float dt; };
struct CM {
    char pad0[0x44]; int n44; char pad1[0x90 - 0x48]; M4 mat; char pad2[0x138 - 0xD0]; float gTanHalfX; float gTanHalfY;
    char pad3[0x170 - 0x140]; float agFrustumXyz[12]; char pad4[0x1A0 - 0x1A0]; M4 matProj; M4 matViewProj; union { qword aplaneFrustum[4]; float agPlane[4][4]; };
    char pad5[0x2A0 - 0x260]; int n2A0; char pad6[0x35C - 0x2A4]; float tJolt;
};
static const CLQ s_clqJolt = { 1.0f, -2.0f, 1.0f };
union QF { float af[4]; qword q; };
static const QF s_dposJolt = { { 0.0f, 0.0f, 0.0f, 0.0f } };
static const QF s_rotJolt = { { 0.05f, 0.0f, 0.0f, 0.0f } };
extern "C" {
extern CLOCK D_0036BB98;
extern float D_00344838;
extern LM D_00341FF0;
void func_0028FFD8(CM *pcm);
void func_00166580(M4 *pmEye, M4 *pmProj, M4 *pmOut);
float sinf(float);
M3 func_0011C930(qword v);
float *func_002BA818(float *pg, qword q);
M4 func_0011D558(M4 *pa, M4 *pb);
void func_00166690(M4 *pmat, qword *paplane, float gTanX, float gTanY);
void func_00166CE8(CM *pcm);
void func_00166A40(CM *pcm);
}
struct VU_FLOAT { qword qw; };
static inline qword QwMulX(qword qwRow, VU_FLOAT gScale)
{
    qword qw;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(qw) : "j"(qwRow), "j"(gScale.qw));
    return qw;
}
static inline VU_FLOAT VuFloatOfFloat(float g)
{
    VU_FLOAT v;
    __asm__("qmtc2.ni %1, %0" : "=j"(v.qw) : "r"(g));
    return v;
}
static inline float GEvaluateClqLm(const CLQ *pclq, LM *plm, float x)
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
void func_00166A40(CM *pcm)
{
    func_0028FFD8(pcm);
    if (pcm->n2A0 == pcm->n44)
        return;
    pcm->n2A0 = pcm->n44;
    M4 matEye;
    float dtJolt = D_0036BB98.t - pcm->tJolt;
    if (dtJolt > D_00344838)
    {
        func_00166580(&pcm->mat, &pcm->matProj, &pcm->matViewProj);
    }
    else
    {
        float gEnv = GEvaluateClqLm(&s_clqJolt, &D_00341FF0, dtJolt / D_00344838);
        float gJolt = sinf(dtJolt * 50.0f) * gEnv;
        {
            M3 matRot = func_0011C930(QwMulX(s_rotJolt.q, VuFloatOfFloat(gJolt)));
            func_002BA818(matEye.af[3], QwMulX(s_dposJolt.q, VuFloatOfFloat(gJolt)));
            matEye.m3 = matRot;
        }
        matEye.af[3][3] = 1.0f;
        matEye.af[2][3] = 0.0f;
        matEye.af[1][3] = 0.0f;
        matEye.af[0][3] = 0.0f;
        matEye = func_0011D558(&pcm->mat, &matEye);
        func_00166580(&matEye, &pcm->matProj, &pcm->matViewProj);
    }
    qword *paplane = pcm->aplaneFrustum;
    func_00166690(&pcm->mat, paplane, pcm->gTanHalfX, pcm->gTanHalfY);
    float *pgDst;
    int i;
    for (i = 0, pgDst = pcm->agFrustumXyz; i < 3; i++)
    {
        pgDst[0] = pcm->agPlane[0][i];
        pgDst[1] = pcm->agPlane[1][i];
        pgDst[2] = pcm->agPlane[2][i];
        pgDst[3] = pcm->agPlane[3][i];
        pgDst += 4;
    }
    func_00166CE8(pcm);
}
