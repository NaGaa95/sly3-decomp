// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct X {
    char pad[0x17D0]; void *p17D0; char pad17D4[0x1884 - 0x17D4]; int a1884; struct X *p1888;
    char pad188C[0x189C - 0x188C]; float g189C; float g18A0; float g18A4;
};
extern char D_00344088[];
void func_00250BD8(struct X *p);
void func_001C8970(struct X *p, int n, void *pv, int m);
void func_001F4670(struct X *p, int n);
void *func_00150690(int kind, int a, int id, int b);
void func_00162108(void *p);
void func_0015F490(struct X *p)
{
    func_00250BD8(p);
    func_001C8970(p, 4, D_00344088, 0);
    func_001F4670(p, 1);
    p->p17D0 = func_00150690(3, 0, 0x6FB, -1);
    p->g18A4 = 0.5f;
    p->g189C = 3000.0f;
    p->g18A0 = 4000.0f;
    p->p1888 = p;
    func_00162108(&p->a1884);
}
