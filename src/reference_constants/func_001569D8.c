// Reference algorithm: src/hand/func_00142830.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0024E3A8(void *p, void *transform);
void func_001569D8(char *p, void *transform)
{
    func_0024E3A8(p, transform);
    *(float *)(p + 0x110C) = *(float *)(p + 0x1BC);
}
