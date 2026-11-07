// Sly 2 counterpart: scePadInfoAct (decomp src/lib/scePadInfoAct.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned char *buf; int x4; int x8; int xC; int open; int x14; int x18; } PadSt;
extern PadSt D_004D0F50[2][4];
typedef struct { unsigned char x0[0x30]; unsigned char act[6][4]; unsigned char x48[0x1C]; unsigned char phase; unsigned char x65; unsigned char x66; unsigned char x67[3]; unsigned char nact; unsigned char x6B[5]; unsigned char state; unsigned char req; unsigned char ok; } PadData;
PadData *func_002A1868(int port, int slot);
int func_002A1B50(int port, int slot, int actno, int term)
{
    PadData *p;
    if (D_004D0F50[port][slot].open == 0) return 0;
    p = func_002A1868(port, slot);
    if (p->ok != 1) return 0;
    if (p->phase < 2) return 0;
    if (actno >= p->nact) return 0;
    if (actno == -1) return p->nact;
    switch (term) {
    case 1: return p->act[actno][0];
    case 2: return p->act[actno][1];
    case 3: return p->act[actno][2];
    case 4: return p->act[actno][3];
    }
    return 0;
}
