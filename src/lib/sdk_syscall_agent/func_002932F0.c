// SLY3_CFLAGS: -O2 -G0
// Independently written C with one EE kernel trap intrinsic.
// Only documented kernel selector/result/argument hardware registers are bound.
typedef unsigned int U64 __attribute__((mode(DI)));
typedef void (*SDK_VOID_HANDLER)(void);
typedef void (*SDK_SBUS_HANDLER)(int);
struct EE_SEMA;
struct EE_THREAD_STATUS;
/* Kernel selector 7: _ExecPS2. */
int func_002932F0(void * entry, void * global_pointer, int argument_count, char ** arguments)
{
    register int selector __asm__("$3") = 7;
    register int result __asm__("$2");
    register void * input0 __asm__("$4") = entry;
    register void * input1 __asm__("$5") = global_pointer;
    register int input2 __asm__("$6") = argument_count;
    register char ** input3 __asm__("$7") = arguments;
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
