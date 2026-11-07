// Sly 2 counterpart: deci2Putchar (decomp src/lib/deci2Putchar.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern int D_0034A60C;
extern char D_004C96D0[];
void func_002996C0(char *);
void func_00294438(int c)
{
    if (D_0034A60C >= 0x7E) {
        D_0034A60C = 0;
        D_004C96D0[0x7F] = 0;
        func_002996C0(D_004C96D0);
    }
    if (c == '\n') {
        D_004C96D0[D_0034A60C] = c;
        D_004C96D0[D_0034A60C + 1] = 0;
        D_0034A60C = 0;
        func_002996C0(D_004C96D0);
    } else {
        D_004C96D0[D_0034A60C++] = c;
    }
}
