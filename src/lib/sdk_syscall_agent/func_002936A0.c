// SLY3_CFLAGS: -O2 -G0
// Independently written C with one hardware trap. Inputs are the primary kernel API contract.
// Register bindings are only V1 selector, V0 result, and actual A0/A1 kernel arguments.
struct EE_SEMA;
struct SIF_DMA_TRANSFER;
/* Kernel selector 64: CreateSema. */
int func_002936A0(struct EE_SEMA * semaphore)
{
    register int selector __asm__("$3") = 64;
    register int result __asm__("$2");
    register struct EE_SEMA * input0 __asm__("$4") = semaphore;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector), "+r"(input0)
        :
        : "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
