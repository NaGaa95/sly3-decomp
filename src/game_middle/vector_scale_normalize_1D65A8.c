// SLY3_CFLAGS: -Os -G0
struct Vec3 { float x, y, z; };
struct ScaledVector {
    unsigned char prefix[0x1F0];
    struct Vec3 vector;
    float factor;
};
extern struct Vec3 D_003242D8;
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
void func_001D65A8(struct ScaledVector *object, float factor)
{
    float root;
    object->vector = D_003242D8;
    object->vector.x *= factor;
    object->vector.y *= factor;
    root = sqrtf_(factor);
    object->factor = factor;
    object->vector.z *= 1.0f / root;
}
