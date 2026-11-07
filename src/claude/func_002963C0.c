// Sly 2 counterpart: _sceFs_Rcv_Intr (decomp src/lib/_sceFs_Rcv_Intr.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db

typedef struct { char b[0x440]; } FsPkt;
typedef struct { int sema; int cmd; void *dst; int size; } RcvHdr;
typedef struct { char c[4]; } W;
typedef struct { int n1; int n2; char *dst1; char *dst2; char buf1[0x40]; char buf2[0x40]; } RdTail;
typedef struct { char b[0x144]; } Dirent;
typedef struct { int b[0x10]; } Stat;
typedef struct { int x0, x4, x8, idx; } SifCmdHdr;
extern int D_0034A6A0;
extern int D_0034A698;
extern volatile int D_0034A618[32];
extern FsPkt D_004CBC80[];
void *func_00291E8C(void *, const void *, unsigned int);
int func_002936D0(int);

void func_002963C0(SifCmdHdr *cmd, void *userData)
{
    RcvHdr h;
    struct DP { void *dst; unsigned int size; } d;
    char *dst, *udst;
    char *p;
    RdTail *rd;
    int i, v;
    register int idx asm("$5");
    unsigned int n;

    idx = 0;
    if (D_0034A6A0)
        idx = cmd->idx;
    {
        register int stride asm("$3") = sizeof(FsPkt);
        int offset = idx * stride;
        D_0034A698 = idx;
        {
            register FsPkt *base asm("$4") = D_004CBC80;
            register unsigned int uncached asm("$5") = 0x20000000;
            p = (char *)(((unsigned int)base + offset) | uncached);
        }
    }
    *(W *)&h.sema = *(W *)(p + 0);
    *(W *)&h.cmd = *(W *)(p + 4);
    *(W *)&h.dst = *(W *)(p + 8);
    *(W *)&h.size = *(W *)(p + 12);
    if (h.sema >= 0)
        func_00291E8C(h.dst, p + 0x10, h.size);
    switch (h.cmd) {
    case 2:
        rd = (RdTail *)(p + 0x14);
        if (rd->n1 > 0) {
            dst = rd->dst1;
            udst = (char *)((unsigned int)dst | 0x20000000);
            for (i = 0; i < rd->n1; i++)
                dst[i] = udst[i] = rd->buf1[i];
        }
        if (rd->n2 > 0) {
            dst = rd->dst2;
            udst = (char *)((unsigned int)dst | 0x20000000);
            for (i = 0; i < rd->n2; i++)
                dst[i] = udst[i] = rd->buf2[i];
        }
        break;
    case 11:
        if (*(int *)h.dst > 0) {
            *(W *)&d.dst = *(W *)(p + 0x14);
            *(Dirent *)d.dst = *(Dirent *)(p + 0x18);
        }
        break;
    case 12:
        *(W *)&d.dst = *(W *)(p + 0x14);
        *(Stat *)d.dst = *(Stat *)(p + 0x18);
        break;
    case 23:
    case 25:
    case 26:
        *(W *)&d.dst = *(W *)(p + 0x14);
        *(W *)&d.size = *(W *)(p + 0x18);
        n = d.size;
        if (n > 0x400)
        {
            d.size = 0x400;
            n = 0x400;
        }
        func_00291E8C(d.dst, p + 0x1C, n);
        break;
    }
    if (h.sema < 0) {
        {
            register int released asm("$2") = -h.sema;
            h.sema = released;
            v = released;
        }
        for (i = 0; i < 32; i++) {
            if (D_0034A618[i] == v) {
                D_0034A618[i] = -1;
                break;
            }
        }
        return;
    }
    func_002936D0(h.sema);
}
