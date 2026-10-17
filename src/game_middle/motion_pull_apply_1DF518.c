// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int PullPacked __attribute__((mode(TI)));
typedef union { PullPacked raw; float scalar; } PullScalarCarrier;
struct PullMethod { short delta, reserved; PullPacked (*function)(void *); };
struct PullTable { unsigned char prefix[0x130]; struct PullMethod method; };
struct PullAnchor { unsigned char prefix[0x80]; PullPacked vector; };
struct PullSelf {
    unsigned char prefix0[0xC];
    struct PullTable *table;
    unsigned char gap10[0xD8 - 0x10];
    struct PullAnchor *anchor;
    unsigned char gapDC[0x1A0 - 0xDC];
    PullPacked offset;
    unsigned char gap1B0[0x1528 - 0x1B0];
    int mode;
};
extern PullPacked D_00317550;
void func_00244828(void *self, PullPacked correction);

static inline PullPacked pull_scale(PullPacked vector, float scale)
{
    PullScalarCarrier carrier;
    PullPacked result;
    __asm__("qmtc2.ni %1,%0" : "=j"(carrier.raw) : "r"(scale));
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(result) : "j"(vector), "j"(carrier.raw));
    return result;
}
static inline PullPacked pull_carrier(float scale)
{
    PullScalarCarrier carrier;
    __asm__("qmtc2.ni %1,%0" : "=j"(carrier.raw) : "r"(scale));
    return carrier.raw;
}
static inline PullPacked pull_difference(PullPacked left, PullPacked right)
{
    PullPacked result;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(left), "j"(right));
    return result;
}
static inline PullPacked pull_dot(PullPacked a, PullPacked b)
{
    PullPacked product, one;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(product), "=&j"(one) : "j"(a), "j"(b));
    return product;
}
static inline PullPacked pull_scale_x(PullPacked vector, PullPacked scalar)
{
    PullPacked result;
    __asm__("vmulx.xyzw %0,%2,%1x" : "=j"(result) : "j"(scalar), "j"(vector));
    return result;
}

void func_001DF518(struct PullSelf *self)
{
    int mode = self->mode;
    if (mode != 1) {
        if (mode >= 2)
            return;
        if (mode != 0)
            return;
        func_00244828(self, pull_scale(self->anchor->vector, -1.0f));
    }
    {
        struct PullMethod *method = &self->table->method;
        PullPacked position = method->function((char *)self + method->delta);
        PullPacked factor = pull_carrier(2.5f);
        PullPacked delta = pull_difference(pull_scale(self->offset, -1.0f), position);
        PullPacked along = pull_scale_x(D_00317550, pull_dot(delta, D_00317550));
        func_00244828(self, pull_scale_x(pull_difference(delta, along), factor));
    }
}
