// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SMP;
float func_0011E3B8(float rad);
float GSmooth__FfffP3SMPPf(float gCur, float gTarget, float dt, struct SMP *psmp, float *pdgNext);
float func_0011E840(float radCur, float radTarget, float dt, struct SMP *psmp, float *pdradNext)
{
    float rad;
    rad = func_0011E3B8(radTarget - radCur);
    rad = GSmooth__FfffP3SMPPf(0.0f, rad, dt, psmp, pdradNext);
    rad = func_0011E3B8(radCur + rad);
    return rad;
}
