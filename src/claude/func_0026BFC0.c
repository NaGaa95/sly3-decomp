// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
union FI { int n; float f; };
struct S {
    char pad[0x1B0]; int n1B0; int pad1B4; union FI u1B8;
    char pad1BC[0x21C - 0x1BC]; float f21C; int n220; float f224;
    char pad228[0x27C - 0x228]; void *p27C; char pad280[0x2B0 - 0x280]; char a2B0[1];
};
void func_001F3C48(struct S *);
int func_001F43F0(struct S *);
void func_001F43D0(struct S *, int);
int func_001F43C8(struct S *);
void func_00137588(void *, struct S *, int, void *, float, float);
void func_0026CD30(struct S *, int);
void func_0026BFC0(struct S *p)
{
    func_001F3C48(p);
    func_001F43D0(p, func_001F43F0(p));
    p->n1B0 = func_001F43C8(p);
    p->u1B8.n = 0;
    p->n220 = 0;
    p->f21C = p->f224;
    func_00137588(p->p27C, p, 9, p->a2B0, p->u1B8.f, 1.0f);
    func_0026CD30(p, 0);
}
