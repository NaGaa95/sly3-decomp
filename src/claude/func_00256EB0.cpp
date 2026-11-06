// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Cf. Sly 2 src/hand/func_0020B2A8.c.
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
struct A;
struct S { char pad[0x10F0]; int k; A *pa; int x10F8; int n10FC; LO *p1100; };
extern "C" {
int func_0013B500(A *pa, int n);
qword func_00250600(S *p);
void func_0022EA88(A *pa, qword q, int a, int b, int c, int d, int *pn);
void func_0024F3B8(S *p, A *pa, int n);
void func_002495E0(A *pa, S *p);
void func_00256EB0(S *p, A *pa, int n);
}
void func_00256EB0(S *p, A *pa, int n)
{
    p->pa = pa;
    p->n10FC = n;
    if (func_0013B500(pa, 0xA)) {
        p->k = 1;
        func_0022EA88(p->pa, p->p1100->PxfGet()->pos, 0, 0, 0, 0, &p->x10F8);
        func_0024F3B8(p, p->pa, 1);
    } else if (func_0013B500(p->pa, 0xC)) {
        p->k = 0;
        func_0022EA88(p->pa, func_00250600(p), 0, 0, 0, 0, &p->x10F8);
        func_0024F3B8(p, p->pa, 1);
    } else if (func_0013B500(p->pa, 0x25)) {
        p->k = 2;
        func_0024F3B8(p, p->pa, 1);
        func_002495E0(p->pa, p);
    } else {
        p->pa = 0;
    }
}
