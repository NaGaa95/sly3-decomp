// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f; } U;
struct Hit { qword pos; qword pad10; qword normal; qword pad30; float t; unsigned char pad44[0x1C]; };
extern qword D_00317550;
int func_00165000(int kind, qword from, qword to, int a, int b, struct Hit *hit);
static inline qword AddScaled(qword base, qword dir, U *s, float g)
{
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s->q) : "r"(g));
    __asm__("vadda.xyzw $ACC,%1,$vf0\n\tvmaddx.xyzw %0,%2,%3x" : "=j"(r) : "j"(base), "j"(dir), "j"(s->q));
    return r;
}
void func_00184580(void *unused, qword *pos, qword *normal, int a, int b, float up, float down)
{
    U s;
    struct Hit hit;
    if (func_00165000(1, AddScaled(*pos, D_00317550, &s, up), AddScaled(*pos, D_00317550, &s, down), a, b, &hit) && hit.t != 0.0f) {
        *pos = hit.pos;
        if (normal) {
            *normal = hit.normal;
        }
    }
}
