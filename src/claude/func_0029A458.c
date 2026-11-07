// Sly 2 counterpart: __main (decomp src/lib/__main__Fv.cpp, libgcc __main)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern int D_004D0BAC;
void func_0029A3A8(void);
void func_0029A458(void)
{
    if (D_004D0BAC == 0) {
        D_004D0BAC = 1;
        func_0029A3A8();
    }
}
