// Reference algorithm: src/hand/func_00140D00.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_0023E108(void *p);
void func_001BAC20(void *p);
void func_001B56F0(void *p);
void func_001BF990(void *p);
void func_00153498(char *p)
{
    func_0023E108(p);
    if (*(int *)(p + 0x33C) != -1) func_001BAC20(p + 0x320);
    if (*(int *)(p + 0x50C) != -1) func_001B56F0(p + 0x500);
    if (*(int *)(p + 0x1014) != -1) func_001BF990(p + 0x1010);
}
