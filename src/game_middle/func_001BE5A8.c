// SLY3_CFLAGS: -Os -G0 -ffast-math
// State change for a two-part presentation object (same routine as Sly 2 func_0019D660, jump-table version).
struct O;
typedef struct { short d; short pad; void (*pfn)(void *); } VTE;
struct O { char pad[0xC]; VTE *vt; char pad2[0x48 - 0x10]; int x48; };
struct B { char pad[0x1BC]; float x1BC; };
struct A { struct B *x0; char pad[0x14]; int x18; char pad2[0x18]; float x34; };
struct S { struct A *x0; int x4; struct O *x8; int xC; struct O *x10; void *x14; };
extern char D_0036C700[];
extern char D_004BC220[];
void func_001BE918(struct S *p);
void func_001BE3D0(struct A *a);
void func_001854C8(void *p, int n, int m);
void *func_002459F8(int n);
void func_00244F08(void *p, int n);
void func_00262450(struct O *p, int n);
void func_00261580(struct O *p, int n, float f);
void func_0027ED18(void *p);
void func_0024C6D8(void *p, int n);
void func_00261070(struct O *p, int n);
void func_00261050(struct O *p, int n);
void func_001BE5A8(struct S *p, int st)
{
    int old;
    if (p->x4 == st) return;
    if (p->x4 == -1) func_001BE918(p);
    old = p->x4;
    p->x4 = st;
    switch (st) {
    case 0:
        if (p->x0->x18 == 1) func_001854C8(D_0036C700, 7, 0);
        else func_001854C8(D_0036C700, 2, 0);
        func_00244F08(func_002459F8(0x32), 0);
        if (p->x8) {
            p->x8->vt[56].pfn((char *)p->x8 + p->x8->vt[56].d);
            func_00262450(p->x8, 0x3CD);
            func_00262450(p->x8, 0x3CC);
            func_00261580(p->x8, 0x3CD, (p->x0->x0->x1BC + 3.1415927f) * 0.15915494f);
            func_00261580(p->x8, 0x3CC, p->x0->x34);
        }
        if (p->x0->x18 == 1) {
            func_0027ED18(D_004BC220);
            if (p->x10) {
                p->x10->vt[56].pfn((char *)p->x10 + p->x10->vt[56].d);
                func_00262450(p->x10, 0x3CF);
            }
        }
        if (p->x14) func_0024C6D8(p->x14, 0);
        break;
    case 1:
        if (p->x0->x18 == 1) func_00262450(p->x10, 0x3CF);
        break;
    case 2:
        func_00262450(p->x10, 0x3D0);
        break;
    case 3:
        func_001BE3D0(p->x0);
        break;
    case 4:
        func_00262450(p->x10, 0x3D1);
        break;
    case 5:
        if (p->x0->x18 == 1) func_001854C8(D_0036C700, 8, 0);
        else func_001854C8(D_0036C700, 3, 0);
        func_00244F08(func_002459F8(0x33), 0);
        if (p->x8) p->x8->vt[54].pfn((char *)p->x8 + p->x8->vt[54].d);
        if (p->x10) p->x10->vt[54].pfn((char *)p->x10 + p->x10->vt[54].d);
        if (p->x14) func_0024C6D8(p->x14, 10);
        break;
    case -1:
        if (old != 5) {
            if (p->x0->x18 == 1) func_001854C8(D_0036C700, 8, 0);
            else func_001854C8(D_0036C700, 3, 0);
        }
        if (p->x8 && p->x8->x48) {
            func_00261070(p->x8, 1);
            func_00261050(p->x8, 1);
        }
        if (p->x10 && p->x10->x48) {
            func_00261070(p->x10, 1);
            func_00261050(p->x10, 1);
        }
        if (p->x14) func_0024C6D8(p->x14, -1);
        break;
    }
}
