// Sly 2 counterpart: scePadInfoPressMode (decomp src/lib/scePadInfoPressMode.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned char *buf; int x4; int x8; int xC; int open; int x14; int x18; } PadSt;
extern PadSt D_004D0F50[2][4];
int func_002A2000(int port, int slot);
int func_002A2168(int port, int slot)
{
    if (D_004D0F50[port][slot].open == 0) return 0;
    return func_002A2000(port, slot) == 0x3FFFF;
}
