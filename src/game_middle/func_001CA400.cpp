// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame update of a spinning object: pauses/resumes its sound while the clock is stopped, steers the spin speed
// toward a target (mode 1 follows a direction, mode 2 settles back to angle 0), turns the rig by the spin angle
// (model matrix * rotation about the axis * object matrix, passed to the rig's virtual SetMatrix-style slot),
// keeps the target's x offset inside a window, drives the near/on light objects and plays an effect on angle steps.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { qword q; float f[4]; } U;
struct SMP { float gA, gB, gC; };
struct LM { float gMin, gMax; };
struct VT { short delta, pad; void *fn; };
struct LO { char pad0[0xC]; VT *vt; char pad10[0x28 - 0x10]; unsigned long flags; };
struct HOLDER { char pad0[0xC]; VT *vt; };
struct HANDLE
{
    HOLDER *p;
    HANDLE(const HANDLE &h);
    ~HANDLE()
    {
        if (p)
        {
            VT *v = &p->vt[2];
            ((void (*)(void *))v->fn)((char *)p + v->delta);
        }
    }
};
struct MODEL { char pad0[0x40]; M3 mat; };
struct SKEL { char pad0[0xA0]; MODEL *model; };
struct RIG { char pad0[0xC]; VT *vt; char pad10[0x4C - 0x10]; SKEL *skel; };
struct TARGET { char pad0[0x20]; qword pos; };
struct P
{
    char pad0[0x130]; int index; float *dir;
    char pad138[0x190 - 0x138]; RIG *rig;
    char pad194[0x1C4 - 0x194]; int mode; int pad1C8; float tMode;
    char pad1D0[0x1D8 - 0x1D0]; LO *loOn; LO *loNear; int effect; float scale[3]; char pad1F0[0x1F8 - 0x1F0]; float heading; float speed; float angle; float anglePrev;
    int paused; int states[3]; char pad218[0x220 - 0x218]; M3 mat; TARGET *target;
};
struct CLOCK { float t, dt; };
extern CLOCK g_clock;
extern qword D_00317530;
struct S11C0 { char pad0[0x1124]; char x1124[0x11C0 - 0x1124]; };
extern S11C0 D_0036E740[];
extern "C" {
void func_00210D58(void *);
void func_00210D78(void *, int, int);
void func_0023C660(P *);
void func_001C9D70(P *);
float func_0011E598(float, float, float, const SMP *, float *);
float func_0011E3B8(float);
float func_0011E560(float, float);
float atan2f(float, float);
M3 func_0011C8C0(float, qword);
float func_001CABB8(P *, int);
void func_001CAD10(P *, int);
void func_001CA078(P *, int);
void func_0012F4F8(TARGET *, qword);
float func_0011E438(int, float);
void *func_002459F8(int);
void func_00244F08(void *, P *);
HANDLE func_002BE658(void *);
void func_00245100(HOLDER *, float, float);
}
// rows of the product: r.r[i] = a.r[0]*b.r[i].x + a.r[1]*b.r[i].y + a.r[2]*b.r[i].z (rows of a read once)
static inline M3 Mul(const M3 &a, const M3 &b) return r
{
    qword a0 = a.r[0], a1 = a.r[1], a2 = a.r[2];
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[0]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[0]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[1]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[1]));
    __asm__("vmulax.xyz $ACC, %1, %4x\n\tvmadday.xyz $ACC, %2, %4y\n\tvmaddz.xyz %0, %3, %4z"
            : "=j"(r.r[2]) : "j"(a0), "j"(a1), "j"(a2), "j"(b.r[2]));
}
static inline void CallLo(LO *o, int slot) { VT *v = &o->vt[slot]; ((void (*)(void *))v->fn)((char *)o + v->delta); }
static inline int FOn(LO *o) { return (int)(o->flags >> 56) & 1; }
static inline float Clamp01(float g)
{
    if (g < 0.0f)
        return 0.0f;
    if (1.0f < g)
        return 1.0f;
    return g;
}

