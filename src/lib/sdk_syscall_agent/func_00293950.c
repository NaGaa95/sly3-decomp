// SLY3_CFLAGS: -O2 -G0
// EE kernel ABI: V1 selector, V0 result, A0 onward actual arguments.
// API declarations and selector IDs checked against the primary PS2SDK headers.
// Independently written C; only the hardware trap is an assembly intrinsic.
typedef unsigned int U64 __attribute__((mode(DI)));
struct EE_THREAD;
/* Kernel selector -104: iFlushCache. */
void func_00293950(int operation)
{
    register int selector __asm__("$3") = -104;
    register int input0 __asm__("$4") = operation;
    __asm__ volatile("syscall"
        : "+r"(selector), "+r"(input0)
        :
        : "$2", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
}
