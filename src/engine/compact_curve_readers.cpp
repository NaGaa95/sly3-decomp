// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/bis.h"

struct CompactTimeSequence {
    signed char wide;
    unsigned char count;
    unsigned char bytes[0];
};
struct CompactCurveRecord {
    void *vtable;
    CompactTimeSequence *sequence;
};
struct FloatCurveRecord {
    CompactCurveRecord base;
    int mask;
    float values[0];
};
extern "C" void func_0012D1C0(CompactCurveRecord *, CBinaryInputStream *);

extern "C" void func_0012D330(FloatCurveRecord *record, CBinaryInputStream *stream)
{
    func_0012D1C0(&record->base, stream);
    float *write = record->values;
    record->mask = stream->U8Read();
    for (int remaining = (~record->mask) & 7; remaining; remaining >>= 1)
        if (remaining & 1)
            *write++ = stream->F32Read();
    for (int sample = 0; sample < record->base.sequence->count; ++sample)
        for (int remaining = record->mask; remaining; remaining >>= 1)
            if (remaining & 1) {
                write[0] = stream->F32Read();
                write[1] = stream->F32Read();
                write[2] = stream->F32Read();
                write += 3;
            }
}

extern "C" void func_0012D908(FloatCurveRecord *record, CBinaryInputStream *stream)
{
    func_0012D1C0(&record->base, stream);
    float *write = record->values;
    record->mask = stream->U8Read();
    for (int remaining = (~record->mask) & 7; remaining; remaining >>= 1)
        if (remaining & 1)
            *write++ = stream->F32Read();
    for (int sample = 0; sample < record->base.sequence->count; ++sample)
        for (int remaining = record->mask; remaining; remaining >>= 1)
            if (remaining & 1) {
                write[0] = stream->F32Read();
                write[1] = stream->F32Read();
                write += 2;
            }
}
