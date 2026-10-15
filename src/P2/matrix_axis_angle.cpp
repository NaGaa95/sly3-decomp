// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Sly2 algorithm; all Sly3 offsets/normalvector/calls verified against original.
struct MATRIX3 { float mat[3][4]; } __attribute__((aligned(16)));
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
extern VECTOR D_00317530;
extern "C" float func_002A3CE8(float g);
static inline float SqrtF(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }

extern "C" void func_0011D0B8(MATRIX3 *pmat, float *prad, VECTOR *pvec)
{
    float c = (pmat->mat[0][0] + pmat->mat[1][1] + pmat->mat[2][2] - 1.0f) * 0.5f;
    if (c > 0.999999f) {
        *prad = 0.0f;
        *pvec = D_00317530;
        return;
    }

    float gRem = 1.0f;
    int i;
    for (i = 0; i < 2; i++) {
        float g = (pmat->mat[i][i] - c) / (1.0f - c);
        float gAbs = __builtin_fabsf(g);
        if (gAbs > gRem)
            gAbs = gRem;
        else if (gAbs < 0.0f)
            gAbs = 0.0f;
        (&pvec->x)[i] = SqrtF(gAbs);
        gRem -= gAbs;
    }
    pvec->z = SqrtF(gRem);

    if (c < -0.9999f) {
        *prad = 3.14159265f;
        float x = pvec->x;
        float y = pvec->y;
        float z = pvec->z;
        if (y < x) {
            if (z < x) {
                if (pmat->mat[0][1] < 0.0f)
                    pvec->y = -y;
                if (pmat->mat[0][2] < 0.0f)
                    pvec->z = -pvec->z;
            } else {
                if (pmat->mat[2][0] < 0.0f)
                    pvec->x = -x;
                if (pmat->mat[2][1] < 0.0f)
                    pvec->y = -pvec->y;
            }
        } else if (z < y) {
            if (pmat->mat[1][0] < 0.0f)
                pvec->x = -x;
            if (pmat->mat[1][2] < 0.0f)
                pvec->z = -pvec->z;
        } else {
            if (pmat->mat[2][0] < 0.0f)
                pvec->x = -x;
            if (pmat->mat[2][1] < 0.0f)
                pvec->y = -pvec->y;
        }
    } else {
        *prad = func_002A3CE8(c);
        if (pmat->mat[1][0] > pmat->mat[0][1])
            pvec->z = -pvec->z;
        if (pmat->mat[2][0] < pmat->mat[0][2])
            pvec->y = -pvec->y;
        if (pmat->mat[2][1] > pmat->mat[1][2])
            pvec->x = -pvec->x;
    }
}
