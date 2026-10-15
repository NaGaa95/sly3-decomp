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
struct ShortCurveRecord {
    CompactCurveRecord base;
    signed char mask, scale;
    unsigned short values[0];
};
struct XYZOutput { float xyz[3]; unsigned char residue[4]; } __attribute__((aligned(16)));
extern "C" int func_0012D0F0(CompactTimeSequence *, float);

static __inline__ int FrameAt(CompactTimeSequence *sequence, int index)
{
    return (sequence->wide == 0 ? sequence->bytes[index] :
            ((WideCompactTimeSequence *)sequence)->samples[index]);
}

extern float D_0036B168[];
extern float D_0036B178[][16];
static __inline__ void UnpackXYZ(const short *packed, int index, float *out)
{
    float scale = D_0036B168[index];
    out[0] = packed[0] * scale;
    out[1] = packed[1] * scale;
    out[2] = packed[2] * scale;
}
static __inline__ void UnpackTangents(unsigned int packed, int scale, float *out)
{
    for (int i = 2; i >= 0; --i) {
        float value = D_0036B178[scale][packed & 15];
        if (packed & 16)
            value = -value;
        *out++ = value;
        packed >>= 5;
    }
}
extern "C" void func_0012E490(ShortCurveRecord *record,
                             float *lower_time, float *upper_time,
                             XYZOutput *lower_value, XYZOutput *upper_value,
                             XYZOutput *lower_derivative, XYZOutput *upper_derivative,
                             float time)
{
    short lower_xyz[3] __attribute__((aligned(16)));
    short upper_xyz[3] __attribute__((aligned(16)));
    int index = func_0012D0F0(record->base.sequence, time);
    *lower_time = FrameAt(record->base.sequence, index - 1) * (1.0f / 60.0f);
    *upper_time = FrameAt(record->base.sequence, index) * (1.0f / 60.0f);
    unsigned short *values = record->values;
    int channels = 5;
    {
        int remaining = (~record->mask) & 7;
        int channel = 0;
        if (remaining) {
            short *lower = lower_xyz;
            do {
                if (remaining & 1) {
                    unsigned short value = *values++;
                    upper_xyz[channel] = value;
                    --channels;
                    *lower = value;
                }
                remaining >>= 1;
                ++lower;
                ++channel;
            } while (remaining);
        }
    }
    unsigned short *upper = values + index * channels;
    unsigned short *lower = upper - channels;
    int remaining = record->mask;
    int channel = 0;
    unsigned short *upper_components = upper + 2;
    unsigned short *lower_components = lower + 2;
    if (remaining) {
        short *out = lower_xyz;
        do {
            if (remaining & 1) {
                *out = *lower_components++;
                upper_xyz[channel] = *upper_components++;
            }
            remaining >>= 1;
            ++out;
            ++channel;
        } while (remaining);
    }
    UnpackTangents(lower[1], record->scale, lower_derivative->xyz);
    UnpackTangents(upper[0], record->scale, upper_derivative->xyz);
    UnpackXYZ(lower_xyz, record->scale, lower_value->xyz);
    UnpackXYZ(upper_xyz, record->scale, upper_value->xyz);
}
extern "C" void func_0012EBB0(ShortCurveRecord *record,
                             float *lower_time, float *upper_time,
                             XYZOutput *lower_value, XYZOutput *upper_value,
                             XYZOutput *lower_derivative, XYZOutput *upper_derivative,
                             float time)
{
    short lower_xyz[3] __attribute__((aligned(16)));
    short upper_xyz[3] __attribute__((aligned(16)));
    int index = func_0012D0F0(record->base.sequence, time);
    *lower_time = FrameAt(record->base.sequence, index - 1) * (1.0f / 60.0f);
    *upper_time = FrameAt(record->base.sequence, index) * (1.0f / 60.0f);
    unsigned short *values = record->values;
    int channels = 4;
    {
        int remaining = (~record->mask) & 7;
        int channel = 0;
        if (remaining) {
            short *lower = lower_xyz;
            do {
                if (remaining & 1) {
                    unsigned short value = *values++;
                    upper_xyz[channel] = value;
                    --channels;
                    *lower = value;
                }
                remaining >>= 1;
                ++lower;
                ++channel;
            } while (remaining);
        }
    }
    unsigned short *upper = values + index * channels;
    unsigned short *lower = upper - channels;
    int remaining = record->mask;
    int channel = 0;
    unsigned short *upper_components = upper + 1;
    unsigned short *lower_components = lower + 1;
    if (remaining) {
        short *out = lower_xyz;
        do {
            if (remaining & 1) {
                *out = *lower_components++;
                upper_xyz[channel] = *upper_components++;
            }
            remaining >>= 1;
            ++out;
            ++channel;
        } while (remaining);
    }
    UnpackTangents(lower[0], record->scale, lower_derivative->xyz);
    UnpackTangents(upper[0], record->scale, upper_derivative->xyz);
    UnpackXYZ(lower_xyz, record->scale, lower_value->xyz);
    UnpackXYZ(upper_xyz, record->scale, upper_value->xyz);
}
