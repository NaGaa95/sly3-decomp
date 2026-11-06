// SLY3_CFLAGS: -O2 -G0
// EE kernel syscall stub: selector 18 (AddDmacHandler). Any further arguments pass through untouched in $a0-$a3.
int func_002933B0(int cause, int (*handler)(int cause), int next)
{
    register int selector __asm__("$3") = 18; /* kernel selector register */
    int result;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector)
        : "r"(cause), "r"(handler), "r"(next)
        : "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
