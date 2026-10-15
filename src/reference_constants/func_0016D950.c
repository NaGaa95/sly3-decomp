// Reference algorithm: src/hand/func_0014B1A0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00131568(void *p);
extern void *D_002DD648;
void func_0016D950(char *p)
{
    func_00131568(p);
    *(int *)(p + 0x3C) = 0x2A;
    *(int *)(p + 0x50) = -1;
}
