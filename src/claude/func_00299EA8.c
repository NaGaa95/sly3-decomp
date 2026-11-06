// SLY3_CFLAGS: -O2 -G0
// Independently written C with one EE kernel trap intrinsic (style of src/lib/sdk_syscall_agent).
// Only documented kernel selector/result/argument hardware registers are bound.
/* Kernel selector 0x5A: kCopy(dest, src, size), called by InitTLBFunctions. */
int func_00299EA8(void *dest, const void *src, int size)
{
    register int selector __asm__("$3") = 0x5A;
    register int result __asm__("$2");
    register void *input0 __asm__("$4") = dest;
    register const void *input1 __asm__("$5") = src;
    register int input2 __asm__("$6") = size;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector), "+r"(input0), "+r"(input1), "+r"(input2)
        :
        : "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
