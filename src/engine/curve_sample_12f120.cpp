// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct CompactTimeSequence {
    signed char wide;
    unsigned char count;
    unsigned char bytes[0];
};
struct WideCompactTimeSequence {
    signed char wide;
    unsigned char count;
    unsigned short samples[0];
};
struct CurveRecord {
    void *vtable;
    CompactTimeSequence *sequence;
    float *values;
};
extern "C" int func_0012D0F0(CompactTimeSequence *, float);
extern "C" void func_00118468(float dt, float t, float dtScale,
                              float g0, float dg0, float g1, float dg1, float *pg, float *pdg);

static __inline__ int FrameAt(CompactTimeSequence *sequence, int index)
{
    return (sequence->wide == 0 ? sequence->bytes[index] :
            ((WideCompactTimeSequence *)sequence)->samples[index]);
}

extern "C" void func_0012F120(CurveRecord *record, float *value, float *derivative, float time, float scale)
{
    int index = func_0012D0F0(record->sequence, time);
    float lower_time = FrameAt(record->sequence, index - 1) * (1.0f / 60.0f);
    float upper_time = FrameAt(record->sequence, index) * (1.0f / 60.0f);
    int offset = index * 12;
    float *upper = (float *)((char *)record->values + offset);
    float *lower = (float *)((char *)record->values + (offset - 12));
    float *g = value;
    float *dg = derivative;
    float s = scale;
    func_00118468(upper_time - lower_time, time - lower_time, s,
                  lower[0], lower[2], upper[0], upper[1], g, dg);
}
