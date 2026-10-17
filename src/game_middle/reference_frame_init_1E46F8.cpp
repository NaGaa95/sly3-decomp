// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "../P2/scene.h"
#include "../P2/state_position_ops.h"
#define Float(p, o) (*(float *)((char *)(p) + (o)))
#define Word(p, o) (*(int *)((char *)(p) + (o)))
struct FrameRows { qword row[3]; };
struct FrameSource {
    unsigned char opaque00[0xC];
    SCENE_VIRTUAL_ENTRY *vtable;
    unsigned char opaque10[0x90 - 0x10];
    float value;
};
struct SourceFrame { qword row[4]; };
union FrameFactor { qword q; float f[4]; };
extern "C" {
extern FrameRows D_00317490;
extern qword D_00317550;
void *func_002BA818(void *output, qword value);
}
static inline qword FrameScalar(float value)
{
    qword scalar;
    asm("qmtc2.ni %1,%0" : "=j"(scalar) : "r"(value));
    return scalar;
}
static inline qword AddFrameOffset(qword base, qword direction, qword scalar)
{
    qword result;
    asm("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
        : "=j"(result) : "j"(base), "j"(direction), "j"(scalar));
    return result;
}
extern "C" void func_001E46F8(FrameSource *source, void *frame)
{
    FrameRows *identity = &D_00317490;
    SCENE_VIRTUAL_ENTRY *entry = &source->vtable[36];
    SourceFrame *sourceFrame = (SourceFrame *)entry->Query((char *)source + entry->delta);
    FrameFactor factor;
    qword position = sourceFrame->row[3];
    factor.q = FrameScalar(2500.0f);
    func_002BA818((char *)frame + 0x30, AddFrameOffset(position, D_00317550, factor.q));
    *(FrameRows *)frame = *identity;
    Float(frame, 0x3C) = 1.0f;
    Float(frame, 0x0) = -1.0f;
    Float(frame, 0x28) = -7500.0f;
    Word(frame, 0x2C) = 0;
    Word(frame, 0x1C) = 0;
    Word(frame, 0xC) = 0;
    Word(frame, 0x40) = 0;
    Float(frame, 0x44) = 0.33333334f;
    Float(frame, 0x48) = 0.33333334f;
    Float(frame, 0x4C) = source->value;
}
