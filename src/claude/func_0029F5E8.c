// func_0029F5E8: sceGsSyncPath(mode) (Sony libgraph). func_002955E0 = scePrintf (void). Each timeout error prints its
// message and the full register dump (macro), and jump2 cross-jumps the copies into the last one, as in the target.
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
void func_002955E0(const char *, ...);
#define R(a) (*(volatile unsigned int *)(a))
static __inline__ int VU1STAT(void) { int v; __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(v)); return v; }
#define DUMP() \
func_002955E0("\t<D1_CHCR=%08x:", R(0x10009000)); \
func_002955E0("D1_TADR=%08x:", R(0x10009030)); \
func_002955E0("D1_MADR=%08x:", R(0x10009010)); \
func_002955E0("D1_QWC=%08x>\r\n", R(0x10009020)); \
func_002955E0("\t<D2_CHCR=%08x:", R(0x1000A000)); \
func_002955E0("D2_TADR=%08x:", R(0x1000A030)); \
func_002955E0("D2_MADR=%08x:", R(0x1000A010)); \
func_002955E0("D2_QWC=%08x>\r\n", R(0x1000A020)); \
func_002955E0("\t<VIF1_STAT=%08x:", R(0x10003C00)); \
func_002955E0("GIF_STAT=%08x>\r\n", R(0x10003020)); \
    return -1
int func_0029F5E8(int mode)
{
    unsigned int cnt = 0;
    int ret;
    int vpu;
    if (mode == 0) {
        while (R(0x10009000) & 0x100)
            if (cnt++ > 0x1000000) goto err1;
        while (R(0x1000A000) & 0x100)
            if (cnt++ > 0x1000000) goto err2;
        while (R(0x10003C00) & 0x1F000003)
            if (cnt++ > 0x1000000) goto err3;
        __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(vpu));
        if (vpu & 0x100)
            do {
                if (cnt++ > 0x1000000) goto err4;
                __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(vpu));
            } while (vpu & 0x100);
        while (R(0x10003020) & 0xC00)
            if (cnt++ > 0x1000000) goto err5;
        return 0;
    err1:
        func_002955E0("sceGsSyncPath: DMA Ch.1 does not terminate\r\n");
        DUMP();
    err2:
        func_002955E0("sceGsSyncPath: DMA Ch.2 does not terminate\r\n");
        DUMP();
    err3:
        func_002955E0("sceGsSyncPath: VIF1 does not terminate\r\n");
        DUMP();
    err4:
        func_002955E0("sceGsSyncPath: VU1 does not terminate\r\n");
        DUMP();
    err5:
        func_002955E0("sceGsSyncPath: GIF does not terminate\r\n");
        DUMP();
    }
    ret = 0;
    if (R(0x10009000) & 0x100) ret = 1;
    if (R(0x1000A000) & 0x100) ret |= 2;
    if (R(0x10003C00) & 0x1F000003) ret |= 4;
    __asm__ volatile("cfc2.ni %0, $vi29" : "=r"(vpu));
    if (vpu & 0x100) ret |= 8;
    if (R(0x10003020) & 0xC00) ret |= 0x10;
    return ret;
}
