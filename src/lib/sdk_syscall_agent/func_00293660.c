// SLY3_CFLAGS: -O2 -G0
// Independently written C with one EE kernel trap intrinsic.
// Only documented kernel selector/result/argument hardware registers are bound.
typedef unsigned int U64 __attribute__((mode(DI)));
typedef void (*SDK_VOID_HANDLER)(void);
typedef void (*SDK_SBUS_HANDLER)(int);
struct EE_SEMA;
struct EE_THREAD_STATUS;
/* Kernel selector 60: SetupThread. */
void * func_00293660(void * global_pointer, void * stack, int stack_size, void * arguments, void * root_function)
{
    register int selector __asm__("$3") = 60;
    register void * result __asm__("$2");
    register void * input0 __asm__("$4") = global_pointer;
    register void * input1 __asm__("$5") = stack;
    register int input2 __asm__("$6") = stack_size;
    register void * input3 __asm__("$7") = arguments;
    register void * input4 __asm__("$8") = root_function;
    /* One hardware trap, followed immediately by a zero-instruction
     * output barrier for the GCC2.95 ten-operand limit. There are no C
     * operations between them; neither argument nor selector is read again. */
    __asm__ volatile("syscall"
        : "=r"(result)
        : "r"(selector), "r"(input0), "r"(input1), "r"(input2), "r"(input3), "r"(input4)
        : "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    __asm__ volatile(""
        : "=r"(selector), "=r"(input0), "=r"(input1), "=r"(input2), "=r"(input3), "=r"(input4)
        :
        : "memory");
    return result;
}
