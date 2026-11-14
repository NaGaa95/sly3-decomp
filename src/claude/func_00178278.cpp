// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// WakeSoWater. Sly 2 reference: src/hand/WakeSoWater__FP2SOP5WATERfP6VECTORT3ff.cpp
// (Sly 3 drops the splash and spawns the ripple through func_001FE840/func_00202C90).
typedef int qword __attribute__((mode(TI)));
struct VTE { short d; short pad; qword (*pfn)(void *); };
struct EVT { short d; short pad; void (*pfn)(void *, qword); };
struct SO { int x0, x4, x8; VTE *pvt; };
struct SND { char pad[0x14C]; float t; void *psnd; };
struct RIPO { char pad[0xC]; EVT *pvt; };
struct WATER { char pad[0x158]; RIPO *px158; int x15C; };
struct RIPS { char pad[0x14]; float g14; float g18; };
struct RIPP { float g0; float g4; int n8; };
struct RIPQ { char pad[0x20]; RIPP rp; };
struct RIPR { char pad[0x14]; RIPQ *px14; char pad18[4]; RIPS *px1C; };
struct RIP { int x0; RIPR *px4; };
struct CLOCK { float t; };

/* rodata int table at 0x003212E0 (not in symbol_addrs) */
static const int D_003212E0[4] = { 0x4B, 0x4D, 0x4E, 0x4C };
extern "C" {
extern CLOCK g_clock;
float func_0011E940(float lo, float hi);
int func_0011E8F0(int lo, int hi);
int func_0013B500(SO *p, int n);
void func_00244E08(void *p, float g);
void func_00244CA8(void *p, float g);
void *func_002459F8(int id);
void func_00244F08(void *p, SO *pso);
void func_00245100(void *p, float a, float b);
void func_002BBCD8(void *pp, void *p);
void *func_001FE840(RIPO *a, RIPO *b, int c, int d);
RIP *func_00202C90(void *p, int n);
void func_001FF590(RIP *p, int n);
}

static inline qword Length(qword a)
{
    qword r, one;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z\n\t"
            "vsqrt $Q, %0x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q"
        : "=j"(r), "=j"(one) : "j"(a));
    return r;
}
static inline qword Sub(qword a, qword b)
{
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b));
    return r;
}
static inline float GClamp(float g, float lo, float hi)
{
    if (g < lo)
        return lo;
    if (hi < g)
        return hi;
    return g;
}
static inline float GetX(qword q)
{
    float f;
    __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q));
    return f;
}

extern "C" void func_00178278(SO *p, WATER *pwater, qword pos, qword v, float dt, float gFrac, float gScale)
{
    float g = 0.0f;
    VTE *pvte = &p->pvt[38];
    float d = GetX(Length(Sub(pos, pvte->pfn((char *)p + pvte->d))));
    int fWake = func_0011E940(g, 3.0f) < dt;
    SND *psnd;
    float t, u;
    psnd = 0;
    if (func_0013B500(p, 0x31))
        psnd = (SND *)p;
    if (d > 10.0f || fWake) {
        u = (d - 10.0f) * 0.0012658228f;
        t = GClamp(u, g, 1.0f);
        if (psnd && pwater->x15C) {
            void **pp = &psnd->psnd;
            float gVol = t * 0.9f + 0.1f;
            if (psnd->psnd) {
                func_00244E08(psnd->psnd, gVol);
            } else {
                void *ps = func_002459F8(D_003212E0[func_0011E8F0(0, 3)]);
                func_00244F08(ps, (SO *)psnd);
                func_00245100(ps, 100.0f, 1000.0f);
                func_00244E08(ps, gVol);
                func_002BBCD8(pp, ps);
            }
        }
        if (!fWake) {
            u = 1.0f - t * (1.0f - gFrac);
            if (psnd) {
                fWake = u < g_clock.t - psnd->t;
            } else {
                float tc = g_clock.t;
                int c0 = (int)(tc / u);
                int c1 = (int)((tc + dt) / u);
                fWake = c0 != c1;
            }
        }
        if (fWake && pwater->px158) {
            if (psnd)
                psnd->t = g_clock.t;
            RIPO *po = pwater->px158;
            EVT *pe = &po->pvt[34];
            pe->pfn((char *)po + pe->d, v);
            RIP *prip = func_00202C90(func_001FE840(pwater->px158, pwater->px158, 0, 0), 0x78C);
            RIPR *pr = prip->px4;
            RIPS *prs = pr->px1C;
            prs->g14 = gScale;
            prs->g18 = gScale;
            RIPP *prp = &pr->px14->rp;
            prp->g0 = gScale;
            prp->g4 = gScale * 0.6f;
            prp->n8 = 0;
            func_001FF590(prip, 1);
        }
    } else if (psnd) {
        void **pp = &psnd->psnd;
        if (pp && *pp) {
            func_00244CA8(*pp, g);
            func_002BBCD8(pp, 0);
        }
    }
}
