// SLY3_CFLAGS: -Os -G0
// func_00286360: state change (exit actions for state 1, enter actions for -1/0/1/2).
struct VTE { short d; short pad; void (*pf)(void *, ...); };
struct O { int a[3]; struct VTE *vt; };
struct A { int a[3]; struct VTE *vt; char pad[0x130 - 0x10]; int x130; };
struct S {
    int a[3]; struct VTE *vt; char pad[0x130 - 0x10]; int x130; char pad1[0x190 - 0x134]; int x190; float g194; int x198; int pad19C; int x1A0;
    char pad2[0x1AC - 0x1A4]; struct A *x1AC; int x1B0; int x1B4; int x1B8; char pad3[0x2B8 - 0x1BC]; int x2B8; int pad2BC; int x2C0; int pad2C4;
    struct O *x2C8; int pad2CC; int x2D0; int x2D4; int pad2D8; void *x2DC;
};
extern struct CLOCK { float t; } D_0036BB98;
extern char D_0036C700[];
extern char D_00475480[];
void func_001854C8(void *p, int n, struct S *s);
void func_00239CE8(void *p, int n);
void func_00239FE0(void *p, int n);
void func_001F4B00(void *g, int n, void *p);
void func_001C7A00(void *a, int b, int n);
void func_00286630(struct S *p, int n);
void func_00286B00(struct S *p, int n);
void func_00261070(struct O *p, int n);
unsigned int func_00154798(struct A *p, int n);
void func_00262450(struct O *p, int n);
void func_002875C0(struct S *p);
void func_0013E510(struct A *p, int n);
void func_00286360(struct S *p, int state)
{
    if (p->x190 == state)
        return;
    if (p->x190 == 1) {
        func_001854C8(D_0036C700, 0x63, p);
        p->x2C0 = 0;
        if (p->x2DC)
            func_00239CE8(p->x2DC, p->x2D4 ? 0xA8 : 0x92);
        if (p->x2C8) {
            p->x2C8->vt[54].pf((char *)p->x2C8 + p->x2C8->vt[54].d);
            p->x2D0 = -1;
        }
        if (p->x130 != -1)
            func_001F4B00(D_00475480, p->x130, p->x1AC);
    }
    p->x190 = state;
    p->g194 = D_0036BB98.t;
    switch (state) {
    case -1:
        if (p->x1B0) {
            p->x1B0 = 0;
            p->x1B4 = 0;
            p->x1B8 = 0;
        }
        if (p->x1AC)
            p->x1AC->vt[116].pf((char *)p->x1AC + p->x1AC->vt[116].d, 0xD);
        func_001C7A00(p, 0, 0x13);
        p->vt[9].pf((char *)p + p->vt[9].d);
        func_00286630(p, -1);
        func_00286B00(p, -1);
        if (p->x2DC)
            func_00239FE0(p->x2DC, 0x7A);
        if (p->x2C8)
            func_00261070(p->x2C8, 1);
        break;
    case 0:
        func_00286630(p, 0);
        func_00286B00(p, 0);
        if (p->x2DC)
            func_00239CE8(p->x2DC, p->x2D4 ? 0xA8 : 0x92);
        break;
    case 2:
        if (p->x1A0 == 2)
            func_00286B00(p, 1);
        if (p->x198 == 2 || p->x198 == 4)
            func_00286630(p, 3);
        break;
    case 1:
        func_00286630(p, 1);
        func_00286B00(p, 1);
        func_001F4B00(D_00475480, p->x1AC->x130, p);
        p->x2B8 = func_00154798(p->x1AC, 0xD) | 0x410;
        if (p->x2C8) {
            p->x2C8->vt[56].pf((char *)p->x2C8 + p->x2C8->vt[56].d);
            func_00262450(p->x2C8, 0x3CA);
            func_002875C0(p);
        }
        if (p->x2DC)
            func_00239CE8(p->x2DC, p->x2D4 ? 0xA9 : 0x90);
        func_001854C8(D_0036C700, 0x62, p);
        func_0013E510(p->x1AC, 0x12);
        break;
    }
}
