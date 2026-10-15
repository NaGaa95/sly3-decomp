// SLY3_CFLAGS: -O2 -G0
// EE kernel ABI: V1 selector, V0 result, A0 onward actual arguments.
// API declarations and selector IDs checked against the primary PS2SDK headers.
// Independently written C; only the hardware trap is an assembly intrinsic.
typedef unsigned int U64 __attribute__((mode(DI)));
struct EE_THREAD;
/* Kernel selector 34: StartThread. */
int func_002934C0(int thread_id, void * argument)
{
    register int selector __asm__("$3") = 34;
    register int result __asm__("$2");
    register int input0 __asm__("$4") = thread_id;
    register void * input1 __asm__("$5") = argument;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector), "+r"(input0), "+r"(input1)
        :
        : "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
