// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Method { short delta, reserved; qword (*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
float func_0011E3B8(float rad);
static inline float Length(qword v)
{
    qword d, one, l;
    float g;
    __asm__("vmul.xyz %0, %2, %2\n\tvaddw.x %1, $vf0, $vf0w\n\tvadday.x $ACC, %0, %0y\n\tvmaddz.x %0, %1, %0z" : "=j"(d), "=j"(one) : "j"(v));
    __asm__("vsqrt $Q, %1x\n\tvwaitq\n\tvaddq.x %0, $vf0, $Q" : "=j"(l) : "j"(d));
    __asm__("mtc1 %1, %0" : "=f"(g) : "r"(l));
    return g;
}
static inline qword Velocity(struct Object *object)
{
    struct Method *method = &object->methods[38];
    return method->call((unsigned char *)object + method->delta);
}
int func_001468A8(char *p)
{
    if (__builtin_fabsf(*(float *)(p + 0x400) - Length(Velocity((struct Object *)p))) > 5.0f)
        return 0;
    if (__builtin_fabsf(func_0011E3B8(*(float *)(p + 0x404) - *(float *)(p + 0x1E0))) > 0.1f)
        return 0;
    if (__builtin_fabsf(func_0011E3B8(*(float *)(p + 0x408) - *(float *)(p + 0x1E4))) > 0.1f)
        return 0;
    if (__builtin_fabsf(func_0011E3B8(*(float *)(p + 0x40C) - *(float *)(p + 0x1E8))) > 0.1f)
        return 0;
    return 1;
}
