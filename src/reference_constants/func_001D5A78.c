// Reference algorithm: src/hand/func_001B0C68.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x1A4]; int x; };
void func_0023BBE0(struct S *p);
void func_00137588(int a, int b, int c, void *d, float f, float g);
void func_001D5A78(struct S *p)
{
    func_0023BBE0(p);
    func_00137588(0, 0, 0, &p->x, 0.0f, 0.0f);
}
