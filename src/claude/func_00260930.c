// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Post-load: centre a screen element on the 4096x4096 GS area (cf. Sly 2 src/hand/func_002123C8.c).
struct VT { char pad[0x1C0]; short d; short pd; void (*pf)(void *); };
struct S {
    char pad[0xC]; struct VT *pvt; char pad10[0x3C - 0x10]; unsigned int x3C; char pad40[0x5D - 0x40]; unsigned char x5D;
    char pad5e[0x84 - 0x5E]; int x84; int x88; float x8C; float x90; char pad94[4]; int x98; char pad9c[0xB8 - 0x9C]; struct S *xB8;
};
struct D { int x0; int w; int h; };
extern struct D D_0036DBE0;
void func_001C7DC8(struct S *p);
int func_002BC640(struct D *, int);
int func_002BC648(struct D *, int);
void func_001C9118(struct S *p, int);
void func_00260930(struct S *p)
{
    unsigned int v;
    float a, b;
    func_001C7DC8(p);
    p->xB8 = p;
    p->x98 = -1;
    a = (float)func_002BC640(&D_0036DBE0, p->x84 * D_0036DBE0.w / 640);
    b = (float)func_002BC648(&D_0036DBE0, p->x88 * D_0036DBE0.h / 480);
    p->x8C = 2048.0f - a * 0.5f;
    p->x90 = 2048.0f - b * 0.5f;
    if (p->x5D)
        p->pvt->pf((char *)p + p->pvt->d);
    func_001C9118(p, 1);
    v = p->x3C;
    if ((v ^ 1) & 1) *(unsigned int *)v |= 0x202;
    else p->x3C = v | 0x202;
}
