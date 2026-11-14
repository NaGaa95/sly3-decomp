// Sly 2 counterpart: _send_to_iop (decomp src/lib/_send_to_iop.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* func_002A1568 (libpad): DMA the 0x20-byte pad command to the IOP double buffer. */
typedef struct { int x0; int x4; int x8; unsigned char data[0x14]; } PadCmd;
typedef struct { unsigned char *buf; PadCmd *cmd; unsigned int dest; unsigned int dmaid; int open; int x14; int x18; } PadSt;
typedef struct { void *src; void *dest; int size; int attr; } SifDmaData;
extern PadSt D_004D0F50[2][4];
extern int D_0034DF4C;
extern char D_0032B820[];
int func_00293A40(unsigned int);
void func_00293BC8(void *, void *);
unsigned int func_00293A60(SifDmaData *, int);
void func_002955E0(const char *, ...);

int func_002A1568(int port, int slot)
{
    SifDmaData dma[16];
    PadCmd *c;
    unsigned int id;
    unsigned int dest;
    int n;

    c = D_004D0F50[port][slot].cmd;
    if (D_004D0F50[port][slot].dmaid != 0 && func_00293A40(D_004D0F50[port][slot].dmaid) >= 0) {
        if (D_0034DF4C)
            func_002955E0(D_0032B820);
        return 0;
    }
    n = c->x0 + 1;
    dest = D_004D0F50[port][slot].dest + ((n & 1) << 5);
    c->x0 = n;
    func_00293BC8(c, (char *)c + 0x1F);
    dma[0].dest = (void *)dest;
    dma[0].src = c;
    dma[0].size = 0x20;
    dma[0].attr = 0;
    id = func_00293A60(dma, 1);
    if (id == 0) {
        if (D_0034DF4C)
            func_002955E0(D_0032B820);
        return 0;
    }
    D_004D0F50[port][slot].dmaid = id;
    return 1;
}
