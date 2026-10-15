// Sly 3 USA 0x0029FA00. SDK loop profile verified against all 52 code bytes.
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASFIX: sdk-loop7
void memclr(char *p, int n)
{
    while (n--) *p++ = 0;
}
