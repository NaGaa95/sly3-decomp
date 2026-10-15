// Reference algorithm: src/hand/func_00142880.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; };
extern struct CLOCK D_0036BB98;
float func_0011E940(float a, float b);
struct X { char pad[0x1208]; float a0, b0, a1, b1; int f; float tNext; };
void func_00155328(struct X *p)
{
    float t;
    if (p->f) {
        t = D_0036BB98.t;
        t += func_0011E940(p->a0, p->b0);
        p->tNext = t;
    } else {
        t = D_0036BB98.t;
        t += func_0011E940(p->a1, p->b1);
        p->tNext = t;
    }
}
