// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
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
struct SO : LO {
    char pad10[0x3C - 0x10]; unsigned int n3C;
    char pad40[0x218 - 0x40]; int n218; float f21C;
    char pad220[0x284 - 0x220]; float f284;
};
extern struct CLOCK { float t; float dt; } g_clock;
extern "C" {
void func_001F3C48(SO *);
float func_002A3EE8(float, float);
void func_0024E878(SO *, float);
void func_0024DA88(SO *p);
}
void func_0024DA88(SO *p)
{
    func_001F3C48(p);
    XF *x = p->PxfGet();
    func_0024E878(p, func_002A3EE8(x->y, x->x));
    p->f21C = g_clock.t;
    p->n218 = 0;
    p->f284 = g_clock.t;
    if (!(p->n3C & 1))
        *(unsigned int *)p->n3C |= 0x10;
    else
        p->n3C |= 0x10;
}
