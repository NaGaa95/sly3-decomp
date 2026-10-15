// SLY3_CFLAGS: -O2 -G0
// Independently written C with one hardware trap. Inputs are the primary kernel API contract.
// Register bindings are only V1 selector, V0 result, and actual A0/A1 kernel arguments.
struct EE_SEMA;
struct SIF_DMA_TRANSFER;
/* Kernel selector 19: RemoveDmacHandler. */
int func_002933D0(int channel, int handler_id)
{
    register int selector __asm__("$3") = 19;
    register int result __asm__("$2");
    register int input0 __asm__("$4") = channel;
    register int input1 __asm__("$5") = handler_id;
    __asm__ volatile("syscall"
        : "=r"(result), "+r"(selector), "+r"(input0), "+r"(input1)
        :
        : "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
    return result;
}
