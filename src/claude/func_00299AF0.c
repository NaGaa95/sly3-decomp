// Sly 2 counterpart: _sceSifSendCmd (decomp src/lib/_sceSifSendCmd.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    unsigned int psize:8;
    unsigned int dsize:24;
    unsigned int dest;
    unsigned int cid;
    unsigned int opt;
} SifCmdHeader;
typedef struct {
    unsigned int data;
    unsigned int addr;
    unsigned int size;
    unsigned int mode;
} sceSifDmaData;
extern void *D_004CF760;
void func_00299DF0(void *, int);
unsigned int func_00293A70(sceSifDmaData *, int);
unsigned int func_00293A60(sceSifDmaData *, int);
unsigned int func_00299AF0(int cid, int mode, void *pp, int ps, void *src, void *dest, int size)
{
    sceSifDmaData dma[2];
    SifCmdHeader *p = (SifCmdHeader *)pp;
    int count;

    if (ps < 16 || ps > 112) return 0;

    count = 0;
    if (size > 0) {
        count = 1;
        dma[0].data = (unsigned int)src;
        p->dsize = size;
        dma[0].addr = (unsigned int)dest;
        p->dest = (unsigned int)dest;
        dma[0].size = size;
        dma[0].mode = 0;
        if (mode & 4) func_00299DF0(src, size);
    } else {
        p->dsize = 0;
        p->dest = 0;
    }
    dma[count].data = (unsigned int)p;
    dma[count].addr = (unsigned int)D_004CF760;
    dma[count].size = ps;
    p->cid = cid;
    p->psize = ps;
    dma[count].mode = 0x44;
    count++;
    func_00299DF0(p, ps);
    if (mode & 1) return func_00293A70(dma, count);
    return func_00293A60(dma, count);
}
