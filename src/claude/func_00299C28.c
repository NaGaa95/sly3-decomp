// Sly 2 counterpart: sceSifSendCmd (decomp src/lib/sceSifSendCmd.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
unsigned int func_00299AF0(int cid, int mode, void *pkt, int pktsize, void *src, void *dest, int size);
unsigned int func_00299C28(int cid, void *pkt, int pktsize, void *src, void *dest, int size)
{
    int mode = 0;
    return func_00299AF0(cid, mode, pkt, pktsize, src, dest, size);
}
