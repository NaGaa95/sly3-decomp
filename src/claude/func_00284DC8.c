// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct O { char pad[0x84]; float g84; };
struct G { char pad[0x14A4]; int x14A4; };
struct S { char pad[0x14]; struct O *po; char pad18[4]; float g1C; char pad20[0x7CD4 - 0x20]; int k; float t; };
struct CLOCK { float t; float dt; };
extern struct CLOCK g_clock;
extern struct G D_0036C700;
void func_00283B98(struct S *p, int k);
void func_001854C8(struct G *pg, int k, struct O *po);
void func_00283550(struct O *po);
void func_00284DC8(struct S *p, unsigned int k)
{
    if (p->k == k)
        return;
    switch (k) {
    case 0:
        D_0036C700.x14A4 = -1;
        func_00283B98(p, 0);
        func_001854C8(&D_0036C700, 0x39, p->po);
        break;
    case 1:
        func_001854C8(&D_0036C700, 0x2C, p->po);
        break;
    case 2:
        func_001854C8(&D_0036C700, 0x34, p->po);
        break;
    case 3:
        func_001854C8(&D_0036C700, 0x35, p->po);
        break;
    case 4:
        func_00283550(p->po);
        func_001854C8(&D_0036C700, 0x36, p->po);
        break;
    case 6:
        if (p->po->g84 <= p->g1C)
            func_00283550(p->po);
        func_001854C8(&D_0036C700, 0x38, p->po);
        break;
    case 5:
        func_001854C8(&D_0036C700, 0x37, p->po);
        break;
    }
    p->k = k;
    p->t = g_clock.t;
}
