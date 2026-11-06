// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct O { char pad[0x9C]; float g9C; };
struct G { char pad[1]; };
struct S { char pad[0x14]; struct O *po; char pad18[4]; float g1C; char pad20[4]; float g24, g28; int x2C; int x30; };
extern struct G D_0036C700;
extern struct { void *p; } D_004794C4;
void func_00284C28(struct S *p, float g);
float floorf(float);
void func_001854C8(struct G *pg, int k, struct O *po);
void func_00186EE0(void *p, int a, int b, int c);
void func_001871C0(void *p);
void func_00284A90(struct S *p, unsigned int k, int n, float g)
{
    p->x30 = n;
    switch (k) {
    case 0:
        func_00284C28(p, g);
        break;
    case 1:
        p->g24 = g;
        break;
    case 3:
        p->g28 = g;
        break;
    case 2:
        func_00284C28(p, p->g1C + g * p->g28);
        break;
    case 4:
        func_00284C28(p, g / p->po->g9C);
        break;
    case 5:
        func_00284C28(p, p->g1C + g / p->po->g9C);
        break;
    case 6:
        func_00284C28(p, g * 0.001f);
        break;
    case 7:
        func_00284C28(p, floorf(p->g1C * 1000.0f + g + 0.5f) * 0.001f);
        break;
    case 8:
        p->x2C = (int)g;
        break;
    case 9:
        p->x2C--;
        func_001854C8(&D_0036C700, 0x33, p->po);
        if (p->x2C > 0)
            break;
    case 10:
        p->x2C = -1;
        func_00186EE0(D_004794C4.p, p->x30, -1, 0x33);
        break;
    case 11:
    case 12:
        func_001871C0(D_004794C4.p);
        break;
    }
}
