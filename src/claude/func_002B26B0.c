// Sly 2 counterpart: _groupOfPicturesHeader (decomp src/lib/_groupOfPicturesHeader.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    char p0[0xFC]; int xFC; char p1[0x1B4 - 0x100]; int closed_gop; int broken_link;
    char p2[0x85C - 0x1BC]; int x85C; int x860; int x864;
} MpegD;
int func_002B0B78(MpegD *d, int n);
void func_002B2CE8(MpegD *d);
void func_002B26B0(MpegD *d)
{
    d->xFC = 0;
    d->x864 = 1;
    d->x85C = d->x860 + 1;
    func_002B0B78(d, 1);
    func_002B0B78(d, 5);
    func_002B0B78(d, 6);
    func_002B0B78(d, 1);
    func_002B0B78(d, 6);
    func_002B0B78(d, 6);
    d->closed_gop = func_002B0B78(d, 1);
    d->broken_link = func_002B0B78(d, 1);
    func_002B2CE8(d);
}
