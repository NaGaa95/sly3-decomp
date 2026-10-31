// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SMP { float gMaxSpeed; float gMinSpeed; float rSpeed; };
struct SMPA { struct SMP smp; float gAccel; };
float GSmooth__FfffP3SMPPf(float gCur, float gTarget, float dt, struct SMP *psmp, float *pdgNext);
float func_0011E730(float gCur, float dgCur, float gTarget, float dt, struct SMPA *psmpa, float *pdgNext)
{
    float dgNext;
    float g = GSmooth__FfffP3SMPPf(gCur, gTarget, dt, &psmpa->smp, &dgNext);
    if (psmpa->gAccel > 0.0f) {
        float ddg = psmpa->gAccel * dt;
        float dgMax = dgCur + ddg;
        float dgMin = dgCur - ddg;
        if (dgNext > dgMax) {
            dgNext = dgMax;
            g = gCur + dgCur * dt + 0.5f * psmpa->gAccel * dt * dt;
        } else if (dgNext < dgMin) {
            dgNext = dgMin;
            g = gCur + dgCur * dt - 0.5f * psmpa->gAccel * dt * dt;
        }
    }
    if (pdgNext)
        *pdgNext = dgNext;
    return g;
}
