// Reference: Sly 2 src/lib/func_0024F770.c; target Sly 3 0x002AE198.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
int sceMpegDemuxPssRing(void *, void *, int, int, int);
int func_002AE198(void *a, void *b, int c)
{
    return sceMpegDemuxPssRing(a, b, c, 0, -1);
}
