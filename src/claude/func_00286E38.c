// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct VTE { short d; short pad; int (*pf)(void *, ...); };
struct T { char pad[0x14]; int x14; };
struct O { char pad[0x1E8]; struct T *x1E8; };
struct Z { char pad[0x14]; struct O *po; char pad18[8]; int x20, x24, x28; char pad2c[0x50 - 0x2C]; int x50; };
struct S { int a[3]; struct VTE *vt; char pad[0x14 - 0x10]; int x14; char pad18[0x130 - 0x18]; int x130; char pad134[0x190 - 0x134];
           int x190; char pad194[0x1A8 - 0x194]; float g1A8; char pad1ac[0x204 - 0x1AC]; struct O *x204; char pad208[0x2CC - 0x208]; int x2CC; };
struct V { char pad[0x11C0]; };
extern float D_0032973C;
extern struct V D_0036E740[];
int func_0013B500(void *pj, int k);
void func_001F4DD8(struct S *p, struct O *po, int k, float g);
void func_001F43D0(struct S *p, int n);
int func_001F43C8(struct S *p);
void func_001A9058(struct V *pv, int k, float g);
void *func_001F4A80(struct S *p);
void func_00167D38(void *p, int k);
void func_00286B00(struct S *p, int k);
int func_00286E38(struct S *p, struct Z *z)
{
    if (p->vt[80].pf((char *)p + p->vt[80].d, z->x20))
        return 0;
    if (!(z->x50 & 2))
        return 0;
    if (z->po == p->x204)
        return 0;
    if (func_0013B500(z->po, 0x59) && z->po->x1E8->x14 == p->x14)
        return 0;
    if (p->x190 == -1)
        return 0;
    func_001F4DD8(p, z->po, z->x20, D_0032973C);
    if (z->x28 || (z->x20 & 0x6000) || p->x190 != 1) {
        func_001F43D0(p, 0);
        p->x2CC = 0;
    } else {
        func_001F43D0(p, func_001F43C8(p) - z->x24);
    }
    if (p->x190 == 1) {
        func_001A9058(&D_0036E740[p->x130], 4, 0.75f);
        func_00167D38(func_001F4A80(p), 0);
    }
    if (func_001F43C8(p) > 0)
        p->g1A8 = 2.0f;
    else
        func_00286B00(p, 3);
    return 1;
}
