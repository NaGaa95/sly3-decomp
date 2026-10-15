// SLY3_CFLAGS: -O2 -G0
// Primary _GetGsDxDyOffset contract; same reviewed GCC2.95 zero-instruction output marker.
/* Kernel selector 128: _GetGsDxDyOffset. */
void func_0029F260(int mode, int * dx, int * dy, int * dw, int * dh)
{
    register int selector __asm__("$3") = 128;
    register int input0 __asm__("$4") = mode;
    register int * input1 __asm__("$5") = dx;
    register int * input2 __asm__("$6") = dy;
    register int * input3 __asm__("$7") = dw;
    register int * input4 __asm__("$8") = dh;
    /* One hardware trap, followed immediately by a zero-instruction
     * output barrier for the GCC2.95 ten-operand limit. There are no C
     * operations between them; neither argument nor selector is read again. */
    __asm__ volatile("syscall"
        : 
        : "r"(selector), "r"(input0), "r"(input1), "r"(input2), "r"(input3), "r"(input4)
        : "$2", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    __asm__ volatile(""
        : "=r"(selector), "=r"(input0), "=r"(input1), "=r"(input2), "=r"(input3), "=r"(input4)
        :
        : "memory");
}
