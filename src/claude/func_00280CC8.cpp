// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
union VU { qword q; float f[4]; };
struct G { char pad[0x3E04]; int grf; char pad1[0x3EB8 - 0x3E08]; int c; int a[(0x3ED0 - 0x3EBC) / 4]; qword q; };
struct S { char pad[0x2C]; unsigned char b2C; char pad1[0x70 - 0x2D]; char a70[0x104 - 0x70]; float f104; int pad2; int x10C;
           char pad3[0x170 - 0x110]; int x170; };
extern "C" {
extern G D_00475480;
void func_0023CBE0(void);
void func_0018E800(void *p, qword q, void *pm, int k, float a, float b);
}
static inline int FIsZero(qword v)
{
    int f;
    __asm__("vadd.xyzw $vf0, %1, %1\n\tvnop\n\tvnop\n\tvnop\n\tvnop\n\tcfc2.ni %0, $vi17" : "=r"(f) : "j"(v));
    return ((f & 0xF) ^ 0xF) == 0;
}
extern "C" void func_00280CC8(S *p)
{
    G *g = &D_00475480;
    if (!(p->b2C & g->grf))
        return;
    func_0023CBE0();
    VU v;
    v.q = g->q;
    if (p->x170) {
        for (int i = 0; i < D_00475480.c; i++) {
            if (v.f[i] != 0.0f && D_00475480.a[i] != p->x170)
                v.f[i] = 0.0f;
        }
    }
    if (!FIsZero(v.q))
        func_0018E800(p->a70, v.q, 0, p->x10C, p->f104, p->f104);
    __asm__("" : : "r"(p)); // keeps p ahead of g in global-alloc priority
}
