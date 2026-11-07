// Sly 2 counterpart: scePadGetButtonMask (decomp src/lib/scePadGetButtonMask.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned char *buf; int x4; int x8; int xC; int open; int x14; int x18; } PadSt;
extern PadSt D_004D0F50[2][4];
unsigned char *func_002A1868(int port, int slot);
int func_002A2000(int port, int slot)
{
    unsigned char *p;
    if (D_004D0F50[port][slot].open == 0) return 0;
    p = func_002A1868(port, slot);
    if (p[0x72] != 1) return 0;
    if (p[0x64] < 2) return 0;
    if (p[0x66] < 2) return 0;
    return (long)p[0x79] + ((long)p[0x7A] << 8) + ((long)p[0x7B] << 16) + ((long)p[0x7C] << 24);
}
