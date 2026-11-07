// Sly 2 counterpart: _quantMatrixExtension (decomp src/lib/_quantMatrixExtension.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    char p0[0x828]; int x828; unsigned int x82C; char p1[0x850 - 0x830]; int load_iq; int load_niq;
} MpegD;
extern char D_0032C8E8[];
extern char D_0032C910[];
int func_002B0B78(MpegD *d, int n);
void func_002B2EB8(MpegD *d);
void _sceMpegError(MpegD *d, const char *msg);
void func_002B29D8(MpegD *d)
{
    if ((d->load_iq = func_002B0B78(d, 1)) != 0) {
        func_002B2EB8(d);
        *(volatile unsigned int *)0x10002000 = 0x50000000;
        d->x82C = 0x50000000;
        d->x828 = 1;
        func_002B2EB8(d);
    }
    if ((d->load_niq = func_002B0B78(d, 1)) != 0) {
        func_002B2EB8(d);
        *(volatile unsigned int *)0x10002000 = 0x58000000;
        d->x82C = 0x50000000;
        d->x828 = 1;
        func_002B2EB8(d);
    }
    if (func_002B0B78(d, 1)) _sceMpegError(d, D_0032C8E8);
    if (func_002B0B78(d, 1)) _sceMpegError(d, D_0032C910);
}
