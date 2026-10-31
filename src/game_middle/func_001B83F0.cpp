// SLY3_ASFIX: engine-divfix1
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Largest positive time at which a point at `position` reaches the height limits of a box of height extent.z:
// two quadratics in z (+-extent.z/2 with one velocity term each) plus the two horizontal-distance bounds.
#include "../P2/state_position_ops.h"
static inline float sqrtf_(float x) { float r; __asm__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
static inline float maxf(float a, float b) { float r; __asm__("max.s %0,%1,%2" : "=f"(r) : "f"(a), "f"(b)); return r; }
extern "C" {
int func_0011EA28(float a, float b, float c, float *roots);
float func_001B83F0(qword position, qword extent, float first, float second, float inner, float outer)
{
    float rootsA[4];
    float rootsB[4];
    float half = PackedVectorZ(extent) * 0.5f;
    float height = PackedVectorZ(position);
    float best = 0.0f;
    int count;
    count = func_0011EA28(-half, -first, height, rootsA);
    if (count > 0)
        best = maxf(rootsA[count - 1], best);
    count = func_0011EA28(half, -second, height, rootsB);
    if (count > 0)
        best = maxf(rootsB[count - 1], best);
    {
        float length = PackedHorizontalLength(position);
        float t = (inner * length - height) / -half;
        if (0.0f < t)
            best = maxf(sqrtf_(t), best);
        t = (outer * length - height) / half;
        if (0.0f < t)
            best = maxf(sqrtf_(t), best);
    }
    return best;
}
}
