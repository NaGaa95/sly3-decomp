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
class SideParticle : public EmitParticle {
public:
    EmitOwner *emitter;
};
typedef ParticleWord qword;
typedef struct { qword r[3]; } M3;
struct O { char pad[0x40]; M3 mat; };
struct SideTrigger {
    char prefix[0x148];
    int owner;
    EmitOwner *left, *right;
    float probability;
    int previous;
    float last;
    O *direction_source;
};
typedef char SideParticleSize[sizeof(SideParticle) == 0x100 ? 1 : -1];
typedef char SideMatrixSize[sizeof(EmitFullMatrix) == 64 ? 1 : -1];

extern "C" {
extern char D_00475480[];
extern float D_0036BB98;
extern ParticleWord D_00325560;
ParticleWord func_0028E990(O *, O *, ParticleWord);
void *func_00165B28(char *);
float func_0011E940(float, float);
EmitParticle *func_0020B9C0(void *, int, void *);
EmitFullMatrix *func_0028BAD0(EmitFullMatrix *, void *, void *);
}

inline EmitFullMatrix *EmitGetMatrix(EmitOwner *owner)
{
    EmitVirtualEntry *entry = &owner->table[36];
    return entry->call.matrix((char *)owner + entry->delta);
}

static inline float SideDot(ParticleWord a, ParticleWord b)
{
    ParticleWord product, one;
    float result;
    __asm__("vmul.xyz %0,%2,%3\n\tvaddw.x %1,$vf0,$vf0w"
            : "=j"(product), "=j"(one) : "j"(a), "j"(b));
    __asm__("vadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z"
            : "+j"(product) : "j"(one));
    __asm__("mtc1 %1,%0" : "=f"(result) : "r"(product));
    return result;
}
static inline float SideMaximum(float a, float b)
{
    __asm__("max.s %0,%0,%1" : "+f"(a) : "f"(b));
    return a;
}

extern "C" void func_001F7770(SideTrigger *source)
{
    if (!source->owner || source->probability <= 0 || !source->direction_source)
        return;

    ParticleWord direction = func_0028E990(source->direction_source, 0, D_00325560);
    EmitOwner *camera = (EmitOwner *)func_00165B28(D_00475480);
    EmitFullMatrix *matrix = EmitGetMatrix(camera);
    int side = SideDot(direction, *(ParticleWord *)&matrix->basis.row[1]) < 0;
    if (side != source->previous) {
        if (func_0011E940(0, 1) < source->probability) {
            if (1 < D_0036BB98 - source->last) {
                EmitOwner *emitter;
                if (SideDot(direction, *(ParticleWord *)&matrix->basis.row[0]) < 0)
                    emitter = source->left;
                else
                    emitter = source->right;
                if (!emitter)
                    goto changed;
                SideParticle *particle = static_cast<SideParticle *>(
                    func_0020B9C0(D_00475480, 3, 0));
                if (!particle)
                    goto changed;
                source->last = D_0036BB98;
                particle->Set(*(ParticleWord *)EmitGetMatrix(emitter)->fourth, 1);
                {
                    int owner = source->owner;
                    particle->emitter = emitter;
                    particle->flags = owner;
                }
                EmitFullMatrix scale;
                func_0028BAD0(&scale, source->direction_source, 0);
                float extent = (scale.basis.row[0][1] - scale.basis.row[1][0]) * 0.5f;
                particle->duration = 1.5f / SideMaximum(1, __builtin_fabsf(extent));
            }
        }
changed:
        source->previous = side;
    }
}
