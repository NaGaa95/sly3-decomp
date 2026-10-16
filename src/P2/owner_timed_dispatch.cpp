// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct DL { void *pvFirst, *pvLast; int ibDle; };
struct DLI;
struct Matrix4 { float elements[16]; } __attribute__((aligned(16)));
extern "C" {
extern DLI *D_0036AE94;
extern float D_0036BB98;
extern Matrix4 D_003174C0;
}
struct DLI {
    DL *pdl;
    void **ppv;
    int ibDle;
    DLI *pdliNext;
    DLI(DL *list)
        : pdl(list), ppv((void **)list), ibDle(list->ibDle),
          pdliNext(D_0036AE94)
    {
        D_0036AE94 = this;
    }
    ~DLI()
    {
        D_0036AE94 = pdliNext;
    }
    void *Next()
    {
        void *value = *ppv;
        ppv = (void **)((unsigned int)value + (unsigned int)ibDle);
        return value;
    }
};
struct TimedParticleMethod {
    short delta, reserved;
    void (*update)(void *, int, Matrix4 *);
};
struct TimedParticle {
    char prefix[0x14];
    float timestamp;
    char opaque18[0xE8 - 0x18];
    TimedParticleMethod *table;
};
struct TimedOwner {
    char prefix[0x130];
    int key;
    DL particles;
};
extern "C" void func_0020B8A8(void *receiver)
{
    TimedOwner *owner = static_cast<TimedOwner *>(receiver);
    DLI iterator(&owner->particles);
    TimedParticle *particle;
    while ((particle = static_cast<TimedParticle *>(iterator.Next())) != 0) {
        if (D_0036BB98 < particle->timestamp)
            continue;
        TimedParticleMethod *method = &particle->table[5];
        method->update(reinterpret_cast<char *>(particle) + method->delta,
                       1, &D_003174C0);
    }
}
extern "C" int func_0020B960(void *receiver)
{
    return static_cast<TimedOwner *>(receiver)->key != 1;
}
