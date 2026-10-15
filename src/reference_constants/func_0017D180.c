// Reference algorithm: src/hand/func_0015DC80.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001C7340(void *p);
void func_001C9118(void *p, int n);
void func_0017D180(char *p)
{
    unsigned int v;
    func_001C7340(p);
    func_001C9118(p, 1);
    v = *(unsigned int *)(p + 0x3C);
    if ((v ^ 1) & 1) *(int *)v |= 0xA;
    else *(unsigned int *)(p + 0x3C) = v | 0xA;
}
