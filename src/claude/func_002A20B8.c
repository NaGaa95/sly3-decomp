// Sly 2 counterpart: scePadSetButtonInfo (decomp src/lib/scePadSetButtonInfo.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
extern char D_004D0F00[];
extern int D_004D1140[];
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
void func_002A1A50(int, int, int);
int func_002A20B8(int port, int slot, int info)
{
    int r;
    D_004D1140[0] = 0xA;
    D_004D1140[1] = port;
    D_004D1140[2] = slot;
    D_004D1140[3] = info;
    if (func_00295F08(D_004D0F00, 1, 0, D_004D1140, 0x80, D_004D1140, 0x80, 0, 0) < 0)
        return 0;
    r = D_004D1140[4];
    if (r == 1) {
        func_002A1A50(port, slot, 2);
        r = D_004D1140[4];
    }
    return r;
}
