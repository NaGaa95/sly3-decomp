// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct Method { short adjustment, reserved; qword (*function)(void *); };
struct Source { unsigned char prefix[0xC]; struct Method *table; unsigned char gap10[0x248 - 0x10]; float base; };
qword func_00250600(struct Source *source);
static inline float Z(qword q) { float f; __asm__("pextuw %0,$0,%1" : "=r"(f) : "r"(q)); return f; }
static inline float sqrtf_(float x) { float r; __asm__ __volatile__("sqrt.s %0, %1" : "=&f"(r) : "f"(x)); return r; }
static inline float maxf(float a, float b) { __asm__("max.s %0,%0,%1" : "+f"(a) : "f"(b)); return a; }
float func_00250418(struct Source *source, float offset, float gravity)
{
    struct Method *method = source->table + 38;
    float floor;
    register float base __asm__("$f0");
    float height;
    qword pos;
    floor = Z(method->function((char *)source + method->adjustment));
    pos = func_00250600(source);
    base = source->base;
    height = Z(pos) - base - offset;
    return maxf(floor, sqrtf_(maxf(0.0f, (gravity + gravity) * height)));
}
