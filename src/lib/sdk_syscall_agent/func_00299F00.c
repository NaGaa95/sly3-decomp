// SLY3_CFLAGS: -O2 -G0
/* Kernel selector 116: SetSyscall. */
void func_00299F00(int syscall_number, void * handler)
{
    register int selector __asm__("$3") = 116;
    register int input0 __asm__("$4") = syscall_number;
    register void * input1 __asm__("$5") = handler;
    __asm__ volatile("syscall"
        : "+r"(selector), "+r"(input0), "+r"(input1)
        :
        : "$2", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
}
