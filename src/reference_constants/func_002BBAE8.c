// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Original pool startup reset. Independent scalar writes precede the first clear.
extern int D_0036AE50, D_0036AE54, D_0036AE58, D_0036AE5C, D_0036AE60;
extern unsigned char D_004D2D78[];
extern unsigned char D_004D2DB8[];
extern unsigned char D_004D2E38[];
extern void *memset(void *destination, int value, unsigned int bytes);
extern void func_0011E210(void *pool);

void func_002BBAE8(void)
{
    D_0036AE60 = 0;
    D_0036AE50 = 0;
    D_0036AE5C = 0;
    D_0036AE58 = 0;
    memset(D_004D2DB8, 0, 128);
    D_0036AE54 = 0;
    memset(D_004D2D78, 0, 64);
    func_0011E210(D_004D2E38);
}
