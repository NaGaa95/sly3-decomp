// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Original pool startup reset. Independent scalar writes precede the first clear.
extern int D_0036AE64, D_0036AE68, D_0036AE6C, D_0036AE70, D_0036AE74;
extern unsigned char D_004D2E50[];
extern unsigned char D_004D2E90[];
extern unsigned char D_004D2F10[];
extern void *memset(void *destination, int value, unsigned int bytes);
extern void func_0011E210(void *pool);

void func_002BBB58(void)
{
    D_0036AE74 = 0;
    D_0036AE64 = 0;
    D_0036AE70 = 0;
    D_0036AE6C = 0;
    memset(D_004D2E90, 0, 128);
    D_0036AE68 = 0;
    memset(D_004D2E50, 0, 64);
    func_0011E210(D_004D2F10);
}
