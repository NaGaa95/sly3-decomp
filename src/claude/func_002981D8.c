// Sly 2 counterpart: kFindAddress (decomp src/lib/kFindAddress.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
int *func_002981D8(int *p, int *end, int val)
{
    for (; *p != val && p < end; p++) ; if (p >= end) return 0; return p;
}
