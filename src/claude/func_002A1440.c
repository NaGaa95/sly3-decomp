// Sly 2 counterpart: _pad_intr_hdr (decomp src/lib/_pad_intr_hdr.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern int (*D_004D11C4)(void *);
extern void *D_004D11C0;
int func_002A1440(void **p)
{
    void *gp;
    int (*f)(void *) = D_004D11C4;
    if (f) {
        __asm__ volatile("move %0, $gp\n\tlw $gp, %1" : "=&r"(gp) : "m"(D_004D11C0));
        f(p[3]);
        __asm__ volatile("move $gp, %0" : : "r"(gp));
    }
    __asm__ volatile("sync.l\n\tei");
}
