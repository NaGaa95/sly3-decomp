// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
// Per-frame handler for actor states 0..2: re-evaluates its input while the state keeps changing (x1520 == 5), then applies the state-specific update.
#include "input_query_api.h"
typedef int qword __attribute__((mode(TI)));
struct VtEntry { short delta; short pad; void *fn; };
struct Device { char prefix[0x8]; float strength; char gap0C[0x18 - 0xC]; unsigned flags; char gap1C[0x2C - 0x1C]; struct VtEntry *vt; };
struct Clock { float now, step; };
struct Held { char pad[0x28]; unsigned long flags; };
struct Target { char pad[0x190]; struct Held *held; };
struct Anim { char pad[0x1C]; float scale; };
struct Mover {
    char prefix0[0xC];
    struct VtEntry *vt;
    char gap10[0x134 - 0x10];
    struct Device *input;
    char gap138[0x1A0 - 0x138];
    qword direction;
    char gap1B0[0x320 - 0x1B0];
    char ctx320[0xF60 - 0x320];
    char ctxF60[0x110C - 0xF60];
    float heading;
    char gap1110[0x113C - 0x1110];
    struct Anim *runtime;
    char gap1140[0x13E8 - 0x1140];
    int x13E8;
    char gap13EC[0x1520 - 0x13EC];
    int x1520;
    float x1524;
    char gap1528[0x1540 - 0x1528];
    struct Target *target;
    char gap1544[0x1574 - 0x1544];
    int x1574;
    int x1578;
    char gap157C[0x1594 - 0x157C];
    int state;
    char gap1598[0x15A0 - 0x1598];
    char ctx15A0[0x1660 - 0x15A0];
    int x1660;
};
extern struct Clock D_0036BB98;
int func_00156998(struct Mover *self);
void func_001E0660(struct Mover *self);
void func_001DE690(struct Mover *self, int state);
void func_001DDCB8(struct Mover *self, int state);
void func_001B7268(void *context, int kind, void *resource, void *record, float gain);
void func_001BDA88(void *context, int a, int b);
int func_0013B500(void *object, int key);
int func_001F1F78(void *object);
void func_0024E878(void *self, float angle);
void func_00258CF0(void *context, float value);
void func_00258DA0(void *context);
qword func_0024F278(void *self, void *object, float scale);
typedef int (*Query2)(void *, int, float);
typedef void (*Call1)(void *, int);
typedef int (*Test1)(void *, int);
#define VCALL(type, object, slot, args...) ((type)(object)->vt[slot].fn)((char *)(object) + (object)->vt[slot].delta, ## args)
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
void func_001DD908(struct Mover *self)
{
    int old;
    union { qword q; float f[4]; } factor;
    do {
        old = self->state;
        if (old < 3) {
            if (old >= 0) {
                if (!((int)(self->target->held->flags >> 56) & 1)) {
                    func_001E0660(self);
                    self->target = 0;
                    func_001DE690(self, 0);
                } else if (func_00156998(self)) {
                    func_001DDCB8(self, 0);
                } else if (VCALL(Query2, self->input, 1, 0x40, 0.1f)) {
                    VCALL(Call1, self->input, 2, 0x40);
                    func_001B7268(self->ctx320, 0xE, 0, 0, 1.0f);
                } else if (func_001A7A80(self->input, 0x80, 0.0f)) {
                    func_001DE690(self, 7);
                } else if (self->x1660 && func_001A7A80(self->input, 0x20, 0.0f)) {
                    if (func_0013B500(self->target->held, 0x3A)) {
                        if (func_001F1F78(self->target->held))
                            func_001DE690(self, 9);
                    } else
                        func_001DE690(self, 7);
                } else if (func_001A7A80(self->input, 0x10, 0.0f) && self->x1574) {
                    self->x1578 = 0;
                    func_001DE690(self, 8);
                } else if (VCALL(Query2, self->input, 1, 0x400, 0.15f)
                           && D_0036BB98.now - self->x1524 > 0.1f
                           && VCALL(Test1, self, 113, 3)) {
                    func_001DDCB8(self, 0);
                    VCALL(Call1, self->input, 2, 0x400);
                    func_001BDA88(self->ctxF60, 0, 0);
                } else {
                    struct Device *in = self->input;
                    float strength = in->strength;
                    if (self->state == 0 ? 0.1f < strength : 0.0f < strength) {
                        if ((in->flags & 8) || self->x13E8)
                            func_001DDCB8(self, 2);
                        else
                            func_001DDCB8(self, 1);
                    } else {
                        func_001DDCB8(self, 0);
                    }
                }
            }
        }
    } while (self->state != old ? self->x1520 == 5 : 0);
    switch (self->state) {
    case 0:
        break;
    case 1:
        func_0024E878(self, self->heading);
        func_00258CF0(self->ctx15A0, self->input->strength);
        func_00258DA0(self->ctx15A0);
        break;
    case 2:
        func_0024E878(self, self->heading);
        {
            qword pushed = func_0024F278(self, self->runtime, self->runtime->scale);
            factor.q = BlendScalar(-1.0f);
            self->direction = BlendScale(pushed, factor.q);
        }
        break;
    }
}
