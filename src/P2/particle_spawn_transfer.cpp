// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "scene.h"
struct S;
struct ParticleSpawnMethod {
    short delta, reserved;
    void (*method)(void *);
};
struct ParticleSpawn {
    char prefix[0x10];
    SCENE_OBJECT *owner;
    char reserved14[0xE8 - 0x14];
    ParticleSpawnMethod *table;
    char reservedEC[8];
    void *property;
};
extern "C" {
void *func_001FE728(void *property, int flags);
void func_00202D30(S *object, void *resource);
}

extern "C" int func_0020E4B0(ParticleSpawn *particle)
{
    SCENE_OBJECT *instance = static_cast<SCENE_OBJECT *>(
        func_001FE728(particle->property, 1));
    instance->handle = particle->owner->handle;
    func_00202D30(reinterpret_cast<S *>(instance), particle);
    instance->anchor = particle->owner->anchor;
    ParticleSpawnMethod *method = &particle->table[6];
    method->method(reinterpret_cast<char *>(particle) + method->delta);
    return 1;
}
