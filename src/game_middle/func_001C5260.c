// SLY3_CFLAGS: -Os -G0 -ffast-math
struct S {
    char pad00[0x3C]; int x3C;
    char pad40[0xD0 - 0x40]; int xD0; int xD4;
    char padD8[0x108 - 0xD8]; int x108;
    char pad10C[0x144 - 0x10C]; float x144; float x148;
    char pad14C[0x154 - 0x14C]; float x154; float x158;
};
void func_0028FD70(struct S *s);
void func_001C9118(struct S *s, int n);
void func_001C5260(struct S *s)
{
    int v;
    func_0028FD70(s);
    s->xD0 = 0;
    s->xD4 = -1; s->x108 = -1;
    s->x154 = 200.0f;
    s->x158 = 2000.0f;
    s->x144 = 240.0f;
    s->x148 = -1.0f;
    func_001C9118(s, 1);
    v = s->x3C;
    if ((v ^ 1) & 1) *(int *)v &= ~0x40;
    else s->x3C = v & ~0x40;
}
