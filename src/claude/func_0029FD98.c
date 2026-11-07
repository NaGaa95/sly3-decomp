// Sly 2 counterpart: sceDmaRecv (decomp src/lib/sceDmaRecv.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned DIR:1; unsigned p0:1; unsigned MOD:2; unsigned ASP:2; unsigned TTE:1; unsigned TIE:1; unsigned STR:1; unsigned p1:7; unsigned TAG:16; } tD_CHCR;
typedef struct { tD_CHCR chcr; unsigned p0[3]; unsigned madr; unsigned p1[3]; unsigned qwc; } sceDmaChan;
void WaitDma(sceDmaChan *d);
int func_0029FD98(sceDmaChan *d)
{
    WaitDma(d);
    d->qwc = 0;
    d->chcr.MOD = 1;
    d->chcr.DIR = 0;
    d->chcr.STR = 1;
}
