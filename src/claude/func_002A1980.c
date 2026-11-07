// Sly 2 counterpart: scePadGetState_243388 (decomp src/lib/scePadGetState_243388.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned char *buf; int x4; int x8; int xC; int open; int x14; int x18; } PadSt;
extern PadSt D_004D0F50[2][4];
int func_002980D0(void);
int func_00298120(void);
unsigned char *func_002A1868(int port, int slot);
int func_002A1980(int port, int slot)
{
    int r;
    unsigned char *p;
    if (D_004D0F50[port][slot].open == 0) return 99;
    r = func_002980D0();
    p = func_002A1868(port, slot);
    if (p[0x70] == 6 && p[0x71] == 2) {
        if (r == 1) func_00298120();
        return 5;
    }
    if (r == 1) func_00298120();
    return p[0x70];
}
