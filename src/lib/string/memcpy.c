// SLY3_ASFIX: engine-const-copy
// Based on the Newlib memory-copy algorithm; EE-specific widths and register
// lifetimes recovered from SCUS_974.64. No inline assembly instructions.
// Loop alignment and constant reuse are separately verified SDK adaptations.
// SLY3_CFLAGS: -O2 -G0 -malign-loops=2
// Reconstructed EE-specific memory widths from Sly 3 USA 0x291E8C.
typedef unsigned int U128 __attribute__((mode(TI)));
typedef unsigned int U64 __attribute__((mode(DI)));
void *memcpy(void *out, const void *in, unsigned int n)
{
    register void *save asm("$8") = out;
    register char *dst asm("$3") = save;
    const char *src = in;
    int len = n;
    if (len >= sizeof(U128)*2 && !(((unsigned int)src | (unsigned int)save) & 15)) {
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
    return save;
}
