// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Update a vehicle's engine/skid sound mix from speed, wheel slip and throttle state.
struct SMP { float gSpring; float gDamp; float dtMax; };
struct LM { float gMin; float gMax; };
struct SREF { void *object; };
struct WHEEL { char pad0[0xC]; float slip; char pad10[4]; float load; char pad18[0x60 - 0x18]; };
struct CAR {
    char pad0[0x190]; struct WHEEL awheel[4]; char pad310[0x32C - 0x310]; float speedMax;
    char pad330[0x33C - 0x330]; float speed; char pad340[0x3C8 - 0x340];
    int idEngine0; int idEngine1; char pad3D0[0x3D8 - 0x3D0]; int idReverse; char pad3DC[0x3E4 - 0x3DC];
    struct SREF engine0; struct SREF engine1; void *skid0; void *skid1; struct SREF reverse;
    char pad3F8[0x400 - 0x3F8]; float speedSmooth; float volume; float rpm; float throttle; float brake;
};
float fabsf(float);
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern struct LM D_00341FF0;
float func_0011E598(const struct SMP *, float *, float, float, float);
float func_0027A610(float);
void func_00244E08(void *, float);
void func_00244ED0(void *, float);
void func_00244CA8(void *, float);
void func_002BBCD8(struct SREF *, void *);
void *func_002459F8(int);
void func_00244F08(void *, void *);
static inline float GLimit(float g, float gMin, float gMax)
{
    if (g < gMin)
        return gMin;
    if (g > gMax)
        return gMax;
    return g;
}
static inline float GClamp(float g)
{
    return GLimit(g, 0.0f, 1.0f);
}
static inline float GLimitLm(const struct LM *plm, float g)
{
    return GLimit(g, plm->gMin, plm->gMax);
}
static inline float GPoly(const float *a, float x)
{
    return a[0] + x * (a[1] + x * a[2]);
}
static inline float GLerpLm(const struct LM *plm, float t)
{
    return (1.0f - t) * plm->gMin + t * plm->gMax;
}
static inline void StopSound(struct SREF *ref, float fade)
{
    if (ref && ref->object) {
        func_00244CA8(ref->object, fade);
        func_002BBCD8(ref, 0);
    }
}
static inline void StartSound(struct SREF *ref, const int *pid)
{
    if (!ref->object) {
        void *v = func_002459F8(*pid);
        func_00244F08(v, 0);
        func_002BBCD8(ref, v);
    }
}
void func_0027A658(struct CAR *p)
{
    static const struct SMP s_smpSpeed = { 2.0f, 0.0f, 0.25f };
    static const struct LM s_lmPitch0 = { 0.0f, 0.3f };
    static const struct LM s_lmPitch1 = { -0.3f, 0.0f };
    static const float s_aThrottle[4] = { -0.01f, 1.26f, -0.5f, 0.0f };
    static const float s_aBrake[4] = { -0.1f, 3.0f, -1.9f, 0.0f };
    static const float s_aRpm[4] = { -1.25f, 1.0f, 0.0f, 0.0f };
    static const float s_aRpmScale[4] = { 0.0f, 2.0f, 0.0f, 0.0f };
    static const struct SMP s_smpVolume = { 10.0f, 0.0f, 0.1f };
    static const float s_aThrottleMix[4] = { -0.5f, 1.25f, 0.0f, 0.0f };
    static const float s_aBrakeMix[4] = { 0.75f, 0.5f, 0.0f, 0.0f };
    static const float s_aRpmMix[4] = { 1.0f, 0.0f, 0.0f, 0.0f };
    float slip;
    float mix;
    float gThrottle, gBrake, gRpm, gScale;
    float wThrottle, wBrake, sum;
    float vol;
    int i;
    void *snd;
    p->speedSmooth = func_0011E598(&s_smpSpeed, 0, p->speedSmooth, fabsf(p->speed) / p->speedMax, g_clock.dt);
    slip = 0.0f;
    for (i = 2; i < 4; i++) {
        struct WHEEL *pw = &p->awheel[i];
        slip += fabsf(pw->slip) * pw->load * 0.5f / p->speedMax;
    }
    mix = p->speedSmooth * 0.39999998f + slip * 0.6f;
    snd = p->skid0;
    if (snd)
        func_00244E08(snd, func_0027A610(1.0f - mix));
    snd = p->skid1;
    if (snd)
        func_00244E08(snd, func_0027A610(mix));
    if (p->skid0)
        func_00244ED0(p->skid0, GLerpLm(&s_lmPitch0, mix));
    if (p->skid1)
        func_00244ED0(p->skid1, GLerpLm(&s_lmPitch1, mix));
    gThrottle = GLimitLm(&D_00341FF0, GPoly(s_aThrottle, GClamp(p->throttle)));
    gBrake = GLimitLm(&D_00341FF0, GPoly(s_aBrake, GClamp(p->brake)));
    gRpm = GLimitLm(&D_00341FF0, GPoly(s_aRpm, p->rpm));
    gScale = GLimitLm(&D_00341FF0, GPoly(s_aRpmScale, p->rpm));
    wThrottle = gThrottle * gScale;
    wBrake = gBrake * gScale;
    sum = wThrottle + wBrake + gRpm;
    vol = GClamp(sum);
    vol = func_0011E598(&s_smpVolume, 0, p->volume, vol, g_clock.dt);
    p->volume = vol;
    if (vol <= 0.0f) {
        StopSound(&p->engine0, 0.0f);
        StopSound(&p->engine1, 0.0f);
    } else {
        float t;
        StartSound(&p->engine0, &p->idEngine0);
        StartSound(&p->engine1, &p->idEngine1);
        t = wThrottle * GLimitLm(&D_00341FF0, GPoly(s_aThrottleMix, GClamp(p->throttle)))
          + wBrake * GLimitLm(&D_00341FF0, GPoly(s_aBrakeMix, GClamp(p->brake)))
          + gRpm * GLimitLm(&D_00341FF0, GPoly(s_aRpmMix, p->rpm));
        if (sum != 0.0f)
            t /= sum;
        snd = p->engine0.object;
        if (snd)
            func_00244E08(snd, func_0027A610(p->volume * (1.0f - t)));
        snd = p->engine1.object;
        if (snd)
            func_00244E08(snd, func_0027A610(p->volume * t));
    }
    if (p->speed >= 0.0f)
        StopSound(&p->reverse, 0.0f);
    else
        StartSound(&p->reverse, &p->idReverse);
}
