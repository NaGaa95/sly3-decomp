// Sly3 particle emission, recovered from the Sly2 emit loop and original factory callbacks.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "resource_attachment_api.h"
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
struct EmitShader { EmitOwner *owner; int word4; int flags8; void *dependency; };
union EmitConfiguration { int selector; unsigned char raw[0x14]; };
struct EmitParticleSource {
    char prefix[8];
    EmitShader *shader;
    char reserved0[0xB0-0xC];
    ParticleWord orientation;
    EmitConfiguration configuration;
    float random_low, random_high;
    int kind, owner_key;
    char reserved1[0xF4-0xE4];
    float override24, override28;
};
class EmitParticle {
public:
    char prefix[0x14];
    float start, duration;
    int flags;
    char reserved20[4];
    float override24, override28;
    char reserved2C[4];
    ParticleWord orientation;
    EmitMatrixPrefix basis;
    char reserved70[0x20];
    ParticleWord velocity;
    char trailing[0xE8-0xA0];
    // Original eleven particle primaries at E8 use only A0/A1/F12 for this slot.
    virtual void Set(ParticleWord position, float weight);
    // Initializers consume a subtype record at C0 plus the genuine dependency;
    // no inherited A3 or FPR is a semantic input to the actual table targets.
    virtual void Initialize(const void *configuration, void *dependency);
};
// key8 is a raw32-bit counted attachment identity; callers may use owner address bits.
struct EmitOptionalContext { int word0; EmitOwner **output; int attachment_key; };
typedef char EmitCheckWordSize[sizeof(ParticleWord) == 16 ? 1 : -1];
typedef char EmitCheckMatrixPrefix[sizeof(EmitMatrixPrefix) == 48 ? 1 : -1];
typedef char EmitCheckFullMatrix[sizeof(EmitFullMatrix) == 64 ? 1 : -1];
typedef char EmitCheckTableEntry[sizeof(EmitVirtualEntry) == 8 ? 1 : -1];
typedef char EmitCheckParticle[sizeof(EmitParticle) == 0xF0 ? 1 : -1];
// The initializer consumes a subtype-specific raw record at C0.  Only kind1 reads
// its first word as a lookup key; other genuine particle initializers interpret
// the record themselves.  The matrix prefix copy writes precisely three rows.
// Optional preexisting owners and shader owners must remain compatible live
// objects, as required by the original indirect calls; no runtime guard is added.
extern "C" {
extern char D_00475480[];
EmitOwner *func_0020AFC0(void *game, int key);
EmitParticle *func_0020B9C0(void *game, int kind, void *list);
float func_0011E940(float low, float high);
void func_00179C28(void *payload, EmitParticleSource *source);
void *func_0017E1B8(void *game, int flags, int key, void *state);
int func_0011B0F0(void *list);
}
inline EmitFullMatrix *EmitGetMatrix(EmitOwner *owner)
{
    EmitVirtualEntry *entry = &owner->table[36];
    return entry->call.matrix((char *)owner + entry->delta);
}
inline void EmitActivateOwner(EmitOwner *owner)
{
    EmitVirtualEntry *entry = &owner->table[9];
    entry->call.method((char *)owner + entry->delta);
}
extern "C" void func_00178F80(void *emitter_record, void *optional_context,
    int count, ParticleWord *positions, ParticleWord *velocities, float *starts, float *ends)
{
    EmitParticleSource *source = static_cast<EmitParticleSource *>(emitter_record);
    EmitOptionalContext *context = static_cast<EmitOptionalContext *>(optional_context);
    EmitOwner *owner = 0;
    EmitParticle *particle;
    int i;
    if (context && context->output)
        owner = *context->output;
    if (!owner) {
        owner = func_0020AFC0(D_00475480, source->owner_key);
        if (!owner)
            return;
        if (context && context->output)
            *context->output = owner;
        if (context && context->attachment_key)
            func_0013BD00(owner, context->attachment_key);
    }
    if (!owner)
        return;
    for (i = 0; i < count &&
         (particle = func_0020B9C0(D_00475480, source->kind, (char *)owner + 0x134)) != 0; ++i) {
        particle->Set(positions[i], func_0011E940(source->random_low, source->random_high));
        if (source->override24 != 0.0f || source->override28 != 0.0f) {
            particle->override24 = source->override24;
            particle->override28 = source->override28;
        }
        particle->velocity = velocities[i];
        particle->start = starts[i];
        particle->duration = ends[i] - starts[i];
        particle->orientation = source->orientation;
        func_00179C28(particle->trailing, source);
        particle->flags = source->shader->flags8;
        if (source->shader->owner)
            particle->basis = EmitGetMatrix(source->shader->owner)->basis;
        void *dependency = source->shader->dependency;
        if (source->kind == 1)
            dependency = func_0017E1B8(D_00475480, 4,
                source->configuration.selector, source->shader->owner);
        particle->Initialize(&source->configuration, dependency);
    }
    if (func_0011B0F0((char *)owner + 0x134))
        EmitActivateOwner(owner);
}
