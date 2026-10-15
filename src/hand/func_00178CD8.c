// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
typedef struct { qword r[3]; } M3;
struct EMITVX { int c; float dTilt; float dPan; float tiltBase; float panBase; };
struct LM { float gMin; float gMax; };
extern qword D_00317530;
extern qword D_00317540;
float func_0011E940(float a, float b);
float func_0011E3B8(float g);
qword func_0011FDD8(float pan, float tilt, float r);
void func_0011FEA8(qword a, qword b, qword c, M3 *pm);

void func_00178CD8(struct EMITVX *pemitvx, float gRand, float sv, struct LM *plm,
                                                     qword *pnormal, int i, qword *pv)
{
    int c = pemitvx->c;
    int iTilt = i / c;
    int iPan = i % c;
    float tilt = pemitvx->tiltBase + (float)iTilt * pemitvx->dTilt;
    float pan = pemitvx->panBase + (float)iPan * pemitvx->dPan;
    U v;
    M3 m;
    qword r;
    if (gRand != 0.0f) {
        tilt += gRand * func_0011E940(-0.5f, 0.5f) * pemitvx->dTilt;
        pan += gRand * func_0011E940(-0.5f, 0.5f) * pemitvx->dPan;
    }
    tilt = func_0011E3B8(tilt + 1.5707964f);
    pan = func_0011E3B8(pan);
    v.q = func_0011FDD8(pan, tilt, func_0011E940(plm->gMin, plm->gMax));
    v.f[2] *= sv;
    m.r[2] = *pnormal;
    func_0011FEA8(*pnormal, D_00317530, D_00317540, &m);
    __asm__("vmulax.xyz $ACC, %2, %1x\n\tvmadday.xyz $ACC, %3, %1y\n\tvmaddz.xyz %0, %4, %1z"
            : "=j"(r) : "j"(v.q), "j"(m.r[0]), "j"(m.r[1]), "j"(m.r[2]));
    *pv = r;
}
