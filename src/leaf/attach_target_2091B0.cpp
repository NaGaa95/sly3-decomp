// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
struct MAT4 { qword a[4]; };
struct Q { char pad[0xA0]; void *xA0; };
class LOB {
public:
    int a[3];
    virtual void V1();
    virtual void V2();
    virtual void V3();
    virtual void V4();
    virtual void V5();
    virtual void V6();
    virtual void V7();
    virtual void V8();
    virtual void V9();
    virtual void V10(void *a, void *m, int b);
    virtual void V11();
    virtual void V12();
    virtual void V13();
    virtual void V14();
    virtual void V15();
    virtual void V16();
    virtual void V17();
    virtual void V18();
    virtual void V19();
    virtual void V20();
    virtual void V21();
    virtual void V22();
    virtual void V23();
    virtual void V24();
    virtual void V25();
    virtual void V26();
    virtual void V27();
    virtual void V28();
    virtual void V29();
    virtual void V30();
    virtual void V31();
    virtual void V32();
    virtual void V33();
    virtual void V34();
    virtual void V35();
    virtual MAT4 *V36();
    virtual void *V37(MAT4 *pm);
    virtual void V38();
    virtual void V39();
    virtual void V40();
    virtual void V41();
    virtual void V42();
    virtual void V43(int n, MAT4 *pm);
};
class LO : public LOB {
public:
    char p0[0x48 - 0x10];
    Q *x48;
    Q *x4C;
    char p1[0xD8 - 0x50];
    int xD8;
};
struct S { void *x0; char p0[0x34 - 4]; LO *x34; char p1[0x94 - 0x38]; int x94; int x98; int x9C; LO *xA0; };
extern "C" {
void func_001309D8(int *p);
LO *func_00208AA0(void *pw, LO *po);
void func_0011D558(MAT4 *pd, MAT4 *pa, MAT4 *pb);
void func_0023EBF8(LO *po, int n);
void func_0023EC98(LO *po, int n);
qword func_0028B388(void *a, void *b);
int func_00130078(LO *p, Q *q, int a, int b, int c, qword d);
void func_00241338(LO *po, float g);
void func_002091B0(S *p, LO *po);
MAT4 func_001C9708(int n, LO *po, MAT4 *pm);
MAT4 func_0011D768(MAT4 m);
}
extern "C" void func_002091B0(S *p, LO *po)
{
    MAT4 buf;
    MAT4 m;
    if (po == p->xA0) return;
    func_001309D8(&p->x94);
    func_001309D8(&p->x98);
    func_001309D8(&p->x9C);
    void *v = p->x34->V37(&buf);
    po->V10(p->x0, v, 0);
    m = *p->x34->V36();
    LO *r = func_00208AA0(p->x0, po);
    if (r) {
        MAT4 u;
        MAT4 t = func_001C9708(0, po, r->V36());
        u = t;
        MAT4 *pm = &m;
        MAT4 w = func_0011D768(u);
        func_0011D558(&t, pm, &w);
        m = t;
    }
    po->V43(0, &m);
    if (po->xD8) {
        func_0023EBF8(po, 1);
        func_0023EC98(po, 1);
    }
    Q *q = po->x48;
    p->x98 = func_00130078(po, q, 5, 0, 2, func_0028B388(q, q));
    q = po->x4C;
    p->x9C = func_00130078(po, q, 5, 0, 2, func_0028B388(q, q));
    func_00241338(po, 0.25f);
    p->xA0 = po;
}
