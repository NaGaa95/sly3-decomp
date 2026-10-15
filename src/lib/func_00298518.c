// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-loop7
int func_00298518(unsigned char *destination, unsigned char *source, unsigned int bytes)
{
    unsigned int i;
    for (i = 0; i < bytes; i++)
        *destination++ = *source++;
    return 0;
}
