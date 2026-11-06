// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Cf. Sly 2 src/hand/func_00143D20.c: will the object hit the ground within dt?
typedef int qword __attribute__((mode(TI)));
static __inline__ float GetZ(qword q) { float z; __asm__("pextuw %0,$0,%1" : "=r"(z) : "r"(q)); return z; }
struct XF { char pad[0x30]; qword pos; };
struct G { char pad[0x88]; float g; };
struct LO {
    int x0, x4, x8;
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
    virtual qword VGet();
};
struct SO : LO {
    char pad[0xD8 - 0x10]; G *pg; char pad2[0x268 - 0xDC]; float z;
};
extern "C" int func_00198D78(qword *ppos, int a, int b, float f, float g);
extern "C" int func_002502F0(SO *p, float dt);
int func_002502F0(SO *p, float dt)
{
    qword pos;
    float h = p->z;
    h += dt * GetZ(p->VGet());
    h += 0.5f * dt * dt * p->pg->g;
    if (h > 0.0f)
        return 0;
    pos = p->PxfGet()->pos;
    return func_00198D78(&pos, 1, 0, 0.0f, h);
}
