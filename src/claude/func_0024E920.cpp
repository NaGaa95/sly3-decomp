// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Pass the offset from this object's position to the other's on to func_0024E8E8.
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
extern "C" qword func_0024E8E8(LO *p, qword v);
extern "C" qword func_0024E920(LO *p, LO *q);
qword func_0024E920(LO *p, LO *q)
{
    qword a = q->PxfGet()->pos;
    qword r;
    __asm__("vsub.xyzw %0, %1, %2" : "=j"(r) : "j"(a), "j"(p->PxfGet()->pos));
    return func_0024E8E8(p, r);
}
