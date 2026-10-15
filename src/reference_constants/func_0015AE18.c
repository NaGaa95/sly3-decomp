// Reference algorithm: src/hand/func_00147EE8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0011B028(void *p, int a);
void func_0011AF60(void *p, int a);
struct X { char pad[0x3DE8]; char sub[0x3DF4 - 0x3DE8]; int n; };
void func_0015AE18(struct X *p, int a)
{
    func_0011B028(p->sub, a);
    if (p->n == 0) p->n = a;
    func_0011AF60(p->sub, a);
}
