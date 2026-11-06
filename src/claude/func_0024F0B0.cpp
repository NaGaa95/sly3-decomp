// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
typedef union { qword q; float f[4]; } V;
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
    virtual void w36();
    virtual void w37();
    virtual void w38();
    virtual void w39();
    virtual void SetVelocity(qword v);
};
struct O { char pad[0xB0]; qword vB0; };
struct SO : LO { char pad10[0x4C - 0x10]; O *p4C; char pad50[0x1BC - 0x50]; float f1BC; char pad1C0[0x204 - 0x1C0]; char a204[1]; };
extern struct CLOCK { float t; float dt; } g_clock;
extern "C" {
float func_002A3EE8(float, float);
float func_0011E3B8(float);
float func_0011E598(float, float, float, void *, float *);
void func_0024F0B0(SO *p);
}
void func_0024F0B0(SO *p)
{
    float zero = 0.0f;
    XF *x = p->PxfGet();
    float d = func_0011E3B8(p->f1BC - func_002A3EE8(x->y, x->x));
    V v;
    v.q = p->p4C->vB0;
    if (func_0011E598(zero, d, g_clock.dt, p->a204, &v.f[2]) == zero)
        v.f[2] = func_0011E3B8((d + d) / g_clock.dt);
    p->SetVelocity(v.q);
}
