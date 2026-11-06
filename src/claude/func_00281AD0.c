// SLY3_CFLAGS: -Os -G0
// Adapted from Sly 2 func_00229EF0 (InitSo-derived init).
typedef unsigned long ulong;
struct S {
    char pad[0x3C]; int f;
    char pad2[0x128 - 0x40]; ulong g;
    int pad3; int a; float b, c;
    char pad4[0x158 - 0x140]; int d;
    char pad5[0x190 - 0x15C]; int e;
    char pad6[0x19C - 0x194]; int h; int i; char pad7[8]; float j;
};
void func_0023AE08(struct S *p);
static inline int FIsPtr(int f) { return !(f & 1); }
void func_00281AD0(struct S *p)
{
    int f;
    func_0023AE08(p);
    f = p->f;
    p->a = 49;
    p->b = 300.0f;
    p->c = 500.0f;
    p->e = -1;
    p->d = -1;
    if (FIsPtr(f)) *(int *)f |= 0xA;
    else p->f = f | 0xA;
    p->h = 255;
    p->i = 255;
    p->g &= ~8L;
    p->j = 5000.0f;
}
