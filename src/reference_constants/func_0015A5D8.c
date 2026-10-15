// Reference algorithm: src/hand/func_001477B0.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_0015A5D8(char *p)
{
    switch (*(int *)(p + 0x130)) {
    case 2:
    case 3:
        return 0;
    }
    return 1;
}
