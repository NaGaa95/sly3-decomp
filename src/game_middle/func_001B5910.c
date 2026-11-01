// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
#include "approach_curve.h"

typedef unsigned long long qword __attribute__((mode(TI)));

struct VuMethod { short delta, reserved; qword (*function)(void *); };
struct ActorTable { unsigned char prefix[0x130]; struct VuMethod velocity; };
struct OtherBody { unsigned char prefix[0x80]; qword velocity; };
struct Actor {
    unsigned char prefix0[0xC];
    struct ActorTable *table;
    unsigned char gap10[0xD8 - 0x10];
    struct OtherBody *other;
};
struct FollowPath { unsigned char prefix[0x1CC]; int active; float limit; float scale; };
struct FollowControl {
    struct Actor *actor;
    unsigned char gap04[4];
    int mode;
    unsigned char gap0C[0x14 - 0x0C];
    struct FollowPath *path;
    unsigned char gap18[4];
    float parameter;
};
struct Clock { float now, step; };

extern struct ApproachCurve D_00322E20;
extern struct Clock D_0036BB98;
void func_0022E148(struct FollowPath *path, void *position, qword *direction, float t);
void func_00244828(struct Actor *actor, qword correction);

static inline qword Dot(qword a, qword b)
{
    qword one, d;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline float FloatX(qword q)
{
    float x;
    __asm__("mtc1 %1,%0" : "=f"(x) : "r"(q));
    return x;
}
union VuFloat { qword q; float f[4]; };
static inline qword Scale(qword v, float s)
{
    union VuFloat scale;
    qword r;
    __asm__("qmtc2.ni %1,%0" : "=j"(scale.q) : "r"(s));
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(scale.q));
    return r;
}
static inline float GLimit(float g, float gMin, float gMax)
{
    if (g < gMin)
        g = gMin;
    else if (gMax < g)
        g = gMax;
    return g;
}

void func_001B5910(struct FollowControl *control)
{
    qword velocity[1];
    qword direction[1];
    qword correction[1];
    float high, low;
    struct FollowPath *path;
    float along, other, value;
    qword d1, d2;
    if (control->mode == 3) {
        path = control->path;
        if (path->active) {
            struct VuMethod *method = &control->actor->table->velocity;
            velocity[0] = method->function((char *)control->actor + method->delta);
            func_0022E148(path, 0, direction, control->parameter);
            d2 = Dot(direction[0], control->actor->other->velocity);
            d1 = Dot(direction[0], velocity[0]);
            along = FloatX(d1);
            other = FloatX(d2);
            func_0011E598(along, path->limit, &D_00322E20, &high, D_0036BB98.step);
            func_0011E598(along, -path->limit, &D_00322E20, &low, D_0036BB98.step);
            value = GLimit(path->scale * other, low, high) - other;
            correction[0] = Scale(direction[0], value);
            func_00244828(control->actor, correction[0]);
        }
    }
}
