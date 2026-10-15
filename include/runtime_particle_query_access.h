#ifndef SLY3_RUNTIME_PARTICLE_QUERY_ACCESS_H
#define SLY3_RUNTIME_PARTICLE_QUERY_ACCESS_H

/* Minimum observed byte views; original class and allocation sizes are unknown. */
typedef struct RuntimeParticleQueryProperties {
    unsigned char opaque00[8];
    float scalar08;
    unsigned char opaque0c[4];
    int signed10;
    unsigned char opaque14[4];
    unsigned short unsigned18;
    unsigned char opaque1a[2];
    int signed1c;
} RuntimeParticleQueryProperties;

typedef struct RuntimeParticleQueryReceiver {
    unsigned char opaque00[0x24];
    RuntimeParticleQueryProperties *properties;
} RuntimeParticleQueryReceiver;

#define SLY3_QUERY_OFF(type, member) ((unsigned int)&(((type *)0)->member))
typedef char RuntimeParticleQueryPointer32[sizeof(void *) == 4 ? 1 : -1];
typedef char RuntimeParticleQueryFloat32[sizeof(float) == 4 ? 1 : -1];
typedef char RuntimeParticleQueryWord32[sizeof(int) == 4 ? 1 : -1];
typedef char RuntimeParticleQueryHalf16[sizeof(unsigned short) == 2 ? 1 : -1];
typedef char RuntimeParticleQueryPointerAt24[SLY3_QUERY_OFF(RuntimeParticleQueryReceiver, properties) == 0x24 ? 1 : -1];
typedef char RuntimeParticleQueryScalarAt08[SLY3_QUERY_OFF(RuntimeParticleQueryProperties, scalar08) == 8 ? 1 : -1];
typedef char RuntimeParticleQuerySignedAt10[SLY3_QUERY_OFF(RuntimeParticleQueryProperties, signed10) == 0x10 ? 1 : -1];
typedef char RuntimeParticleQueryUnsignedAt18[SLY3_QUERY_OFF(RuntimeParticleQueryProperties, unsigned18) == 0x18 ? 1 : -1];
typedef char RuntimeParticleQuerySignedAt1C[SLY3_QUERY_OFF(RuntimeParticleQueryProperties, signed1c) == 0x1c ? 1 : -1];
#undef SLY3_QUERY_OFF

#ifdef __cplusplus
extern "C" {
#endif
float func_002B5708(RuntimeParticleQueryReceiver *receiver);
unsigned short func_002B5740(RuntimeParticleQueryReceiver *receiver);
int func_002B57D0(RuntimeParticleQueryReceiver *receiver);
int func_002B57E0(RuntimeParticleQueryReceiver *receiver);
#ifdef __cplusplus
}
#endif
#endif
