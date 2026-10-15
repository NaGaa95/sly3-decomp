// SLY3_CFLAGS: -O2 -G0
// Independently written C with one hardware trap. Inputs are the primary kernel API contract.
// Register bindings are only V1 selector, V0 result, and actual A0/A1 kernel arguments.
struct EE_SEMA;
struct SIF_DMA_TRANSFER;
/* Kernel selector 74: SetOsdConfigParam. */
void func_00293740(void * configuration)
{
    register int selector __asm__("$3") = 74;
    register void * input0 __asm__("$4") = configuration;
    __asm__ volatile("syscall"
        : "+r"(selector), "+r"(input0)
        :
        : "$2", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "hi", "lo", "hi1", "lo1", "memory");
}
