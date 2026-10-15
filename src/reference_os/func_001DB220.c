// Sly 2 reference: src/hand/func_001B3040.c; Sly 3 identity remains canonical.
// Original Sly 3 call/data operands bind all external symbols.
// SLY3_CFLAGS: -Os -G0
struct G { char pad[0x110]; int x110; };
extern struct G D_00389AC0;
extern char D_00474FF0[], D_004BC220[];
struct S { int x0; int x4; char x8[0x28]; char x30[0x20]; char x50[0x50]; int xA0; int xA4; };
void func_002910E8(unsigned int m);
void func_00248740(void *p);
void func_0027ED18(void *p);
void func_002910B8(void);
int func_002908F0(void);
void func_002919E8(int n);
void func_00291A10(int n);
int func_00290ED0(int n);
void func_00290E98(int n, int m);
void func_0014EF50(void *p, int cb, void *pv);
void func_001DB220(struct S *p)
{
    func_002910E8(0xFFFFFFFF);
    func_00248740(D_00474FF0);
    func_0027ED18(D_004BC220);
    func_002910B8();
    while (func_002908F0()) ;
    func_002919E8(1);
    func_00291A10(0);
    p->xA0 = func_00290ED0(2);
    p->xA4 = func_00290ED0(0x10);
    func_00290E98(2, 0x400);
    func_00290E98(0x10, 0x400);
    p->x0 = 1;
    p->x4 = -1;
    func_0014EF50(p->x30, 0x28, p->x8);
    func_0014EF50(p->x50, 0x18000, (void *)(D_00389AC0.x110 + 0x80000));
}
