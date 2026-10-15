// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-loop7
int func_002985A0(unsigned int *destination, unsigned int *source, unsigned int bytes)
{
    unsigned int i;
    bytes >>= 2;
    for (i = 0; i < bytes; i++)
        *destination++ = *source++;
    return 0;
}
