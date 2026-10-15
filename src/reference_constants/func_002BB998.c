// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Original pool startup reset. Independent scalar writes precede the first clear.
extern int D_0036AE28, D_0036AE2C, D_0036AE30, D_0036AE34, D_0036AE38;
extern unsigned char D_004D2BC8[];
extern unsigned char D_004D2C08[];
extern unsigned char D_004D2C88[];
extern void *memset(void *destination, int value, unsigned int bytes);
extern void func_0011E210(void *pool);

void func_002BB998(void)
{
    D_0036AE38 = 0;
    D_0036AE28 = 0;
    D_0036AE34 = 0;
    D_0036AE30 = 0;
    memset(D_004D2C08, 0, 128);
    D_0036AE2C = 0;
    memset(D_004D2BC8, 0, 64);
    func_0011E210(D_004D2C88);
}
