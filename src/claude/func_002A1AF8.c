// Sly 2 counterpart: scePadGetState (decomp src/hand/scePadGetState.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned char *buf; int x4; int x8; int xC; int open; int x14; int x18; } PadSt;
extern PadSt D_004D0F50[2][4];
unsigned char *func_002A1868(int port, int slot);
int func_002A1AF8(int port, int slot)
{
    if (D_004D0F50[port][slot].open == 0) return 0;
    return func_002A1868(port, slot)[0x71];
}
