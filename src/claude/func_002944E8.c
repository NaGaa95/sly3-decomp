// Sly 2 counterpart: serialPutchar (decomp src/lib/serialPutchar.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
void func_00294400(int c);
void func_002944E8(int c)
{
    if (c == '\n') {
        func_00294400('\r');
        func_00294400('\n');
        return;
    }
    func_00294400(c);
}
