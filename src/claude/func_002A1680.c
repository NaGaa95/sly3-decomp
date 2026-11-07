// Sly 2 counterpart: scePadPortOpen (decomp src/lib/scePadPortOpen.c)
// func_002A1680 (0x243088) MATCH (Lilly's agent, T1642, 2026-10-24). Plain C, no asm/pins/volatile; from lilly9 (T1636).
// The key: the IOP request buffer D_004D1140 is used directly (lilly9 reused the loop pointer p, which has no alias base).
// With strict aliasing the field types decide which tail stores conflict: open/dmaid/x0 (int) conflict, cmd/iopcmd
// (PadCmd *) conflict, buf (PadData *) and the void * read of D_004D1140[5] are alone. The int return read
// D_004D1140[3] has a known base in sched1, so it stays independent of the PadSt stores there; in sched2 (hard-reg
// addresses are baseless) it depends on the int stores, which raises the dmaid store's priority so it issues right
// after c->x0 like the target. See notes/23C000.md (T1636, T1642).
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
typedef struct { int x0; int x4; int x8; unsigned char data[0x14]; } PadCmd;
typedef struct { unsigned char x0[0x58]; int frame; int x5C; int len; int x64; unsigned char x68[8]; unsigned char state; unsigned char req; unsigned char ok; unsigned char x73[0xD]; } PadData;
typedef struct { PadData *buf; PadCmd *cmd; PadCmd *iopcmd; int dmaid; int open; int x14; int x18; } PadSt;
extern PadSt D_004D0F50[2][4];
extern PadCmd D_004D1040[2][4];
extern char D_004D0F00[];
extern int D_004D1140[];
extern int D_0034DF4C;
extern char D_0032B840[];
extern char D_0032B870[];
int func_002955E0(const char *, ...);
void *func_00292034(void *, int, int);
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002A1680(int port, int slot, void *addr)
{
    int i;
    PadData *p;
    PadCmd *c;
    void *t;
    if ((int)addr & 0x3F) {
        if (D_0034DF4C) func_002955E0(D_0032B840, addr);
        return 0;
    }
    if (D_004D0F50[port][slot].open == 1) {
        if (D_0034DF4C) func_002955E0(D_0032B870, port, slot);
        return 0;
    }
    p = (PadData *)addr;
    for (i = 0; i < 2; i++) {
        p->frame = 0;
        p->state = 5;
        p->req = 2;
        p->x68[-1] = 0;
        func_00292034(p, 0xFF, 0x20);
        p->len = 0;
        p++;
    }
    D_004D1140[0] = 1;
    D_004D1140[1] = port;
    D_004D1140[2] = slot;
    D_004D1140[4] = (int)addr;
    if (func_00295F08(D_004D0F00, 1, 0, D_004D1140, 0x80, D_004D1140, 0x80, 0, 0) < 0)
        return 0;
    c = &D_004D1040[port][slot];
    t = ((void **)D_004D1140)[5];
    D_004D0F50[port][slot].open = 1;
    D_004D0F50[port][slot].iopcmd = t;
    D_004D0F50[port][slot].buf = addr;
    D_004D0F50[port][slot].cmd = c;
    c->x0 = 0;
    D_004D0F50[port][slot].dmaid = 0;
    return D_004D1140[3];
}
