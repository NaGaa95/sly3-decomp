// Sly 2 counterpart: receiveDataFromIPU (decomp src/lib/receiveDataFromIPU.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
int func_002980D0(void);
int func_00298120(void);
void func_002B1EA8(unsigned int addr, int size)
{
    int r = func_002980D0();
    if ((addr >> 28) == 7) {
        addr &= 0x0FFFFFFF;
        addr |= 0x80000000;
    } else
        addr &= 0x0FFFFFFF;
    *(volatile unsigned int *)0x1000B010 = addr;
    *(volatile unsigned int *)0x1000B020 = size >> 4;
    *(volatile unsigned int *)0x1000B000 = 0x100;
    if (r) func_00298120();
}
