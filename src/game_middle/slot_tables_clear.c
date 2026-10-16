// SLY3_CFLAGS: -Os -G0
struct SlotTables { unsigned char opaque[0x13C]; unsigned char primary[2][0x14]; unsigned char secondary[2][0x14]; };
void *func_00292034(void *destination, int value, unsigned int size);
void func_001A03F8(void *receiver, int clear_secondary)
{
    struct SlotTables *tables = (struct SlotTables *)receiver;
    unsigned int row;
    for (row = 0; row < 2; row++) {
        func_00292034(tables->primary[row], 0, 0x14);
        if (clear_secondary)
            func_00292034(tables->secondary[row], 0, 0x14);
    }
}
