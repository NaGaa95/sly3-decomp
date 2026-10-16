// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "common.h"

typedef qword ParticleWord;
struct ParticleMatrix { ParticleWord rows[4]; };
struct SpatialRegistrationOwner;
struct SpatialRegistrationMethod {
    short adjustment, padding;
    const ParticleMatrix *(*matrix)(void *);
};
struct SpatialRegistrationEntry {
    qword position;
    float extent;
    long kind : 4;
    long category : 8;
    SpatialRegistrationOwner *owner;
    void *next;
};
struct SpatialRegistrationGeneration {
    unsigned char beforeGeneration[0xA4];
    int generation;
};
struct SpatialRegistrationOwner {
    unsigned char beforePrimary[0x0C];
    SpatialRegistrationMethod *primary;
    unsigned char beforeCategory[0x2C - 0x10];
    unsigned char category;
    unsigned char beforeExtent[0x34 - 0x2D];
    float extent;
    unsigned char beforeFlags[0x3C - 0x38];
    int flags;
    unsigned char beforeGenerationSource[0x50 - 0x40];
    SpatialRegistrationGeneration *generationSource;
    unsigned char beforePosition[0x80 - 0x54];
    qword position;
    float radius;
    unsigned char beforeGeneration[0x118 - 0x94];
    int generation;
    SpatialRegistrationEntry *entry;
};

extern "C" void func_00211F18(void *receiver)
{
    SpatialRegistrationOwner *object = (SpatialRegistrationOwner *)receiver;
    if (object->entry) {
        int value;
        object->entry->kind = 5;
        object->generation = -1;
        object->entry = 0;
        value = object->flags;
        if ((value ^ 1) & 1) *(int *)value &= ~0x100;
        else object->flags = value & ~0x100;
    }
}
