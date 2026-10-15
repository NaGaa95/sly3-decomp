// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/vector_intrinsics.h"

struct FloatCurveRecord;
struct XYZOutput {
    float xyz[3];
    unsigned char residue[4];
} __attribute__((aligned(16)));
struct CurveXYZRuntime {
    unsigned char prefix[0x80];
    float lower_time, upper_time;
    float *lower_time_pointer, *upper_time_pointer;
    unsigned char unused90[10];
    short samples;
    unsigned char unused9c[0x24];
    XYZOutput lower_value, lower_derivative, upper_value, upper_derivative;
};
extern qword D_00317560;
extern "C" int func_0011E9F0(float, float, float);
extern "C" void func_0012D6F8(FloatCurveRecord *, float *, float *, XYZOutput *, XYZOutput *, XYZOutput *, XYZOutput *, float);
extern "C" void func_0012DCC0(FloatCurveRecord *, float *, float *, XYZOutput *, XYZOutput *, XYZOutput *, XYZOutput *, float);

static __inline__ qword PackedStorage(const XYZOutput *slot)
{
    qword value;
    __builtin_memcpy(&value, slot, sizeof(value));
    return value;
}
static __inline__ int NearXYZ(qword a, qword b)
{
    return func_0011E9F0(PackedVectorX(a), PackedVectorX(b), 0.0001f) &&
           func_0011E9F0(PackedVectorY(a), PackedVectorY(b), 0.0001f) &&
           func_0011E9F0(PackedVectorZ(a), PackedVectorZ(b), 0.0001f);
}

extern "C" void func_0012D438(FloatCurveRecord *record, CurveXYZRuntime *runtime)
{
    func_0012D6F8(record, &runtime->lower_time, &runtime->upper_time,
                 &runtime->lower_value, &runtime->upper_value,
                 &runtime->lower_derivative, &runtime->upper_derivative,
                 *runtime->lower_time_pointer);
    int stationary = NearXYZ(PackedStorage(&runtime->lower_value), PackedStorage(&runtime->upper_value)) &&
                     NearXYZ(D_00317560, PackedStorage(&runtime->lower_derivative)) &&
                     NearXYZ(D_00317560, PackedStorage(&runtime->upper_derivative));
    runtime->samples = stationary ? 2 : 1;
}

extern "C" void func_0012DA00(FloatCurveRecord *record, CurveXYZRuntime *runtime)
{
    func_0012DCC0(record, &runtime->lower_time, &runtime->upper_time,
                 &runtime->lower_value, &runtime->upper_value,
                 &runtime->lower_derivative, &runtime->upper_derivative,
                 *runtime->lower_time_pointer);
    int stationary = NearXYZ(PackedStorage(&runtime->lower_value), PackedStorage(&runtime->upper_value)) &&
                     NearXYZ(D_00317560, PackedStorage(&runtime->lower_derivative)) &&
                     NearXYZ(D_00317560, PackedStorage(&runtime->upper_derivative));
    runtime->samples = stationary ? 2 : 1;
}
