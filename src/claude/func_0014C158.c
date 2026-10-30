// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct Method { short delta, reserved; qword (*call)(void *); };
struct Object { unsigned char pad00[0xC]; struct Method *methods; };
extern float g_clock;
void func_0023C660(void *p);
void func_0014CE20(void *p);
void func_0014C218(void *p);
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
static inline int FSlow(char *p)
{
    return Length(Velocity((struct Object *)p)) < *(float *)(p + 0x138);
}
void func_0014C158(char *p)
{
    func_0023C660(p);
    if (*(float *)(p + 0x134) <= g_clock || FSlow(p))
        func_0014CE20(p);
    else if (*(int *)(p + 0x1DC))
        func_0014C218(p);
}
