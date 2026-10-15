// Reference algorithm: src/hand/func_0014A1B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_00238970(void *p);
void func_00248EC0(void *p);
void func_00252E40(void *p, int n);
extern char D_00474FF0[];
void func_0015E380(char *p)
{
    func_00238970(p);
    func_00248EC0(D_00474FF0);
    func_00252E40(*(void **)(p + 0x10), 0x36);
    *(int *)(p + 0x30) = -1;
    *(int *)(p + 0x40) = -1;
    *(int *)(p + 0x3C) = -1;
}
