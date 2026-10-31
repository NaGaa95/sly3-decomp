// Switch the mover between mode 0 (settle toward the target) and mode 1 (capture the current offset), stamping the change time.
// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[4]; };
struct Method { short delta, reserved; void *(*call)(void *, ...); };
struct Mover {
    unsigned char pad00[0xC];
    struct Method *methods;
    unsigned char pad10[0x1C0 - 0x10];
    int mode;
    float modeTime;
    unsigned char pad1C8[0x25C - 0x1C8];
    float settle[3];
    void *target;
};
struct Clock { float time; };
extern struct Clock g_clock;
void func_0022EA88(void *target, qword position, int a, qword *out, int b, int c, void *d);
void func_00217328(struct Mover *self, qword position, qword reference);
#define MATRIX(o) ((struct Matrix *)(o)->methods[36].call((unsigned char *)(o) + (o)->methods[36].delta))

void func_002171E8(struct Mover *self, int mode)
{
    if (self->mode == mode) return;
    self->mode = mode;
    self->modeTime = g_clock.time;
    switch (mode) {
    case 0:
        func_0022EA88(self->target, MATRIX(self)->rows[3], 0, 0, 0, 0, self->settle);
        break;
    case 1: {
        qword reference;
        func_0022EA88(self->target, MATRIX(self)->rows[3], 0, &reference, 0, 0, 0);
        func_00217328(self, MATRIX(self)->rows[3], reference);
        break;
    }
    }
}
