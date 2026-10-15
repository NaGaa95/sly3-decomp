// Test the original Sly 3 state enumeration with an integer input; all 22 original switch-table destinations are checked after relocation.
// Reference algorithm: src/hand/func_001894F8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
int func_0028EFD8(int state)
{
    switch (state) {
    case 1: case 2: case 3: case 8: case 9: case 10: case 11: case 12: case 13: case 18: case 19: case 20: case 21: case 22:
        return 1;
    }
    return 0;
}
