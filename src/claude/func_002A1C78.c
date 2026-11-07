// Sly 2 counterpart: scePadInfoMode (decomp src/lib/scePadInfoMode.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned char *buf; int x4; int x8; int xC; int open; int x14; int x18; } PadSt;
extern PadSt D_004D0F50[2][4];
typedef struct { unsigned char x0[0x30]; unsigned char act[6][4]; unsigned char x48[8]; unsigned short modes[10]; unsigned char phase; unsigned char id; unsigned char x66; unsigned char x67; unsigned char nmodes; unsigned char curmode; unsigned char nact; unsigned char x6B[5]; unsigned char state; unsigned char req; unsigned char ok; } PadData;
PadData *func_002A1868(int port, int slot);
int func_002A1C78(int port, int slot, int term, int offs)
{
    PadData *p;
    if (D_004D0F50[port][slot].open == 0) return 0;
    p = func_002A1868(port, slot);
    if (p->ok != 1) return 0;
    if (p->req == 2) return 0;
    switch (term) {
    case 1:
        if (p->id == 0xF3) return 0;
        return p->id >> 4;
    case 2:
        if (p->phase == 1) return 0;
        return p->modes[p->curmode];
    case 3:
        if (p->phase == 1) return 0;
        return p->curmode;
    case 4:
        if (p->phase == 1) return 0;
        if (offs == -1) return p->nmodes;
        if (offs < p->nmodes) return p->modes[offs];
        return 0;
    }
    return 0;
}
