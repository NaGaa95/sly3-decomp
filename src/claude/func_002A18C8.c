// Sly 2 counterpart: scePadRead (decomp src/lib/scePadRead.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned char *buf; int x4; int x8; int xC; int open; int x14; int x18; } PadSt;
extern PadSt D_004D0F50[2][4];
int func_002980D0(void);
int func_00298120(void);
unsigned char *func_002A1868(int port, int slot);
void *func_00291E8C(void *, const void *, int);
int func_002A18C8(int port, int slot, unsigned char *rdata)
{
    int r;
    unsigned char *p;
    if (D_004D0F50[port][slot].open == 0) return 0;
    r = func_002980D0();
    p = func_002A1868(port, slot);
    func_00291E8C(rdata, p, *(int *)(p + 0x60));
    if (r == 1) func_00298120();
    return *(int *)(p + 0x60);
}
