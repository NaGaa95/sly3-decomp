// Sly 2 counterpart: scePadSetActDirect (decomp src/lib/scePadSetActDirect.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int x0; int x4; int x8; unsigned char data[6]; } PadCmd;
typedef struct { unsigned char *buf; PadCmd *cmd; int x8; int xC; int open; int x14; int x18; } PadSt;
extern PadSt D_004D0F50[2][4];
unsigned char *func_002A1868(int port, int slot);
int func_002A1568(int port, int slot);
int func_002A1E68(int port, int slot, const unsigned char *data)
{
    int i;
    PadCmd *c;
    if (func_002A1868(port, slot)[0x72] != 1) return 0;
    c = D_004D0F50[port][slot].cmd;
    for (i = 0; i < 6; i++) c->data[i] = data[i];
    c->x4 = 1;
    c->x8 = 6;
    if (func_002A1568(port, slot) != 1) return 0;
    return 1;
}
