// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; int n[4]; } V;
struct XF { float x, y; };
struct LO {
    char pad[12];
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual void v9();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17();
    virtual void v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual XF *PxfGet();
    virtual void v36();
    virtual void v37();
    virtual qword VelGet();
};
struct T { float f0, f4, f8; };
struct SO : LO { char pad10[0x134 - 0x10]; T *p134; char pad138[0x1BC - 0x138]; float f1BC; char pad1C0[0x1F0 - 0x1C0]; qword v1F0; char pad200[0x11CC - 0x200]; int k11CC; };
extern struct CLOCK { float t; float dt; } g_clock;
extern qword D_00317560;
extern char D_003274A0[];
static inline float Z(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
extern "C" {
float func_0011E598(float, float, float, void *, float *);
float func_002A3EE8(float, float);
void func_0024E878(SO *, float);
void *func_001F4A80(SO *);
float func_00168108(void *, float, float, float);
void func_00257D78(SO *p, int fOn);
}
void func_00257D78(SO *p, int fOn)
{
    T *t = p->p134;
    if (p->k11CC == 3) {
        V v;
        v.q = D_00317560;
        if (fOn) {
            qword vel = p->VelGet();
            float nx = -t->f0;
            float z = func_0011E598(Z(vel), nx + nx, g_clock.dt, D_003274A0, 0);
            v.n[0] = 0;
            v.f[2] = z;
            v.n[1] = 0;
        }
        p->v1F0 = v.q;
        XF *x = p->PxfGet();
        func_0024E878(p, func_002A3EE8(x->y, x->x));
    } else if (t->f8 != 0.0f && fOn) {
        func_0024E878(p, func_00168108(func_001F4A80(p), t->f0, t->f4, p->f1BC));
    }
}
