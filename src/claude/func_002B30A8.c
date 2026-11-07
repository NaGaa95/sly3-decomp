// Sly 2 counterpart: _sequenceDisplayExtension (decomp src/lib/_sequenceDisplayExtension.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { char p0[0x154]; int matrix; int hsize; int vsize; } D;
unsigned int func_002B0B78(D *d, int n);
void func_002B30A8(D *d)
{
    func_002B0B78(d, 3);
    if (func_002B0B78(d, 1)) {
        func_002B0B78(d, 8);
        func_002B0B78(d, 8);
        d->matrix = func_002B0B78(d, 8);
    }
    d->hsize = func_002B0B78(d, 14);
    ((void (*)(D *, int))func_002B0B78)(d, 1);
    d->vsize = func_002B0B78(d, 14);
}
