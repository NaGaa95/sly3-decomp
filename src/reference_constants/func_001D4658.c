// Reference algorithm: src/hand/func_001B0108.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001D45B0(void *receiver);
int func_001D4658(void *receiver)
{
    switch (func_001D45B0(receiver)) {
    case 0x25: case 0x2A: case 0x2B:
        return 1;
    }
    return 0;
}
