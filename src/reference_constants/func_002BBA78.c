// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0
// Original pool startup reset. Independent scalar writes precede the first clear.
extern int D_0036AE3C, D_0036AE40, D_0036AE44, D_0036AE48, D_0036AE4C;
extern unsigned char D_004D2CA0[];
extern unsigned char D_004D2CE0[];
extern unsigned char D_004D2D60[];
extern void *memset(void *destination, int value, unsigned int bytes);
extern void func_0011E210(void *pool);

void func_002BBA78(void)
{
    D_0036AE4C = 0;
    D_0036AE3C = 0;
    D_0036AE48 = 0;
    D_0036AE44 = 0;
    memset(D_004D2CE0, 0, 128);
    D_0036AE40 = 0;
    memset(D_004D2CA0, 0, 64);
    func_0011E210(D_004D2D60);
}
