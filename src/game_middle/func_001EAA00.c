// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_001EAA00: raises actor->reach (x1700) from how deep the hero's nearest surface point is inside a distance-dependent
// radius (quadratic falloff D_00324D90 clamped to D_00324DA0, then eased through the curve D_00341FF0); also reports the depth.
// Allocation notes: Sub takes the point through a pointer (address-taken parameters are renumbered above the other
// pseudos, which gives the original spill slots and vf numbering); Clamp loads maximum before minimum, which orders the FP allocation.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Frame { unsigned char prefix[0x30]; qword position; };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
struct Limits { float minimum, maximum; };
struct Falloff { float constant, linear, quadratic; };
struct Actor {
    unsigned char prefix[0x1700];
    float reach;
};
extern struct Falloff D_00324D90;
extern struct Limits D_00324DA0;
extern struct Limits D_00341FF0;
void *func_001F4A80(struct Actor *actor);
qword func_001678C8(void *object, qword point);
float func_0011EE68(struct Limits *curve, float t);
static inline qword Sub(const qword *a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(*a), "j"(b)); return r; }
static inline float Length(qword v)
{
    qword d, one, l;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
static inline float GetX(qword q) { float x; __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q)); return x; }

static inline float Clamp(float value, const struct Limits *lim)
{
    float high = lim->maximum;
    float low = lim->minimum;
    if (value < low)
        return low;
    if (high < value)
        return high;
    return value;
}
void func_001EAA00(struct Actor *actor, qword point, float *penetration)
{
    struct Object *object = (struct Object *)func_001F4A80(actor);
    struct Method *method = &object->methods[36];
    struct Frame *frame = ((struct Frame *(*)(void *))method->function)((char *)object + method->adjustment);
    qword nearest;
    float distance, radius, depth, scale;
    qword position = frame->position;
    nearest = func_001678C8(object, point);
    distance = Length(Sub(&point, position));
    radius = Clamp(D_00324D90.constant + distance * (D_00324D90.linear + distance * D_00324D90.quadratic), &D_00324DA0);
    depth = __builtin_fabsf(GetX(nearest)) - radius;
    scale = 1.0f - func_0011EE68(&D_00341FF0, depth / (radius + radius));
    if (penetration)
        *penetration = depth;
    {
        float current = actor->reach;
        actor->reach = current < scale ? scale : current;
    }
}
