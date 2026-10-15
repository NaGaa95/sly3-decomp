// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/bis.h"
struct CompactTimeSequence {
    signed char wide;
    unsigned char count;
    unsigned char bytes[0];
};
struct ScalarKey { float value, incoming, outgoing; };
struct ScalarCurveRecord {
    void *vtable;
    CompactTimeSequence *sequence;
    ScalarKey *keys;
};
struct ConstantScalarRecord { void *vtable; float value; };
extern CompactTimeSequence **D_0036B160;
extern "C" void *func_00117B40(void *, unsigned int, int);
extern "C" void func_0012EFE0(ConstantScalarRecord *record, CBinaryInputStream *stream)
{
    record->value = stream->F32Read();
}
extern "C" void func_0012F010(ConstantScalarRecord *record, float *value, float *derivative)
{
    if (value)
        *value = record->value;
    if (derivative)
        *derivative = 0;
}
extern "C" void func_0012F030(ScalarCurveRecord *record, CBinaryInputStream *stream, void *heap)
{
    record->sequence = D_0036B160[stream->U16Read()];
    stream->U16Read();
    record->keys = (ScalarKey *)func_00117B40(heap, record->sequence->count * sizeof(ScalarKey), 0x13);
    for (int i = 0; i < record->sequence->count; ++i) {
        ScalarKey *key = &record->keys[i];
        key->value = stream->F32Read();
        key->incoming = stream->F32Read();
        key->outgoing = stream->F32Read();
    }
}
