// Sly 2 counterpart: isceSifSendCmd (decomp src/lib/isceSifSendCmd.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
// 3/15 with gnu-reorder: `addiu sp,-0x10` scheduled 2 insns earlier than target (scheduler difference, see sceFsReset).
unsigned int func_00299AF0(int cid, int mode, void *pkt, int pktsize, void *src, void *dest, int size);
unsigned int func_00299C68(int cid, void *pkt, int pktsize, void *src, void *dest, int size)
{
    return func_00299AF0(cid, 1, pkt, pktsize, src, dest, size);
}
