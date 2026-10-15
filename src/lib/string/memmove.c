// SLY3_ASFIX: engine-const-copy
// EE overlap-aware copy, recovered from SCUS_974.64 0x00291F38.
// Typed register constraints reproduce the original argument lifetimes.
// SLY3_CFLAGS: -O2 -G0 -malign-loops=2
// Derived from the Newlib copy algorithm with the retail EE 128/64-bit paths.
typedef unsigned int U128 __attribute__((mode(TI)));
typedef unsigned int U64 __attribute__((mode(DI)));
void *memmove(void *out, const void *in, unsigned int n)
{
    register void *save asm("$8") = out;
    register char *dst asm("$3") = save;
    register const char *src asm("$5") = in;
    register int len asm("$6") = n;
    if (src < (const char *)save) {
        register const char *end asm("$7") = src + len;
        if ((const char *)save >= end) goto Forward;
        src = end; dst = (char *)save + len;
        while (len--) *--dst = *--src;
        goto Done;
    }
Forward:
    if (len >= sizeof(U128)*2 && !(((unsigned int)src | (unsigned int)dst) & 15)) {
        register U128 *d asm("$7") = (U128 *)dst;
        const U128 *s = (const U128 *)src;
        while (len >= sizeof(U128)*2) {
            register U128 first asm("$3");
            register U128 second asm("$2");
            first = *s++;
            *d++ = first;
            second = *s++;
            *d++ = second;
            len -= sizeof(U128)*2;
        }
        dst = (char *)d;
        src = (const char *)s;
        {
            register U64 *d asm("$7") = (U64 *)dst;
            const U64 *s = (const U64 *)src;
            while (len >= sizeof(U64)) {
                *d++ = *s++;
                len -= sizeof(U64);
            }
            dst = (char *)d;
            src = (const char *)s;
        }
    }
    while (len--) *dst++ = *src++;
Done:
    return save;
}
