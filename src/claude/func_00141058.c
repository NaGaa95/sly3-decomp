// SLY3_CFLAGS: -Os -G0
#define I(o) (*(int *)((char *)s + (o)))
#define F(o) (*(float *)((char *)s + (o)))
struct SM { float v; int n; float k; };
void func_001F3B50(void *s);
void func_001F43F8(void *s, int n);
int func_001F43F0(void *s);
static inline void InitSm(struct SM *p, float v)
{
    p->v = v;
    p->k = 1.0f;
    p->n = 0;
}
void func_00141058(char *s)
{
    int t;
    func_001F3B50(s);
    F(0x19C) = 1800.0f;
    F(0x1A0) = 1.6f;
    F(0x1A4) = 0.7f;
    F(0x1A8) = 10000.0f;
    F(0x1AC) = 1.22173059f;
    F(0x1B0) = 1.13446414f;
    F(0x1B4) = 0.261799425f;
    F(0x1B8) = 0.52359885f;
    InitSm((struct SM *)(s + 0x1BC), 2.0f);
    InitSm((struct SM *)(s + 0x1C8), 0.8f);
    InitSm((struct SM *)(s + 0x1D4), 0.6f);
    F(0x27C) = 10.0f;
    F(0x280) = 15000.0f;
    func_001F43F8(s, 100);
    F(0x1F0) = 0.25f;
    F(0x1F4) = 4000.0f;
    I(0x1F8) = func_001F43F0(s) / 3 + 1;
    I(0x1FC) = func_001F43F0(s) / 8;
    F(0x200) = 500.0f;
    F(0x2A8) = -150.0f;
    F(0x2AC) = 200.0f;
    I(0x178) = (int)F(0x27C) * 30;
    I(0x2B0) = -1;
    I(0x394) = -1;
    I(0x2B8) = -1;
    I(0x2C0) = -1;
    I(0x2F4) = -1;
    I(0x2A4) = -1;
    I(0x2E8) = -1;
    I(0x3D4) = -1;
    I(0x3D8) = -1;
    I(0x3DC) = -1;
    I(0x3E0) = -1;
    I(0x3E4) = -1;
    I(0x3E8) = -1;
    I(0x3EC) = -1;
    I(0x3F0) = -1;
    I(0x3F4) = -1;
    I(0x3CC) = 1;
    I(0x3D0) = 1;
    F(0x354) = 2.0f;
    I(0x430) = -1;
    t = I(0x3C);
    if ((t ^ 1) & 1)
        *(int *)t |= 8;
    else
        I(0x3C) = t | 8;
}
