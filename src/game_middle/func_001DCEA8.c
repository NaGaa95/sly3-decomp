// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31
// Per-frame state machine of the actor, state 0..23: the first switch plays the entry effect for the states that have
// one, the second runs the state's update and decides on the next state; repeated while the state keeps changing.
#include "input_query_api.h"
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; void *function; };
struct Input { unsigned char prefix[8]; float strength; unsigned char gapC[0x18 - 0xC]; unsigned flags; unsigned char gap1C[0x2C - 0x1C]; struct Method *methods; };
struct Clock { float time, step; };
struct Actor {
    unsigned char prefix0[0xC];
    struct Method *methods;
    unsigned char gap10[0x134 - 0x10];
    struct Input *input;
    unsigned char gap138[0x320 - 0x138];
    unsigned char context320[4];
    int substate;
    unsigned char gap328[0x33C - 0x328];
    int x33C;
    unsigned char gap340[0x500 - 0x340];
    unsigned char context500[8];
    int x508;
    unsigned char gap50C[0xE40 - 0x50C];
    unsigned char contextE40[0xF60 - 0xE40];
    unsigned char contextF60[0x1010 - 0xF60];
    unsigned char context1010[0x1108 - 0x1010];
    void *slot1108;
    unsigned char gap110C[0x113C - 0x110C];
    void *anim;
    void *other;
    unsigned char gap1144[0x13E8 - 0x1144];
    int x13E8;
    unsigned char gap13EC[0x1520 - 0x13EC];
    int state;
    float x1524;
    unsigned char gap1528[0x1538 - 0x1528];
    int x1538;
    unsigned char gap153C[0x18C0 - 0x153C];
    int x18C0;
    unsigned char gap18C4[0x18E0 - 0x18C4];
    unsigned char context18E0[1];
};
extern struct Clock D_0036BB98;
int func_002503C8(struct Actor *self, float limit);
int func_002502F0(struct Actor *self, float limit);
void func_001B7268(void *context, int kind, void *resource, void *record, float gain);
int func_00156998(struct Actor *self);
int func_00153290(struct Actor *self, int mode);
void func_001DE690(struct Actor *self, int state);
int func_00173428(void *slot);
void func_001BDA88(void *context, int a, int b);
int func_001E0DF8(struct Actor *self);
void func_001E0F38(struct Actor *self);
void func_001E0E58(struct Actor *self);
int func_001DF888(struct Actor *self);
int func_001B5170(void *context);
void func_001B9020(void *context);
void func_001B27D8(void *context);
void func_001C2A18(void *context);
void func_001DF418(struct Actor *self);
void func_001DD908(struct Actor *self);
void func_001DDE80(struct Actor *self);
void func_001E1DE0(struct Actor *self);
int func_00138AC8(void *anim);
void func_001E1370(struct Actor *self);
void func_001DDFE8(struct Actor *self);
void func_001E1810(struct Actor *self);
void func_00271F78(void *context);
void func_001BF1F8(void *context);
int func_00239CC0(void *other);
typedef int (*Query2)(void *, int, float);
typedef void (*Call1)(void *, int);
typedef int (*Test1)(void *, int);
#define VCALL(type, object, slot, args...) ((type)(object)->methods[slot].function)((char *)(object) + (object)->methods[slot].adjustment, ## args)
static inline int IsActive(void *slot)
{
    return slot && func_00173428(slot) != 0;
}
void func_001DCEA8(struct Actor *self)
{
    int old;
    do {
        old = self->state;
        switch (old) {
        default:
            if (func_002503C8(self, 0.1f)) {
                switch (self->state) {
                case 9:
                case 5:
                    func_001B7268(self->context320, 0xF, 0, 0, 1.0f);
                    break;
                case 13:
                    if (self->x18C0 == 3)
                        func_001B7268(self->context320, 0xB, 0, 0, 1.0f);
                    break;
                case 14:
                    if (self->x508 != 1 && self->x508 != 12)
                        func_001B7268(self->context320, 0, 0, 0, 1.0f);
                    break;
                default:
                    func_001B7268(self->context320, 0, 0, 0, 1.0f);
                    break;
                }
            }
            break;
        case 2:
        case 3:
        case 4:
        case 6:
        case 7:
        case 8:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 21:
        case 22:
        case 23:
            break;
        }
        switch (self->state) {
        case 0:
        case 1:
        case 11:
            if (func_00156998(self)) {
                func_001DE690(self, 0);
            } else if (!((self->input->flags & 8) || self->x13E8) && func_00153290(self, 0)) {
                func_001DE690(self, 10);
            } else if (func_001A7A80(self->input, 0x40, 0.1f)) {
                if (IsActive(self->slot1108))
                    func_001B7268(self->context320, 0x11, 0, 0, 1.0f);
                else
                    func_001B7268(self->context320, 1, 0, 0, 1.0f);
            } else if (VCALL(Query2, self->input, 1, 0x400, 0.15f) && D_0036BB98.time - self->x1524 > 0.1f
                       && VCALL(Test1, self, 113, 3)) {
                func_001DE690(self, 0);
                VCALL(Call1, self->input, 2, 0x400);
                func_001BDA88(self->contextF60, 0, 0);
            } else if (func_001E0DF8(self) && func_001A7A80(self->input, 0x10, 0.15f)) {
                func_001E0F38(self);
            } else if (func_001DF888(self)) {
            } else if (func_001A7A80(self->input, 0x20, 0.2f) && func_001B5170(self->context500)) {
            } else if (func_001E0DF8(self) && func_001A7A80(self->input, 0x80, 0.15f)) {
                func_001E0E58(self);
            } else {
                float strength = self->input->strength;
                if (self->state == 0 ? 0.1f < strength : 0.0f < strength) {
                    if (IsActive(self->slot1108))
                        func_001DE690(self, 0xB);
                    else if ((self->input->flags & 8) || self->x13E8)
                        func_001DE690(self, 1);
                    else
                        func_001DE690(self, 0xB);
                } else {
                    func_001DE690(self, 0);
                }
            }
            break;
        case 2:
            func_001B9020(self->context320);
            switch (self->substate) {
            case 0:
            case 11:
            case 14:
            case 15:
                break;
            default:
                if (VCALL(Query2, self->input, 1, 0x90, 0.15f) && VCALL(Test1, self, 113, 2)
                    && self->x33C < 8 && self->x33C > 0 && !func_002502F0(self, 0.1f)) {
                    VCALL(Call1, self->input, 2, 0x90);
                    self->x1538 = 0;
                    func_001DE690(self, 3);
                }
                break;
            }
            break;
        case 14:
            func_001B27D8(self->context500);
            break;
        case 15:
            func_001C2A18(self->contextE40);
            break;
        case 3:
            func_001DF418(self);
            break;
        case 5:
            func_001DD908(self);
            break;
        case 6:
            func_001DDE80(self);
            break;
        case 4:
            func_001E1DE0(self);
            break;
        case 7:
        case 8:
            if (func_00138AC8(self->anim))
                func_001DE690(self, 0);
            break;
        case 9:
            if (func_00138AC8(self->anim))
                func_001DE690(self, 5);
            break;
        case 12:
            func_001E1370(self);
            break;
        case 10:
            func_001DDFE8(self);
            break;
        case 13:
            func_001E1810(self);
            break;
        case 16:
            func_00271F78(self->context18E0);
            break;
        case 21:
            func_001BF1F8(self->context1010);
            break;
        case 18:
            if (self->anim && func_00138AC8(self->anim)) {
                func_001DE690(self, 0);
                break;
            }
            if (self->other && func_00239CC0(self->other))
                func_001DE690(self, 0);
            break;
        case 17:
        case 19:
        case 20:
        case 22:
        case 23:
            break;
        }
    } while (self->state != old);
}
