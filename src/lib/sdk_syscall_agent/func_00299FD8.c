// SLY3_CFLAGS: -O2 -G0
/* Kernel selector 86: _SetTLBEntry. */
int func_00299FD8(unsigned int index, unsigned int page_mask, unsigned int entry_hi, unsigned int entry_lo0, unsigned int entry_lo1)
{
    register int selector __asm__("$3") = 86;
    register int result __asm__("$2");
    register unsigned int input0 __asm__("$4") = index;
    register unsigned int input1 __asm__("$5") = page_mask;
    register unsigned int input2 __asm__("$6") = entry_hi;
    register unsigned int input3 __asm__("$7") = entry_lo0;
    register unsigned int input4 __asm__("$8") = entry_lo1;
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
