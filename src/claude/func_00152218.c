// SLY3_CFLAGS: -Os -G0
#define I(o) (*(int *)((char *)s + (o)))
#define F(o) (*(float *)((char *)s + (o)))
#define P(o) (*(void **)((char *)s + (o)))
extern char D_0036E6D0[];
void func_0024D8A8(void *s);
void func_001B7190(void *p, void *s);
void func_001B26B8(void *p, void *s);
void func_001C0370(void *p, void *s);
void func_001C2018(void *p, void *s);
void func_001BDA30(void *p, void *s);
void func_00271E38(void *p, void *s);
void func_001BEE28(void *p, void *s);
void func_00156FB8(void *p, void *s);
void func_00139B70(void *p, void *s);
void func_001F4460(void *s, int n);
void func_00156A08(void *s, int n);
void func_001F43F8(void *s, int n);
void func_00152218(char *s)
{
    func_0024D8A8(s);
    func_001B7190(s + 0x320, s);
    func_001B26B8(s + 0x500, s);
    func_001C0370(s + 0xA20, s);
    func_001C2018(s + 0xE40, s);
    func_001BDA30(s + 0xF60, s);
    func_00271E38(s + 0x1290, s);
    func_001BEE28(s + 0x1010, s);
    func_00156FB8(s + 0x10A0, s);
    func_00139B70(s + 0x10D0, s);
    I(0x11C8) = 1;
    I(0x11C4) = -1;
    I(0x11BC) = -1;
    I(0x13E0) = 1;
    F(0x1148) = 20.0f;
    F(0x11B0) = 1.0f;
    F(0x1158) = 125.0f;
    F(0x11AC) = 1.0f;
    F(0x1208) = 1.5f;
    F(0x120C) = 2.5f;
    F(0x1210) = 3.0f;
    F(0x1214) = 5.0f;
    F(0x1130) = 100.0f;
    func_001F4460(s, 100);
    I(0x1404) = -1;
    I(0x11A0) = -1;
    P(0x1440) = D_0036E6D0;
    func_00156A08(s, 0);
    func_001F43F8(s, 0x28);
    I(0x2F4) = 1;
    I(0x304) = -1;
    I(0x300) = -1;
    I(0x310) = 0xFF;
    F(0x2F8) = 3.402823466e+38f;
}

/* Next .rodata item of the original unit (read by func_00152A48). */
const float D_00320548[2] = { 1500.0f, 0.0f };
