// SLY3_ASFIX: sdk-branch-fold
// SLY3_CFLAGS: -O2 -G0 -malign-loops=2 -fno-schedule-insns2
typedef unsigned int U128 __attribute__((mode(TI)));
typedef unsigned int U64 __attribute__((mode(DI)));
int memcmp(const void *p1, const void *p2, unsigned int n)
{
    register const unsigned char *a asm("$4") = p1;
    register const unsigned char *b asm("$5") = p2;
    if(n>=sizeof(U128)&& !(((unsigned int)a|(unsigned int)b)&15)) {
        do {
            register U128 first asm("$3") = *(const U128*)a;
            register unsigned int small asm("$7") = n < sizeof(U128)*2;
            register U128 second asm("$2") = *(const U128*)b;
            register U128 lanes asm("$8");
            register U64 lower asm("$8"), upper asm("$10");
            register U64 different asm("$9");
            a+=16;
            asm("" : "+r"(a));
            /* R5900 XOR/extract intrinsics. The tied scalar output exposes the
             * lower64 bits without emitting a whole-register copy. */
            asm("pxor %0,%1,%2" : "=r"(lanes) : "r"(second), "r"(first));
            asm("pcpyud %0,%2,%3" : "=r"(upper), "=r"(lower) : "1"(lanes), "r"(small));
            different=upper|lower;
            asm("" : "+r"(different));
            b=different ? b : b+16;
            if(different) { a-=16; break; }
            n-=sizeof(U128);
            if(small) break;
        } while(1);
    }
    while(n--) {
        register unsigned int first asm("$3") = *a++;
        register unsigned int second asm("$2") = *b;
        if(first!=second) return first-second;
        ++b;
    }
    return 0;
}
