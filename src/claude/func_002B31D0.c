// Sly 2 counterpart: _pictureDisplayExtension (decomp src/lib/_pictureDisplayExtension.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0 -fno-strength-reduce
// SLY3_ASM: gnu-reorder-db
typedef struct {
    char p0[0x14C]; int progressive_sequence;
    char p150[0x184 - 0x150]; int picture_structure; int top_field_first;
    char p18C[0x194 - 0x18C]; int repeat_first_field;
    char p198[0x19C - 0x198]; int hoffs[3]; int voffs[3];
} D;
unsigned int func_002B0B78(D *d, int n);
void func_002B31D0(D *d)
{
    int n;
    int i;

    if (d->progressive_sequence) {
        if (!d->repeat_first_field) goto one;
        n = 2;
        if (d->top_field_first) n = 3;
    } else if (d->picture_structure != 3) {
    one:
        n = 1;
    } else {
        n = 2;
        if (d->repeat_first_field) n = 3;
    }
    for (i = 0; i < n; i++) {
        d->hoffs[i] = func_002B0B78(d, 16);
        func_002B0B78(d, 1);
        d->voffs[i] = func_002B0B78(d, 16);
        func_002B0B78(d, 1);
    }
}
