// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/bis.h"

struct CompactTimeSequence;
struct CompactCurveRecord {
    void *vtable;
    CompactTimeSequence *sequence;
};
extern CompactTimeSequence **D_0036B160;

struct CompactXYZ {
    float x, y, z;
};
struct StaticXYZRecord {
    void *vtable;
    CompactXYZ value;
};
struct RawXYZSlot {
    CompactXYZ xyz;
    unsigned char residue[4];
} __attribute__((aligned(16)));
struct StaticXYZRuntime {
    unsigned char prefix[0x80];
    float lower_time;
    float upper_time;
    float *lower_time_pointer;
    float *upper_time_pointer;
    unsigned char unused90[10];
    short samples;
    unsigned char unused9c[0x24];
    RawXYZSlot first, first_tangent, last, last_tangent;
};
typedef char RuntimeLayoutGuard[sizeof(StaticXYZRuntime)==0x100?1:-1];

extern "C" void func_0012D1C0(CompactCurveRecord *record, CBinaryInputStream *stream)
{
    record->sequence = D_0036B160[stream->U16Read()];
    stream->U16Read();
}

extern "C" void func_0012D218(StaticXYZRecord *record, CBinaryInputStream *stream)
{
    stream->Read(12, &record->value);
}

static __inline__ void ClearXYZ(RawXYZSlot *slot)
{
    slot->xyz.x = slot->xyz.y = slot->xyz.z = 0;
}

extern "C" void func_0012D240(StaticXYZRecord *record, StaticXYZRuntime *runtime)
{
    runtime->samples = 2;
    runtime->upper_time = 1.0f;
    runtime->lower_time_pointer = &runtime->lower_time;
    runtime->upper_time_pointer = &runtime->upper_time;
    runtime->lower_time = 0.0f;
    runtime->first.xyz = record->value;
    __builtin_memcpy(&runtime->last, &runtime->first, sizeof(RawXYZSlot));
    ClearXYZ(&runtime->first_tangent);
    ClearXYZ(&runtime->last_tangent);
}
