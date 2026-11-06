// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { void *p0; char pad[0x20 - 4]; void *p20; };
void func_00169E28(struct S *);
void func_00167960(void *, float);
void func_001679E0(void *, float);
void func_001C7A00(void *, void *, int);
void func_001C8FB0(void *, void *);
void func_00166A40(void *);
void func_0026DEC8(struct S *p)
{
    func_00169E28(p);
    func_00167960(p->p0, 1.4f);
    func_001679E0(p->p0, 10.0f);
    func_001C7A00(p->p0, p->p20, 0);
    func_001C8FB0(p->p0, p->p20);
    func_00166A40(p->p0);
}
