// SLY3_CFLAGS: -Os -G0 -ffast-math
// Pan/zoom update of a menu overlay (same math as the session menu's transform code): integrates the stick into the two
// ranged offsets, eases the zoom amount towards a 0 / 0.5 / 1 level and sends the three transform records.
struct Range { float minimum, maximum; };
struct StickInput { float x, y; };
struct Transform { float a[8]; } __attribute__((aligned(16)));
struct Clock { float now, step; };
struct Pan {
    char prefix[0x130];
    int slot;
    struct StickInput *input;
    char gap138[0x19C - 0x138];
    float px;
    float py;
    struct Range range_x;
    struct Range range_y;
    float amount;
    float scale;
    void *control;
};
extern struct Clock D_0036BB98;
extern struct Transform D_00317FC0;
extern unsigned char D_0036E740[][0x11C0];
struct ApproachCurve;
extern struct ApproachCurve D_00324BD0;
float func_0011EE68(const struct Range *range, float value);
float func_0011E598(float input, float target, const struct ApproachCurve *curve, float *derivative, float step);
void func_00262990(void *control, int key, const void *data);
static inline float Clamp(float value, float low, float high)
{
    if (value < low)
        return low;
    if (high < value)
        return high;
    return value;
}
void func_001E8F38(struct Pan *self)
{
    struct StickInput *in = self->input;
    float level;
    unsigned char *object;
    float px, py;
    float k, rest;
    float dx = __builtin_fabsf(in->x) * in->x;
    float dy = __builtin_fabsf(in->y) * in->y;
    struct Transform t;
    self->px = func_0011EE68(&self->range_x, self->px + dx * D_0036BB98.step);
    self->py = func_0011EE68(&self->range_y, self->py + dy * D_0036BB98.step);
    object = D_0036E740[self->slot];
    level = Clamp(object[0x111E] * 0.015625f, 0.0f, 1.0f);
    if (level <= 0.0f)
        level = 0.0f;
    else if (level <= 0.75f)
        level = 0.5f;
    else
        level = 1.0f;
    if (0.0f <= level) {
        self->amount = func_0011E598(self->amount, level, &D_00324BD0, 0, D_0036BB98.step);
        self->amount = Clamp(self->amount, 0.0f, 1.0f);
    }
    px = self->px * 320.0f + 320.0f;
    py = self->py * -240.0f + 240.0f;
    k = self->amount * self->scale;
    t = D_00317FC0;
    t.a[0] += k;
    t.a[3] += k;
    t.a[4] = -px * k;
    t.a[5] = -py * k;
    func_00262990(self->control, 0x3E0, &t);
    t = D_00317FC0;
    rest = 1.0f - self->amount;
    t.a[0] += rest;
    t.a[3] += rest;
    t.a[4] = px;
    t.a[5] = py;
    func_00262990(self->control, 0x3DF, &t);
    func_00262990(self->control, 0x3DE, &t);
}
