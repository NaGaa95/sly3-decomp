// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "particle_emission_api.h"
class EmitParticle;
struct ContactWaveEntry {
    short delta, reserved;
    union { void (*simple)(void *); void (*set)(void *, ParticleWord, float); } call;
};
struct ContactWaveObject {
    unsigned char opaque00[0x18];
    float duration;
    unsigned int parameter;
    float radius, value;
    unsigned char opaque28[0xC0];
    ContactWaveEntry *table;
};
struct ContactWaveReceiver {
    ContactWaveObject common;
    unsigned char opaqueEC[8];
    unsigned int parameter;
};
struct ContactWaveContact { void *subject; char *owner; };
extern "C" {
extern char D_00475480[];
int func_0013B500(char *object, int kind);
EmitParticle *func_0020B9C0(void *game, int kind, void *list);
}
extern "C" int func_0020E320(void *receiver, const ContactWaveContact *contact, ParticleWord position)
{
    ContactWaveReceiver *source = static_cast<ContactWaveReceiver *>(receiver);
    if (func_0013B500(contact->owner, 0x65)) {
        ContactWaveObject *created = reinterpret_cast<ContactWaveObject *>(func_0020B9C0(D_00475480, 6, 0));
        if (created) {
            const float radius = 40.0f;
            ContactWaveEntry *entry = &created->table[1];
            entry->call.set(reinterpret_cast<char *>(created) + entry->delta, position, radius);
            created->duration = 0.75f;
            created->radius = radius;
            created->value = 30.0f;
            created->parameter = source->parameter;
        }
    }
    ContactWaveEntry *cleanup = &source->common.table[6];
    cleanup->call.simple(reinterpret_cast<char *>(source) + cleanup->delta);
    return 1;
}
