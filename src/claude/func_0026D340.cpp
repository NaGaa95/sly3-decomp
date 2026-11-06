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
    virtual void Teleport(qword v);
    virtual void v34();
    virtual XF *PxfGet();
};
struct D4 { char pad[8]; float f8; };
struct SO : LO { char pad10[0xD4 - 0x10]; D4 *pD4; char padD8[0x1C0 - 0xD8]; union { qword q; float f[4]; } v1C0; };
static inline float X(qword q) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(q)); return f; }
static inline float Y(qword q) { float f; __asm__("prot3w %0, %1" : "=r"(f) : "r"(q)); return f; }
static inline float Z(qword q) { float f; __asm__("pextuw %0, $0, %1" : "=r"(f) : "r"(q)); return f; }
static inline qword QwFromXyz(float x, float y, float z)
{
    qword q;
    int t;
    __asm__("mfc1 %0, %2\n\tmfc1 %1, %3\n\tpextlw %0, %1, %0\n\tmfc1 %1, %4\n\tpcpyld %0, %1, %0"
            : "=&r"(q), "=&r"(t) : "f"(x), "f"(y), "f"(z));
    return q;
}
struct VECTOR4 { float x,y,z,w; } __attribute__((aligned(16)));
extern "C" {
int func_0026D228(qword pos, float r, SO *self);
void func_0026CD30(SO *, int);
void func_0026D340(SO *p);
}
void func_0026D340(SO *p)
{
    qword pos = p->PxfGet()->pos;
    VECTOR4 v; qword vq = QwFromXyz(X(pos), Y(pos), Z(pos) + 400.0f); float r = p->pD4->f8;
    *(qword*)&v = vq;
    if (!func_0026D228(vq, r, p)) {
        float *pv = p->v1C0.f;
        p->v1C0.q = p->PxfGet()->pos;
        pv[2] -= 10.0f;
        if (!func_0026D228(p->v1C0.q, p->pD4->f8, p)) {
            p->Teleport(vq);
            func_0026CD30(p, 2);
        }
    }
}
