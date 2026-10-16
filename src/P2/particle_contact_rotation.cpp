// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "particle_emission_api.h"
struct SCENE_OBJECT;
struct ParticleContactRecord { void *subject; SCENE_OBJECT *owner; };
struct ParticleContactMethod {
    short delta, reserved;
    void (*method)(void *);
};
struct ParticleContactView {
    char prefix[0x1C];
    void *property;
    char reserved20[0xE8 - 0x20];
    ParticleContactMethod *table;
    void *reservedEC;
    void *contactProperty;
};
extern "C" void *func_0020C8E8(void *particle, void *property, void *subject,
                              ParticleWord position, ParticleWord direction);
#include "rotation_matrix_intrinsics.h"
struct ParticleContactRotation {
    char prefix[0x40];
    ROTATION_MATRIX rotation;
};
extern "C" ROTATION_MATRIX func_001C9598(SCENE_OBJECT *source,
    SCENE_OBJECT *destination, ROTATION_MATRIX *rotation);

extern "C" int func_0020E210(ParticleContactView *particle,
    const ParticleContactRecord *contact, ParticleWord position,
    ParticleWord direction)
{
    ParticleContactRotation *created = static_cast<ParticleContactRotation *>(
        func_0020C8E8(particle, particle->property, contact->subject,
                      position, direction));
    created->rotation = func_001C9598(0, contact->owner, &created->rotation);
    ParticleContactMethod *method = &particle->table[6];
    method->method(reinterpret_cast<char *>(particle) + method->delta);
    return 1;
}
