// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/bis.h"
struct PackedXYZ { short x, y, z; };
struct PackedStaticXYZRecord {
    void *vtable;
    short scale;
    PackedXYZ value;
};
struct CompactXYZ { float x, y, z; };
struct RawXYZSlot {
    CompactXYZ xyz;
    unsigned char residue[4];
} __attribute__((aligned(16)));
struct PackedXYZRuntime {
    unsigned char prefix[0x80];
    float lower_time, upper_time;
    float *lower_time_pointer, *upper_time_pointer;
    unsigned char unused90[10];
    short samples;
    unsigned char unused9c[0x24];
    RawXYZSlot lower_value, lower_derivative, upper_value, upper_derivative;
};
extern float D_0036B168[];
static __inline__ void ClearXYZ(RawXYZSlot *slot)
{
    slot->xyz.x = slot->xyz.y = slot->xyz.z = 0;
}
static __inline__ void UnpackXYZ(const PackedXYZ *packed, int index, CompactXYZ *out)
{
    float scale = D_0036B168[index];
    out->x = packed->x * scale;
    out->y = packed->y * scale;
    out->z = packed->z * scale;
}
extern "C" void func_0012DED0(PackedStaticXYZRecord *record, CBinaryInputStream *stream)
{
    record->scale = stream->S8Read();
    record->value.x = stream->S16Read();
    record->value.y = stream->S16Read();
    record->value.z = stream->S16Read();
}
extern "C" void func_0012DF30(PackedStaticXYZRecord *record, PackedXYZRuntime *runtime)
{
    runtime->samples = 2;
    runtime->upper_time = 1.0f;
    runtime->lower_time_pointer = &runtime->lower_time;
    runtime->upper_time_pointer = &runtime->upper_time;
    runtime->lower_time = 0.0f;
    UnpackXYZ(&record->value, record->scale, &runtime->lower_value.xyz);
    __builtin_memcpy(&runtime->upper_value, &runtime->lower_value, sizeof(RawXYZSlot));
    ClearXYZ(&runtime->lower_derivative);
    ClearXYZ(&runtime->upper_derivative);
}
extern "C" void func_0012DFF0(PackedStaticXYZRecord *record, RawXYZSlot *value, RawXYZSlot *derivative)
{
    if (value)
        UnpackXYZ(&record->value, record->scale, &value->xyz);
    if (derivative)
        ClearXYZ(derivative);
}
