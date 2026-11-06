// SLY3_CFLAGS: -O2 -G0
// EE kernel syscall stub: selector 80. Any further arguments pass through untouched in $a0-$a3.
int func_002937A0(void)
{
    register int selector __asm__("$3") = 80; /* kernel selector register */
    int result;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector)
        :
        : "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
