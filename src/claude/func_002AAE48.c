// Sly 2 counterpart: _sceMpegOutputFrame (decomp src/lib/_sceMpegOutputFrame.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct {
    char p0[0x108]; int x108; char p1[0x160 - 0x10C]; int x160; char p2[0x184 - 0x164]; int x184;
    char p3[0x1C8 - 0x188]; void *a[4]; void *b[4]; void *c[4];
} D;
void func_002AA6A8(D *d, void *img, int n);
void func_002AA968(D *d, void *i0, void *i1, int n);
void func_002AAE48(D *d, int n, int flag)
{
    if (flag) {
        if (d->x184 == 3) {
            func_002AA6A8(d, d->x160 == 3 ? d->a[3] : d->a[0], n - 1);
        } else {
            void *i0, *i1;
            if (d->x160 == 3) {
                i0 = d->b[3];
                i1 = d->c[3];
            } else {
                i0 = d->b[0];
                i1 = d->c[0];
            }
            func_002AA968(d, i0, i1, n - 1);
        }
    }
    if (d->x108 == 1)
        d->x108 = 2;
}
