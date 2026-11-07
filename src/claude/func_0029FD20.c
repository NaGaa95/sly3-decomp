// Sly 2 counterpart: sceDmaSend (decomp src/lib/sceDmaSend.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { unsigned DIR:1; unsigned p0:1; unsigned MOD:2; unsigned ASP:2; unsigned TTE:1; unsigned TIE:1; unsigned STR:1; unsigned p1:7; unsigned TAG:16; } tD_CHCR;
typedef struct { tD_CHCR chcr; unsigned p0[3]; void *madr; unsigned p1[3]; unsigned qwc; unsigned p2[3]; void *tadr; } sceDmaChan;
void WaitDma(sceDmaChan *d);
void *CheckAddress(void *p);
void func_0029FD20(sceDmaChan *d, void *tag)
{
    void *a = CheckAddress(tag);
    WaitDma(d);
    if (d->tadr != (void *)-1) d->tadr = a;
    d->qwc = 0;
    d->chcr.MOD = 1;
    d->chcr.DIR = 1;
    d->chcr.STR = 1;
}
