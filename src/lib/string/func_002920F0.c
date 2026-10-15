// SLY3_CFLAGS: -O2 -G0 -malign-loops=3 -fno-builtin -fno-schedule-insns2
// strncmp at SCUS_974.64 0x002920F0, recovered from the complete EE body.
// Behavioral reference: Newlib 1.8.2 newlib/libc/string/strncmp.c.
// Newlib license: COPYING.NEWLIB in this directory.
// Packed operators are individual EE intrinsics unavailable as C operators.
// Empty constraints preserve register lifetimes and TI-to-DI low-lane views;
// they emit no instructions. C statements supply every branch and loop.
typedef unsigned int U128 __attribute__((mode(TI)));
typedef unsigned int U64 __attribute__((mode(DI)));
int func_002920F0(const char *in1, const char *in2, unsigned int n)
{
    register const char *s1 asm("$4") = in1;
    register const char *s2 asm("$5") = in2;
    unsigned int combined;
    asm("" : "+r"(s1), "+r"(s2));
    combined = (unsigned int)s1 | (unsigned int)s2;
    if (n == 0) return 0;
    if (!(combined & 7)) {
        register unsigned int wide_guard asm("$2") = combined & 15;
        register unsigned int small asm("$7") = n < 16;

        register U64 ones asm("$9") = 0x0101010101010101ULL;
        asm("" : "+r"(wide_guard), "+r"(small), "+r"(ones));
        wide_guard |= small;
        asm("" : "+r"(wide_guard));
        if (!wide_guard) {
            register const U128 *qa asm("$7") = (const U128 *)s1;
            register const U128 *qb asm("$8");
            register U128 wide_ones asm("$10");
            register U128 high asm("$9");
            register U128 left asm("$3");
            register U128 right asm("$2");
            register U64 mask asm("$8");
            register U64 upper asm("$2");
            register U64 lower asm("$3");
            U64 difference;
            register U64 first_difference asm("$3");
            left = *(const U128 *)s1;
            asm volatile("pcpyld %0,%1,%1" : "=r"(wide_ones) : "r"(ones));
            right = *(const U128 *)s2;
            mask = 0x8080808080808080ULL;
            asm("psubw %0,%1,%2" : "=r"(left) : "r"(left), "r"(right));
            asm("pcpyld %0,%1,%1" : "=r"(high) : "r"(mask));
            asm("pcpyud %0,%1,%2" : "=r"(upper) : "r"(left), "r"(s1));
            asm("" : "=r"(lower) : "0"(left));
            qb = (const U128 *)s2;
            asm("" : : "r"(qb));
            first_difference = upper | lower;
            if (first_difference) goto Bytes;
            {
WideLoop:
                {
                    register U128 current asm("$2");
                    register U128 inverse asm("$3");
                    register U128 zero asm("$3");
                    register U64 lo asm("$3");
                    register U64 hi asm("$2");
                    n -= 16;
                    if (!n) return 0;
                    current = *qa;
                    asm("pnor %0,$0,%1" : "=r"(inverse) : "r"(current));
                    asm("psubb %0,%1,%2" : "=r"(current) : "r"(current), "r"(wide_ones));
                    asm("pand %0,%1,%2" : "=r"(current) : "r"(current), "r"(inverse));
                    asm("pand %0,%1,%2" : "=r"(zero) : "r"(current), "r"(high));
                    asm("pcpyud %0,%1,%2" : "=r"(hi) : "r"(zero), "r"(s1));
                    asm("" : "=r"(lo) : "0"(zero));
                    if (hi | lo) return 0;
                    {
                        register unsigned int small_next asm("$2");
                        qa++;
                        small_next = n < 16;
                        asm("" : "+r"(small_next));
                        // The original probes the next quad before its count guard.
                        left = *(const volatile U128 *)qa;
                        qb++;
                        if (small_next) goto PackedDone;
                    }
                    right = *qb;
                    asm("psubw %0,%1,%2" : "=r"(left) : "r"(left), "r"(right));
                    asm("pcpyud %0,%1,%2" : "=r"(upper) : "r"(left), "r"(s1));
                    asm("" : "=r"(lower) : "0"(left));
                    difference = upper | lower;
                    if (!difference) goto WideLoop;
                }
PackedDone:
                s1 = (const char *)qa;
                s2 = (const char *)qb;
            }
        } else {
            register const U64 *wa asm("$7") = (const U64 *)s1;
            register const U64 *wb asm("$8") = (const U64 *)s2;
            register U64 high64 asm("$10");
            if (n < 8) goto ScalarDone;
            if (*(const U64 *)s1 != *(const U64 *)s2) goto Bytes;
            n -= 8;
            asm("" : "+r"(n));
            high64 = 0x8080808080808080ULL;
            asm("" : "+r"(high64));
            // First decrement precedes mask setup; later iterations decrement
            // at the loop entry. The entry label preserves those two lifetimes.
            goto ScalarBody;
            {
                do {
                    register U64 current asm("$2");
                    n -= 8;
ScalarBody:
                    if (!n) return 0;
                    current = *(const volatile U64 *)wa;
                    asm("" : "+r"(current));
                    if ((current - ones) & ~current & high64) return 0;
                    wa++; wb++;
                } while(n >= 8 && *wa == *wb);
            }
ScalarDone:
            s1 = (const char *)wa;
            s2 = (const char *)wb;
        }
    }
Bytes:
    while (n-- > 0 && *s1 == *s2) {
        if (n == 0 || *s1 == '\0') return 0;
        s1++; s2++;
    }
    {
        register unsigned int right asm("$2") = *(const unsigned char *)s2;
        register unsigned int left asm("$3");
        asm("" : "+r"(right));
        left = *(const unsigned char *)s1;
        return left - right;
    }
}
