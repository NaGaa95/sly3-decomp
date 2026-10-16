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
extern "C" int func_0013B500(char *object, int kind);

extern "C" int func_0020CB98(ParticleContactView *particle,
    const ParticleContactRecord *contact, ParticleWord position,
    ParticleWord direction)
{
    if (!func_0013B500(reinterpret_cast<char *>(contact->owner), 0x65))
        func_0020C8E8(particle, particle->contactProperty, contact->subject,
                      position, direction);
    ParticleContactMethod *method = &particle->table[6];
    method->method(reinterpret_cast<char *>(particle) + method->delta);
    return 1;
}
