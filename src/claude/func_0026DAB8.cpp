// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly3 SO aim/camera update: stick-driven pan/tilt rate with deadzone, smoothing (state 0) or look-at target (states 1-2).
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
struct VTE { short delta; short pad; void *(*method)(void *); };
struct POSQ { char pad[0x30]; qword pos; };
struct LO { char pad[0xC]; struct VTE *vt; };
struct INPUT { float lx, ly; };
struct SO {
    char pad[0xC]; struct VTE *vt; char pad10[0x134 - 0x10]; struct INPUT *p134; char pad138[0x198 - 0x138]; int n198;
    char pad19C[0x1DC - 0x19C]; float f1DC, f1E0; float lim1E4[2]; float f1EC, f1F0, f1F4, f1F8, f1FC, f200, f204, f208, f20C, f210, f214, f218;
    char pad21C[0x270 - 0x21C]; struct LO *p270;
};
extern "C" {
extern struct CLOCK { float t, dt; } g_clock;
extern struct CLOCK2 { float dt; } D_0036BB9C;
void func_001A7B38(struct INPUT *, int, float *, float *);
float func_0011E560(float g, float gMax);
float func_0011E3B8(float);
float func_0011EE68(const void *limits, float value);
M3 func_0011CBA0(qword v);
void func_0011D048(M3 *pm, float *pan, float *tilt);
void func_0026DAB8(struct SO *p);
}
#define VCALL(po, n) ((po)->vt[n].method((char *)(po) + (po)->vt[n].delta))
static inline float Clamp(float x, float lo, float hi) { if (x < lo) return lo; if (hi < x) return hi; return x; }
static inline float GLerp(float a, float b, float t) { return (1.0f - t) * a + t * b; }
static inline qword Pos(struct LO *po) { return ((struct POSQ *)VCALL(po, 36))->pos; }
static inline float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=f"(r) : "f"(g)); return r; }
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(b)); return r; }
void func_0026DAB8(struct SO *p)
{
    switch (p->n198) {
    case 0: {
        float g, l;
        float vx, vy;
        g = __builtin_fabsf(p->p134->lx) - p->f214;
        if (0.0f < g) {
            g /= 1.0f - p->f214;
            g *= (p->f200 - p->f1FC) / p->f20C;
            p->f1EC += g * D_0036BB9C.dt;
        }
        p->f1EC = Clamp(p->f1EC, p->f1FC, GLerp(p->f1FC, p->f200, __builtin_fabsf(p->p134->lx)));
        g = __builtin_fabsf(p->p134->ly) - p->f218;
        if (0.0f < g) {
            g /= 1.0f - p->f218;
            g *= (p->f208 - p->f204) / p->f210;
            p->f1F0 += g * D_0036BB9C.dt;
        }
        p->f1F0 = Clamp(p->f1F0, p->f204, GLerp(p->f204, p->f208, __builtin_fabsf(p->p134->ly)));
        func_001A7B38(p->p134, 5, &vx, &vy);
        vx *= p->f1EC;
        vy *= p->f1F0;
        {
            float ax = __builtin_fabsf(vx * p->f1F0);
            float ay = __builtin_fabsf(vy * p->f1EC);
            float len = SqrtF(ax * ax + ay * ay);
            if (0.0001f < len) {
                vx *= ax / len;
                vy *= ay / len;
            }
        }
        {
            float k;
            float d = vx - p->f1F4;
            float t = g_clock.dt;
            k = 12.0f;
            vx = p->f1F4 + func_0011E560(d, t * k);
            vy = p->f1F8 + func_0011E560(vy - p->f1F8, g_clock.dt * k);
        }
        p->f1DC += vx * g_clock.dt;
        p->f1E0 += vy * g_clock.dt;
        p->f1DC = func_0011E3B8(p->f1DC);
        p->f1E0 = func_0011EE68(p->lim1E4, p->f1E0);
        p->f1F4 = vx;
        p->f1F8 = vy;
        break;
    }
    case 1:
    case 2: {
        M3 m;
        m = func_0011CBA0(Sub(Pos((struct LO *)p->p270), Pos((struct LO *)p)));
        func_0011D048(&m, &p->f1DC, &p->f1E0);
        p->f1DC = func_0011E3B8(p->f1DC);
        p->f1E0 = func_0011EE68(p->lim1E4, p->f1E0);
        break;
    }
    }
}
