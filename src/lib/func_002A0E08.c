// Reference: Sly 2 src/lib/sceCdGetReadPos.c; target Sly 3 0x002A0E08.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
extern int _sceCd_mode; extern int _sceCd_readpos;
int sceCdGetReadPos(void)
{
    if (_sceCd_mode != 1) return 0;
    return *(int *)((unsigned)&_sceCd_readpos | 0x20000000);
}
