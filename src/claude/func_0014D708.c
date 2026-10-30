// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Evolved from Sly 2 src/hand/func_0013C000.c. Owns rodata 0x3202C0 (curve) + jump table 0x3202D0. */
typedef int qword __attribute__((mode(TI)));
typedef struct { qword q[4]; } M4;
typedef struct { qword q[3]; } M3;
typedef union { qword q; float f[4]; } VU;
extern struct CLOCK { float t; } g_clock;
static const float s_curve[3] = { 0.0f, 0.0f, 1.5f };
struct RANGE { float a; float b; };
extern struct RANGE D_00341FF0;
extern qword D_00479350;
struct P;
struct VTE { short d; short pad; M4 *(*pfn)(void *); };
struct VT { char pad[0x120]; struct VTE e120; };
struct P { char pad[0xC]; struct VT *pvt; char pad1[0x150 - 0x10]; VU v150; float x160; int x164; float x168; };
void func_0023CC40(struct P *);
M4 func_0011D660(qword pos, M4 *pmat, VU *pv);
void func_001C8248(struct P *, qword, M4 *, float, float);

static inline float GClamp(float g, float gMin, float gMax)
{
    float r;
    if (g < gMin)
        r = gMin;
    else if (gMax < g)
        r = gMax;
    else
        r = g;
    return r;
}

static inline M4 *Mat(struct P *p) { return p->pvt->e120.pfn((char *)p + p->pvt->e120.d); }

void func_0014D708(struct P *p)
{
    switch (p->x164) {
    case 4: {
        VU v;
        M4 m;
        M4 mT;
        float dt = g_clock.t - p->x168;
        if (p->x160 <= dt) {
            v = p->v150;
        } else {
            float u = dt / p->x160;
            float g = GClamp(s_curve[0] + u * (s_curve[1] + u * s_curve[2]), D_00341FF0.a, D_00341FF0.b);
            int i;
            for (i = 0; i < 3; i++)
                v.f[i] = (1.0f - g) + g * p->v150.f[i];
        }
        mT = func_0011D660(Mat(p)->q[3], Mat(p), &v);
        m = mT;
        func_001C8248(p, D_00479350, &m, 1.0f, 1.0f);
        break;
    }
    case 1:
    case 5:
        func_0023CC40(p);
        break;
    case 2:
    case 3:
    case 6:
    case 7:
        break;
    }
}
