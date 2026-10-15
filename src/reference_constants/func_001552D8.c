// Reference algorithm: src/hand/func_00142830.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00155270(void *p, int a, int b);
void func_001552D8(char *p, int a, int b)
{
    func_00155270(p, a, b);
    *(int *)(p + 0x11D8) = 1;
}
