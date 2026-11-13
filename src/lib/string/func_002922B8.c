// SLY3_CFLAGS: -O2 -G0 -malign-loops=3 -fno-builtin -fno-schedule-insns -fno-schedule-insns2
// strncpy at SCUS_974.64 0x002922B8, recovered from the complete EE body.
// Behavioral reference: Newlib 1.8.2 newlib/libc/string/strncpy.c.
// Newlib license: COPYING.NEWLIB in this directory.
// Packed operators are individual EE intrinsics unavailable as C operators.
// Empty constraints preserve register lifetimes and TI-to-DI low-lane views;
// they emit no instructions. C statements supply every branch and loop.
// The original's second quad probe continues into the doubleword loop
// (QReload), and its first quad probe tests ~x - ones; both are kept as-is.
typedef unsigned int U128 __attribute__((mode(TI)));
typedef unsigned int U64 __attribute__((mode(DI)));
char *func_002922B8(char *in_dst, const char *in_src, unsigned int in_count)
{
    register char *dscan asm("$4") = in_dst;
    register const char *sscan asm("$5") = in_src;
    register unsigned int count asm("$6") = in_count;
    register char *d asm("$7");
    register char *dst0 asm("$8");
    register U64 ones asm("$9");
    register U64 high asm("$10");
    register U64 w asm("$3");
    register unsigned int k asm("$2");
    asm("" : "+r"(dscan), "+r"(sscan), "+r"(count));
    {
    register unsigned int combined asm("$7");
    register unsigned int lim asm("$9");
    register unsigned int sixteen asm("$10");
    register unsigned int c7 asm("$2");
    dst0 = dscan;
    combined = (unsigned int)sscan | (unsigned int)dscan;
    sixteen = 16;
    c7 = combined & 7;
    lim = 8;
    asm("" : "+r"(dst0), "+r"(combined), "+r"(sixteen), "+r"(c7), "+r"(lim));
    if (!c7) {
        register unsigned int c15 asm("$2") = combined & 15;
        register unsigned int small asm("$2");
        asm("" : "+r"(c15));
        if (!c15) lim = sixteen;
        asm("" : "+r"(lim));
        if (!c15) {
            register U128 wones asm("$9");
            register U128 whigh asm("$10");
            register U128 x asm("$3");
            register U128 t asm("$2");
            register U64 hi asm("$3");
            register U64 lo asm("$2");
            small = count < lim;
            if (small) goto Bytes;
            {
            register U64 pattern asm("$7") = 0x0101010101010101ULL;
            x = *(const U128 *)sscan;
            asm("pcpyld %0,%1,%1" : "=r"(wones) : "r"(pattern));
            }
            asm("pnor %0,$0,%1" : "=r"(x) : "r"(x));
            {
            register U64 pattern asm("$7") = 0x8080808080808080ULL;
            asm("psubb %0,%1,%2" : "=r"(t) : "r"(x), "r"(wones));
            asm("pcpyld %0,%1,%1" : "=r"(whigh) : "r"(pattern));
            }
            asm("pand %0,%1,%2" : "=r"(t) : "r"(t), "r"(x));
            asm("pand %0,%1,%2" : "=r"(t) : "r"(t), "r"(whigh));
            asm("pcpyud %0,%1,%2" : "=r"(hi) : "r"(t), "r"(dscan));
            asm("" : "=r"(lo) : "0"(t));
            d = dst0;
            hi = lo | hi;
            if (hi) goto Out;
            x = *(const volatile U128 *)sscan;
            count -= 16;
            sscan += 16;
            asm("" : "+r"(sscan));
            small = count < 16;
            *(U128 *)d = x;
            d += 16;
            if (small) goto Out;
            {
            register U128 y asm("$2");
            register U128 z asm("$3");
            y = *(const volatile U128 *)sscan;
            asm("pnor %0,$0,%1" : "=r"(z) : "r"(y));
            asm("psubb %0,%1,%2" : "=r"(y) : "r"(y), "r"(wones));
            asm("pand %0,%1,%2" : "=r"(y) : "r"(y), "r"(z));
            asm("pand %0,%1,%2" : "=r"(y) : "r"(y), "r"(whigh));
            asm("pcpyud %0,%1,%2" : "=r"(hi) : "r"(y), "r"(dscan));
            asm("" : "=r"(lo) : "0"(y));
            lo = lo | hi;
            }
            if (!lo) goto QReload;
            // Keeps the fall-through store out of the branch delay slot.
            asm volatile("");
            dscan = d;
            goto Bytes;
        } else {
            register U64 v asm("$2");
            small = count < lim;
            if (small) goto Bytes;
            w = *(const U64 *)sscan;
            ones = 0x0101010101010101ULL;
            high = 0x8080808080808080ULL;
            v = w - ones;
            w = ~w;
            v &= w;
            v &= high;
            d = dst0;
            if (v) goto Out;
            w = *(const U64 *)sscan;
            for (;;) {
Dword:
                count -= 8;
                sscan += 8;
                asm("" : "+r"(sscan));
                small = count < 8;
                *(U64 *)d = w;
                d += 8;
                if (small) break;
                v = *(const volatile U64 *)sscan;
                {
                    register U64 nv asm("$3") = ~v;
                    v -= ones;
                    v &= nv;
                }
                v &= high;
                if (!v) goto Reload;
                asm volatile("");
                break;
            }
        }
Out:
        dscan = d;
    }
    }
Bytes:
    for (;;) {
        int c;
        if (count == 0) goto Empty;
        c = *(const unsigned char *)sscan;
        asm("" : "+r"(c));
        --count;
        sscan++;
        *dscan = c;
        dscan++;
        if ((char)c == '\0') break;
    }
    k = count;
    count--;
    if (k) {
        do {
            *dscan = '\0';
            k = count;
            dscan++;
            count--;
        } while (k);
    }
Done:
    asm("" : : "r"(k));
    return dst0;
    // Out-of-line count==0 exit: its copy fills the loop-test delay slot.
Empty:
    k = count;
    goto Done;
    // Reload blocks: their loads become the annulled delay-slot insns.
Reload:
    w = *(const U64 *)sscan;
    goto Dword;
QReload:
    {
        register U128 x asm("$3");
        x = *(const U128 *)sscan;
    }
    goto Dword;
}
