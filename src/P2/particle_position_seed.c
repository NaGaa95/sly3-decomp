// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct ParticleSeedRange { float low, high; };
struct ParticleSeed {
    char prefix[0x18];
    float duration;
    char reserved1C[0xF0 - 0x1C];
    float position[3];
};
extern struct ParticleSeedRange D_00325A20;
void func_0020BDA8(void);
float func_0011E940(float low, float high);
void func_0020BC78(void *particle);

void func_0020CD18(struct ParticleSeed *particle, const float *configuration)
{
    func_0020BDA8();
    particle->duration *= func_0011E940(D_00325A20.low, D_00325A20.high);
    particle->position[0] = configuration[0];
    particle->position[1] = configuration[1];
    particle->position[2] = configuration[2];
    func_0020BC78(particle);
}
