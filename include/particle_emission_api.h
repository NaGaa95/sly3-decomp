#ifndef SLY3_PARTICLE_EMISSION_API_H
#define SLY3_PARTICLE_EMISSION_API_H
// The emitter and optional context are separate opaque borrowed records.
// Positions and velocities are complete aligned16-byte packed values;
// start and end arrays hold one32-bit float per emitted element.
typedef int ParticleWord __attribute__((mode(TI)));
#ifdef __cplusplus
extern "C" {
#endif
void func_00178F80(void *emitter, void *optional_context, int count,
    ParticleWord *positions, ParticleWord *velocities, float *starts, float *ends);
#ifdef __cplusplus
}
#endif
#endif
