// SLY3_CFLAGS: -O2 -G0
// Independently written C with one EE kernel trap intrinsic.
// Only documented kernel selector/result/argument hardware registers are bound.
typedef unsigned int U64 __attribute__((mode(DI)));
typedef void (*SDK_VOID_HANDLER)(void);
typedef void (*SDK_SBUS_HANDLER)(int);
struct EE_SEMA;
struct EE_THREAD_STATUS;
/* Kernel selector -49: iReferThreadStatus. */
int func_002935B0(int thread_id, struct EE_THREAD_STATUS * status)
{
    register int selector __asm__("$3") = -49;
    register int result __asm__("$2");
    register int input0 __asm__("$4") = thread_id;
    register struct EE_THREAD_STATUS * input1 __asm__("$5") = status;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector), "+r"(input0), "+r"(input1)
        :
        : "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
