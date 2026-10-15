// Reference algorithm: src/hand/func_0021BBD0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x140]; int f; };
void func_0023BAB8(struct S *p);
void func_0026E150(struct S *p);
void func_0026E118(struct S *p)
{
    func_0023BAB8(p);
    if (p->f)
        func_0026E150(p);
}
