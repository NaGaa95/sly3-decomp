// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "vector_intrinsics.h"
#include "matrix_algorithms.h"

// Each frame supplies one complete eighty-byte sample. Translation defaults
// copy all four stored matrix words. Packed Euler W is Z sign-extension
// residue from the established platform operation, not a fourth angle.
struct TrajectorySample {
    qword position;
    qword rotation;
    float scale;
    float time_offset;
    int word28;
    int word2C;
    int use_explicit;
    unsigned char unused34[0x50 - 0x34];
};
typedef char TrajectorySampleIs80[(sizeof(TrajectorySample) == 0x50) ? 1 : -1];

// Only these eighty-four consumed bytes have a layout claim; no whole-prefix
// copy or claim about the external trailing record is made.
struct TrajectoryFrameDataPrefix {
    TrajectorySample sample;
    float additional_time;
};
struct TrajectoryFrameReferenceView {
    unsigned char unused[8];
    const TrajectoryFrameDataPrefix *data;
};
struct TrajectoryTask;
struct TrajectoryOwner;
struct TrajectoryNodeView {
    unsigned char prefix14[0x14];
    TrajectoryOwner *owner;
    unsigned char unused18[0x88 - 0x18];
    float time;
    TrajectoryTask *effect;
};
struct TrajectoryVirtualEntry {
    short delta;
    short reserved;
    void *call;
};
struct TrajectoryObjectView {
    unsigned char prefix[0xC];
    TrajectoryVirtualEntry *table;
    unsigned char unused10[0x118 - 0x10];
    float scalar118;
};

extern "C" {
    extern float D_00326C38;
    extern qword D_00317560;
    float func_00226458(TrajectoryOwner *);
    void *func_00226B20(void *);
    int func_0011E9F0(float, float, float);
    void *func_00169BF8(unsigned int);
    void *func_0016B5E8(void *, void *, int);
    void func_00169CE0(TrajectoryTask *);
    void func_0016BDE8(TrajectoryTask *, const TrajectorySample *,
                     const TrajectorySample *, const TrajectorySample *);
    void func_0022BB78(TrajectoryNodeView *, const TrajectoryFrameReferenceView *,
                      const TrajectoryFrameReferenceView *,
                      const TrajectoryFrameReferenceView *);
}

static inline bool PackedNear(qword reference, qword value)
{
    return func_0011E9F0(PackedVectorX(reference), PackedVectorX(value), 0.0001f)
        && func_0011E9F0(PackedVectorY(reference), PackedVectorY(value), 0.0001f)
        && func_0011E9F0(PackedVectorZ(reference), PackedVectorZ(value), 0.0001f);
}

static inline const MATRIX4 *Matrix(TrajectoryObjectView *provider)
{
    TrajectoryVirtualEntry *entry = provider->table + 36;
    return static_cast<MATRIX4 *>(((void *(*)(void *))entry->call)(
        (char *)provider + entry->delta));
}

void func_0022BB78(TrajectoryNodeView *p,
                  const TrajectoryFrameReferenceView *first,
                  const TrajectoryFrameReferenceView *second,
                  const TrajectoryFrameReferenceView *third)
{
    if (first->data->additional_time == 0.0f)
        p->time = D_00326C38;
    else
        p->time = (func_00226458(p->owner) + first->data->sample.time_offset)
                + first->data->additional_time;

    TrajectorySample samples[3] = {
        first->data->sample, second->data->sample, third->data->sample
    };
    TrajectoryObjectView *provider =
        static_cast<TrajectoryObjectView *>(func_00226B20(p));

    for (unsigned int i = 0; i < 3; ++i) {
        TrajectorySample *sample = &samples[i];
        if (!sample->use_explicit) {
            if (PackedNear(D_00317560, sample->position)) {
                const MATRIX4 *matrix = Matrix(provider);
                __builtin_memcpy(&sample->position, matrix->mat[3], 16);
            }
            if (PackedNear(D_00317560, sample->rotation))
                sample->rotation = func_0011D3C0((const MATRIX3 *)Matrix(provider));
        }
        if (sample->scale == 0.0f)
            sample->scale = provider->scalar118;
    }

    if (!p->effect) {
        p->effect = static_cast<TrajectoryTask *>(
            func_0016B5E8(func_00169BF8(0x170), provider, 13));
        func_00169CE0(p->effect);
    }
    func_0016BDE8(p->effect, &samples[0], &samples[1], &samples[2]);
}
