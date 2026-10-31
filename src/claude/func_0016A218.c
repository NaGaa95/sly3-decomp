// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0016A218: adapted from Sly 2 func_00150160 (joystick-driven camera dolly/pan update).
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
struct POLY { float c0, c1, c2; };
struct SMP { float a, b, c; };
struct LM { float gMin, gMax; };
static const struct POLY s_poly = { 2.0f, 0.0f, -1.0f };
static const struct SMP s_smp = { 1.0f, 0.0f, 0.2f };
static const struct LM s_lm = { 0.0f, 1.3f };
extern struct LM D_00341FF0, D_00341FF8;
struct CM { char pad[0x118]; float g118; };
struct SND { char pad[0x5A]; short c5A; };
struct JOY { char pad[0x10]; float g10; };
struct X {
    struct CM *pcm; char pad4[0x24 - 0x4]; float g24; float g28; float g2C; float g30; float g34; float g38; int pad3C;
    float g40; float g44; struct SND *p48; int pad4C; float g50; float g54; float g58; float g5C;
};
void func_00169E78(struct X *p);
struct JOY *func_00169EB0(struct X *p);
float func_0011EE68(const struct LM *plm, float g);
void func_00244ED0(struct SND *p, float g);
void func_00244E08(struct SND *p, float g);
void func_00244C70(struct SND *p);
void func_00244C28(struct SND *p);
void func_00167960(struct CM *p, float g);
void func_001A7B38(struct JOY *p, int n, float *pgPan, float *pgTilt);
float func_0011E560(float g, float gMax);
float GSmooth__FfffP3SMPPf(float gCur, float gTarget, float dt, const struct SMP *psmp, float *pdgNext);
float func_0011E3B8(float g);
qword func_0016A078(struct X *p);
qword func_00169FF0(struct X *p);
void func_00166E48(struct CM *p, qword a, qword b, float c, float d);
void func_00168670(struct CM *p, int n);

static __inline__ float GClamp(float g, float gMin, float gMax)
{
    if (g < gMin) return gMin;
    if (gMax < g) return gMax;
    return g;
}

static __inline__ float GClamp2(float g, float gMin, float gMax)
{
    if (g < gMin) g = gMin;
    else if (gMax < g) g = gMax;
    return g;
}

void func_0016A218(struct X *p)
{
    float x, u, dt;
    struct { float pan, tilt, gMin, gMax; } s;
    struct JOY *pjoy;
    func_00169E78(p);
    pjoy = func_00169EB0(p);
    x = p->g34;
    p->g38 = (s_poly.c0 + x * (s_poly.c1 + x * s_poly.c2)) * pjoy->g10 * __builtin_fabsf(pjoy->g10);
    x += p->g38 * g_clock.dt;
    p->g34 = x = GClamp2(x, 0.0f, 1.0f);
    if (p->g38 != 0.0f && 0.0f < x && x < 1.0f) {
        struct SND *ps = p->p48;
        func_00244ED0(ps, func_0011EE68(&D_00341FF8, __builtin_fabsf(p->g38)));
        ps = p->p48;
        func_00244E08(ps, func_0011EE68(&D_00341FF0, __builtin_fabsf(p->g38) * 0.5f + 0.5f));
        if (p->p48->c5A > 0)
            func_00244C70(p->p48);
    } else {
        if (p->p48->c5A <= 0)
            func_00244C28(p->p48);
    }
    u = 1.0f - p->g34;
    func_00167960(p->pcm, (1.0f - u) * p->g40 + u * p->g44);
    func_001A7B38(pjoy, 1, &s.pan, &s.tilt);
    s.pan = p->g2C + func_0011E560(s.pan - p->g2C, g_clock.dt * 10.0f);
    s.tilt = p->g30 + func_0011E560(s.tilt - p->g30, g_clock.dt * 10.0f);
    dt = g_clock.dt * 0.5f;
    {
        GSmooth__FfffP3SMPPf(p->g24, p->g50, dt, &s_smp, &s.gMin);
        GSmooth__FfffP3SMPPf(p->g24, p->g54, dt, &s_smp, &s.gMax);
        p->g2C = GClamp(s.pan, s.gMin, s.gMax);
        GSmooth__FfffP3SMPPf(p->g28, p->g58, dt, &s_smp, &s.gMin);
        GSmooth__FfffP3SMPPf(p->g28, p->g5C, dt, &s_smp, &s.gMax);
        p->g30 = GClamp(s.tilt, s.gMin, s.gMax);
    }
    {
        float k = (1.0f - p->pcm->g118) * s_lm.gMin + p->pcm->g118 * s_lm.gMax;
        p->g24 += k * p->g2C * g_clock.dt;
        p->g28 += k * p->g30 * g_clock.dt;
    }
    if (6.2831855f <= p->g54 - p->g50)
        p->g24 = func_0011E3B8(p->g24);
    func_00166E48(p->pcm, func_0016A078(p), func_00169FF0(p), 0.0f, 0.0f);
    func_00168670(p->pcm, 2);
}
