// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "common.h"
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
struct GuardedSpawn {
    char prefix[0xC]; EmitVirtualEntry *table;
    char reserved10[0x130-0x10]; int mode;
    char reserved134[0x16C-0x134]; EmitOwner *observer;
    char reserved170[0x194-0x170]; void *property;
    char reserved198[0x1A0-0x198]; float lowDelay, highDelay, delay;
    int firstArgument, secondArgument;
};
typedef char CheckParticleBase[sizeof(EmitParticle)==0xF0?1:-1];
typedef char CheckScriptParticle[sizeof(ScriptParticle)==0x110?1:-1];
extern "C" {
extern char D_00475480[], D_00347060[];
EmitParticle *func_0020B9C0(void *game, int kind, void *list);
float func_0011E940(float low, float high);
void func_001F7FA8(void *unused_receiver, int unused_mode);
void *func_001FE728(void *property, int flags);
void func_001F7588(void *receiver, int mode);
}
static inline EmitFullMatrix *GuardedSpawnMatrix(EmitOwner *owner)
{
    EmitVirtualEntry *entry=&owner->table[36];
    return entry->call.matrix((char *)owner+entry->delta);
}
extern "C" void func_001F7DC0(void *receiver, int mode)
{
    GuardedSpawn *object=(GuardedSpawn *)receiver;
    if(object->mode==mode)return;
    switch(mode) {
    case 0:
        object->delay=func_0011E940(object->lowDelay,object->highDelay);
        break;
    case 1: {
        EmitOwner *observer=object->observer;
        EmitVirtualEntry *entry=&observer->table[86];
        if(!((int (*)(void *))entry->call.method)((char *)observer+entry->delta)) {
            mode=object->mode;
            break;
        }
        ScriptParticle *particle=static_cast<ScriptParticle *>(func_0020B9C0(D_00475480,8,0));
        if(particle) {
            particle->actor=receiver;
            particle->configuration=D_00347060;
            particle->parameter=0;
            particle->Set(((ParticleWord *)GuardedSpawnMatrix((EmitOwner *)receiver))[3],1.0f);
            particle->flags=(int)receiver;
            particle->basis=GuardedSpawnMatrix((EmitOwner *)receiver)->basis;
        } else {
            func_001F7FA8(receiver,0);
        }
        observer=object->observer;
        entry=&observer->table[88];
        ((void (*)(void *,void *))entry->call.method)((char *)observer+entry->delta,receiver);
        observer=object->observer;
        entry=&observer->table[87];
        ((void (*)(void *,int,int))entry->call.method)
            ((char *)observer+entry->delta,object->firstArgument,object->secondArgument);
        if(object->property)func_001FE728(object->property,1);
        entry=&object->table[3];
        ((void (*)(void *,int,void *,int,void *,void *))entry->call.method)
            ((char *)receiver+entry->delta,5,0,0,0,0);
        entry=&object->table[80];
        ((void (*)(void *,int))entry->call.method)((char *)receiver+entry->delta,-1);
        return;
    }
    }
    func_001F7588(receiver,mode);
}
