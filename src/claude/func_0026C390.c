// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct S { char pad[0x1A0]; qword v1A0; char pad2[0x228 - 0x1B0]; int n228; float f22C; float f230; };
float func_002A3408(float);
static inline qword Scale(qword v, float g)
{
    union { qword q; float f; } s;
    qword r;
    __asm__("qmtc2.ni %1, %0" : "=j"(s.q) : "r"(g));
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(s.q));
    return r;
}
qword func_0026C390(struct S *p, float t)
{
    float a = 1.0f - func_002A3408(t * 3.14159265f) * 0.5f;
    float m = 1.0f;
    float k;
    if (p->n228)
        m = p->f22C;
    k = a * 2250.0f;
    return Scale(p->v1A0, p->f230 * k * m);
}
