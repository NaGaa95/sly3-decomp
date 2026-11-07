// Sly 2 counterpart: scePadGetModVersion (decomp src/lib/scePadGetModVersion.c)
// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0 
// SLY3_ASM: gnu-reorder-db
// SLY3_SAVES: sd
extern char D_004D0F00[];
extern int D_004D1140[];
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002A2238(void)
{
    D_004D1140[0] = 0x12;
    if (func_00295F08(D_004D0F00, 1, 0, D_004D1140, 0x80, D_004D1140, 0x80, 0, 0) >= 0)
        return D_004D1140[3];
    return 0;
}
