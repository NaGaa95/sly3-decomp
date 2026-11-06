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
struct SO : LO { char pad10[0x218 - 0x10]; int n218; char pad21C[0x248 - 0x21C]; float f248; char pad24C[0x268 - 0x24C]; float f268; };
struct T { union { qword pos; float f[4]; } u; char pad[0x6C - 0x10]; unsigned int n6C; };
extern "C" {
void func_00250690(SO *, T *);
int func_002533C0(SO *, int);
void func_00257478(SO *p, T *t);
}
void func_00257478(SO *p, T *t)
{
    func_00250690(p, t);
    __asm__("" : : "r"(t)); /* zero-insn: raises t's allocation priority (s0) */
    t->u.pos = p->PxfGet()->pos;
    if (p->n218)
        t->u.f[2] = p->f248 + 180.0f;
    else {
        t->u.f[2] += p->f268 + 180.0f;
        t->n6C |= 4;
    }
    if (func_002533C0(p, 0x15) || func_002533C0(p, 0xD))
        t->n6C |= 1;
}
