// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_0028A920: schedule a new timed entry: random ranges, merge other entries' busy windows (func_0028A868), push start past overlaps, init record vectors.
typedef int qword __attribute__((mode(TI)));
struct F { float x0; float x4; };
struct R { int x0; int pad4[2]; int xC; char pad10[0x10]; qword v20; qword v30; qword v40; qword v50; qword v60; float x70; float x74; float x78; };
struct Q { R *p; float x4; float x8; F f; };
struct E { float x0, x4, x8, xC, x10, x14, x18, x1C, x20, x24; int c; Q aq[2]; };
struct S { char pad[0x690]; int c; int pad694; E ae[1]; };
extern "C" {
extern struct CLOCK { float t; } g_clock;
extern struct { float g; } D_0047A2C8;
extern qword D_00317550;
R *func_0028A7D0(S *p, E *e);
int func_0028A868(int n, F *a);
int func_0028A470(S *p);
float func_0011E940(float low, float high);
float func_0011E3B8(float rad);
qword func_0011FD70(float a, float b, float c);
void func_0028A920(S *p, int i, float g);
}
float GModPositive(float value, float limit);
static inline float GMin(float a, float b) { return a < b ? a : b; }
static inline float SqrtF(float g) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(g)); return r; }
struct VU_FLOAT { qword q; VU_FLOAT(const VU_FLOAT &s) { q = s.q; } VU_FLOAT(float f) { qword t; __asm__("qmtc2.ni %1, %0" : "=j"(t) : "r"(f)); q = t; } };
struct VU_VECTOR { qword q; VU_VECTOR(const VU_VECTOR &s) { q = s.q; } VU_VECTOR(const qword &v) { q = v; } };
static inline qword VuVector(qword q) { qword r; __asm__("qmtc2.ni %1, %0" : "=j"(r) : "r"(q)); return r; }
static inline qword Scale(qword a, VU_FLOAT s) { qword r; __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(s.q), "j"(a)); return r; }

void func_0028A920(S *p, int i, float g)
{
    E *e = &p->ae[i];
    R *r = func_0028A7D0(p, e);
    if (!r)
        return;
    Q *q = &e->aq[e->c++];
    q->p = r;
    float g24 = func_0011E940(e->x0, e->x4);
    float g27 = func_0011E940(e->x8, e->xC);
    float t = func_0011E940(e->x10, e->x14);
    float g21 = func_0011E940(e->x18, e->x1C);
    F af[16];
    int n = 0;
    for (int j = 0; j < p->c; j++) {
        if (j == i)
            continue;
        E *e2 = &p->ae[j];
        for (int k = 0; k < e2->c; k++)
        {
            Q *pq = &e2->aq[k];
            af[n++] = pq->f;
        }
    }
    n = func_0028A868(n, af);
    float now = g_clock.t;
    float gap = GMin(t - g, e->x20);
    for (int k = 0; k < n; k++) {
        F *pf = &af[k];
        float s = now + t;
        if (pf->x0 <= s && s - gap < pf->x4) {
            t = pf->x4 + e->x20 - now;
            gap = e->x20;
        }
    }
    q->x4 = now;
    q->f.x4 = now + t;
    q->x8 = now + g;
    q->f.x0 = now + t - gap;
    float rad = func_0011E3B8(D_0047A2C8.g + 3.1415927f + g21);
    float s21 = SqrtF(g24 * 278.52115f);
    r->x0 = 0;
    r->xC = func_0028A470(p);
    qword v = VuVector(func_0011FD70(rad, 1.0f, 0.0f));
    r->v20 = v;
    r->v30 = Scale(v, VU_FLOAT(g27));
    r->v50 = Scale(D_00317550, VU_FLOAT(g27));
    r->x70 = 1.0f / g24;
    r->x74 = e->x24 * s21 / g24;
    if (e->c < 2) {
        r->x78 = 0.0f;
    } else {
        float tt = now + g * 0.25f;
        R *r0 = e->aq[0].p;
        r->x78 = GModPositive(r0->x74 * tt + r0->x78 - r->x74 * tt, 1.0f);
    }
}
