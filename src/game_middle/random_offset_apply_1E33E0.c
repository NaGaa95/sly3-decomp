// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int OffsetVector __attribute__((mode(TI)));
struct Method { short adjustment, word2; void *function; };
struct OffsetTable {
    unsigned char prefix[0x138];
    struct Method getPosition;
    unsigned char gap148[0x148 - 0x140];
    struct Method setPosition;
};
struct OffsetObject {
    unsigned char prefix[0xC];
    struct OffsetTable *methods;
};
extern float D_00324A30[2];
float func_0011E940(float low, float high);
OffsetVector func_0011FD70(float heading, float radius, float height);
static __inline__ OffsetVector AddOffsetVectors(OffsetVector a, OffsetVector b)
{
    OffsetVector sum;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(sum) : "j"(a), "j"(b));
    return sum;
}
void func_001E33E0(struct OffsetObject *object)
{
    struct Method *method = &object->methods->getPosition;
    OffsetVector position = ((OffsetVector (*)(void *))method->function)((char *)object + method->adjustment);
    float heading = func_0011E940(-3.14159265f, 3.14159265f);
    float radius = func_0011E940(D_00324A30[0], D_00324A30[1]);
    OffsetVector offset = func_0011FD70(heading, radius, 0.0f);
    method = &object->methods->setPosition;
    ((void (*)(void *, OffsetVector))method->function)((char *)object + method->adjustment, AddOffsetVectors(position, offset));
}
