// SLY3_CFLAGS: -Os -G0
struct G { char pad[0x4044]; int x4044; char pad2[0x4F48 - 0x4048]; float f4F48; char pad3[0x4F58 - 0x4F4C]; int x4F58; int x4F5C; };
extern struct G D_00475480;
extern struct CLOCK { float t; } g_clock;
struct S { char pad[0x130]; int k130; char pad2[0x190 - 0x134]; int x190; void *x194; int x198; };
int func_0021F410(int id);
int func_00187CD0(void *p);
int func_00282750(struct S *p)
{
    struct G *g;
    if (p->x198)
        return 1;
    g = &D_00475480;
    if (g_clock.t - g->f4F48 > 12.0f)
        return 0;
    switch (p->k130) {
    case 0:
        if (!g->x4044)
            break;
        return 0;
    case 2:
        if (g->x4F58 < g->x4F5C)
            return 0;
        if (g->x4044)
            return 0;
        if (p->x190 != -1 && func_0021F410(p->x190))
            return 0;
        if (!p->x194)
            break;
        if (func_00187CD0(p->x194))
            break;
        return 0;
    case 1:
        if (g->x4044)
            break;
        return 0;
    }
    return 1;
}
