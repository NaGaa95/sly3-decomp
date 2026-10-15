// Reference algorithm: src/hand/func_00156CC8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0028FD70(void *p);
void func_001C9118(void *p, int n);
void func_00173F30(char *p)
{
    unsigned int v;
    func_0028FD70(p);
    func_001C9118(p, 0);
    v = *(unsigned int *)(p + 0x3C);
    if ((v ^ 1) & 1) *(int *)v |= 2;
    else *(unsigned int *)(p + 0x3C) = v | 2;
}
