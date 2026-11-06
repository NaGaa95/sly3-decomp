// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct VTE { short d; short pad; void (*pf)(void *); };
struct Y { int a[3]; struct VTE *vt; };
struct X { char pad[0x50]; int x50; char pad2[0x94 - 0x54]; int x94; char pad3[0x9C - 0x98]; float f9C; float fA0; };
struct S { char pad[0x14]; struct X *x14; struct Y *x18; float f1C; };
extern "C" {
extern int D_004797C8;
extern char D_00375290[];
int func_002852B0(struct S *p);
void func_00283F20(struct S *p);
void func_001CFE08(void *p);
void func_00262450(struct Y *y, int id);
void func_00261580(struct Y *y, int id, float g);
}
static inline int State(struct X *x)
{
    return x ? x->x50 : -1;
}
extern "C" void func_00283A50(struct S *p)
{
    struct X *x;
    struct Y *y;
    if (func_002852B0(p) && (D_004797C8 & 4)) {
        struct X *x1 = p->x14;
        int f = 0;
        if (!x1 || x1->x50 == 1) {
            f = 1;
        }
        if (!f)
            func_00283F20(p);
    }
    if (D_004797C8 & 0x40)
        func_001CFE08(D_00375290);
    y = p->x18;
    if (!y)
        return;
    if (State(p->x14))
        return;
    y->vt[56].pf((char *)y + y->vt[56].d);
    func_00262450(p->x18, 0x3E3);
    x = p->x14;
    if (x->fA0 != 0.0f) {
        func_00262450(p->x18, 0x3E5);
        return;
    }
    if (x->f9C != 0.0f || x->x94) {
        func_00262450(p->x18, 0x3E4);
        func_00262450(p->x18, 0x3E8);
        func_00261580(p->x18, 0x3E8, p->f1C);
    }
}
