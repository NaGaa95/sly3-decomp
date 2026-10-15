// Reference algorithm: src/hand/func_001471C0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0023AE08(void *p);
void func_001C9118(void *p, int n);
void func_00159DF0(char *p)
{
    unsigned int v;
    func_0023AE08(p);
    *(int *)(p + 0x130) = -1;
    func_001C9118(p, 1);
    v = *(unsigned int *)(p + 0x3C);
    if ((v ^ 1) & 1) *(int *)v |= 0x202;
    else *(unsigned int *)(p + 0x3C) = v | 0x202;
}
