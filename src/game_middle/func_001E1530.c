// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
// Direction blend: pushes the target's direction (negated), and while active mixes it with the heading derived from the
// velocity, weighted by a clamped polynomial of the animation progress (same routine as Sly 2 func_001B8B70).
typedef int qword __attribute__((mode(TI)));
union BlendFactor { qword q; float f[4]; };
struct BlendTarget { unsigned char prefix[0x14]; void *library; unsigned char gap18[4]; float scale; };
struct BlendSpeed { unsigned char prefix[8]; float value; };
struct BlendActor {
    unsigned char prefix0[0x134];
    struct BlendSpeed *speed;
    unsigned char gap138[0x1A0 - 0x138];
    qword direction;
    unsigned char gap1B0[0x110C - 0x1B0];
    float heading;
    unsigned char gap1110[0x113C - 0x1110];
    struct BlendTarget *target;
    unsigned char gap1140[0x1780 - 0x1140];
    qword velocity;
    unsigned char gap1790[0x1898 - 0x1790];
    int active;
    unsigned char gap189C[0x18A4 - 0x189C];
    void *extra;
};
struct POLY { float a, b, c; };
extern struct POLY D_00324840;
static inline float Polynomial(const struct POLY *p, float t) { return p->a + t * (p->b + t * p->c); }
struct LIMIT { float lo, hi; };
extern struct LIMIT D_00341FF0;
static inline float Clamp(float value, const struct LIMIT *lim)
{
    float low = lim->lo;
    float high = lim->hi;
    if (value < low)
        return low;
    if (high < value)
        return high;
    return value;
}
qword func_0024F278(void *receiver, struct BlendTarget *target, float scale);
float *func_00136880(void *library, int key);
qword func_0011FD70(float heading, float magnitude, float vertical);
qword func_001C94E8(void *source, void *destination, qword direction);
void func_0024E920(void *owner, void *extra);
static inline qword BlendScalar(float value)
{
    qword scalar;
    __asm__("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}
static inline qword BlendScale(qword vector, qword scalar)
{
    qword result;
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(result) : "j"(vector), "j"(scalar));
    return result;
}
static inline qword BlendMix(qword base, qword base_scale, qword other, qword other_scale)
{
    qword result;
    __asm__("vmulax.xyzw $ACC,%1,%2x\n\tvmaddx.xyzw %0,%3,%4x"
            : "=j"(result) : "j"(base), "j"(base_scale), "j"(other), "j"(other_scale));
    return result;
}
static inline qword BlendLengthXY(qword value)
{
    qword result;
    __asm__("vmul.xy %0,%1,%1\n\tvaddy.x %0,%0,%0y" : "=j"(result) : "j"(value));
    return result;
}
static inline qword BlendSqrtX(qword value)
{
    qword root;
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(root) : "j"(value));
    return root;
}
static inline float BlendLow(qword value)
{
    float x;
    __asm__("qmfc2.ni %0,%1" : "=r"(x) : "j"(value));
    return x;
}
void func_001E1530(struct BlendActor *self)
{
    union BlendFactor factor;
    float blend;
    if (self->target) {
        qword pushed = func_0024F278(self, self->target, self->target->scale);
        factor.q = BlendScalar(-1.0f);
        self->direction = BlendScale(pushed, factor.q);
        if (self->active) {
            float *first = func_00136880(self->target->library, 0x2A0);
            float *last = func_00136880(self->target->library, 0x2A2);
            float ratio = (self->target->scale - *first) / (*last - *first);
            float value = Polynomial(&D_00324840, ratio);
            qword converted, scaled, keep, weight;
            blend = Clamp(value, &D_00341FF0);
            converted = func_001C94E8(0, self,
                func_0011FD70(self->heading, self->speed->value * BlendLow(BlendSqrtX(BlendLengthXY(self->velocity))), 0.0f));
            factor.q = BlendScalar(-1.0f);
            scaled = BlendScale(converted, factor.q);
            factor.q = BlendScalar(1.0f - blend);
            keep = factor.q;
            factor.q = BlendScalar(blend);
            weight = factor.q;
            self->direction = BlendMix(self->direction, keep, scaled, weight);
        }
    }
    if (self->extra)
        func_0024E920(self, self->extra);
}
