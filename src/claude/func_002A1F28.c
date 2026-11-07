// Sly 2 counterpart: scePadSetActAlign (decomp src/lib/scePadSetActAlign.c)
// (Claude agent) 2 diffs: pad result pattern r = p->result; if (r == 1) { f(); r = p->result; }. Left: loop body sb/slti order (ours sb first) in every mode/compiler tried.
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { int cmd; int port; int slot; unsigned char data[8]; int result; char pad[0x80 - 0x18]; } PadBuf;
extern PadBuf D_004D1140;
extern char D_004D0F00[];
int func_00295F08(void *cd, int fno, unsigned int mode, void *send, int ssize, void *recv, int rsize, void *end, void *earg);
int func_002A1A50(int port, int slot, int state);
int func_002A1F28(int port, int slot, const unsigned char *data)
{
    int i;
    int r;
    PadBuf *p = &D_004D1140;
    D_004D1140.cmd = 8;
    p->port = port;
    p->slot = slot;
    for (i = 0; i < 6; i++)
        p->data[i] = data[i];
    if (func_00295F08(D_004D0F00, 1, 0, p, 0x80, p, 0x80, 0, 0) < 0)
        return 0;
    r = p->result;
    if (r == 1) {
        func_002A1A50(port, slot, 2);
        r = p->result;
    }
    return r;
}
