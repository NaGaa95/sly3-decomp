// SLY3_CFLAGS: -Os -G0
struct SlotTables { unsigned char opaque[0x13C]; int primary[2][5]; int secondary[2][5]; };
int func_001A04E0(void *receiver, unsigned int row, int column, int secondary)
{
    struct SlotTables *tables = (struct SlotTables *)receiver;
    if (column == -1)
        return 0;
    if (column >= 5)
        return 0;
    if (row >= 2)
        return 0;
    if (secondary != 0) {
        return tables->secondary[row][column];
    } else {
        return tables->primary[row][column];
    }
}
