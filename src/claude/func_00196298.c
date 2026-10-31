// SLY3_CFLAGS: -Os -G0
// New Sly 3 code (GS display/frame setup for a resolution; cf. Sly 2 func_001700D0). Display-env structs are
// int-based so the bitfields use lw/sw; the dispfb read is done before the pmode updates (aliasing order).
typedef unsigned long u_long;
struct RES { int w; int h; int flags; };
struct DISPENV {
    union { int w; unsigned char b[4]; } pmode; int pmode_hi;
    int smode2[2];
    struct { unsigned int fbp : 9; unsigned int fbw : 6; unsigned int psm : 5; unsigned int p0 : 12; unsigned int hi; } dispfb;
    struct { unsigned int dx : 12; unsigned int dy : 11; unsigned int magh : 4; unsigned int magv : 2; unsigned int p0 : 3; unsigned int dw : 12; unsigned int dh : 11; unsigned int p1 : 9; } display;
    int bgcolor[2];
};
struct FB { u_long fbp : 9; u_long rest : 55; };
struct GSG { struct FB frame[5]; struct DISPENV disp[2]; };
struct SELF {
    int pad0; struct RES res; int n10; float g14; float g18; int n1C; int n20; float g24; float g28; int pad2C;
    u_long frame0; u_long frame1; u_long zbuf; u_long xyoffset; u_long scissor;
};
struct B { int a[12]; };
extern struct GSG D_0036DC10;
extern int D_0036E680[4];
extern int D_0036DCB0[], D_0036DCAC[], D_0036DF90[], D_0036DF80[];
extern void (*D_00345090[2])(void);
int func_00196260(struct SELF *p, struct RES *pres);
void func_00196818(struct SELF *p, float a, float b);
int func_002BC640(struct SELF *p, int w);
int func_002BC648(struct SELF *p, int h);
int func_002BC668(struct SELF *p, int x);
int func_002BC670(struct SELF *p, int y);
void func_0029EFB8(short mode, short inter, short omode, short ffmode);
void func_0029F270(struct DISPENV *p, short psm, short w, short h, short dx, short dy);
void func_00196768(struct SELF *p, struct DISPENV *pd, float a, float b);
void func_0018C750(struct B *pb);
void func_00174538(struct B *pb, int n, int *p);
void func_00174550(struct B *pb, int *p, int n);
void func_00195808(int *pc, int *p, int n, struct B *pb);
void func_00196A10(void);
void func_00196298(struct SELF *p, struct RES *pres)
{
    int i;
    unsigned int j;
    struct B b;
    int c;
    if (func_00196260(p, pres)) {
        func_00196818(p, p->g24, p->g28);
        return;
    }
    p->res = *pres;
    p->n10 = (p->res.flags & 3) ? 1 : 2;
    p->g14 = 4055.04f / (float)func_002BC640(p, p->res.w);
    p->g18 = 4055.04f / (float)func_002BC648(p, p->res.h);
    p->n1C = func_002BC640(p, p->res.w) * func_002BC648(p, p->res.h) / 64;
    p->n20 = func_002BC640(p, p->res.w) * ((func_002BC648(p, p->res.h) + 63) & ~63) / 128;
    {
        int w = p->res.w, h = p->res.h;
        D_0036E680[0] = 0;
        D_0036E680[1] = 0;
        D_0036E680[2] = w;
        D_0036E680[3] = h;
    }
    func_0029EFB8(0, 1, 2, (p->res.flags & 3) == 0);
    p->frame0 = (u_long)(func_002BC640(p, p->res.w) / 64) << 16;
    {
        int fbp = p->n1C / 32;
        int z;
        p->frame1 = (u_long)fbp | ((u_long)(func_002BC640(p, p->res.w) / 64) << 16);
        z = p->n1C * 2;
        p->zbuf = (u_long)(z / 32) | ((u_long)0x30 << 24);
    }
    p->xyoffset = (u_long)func_002BC668(p, 0x800 - func_002BC640(p, p->res.w) / 2) | ((u_long)func_002BC670(p, 0x800 - func_002BC648(p, p->res.h) / 2) << 32);
    p->scissor = ((u_long)(func_002BC640(p, p->res.w) - 1) << 16) | ((u_long)(func_002BC648(p, p->res.h) - 1) << 48);
    for (i = 0; i < 2; i++) {
        struct DISPENV *pd = &D_0036DC10.disp[i];
        func_0029F270(pd, 0, func_002BC640(p, p->res.w), func_002BC648(p, p->res.h), 0, 0);
        if (func_002BC640(p, p->res.w) == 0x180) {
            pd->display.magh = 5;
            pd->display.dw = func_002BC640(p, p->res.w) * (pd->display.magh + 1) - 1;
            pd->display.dx = 0x2F0;
        }
        func_00196768(p, pd, p->g24, p->g28);
        pd->dispfb.fbp = D_0036DC10.frame[i].fbp;
        pd->pmode.w &= ~1;
        pd->pmode.b[1] = 0x80;
        pd->pmode.w |= 0x20;
    }
    func_0018C750(&b);
    func_00174538(&b, 0x2D, D_0036DCB0);
    c = 0x80000000;
    func_00195808(&c, D_0036E680, 3, &b);
    func_00174550(&b, D_0036DCAC, 0);
    func_00174538(&b, 0x2D, D_0036DF90);
    c = 0x80000000;
    func_00195808(&c, D_0036E680, 2, &b);
    func_00174550(&b, D_0036DF80, 0);
    func_00196A10();
    for (j = 0; j < 2; j++)
        D_00345090[j]();
}
