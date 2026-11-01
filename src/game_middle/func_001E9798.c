// SLY3_CFLAGS: -Os -G0
// Mover update: runs the 0..8 state machine until the state settles. Before each pass the idle states poke the context at
// +0x320; the active states (0..3 on the ground, 4..8 special) read the input device and request transitions.
#include "input_query_api.h"
struct VtEntry { short delta; short pad; void *fn; };
struct Device { char prefix[0x8]; float strength; char gap0C[0x18 - 0xC]; unsigned flags; char gap1C[0x2C - 0x1C]; struct VtEntry *vt; };
struct Clock { float now, step; };
struct Mover {
    char prefix0[0xC];
    struct VtEntry *vt;
    char gap10[0x134 - 0x10];
    struct Device *input;
    char gap138[0x320 - 0x138];
    char ctx320[0x500 - 0x320];
    char ctx500[8];
    int x508;
    char gap50C[0xE40 - 0x50C];
    char ctxE40[0xF60 - 0xE40];
    char ctxF60[0x10DC - 0xF60];
    void *x10DC;
    char gap10E0[0x10F8 - 0x10E0];
    int x10F8;
    char gap10FC[0x113C - 0x10FC];
    void *x113C;
    void *x1140;
    char gap1144[0x13E8 - 0x1144];
    int x13E8;
    char gap13EC[0x1470 - 0x13EC];
    int state;
    float state_time;
    char gap1478[0x16A8 - 0x1478];
    int mode;
    char gap16AC[0x16EC - 0x16AC];
    int x16EC;
};
extern struct Clock D_0036BB98;
int func_00156998(struct Mover *self);
int func_001398F0(void *object);
int func_002503C8(struct Mover *self, float time);
void func_001B7268(void *context, int kind, void *resource, void *record, float gain);
void func_001B9020(void *context);
void func_001B27D8(void *context);
void func_001C2A18(void *context);
void func_001B5170(void *context);
void func_001BDA88(void *context, int a, int b);
int func_00138AC8(void *object);
int func_00239CC0(void *object);
void func_001E9BC8(struct Mover *self, int state);
void func_001EA4B0(struct Mover *self, int state);
typedef int (*Query2)(void *, int, float);
typedef void (*Call1)(void *, int);
typedef int (*Test1)(void *, int);
typedef void (*Call0)(void *);
#define VCALL(type, object, slot, args...) ((type)(object)->vt[slot].fn)((char *)(object) + (object)->vt[slot].delta, ## args)
void func_001E9798(struct Mover *self)
{
    int old;
    do {
        old = self->state;
        switch (old) {
        case 4:
        case 6:
        case 8:
            break;
        case 7:
            if (func_001398F0(self->x10DC) || self->x10F8) {
                if (func_002503C8(self, 0.1f))
                    func_001B7268(self->ctx320, 0, 0, 0, 1.0f);
            }
            break;
        case 5:
            if (self->x508 != 1 && self->x508 != 12) {
                if (func_002503C8(self, 0.1f))
                    func_001B7268(self->ctx320, 0, 0, 0, 1.0f);
            }
            break;
        default:
            if (func_002503C8(self, 0.1f))
                func_001B7268(self->ctx320, 0, 0, 0, 1.0f);
            break;
        }
        switch (self->state) {
        case 0:
        case 1:
        case 2:
        case 3:
            if (func_00156998(self)) {
                func_001E9BC8(self, 0);
                break;
            }
            if (func_001A7A80(self->input, 0x40, 0.1f)) {
                func_001B7268(self->ctx320, 1, 0, 0, 1.0f);
                break;
            }
            if (VCALL(Query2, self->input, 1, 0x400, 0.15f)) {
                if (D_0036BB98.now - self->state_time > 0.1f) {
                    if (VCALL(Test1, self, 113, 3)) {
                        func_001E9BC8(self, 0);
                        VCALL(Call1, self->input, 2, 0x400);
                        func_001BDA88(self->ctxF60, 0, 0);
                        break;
                    }
                }
            }
            if (func_001A7A80(self->input, 0x20, 0.2f)) {
                func_001B5170(self->ctx500);
                break;
            }
            {
                int mode = self->mode;
                struct Device *in;
                float strength;
                if (mode == -1 && (self->x16EC || (self->input->flags & 4))) {
                    func_001EA4B0(self, 0);
                    break;
                }
                in = self->input;
                strength = in->strength;
                if (self->state == 0 ? 0.1f < strength : 0.0f < strength) {
                    if ((unsigned)mode < 2) {
                        func_001E9BC8(self, 3);
                        break;
                    }
                    if ((in->flags & 8) || self->x13E8)
                        func_001E9BC8(self, 1);
                    else
                        func_001E9BC8(self, 2);
                    break;
                }
                func_001E9BC8(self, 0);
            }
            break;
        case 4:
            func_001B9020(self->ctx320);
            break;
        case 5:
            func_001B27D8(self->ctx500);
            break;
        case 6:
            func_001C2A18(self->ctxE40);
            break;
        case 7:
            if (func_001398F0(self->x10DC)) {
                if (0.0f < self->input->strength)
                    func_001E9BC8(self, 2);
                else if (func_001A7A80(self->input, 0x40, 0.1f))
                    func_001B7268(self->ctx320, 1, 0, 0, 1.0f);
            }
            break;
        case 8:
            if (self->x113C && func_00138AC8(self->x113C))
                func_001E9BC8(self, 0);
            else if (self->x1140 && func_00239CC0(self->x1140))
                func_001E9BC8(self, 0);
            break;
        }
        ((Call0)self->vt[98].fn)((char *)self + self->vt[98].delta);
    } while (self->state != old);
}
