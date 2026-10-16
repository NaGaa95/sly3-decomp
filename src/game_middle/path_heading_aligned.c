// SLY3_CFLAGS: -Os -G0
struct HeadingSlot { short delta, word2; void *method; };
struct HeadingActor {
    unsigned char opaque00[0xC];
    struct HeadingSlot *methods;
    unsigned char opaque10[0x1B8 - 0x10];
    float heading;
};
float func_002A3EE8(float y, float x);
float func_0011E3B8(float angle);

int func_001D6658(struct HeadingActor *actor)
{
    const float *matrix = ((const float *(*)(void *))actor->methods[36].method)(
        (char *)actor + actor->methods[36].delta);
    float difference = func_0011E3B8(actor->heading - func_002A3EE8(matrix[1], matrix[0]));
    if (__builtin_fabsf(difference) < 0.017453294f)
        return 1;
    return 0;
}
