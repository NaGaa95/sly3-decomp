// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame vehicle update: throttle/steer from input or path, rumble, horn, door flags and pickups.
typedef int qword __attribute__((mode(TI)));
struct SMP { float gSpring; float gDamp; float dtMax; };
struct LM { float gMin; float gMax; };
struct SREF { void *object; };
struct XF { char pad[0x28]; float f28; char pad2C[4]; qword pos; };
struct VTE { short d; short pad; void *pf; };
struct INPUT { float steer; char pad4[0x18 - 4]; int grf; };
struct FLAG { char pad[0x1C]; int grf; };
struct PICK { char pad[0xB0]; qword v; };
struct RUMBLE { int kind; unsigned char b4; unsigned char b5; char pad6[2]; float f8; unsigned char bC; unsigned char bD; char padE[2]; float f10; };
struct OUT { qword q0; char pad[0x100]; };
struct JOY { char pad[0x11C0]; };
struct CAR {
    char pad0[0xC]; struct VTE *vt; char pad10[0x130 - 0x10]; int ijoy; struct INPUT *pin;
    char pad138[0x198 - 0x138]; float f198; char pad19C[0x1F8 - 0x19C]; float f1F8;
    char pad1FC[0x32C - 0x1FC]; float speedFwd; float speedRev; float scale; char pad338[4]; float speed; float throttle;
    struct FLAG *pflag0; struct FLAG *pflag1; float tRumble; float t350; char pad354[4];
    struct PICK *ppick; int x35C; char pad360[4]; int x364; float t368; char pad36C[0x3B0 - 0x36C];
    int state; char pad3B4[4]; void *path; float u; float du; char pad3C4[0x3E0 - 0x3C4]; int idHorn;
    char pad3E4[0x3FC - 0x3E4]; struct SREF horn; char pad400[0x418 - 0x400]; float tHorn;
};
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern struct JOY D_0036E740[];
extern char D_00475480[];
float fabsf(float);
void func_0023C660(struct CAR *);
float func_0011E598(const struct SMP *, float *, float, float, float);
void func_001A9098(struct JOY *, struct RUMBLE *, float);
void func_00244CA8(void *, float);
void func_002BBCD8(struct SREF *, void *);
void *func_002459F8(int);
void func_00244F08(void *, void *);
void func_0022EEA0(void *, qword, int, int, int, int, float *, float);
float func_0022E0B8(void *, float);
void func_0022E330(void *, struct OUT *, int, float);
qword func_001C9428(int, struct CAR *, qword);
qword func_001C94E8(int, struct CAR *, qword);
float func_002A3EE8(float, float);
float func_0011E3B8(float);
float func_0011E560(float, float);
void func_0023E228(struct CAR *);
int func_0011EE30(int *, float);
void func_001FE728(int, int);
int func_001F4A80(struct CAR *);
void func_00167D38(int, int);
void func_001CBAA0(void *, struct PICK *);
void func_0027A658(struct CAR *);
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
static inline int NLimit(int n, int nMin, int nMax)
{
    if (n < nMin)
        return nMin;
    if (n > nMax)
        return nMax;
    return n;
}
static inline float GLerpLm(const struct LM *plm, float t)
{
    return (1.0f - t) * plm->gMin + t * plm->gMax;
}
static inline float Length(qword v)
{
    qword sq, one, l;
    float f;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(sq), "=&j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(sq));
    __asm__("qmfc2.ni %0, %1" : "=r"(f) : "j"(l));
    return f;
}
static inline float GetX(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float GetY(qword q) { float f; __asm__("prot3w %0,%1" : "=r"(f) : "r"(q)); return f; }
static inline qword Velocity(struct CAR *p)
{
    return ((qword (*)(void *))p->vt[38].pf)((char *)p + p->vt[38].d);
}
static inline struct XF *Xf(struct CAR *p)
{
    return ((struct XF *(*)(void *))p->vt[36].pf)((char *)p + p->vt[36].d);
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
#define RUMBLE_JOY(p, x, r) { \
    float t_ = 1.0f - (x); \
    float g_; \
    (r).kind = 2; \
    (r).b4 = 0; \
    g_ = GLerpLm(&s_lmRumble, t_); \
    (r).b5 = NLimit((int)((x) * 255.0f), 0x4B, 0xFF); \
    (r).f8 = g_; \
    (r).f10 = g_; \
    (r).bC = 0; \
    (r).bD = 0; \
    func_001A9098(&D_0036E740[(p)->ijoy], &(r), 0.25f); \
}
static inline qword PosAtU(void *path, float u, struct OUT *pout)
{
    func_0022E330(path, pout, 0, u);
    return pout->q0;
}
union VQ { qword q; float f[4]; };
static inline void UpdateFlags(struct CAR *p, union VQ *pv)
{
    pv->q = func_001C94E8(0, p, Velocity(p));
    if (p->pflag0)
        p->pflag0->grf = pv->f[0] > 600.0f ? 0x200 : 0;
    if (p->pflag1)
        p->pflag1->grf = pv->f[0] < -600.0f ? 0x200 : 0;
}
union SHARED { struct RUMBLE r; struct OUT out; union VQ v; };
void func_0027A0B0(struct CAR *p)
{
    static const struct SMP s_smpThrottle = { 10.0f, 1.0f, 0.2f };
    static const struct LM s_lmRumble = { 0.025f, 0.05f };
    union SHARED u;
    func_0023C660(p);
    switch (p->state) {
    case 0:
        p->throttle = 0.0f;
        p->speed = 0.0f;
        break;
    case 1: {
        int grf;
        p->throttle = func_0011E598(&s_smpThrottle, 0, p->throttle, -p->pin->steer * p->scale, g_clock.dt);
        grf = p->pin->grf;
        if (grf & 0x40)
            p->speed = p->speedFwd;
        else if (grf & 0xA0)
            p->speed = -p->speedRev;
        else
            p->speed = 0.0f;
        if (p->speed != 0.0f && g_clock.t - p->tRumble > 0.25f) {
            float x = GClamp(Length(Velocity(p)) / fabsf(p->speed));
            RUMBLE_JOY(p, x, u.r);
            p->tRumble = g_clock.t;
        }
        if (p->idHorn != -1) {
            if (p->pin->grf & 0x10) {
                struct SREF *ref = &p->horn;
                if (!ref->object && g_clock.t - p->tHorn > 0.25f)
                    StartSound(ref, &p->idHorn);
            } else if (p->horn.object) {
                StopSound(&p->horn, 0.0f);
                p->tHorn = g_clock.t;
            }
        }
        break;
    }
    case 2:
    case 3: {
        qword d;
        float g;
        func_0022EEA0(p->path, Xf(p)->pos, 0, 0, 0, 0, &p->u, p->u);
        d = func_001C9428(0, p, (func_0022E330(p->path, &u.out, 0, func_0022E0B8(p->path, p->u + p->du)), u.out.q0));
        if (p->state == 2)
            g = func_002A3EE8(GetY(d), GetX(d));
        else
            g = func_002A3EE8(GetY(d), -GetX(d));
        p->throttle = func_0011E560(func_0011E3B8(g), p->scale);
        break;
    }
    }
    p->f198 = p->throttle;
    p->f1F8 = p->throttle;
    func_0023E228(p);
    u.v.q = func_001C94E8(0, p, Velocity(p));
    if (p->pflag0)
        p->pflag0->grf = u.v.f[0] > 600.0f ? 0x200 : 0;
    if (p->pflag1)
        p->pflag1->grf = u.v.f[0] < -600.0f ? 0x200 : 0;
    if (Xf(p)->f28 > 0.5f)
        p->t350 = g_clock.t;
    if (p->ppick) {
        if (p->x364 && p->t368 < p->t350) {
            if (func_0011EE30(&p->x35C, Length(p->ppick->v))) {
                func_001FE728(p->x364, 1);
                func_00167D38(func_001F4A80(p), 0);
                p->t368 = g_clock.t;
            }
        }
        func_001CBAA0(D_00475480, p->ppick);
        p->ppick = 0;
    }
    func_0027A658(p);
}
