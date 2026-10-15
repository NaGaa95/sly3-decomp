// SLY3_CFLAGS: -O2 -G0
// Independently written C with one EE kernel trap intrinsic.
// Only documented kernel selector/result/argument hardware registers are bound.
typedef unsigned int U64 __attribute__((mode(DI)));
typedef void (*SDK_VOID_HANDLER)(void);
typedef void (*SDK_SBUS_HANDLER)(int);
struct EE_SEMA;
struct EE_THREAD_STATUS;
/* Kernel selector -88: iProbeTLBEntry. */
int func_00293820(unsigned int entry_hi, unsigned int * page_mask, unsigned int * entry_lo0, unsigned int * entry_lo1)
{
    register int selector __asm__("$3") = -88;
    register int result __asm__("$2");
    register unsigned int input0 __asm__("$4") = entry_hi;
    register unsigned int * input1 __asm__("$5") = page_mask;
    register unsigned int * input2 __asm__("$6") = entry_lo0;
    register unsigned int * input3 __asm__("$7") = entry_lo1;
    /* One hardware trap, followed immediately by a zero-instruction
     * output barrier for the GCC2.95 ten-operand limit. There are no C
     * operations between them; neither argument nor selector is read again. */
    __asm__ volatile("syscall"
        : "=r"(result)
        : "r"(selector), "r"(input0), "r"(input1), "r"(input2), "r"(input3)
        : "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    __asm__ volatile(""
        : "=r"(selector), "=r"(input0), "=r"(input1), "=r"(input2), "=r"(input3)
        :
        : "memory");
    return result;
}
