// SLY3_CFLAGS: -O2 -G0
// Two EE kernel syscall stubs (selectors 2 and 3); config/functions.csv gives func_002932A0 both of them.
int func_002932A0(void)
{
    register int selector __asm__("$3") = 2; /* kernel selector register */
    int result;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector)
        :
        : "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}

int func_002932B0(void)
{
    register int selector __asm__("$3") = 3; /* kernel selector register */
    int result;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector)
        :
        : "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
