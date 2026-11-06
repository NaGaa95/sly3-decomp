// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct VECTOR { float x, y, z, w; } __attribute__((aligned(16)));
struct P8 { char pad[0x10]; qword v10; };
struct E { int k; int x4; struct P8 *p8; };
struct X { char pad[0x1C]; float f1C; };
struct Q8 { float g; };
struct Q { char pad[8]; struct Q8 *p8; };
struct S { char pad[0x1A0]; qword v1A0; char pad2[0x1F0 - 0x1B0]; qword v1F0; char pad3[0x11D8 - 0x200]; struct Q *p11D8; };
struct VU_FLOAT {
    qword q;
    VU_FLOAT(float f) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(f)); }
    VU_FLOAT(const float *pf) { __asm__("qmtc2.ni %1, %0" : "=j"(q) : "r"(*(const int *)pf)); }
};
static inline qword operator*(const qword &v, VU_FLOAT f)
{
    qword r;
    __asm__("vmulx.xyzw %0, %1, %2x" : "=j"(r) : "j"(v), "j"(f.q));
    return r;
}
extern "C" {
extern qword D_00317560;
struct X *func_00254F80(struct E *);
qword func_0024F278(struct S *, struct X *, float);
qword func_0024F318(struct S *, struct X *, float);
void func_00255038(struct E *e, struct S *p);
}
void func_00255038(struct E *e, struct S *p)
{
    qword v;
    qword w;
    v = D_00317560;
    w = D_00317560;
    switch (e->k) {
    case 0:
    case 1:
    case 2: {
        struct X *x = func_00254F80(e);
        if (x) {
            v = func_0024F278(p, x, x->f1C);
            w = func_0024F318(p, x, x->f1C);
        }
        break;
    }
    case 3:
        v = e->p8->v10;
        break;
    }
    if (p->p11D8)
        v = v * VU_FLOAT(&p->p11D8->p8->g);
    p->v1F0 = w;
    p->v1A0 = v * VU_FLOAT(-1.0f);
}
