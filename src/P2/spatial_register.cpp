// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "mat.h"

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

extern "C" char D_00475480[];
extern "C" float func_0011DF08(const MATRIX4 *);
extern "C" SpatialRegistrationEntry *func_00212120(
    void *, qword, float, float, int);

static __inline__ ParticleWord RuntimeAffinePointXYZ(const ParticleMatrix *matrix,ParticleWord point)
{
    ParticleWord result;
    __asm__("vmulax.xyz $ACC,%1,%5x\n\tvmadday.xyz $ACC,%2,%5y\n\tvmaddaz.xyz $ACC,%3,%5z\n\tvmaddw.xyz %0,%4,$vf0w"
            : "=j"(result) : "j"(matrix->rows[0]),"j"(matrix->rows[1]),"j"(matrix->rows[2]),"j"(matrix->rows[3]),"j"(point));
    return result;
}

extern "C" void func_00211F90(void *receiver)
{
    SpatialRegistrationOwner *object = (SpatialRegistrationOwner *)receiver;
    ParticleMatrix matrix = *object->primary[36].matrix(
        (char *)object + object->primary[36].adjustment);
    qword position = RuntimeAffinePointXYZ(&matrix, object->position);
    float radius = func_0011DF08((const MATRIX4 *)&matrix) * object->radius;
    SpatialRegistrationEntry *entry = func_00212120(
        D_00475480, position, radius, object->extent, object->category);
    object->entry = entry;
    if (entry) {
        entry->kind = 4;
        object->entry->owner = object;
        if ((object->flags ^ 1) & 1)
            *(int *)object->flags |= 0x100;
        else
            object->flags |= 0x100;
        object->generation = object->generationSource->generation;
    }
}
