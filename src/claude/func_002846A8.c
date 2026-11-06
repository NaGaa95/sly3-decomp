// SLY3_CFLAGS: -Os -G0
struct X { char pad[0x50]; int x50; char pad2[0x84 - 0x54]; float f84; char pad3[0xA4 - 0x88]; float fA4; };
struct S { char pad[0x14]; struct X *x14; char pad2[4]; float f1C; char pad3[0x2C - 0x20]; int x2C; };
void func_00284DC8(struct S *p, int state);
void func_002846A8(struct S *p)
{
    struct X *x = p->x14;
    int k = x ? x->x50 : -1;
    if (k == 0 || k == 2) {
        if (k == 2)
            func_00284DC8(p, 5);
        else if (p->x2C <= 0)
            func_00284DC8(p, 2);
        else if (x->f84 != 0.0f && p->f1C < x->f84)
            func_00284DC8(p, 3);
        else if (x->fA4 < p->f1C)
            func_00284DC8(p, 6);
        else
            func_00284DC8(p, 4);
    }
}
