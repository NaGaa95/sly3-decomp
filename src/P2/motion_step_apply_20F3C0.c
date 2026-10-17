// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int MotionPacked __attribute__((mode(TI)));
typedef union { MotionPacked raw; float scalar; } MotionScalarCarrier;
typedef struct { MotionPacked r[3]; } MotionM3;
typedef struct { float x, y, z; } MotionV3;
struct MotionSelf {
    unsigned char prefix[0x1C0];
    float amount;
    float shift;
    unsigned char gap1C8[4];
    int state;
    unsigned char gap1D0[0x204 - 0x1D0];
    float angle;
    int forward;
    int backward;
};
extern MotionPacked D_00317530;
extern MotionPacked D_00317550;
void func_00243738(void *self);
MotionPacked func_001C94E8(void *source, void *destination, MotionPacked direction);
void func_00244828(void *self, MotionPacked correction);
MotionM3 *func_0011C8C0(MotionM3 *matrix, float angle, MotionPacked axis);
void func_0023EDE8(void *self, MotionM3 matrix, MotionV3 limits);
void *func_00292034(void *destination, int byte, unsigned bytes);
void func_0020FB58(void *self);

static inline MotionPacked motion_scale_bits(MotionPacked vector, int bits)
{
    MotionScalarCarrier carrier;
    MotionPacked result;
    __asm__("qmtc2.ni %1,%0" : "=j"(carrier.raw) : "r"(bits));
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(result) : "j"(vector), "j"(carrier.raw));
    return result;
}

static inline MotionPacked motion_scale(MotionPacked vector, float scale)
{
    MotionScalarCarrier carrier;
    MotionPacked result;
    __asm__("qmtc2.ni %1,%0" : "=j"(carrier.raw) : "r"(scale));
    __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(result) : "j"(vector), "j"(carrier.raw));
    return result;
}

void func_0020F3C0(struct MotionSelf *self)
{
    func_00243738(self);
    if (self->state == 2) {
        if (self->forward) {
            self->forward = 0;
            func_00244828(self, func_001C94E8(self, 0, motion_scale_bits(D_00317530, *(int *)&self->amount)));
        } else if (self->backward) {
            self->backward = 0;
            func_00244828(self, func_001C94E8(self, 0, motion_scale(D_00317530, -self->amount)));
        }
        {
            MotionV3 copy;
            MotionV3 limits;
            MotionM3 matrix;
            func_00292034(&limits, 0, sizeof limits);
            limits.x = self->shift;
            limits.z = 0.25f;
            copy = limits;
            func_0011C8C0(&matrix, self->angle, D_00317550);
            func_0023EDE8(self, matrix, copy);
        }
        func_0020FB58(self);
    }
}
