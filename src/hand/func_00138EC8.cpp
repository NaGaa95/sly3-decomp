// Sly 2 reference: src/hand/func_00131D68.cpp.
// GNU declaration labels establish canonical Sly 3 symbols without executable assembly.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
class C {
    public: virtual void V1();
    virtual void V2();
    virtual void V3(int a, int b, float g0, float g1);
};
struct O {
    char pad[0x1c];
    float f1c;
    char pad2[0x40 - 0x20];
    float f40;
};
struct S {
    int pad[7];
    C *pc;
    int f20;
    O *po;
};
extern "C" int func_00138938(O *, float *, float *) __asm__("func_00138938");
extern "C" void func_0012F320(S *, int, int) __asm__("func_0012F320");
extern "C" void func_00138EC8(S *p, int a, int b, float g) __asm__("func_00138EC8");
extern "C" void func_00138EC8(S *p, int a, int b, float g) {
    if (p->pc) {
        O *po = p->po;
        float t, dt;
        dt = po->f40;
        t = po->f1c + g * dt;
        func_00138938(po, &t, &dt);
        p->pc->V3(a, b, t, dt);
    }
    else {
        func_0012F320(p, a, b);
    }
}
