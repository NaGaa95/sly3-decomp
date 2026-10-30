// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { void *p0; };
void func_00169E28(struct S *p);
void func_001679E0(void *p, float g);
void func_0016C670(struct S *p)
{
    func_00169E28(p);
    func_001679E0(p->p0, 25.0f);
}
