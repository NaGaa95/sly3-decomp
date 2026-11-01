// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Switches the actor to animation state k: picks the look-at target, restarts the clip and re-anchors the actor on the clip segment. Related to Sly 2 func_001B86B0.
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Object { unsigned char prefix[0xC]; struct Method *methods; };
struct Frame { unsigned char prefix[0x30]; qword position; };
struct Input { unsigned char prefix[0x18]; unsigned flags; };
struct Falloff { float constant, linear, quadratic; };
struct Limits { float minimum, maximum; };
struct Clock { float time, step; };
struct Dispatch { struct Method *methods; };
struct Segment { int word0; struct Dispatch *object; };
struct Clip { unsigned char prefix[0x64]; float duration; };
struct Anim { unsigned char prefix[0x14]; struct Clip *clip; };
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x134 - 0x10];
    struct Input *input;
    unsigned char gap138[0x1A0 - 0x138];
    qword direction;
    unsigned char gap1B0[0x1BC - 0x1B0];
    float heading;
    qword basis[3];
    unsigned char gap1F0[0x113C - 0x1F0];
    struct Anim *anim;
    unsigned char context[0x11B4 - 0x1140];
    struct Object *focus;
    unsigned char gap11B8[4];
    int focusKind;
    unsigned char gap11C0[0x13E8 - 0x11C0];
    int x13E8;
    unsigned char gap13EC[0x187C - 0x13EC];
    void *clips[5];
    int state;
    float changed;
    int x1898, x189C, x18A0;
    struct Object *target;
    unsigned char gap18A8[0x18B0 - 0x18A8];
    qword anchor;
    unsigned char gap18C0[0x18DC - 0x18C0];
    void *resource;
};
extern struct Clock D_0036BB98;
extern qword D_00317560;
extern struct Falloff D_00324800;
extern struct Limits D_00324810;
void func_00137628(void *resource);
void func_0023AC58(void *context);
void func_00137588(void *clip, struct Actor *actor, float start, float rate, int flags, struct Anim **slot);
struct Segment *func_00136EE0(struct Clip *clip, struct Actor *actor, int a, int b);
float func_001205C8(qword v);
float func_0011E3B8(float angle);
void func_0024E920(struct Actor *actor, struct Object *target);
void func_0024F0B0(struct Actor *actor);
void func_00155D00(struct Actor *actor);

static inline qword Position(void *self)
{
    struct Method *method = &((struct Object *)self)->methods[36];
    struct Frame *frame = ((struct Frame *(*)(void *))method->function)((char *)self + method->adjustment);
    return frame->position;
}
static inline qword Sub(qword a, qword b) { qword r; __asm__("vsub.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline qword Add(qword a, qword b) { qword r; __asm__("vadd.xyzw %0,%1,%2" : "=j"(r) : "j"(a), "j"(b)); return r; }
static inline float PlanarLength(qword v)
{
    qword d, l;
    float g;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(d) : "j"(v));
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
static inline qword Rotate(qword *m, qword v)
{
    __asm__("vmulax.xyz $ACC,%1,%0x\n\tvmadday.xyz $ACC,%2,%0y\n\tvmaddz.xyz %0,%3,%0z" : "+j"(v) : "j"(m[0]), "j"(m[1]), "j"(m[2]));
    return v;
}
void func_001E1018(struct Actor *self, int k)
{
    void *clip;
    float start;
    if (k == self->state)
        return;
    self->state = k;
    self->changed = D_0036BB98.time;
    if (k == -1)
        return;
    self->x18A0 = 0;
    self->x1898 = 0;
    self->x189C = 0;
    self->target = 0;
    if (self->resource)
        func_00137628(&self->resource);
    clip = self->clips[k];
    self->direction = D_00317560;
    if (k == 4) {
        self->target = self->focus;
    } else if (self->focus && self->focusKind >= 2) {
        if (!(self->input->flags & 8) && !self->x13E8) {
            self->target = self->focus;
        } else {
            qword d = Sub(Position(self->focus), Position(self));
            float heading = func_001205C8(d);
            float current = self->heading;
            float length = PlanarLength(d);
            float reach = Clamp(D_00324800.constant + length * (D_00324800.linear + length * D_00324800.quadratic), &D_00324810);
            if (__builtin_fabsf(func_0011E3B8(heading - current)) < reach)
                self->target = self->focus;
        }
    }
    if (self->target) {
        func_0024E920(self, self->target);
        func_0024F0B0(self);
    }
    start = 0.0f;
    func_0023AC58(self->context);
    func_00137588(clip, self, start, 1.0f, 1, &self->anim);
    if (self->anim) {
        struct Segment *segment = func_00136EE0(self->anim->clip, self, 1, 1);
        if (segment) {
            qword a, b;
            struct Method *method = &segment->object->methods[3];
            ((void (*)(void *, qword *, float, float, int))method->function)((char *)segment->object + method->adjustment, &a, 0.0f, 0.0f, 0);
            method = &segment->object->methods[3];
            ((void (*)(void *, qword *, float, float, int))method->function)((char *)segment->object + method->adjustment, &b, self->anim->clip->duration, 0.0f, 0);
            self->anchor = Add(Position(self), Rotate(self->basis, Sub(b, a)));
        } else {
            self->anchor = Position(self);
        }
    }
    func_00155D00(self);
}
