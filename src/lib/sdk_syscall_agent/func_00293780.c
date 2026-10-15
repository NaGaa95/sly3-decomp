// SLY3_CFLAGS: -O2 -G0
// Independently written C with one EE kernel trap intrinsic.
// Only documented kernel selector/result/argument hardware registers are bound.
typedef unsigned int U64 __attribute__((mode(DI)));
typedef void (*SDK_VOID_HANDLER)(void);
typedef void (*SDK_SBUS_HANDLER)(int);
struct EE_SEMA;
struct EE_THREAD_STATUS;
/* Kernel selector 78: SetGsHParam. */
void func_00293780(void * addr1, void * addr2, void * addr3, void * addr4)
{
    register int selector __asm__("$3") = 78;
    register void * input0 __asm__("$4") = addr1;
    register void * input1 __asm__("$5") = addr2;
    register void * input2 __asm__("$6") = addr3;
    register void * input3 __asm__("$7") = addr4;
    /* One hardware trap, followed immediately by a zero-instruction
     * output barrier for the GCC2.95 ten-operand limit. There are no C
     * operations between them; neither argument nor selector is read again. */
    __asm__ volatile("syscall"
        : 
        : "r"(selector), "r"(input0), "r"(input1), "r"(input2), "r"(input3)
        : "$2", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    __asm__ volatile(""
        : "=r"(selector), "=r"(input0), "=r"(input1), "=r"(input2), "=r"(input3)
        :
        : "memory");
}
