// SLY3_CFLAGS: -O2 -G0
// Independently written C with one EE kernel trap intrinsic.
// Only documented kernel selector/result/argument hardware registers are bound.
typedef unsigned int U64 __attribute__((mode(DI)));
typedef void (*SDK_VOID_HANDLER)(void);
typedef void (*SDK_SBUS_HANDLER)(int);
struct EE_SEMA;
struct EE_THREAD_STATUS;
/* Kernel selector 110: SetOsdConfigParam2. */
void func_002939A0(void * configuration, int size, int offset)
{
    register int selector __asm__("$3") = 110;
    register void * input0 __asm__("$4") = configuration;
    register int input1 __asm__("$5") = size;
    register int input2 __asm__("$6") = offset;
    __asm__ volatile("syscall"
        : "+r"(selector), "+r"(input0), "+r"(input1), "+r"(input2)
        :
        : "$2", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
}
