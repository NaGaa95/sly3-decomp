// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "common.h"
#include "particle_emission_api.h"
#include "transition_counter_api.h"

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
    virtual void Set(ParticleWord position, float weight);
    virtual void Initialize(const void *configuration, void *dependency);
};

class ScriptParticle : public EmitParticle {
public:
    const void *configuration;
    void *actor;
    int parameter;
    ParticleWord projectedPosition;
};
struct SpawnTransition {
    char prefix[0xC]; EmitVirtualEntry *table;
    char reserved10[0x130 - 0x10]; int mode;
    char reserved134[0x16C - 0x134]; EmitOwner *observer;
    char reserved170[0x194 - 0x170]; void *property;
    char reserved198[0x1A0 - 0x198]; float lowDelay, highDelay, delay;
};
typedef char CheckParticleBase[sizeof(EmitParticle) == 0xF0 ? 1 : -1];
typedef char CheckScriptParticle[sizeof(ScriptParticle) == 0x110 ? 1 : -1];
struct P;
struct SCENE_OBJECT;
extern "C" {
extern char D_00475480[], D_0036C700[], D_00346FF0[];
EmitParticle *func_0020B9C0(void *game, int kind, void *list);
float func_0011E940(float low, float high);
void *func_002459F8(int identifier);
void func_00244F08(P *sound, int mode);
void *func_001FE728(void *property, int flags);
void func_001853D8(char *context);
void func_001854C8(void *context, int event, SCENE_OBJECT *receiver);
void func_001F7588(void *receiver, int mode);
}
static inline EmitFullMatrix *SpawnMatrix(EmitOwner *owner)
{
    EmitVirtualEntry *entry = &owner->table[36];
    return entry->call.matrix((char *)owner + entry->delta);
}
extern "C" void func_001F7A90(void *receiver, int mode)
{
    SpawnTransition *object = (SpawnTransition *)receiver;
    if (object->mode == mode)
        return;
    switch (mode) {
    case 0:
        object->delay = func_0011E940(object->lowDelay, object->highDelay);
        break;
    case 1: {
        ScriptParticle *particle = static_cast<ScriptParticle *>(
            func_0020B9C0(D_00475480, 8, 0));
        if (particle) {
            particle->actor = receiver;
            particle->configuration = D_00346FF0;
            particle->parameter = 0;
            particle->Set(((ParticleWord *)SpawnMatrix((EmitOwner *)receiver))[3], 1.0f);
            particle->flags = (int)receiver;
            particle->basis = SpawnMatrix((EmitOwner *)receiver)->basis;
        } else {
            func_001F7C70(receiver, 0);
        }
        EmitOwner *observer = object->observer;
        if (observer) {
            EmitVirtualEntry *entry = &observer->table[88];
            ((void (*)(void *, void *))entry->call.method)
                ((char *)observer + entry->delta, receiver);
        }
        func_00244F08((P *)func_002459F8(0x29), 0);
        if (object->property)
            func_001FE728(object->property, 1);
        EmitVirtualEntry *entry = &object->table[3];
        ((void (*)(void *, int, void *, int, void *, void *))entry->call.method)
            ((char *)receiver + entry->delta, 5, 0, 0, 0, 0);
        func_001853D8(D_00475480);
        func_001854C8(D_0036C700, 14, (SCENE_OBJECT *)receiver);
        entry = &object->table[80];
        ((void (*)(void *, int))entry->call.method)
            ((char *)receiver + entry->delta, -1);
        return;
    }
    }
    func_001F7588(receiver, mode);
}
