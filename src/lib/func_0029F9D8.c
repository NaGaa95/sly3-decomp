// Reference: Sly 2 src/lib/CheckAddress.c; target Sly 3 0x0029F9D8.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
unsigned int CheckAddress(unsigned int a)
{
    if ((a >> 28) == 7) {
        a &= 0x0FFFFFFF;
        a |= 0x80000000;
    }
    return a;
}
