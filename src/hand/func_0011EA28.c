// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Solve the quadratic polynomial, sorting the real roots.
// The one-instruction EE sqrt intrinsic follows the Sly 2 implementation.
static inline float sqrtf_(float x) { float r; __asm__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
#define sqrtf sqrtf_
float fabsf(float x);

int func_0011EA28(float a, float b, float c, float *ax)
{
    float alpha;
    float beta;

    c *= 4.0f;
    alpha = b * b - a * c;
    if (alpha < 0.0f)
        return 0;
    a = a + a;
    alpha = sqrtf(alpha) / a;
    beta = b / a;
    if (fabsf(alpha) < 0.0001f) {
        *ax = -beta;
        return 1;
    }
    ax[0] = -beta + alpha;
    ax[1] = -beta - alpha;
    if (ax[1] < ax[0]) {
        ax[0] = -beta - alpha;
        ax[1] = -beta + alpha;
    }
    return 2;
}
