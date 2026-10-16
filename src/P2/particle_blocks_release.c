// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S;
struct ParticleBlockList {
    char prefix[0xF8];
    int count;
    void *blocks[0];
};
extern unsigned char D_00475480[];
void func_0011E1F0(void *pool, void *allocation);
void func_0020BD70(struct S *object);

void func_0020E580(void *receiver)
{
    struct ParticleBlockList *particle = receiver;
    int i;
    for (i = 0; i < particle->count; ++i)
        func_0011E1F0(D_00475480 + 0x45AC, particle->blocks[i]);
    func_0020BD70((struct S *)particle);
}
