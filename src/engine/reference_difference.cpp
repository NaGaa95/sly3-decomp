// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
#include "../P2/state_position_ops.h"
struct ReferenceDifferenceMatrix { qword row[4]; };
struct ReferenceDifferenceMethod {
    short delta, reserved;
    ReferenceDifferenceMatrix *(*matrix)(void *receiver);
};
struct ReferenceDifferenceOwner { char prefix[12]; ReferenceDifferenceMethod *methods; };
struct ReferenceDifferenceState { char prefix[0x10]; ReferenceDifferenceOwner *owner; };
extern "C" qword func_001407E8(void *state);
extern "C" void func_0024E8E8(void *owner, qword difference);
extern "C" void func_00140900(ReferenceDifferenceState *state)
{
    qword target = func_001407E8(state);
    ReferenceDifferenceOwner *owner = state->owner;
    ReferenceDifferenceMethod *method = &owner->methods[36];
    qword position = method->matrix((char *)owner + method->delta)->row[3];
    func_0024E8E8(state->owner, PackedDifference(target, position));
}
