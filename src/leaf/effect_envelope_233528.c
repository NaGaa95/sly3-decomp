// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Per-frame envelope of a timed effect: count the remaining time down (by the frame time D_0036BB98.dt) and drive the object at
// +0x138 with an intensity that ramps in (func_00118468 curve), holds at the sustain value, ramps out, and finally stops the
// effect (func_00137588) once the time is up.
extern struct { float t; float dt; } D_0036BB98;
struct Effect {
    unsigned char pad00[0x138]; void *object;
    unsigned char pad13C[0x168 - 0x13C]; int link[2];
    int index170, index174; int pad178; float remaining;
    unsigned char pad180[0x2A0 - 0x180];
    float rampIn, holdA, holdB, rampOut, sustain; int pad2B4; float scaleOverride;
};
void func_00118468(float a, float b, float c, float d, float e, float f, float g, float *out, int zero);
void *func_00233668(struct Effect *self);
void func_00137588(void *owner, struct Effect *self, int kind, int *link, float a, float b);
void func_00138B68(void *object, float value);
void func_00233528(struct Effect *self)
{
    float zero = 0.0f;
    float level;
    float scale;
    float previous = self->remaining;
    if (zero < previous) {
        float remaining = previous - D_0036BB98.dt;
        self->remaining = remaining;
        scale = 1.0f;
        if (self->index174 < self->index170)
            scale = self->scaleOverride;
        if (self->holdA + self->holdB < remaining) {
            func_00118468(self->rampIn, self->rampOut - remaining, 1.0f, 1.0f, zero, self->sustain, zero, &level, 0);
        } else if (self->holdB < remaining) {
            level = self->sustain;
        } else if (zero < remaining) {
            func_00118468(self->holdB, remaining, 1.0f, scale, zero, self->sustain, zero, &level, 0);
        } else {
            func_00137588(func_00233668(self), self, 9, self->link, zero, 1.0f);
            level = scale;
        }
        func_00138B68(self->object, level);
    }
}
