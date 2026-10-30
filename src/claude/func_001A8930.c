// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Sly 2 reference: GetJoyXYDeflection__FP3JOYUcUcPfN23PUcT6PiP2LM (adds a smoothed-deflection in/out param).
typedef unsigned char uchar;
struct JOY { char pad[0x105C]; float g105C; };
struct LM { float gMin; float gMax; };
struct VEC2 { float x; float y; };
/* .data table at 0x345108 (no symbol in symbol_addrs.txt); placed by its bytes. */
static struct VEC2 D_00345108[4] = { { 1.0f, 0.0f }, { 0.0f, 1.0f }, { 0.7f, 0.7f }, { 0.7f, -0.7f } };
static inline float SqrtF(float g) { float r; __asm__ volatile("sqrt.s %0, %1" : "=&f"(r) : "f"(g)); return r; }
static inline float GClamp(float g, float lo, float hi)
{
    if (g < lo) return lo;
    if (g > hi) return hi;
    return g;
}
static inline float GMax(float a, float b) { return a < b ? b : a; }
void func_001A8930(struct JOY *pjoy, uchar bX, uchar bY, float *px, float *py, float *pgDeflection,
                   float *pgSmooth, uchar *pbXPrev, uchar *pbYPrev, int *pfActive, struct LM *alm)
{
    float x, y, gMax, g, r, gSmooth, k;
    unsigned int i;
    if (!*pfActive) {
        int fActive = 0;
        if (pjoy->g105C != 0.0f &&
            (bX != *pbXPrev || bY != *pbYPrev || bX < 0x60 || bX > 0xA0 || bY < 0x60 || bY > 0xA0))
            fActive = 1;
        *pfActive = fActive;
    }
    if (*pfActive) {
        x = 2.0f * (float)bX * (1.0f / 255.0f) + -1.0f;
        y = 1.0f - 2.0f * (float)bY * (1.0f / 255.0f);
    } else {
        x = y = 0.0f;
    }
    gMax = 0.0f;
    for (i = 0; i < 4; i++) {
        struct VEC2 *pv = &D_00345108[i];
        g = x * pv->x + y * pv->y;
        if (g >= 0.0f) {
            if (alm[i].gMax < g) alm[i].gMax = g;
            r = g / alm[i].gMax;
        } else {
            if (g < alm[i].gMin) alm[i].gMin = g;
            r = g / alm[i].gMin;
        }
        if (gMax < r) gMax = r;
    }
    r = GClamp((gMax - 0.35f) * 2.0f, 0.0f, 1.0f);
    gSmooth = GMax(*pgSmooth - 0.2f, 0.0f);
    if (gSmooth <= r) {
        k = r * SqrtF(x * x + y * y);
        gSmooth = r;
        *px = k * x;
        *py = k * y;
    } else {
        k = r / *pgSmooth;
        *px = k * *px;
        *py = k * *py;
    }
    *pbXPrev = bX;
    *pbYPrev = bY;
    *pgDeflection = r;
    *pgSmooth = gSmooth;
}
