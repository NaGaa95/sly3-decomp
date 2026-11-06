// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct XF { char pad[0x30]; qword pos; };
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
struct X { char pad[0x30]; qword pos; char pad40[4]; LO *o44; char pad48[0x54 - 0x48]; int n54; };
struct SO : LO { char pad10[0x1000 - 0x10]; void *p1000; char pad1004[0x10B0 - 0x1004]; float f10B0; };
struct G { char pad[0x47B8]; void *p47B8; };
extern G D_00475480;
extern struct CLOCK { float t; float dt; } g_clock;
extern "C" {
void func_00173778(void *, qword, SO *, X **);
X *func_001738C0(void *, qword, SO *);
void func_00256CF8(SO *p, LO *o);
}
void func_00256CF8(SO *p, LO *o)
{
    qword pos = o->PxfGet()->pos;
    X *x = 0;
    if (p->p1000)
        func_00173778(p->p1000, p->PxfGet()->pos, p, &x);
    else
        x = func_001738C0(D_00475480.p47B8, p->PxfGet()->pos, p);
    x->pos = pos;
    x->o44 = o;
    x->n54 = 4;
    p->f10B0 = g_clock.t + 1.0f;
}
