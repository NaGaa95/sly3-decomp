// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } U;
struct VECTOR4 { float x, y, z, w; } __attribute__((aligned(16)));
extern struct VECTOR4 D_00317560;
void func_0014B590(void *object, void *handle, int a, int count, void *points, int b, float g);

void func_0014B6E8(void *object, void *handle, int a, int b, float scale, float g)
{
    if (scale == 0.0f) {
        func_0014B590(object, handle, a, 1, &D_00317560, b, g);
    } else {
        struct VECTOR4 av[4] = {
            { 0.0f, 0.0f, 1.0f, 0.0f },
            { 0.866f, 0.0f, -0.5f, 0.0f },
            { 0.433f, 0.75f, -0.5f, 0.0f },
            { -0.433f, 0.75f, -0.5f, 0.0f },
        };
        int i;
        for (i = 0; i < 4; i++) {
            U u;
            qword r;
            __asm__("qmtc2.ni %1, %0" : "=j"(u.q) : "r"(scale));
            __asm__("vmulx.xyzw %0, %2, %1x" : "=j"(r) : "j"(u.q), "j"(*(qword *)&av[i]));
            *(qword *)&av[i] = r;
        }
        func_0014B590(object, handle, a, 4, av, b, g);
    }
}
