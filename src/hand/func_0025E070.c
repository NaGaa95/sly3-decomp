// Return the indexed 64-byte record in the static global array, or null for the absent index.
// Reference algorithm: src/hand/func_00210990.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct E { char pad[0x40]; };
extern struct E D_002EDFD8[];
struct E *func_0025E070(int i)
{
    if (i == -1)
        return 0;
    return &D_002EDFD8[i];
}
