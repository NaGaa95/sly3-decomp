// Sly 2 counterpart: _decPicture (decomp src/lib/_decPicture.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p0[0x28]; int ready; } IMG;
typedef struct {
    char p0[0x130]; int second_field;
    char p134[0x184 - 0x134]; int picture_structure;
    char p188[0x1C8 - 0x188]; IMG *a[4]; IMG *b[4]; IMG *c[4];
} D;
void _sceMpegError(D *d, const char *msg);
int func_002AF688(D *d);
int func_002AA250(D *d)
{
    IMG *img;
    int r;
    int ps;

    ps = d->picture_structure;
    if (ps == 3 && d->second_field) {
        _sceMpegError(d, "odd number of field pictures");
        d->second_field = 0;
        ps = d->picture_structure;
    }
    switch (ps) {
    case 3:
        img = d->a[2];
        break;
    case 1:
        img = d->b[2];
        break;
    case 2:
        img = d->c[2];
        break;
    default:
        img = d->a[2];
        _sceMpegError(d, "unknown picture sutructure");
        break;
    }
    r = func_002AF688(d);
    if (r) img->ready = 1;
    return r;
}
