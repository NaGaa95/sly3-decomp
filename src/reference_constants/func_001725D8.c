// Reference algorithm: src/hand/func_00145CD0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001C7340(void *p);
void func_001725D8(char *p)
{
    func_001C7340(p);
    *(int *)(p + 0x48) = -1;
}