extern "C" void func_001CA400(P *p)
{
    static const SMP s_smpSettle = { 10.0f, 0.0f, 0.25f };
    static const SMP s_smpSpin = { 100.0f, 20.0f, 0.25f };
    static const LM s_lmWrap = { -0.8f, 0.8f };
    static const LM s_lmBack = { -0.6f, 0.6f };
    float gTarget;
    float g;
    M3 mat;
    if (g_clock.dt == 0.0f)
    {
        if (!p->paused)
        {
            { S11C0 *ps = &D_0036E740[p->index]; func_00210D58(ps->x1124); }
            p->paused = 1;
        }
        return;
    }
    p->paused = 0;
    func_0023C660(p);
    func_001C9D70(p);
    switch (p->mode)
    {
    case -1:
    case 0:
        gTarget = 0.0f;
        break;
    case 2:
        if (g_clock.t - p->tMode > 0.25f)
        {
            float g = p->angle;
            if (0.0f < g)
                g -= 6.28318548f;
            g = func_0011E598(g, 0.0f, g_clock.dt, &s_smpSettle, &p->speed);
            p->anglePrev = p->angle;
            p->angle = func_0011E3B8(g);
            goto turned;
        }
        gTarget = s_smpSettle.gA;
        break;
    case 1:
    {
        float d = func_0011E3B8(atan2f(p->dir[1], p->dir[0]) - p->heading);
        if (0.1f < d)
            d -= 0.1f;
        else if (d < -0.1f)
            d += 0.1f;
        else
            d = 0.0f;
        p->heading = func_0011E3B8(p->heading + d);
        gTarget = func_0011E560(d / g_clock.dt, 5.0f);
        break;
    }
    }
    p->speed = func_0011E598(p->speed, gTarget, g_clock.dt, &s_smpSpin, 0);
    p->anglePrev = p->angle;
    p->angle += p->speed * g_clock.dt;
turned:
    {
        MODEL *model = p->rig->skel->model;
        mat = Mul(Mul(model->mat, func_0011C8C0(p->angle, D_00317530)), p->mat);
        RIG *rig = p->rig;
        VT *v = &rig->vt[35];
        ((void (*)(void *, M3 *))v->fn)((char *)rig + v->delta, &mat);
    }
    switch (p->states[0])
    {
    case 3:
    case 4:
        if (p->angle * func_001CABB8(p, 0) < 0.0f)
            func_001CAD10(p, 2);
        break;
    }
    for (unsigned int i = 0; i < 3; i++)
        func_001CA078(p, i);
    float level = 0.0f;
    int fNear = 0;
    if (p->mode != -1)
    {
        U pos;
        pos.q = p->target->pos;
        for (;;)
        {
            g = func_0011E3B8(p->angle + pos.f[0]);
            if (g < s_lmWrap.gMin)
                pos.f[0] += s_lmBack.gMax - s_lmWrap.gMin;
            else if (s_lmWrap.gMax < g)
                pos.f[0] += s_lmBack.gMin - s_lmWrap.gMax;
            else
                break;
        }
        func_0012F4F8(p->target, pos.q);
        if (p->mode == 1)
        {
            for (unsigned int i = 0; i < 3; i++)
            {
                switch (p->states[i])
                {
                case 3:
                case 4:
                case 5:
                case 6:
                {
                    float d = func_001CABB8(p, i) * p->scale[i] - p->angle;
                    g = __builtin_fabsf(d);
                    level = Clamp01(1.0f - g * 1.98943675f);
                    fNear = g < 0.251327425f;
                    break;
                }
                }
            }
        }
        { S11C0 *ps = &D_0036E740[p->index]; func_00210D78(ps->x1124, fNear, (int)(level * 255.0f)); }
    }
    int fOn = !fNear && 0.0f < level;
    if (p->loOn && fOn != FOn(p->loOn))
    {
        if (fOn)
            CallLo(p->loOn, 8);
        else
            CallLo(p->loOn, 9);
    }
    if (p->loNear && fNear != FOn(p->loNear))
    {
        if (fNear)
            CallLo(p->loNear, 8);
        else
            CallLo(p->loNear, 9);
    }
    if (p->effect != -1)
    {
        float g = func_0011E438(0x19, p->angle);
        if (__builtin_fabsf(func_0011E3B8(g - func_0011E438(0x19, p->anglePrev))) > 0.001f)
        {
            void *e = func_002459F8(p->effect);
            func_00244F08(e, p);
            HANDLE h = func_002BE658(e);
            func_00245100(h.p, 1000.0f, 6000.0f);
        }
    }
}
