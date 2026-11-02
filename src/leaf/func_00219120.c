// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Vec4 { float x, y, z, w; } __attribute__((aligned(16)));
struct Range { float minimum, maximum; };
struct Limit { float minimum, maximum; };
extern struct Range D_0047A2B8, D_0047A2C0;
extern struct Limit D_00325CC8, D_00325CD0;
float func_0011EE68(struct Limit *limit, float value);
static __inline__ float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }
static __inline__ float GetY(qword q) { float y; __asm__("prot3w %0,%1" : "=r"(y) : "r"(q)); return y; }
static inline float Remap(float value, struct Range *range, struct Limit *limit)
{
    float fraction;
    if (range->minimum == range->maximum) fraction = 0.0f;
    else fraction = (value - range->minimum) / (range->maximum - range->minimum);
    return func_0011EE68(limit, fraction);
}

struct Vec4 func_00219120(void *self, qword position)
{
    struct Vec4 screen;
    screen.x = Remap(GetX(position), &D_0047A2B8, &D_00325CC8) * 640.0f;
    screen.y = Remap(-GetY(position), &D_0047A2C0, &D_00325CD0) * 480.0f;
    screen.z = 0.0f;
    return screen;
}
