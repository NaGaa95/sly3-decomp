// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// Steering update of the controller: turns the actor towards the goal (planar direction, reach from a clamped
// polynomial of the distance), and copies the target's input mask once the target is close enough and ready.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Frame { qword row[4]; };
struct Falloff { float constant, linear, quadratic; };
struct Limits { float minimum, maximum; };
struct Clock { float time, step; };
struct Input { unsigned char prefix[0x18]; unsigned flags; };
struct Target {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x134 - 0x10];
    struct Input *input;
};
struct Mover {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x110C - 0x10];
    float heading;
    unsigned char gap1110[0x140C - 0x1110];
    unsigned char context140C[0x1424 - 0x140C];
    unsigned held;
    unsigned char gap1428[0x143C - 0x1428];
    unsigned pressed;
};
struct Controller {
    unsigned char prefix0[0x10];
    struct Mover *mover;
    unsigned char gap14[0x3C - 0x14];
    int disabled;
    float stamp;
    unsigned char gap44[0x60 - 0x44];
    qword goal;
    unsigned char gap70[0xB0 - 0x70];
    struct Target *target;
    unsigned mask;
    float interval;
    int hold;
    float gain;
};
extern struct Clock D_0036BB98;
extern qword D_00317550;
extern struct Falloff D_00324370;
extern struct Limits D_00341FF0;
void func_001A9960(void *context, float amount);
float func_001205C8(qword v);
int func_0013B500(void *object, int key);
static inline qword Position(void *self)
{
    struct Method *method = &((struct Target *)self)->methods[36];
    return ((struct Frame *(*)(void *))method->function)((char *)self + method->adjustment)->row[3];
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Dot(qword a, qword b)
{
    qword d, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(d), "=j"(one) : "j"(a), "j"(b));
    return d;
}
static inline qword ScaleX(qword v, qword s) { qword r; __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(r) : "j"(s), "j"(v)); return r; }
static inline float PlanarLength(qword v)
{
    qword d, l;
    float g;
    __asm__("vmul.xy %0,%1,%2\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v), "j"(v));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1,%0" : "=f"(g) : "r"(l));
    return g;
}
static inline float Clamp(float value, const struct Limits *lim)
{
    float low = lim->minimum;
    float high = lim->maximum;
    if (value < low)
        return low;
    if (high < value)
        return high;
    return value;
}
void func_001D90B8(struct Controller *self)
{
    int ready;
    if (self->disabled)
        return;
    {
        qword goal = self->goal;
        qword offset = Sub(goal, Position(self->mover));
        qword up = D_00317550;
        qword flat = Sub(offset, ScaleX(up, Dot(offset, up)));
        float length = PlanarLength(flat);
        float reach = Clamp(D_00324370.constant + length * (D_00324370.linear + length * D_00324370.quadratic), &D_00341FF0);
        if (0.0f < reach) {
            func_001A9960((char *)self->mover + 0x140C, reach * self->gain);
            self->mover->heading = func_001205C8(flat);
        }
    }
    if (self->hold)
        self->mover->held |= 8;
    if (self->target && D_0036BB98.time - self->stamp > self->interval) {
        ready = 1;
        if (500.0f < PlanarLength(Sub(Position(self->mover), Position(self->target))))
            self->mover->held |= 8;
        if (func_0013B500(self->target, 0x33))
            ready = ((int (*)(void *))self->target->methods[100].function)((char *)self->target + self->target->methods[100].adjustment) != 0;
        if (ready) {
            unsigned mask = self->target->input->flags & self->mask;
            self->mover->pressed |= mask & ~self->mover->held;
            self->mover->held |= mask;
        }
    }
}
