// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions
#include "../P2/state_position_ops.h"
struct PositionBinding;
struct PositionBindingRuntime {
    unsigned char prefix[0x90];
    PositionBinding *active;
    unsigned char gap94[0x2C];
    qword position;
};
struct PositionBinding {
    unsigned char prefix[4];
    void *owner;
    PositionBindingRuntime *runtime;
    unsigned char unusedC[0x14];
    qword position;
};
extern qword D_00317560;
extern "C" int func_0011E9F0(float, float, float);
extern "C" void func_0028F260(void *, PositionBindingRuntime *);
static __inline__ int NearXYZ(qword a, qword b)
{
    return func_0011E9F0(PackedVectorX(a), PackedVectorX(b), 0.0001f) &&
           func_0011E9F0(PackedVectorY(a), PackedVectorY(b), 0.0001f) &&
           func_0011E9F0(PackedVectorZ(a), PackedVectorZ(b), 0.0001f);
}
extern "C" void func_0012F4F8(void *receiver, qword value)
{
    PositionBinding *binding = (PositionBinding *)receiver;
    qword change = PackedDifference(value, binding->position);
    binding->position = value;
    if (binding->runtime->active == binding && !NearXYZ(D_00317560, change)) {
        binding->runtime->position = value;
        func_0028F260(binding->owner, binding->runtime);
    }
}
