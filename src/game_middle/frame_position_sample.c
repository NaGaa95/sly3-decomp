// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int SampleVector __attribute__((mode(TI)));
struct SCENE_OBJECT;
struct SampleSource {
    unsigned char opaque00[0x100];
    SampleVector position;
};

float func_0011E940(float low, float high);
SampleVector func_001C9428(struct SCENE_OBJECT *source,
                          struct SCENE_OBJECT *destination,
                          SampleVector position);
SampleVector func_0011FD70(float heading, float radius, float height);
extern SampleVector D_00317550;

static __inline__ SampleVector AddSampleVectors(SampleVector a, SampleVector b)
{
    SampleVector sum;
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(sum) : "j"(a), "j"(b));
    return sum;
}

void func_001A2698(void *receiver, SampleVector *position, SampleVector *direction)
{
    struct SampleSource *source = (struct SampleSource *)receiver;
    float heading = func_0011E940(-3.14159265f, 3.14159265f);
    float radius = func_0011E940(0.0f, 75.0f);
    SampleVector origin = func_001C9428((struct SCENE_OBJECT *)receiver, 0,
                                      source->position);
    *position = AddSampleVectors(origin, func_0011FD70(heading, radius, 0.0f));
    *direction = D_00317550;
}
