// Sly 2 counterpart: _sceFs_Poff_Intr (decomp src/lib/_sceFs_Poff_Intr.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
typedef struct { void (*func)(void *); void *arg; } PoffCb;
extern void *D_004CC7C0;
void func_00296810(void *pkt, PoffCb *cb)
{
    void (*f)(void *) = cb->func;
    if (f) {
        void *gp;
        __asm__ volatile("move %0, $gp\n\tlw $gp, %1" : "=&r"(gp) : "m"(D_004CC7C0));
        f(cb->arg);
        __asm__ volatile("move $gp, %0" : : "r"(gp));
    }
    __asm__ volatile("sync");
    __asm__ volatile("ei");
}
