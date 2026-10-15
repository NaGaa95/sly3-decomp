// Original emitter pause/count controls; Sly 2 FPausedEmitter and SetEmitterParticleCount references.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct EmitterControl {
    char prefix[0xD0];
    int dirty;
    char reservedD4[0xE0-0xD4];
    int kind, count;
    char reservedE8[0x124-0xE8];
    float unpause_time;
};
struct EmissionClock { float time; };
extern "C" EmissionClock D_0036BB98;
extern "C" int func_00178170(EmitterControl *emitter)
{
    if (D_0036BB98.time < emitter->unpause_time)
        return 1;
    switch (emitter->kind) {
    case 1:
        if (emitter->count == 0)
            return 1;
    }
    return 0;
}
