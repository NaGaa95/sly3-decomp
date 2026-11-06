// Heading update of a context state: kind 7 turns the owner away from its
// forward vector, kind 8 steers the owner towards a heading derived from the
// owner's own direction and ends the state once it has settled.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti -fno-cse-skip-blocks
#include "../P2/scene.h"
#include "../P2/packed_matrix_intrinsics.h"

// One packed direction.
union HeadingVector {
    qword packed;
    float lane[4];
};
struct HeadingTarget { char opaque00[0x1C]; float scale; };
struct HeadingLimit { char opaque00[8]; float value; };
struct HeadingOwner {
    char opaque00[0xC];
    SCENE_VIRTUAL_ENTRY *table;
    char opaque10[0x134 - 0x10];
    HeadingLimit *limit;
    char opaque138[0x1A0 - 0x138];
    qword direction;
    char opaque1B0[0x1BC - 0x1B0];
    float turn;
    char opaque1C0[0x218 - 0x1C0];
    int pending;
    char opaque21C[0x110C - 0x21C];
    float heading;
    char opaque1110[0x113C - 0x1110];
    HeadingTarget *target;
};
struct HeadingClock { float now, step; };
struct HeadingState {
    HeadingOwner *owner;
    int kind;
    float stamp;
};

extern "C" {
extern HeadingClock D_0036BB98;
extern unsigned char D_003235F0[];
float func_001205C8(qword direction);
float func_0011E840(void *table, int mode, float current, float target, float step);
void func_0024E878(void *owner, float heading);
int func_001BADF8(void *owner, float stamp, void *record);
void func_001C2E78(HeadingState *state);
qword func_0024F278(void *owner, void *target, float scale);
float func_0011E3B8(float angle);

void func_001C2B48(HeadingState *state)
{
    switch (state->kind) {
    case 8: {
        HeadingVector direction;
        SCENE_VIRTUAL_ENTRY *entry = &state->owner->table[38];
        direction.packed = ((qword (*)(void *))entry->Simple)((char *)state->owner + entry->delta);
        float angle = func_001205C8(direction.packed);
        func_0024E878(state->owner, func_0011E840(D_003235F0, 0, state->owner->turn,
                                                  angle + 3.14159274f, D_0036BB98.step));
        if ((D_0036BB98.now - state->stamp > 0.25f && state->owner->pending) ||
            func_001BADF8(state->owner, state->stamp, 0))
            func_001C2E78(state);
        break;
    }
    case 7: {
        HeadingOwner *owner = state->owner;
        qword forward = func_0024F278(owner, owner->target, owner->target->scale);
        HeadingLimit *limit = owner->limit;
        // -1.0f as a packed scalar (the float is moved through a GPR into the VU register); the original keeps a stack copy of it
        qword factor;
        HeadingVector scale;
        __asm__("qmtc2.ni %1,%0" : "=j"(factor) : "r"(-1.0f));
        scale.packed = factor;
        owner->direction = ScalePackedMatrixRow(forward, factor);
        if (0.0f < limit->value)
            func_0024E878(owner, func_0011E3B8(owner->heading + 3.14159274f));
        break;
    }
    }
}
}
