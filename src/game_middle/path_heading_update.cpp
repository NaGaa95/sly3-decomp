// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/packed_matrix_intrinsics.h"

struct PathHeadingOwner {
    unsigned char opaque00[0x1A0];
    float speed;
    unsigned char opaque1A4[0x10F4 - 0x1A4];
    void *path;
    float parameter;
    int reverse;
};
struct PathHeadingLink { unsigned char opaque00[8]; void *object; };
struct PathHeadingComponent {
    unsigned char opaque00[0x40];
    PathHeadingLink *link;
};
struct PathHeadingState {
    unsigned char opaque00[0x10];
    PathHeadingOwner *owner;
    unsigned char opaque14[4];
    PathHeadingComponent *component;
    unsigned char opaque1C[0x30 - 0x1C];
    int mode;
    float timestamp, gain, target;
};
struct PathHeadingClock { float now, step; };
union PathHeadingVector { qword q; float f[4]; };
static inline qword PathHeadingScalarToVU(float value)
{
    qword result;
    asm("qmtc2.ni %1,%0" : "=j"(result) : "r"(value));
    return result;
}
extern "C" {
extern PathHeadingClock D_0036BB98;
void func_002389A0(void *unused_receiver);
float func_0022E058(void *path, float parameter);
int func_001DA768(void *state);
void func_001DA630(void *state, int mode);
void func_0022E330(void *path, float parameter, void *position, qword *tangent);
float func_001205C8(qword direction);
void func_0024E878(void *owner, float heading);
void func_00138B68(void *object, float value);
}

extern "C" void func_001DA4F0(PathHeadingState *state)
{
    int previous;
    func_002389A0(state);
    do {
        previous = state->mode;
        if (previous == 0) {
            PathHeadingOwner *owner = state->owner;
            void *path = owner->path;
            float desired;
            owner->reverse = owner->parameter < state->target;
            if (state->owner->reverse)
                desired = -state->owner->speed;
            else
                desired = state->owner->speed;
            state->owner->parameter = func_0022E058(path,
                state->owner->parameter + desired * D_0036BB98.step);
            if (func_001DA768(state)) {
                func_001DA630(state, 1);
            } else {
                PathHeadingVector direction;
                func_0022E330(path, state->owner->parameter, 0, &direction.q);
                if (!state->owner->reverse) {
                    PathHeadingVector factor;
                    factor.q = PathHeadingScalarToVU(-1.0f);
                    direction.q = ScalePackedMatrixRow(direction.q, factor.q);
                }
                func_0024E878(state->owner, func_001205C8(direction.q));
                func_00138B68(state->component->link->object, state->gain);
            }
        }
    } while (state->mode != previous);
}
