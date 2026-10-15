// Original emitter pause/unpause setters use the same124 time field as the query.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ParticlePauseControl { char prefix[0x124]; float unpause_time; };
extern "C" void func_00178150(ParticlePauseControl *emitter)
{
    emitter->unpause_time=3.402823466e+38f;
}
extern "C" void func_00178160(ParticlePauseControl *emitter)
{
    emitter->unpause_time=-1.0f;
}
