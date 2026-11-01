// SLY3_CFLAGS: -Os -G0
// Follower state setter: leaves the old state (-1 stops the effects, 1 resets the slot object), stamps the time, starts the
// animation of the new state and, for states -1 / 2 / 3, releases the targets of all pairs.
struct VtEntry { short delta; short pad; void *fn; };
struct Link { int w0, w4, w8; struct VtEntry *vt; };
struct Follower {
    char prefix[0x130];
    int slot;
    char gap134[0x1690 - 0x134];
    void *animations[5];
    void *runtime;
    int state;
    float state_time;
    struct { struct Link *source; struct Link *target; int extra; } pairs[4];
    int pair_count;
    int count;
    int limit;
    int pending;
    int gap16F0[2];
    struct Link *effect_a;
    struct Link *effect_b;
    float strength;
};
struct Clock { float now, step; };
extern struct Clock D_0036BB98;
extern char D_0036E740[][0x11C0];
void func_00155310(void *self, int flag);
void func_00155308(void *self);
void func_00155328(void *self);
void func_00262450(void *object, int key);
void func_00261580(void *object, int key, float value);
void func_001A9058(void *object, int kind, float value);
void func_00137588(void *animation, void *self, int flags, void *runtime, float time, float rate);
typedef void (*VoidFn)(void *);
// Calls a no-argument virtual method of the link object (vtable slot `slot`, this-adjusted by its delta).
#define CALL_SLOT(object, slot) ((VoidFn)(object)->vt[slot].fn)((char *)(object) + (object)->vt[slot].delta)
void func_001EA4B0(struct Follower *self, int next)
{
    void *animation;
    int flags;
    int i;
    if (self->state == next)
        return;
    switch (self->state) {
    case -1:
        func_00155310(self, 1);
        if (self->effect_a) {
            CALL_SLOT(self->effect_a, 56);
            func_00262450(self->effect_a, 0x3CA);
        }
        if (self->effect_b) {
            CALL_SLOT(self->effect_b, 56);
            func_00262450(self->effect_b, 0x37C);
            self->strength = 0.0f;
            func_00261580(self->effect_b, 0x37C, self->strength);
        }
        break;
    case 1:
        func_001A9058(D_0036E740[self->slot], 0, 0.1f);
        break;
    }
    self->state = next;
    self->state_time = D_0036BB98.now;
    flags = 1;
    animation = 0;
    switch (next) {
    case -1:
        func_00155308(self);
        func_00155328(self);
        if (self->effect_a)
            CALL_SLOT(self->effect_a, 54);
        if (self->effect_b)
            CALL_SLOT(self->effect_b, 54);
        break;
    case 0:
    case 1:
        flags = 9;
        animation = self->animations[self->state];
        if (self->state == 1)
            func_001A9058(D_0036E740[self->slot], 0, 1.0f);
        break;
    case 2:
    case 3:
        animation = self->animations[self->state];
        break;
    }
    func_00137588(animation, self, flags, &self->runtime, 0.0f, 1.0f);
    if (self->state < 2) {
        if (self->state >= 0)
            goto settled;
    }
    for (i = 0; i < self->pair_count; i++) {
        if (self->pairs[i].target)
            CALL_SLOT(self->pairs[i].target, 9);
    }
settled:
    if (self->state < 3) {
        if (self->state > 0)
            return;
        self->count = 0;
    } else
        self->count = 0;
    self->pair_count = 0;
}
