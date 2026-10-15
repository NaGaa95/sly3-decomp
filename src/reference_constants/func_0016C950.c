// Reference algorithm: src/hand/func_00145CD0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00238970(void *p);
void func_0016C950(char *p)
{
    func_00238970(p);
    *(int *)(p + 0x44) = -1;
}
