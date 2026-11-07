// Sly 2 counterpart: InitSystemCallTableAddress (decomp src/lib/InitSystemCallTableAddress.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern unsigned int D_0034A6C8[4];
extern unsigned int D_0034A6C0;
extern unsigned int func_002981D8[];
extern unsigned int func_002981A0[];
void func_00298330(unsigned int, unsigned int);
unsigned int func_00298218(unsigned int, unsigned int, unsigned int *);
void func_00298230(void)
{
    unsigned int a, b, ta, tb;
    func_00298330(D_0034A6C8[0], D_0034A6C8[1]);
    func_00298330(D_0034A6C8[2], D_0034A6C8[3]);
    a = func_00298218(0x80000000, 0x80080000, func_002981D8);
    b = func_00298218(0x80000000, 0x80080000, func_002981A0);
    ta = a - 0x20C;
    tb = b - 0x168;
    while (ta != tb) {
        if (ta < tb) {
            a = func_00298218(a + 4, 0x80080000, func_002981D8);
            ta = a - 0x20C;
        } else {
            b = func_00298218(b + 4, 0x80080000, func_002981A0);
            tb = b - 0x168;
        }
    }
    D_0034A6C0 = ta;
}
