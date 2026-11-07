// Sly 2 counterpart: scePadSetMainMode (decomp src/lib/scePadSetMainMode.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
extern char D_004D0F00[];
extern int D_004D1140[];
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
void func_002A1A50(int, int, int);
int func_002A1DB0(int port, int slot, int offs, int lock)
{
    int r;
    D_004D1140[0] = 6;
    D_004D1140[1] = port;
    D_004D1140[2] = slot;
    D_004D1140[3] = offs;
    D_004D1140[4] = lock;
    if (func_00295F08(D_004D0F00, 1, 0, D_004D1140, 0x80, D_004D1140, 0x80, 0, 0) < 0)
        return 0;
    r = D_004D1140[5];
    if (r == 1) {
        func_002A1A50(port, slot, 2);
        r = D_004D1140[5];
    }
    return r;
}
