// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Entry { short delta, pad; void *fn; };
struct Target { int pad[3]; struct Entry *vt; };
struct Self { unsigned char pad[0x24]; struct Entry *vt; };
extern qword D_00317550;
float func_0011E940(float lo, float hi);
qword func_0011FDD8(float a, float b, float c);
static inline float GAbs(float x) { return x < 0.0f ? -x : x; }
void func_001A0838(struct Self *self, qword *pos, qword *dir)
{
    struct Entry *e = &self->vt[6];
    struct Target *target = ((struct Target *(*)(void *))e->fn)((char *)self + e->delta);
    float yaw = func_0011E940(-3.14159265f, 3.14159265f);
    float r = func_0011E940(-1.0f, 1.0f);
    float pitch = GAbs(r) * r * 1.57079633f;
    float dist = func_0011E940(0.0f, 35.0f);
    qword base, offset, sum;
    e = &target->vt[36];
    base = *(qword *)(((unsigned char *(*)(void *))e->fn)((char *)target + e->delta) + 0x30);
    offset = func_0011FDD8(yaw, pitch, dist);
    __asm__("vadd.xyzw %0,%1,%2" : "=j"(sum) : "j"(base), "j"(offset));
    *pos = sum;
    *dir = D_00317550;
}
