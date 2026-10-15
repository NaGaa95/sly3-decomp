// Reference algorithm: src/hand/func_00185BF8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0xC0]; float g; };
extern float D_002A5690;
void func_001D8008(struct S *p);
void func_001D9010(struct S *p)
{
    func_001D8008(p);
    p->g = 1.0f;
}
