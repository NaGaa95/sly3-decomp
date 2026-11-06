// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union QV { qword q; float f[4]; };
struct AREQ { int cb; int cbAlign; int pad[2]; AREQ(int c, int a) { cb = c; cbAlign = a; } };
class FRAME { public: FRAME(); ~FRAME(); int a[4]; };
struct VU_FLOAT { qword qw; };
struct VEntry { short delta; short pad; void *fn; };
struct Range { float min, max; };
struct Params {
    char pad0[0x20]; qword origin;
    char pad30[0x40 - 0x30]; Range speed;
    char pad48[0x50 - 0x48]; Range spread;
    Range life;
    char pad60[0x78 - 0x60]; float delay;
};
struct Node { char pad0[0x14]; Params *params; };
struct Zone { char pad0[0xD4]; Node **nodes; };
struct Owner { char pad0[0x13F0]; Zone *zone; };
struct Game { char pad0[0x4FA4]; int flag; };
struct Source { char pad0[0x1C]; int active; char pad20[4]; VEntry *vtable; };
struct Entry { char pad0[4]; Source *source; char pad8[4]; int id; char pad10[8]; float time; char pad1C[0x30 - 0x1C]; };
struct Batch { int count; qword *positions; qword *velocities; float *starts; float *ends; };
struct Spawner { char pad0[0x40]; VEntry *vtable; };
struct Result { char pad0[0x6C]; Spawner *spawner; };
struct ClockStep { float now, step; };
extern "C" {
extern ClockStep D_0036BB98;
extern qword D_00322EB0;
extern qword D_00322EC0;
float func_0011E940(float low, float high);
qword func_001C9428(int n, void *matrix, qword v);
qword func_001C94E8(int n, void *matrix, qword v);
void *func_001D25B0(const AREQ &req);
Result *func_001FE840(Zone *a, Zone *b, void *matrix, int flag);
void func_001B6B10(Game *game, Owner *owner, int count, Entry *entries);
}
static inline float Rand(Range *range) { return func_0011E940(range->min, range->max); }
static inline VU_FLOAT VuFloat(float g) { VU_FLOAT v; __asm__("qmtc2.ni %1,%0" : "=j"(v.qw) : "r"(g)); return v; }
static inline qword QwMulX(qword v, VU_FLOAT s) { qword r; __asm__("vmulx.xyzw %0,%1,%2x" : "=j"(r) : "j"(v), "j"(s.qw)); return r; }
static inline qword QwAddScaled(qword base, qword vec, VU_FLOAT s) { qword r; __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(vec), "j"(s.qw)); return r; }
void func_001B6B10(Game *game, Owner *owner, int count, Entry *entries)
{
    Zone *zone = owner->zone;
    Params *params;
    int i;
    if (!zone)
        return;
    params = zone->nodes[0]->params;
    params->origin = game->flag ? D_00322EC0 : D_00322EB0;
    for (i = 0; i < count; i++) {
        Entry *entry = &entries[i];
        int n;
        if (entry->id == -1)
            continue;
        {
            float expected = D_0036BB98.step * 15.0f;
            n = (int)expected;
            if (func_0011E940(0.0f, 1.0f) < expected - (float)n)
                n++;
        }
        if (n == 0)
            continue;
        {
            void *matrix = 0;
            if (entry->source->active)
                matrix = ((void *(*)(void *))entry->source->vtable[6].fn)((char *)entry->source + entry->source->vtable[6].delta);
            FRAME frame;
            Batch batch;
            batch.count = n;
            batch.positions = (qword *)func_001D25B0(AREQ(n * 16, 16));
            batch.velocities = (qword *)func_001D25B0(AREQ(n * 16, 16));
            batch.starts = (float *)func_001D25B0(AREQ(n * 4, 16));
            batch.ends = (float *)func_001D25B0(AREQ(n * 4, 16));
            int j;
            for (j = 0; j < n; j++) {
                QV position, direction, velocity;
                ((void (*)(void *, qword *, qword *, float))entry->source->vtable[5].fn)((char *)entry->source + entry->source->vtable[5].delta, &position.q, &direction.q, entry->time);
                velocity.q = QwMulX(direction.q, VuFloat(Rand(&params->speed)));
                float birth = D_0036BB98.now;
                birth -= Rand(&params->life);
                batch.starts[j] = birth;
                batch.ends[j] = batch.starts[j] + params->delay;
                if (params->spread.min != params->spread.max) {
                    qword origin = position.q;
                    position.q = QwAddScaled(origin, velocity.q, VuFloat(Rand(&params->spread)));
                }
                int offset = j * sizeof(qword);
                qword *outPosition = (qword *)(offset + (int)batch.positions);
                *outPosition = func_001C9428(0, matrix, position.q);
                qword *outVelocity = (qword *)(offset + (int)batch.velocities);
                *outVelocity = func_001C94E8(0, matrix, velocity.q);
            }
            {
                Spawner *spawner = func_001FE840(zone, zone, matrix, 1)->spawner;
                ((void (*)(void *, Batch *))spawner->vtable[2].fn)((char *)spawner + spawner->vtable[2].delta, &batch);
            }
        }
    }
}
