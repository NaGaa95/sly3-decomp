// Sly 2 counterpart: _sceCd_Poff_Intr (decomp src/lib/_sceCd_Poff_Intr.c)
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
extern void (*D_004D0C48)(void *);
extern void *D_004D0C4C;
extern void *D_004D0C50;
extern int D_0034C3A4;
void func_002A01B0(void)
{
    void *gp;
    void (*f)(void *) = D_004D0C48;
    if (f && !D_0034C3A4) {
        __asm__ volatile("move %0, $gp\n\tlw $gp, %1" : "=&r"(gp) : "m"(D_004D0C4C));
        f(D_004D0C50);
        __asm__ volatile("move $gp, %0" : : "r"(gp));
    }
}
