// SLY3_CFLAGS: -O2 -G0
/* Kernel selector 91: GetEntryAddress. */
void * func_00299EF0(int syscall_number)
{
    register int selector __asm__("$3") = 91;
    register void * result __asm__("$2");
    register int input0 __asm__("$4") = syscall_number;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector), "+r"(input0)
        :
        : "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
