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
struct CompactCurveRecord {
    void *vtable;
    CompactTimeSequence *sequence;
};
struct FloatCurveRecord {
    CompactCurveRecord base;
    int mask;
    float values[0];
};
struct XYZOutput { float xyz[3]; unsigned char residue[4]; } __attribute__((aligned(16)));
extern "C" int func_0012D0F0(CompactTimeSequence *, float);

static __inline__ int FrameAt(CompactTimeSequence *sequence, int index)
{
    return (sequence->wide == 0 ? sequence->bytes[index] :
            ((WideCompactTimeSequence *)sequence)->samples[index]);
}

extern "C" void func_0012D6F8(FloatCurveRecord *record,
                             float *lower_time, float *upper_time,
                             XYZOutput *lower_value, XYZOutput *upper_value,
                             XYZOutput *lower_derivative, XYZOutput *upper_derivative,
                             float time)
{
    int index = func_0012D0F0(record->base.sequence, time);
    *lower_time = FrameAt(record->base.sequence, index - 1) * (1.0f / 60.0f);
    *upper_time = FrameAt(record->base.sequence, index) * (1.0f / 60.0f);
    float *values = record->values;
    int channels = 3;
    int remaining = (~record->mask) & 7;
    if (remaining) {
        float *ld = lower_derivative->xyz, *ud = upper_derivative->xyz;
        float *lv = lower_value->xyz, *uv = upper_value->xyz;
        do {
            int selected = remaining & 1;
            remaining >>= 1;
            if (selected) {
                *lv = *uv = *values++;
                *ld = *ud = 0;
                --channels;
            }
            ++ld; ++ud; ++lv; ++uv;
        } while (remaining);
    }
    float *upper = values + index * channels * 3;
    float *lower = upper - channels * 3;
    remaining = record->mask;
    if (remaining) {
        float *uv = upper_value->xyz, *ud = upper_derivative->xyz;
        float *lv = lower_value->xyz, *ld = lower_derivative->xyz;
        do {
            int selected = remaining & 1;
            remaining >>= 1;
            if (selected) {
                *ld = lower[1];
                *lv = lower[2];
                lower += 3;
                *ud = upper[0];
                *uv = upper[2];
                upper += 3;
            }
            ++uv; ++ud; ++lv; ++ld;
        } while (remaining);
    }
}

extern "C" void func_0012DCC0(FloatCurveRecord *record,
                             float *lower_time, float *upper_time,
                             XYZOutput *lower_value, XYZOutput *upper_value,
                             XYZOutput *lower_derivative, XYZOutput *upper_derivative,
                             float time)
{
    int index = func_0012D0F0(record->base.sequence, time);
    *lower_time = FrameAt(record->base.sequence, index - 1) * (1.0f / 60.0f);
    *upper_time = FrameAt(record->base.sequence, index) * (1.0f / 60.0f);
    float *values = record->values;
    int channels = 3;
    int remaining = (~record->mask) & 7;
    if (remaining) {
        float *ld = lower_derivative->xyz, *ud = upper_derivative->xyz;
        float *lv = lower_value->xyz, *uv = upper_value->xyz;
        do {
            int selected = remaining & 1;
            remaining >>= 1;
            if (selected) {
                *lv = *uv = *values++;
                *ld = *ud = 0;
                --channels;
            }
            ++ld; ++ud; ++lv; ++uv;
        } while (remaining);
    }
    float *upper = values + index * channels * 2;
    float *lower = upper - channels * 2;
    remaining = record->mask;
    if (remaining) {
        float *ud = upper_derivative->xyz, *uv = upper_value->xyz;
        float *ld = lower_derivative->xyz, *lv = lower_value->xyz;
        do {
            int selected = remaining & 1;
            remaining >>= 1;
            if (selected) {
                *lv = lower[1];
                *ld = lower[0];
                lower += 2;
                *uv = upper[1];
                *ud = upper[0];
                upper += 2;
            }
            ++ud; ++uv; ++ld; ++lv;
        } while (remaining);
    }
}
