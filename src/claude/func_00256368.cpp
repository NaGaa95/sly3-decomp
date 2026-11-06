// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Heading angle of the target object (0: looked up, 1: the attached one).
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
};
struct S { char pad[0xC]; LO *pc; int k; };
extern "C" {
LO *func_00256318(void);
void func_0028FFD8(LO *);
float func_002A3EE8(float, float);
float func_00256368(S *p);
}
static inline float Heading(LO *o)
{
    XF *x = o->PxfGet();
    return func_002A3EE8(x->y, x->x);
}
float func_00256368(S *p)
{
    float g = 0.0f;
    switch (p->k) {
    case 0: {
        LO *o = func_00256318();
        func_0028FFD8(o);
        g = Heading(o);
        break;
    }
    case 1:
        g = Heading(p->pc);
        break;
    case -1:
        break;
    }
    return g;
}
