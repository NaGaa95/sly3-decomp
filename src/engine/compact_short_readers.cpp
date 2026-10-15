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
struct ShortCurveRecord {
    CompactCurveRecord base;
    signed char mask;
    signed char scale;
    short values[0];
};
extern "C" void func_0012D1C0(CompactCurveRecord *, CBinaryInputStream *);

extern "C" void func_0012E0B0(ShortCurveRecord *record, CBinaryInputStream *stream)
{
    func_0012D1C0(&record->base, stream);
    short *write = record->values;
    record->mask = stream->U8Read();
    record->scale = stream->S8Read();
    for (int remaining = (~record->mask) & 7; remaining; remaining >>= 1)
        if (remaining & 1)
            *write++ = stream->S16Read();
    for (int sample = 0; sample < record->base.sequence->count; ++sample) {
        *write++ = stream->U16Read();
        *write++ = stream->U16Read();
        for (int remaining = record->mask; remaining; remaining >>= 1)
            if (remaining & 1)
                *write++ = stream->S16Read();
    }
}

extern "C" void func_0012E7E0(ShortCurveRecord *record, CBinaryInputStream *stream)
{
    func_0012D1C0(&record->base, stream);
    short *write = record->values;
    record->mask = stream->U8Read();
    record->scale = stream->S8Read();
    for (int remaining = (~record->mask) & 7; remaining; remaining >>= 1)
        if (remaining & 1)
            *write++ = stream->S16Read();
    for (int sample = 0; sample < record->base.sequence->count; ++sample) {
        *write++ = stream->U16Read();
        for (int remaining = record->mask; remaining; remaining >>= 1)
            if (remaining & 1)
                *write++ = stream->S16Read();
    }
}
