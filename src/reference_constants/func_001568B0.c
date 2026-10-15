// Reference algorithm: src/hand/func_00144338.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0024F8C0(void *p, int a, int b);
void func_00156928(void *p);
void func_001568B0(char *p, int a, int b)
{
    func_0024F8C0(p, a, b);
    if (b) {
        if (--*(int *)(p + 0x13EC) == 0) func_00156928(p);
    }
}
