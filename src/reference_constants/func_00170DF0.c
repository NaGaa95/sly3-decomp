// Reference algorithm: src/hand/func_00145CD0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0023AE08(void *p);
void func_00170DF0(char *p)
{
    func_0023AE08(p);
    *(int *)(p + 0x130) = -1;
}
