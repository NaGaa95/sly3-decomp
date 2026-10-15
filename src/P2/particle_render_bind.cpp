// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "vifs.h"

struct ParticleFrames {
    int unknown0;
    int frame_count;
    char frame_storage[0x208];
    void *palette;
    int use_colors;
    int color_count;
    unsigned char colors[1];
};
struct ParticleDrawDefinition {
    float scale;
    char reserved04[0x1C];
    ParticleFrames *frames;
    int mode;
};
struct ParticleDefinition {
    char reserved00[0x1C];
    ParticleDrawDefinition *draw;
};
struct ParticleBindingProperty {
    char reserved00[4];
    ParticleDefinition *definition;
    char reserved08[0x68];
    float extent[3];
    char reserved7C[0x14];
    float color[3];
    char reserved9C[4];
    float coefficientsA0[3];
    char reservedAC[4];
    float age[3];
};
struct ParticleRenderView {
    char reserved00[0x1A0];
    float parameter1A0;
    char reserved1A4[0x10];
    float parameter1B4;
};
struct ParticleClock {
    float time;
    char reserved04[0x40];
    float elapsed;
};

extern VIFS D_0036C308;
extern ParticleClock D_0036BB98;
extern unsigned char D_00341FE0[];
extern unsigned char D_0036B260[];

extern "C" void func_00201C18(ParticleBindingProperty *property,
                              ParticleRenderView *view, int mode)
{
    bool special = mode == 12;
    uint *timing;
    uint *configuration;
    ParticleDrawDefinition *draw = property->definition->draw;
    D_0036C308.UnpackHelper(UPK_V4_32, 1, 5, 0, &timing);
    ((float *)timing)[0] = view->parameter1A0;
    ((float *)timing)[1] = view->parameter1B4;
    ((float *)timing)[2] = draw->mode == 1 ? draw->scale : 1.0f;
    ((float *)timing)[3] = D_0036BB98.time;

    ParticleFrames *frames = property->definition->draw->frames;
    D_0036C308.UnpackHelper(UPK_V4_32, 1, 6, 0, &configuration);
    configuration[0] = frames->use_colors != 0;
    configuration[1] = frames->color_count;
    configuration[2] = frames->frame_count;
    ((float *)configuration)[3] = D_0036BB98.elapsed;
    int count = frames->color_count;
    D_0036C308.AddVifUnpack(UPK_V4_8, count, frames->colors,
                          (int)(0x30u - (unsigned int)count));
    D_0036C308.AddVifUnpack(UPK_V3_32, 1,
                          !special ? (void *)property->color : D_00341FE0, 1);
    D_0036C308.AddVifUnpack(UPK_V3_32, 1, property->extent, 2);
    D_0036C308.AddVifUnpack(UPK_V3_32, 1, property->coefficientsA0, 3);
    D_0036C308.AddVifUnpack(UPK_V3_32, 1, property->age, 4);
    D_0036C308.AddVifUnpack(UPK_V4_32, 4,
                          !special ? frames->palette : (void *)D_0036B260, 0x30);
    D_0036C308.AddVifUnpackRefs(UPK_V4_32, frames->frame_count,
                              (char *)frames + 0x10, 0xF, 0);
}
