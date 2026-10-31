// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0017D270: screen flash fade (adapted from Sly 2 func_0015DD48); the quad is built in a stack GIFS.
#include "../P2/gifs.h"
#include "../P2/vifs.h"
struct RGBA { unsigned char r, g, b, a; RGBA() {} };
struct CLOCK { float t; float dt; };
extern CLOCK g_clock;
struct X {
    char pad[0x40];
    RGBA rgba40, rgba44, rgba48;
    float d4C, d50, d54;
    float t58;
    int k5C;
    char *p60;
};
struct Q { int x0; int x4; QW *pqw; };
struct FLASHES { char pad[0x3EB8]; int c; };
struct WEIGHTS { float ag[0x468 / 4]; int f; };
extern FLASHES D_00475480;
extern WEIGHTS D_00479350;
extern VIFS D_0036C308;
extern char D_0036E680[];
extern "C" {
void func_00195808(RGBA *prgba, void *pv, int n, GIFS *pgifs);
Q *func_00209B60(void);
int func_00174FF0(int a, int i);
int func_00174FF8(int a, int b);
void func_0017D270(X *p);
}
static inline int NLerp(float g, int a, int b)
{
    if (a == b)
        return b;
    if (a < b)
        return a + (int)(g * ((float)b + 0.999f - (float)a));
    return b + (int)((1.0f - g) * ((float)a + 0.999f - (float)b));
}
static inline RGBA RgbaLerp(float t, RGBA a, RGBA b)
{
    RGBA r;
    r.r = NLerp(t, a.r, b.r);
    r.g = NLerp(t, a.g, b.g);
    r.b = NLerp(t, a.b, b.b);
    r.a = NLerp(t, a.a, b.a);
    return r;
}
static inline void Build(GIFS *pgifs, RGBA rgba, char *pv)
{
    RGBA *prgba = &rgba;
    func_00195808(prgba, pv ? pv + 0x160 : D_0036E680, 3, pgifs);
}
static inline int Flags(int a, int b, int i) { return func_00174FF8(b, func_00174FF0(a, i)); }
extern "C" void func_0017D270(X *p)
{
    RGBA rgba;
    RGBA a, b;
    float d;
    float dt = g_clock.t - p->t58;
    if (dt < p->d4C) {
        a = p->rgba40;
        b = p->rgba44;
        d = p->d4C;
    } else {
        dt -= p->d4C;
        if (dt < p->d50) {
            a = p->rgba44;
            b = p->rgba44;
            d = p->d50;
        } else {
            dt -= p->d50;
            if (dt < p->d54) {
                a = p->rgba44;
                d = p->d54;
                b = p->rgba48;
            }
        }
    }
    rgba = RgbaLerp(dt / d, a, b);
    GIFS gifs;
    GIFS *pgifs = &gifs;
    QW aqw[0x2D];
    pgifs->AllocStatic(0x2D, aqw);
    Build(pgifs, rgba, p->p60);
    VIFS *pvifs = &D_0036C308;
    QW *pqw = (QW *)pvifs->m_pb;
    pvifs->AddDmaCnt();
    pvifs->AddVifDirect((unsigned int)(gifs.m_pb - gifs.m_ab) >> 4, (QW *)gifs.m_ab, 0);
    pvifs->EndDmaCnt();
    pvifs->AddDmaRet();
    for (int i = 0; i < D_00475480.c; i++) {
        if (D_00479350.ag[i] == 0.0f)
            continue;
        Q *pq = func_00209B60();
        pq->pqw = pqw;
        switch (p->k5C) {
        case 0:
        default:
            pq->x0 = Flags(5, 0, i);
            break;
        case 2:
            if (D_00479350.f == 0) {
                pq->x0 = Flags(10, 0xF, i);
                break;
            }
            pq->x0 = Flags(5, 0xF, i);
            break;
        case 1:
            pq->x0 = Flags(5, 0xF, i);
            break;
        }
    }
}
