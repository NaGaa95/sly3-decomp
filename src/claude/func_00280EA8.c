// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } VU;
struct P { char pad[0x30]; qword q30; };
struct VTE { short d; short pad; struct P *(*pf)(void *); };
struct D { float f0, f4, f8, fC, f10, f14, f18; };
struct O { int a[3]; struct VTE *vt; char pad[0xDC - 0x10]; struct D *xDC; char pad2[0x218 - 0xE0]; int x218;
           char pad3[0x248 - 0x21C]; float f248; char pad4[0x268 - 0x24C]; float f268; };
int func_0013B500(struct O *p, int k);
void func_00280F70(void *s, qword a, qword b, int x, int y);
static inline float GMax(float a, float b) { return a < b ? b : a; }
void func_00280EA8(void *s, struct O *p, int x, int y)
{
    VU a, b;
    a.q = b.q = p->vt[36].pf((char *)p + p->vt[36].d)->q30;
    if (func_0013B500(p, 0x32)) {
        a.f[2] += p->f268;
        if (p->x218)
            a.f[2] = GMax(p->f248, a.f[2]);
    } else {
        a.f[2] = p->xDC->f8;
    }
    b.f[2] = p->xDC->f18;
    func_00280F70(s, a.q, b.q, x, y);
}
