// SLY3_CFLAGS: -O2 -G0
// EE kernel syscall stub: selector 91. Any further arguments pass through untouched in $a0-$a3.
int func_002985D8(void)
{
    register int selector __asm__("$3") = 91; /* kernel selector register */
    int result;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector)
        :
        : "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
