// SLY3_CFLAGS: -O2 -G0 -malign-loops=2 -fno-gcse
// Recovered EE memory fill at SCUS_974.64 0x00292034.
// PCPYH/PCPYLD supply the EE packed-lane operations unavailable as C operators.
// Empty constraints preserve pointer/temporary lifetimes; they emit no code.
typedef unsigned int U128 __attribute__((mode(TI)));
typedef unsigned int U64 __attribute__((mode(DI)));

void *memset(void *out, int c, unsigned int n)
{
    char *dst = out;
    if (n >= sizeof(U64) && !((unsigned int)out & 15)) {
        U64 *d = out;
        register unsigned int byte asm("$9");
        register U64 buffer asm("$8");
        register U64 repeated asm("$3");
        register unsigned int small asm("$10");
        register U64 shifted asm("$3");
        asm("" : : "r"(d));
        byte = (unsigned char)c;
        small = n < sizeof(U128)*2;
        buffer = byte;
        asm("" : "+r"(buffer));
        shifted = buffer << 8;
        buffer = shifted | byte;
        asm("pcpyh %0,%1" : "=r"(repeated) : "r"(buffer));
        if (!small) {
            U128 *q = (U128 *)d;
            register U128 wide asm("$8");
            asm("pcpyld %0,%1,%1" : "=r"(wide) : "r"(repeated));
            while (n >= sizeof(U128)*2) {
                *q++ = wide;
                *q++ = wide;
                n -= sizeof(U128)*2;
            }
            d = (U64 *)q;
        }
        while (n >= sizeof(U64)) {
            *d++ = repeated;
            n -= sizeof(U64);
        }
        dst = (char *)d;
    }
    while (n--) *dst++ = (char)c;
    return out;
}
