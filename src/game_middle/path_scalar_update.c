// SLY3_CFLAGS: -Os -G0
#include "approach_curve.h"

struct PathScalarOwner {
    unsigned char opaque00[0x1A8];
    float speed;
    unsigned char opaque1AC[0x1C0 - 0x1AC];
    unsigned char frame[0x30];
    unsigned char opaque1F0[0x10F4 - 0x1F0];
    void *path;
    float parameter;
    int reverse;
};
struct PathScalarState {
    unsigned char opaque00[0x10];
    struct PathScalarOwner *owner;
    unsigned char opaque14[0x30 - 0x14];
    int mode;
    float timestamp;
    float target, current;
};
struct PathScalarClock { float now, step; };
extern struct PathScalarClock D_0036BB98;
void func_002389A0(void *unused_receiver);
int func_001DA400(void *);
void func_001DA2C8(void *, int mode);
float func_0022E058(void *path, float parameter);
void func_001F32E8(void *path, float parameter, int reverse, void *output_frame);

void func_001DA1A8(struct PathScalarState *state)
{
    int previous;
    func_002389A0(state);
    do {
        previous = state->mode;
        if (previous == 0) {
            if (func_001DA400(state)) {
                func_001DA2C8(state, 1);
            } else {
                struct ApproachCurve curve;
                float desired, value;
                state->owner->reverse = state->owner->parameter < state->target;
                if (state->owner->reverse)
                    desired = -state->owner->speed;
                else
                    desired = state->owner->speed;
                curve.initial = __builtin_fabsf(desired);
                curve.terminal = 0.0f;
                curve.duration = 0.1f;
                value = func_0011E598(state->current, desired, &curve, 0,
                                     D_0036BB98.step);
                state->current = value;
                state->owner->parameter = func_0022E058(state->owner->path,
                    state->owner->parameter + value * D_0036BB98.step);
            }
        }
    } while (state->mode != previous);
    {
        struct PathScalarOwner *owner = state->owner;
        func_001F32E8(owner->path, owner->parameter, owner->reverse, owner->frame);
    }
}
