// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef struct { short d; short pad; void *pfn; } VTE;
union U { qword q; float f[4]; };
struct LM { float minimum, maximum; };
struct Shape { unsigned char pad00[0x64]; float scale; };
struct Handle {
    unsigned char pad00[0xC];
    VTE *vt;
    unsigned char pad10[4];
    Shape *shape;
    unsigned char pad18[4];
    float length;
    unsigned char pad20[0x28 - 0x20];
    unsigned long flags;
    unsigned char pad30[0x40 - 0x30];
    float value;
};
struct Sway { unsigned char pad[0x1C]; LM range; unsigned char pad24[4]; float amplitude; };
struct Mover {
    unsigned char pad00[0x1B0];
    int kind;
    unsigned char pad1B4[0x1DC - 0x1B4];
    Sway *sway;
    unsigned char pad1E0[0x21C - 0x1E0];
    float angle;
    float extent;
    float limit;
    unsigned char pad228[0x230 - 0x228];
    float output;
    unsigned char pad234[4];
    void *speaker;
    float nextTime;
    float target;
    float current;
    unsigned char pad248[0x438 - 0x248];
    Handle *driven;
    float low;
    float high;
    unsigned char pad444[0x44C - 0x444];
    Handle *partner;
    float stamp;
    float threshold;
};
struct Clock { float now, step; };
extern "C" {
extern Clock D_0036BB98;
extern LM D_00341FF0, D_00325C78, D_00325C80, D_00325C88, D_00325C90;
float func_0011EE68(const LM *table, float value);
int func_0011EE30(const LM *table, float value);
float func_0011E940(float low, float high);
float func_0011E598(float current, float goal, float step, const LM *params, float *velocity);
void func_00137D08(Handle *handle, float a, float b, int c, int d);
void func_0012F4F8(void *speaker, qword q);
}
static inline qword Pack(float x, float y, float z, U &home)
{
    qword q, t;
    __asm__("mfc1 %0,%2\n\tmfc1 %1,%3\n\tpextlw %0,%1,%0\n\tmfc1 %1,%4\n\tpcpyld %0,%1,%0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    home.q = q;
    return home.q;
}
#define HCALL(h, slot) ((void (*)(void *))((h)->vt[slot].pfn))((char *)(h) + (h)->vt[slot].d)
extern "C" void func_002179A0(Mover *self)
{
    if (self->kind) {
        if (self->driven) {
            float zero = 0.0f;
            if (self->driven->value == zero) {
                float phase = func_0011EE68(&D_00341FF0, (self->angle + 3.1415927f) * 0.15915494f);
                float lo = self->low;
                float scale = self->driven->shape->scale;
                float a = phase * scale;
                float b = zero;
                if (lo < a) {
                    float hi = self->high;
                    if (a < hi) {
                        float f5 = self->driven->length / scale;
                        if ((phase - 0.5f) * (f5 - 0.5f) < zero) {
                            if (phase < f5) { a = hi; b = -1.0f; }
                            else { b = 1.0f; a = lo; }
                        } else if (phase < 0.5f) a = lo;
                        else a = hi;
                    }
                }
                func_00137D08(self->driven, a, b, 0, 0);
            }
        }
    }
    if (self->partner) {
        if (self->limit >= self->threshold) {
            if (self->kind == 2) {
                if (((int)(self->partner->flags >> 56) & 1) == 0) {
                    HCALL(self->partner, 8);
                    self->stamp = D_0036BB98.now;
                }
            } else goto timed;
        } else {
        timed:
            if (D_0036BB98.now - self->stamp > 1.0f)
                HCALL(self->partner, 9);
        }
    }
    if (self->speaker) {
        if (self->sway) {
            float magnitude = __builtin_fabsf(self->angle);
            float t = magnitude * 0.31830987f;
            float level;
            if (t < 0.5f) {
                float u = t + t;
                float amp = self->sway->amplitude;
                float soft = amp * 0.75f;
                level = (1.0f - u) * soft + u * amp;
            } else {
                float v = t - 0.5f;
                float u = v + v;
                float amp = self->sway->amplitude;
                float soft = amp * 0.1f;
                level = (1.0f - u) * amp + u * soft;
            }
            if (func_0011EE30(&D_00325C78, magnitude)) {
                if (self->nextTime < D_0036BB98.now) {
                    self->target = func_0011E940(D_00325C88.minimum, D_00325C88.maximum);
                    float when = D_0036BB98.now;
                    when += func_0011E940(D_00325C80.minimum, D_00325C80.maximum);
                    self->nextTime = when;
                }
                self->current = func_0011E598(self->current, self->target, D_0036BB98.step, &D_00325C90, 0);
                level *= self->current;
            }
            if (0.0f < self->angle) level = -level;
            self->output = func_0011E598(self->output, level, D_0036BB98.step, &self->sway->range, 0);
        } else if (self->kind != 7) {
            self->output = 0.0f;
        }
        {
            U home;
            func_0012F4F8(self->speaker, Pack(self->output, 0.0f, 0.0f, home));
        }
    }
}
