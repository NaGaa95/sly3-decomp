// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "particle_emission_api.h"

struct EmitMatrixPrefix { float row[3][4]; } __attribute__((aligned(16)));
struct EmitFullMatrix { EmitMatrixPrefix basis; float fourth[4]; } __attribute__((aligned(16)));
struct EmitVirtualEntry {
    short delta;
    short unused;
    union {
        void (*method)(void *);
        EmitFullMatrix *(*matrix)(void *);
    } call;
};
struct EmitOwner { char prefix[12]; EmitVirtualEntry *table; };
struct TriggerPosition { char prefix[0x70]; ParticleWord position; };
union TriggerShapeState {
    unsigned long flags;
    struct { unsigned int flags_low; int property; } words;
};
struct TriggerShape {
    TriggerPosition *position;
    int word4;
    float radius;
    char reservedC[0x18-0xC];
    TriggerShapeState state;
    char remaining[0xD0-0x20];
};
struct TriggerObject {
    char prefix[0xD0];
    int count;
    TriggerShape *shapes;
};
struct TriggerNode { char prefix[0x10]; TriggerObject *object; };
struct TriggerSource {
    char prefix[0x18C];
    float radius;
    int filter;
};
struct TriggerContact {
    ParticleWord position, surface;
    int kind;
    void *reference;
};
typedef char TriggerShapeSize[sizeof(TriggerShape) == 0xD0 ? 1 : -1];
typedef char TriggerContactSize[sizeof(TriggerContact) == 0x30 ? 1 : -1];

extern "C" {
int func_00240E10(void *, int);
void func_001F7700(char *, int);
int func_001CD098(ParticleWord position, TriggerShape *shape, int mask,
    int triangle_count, void *triangles, int capacity, TriggerContact *contacts, float radius);
}
inline EmitFullMatrix *EmitGetMatrix(EmitOwner *owner)
{
    EmitVirtualEntry *entry = &owner->table[36];
    return entry->call.matrix((char *)owner + entry->delta);
}
static inline ParticleWord TriggerSubtract(ParticleWord a, ParticleWord b)
{
    ParticleWord result;
    __asm__("vsub.xyzw %0,%1,%2" : "=j"(result) : "j"(a), "j"(b));
    return result;
}
static inline float TriggerLengthSquared(ParticleWord vector)
{
    ParticleWord product, one;
    float result;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\t"
            "vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "=j"(product), "=&j"(one) : "j"(vector));
    __asm__("mtc1 %1,%0" : "=f"(result) : "r"(product));
    return result;
}
static inline float TriggerMaximum(float a, float b)
{
    __asm__("max.s %0,%0,%1" : "+f"(a) : "f"(b));
    return a;
}

extern "C" int func_001F7030(void *receiver, void *input)
{
    TriggerSource *source = static_cast<TriggerSource *>(receiver);
    TriggerNode *node = static_cast<TriggerNode *>(input);
    TriggerContact contact;
    float maximum = TriggerMaximum(source->radius, 300);
    TriggerObject *object = node->object;
    ParticleWord here = *(ParticleWord *)EmitGetMatrix((EmitOwner *)source)->fourth;
    float distance = TriggerLengthSquared(TriggerSubtract(here,
        *(ParticleWord *)EmitGetMatrix((EmitOwner *)object)->fourth));
    if (maximum * maximum < distance)
        return 0;

    int count = object->count;
    TriggerShape *shapes = object->shapes;
    for (int i = 0; i < count; ++i) {
        TriggerShape *shape = &shapes[i];
        if (shape->state.flags & 0x80000UL)
            continue;
        if (!shape->state.words.property) {
            if (source->filter)
                continue;
        } else if (!(func_00240E10(source, shape->state.words.property) & 2))
            continue;

        if (shape->state.flags & 0x20000UL) {
            float radius = source->radius + shape->radius;
            ParticleWord position = *(ParticleWord *)EmitGetMatrix((EmitOwner *)source)->fourth;
            if (TriggerLengthSquared(TriggerSubtract(position, shape->position->position)) < radius * radius) {
                func_001F7700((char *)source, (int)object);
                return 1;
            }
        } else {
            ParticleWord position = *(ParticleWord *)EmitGetMatrix((EmitOwner *)source)->fourth;
            if (func_001CD098(position, shape, 0x7FFFFFFF, 0, 0, 1, &contact, source->radius)) {
                func_001F7700((char *)source, (int)object);
                return 1;
            }
        }
    }
    return 0;
}
