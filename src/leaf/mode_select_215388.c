// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-strength-reduce
enum Mode { MODE_NONE = -1, MODE_3E = 0x3E, MODE_3F = 0x3F, MODE_GROW = 0x40, MODE_SHIFT = 0x41, MODE_42 = 0x42 };
struct Slot {
    unsigned char pad0[0x10];
    int type;
    float shift;
    float value;
};
struct ModeSelf {
    unsigned char pad0[0x190];
    int cur[2];
    int cap[2];
    unsigned char pad1A0[0x270 - 0x1A0];
    struct Slot slots[2][6];
    int counts[2];
    unsigned char pad3C8[0x400 - 0x3C8];
    float lo, hi;
    unsigned char pad408[0x4F4 - 0x408];
    enum Mode mode;
    float enterTime;
    float timer;
    float to500, to504;
};
struct CLOCK { float now; };
extern struct CLOCK D_0036BB98;
static inline int Min(int a, int b) { return a < b ? a : b; }
// Switch the selection mode: the 0x3E/0x3F/0x42 modes just arm the timer, 0x40 tops up the smaller counter, 0x41 re-interpolates every slot value between the two
// end values by its position between lo and hi; everything else disarms the timer.
void func_00215388(struct ModeSelf *self, enum Mode mode)
{
    int j, i, k;
    if (mode == self->mode)
        return;
    self->mode = mode;
    self->enterTime = D_0036BB98.now;
    switch (mode) {
    case MODE_3F:
        self->timer = 60.0f;
        return;
    case MODE_3E:
        self->timer = 60.0f;
        return;
    case MODE_42:
        self->timer = 60.0f;
        return;
    case MODE_GROW: {
        int best = 0;
        int lowest = self->cap[0];
        int *cur;
        int *slot;
        self->timer = -1.0f;
        for (k = 0; k < 2; k++) {
            int v;
            int off = k * 4;
            cur = self->cur;
            v = *(int *)((char *)cur + off);
            if (v < lowest) {
                lowest = v;
                best = k;
            }
        }
        slot = &cur[best];
        *slot = Min(self->cap[best], *slot + (int)(self->cap[best] * 0.2f));
        return;
    }
    case MODE_SHIFT:
        self->timer = 60.0f;
        for (i = 0; i < 2; i++) {
            int n = self->counts[i];
            for (j = 0; j < n; j++) {
                struct Slot *slot = &self->slots[i][j];
                switch (slot->type) {
                case 2: {
                    float v = slot->value;
                    float t;
                    if (self->lo == self->hi)
                        t = 0.0f;
                    else
                        t = (v - self->lo) / (self->hi - self->lo);
                    slot->value = (1.0f - t) * self->to500 + t * self->to504;
                    break;
                }
                case 3: {
                    float v = slot->value;
                    float t;
                    if (self->lo == self->hi)
                        t = 0.0f;
                    else
                        t = (v - self->lo) / (self->hi - self->lo);
                    slot->shift = slot->shift - v + ((1.0f - t) * self->to500 + t * self->to504);
                    break;
                }
                }
            }
        }
        return;
    case MODE_NONE:
    default:
        self->timer = -1.0f;
        return;
    }
}
