// SLY3_CFLAGS: -O2 -G0
// Independently written C with one EE kernel trap intrinsic.
// Only documented kernel selector/result/argument hardware registers are bound.
typedef unsigned int U64 __attribute__((mode(DI)));
typedef void (*SDK_VOID_HANDLER)(void);
typedef void (*SDK_SBUS_HANDLER)(int);
struct EE_SEMA;
struct EE_THREAD_STATUS;
/* Kernel selector 126: MachineType. */
int func_00293AF0(void)
{
    register int selector __asm__("$3") = 126;
    register int result __asm__("$2");
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector)
        :
        : "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
