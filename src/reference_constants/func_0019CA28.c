// Reference algorithm: src/hand/func_00185BF8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x1F0]; float g; };
extern float D_00321FD0;
void func_0019B668(struct S *p);
void func_0019CA28(struct S *p)
{
    func_0019B668(p);
    p->g = D_00321FD0;
}
