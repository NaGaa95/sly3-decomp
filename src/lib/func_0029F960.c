// SLY3_CC: tools/third_party/ee-gcc2.95.3-114
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-gp64

extern const char D_0032B4B8[];
int func_002955E0(const char *format, ...);
int func_0029FE28(unsigned int *channel);

void func_0029F960(unsigned int *channel)
{
    int timeout = 0x1000000;

    while (*(volatile unsigned int *)channel & 0x100) {
        if (--timeout < 0) {
            func_002955E0(D_0032B4B8);
            func_0029FE28(channel);
        }
    }
}

typedef char RuntimeDmaStatusWordWidth4[(sizeof(unsigned int) == 4) ? 1 : -1];
