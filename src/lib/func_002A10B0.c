// Reference: Sly 2 src/lib/sceCdGetDiskType_242AB8.c; target Sly 3 0x002A10B0.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int func_002A1018(void);
int sceCdGetDiskType_242AB8(void)
{
    int r = func_002A1018();
    return (r == -1) ? 0 : r;
}
