// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "common.h"

typedef union { qword q; float f[4]; } ScalarVector;
struct Property;
struct ParticleBatch {
    int count;
    qword *position, *velocity;
    float *birth, *death;
};
struct LifetimeParameters {
    unsigned char prefix[0x50];
    float displacement_low, displacement_high;
    float age_low, age_high;
    unsigned char to_lifetime[0x78 - 0x60];
    float lifetime;
};
struct BatchDefinition {
    unsigned char prefix[0x14];
    struct LifetimeParameters *timing;
};
struct BatchPropertyView {
    void *owner;
    struct BatchDefinition *definition;
};
struct Clock { float time; };
extern struct Clock D_0036BB98;
float func_0011E940(float low, float high);

void func_002001C0(struct Property *property, struct ParticleBatch *batch)
{
    struct LifetimeParameters *p = ((struct BatchPropertyView *)property)->definition->timing;
    {
        int i;
        for (i = 0; i < batch->count; ++i) {
            float time = D_0036BB98.time;
            float age = func_0011E940(p->age_low, p->age_high);
            batch->birth[i] = time - age;
            batch->death[i] = batch->birth[i] + p->lifetime;
        }
    }
    if (p->displacement_low != 0.0f || p->displacement_high != 0.0f) {
        int i;
        for (i = 0; i < batch->count; ++i) {
            float displacement = func_0011E940(p->displacement_low, p->displacement_high);
            qword position = batch->position[i];
            ScalarVector scalar;
            qword result;
            __asm__("qmtc2.ni %1,%0" : "=j"(scalar.q) : "r"(displacement));
            __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x"
                : "=j"(result) : "j"(position), "j"(batch->velocity[i]), "j"(scalar.q));
            batch->position[i] = result;
            batch->birth[i] -= displacement;
            batch->death[i] -= displacement;
        }
    }
}
