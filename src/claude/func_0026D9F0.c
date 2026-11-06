// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { char pad[0x1B0]; int n1B0; int pad1B4; float f1B8; };
extern struct CLOCK { float t; float dt; } g_clock;
extern char D_00328B70[];
int func_001F43C8(struct S *);
float func_0011E598(float, float, float, void *, float *);  /* GSmooth */
void func_0026D7B0(struct S *, int);
void func_00240DB0(struct S *);
void func_0026D9F0(struct S *p)
{
    if (p->n1B0 != func_001F43C8(p)) {
        float a = (float)p->n1B0;
        p->n1B0 = (int)func_0011E598(a, (float)func_001F43C8(p), g_clock.dt, D_00328B70, 0);
        func_0026D7B0(p, 0);
    }
    if (p->f1B8 > 0.0f) {
        float f = p->f1B8 - g_clock.dt;
        p->f1B8 = f;
        if (f <= 0.0f) {
            p->f1B8 = 0.0f;
            func_00240DB0(p);
        }
    }
}
