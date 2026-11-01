// SLY3_CFLAGS: -Os -G0 -ffast-math
// Sample a path interval: take the interval [lower, upper] around a (clamped to the path length unless the path is cyclic),
// shape a fraction in [-1, 1] with the curve selected by a global (linear, |t|*t, smoothstep, signed sqrt), map it to [0, 1] and
// interpolate between the interval ends; cyclic paths wrap the result. Sly 2 func_001E8008.
struct P { char pad[0xD4]; int fD4; };
extern int D_003496B0;
float func_0022DFD8(struct P *);
float func_0011E940(float, float);
float func_0022E058(struct P *, float);
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
static inline float GClamp(float x, float lo, float hi)
{
    if (x < lo) return lo;
    if (hi < x) return hi;
    return x;
}
static inline float GMin(float a, float b) { return b < a ? b : a; }
static inline float GMax(float a, float b) { return a < b ? b : a; }
float func_0022FC20(struct P *p, float a, float b)
{
    float r[2];
    float t,u,upper,lower;
    if (p->fD4) {
        r[0] = a - b;
        r[1] = a + b;
    } else {
        float m = func_0022DFD8(p);
        float c = GClamp(a, b, m - b);
        r[0] = GMax(c - b, 0.0f);
        r[1] = GMin(c + b, m);
    }
    t = func_0011E940(-1.0f, 1.0f);
    switch (D_003496B0) {
    case 0:
        break;
    case 1:
        t = t * __builtin_fabsf(t);
        break;
    case 2:
        if (0.0f < t) upper = t * t * (3.0f - (t + t));
        else upper = t * t * (-3.0f - (t + t));
        t = upper;
        break;
    case 3:
        if (0.0f < t) upper = sqrtf_(t);
        else { upper = sqrtf_(-t); upper = -upper; }
        t = upper;
        break;
    }
    t = t * 0.5f + 0.5f;
    u = (1.0f - t) * r[0] + t * r[1];
    if (p->fD4)
        u = func_0022E058(p, u);
    return u;
}
