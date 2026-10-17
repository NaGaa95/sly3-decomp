// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } VectorWord;
struct NegateTarget { unsigned char prefix[0x1C]; float scale; };
struct NegateSelf {
    unsigned char prefix0[0x190];
    float marker;
    unsigned char gap194[0x1A0 - 0x194];
    qword direction;
    unsigned char gap1B0[0x113C - 0x1B0];
    struct NegateTarget *target;
    unsigned char gap1140[0x18C0 - 0x1140];
    int mode;
};
qword func_0024F278(void *receiver, struct NegateTarget *target, float scale);
static inline qword ScaleX(qword vector, float scale)
{
    VectorWord s;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(scale));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(vector), "j"(s.q));
    return r;
}
void func_001E19F0(struct NegateSelf *self)
{
    if (self->mode == 1 || self->mode == 3) {
        self->direction = ScaleX(func_0024F278(self, self->target, self->target->scale), -1.0f);
        self->marker = 1.0f;
    }
}
