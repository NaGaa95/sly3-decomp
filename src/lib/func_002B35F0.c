// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-loop7
int func_002B35F0(int mode, unsigned short timeout)
{
    int result = 0;
    switch (mode) {
    case 0:
        while ((int)*(volatile unsigned int *)0x10002010 < 0)
            ;
        result = 0;
        break;
    case 1:
        result = *(volatile unsigned int *)0x10002010 >> 31;
        break;
    }
    return result;
}
